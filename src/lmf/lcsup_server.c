/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock.de>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "lcsup_server.h"
#include <poll.h>

static ogs_list_t poll_handles;

/* Remove a poll handle from global list using a socket reference */
static bool lmf_remove_poll_handle_by_socket(ogs_sock_t *sock)
{
	lmf_poll_handle_t *handle = NULL;

	ogs_assert(sock);

	ogs_list_for_each(&poll_handles, handle) {
		ogs_assert(handle);
		if(handle->sock == sock)
		{
			ogs_list_remove(&poll_handles, handle);
			ogs_pollset_remove(handle->handle);
			ogs_free(handle);
			return true;
		}
	}

	ogs_warn("No poll handle found in global list for socket %p.", sock);
	return false;
}

/* Handler for received UL LCS-UP TRANSPORT messages */
static void lmf_ue_handle_ul_lcsup_transport(short when, ogs_socket_t fd, void *data)
{
	int rv;
	uint32_t size, recv = 0;
	uint8_t buf[16384] = {0}; //default TLS record size
	lmf_lcs_up_context_t *context = data;
	lmf_location_request_t *location_request = NULL;
	ogs_pkbuf_t *pkbuf = NULL;
	ogs_upp_message_t message;
	ogs_upp_lcs_lpp_payload_t *cur = NULL;
	lmf_event_t *e = NULL;

	ogs_assert(context);
	ogs_assert(context->tls);
	ogs_assert(context->tls->handle);

	/* Stop timer INACTIVITY before continue */
	CLEAR_LCS_UP_TIMER(context->inactivity);

	/* Allocate a new pkbuf structure */
	size = 65795; //maximum size of a UL LCS-UP TRANSPORT message (TS 24.572, 10.2.1.1)
	pkbuf = ogs_pkbuf_alloc(NULL, size);
	ogs_assert(pkbuf);
	ogs_pkbuf_put(pkbuf, size);

	/* Message reception by TLS records */
	while((rv = wolfSSL_read(context->tls->handle, buf, 16384)) > 0)
	{
		/* Check if enough memory is still there */
		if(recv + rv > size)
		{
			ogs_error("[%s] Received data size exceeds expected UL LCS-UP TRANSPORT message size (%d > %d).", context->supi, rv + recv, size);
			ogs_pkbuf_free(pkbuf);
			goto end;
		}

		/* Copy data to target pkbuf */
		ogs_assert(ogs_pkbuf_pull(pkbuf, rv));
		memcpy(pkbuf->data - rv, buf, rv);

		/* Adjust received data size */
		recv += rv;

		/* If less than a TLS record was received, it is assumed that not more data is available. */
        if(rv < 16384)
        {
			break;
        }
	}

	/* Check for an error during message reception */
	if(rv <= 0)
	{
		ogs_error("[%s] Error detected during data reception via TLS.", context->supi);
		ogs_pkbuf_free(pkbuf);
		goto end;
	}

	/* Align pkbuf structure */
	ogs_assert(ogs_pkbuf_push(pkbuf, recv));
    pkbuf->len = recv;

	/* Decode received LCS-UPP message */
	rv = ogs_upp_decode(&message, pkbuf);
	if(rv != recv)
	{
		ogs_error("[%s] Received LCS-UPP message could not be decoded completely (%d/%d B).", context->supi, rv, recv);
		ogs_pkbuf_free(pkbuf);
		goto end;
	}

	ogs_pkbuf_free(pkbuf);

	/* Check, if the received message is an UL LCS-UP TRANSPORT message */
	if(message.type != LCS_UPP_UL_LCS_TRANSPORT)
	{
		ogs_error("[%s] Received LCS-UPP message is of wrong type (%s).", context->supi, ogs_upp_get_message_name(message.type));
		goto end;
	}

	/*
	 * TS 24.572, 6.2.1.1.6:
	 *
	 * d) Uplink LCS-UP transport procedure and network initiated user plane connection establishment procedure collision
	 *	If the LMF receives an UL LCS-UP TRANSPORT message via an LCS secured user plane connection bound to
	 *	a UE, and the network initiated user plane connection establishment procedure is ongoing, the LMF shall store
	 *	the UL LCS-UP TRANSPORT message associated with the UE. After the network initiated user plane
	 *	connection establishment procedure is completed successfully, the LMF shall process the stored UL LCS-UP
	 *	TRANSPORT messages associated with the UE. If the network initiated user plane connection establishment
	 *	procedure fails, the LMF shall discard the stored UL LCS-UP TRANSPORT messages associated with the UE.
	 */
	if(context->status != OpenAPI_up_connection_status_ESTABLISHED)
	{
		/* If there is already a pending UL LCS-UP TRANSPORT message, we will drop the received message. */
		if(context->message)
		{
			ogs_error("[%s] LCS-UP connection is currently not established and an UL LCS-UP TRANSPORT message is already pending. Drop received message.", context->supi);
			goto end;
		}

		/* Store received UL LCS-UP TRANSPORT message */
		ogs_warn("[%s] LCS-UP connection is currently not established. Store received UL LCS-UP TRANSPORT message.", context->supi);
		context->message = ogs_calloc(1, sizeof(message));
		ogs_assert(context->message);
		memcpy(context->message, &message, sizeof(message));

		goto end;
	}

	/* Check included LCS-UP payload type */
	switch(message.lcs.ul_lcs_up_transport.payload_container_type.value)
	{
		/* LTE Positioning Protocol (LPP) payload */
		case LCS_UPP_PAYLOAD_TYPE_LPP:
			/* Look up the corresponding LR based on the included Session Identity IE */
			char *tmp = ogs_calloc(message.lcs.ul_lcs_up_transport.session_identity.length + 1, sizeof(char));
			ogs_assert(tmp && atoi(tmp) > 0 && atoi(tmp) <= LCS_UPP_SESSION_IDENTITY_MAX);
			memcpy(tmp, message.lcs.ul_lcs_up_transport.session_identity.identity, message.lcs.ul_lcs_up_transport.session_identity.length);

			if((location_request = lmf_location_request_find_by_lcs_id(atoi(tmp))) == NULL)
			{
				ogs_error("[%s] No LR context found for Session Identity %s included in UL LCS-UP TRANSPORT message.", context->supi, tmp);
				ogs_free(tmp);
				goto end;
			}
			ogs_free(tmp);

			/* Loop over each LPP message that is included in the LCS-UP payload IE */
			for(recv = 0, cur = (ogs_upp_lcs_lpp_payload_t*) message.lcs.ul_lcs_up_transport.payload.contents, size = ntohs(message.lcs.ul_lcs_up_transport.payload.length); recv < size;)
			{
				/* Extract encoded LPP message from LCS-UP payload IE */
				cur->length = ntohs(cur->length);
				pkbuf = ogs_pkbuf_alloc(NULL, cur->length);
				ogs_assert(pkbuf && ogs_pkbuf_pull(pkbuf, cur->length));
				ogs_pkbuf_put(pkbuf, cur->length);
				memcpy(pkbuf->data - cur->length, message.lcs.ul_lcs_up_transport.payload.contents + recv + 2, cur->length);
				ogs_assert(ogs_pkbuf_push(pkbuf, cur->length));
				pkbuf->len = cur->length;

				/* Forward extracted LPP payload to target LPP entity */
				if(!OGS_FSM_STATE(&location_request->lpp.sm))
				{
					ogs_error("[%s] LPP state machine of LR %d is currently not running. Stop processing of UL LCS-UP TRANSPORT message.", context->supi, location_request->correlation_id);
					ogs_pkbuf_free(pkbuf);
					break;
				}

				else
				{
					/* Create a new LMF event */
            		e = lmf_event_new(LMF_EVENT_LPP_MESSAGE_UP);
		            ogs_assert(e);
        		    e->lr_id = location_request->id;
            		e->message = pkbuf; //@pkbuf is freed by target entity

		            rv = ogs_queue_push(ogs_app()->queue, e);
        		    if (rv != OGS_OK) {
                		ogs_error("ogs_queue_push() failed: %d", (int)rv);
                		ogs_pkbuf_free(e->message);
                		ogs_event_free(e);
						break;
    		        }
				}

				/* Update the number of processed octets and set @cur to its next position */
				recv += (2 + cur->length);
				cur = (ogs_upp_lcs_lpp_payload_t*) (message.lcs.ul_lcs_up_transport.payload.contents + recv);
			}

			if(recv < size)
			{
				ogs_warn("[%s] Only %d/%d B processed of LPP payload of UL LCS-UP TRANSPORT message.", context->supi, recv, size);
			}

			break;

		case LCS_UPP_PAYLOAD_TYPE_LCS:
			ogs_warn("[%s] LCS-UP payload of type LCS is currently not handled.", context->supi);
			goto end;

		default:
			ogs_error("[%s] Unknown LCS-UP payload type detected (%.2x).", context->supi, message.lcs.ul_lcs_up_transport.payload_container_type.value);
	}

end:
	/* Restart INACTIVITY timer */
	ogs_timer_start(context->inactivity.timer, lmf_timer_cfg(LMF_TIMER_INACTIVITY)->duration);
}

