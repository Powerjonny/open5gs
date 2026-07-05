/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
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
#include "context.h"
#include "sbi-path.h"
#include "namf-build.h"

#include "upp-build.h"
#include "upp-path.h"

void upp_state_initial(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

    OGS_FSM_TRAN(s, &upp_state_disconnected);
}

void upp_state_final(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

    lmf_sm_debug(e);
}

void upp_state_disconnected(ogs_fsm_t *s, lmf_event_t *e)
{
	int rv;
    lmf_lcs_up_context_t *context = NULL;
    lmf_subscribe_params_t params;
	lmf_sbi_params_t sbi_params;

	lmf_lcs_up_server_t *lcsup_server = NULL;

	ogs_upp_message_t message;

	ogs_sbi_response_t *response = NULL;
    ogs_sbi_message_t sendmsg;
	ogs_sbi_stream_t *stream = NULL;

    ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

	/* Pick up corresponding LCS-UP context */
    context = lmf_find_lcs_up_context_by_id(e->binding_id);
	ogs_assert(context);

start:
    switch (e->h.id) {

	case OGS_FSM_EXIT_SIG:
		/* Free a received UPP-CM message if present */
		if(e->message)
        {
            ogs_pkbuf_free(e->message);
            e->message = 0;
        }
        break;

    case OGS_FSM_ENTRY_SIG:
sub:
        /*
		 * If there is no N1 subscription for the target UE,
		 * we subscribe to AMF to get notifications of received UPP messages
		 */
		ogs_assert(context->supi);
		if(context->subscription == NULL &&
		   (context->subscription = lmf_find_subscription(context->supi, NULL, true)) == NULL)
		{
        	memset(&params, 0, sizeof(params));
        	params.n1 = OpenAPI_n1_message_class_UPP_CM;

			memset(&sbi_params, 0, sizeof(sbi_params));
			sbi_params.type = LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT;
			sbi_params.lcs_up_context = context;

        	rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, NULL,(ogs_sbi_request_t *(*)(lmf_sbi_params_t *, void *))lmf_namf_build_n1n2_message_subscribe,
                &sbi_params, &params);

	        if(rv != OGS_OK)
    	    {
        	    ogs_error("[%s] Subscription for N1 messages (UPP-CM) failed - remove LCS-UP context (ID=%d).", context->supi, context->id);

				//TODO: If this LCS-UP context is UE-initiated (Nlmf_Location_UPConfig), then we have to send a CONNECTION ESTABLISHMENT FAILURE message back to the UE.

				/* Terminate this state machine to remove the LCS-UP context */
				context->terminate = true;
        	}
#if 0
			else
			{
	        	ogs_info("[%s] Subscription for N1 messages (UPP) was sent to AMF (xact ID=%d)", context->supi, context->xact->id);
			}
#endif
			break;
		}

		else if(context->subscription->sid == NULL)
		{
			/*
			 * N1 subscription was sent but no response has been currently received.
			 * Therefore, we have to wait. ;-)
			 */
			break;
		}

		/* Otherwise, we go to the CONNECTION_ESTABLISHMENT event below */

	case LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT:
		if(context->subscription == NULL &&
           (context->subscription = lmf_find_subscription(context->supi, NULL, true)) == NULL)
		{
			ogs_warn("[%s] Missing subscription for UPP-CM messages. Stepping back.", context->supi);
			goto sub;
		}

		/*
		 * UPP connection establishment procedure (TS 24.572, 6.2.1.1.2):
		 *
		 * a) allocate a unique LCS-UP binding ID value and associate the LCS-UP binding ID value with the UE identity
		 *		=> this is already done: LCS-UP context has been created before.
         * b) create the USER PLANE CONNECTION ESTABLISHMENT COMMAND message;
         * c) send the USER PLANE CONNECTION ESTABLISHMENT COMMAND message to the UE; and
         * d) start a timer T5012 upon sending the USER PLANE CONNECTION ESTABLISHMENT COMMAND message
		 */

		/* Resetting timer T5012 */
		CLEAR_LCS_UP_TIMER(context->t5012);

		/* Get LCS-UP server instance */
		lcsup_server = lmf_get_lcs_up_server_instance();
		ogs_assert(lcsup_server->initialized && lcsup_server->family == AF_INET); //FIXME: Currently, only IPv4 is supported...

		/* Assign LMF LCS-UP address */
		if(!context->address.type)
		{
			context->address.type = UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4;
			rv = ogs_upp_lookup_lcs_up_address(&context->address, &lcsup_server->addr, OGS_UPP_LMF_PORT);
			ogs_expect(rv == OGS_OK);
			ogs_assert(rv != OGS_ERROR);
		}

		/* We store the encoded message if we have to retransmit it. */
		context->t5012.pkbuf = upp_build_connection_establishment_command(context->id, &context->address, NULL);
		ogs_assert(context->t5012.pkbuf);

		rv = upp_send_to_amf(context, context->t5012.pkbuf, LMF_TIMER_T5012);
		ogs_expect(rv == OGS_OK);
        ogs_assert(rv != OGS_ERROR);

		break;

	case LMF_EVENT_UPP_MESSAGE:
		ogs_assert(e->message);

		if(e->message->len != ogs_upp_decode(&message, e->message))
		{
			ogs_error("[%s] Decoding of UPP-CM message (%d B) failed.", context->supi, e->message->len);
			ogs_pkbuf_free(e->message);
			e->message = 0;
			break;
		}
		ogs_debug("[%s] UPP-CM message (%s) from AMF received (%d B).", context->supi, ogs_upp_get_message_name(message.type), e->message->len);

		/* Next actions depend on UPP-CM message type */
		switch(message.type)
		{
			case UPP_CM_CONN_ESTABLISHMENT_COMPLETE:
				/* Check if TLS context is available */
				if(!context->tls)
				{
					ogs_error("[%s] %s message received, but no TLS context is available.", context->supi, ogs_upp_get_message_name(message.type));
					break;
				}

				/*
				 * TS 24.572, 6.2.1.1.4:
				 *
				 * Upon receipt of a USER PLANE CONNECTION ESTABLISHMENT COMPLETE message from the UE, the LMF
				 * shall stop the timer T5012 and shall consider that the LCS secured user plane connection between the UE and the LMF
				 * is established.
				 */
				CLEAR_LCS_UP_TIMER(context->t5012);
				context->status = OpenAPI_up_connection_status_ESTABLISHED;

				/* Respond to AMF's UpConfig request if present */
				if(context->stream_id && (stream = ogs_sbi_stream_find_by_id(context->stream_id)) != NULL)
				{
					memset(&sendmsg, 0, sizeof(sendmsg));
				    response = ogs_sbi_build_response(&sendmsg, OGS_SBI_HTTP_STATUS_NO_CONTENT);
    				ogs_assert(response);
    				ogs_assert(true == ogs_sbi_server_send_response(stream, response));
					context->stream_id = 0;

					/* Notification to AMF that the LCS-UP connection has been established. */
					if(!lmf_sbi_send_lcsup_notification(context, NULL))
					{
						ogs_warn("[%s] AMF could not be notified about the LCS-UP connection establishment.", context->supi);
					}
				}

				ogs_info("[%s] LCS-UP connection has been successfully established.", context->supi);

				/* Moving to CONNECTED state via OGS_FSM_ENTRY_SIG event -> this is triggered by ogs_fsm_dispatch in lmf-sm.c when the state has beend changed */
				OGS_FSM_TRAN(s, &upp_state_connected);

				break;

			case UPP_CM_CONN_ESTABLISHMENT_FAILURE:
				/*
				 * TS 24.572, 6.2.1.1.5:
				 *
				 * Upon reception of a USER PLANE CONNECTION ESTABLISHMENT FAILURE message from the UE, the LMF
				 * shall stop the timer T5012, release the allocated LCS-UP binding ID value, if any, and release the association of the
				 * TLS connection with the UE, if any, abort the network initiated user plane connection establishment procedure, and
				 * consider the LCS secured user plane connection between the UE and the LMF as not established. After that, if cause
				 * value #4 "User plane not available" is not included in the USER PLANE CONNECTION ESTABLISHMENT
				 * FAILURE message, the LMF may perform the network initiated user plane connection establishment procedure as
				 * specified in clause 6.2.1.1.2. If cause value #4 "User plane not available" is included in the USER PLANE
				 * CONNECTION ESTABLISHMENT FAILURE message, the LMF should not initiate the network initiated user plane
				 * connection establishment procedure as specified in clause 6.2.1.1 and may consider to use other available positioning
				 * solutions if the location services are still needed, until the LMF receives the USER PLANE CONNECTION
				 * ESTABLISHMENT REQUEST message from the UE as specified in clause 6.2.2.1.
				 */
				CLEAR_LCS_UP_TIMER(context->t5012);

				if(context->tls)
				{
					lmf_lcs_up_context_terminate_tls(context);
				}

				if(message.cm.connection_establishment_failure.cause.value != UPP_CM_FAILURE_CAUSE_USER_PLANE_NOT_AVAILABLE)
				{
					ogs_warn("[%s] %s message (UPP-CM) received with cause %s: Try re-establishment.", context->supi, ogs_upp_get_message_name(message.type), ogs_upp_get_error_cause_name(message.cm.connection_establishment_failure.cause.value));
					e->h.id = LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT;
					ogs_pkbuf_free(e->message);
					e->message = 0;
					goto start;
				}
				else
				{
					ogs_warn("[%s] LCS-UP connection establishment failed. Waiting for a CONNECTION ESTABLISHMENT REQUEST message from UE.", context->supi);
					//TODO: If there is a LR for the target UE, we start its LPP state machine.
				}

				/* Free received UL LCS-UP message if present */
				if(context->message)
				{
					ogs_free(context->message);
					context->message = 0;
				}

				break;

			default:
				ogs_warn("[%s] %s message (UPP-CM) is not handled in DISCONNECTED state.", context->supi, ogs_upp_get_message_name(message.type));
				break;
		}

		/* Free received UPP message, if available */
	    if(e->message)
    	{
        	ogs_pkbuf_free(e->message);
			e->message = 0;
    	}

		break;

	case LMF_EVENT_UPP_TIMER:
        switch (e->h.timer_id) {
        	case LMF_TIMER_T5012:
            	if (context->t5012.retry_count >=
                    lmf_timer_cfg(LMF_TIMER_T5012)->max_count) {
                	ogs_warn("[%s] Retransmission of Connection Establishment Command failed. "
                        "Stop retransmission", context->supi);

					CLEAR_LCS_UP_TIMER(context->t5012);

					/*
					 * TS 24.572, 6.2.1.1.6a:
					 *
					 * On the fifth expiry of timer T5012, the LMF shall release the allocated LCS-UP binding ID
					 * value and its association with the UE, [...], and abort the network initiated user plane
					 * connection establishment procedure.
					 */
					context->terminate = true; //the caller frees everything (because ogs_fsm_dispatch checks state transition. So we can not remove everything from here...
	           	} else {
					/* Retransmission of Connection Establishment Command message */
                	context->t5012.retry_count++;
					ogs_assert(context->t5012.pkbuf);
					ogs_info("[%s] Retransmission %d/%d of Connection Establishment Command", context->supi, context->t5012.retry_count, lmf_timer_cfg(LMF_TIMER_T5012)->max_count);
                	rv = upp_send_to_amf(context, context->t5012.pkbuf, LMF_TIMER_T5012);
                	ogs_expect(rv == OGS_OK);
                	ogs_assert(rv != OGS_ERROR);
            	}
            	break;

			default:
				ogs_error("Unknown timer event %s", lmf_timer_get_name(e->h.timer_id));
				break;
		}
		break;

    default:
        ogs_error("Unknown event %s", lmf_event_get_name(e));
        break;
    }
}

