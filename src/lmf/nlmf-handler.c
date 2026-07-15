/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock>
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

#include "nlmf-handler.h"
#include "namf-build.h"
#include "context.h"
#include "sbi-path.h"

int lmf_nlmf_handle_determine_location(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
	lmf_event_t e;
    lmf_location_request_t *location_request = NULL;
	lmf_lcs_up_server_t *lcsup_server = NULL;
	ogs_pkbuf_t *pkbuf = NULL;
    OpenAPI_input_data_t *input_data = NULL;
	OpenAPI_lnode_t *node;

    ogs_assert(stream);
    ogs_assert(recvmsg);

    /* Parse InputData from message */
    input_data = recvmsg->InputData;
    if (!input_data) {
        ogs_error("No InputData in determine location request");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No InputData", NULL, NULL));
        return OGS_ERROR;
    }

    /* Extract SUPI (required) */
    if (!input_data->supi) {
        ogs_error("No SUPI in InputData");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No SUPI in InputData", NULL, NULL));
        return OGS_ERROR;
    }

	/* Extract LCS Correlation Identifier (required) */
	if(!input_data->correlation_id)
	{
		ogs_error("No LCS Correlation Identifier in InputData");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No LCS Correlation Identifier in InputData", NULL, NULL));
        return OGS_ERROR;
	}

    /* Create location request context */
    location_request = lmf_location_request_add();
    if (!location_request) {
        ogs_error("lmf_location_request_add() failed");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                recvmsg, "Internal server error", NULL, NULL));
        return OGS_ERROR;
    }

    /* Store stream ID for async response */
    location_request->stream_id = ogs_sbi_id_from_stream(stream);

	/* Store LCS Correlation identifier */
	location_request->correlation_id = atoi(input_data->correlation_id);

    /* Extract SUPI */
    location_request->supi = ogs_strdup(input_data->supi);
    ogs_assert(location_request->supi);

    /* Extract AMF ID if present */
    if (input_data->amf_id) {
        location_request->amf_id = ogs_strdup(input_data->amf_id);
        ogs_assert(location_request->amf_id);
    }

    /* Extract NR CGI if present */
    if (input_data->ncgi) {
        if(!ogs_sbi_parse_plmn_id(&location_request->nr_cgi.plmn_id, input_data->ncgi->plmn_id))
        {
			ogs_error("[%s] Included NR Global Cell Identifier of serving gNB could not be extracted", location_request->supi);
			goto err;
		}
		location_request->nr_cgi.cell_id = ogs_uint64_from_string_hexadecimal(input_data->ncgi->nr_cell_id);
    }

    /* Extract LCS Indicator if present */
    if(input_data->ue_location_service_ind != OpenAPI_ue_location_service_ind_NULL)
    {
		location_request->is_molr = true;
		location_request->lcs_service_type = input_data->ue_location_service_ind;
    }

    ogs_info("[%s] Location request: SUPI=%s, AMF_ID=%s",
            location_request->supi,
            location_request->supi,
            location_request->amf_id ? location_request->amf_id : "N/A");

    /* Store the input message in location_request for later cleanup */
    /* We need to keep it because it contains allocated OpenAPI objects (InputData) */
    location_request->input_message = ogs_calloc(1, sizeof(ogs_sbi_message_t));
    if (!location_request->input_message) {
        ogs_error("[%s] Failed to allocate input_message",
                location_request->supi);
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                recvmsg, "Internal server error", NULL, NULL));
        /* Don't free recvmsg->h here - it's shared with request->h
         * which will be freed by the server framework */
        ogs_sbi_message_free(recvmsg);
        lmf_location_request_remove(location_request);
        return OGS_ERROR;
    }
    /* Copy the message structure - this transfers ownership of allocated members */
    memcpy(location_request->input_message, recvmsg, sizeof(ogs_sbi_message_t));
    /* Clear the original message to prevent double-free when caller frees it */
    memset(recvmsg, 0, sizeof(ogs_sbi_message_t));

    /*
     * Determine positioning capabilities of UE:
     *
     * (a) if LCS over user plane and LPP is supported:
     *    - subscribe for N1 messages (UPP-CMI) to AMF
     *	  - initialize the UPP state machine and negotiate
	 *		a secure user plane connection for LCS (UPP-CM)
     *	  - goto b)
     *
	 * (b) if LPP is supported:
     *    - subscribe for N1 messages (LPP) to AMF if needed.
     *    - check, if LPP messages were already received within MO-LR.
     *    - request LPP capabilities if needed.
	 *
     * (c) otherwise: a network-based approach must be used (e.g. ECID, NR ECID)
     *	  - TODO ...
     */
    if(input_data->lpp_message || (input_data->ue_lcs_cap && input_data->ue_lcs_cap->is_lpp_support && input_data->ue_lcs_cap->lpp_support))
    {
		/* Storing LPP support in LR context */
		location_request->ue_lcs_cap.lpp = true;
	}

	/*
	 * If LCS-UP is also supported, we also initialize its state machine...
 	 */
	lcsup_server = lmf_get_lcs_up_server_instance();
	if(location_request->ue_lcs_cap.lpp && input_data->ue_up_pos_caps)
	{
    	OpenAPI_list_for_each(input_data->ue_up_pos_caps, node) {
        	OpenAPI_ue_up_positioning_capabilities_e val = (OpenAPI_ue_up_positioning_capabilities_e) node->data;

			if(val == OpenAPI_ue_up_positioning_capabilities_LCS_UPP)
			{
				/* Storing UPP support in LR context */
		   		location_request->ue_lcs_cap.lcsupp = true;
			}
			else if(val == OpenAPI_ue_up_positioning_capabilities_MULTIPLE_LCS_UPP)
			{
				/* Multiple LCS-UP connections are supported */
	   			location_request->ue_lcs_cap.mlcs_up = true;
			}
    	}
	}

	/* If LCS-UP is supported and a LCS-UP server is running, we create a corresponding context and try to establish a LCS-UP connection */
	if(location_request->ue_lcs_cap.lcsupp && lcsup_server->initialized)
	{
		/* Create a LCS-UP context if it does not exist */
        if((location_request->upp.ctx = lmf_find_lcs_up_context_by_supi(location_request->supi)) == NULL)
        {
        	location_request->upp.ctx = lmf_create_lcs_up_context(location_request->supi, location_request->ue_lcs_cap.lpp, location_request->ue_lcs_cap.mlcs_up);
            ogs_assert(location_request->upp.ctx);
        }

		/* Initialize LPP's state machine - if LPP is supported */
		if(location_request->ue_lcs_cap.lpp)
		{
			memset(&e, 0, sizeof(lmf_event_t));
        	e.lr_id = location_request->id;

			/* Add received LPP message, if present */
			if(input_data->lpp_message && (pkbuf = ogs_sbi_find_part_by_content_id(recvmsg, input_data->lpp_message->content_id)) != NULL)
			{
				e.message = ogs_pkbuf_copy(pkbuf);
				ogs_assert(e.message);
			}

        	ogs_fsm_init(&location_request->lpp.sm, lpp_state_initial, lpp_state_final, &e);
		}
	}

	/* If we are here, only LPP via control plane is possible... */
	else if(location_request->ue_lcs_cap.lpp)
	{
		/* Initialize LPP's state machine */
        memset(&e, 0, sizeof(lmf_event_t));
        e.lr_id = location_request->id;

		/* Add received LPP message, if present */
        if(input_data->lpp_message && (pkbuf = ogs_sbi_find_part_by_content_id(recvmsg, input_data->lpp_message->content_id)) != NULL)
        {
			e.message = ogs_pkbuf_copy(pkbuf);
			ogs_assert(e.message);
		}

        ogs_fsm_init(&location_request->lpp.sm, lpp_state_initial, lpp_state_final, &e);
	}

	/* Otherwise, only network-based positioning can be used... */
    else
    {
		//Here, we have to subscribe for N2 (NRPPa) messages first, when we implement it in future.
		ogs_error("[%s] No LPP/UPP support. Network-based positioning is currently not implemented.", location_request->supi);
		goto err;
    }

    /* Response will be sent asynchronously when location is determined */
    /* input_message will be freed in lmf_location_request_remove() */
    return OGS_OK;