/* Handler that is triggered when a LCS-UP Binding Request message has been received after TLS handshake */
static void lmf_ue_binding_request_received(short when, ogs_socket_t fd, void *data)
{
    int ret;
    uint32_t *ptr;

    ogs_pkbuf_t *pkbuf = NULL;
    ogs_upp_message_t upp;
    ogs_pool_id_t binding_id = 0;
    lmf_lcs_up_context_t *ctx = NULL;

	lmf_binding_params_t *params = NULL;

    ogs_assert(fd != INVALID_SOCKET);
    params = data;
    ogs_assert(params);
	ogs_assert(params->ssl);
	ogs_assert(params->sock);

    /* Allocate a new pkbuf structure */
    pkbuf = ogs_pkbuf_alloc(NULL, 257); //LCS-UP BINDING REQUEST message size (TS 24.572, 10.2.3.1)

    if(!pkbuf)
    {
        ogs_error("LCS-UP BINDING procedure failed (pkbuf).");
        goto reject;
    }

    /* Set size to target UPP message size */
    ogs_pkbuf_put(pkbuf, 257);

    /* Read LCS-UPP message from TLS  */
    ret = wolfSSL_read(params->ssl, pkbuf->data, pkbuf->len);
    if(ret < UPP_CM_LCS_UP_BINDING_ID_MIN + 2)
    {
        ogs_error("LCS-UP BINDING procedure failed (TLS I/O).");
        goto reject;
    }
    pkbuf->len = ret;

    /* Decode received UPP message */
    ret = ogs_upp_decode(&upp, pkbuf);
    if(ret < UPP_CM_LCS_UP_BINDING_ID_MIN + 2)
    {
        ogs_error("LCS-UP BINDING procedure failed (decode, %d B).", pkbuf->len);
        goto reject;
    }
    ogs_pkbuf_free(pkbuf);
    pkbuf = NULL;

    /* Process decoded UPP message */
    if(upp.type != LCS_UPP_CONN_BINDING_REQUEST &&
       upp.present != OGS_UPP_MESSAGE_PRESENT_LCS)
    {
        ogs_error("LCS-UP BINDING procedure failed (message type).");
        goto reject;
    }

    /* Convert included BINDING ID IE */
    if(upp.lcs.binding_request.binding_id.length > UPP_CM_LCS_UP_BINDING_ID_MIN)
    {
        ogs_error("LCS-UP BINDING procedure failed (binding ID).");
        goto reject;
    }
    ptr = (uint32_t*) upp.lcs.binding_request.binding_id.binding_id;
    binding_id = ntohl(*ptr);

    ogs_debug("LCS-UP BINDING REQUEST message received with ID=%d.", binding_id);

	/* Searching for the corresponding LCS-UP context */
    ctx = lmf_find_lcs_up_context_by_id(binding_id);
    if(!ctx)
    {
        ogs_error("LCS-UP BINDING procedure failed (no LCS-UP context).");
        goto reject;
    }

    /* Allocate pkbuf for successful response */
    pkbuf = ogs_pkbuf_alloc(NULL, 1); //LCS-UP BINDING ACCEPT message size (TS 24.572, 10.2.4.1)
    if(!pkbuf)
    {
        ogs_error("LCS-UP BINDING procedure failed (pkbuf).");
        goto reject;
    }
    ogs_pkbuf_put(pkbuf, 1);

    /* Create LMF LCS-UP TLS context */
    ctx->tls = ogs_calloc(1, sizeof(lmf_tls_context_t));
    ogs_assert(ctx->tls);

    ctx->tls->base = params->base;
    ctx->tls->handle = (void*) params->ssl;
    ctx->tls->sock = params->sock;

    /* Send LCS-UP BINDING ACCEPT message to UE */
    memset(&upp, 0, sizeof(ogs_upp_message_t));
    upp.type = LCS_UPP_CONN_BINDING_ACCEPT;

    ret = ogs_upp_encode(pkbuf, &upp);
    if(ret != 1)
    {
        ogs_error("LCS-UP BINDING procedure failed (encode).");
        ogs_free(ctx->tls);
        ctx->tls = 0;
        goto reject;
    }
    ogs_assert(ogs_pkbuf_push(pkbuf, ret));
    pkbuf->len = ret;

    ret = wolfSSL_write(params->ssl, pkbuf->data, pkbuf->len);
    if(ret != 1)
    {
        ogs_error("LCS-UP BINDING procedure failed (TLS I/O).");
        ogs_free(ctx->tls);
        ctx->tls = 0;
        goto reject;
    }

	/* Remove this handler from LMF's global pollset */
	while(!lmf_remove_poll_handle_by_socket(params->sock))
	{
		ogs_msleep(10);	/* To prevent race condition */
	}

    /* Install a new handler for the target LCS-UP context in LMF's global pollset (to access internal structures only by a single thread). */
    ctx->tls->recv = ogs_pollset_add(ogs_app()->pollset, OGS_POLLIN, params->sock->fd, lmf_ue_handle_ul_lcsup_transport, ctx);
    ogs_assert(ctx->tls->recv);

	ogs_free(params);

	ogs_debug("[%s] LCS-UP binding procedure successfully completed (LCS-UP context ID=%d).", ctx->supi, ctx->id);

    return;

reject:
    if(pkbuf)
    {
        ogs_pkbuf_free(pkbuf);
    }

    pkbuf = ogs_pkbuf_alloc(NULL, 1); //LCS-UP BINDING REJECT message size (TS 24.572, 10.2.5.1)
    if(!pkbuf)
    {
        goto err;
    }
    ogs_pkbuf_put(pkbuf, 1);

    /* Send LCS-UP BINDING REJECT message to UE. */
    memset(&upp, 0, sizeof(ogs_upp_message_t));
    upp.type = LCS_UPP_CONN_BINDING_REJECT;

    ret = ogs_upp_encode(pkbuf, &upp);
    if(ret != 1)
    {
        goto err;
    }
    ogs_assert(ogs_pkbuf_push(pkbuf, ret));
    pkbuf->len = ret;

    wolfSSL_write(params->ssl, pkbuf->data, pkbuf->len);

err:
    if(params->ssl)
    {
        wolfSSL_free(params->ssl);
    }
    ogs_sock_destroy(params->sock);

	ogs_free(params);

    if(pkbuf)
    {
        ogs_pkbuf_free(pkbuf);
    }

    return;
}