void upp_state_connected(ogs_fsm_t *s, lmf_event_t *e)
{
	int rv;
	lmf_lcs_up_context_t *context = NULL;
	ogs_upp_message_t message;

	ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

    /* Pick up corresponding LCS-UP context */
    context = lmf_find_lcs_up_context_by_id(e->binding_id);
    ogs_assert(context);

	switch (e->h.id) {
	    case OGS_FSM_EXIT_SIG:
    	    break;

	    case OGS_FSM_ENTRY_SIG:
			/* Starting inactivity timer for established LCS-UP connection */
			ogs_timer_start(context->inactivity.timer, lmf_timer_cfg(LMF_TIMER_INACTIVITY)->duration);
			ogs_info("[%s] Inactivity timer (%llds) for the established LCS-UP connection started.", context->supi, ogs_time_to_sec(lmf_timer_cfg(LMF_TIMER_INACTIVITY)->duration));
			break;

		case LMF_EVENT_UPP_CONNECTION_RELEASE:
			break;

		case LMF_EVENT_UPP_MESSAGE:
	        ogs_assert(e->message);
			if(e->message->len != ogs_upp_decode(&message, e->message))
        	{
            	ogs_error("[%s] Decoding of UPP-CM message (%d B) failed.", context->supi, e->message->len);
				ogs_pkbuf_free(e->message);
				e->message = 0;
            	break;
        	}
        	ogs_debug("[%s] UPP-CM message (%s) from AMF received (%d B).", context->supi, ogs_upp_get_message_name(message.type), e->message->len);

        	/* Next actions depend on UPP-CM message type */
        	switch(message.type)
        	{
				case UPP_CM_CONN_RELEASE_REQUEST:
					break;

				case UPP_CM_CONN_RELEASE_COMPLETE:
					break;

				case UPP_CM_CONN_MODIFICATION_COMPLETE:
					break;

				case UPP_CM_CONN_MODIFICATION_REJECT:
					break;

				default:
                	ogs_warn("[%s] %s message (UPP-CM) is not handled in CONNECTED state.", context->supi, ogs_upp_get_message_name(message.type));
                	break;
			}

			/* Free received UPP message, if available */
        	if(e->message)
        	{
            	ogs_pkbuf_free(e->message);
				e->message = 0;
        	}

			break;

		case LMF_EVENT_UPP_TIMER:
			switch (e->h.timer_id) {
            	case LMF_TIMER_T5010:
                	if (context->t5010.retry_count >=
                    	lmf_timer_cfg(LMF_TIMER_T5010)->max_count) {
                    		ogs_warn("[%s] Retransmission of Connection Release Command failed. "
                        		"Stop retransmission", context->supi);

                    	CLEAR_LCS_UP_TIMER(context->t5010);

	                    /*
    	                 * TS 24.572, 6.2.1.2.4a:
        	             *
            	         * On the fifth expiry of timer T5010, the LMF shall abort ongoing LCS-UPP procedures on this LCS secured user
						 * plane connection and locally release the LCS secured user plane connection between the UE and the LMF
                    	 */
						//TODO
                    	context->terminate = true; //the caller frees everything (because ogs_fsm_dispatch checks state transition. So we can not remove everything from here...
                	} else {
                    	/* Retransmission of Connection Release Command message */
                    	context->t5010.retry_count++;
                    	ogs_assert(context->t5010.pkbuf);
 	                    ogs_info("[%s] Retransmission %d/%d of Connection Release Command", context->supi, context->t5010.retry_count, lmf_timer_cfg(LMF_TIMER_T5010)->max_count);
	                    rv = upp_send_to_amf(context, context->t5010.pkbuf, LMF_TIMER_T5010);
	                    ogs_expect(rv == OGS_OK);
    	                ogs_assert(rv != OGS_ERROR);
        	        }
            	    break;

				case LMF_TIMER_T5015:
                    if (context->t5015.retry_count >=
                        lmf_timer_cfg(LMF_TIMER_T5015)->max_count) {
                            ogs_warn("[%s] Retransmission of Connection Modification Command failed. "
                                "Stop retransmission", context->supi);

                        CLEAR_LCS_UP_TIMER(context->t5015);

                        /*
                         * TS 24.572, 6.2.1.3.5a:
                         *
                         * On the fifth expiry of timer T5015, the LMF shall abort the ongoing network initiated user
						 * plane connection modification procedure on the LCS secured user plane connection.
                         */
                        //TODO
                        context->terminate = true; //the caller frees everything (because ogs_fsm_dispatch checks state transition. So we can not remove everything from here...
                    } else {
                        /* Retransmission of Connection Modification Command message */
                        context->t5015.retry_count++;
                        ogs_assert(context->t5015.pkbuf);
                        ogs_info("[%s] Retransmission %d/%d of Connection Modification Command", context->supi, context->t5015.retry_count, lmf_timer_cfg(LMF_TIMER_T5015)->max_count);
                        rv = upp_send_to_amf(context, context->t5015.pkbuf, LMF_TIMER_T5015);
                        ogs_expect(rv == OGS_OK);
                        ogs_assert(rv != OGS_ERROR);
                    }
                    break;

				case LMF_TIMER_INACTIVITY:
	                /*
    	             * TS 24.572, 4.2:
        	         *
            	     * The LMF may monitor the LCS secured user plane connection by running an implementation specific inactivity timer.
                	 * Upon expiry of the implementation specific inactivity timer, the LMF shall initiate the network initiated user plane
  	    	         * connection release procedure as specified in clause 6.2.1.2.
    	             */
					ogs_warn("[%s] Inactivity timer (%llds) for the established LCS-UP connection expired.", context->supi, ogs_time_to_sec(lmf_timer_cfg(LMF_TIMER_INACTIVITY)->duration));

					//TODO: Initiate Connection Release procedure!
					break;

            	default:
                	ogs_error("Unknown timer event %s", lmf_timer_get_name(e->h.timer_id));
                	break;
	        }

			break;

		default:
	        ogs_error("Unknown event %s", lmf_event_get_name(e));
    	    break;
    }
}