err:
    /* Only send error if location_request still exists or can not be handled (error wasn't already sent) */
    if (location_request->input_message) {
        ogs_assert(true ==
              ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                    location_request->input_message, "Location determination failed", NULL, NULL));
        /* Free InputData explicitly before freeing message */
        if (location_request->input_message->InputData) {
            OpenAPI_input_data_free(location_request->input_message->InputData);
               location_request->input_message->InputData = NULL;
        }
        ogs_sbi_message_free(location_request->input_message);
        ogs_free(location_request->input_message);
        location_request->input_message = NULL;
    }

    /* Only remove if it wasn't already removed */
    if (location_request->supi) {
        lmf_location_request_remove(location_request);
    }

    return OGS_ERROR;
}

int lmf_nlmf_handle_upconfig(ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
	lmf_lcs_up_context_t *ctx = NULL;
	OpenAPI_up_config_t *upcfg;
	OpenAPI_lnode_t *node;
	lmf_lcs_up_server_t *lcsup_server = NULL;

	bool rc;
    OpenAPI_uri_scheme_e scheme = OpenAPI_uri_scheme_NULL;
    char *fqdn = NULL;
    uint16_t fqdn_port = 0;
    ogs_sockaddr_t *addr = NULL, *addr6 = NULL;

	ogs_assert(stream);
    ogs_assert(recvmsg);

	/* Get UpConfig IE from message */
    upcfg = recvmsg->UpConfig;
    if (!upcfg) {
        ogs_error("No UpConfig IE in SBI request");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No UpConfig", NULL, NULL));
        return OGS_ERROR;
    }

    /* Check SUPI (required) */
    if (!upcfg->supi) {
        ogs_error("No SUPI in UpConfig");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No SUPI in UpConfig", NULL, NULL));
        return OGS_ERROR;
    }

	/* Check Callback URI and Correlation ID */
	if(!upcfg->up_notify_call_back_uri || !upcfg->notif_correlation_id)
	{
		ogs_error("Missing callback URI and/or correlation ID in UpConfig IE.");
		ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "Invalid UpConfig IE", NULL, NULL));
        return OGS_ERROR;
	}

	/* Get connection indication if present */
	if(!upcfg->lcs_up_connection_ind)
	{
		ogs_warn("[%s] Received UpConfig request does not include a connection indication. SETUP is assumed.", upcfg->supi);
		upcfg->lcs_up_connection_ind = OpenAPI_lcs_up_connection_ind_SETUP;
	}

	/* Check if a LCS-UP server is running */
	lcsup_server = lmf_get_lcs_up_server_instance();
	if(!lcsup_server->initialized)
	{
		ogs_error("[%s] No LCS-UP server is currently running. Aborting...", upcfg->supi);
		ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                recvmsg, "No LCS-UP server is running", NULL, NULL));
        return OGS_ERROR;
	}

	/* Check, if LCS-UP context already exists and continue based on connection indicator */
	ctx = lmf_find_lcs_up_context_by_supi(upcfg->supi);
	switch(upcfg->lcs_up_connection_ind)
	{
		case OpenAPI_lcs_up_connection_ind_SETUP:
			if(ctx)
			{
				/*
				 * TS 24.572, 6.2.1.1.6:
				 *
				 * If the LMF receives a USER PLANE CONNECTION ESTABLISHMENT REQUEST message during the
				 * network initiated user plane connection establishment procedure, the LMF shall ignore the USER PLANE
				 * CONNECTION ESTABLISHMENT REQUEST message and proceed with the network initiated user plane
				 * connection establishment procedure.
				 */
				if(ctx->status == OpenAPI_up_connection_status_NULL)
				{
					ogs_warn("[%s] CONNECTION ESTABLISHMENT REQUEST message is ignored due to an ongoing connection establishment procedure.", ctx->supi);

					ogs_sbi_message_t sendmsg;
	                ogs_sbi_response_t *response = NULL;

					memset(&sendmsg, 0, sizeof(sendmsg));
                	response = ogs_sbi_build_response(&sendmsg, OGS_SBI_HTTP_STATUS_NO_CONTENT);
                	ogs_assert(response);
                	ogs_assert(true == ogs_sbi_server_send_response(stream, response));

                	return OGS_OK;
				}
				else
				{
					ogs_error("[%s] SETUP of an already existing LCS-UP context (ID=%d) is not allowed.", upcfg->supi, ctx->id);
	            	ogs_assert(true ==
    	        		ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                		recvmsg, "Invalid UpConfig IE", NULL, NULL));
	        	    return OGS_ERROR;
				}
			}

			if(upcfg->ue_up_pos_caps)
            {
                bool lcsupp = false, mlcs_up = false;

                OpenAPI_list_for_each(upcfg->ue_up_pos_caps, node) {
                    OpenAPI_ue_up_positioning_capabilities_e val = (OpenAPI_ue_up_positioning_capabilities_e) node->data;

                    if(val == OpenAPI_ue_up_positioning_capabilities_LCS_UPP)
                    {
                        lcsupp = true;
                    }
                    else if(val == OpenAPI_ue_up_positioning_capabilities_MULTIPLE_LCS_UPP)
                    {
                        mlcs_up = true;
                    }
                }

                /* If LCS-UPP is not supported, we reject the request! */
                if(!lcsupp)
                {
                    ogs_error("[%s] SETUP of a new LCS-UP context failed because UE does not support LCS-UPP.", upcfg->supi);
                    ogs_assert(true ==
                    ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                        recvmsg, "Invalid UpConfig IE", NULL, NULL));
                    return OGS_ERROR;
                }

                ctx = lmf_create_lcs_up_context(upcfg->supi, false, mlcs_up);
            }
            else
            {
                ogs_warn("[%s] UpConfig request does not contain UE's LCS capabilities. LCS-UPP support is assumed.", upcfg->supi);
                ctx = lmf_create_lcs_up_context(upcfg->supi, false, false);
            }
            ogs_assert(ctx);


            /* Assign correlation ID */
            ctx->correlation_id = atoi(upcfg->notif_correlation_id);

            /* Find client for AMF notifications */
            rc = ogs_sbi_getaddr_from_uri(&scheme, &fqdn, &fqdn_port, &addr, &addr6, upcfg->up_notify_call_back_uri);
	        if (rc == false || scheme == OpenAPI_uri_scheme_NULL) {
    	        ogs_error("[%s] Invalid URI [%s]", upcfg->supi, upcfg->up_notify_call_back_uri);
            	lmf_remove_lcs_up_context(ctx);

            	goto err;
        	}

        	ctx->client = ogs_sbi_client_find(scheme, fqdn, fqdn_port, addr, addr6);
			if(!ctx->client) {
            	ogs_debug("%s: ogs_sbi_client_add()", OGS_FUNC);
            	ctx->client = ogs_sbi_client_add(scheme, fqdn, fqdn_port, addr, addr6);
            	if(!ctx->client) {
                	ogs_error("%s: ogs_sbi_client_add() failed", OGS_FUNC);

                	ogs_free(fqdn);
                	ogs_freeaddrinfo(addr);
                	ogs_freeaddrinfo(addr6);

	                lmf_remove_lcs_up_context(ctx);

	                goto err;
    	       }
       		}
       		ogs_free(fqdn);
       		ogs_freeaddrinfo(addr);
       		ogs_freeaddrinfo(addr6);

			/* Store callback URI for notifications */
			ctx->amf_cb_uri = upcfg->up_notify_call_back_uri;
			upcfg->up_notify_call_back_uri = NULL;

			break;

		case OpenAPI_lcs_up_connection_ind_TERMINATION:
			if(!ctx)
			{
				ogs_error("[%s] TERMINATION of a non-existing LCS-UP context is not possible.", upcfg->supi);
	            ogs_assert(true ==
    	        ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "Invalid UpConfig IE", NULL, NULL));
        	    return OGS_ERROR;
			}

			/* No LMF relocation is needed, just remove the LCS-UP context */
			if(!upcfg->target_lmfid)
			{
				lmf_remove_lcs_up_context(ctx);

				ogs_sbi_message_t sendmsg;
				ogs_sbi_response_t *response = NULL;

				/* Build response message: TS 29.572, 6.1.4.7.2 */
			    memset(&sendmsg, 0, sizeof(sendmsg));
    			response = ogs_sbi_build_response(&sendmsg, OGS_SBI_HTTP_STATUS_NO_CONTENT);
    			ogs_assert(response);
    			ogs_assert(true == ogs_sbi_server_send_response(stream, response));

				return OGS_OK;
			}

			//TODO: move LCS-UP context to a different LMF, if @upcfg->target_lmfid is set!

			break;

		default:
			ogs_error("[%s] Unknown LCS-UP connection indication received (%.2x).", upcfg->supi, upcfg->lcs_up_connection_ind);
            ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "Invalid UpConfig IE", NULL, NULL));
            return OGS_ERROR;
	}

	/*
	 * Store stream ID for asnyc response:
	 *
	 * a) The UpConfig request includes a SETUP indicator: The response is sent,
	 *	  after the LCS-UP connection has been set up (TS 23.273, 6.18.2).
	 *
	 * b) The UpConfig request includes a TERMINATE indicator: The response is sent, when LMF relocation is completed (TS 23.273, 6.18.3).
	 *	  If a target LMF identifier is not included in the UpConfig request (@upcfg->target_lmfid), then the response is sent directly,
	 *	  after the LCS-UP connection has been removed. In the latter case, however, we do not reach this line... . :-)
	 */
	ctx->stream_id = ogs_sbi_id_from_stream(stream);

	return OGS_OK;

err:

	ogs_assert(true ==
       ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
       recvmsg, "Handling failed", NULL, NULL));

	return OGS_ERROR;
}