void
lmf_lcs_up_server_loop(void *data)
{
	int ret;
	char buf_err[80];
	lmf_lcs_up_server_t *server = NULL;
	ogs_sock_t *ue = NULL;
	struct pollfd pfd;

	WOLFSSL *ssl = NULL;

	lmf_binding_params_t *params = NULL;
	lmf_poll_handle_t *handle = NULL;

	ogs_assert(data);

	/* Get LMF LCS-UP server instance */
	server = (lmf_lcs_up_server_t*) data;
	ogs_assert(server->sock);

	/* Initialize poll handle list */
	ogs_list_init(&poll_handles);

	/* Waiting for UE requests */
	while(1)
	{
		ue = ogs_sock_accept(server->sock);
		ogs_assert(ue);

		/* Create a new TLS session context */
	    if((ssl = wolfSSL_new(server->ctx)) == NULL)
    	{
        	ogs_error("TLS session context could not be created.");
			ogs_sock_destroy(ue);
        	continue;
    	}
    	wolfSSL_set_fd(ssl, ue->fd);

		/* Waiting until the self-defined timeout expires */
		memset(&pfd, 0, sizeof(struct pollfd));
		pfd.fd = ue->fd;
		pfd.events = POLLIN;
		ret = poll(&pfd, 1, server->timeout);

		/* Continue depending on poll's return value */
		if(ret > 0)
		{
			/* Realize TLS 1.3 handshake */
    		if((ret = wolfSSL_accept(ssl)) != SSL_SUCCESS)
    		{
				memset(buf_err, 0, sizeof(buf_err));
        		ogs_error("TLS handshake with target UE failed: %s", wolfSSL_ERR_error_string(wolfSSL_get_error(ssl, ret), buf_err));
				wolfSSL_free(ssl);
        		ogs_sock_destroy(ue);
            	continue;
    		}

			/* Waiting for UE's LCS-UPP request message until the same timeout expires again */
			memset(&pfd, 0, sizeof(struct pollfd));
	        pfd.fd = ue->fd;
    	    pfd.events = POLLIN;
        	ret = poll(&pfd, 1, server->timeout);

			if(ret > 0)
			{
				/* Pass multiple params to target handler function */
				params = ogs_calloc(1, sizeof(lmf_binding_params_t));
				ogs_assert(params);
				params->ssl = ssl;
				params->sock = ue;
				params->base = server->base;

				/* Installing handler for LCS-UP Binding Requests via LMF's global pollset */
				handle = ogs_calloc(1, sizeof(lmf_poll_handle_t));
				ogs_assert(handle);

				handle->sock = ue;
				handle->handle = ogs_pollset_add(ogs_app()->pollset, OGS_POLLIN, ue->fd, lmf_ue_binding_request_received, params);
				ogs_assert(handle->handle);

				/* Adding handle to global list */
				ogs_list_add(&poll_handles, handle);
			}
			else if(!ret)
			{
				wolfSSL_shutdown(ssl);
				goto timeout;
			}
			else
			{
				wolfSSL_shutdown(ssl);
                goto tls_failure;
			}
		}
		else if(!ret)
		{
timeout:
			ogs_warn("Timeout of UE expired to initialize the TLS handshake.");
			wolfSSL_free(ssl);
			ogs_sock_destroy(ue);
			continue;
		}
		else
		{
tls_failure:
			ogs_error("Waiting for TLS handshake initiation failed: %s", strerror(errno));
			wolfSSL_free(ssl);
			ogs_sock_destroy(ue);
			continue;
		}
	}
}
