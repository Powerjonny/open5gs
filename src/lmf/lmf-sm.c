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

#include "sbi-path.h"
#include "context.h"
#include "event.h"
#include "nlmf-handler.h"
#include "namf-handler.h"

void lmf_state_initial(ogs_fsm_t *s, lmf_event_t *e)
{
    lmf_sm_debug(e);

    ogs_assert(s);

    OGS_FSM_TRAN(s, &lmf_state_operational);
}

void lmf_state_final(ogs_fsm_t *s, lmf_event_t *e)
{
    lmf_sm_debug(e);

    ogs_assert(s);
}

void lmf_state_operational(ogs_fsm_t *s, lmf_event_t *e)
{
    int rv;
    ogs_sbi_stream_t *stream = NULL;
    ogs_pool_id_t stream_id = OGS_INVALID_POOL_ID;
	ogs_pool_id_t location_request_id = OGS_INVALID_POOL_ID;
    ogs_sbi_request_t *request = NULL;
    ogs_sbi_nf_instance_t *nf_instance = NULL;
    ogs_sbi_subscription_data_t *subscription_data = NULL;
    ogs_sbi_xact_t *sbi_xact = NULL;
    ogs_pool_id_t sbi_xact_id = OGS_INVALID_POOL_ID;
    lmf_location_request_t *location_request = NULL;
	lmf_lcs_up_context_t *lcs_up_context = NULL;

	lmf_sbi_params_t sbi_params;
	char *supi = NULL;

    ogs_sbi_message_t message;

    ogs_assert(e);
    ogs_assert(s);

    lmf_sm_debug(e);

    switch (e->h.id) {
    case OGS_FSM_ENTRY_SIG:
        break;

    case OGS_FSM_EXIT_SIG:
        break;

    case OGS_EVENT_SBI_SERVER:
        request = e->h.sbi.request;
        ogs_assert(request);
        stream_id = OGS_POINTER_TO_UINT(e->h.sbi.data);
        ogs_assert(stream_id >= OGS_MIN_POOL_ID &&
                stream_id <= OGS_MAX_POOL_ID);

        stream = ogs_sbi_stream_find_by_id(stream_id);
        if (!stream) {
            ogs_error("STREAM has already been removed [%d]", stream_id);
            break;
        }

        rv = ogs_sbi_parse_request(&message, request);
        if (rv != OGS_OK) {
            /* Health check requests (GET /) are expected and benign - log at debug level */
            if (request->h.uri && strcmp(request->h.uri, "/") == 0) {
                ogs_debug("cannot parse HTTP message (health check) [method:%s, uri:%s]",
                        request->h.method ? request->h.method : "NULL",
                        request->h.uri ? request->h.uri : "NULL");
            } else {
                ogs_warn("cannot parse HTTP message [method:%s, uri:%s]",
                        request->h.method ? request->h.method : "NULL",
                        request->h.uri ? request->h.uri : "NULL");
            }
            ogs_assert(true ==
                ogs_sbi_server_send_error(
                    stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                    NULL, "cannot parse HTTP message", NULL, NULL));
            break;
        }

        if (strcmp(message.h.api.version, OGS_SBI_API_V1) != 0) {
            ogs_error("Not supported version [%s]", message.h.api.version);
            ogs_assert(true ==
                ogs_sbi_server_send_error(
                    stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                    &message, "Not supported version", NULL, NULL));
            ogs_sbi_message_free(&message);
            break;
        }

	SWITCH(message.h.service.name)
        /* NRF management service */
        CASE(OGS_SBI_SERVICE_NAME_NNRF_NFM)
            SWITCH(message.h.resource.component[0])
            CASE(OGS_SBI_RESOURCE_NAME_NF_STATUS_NOTIFY)
                SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
                    ogs_nnrf_nfm_handle_nf_status_notify(stream, &message);
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert(true ==
                        ogs_sbi_server_send_error(stream,
                            OGS_SBI_HTTP_STATUS_FORBIDDEN, &message,
                            "Invalid HTTP method", message.h.method, NULL));
                END
                break;

            DEFAULT
                ogs_error("Invalid resource name [%s]",
                        message.h.resource.component[0]);
                ogs_assert(true ==
                    ogs_sbi_server_send_error(stream,
                        OGS_SBI_HTTP_STATUS_BAD_REQUEST, &message,
                        "Invalid resource name",
                        message.h.resource.component[0], NULL));
            END
            break;

        /* LMF location service */
        CASE(OGS_SBI_SERVICE_NAME_NLMF_LOC)
            SWITCH(message.h.resource.component[0])
			/* Endpoint for N1 message notifications from AMF */
			CASE("n1-notify")
				SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
                    rv = lmf_namf_handle_n1_message_notify(stream, &message);
                    if (rv != OGS_OK) {
                        ogs_error("lmf_namf_handle_n1_message_notify() failed");
                    }
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert(true ==
                        ogs_sbi_server_send_error(stream,
                            OGS_SBI_HTTP_STATUS_FORBIDDEN, &message,
                            "Invalid HTTP method", message.h.method, NULL));
                END
                break;

            CASE(OGS_SBI_RESOURCE_NAME_DETERMINE_LOCATION)
                SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
				    rv = lmf_nlmf_handle_determine_location(stream, &message);
                    if (rv != OGS_OK) {
                        ogs_error("lmf_nlmf_handle_determine_location() failed");
                    }
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert(true ==
                        ogs_sbi_server_send_error(stream,
                            OGS_SBI_HTTP_STATUS_FORBIDDEN, &message,
                            "Invalid HTTP method", message.h.method, NULL));
                END
                break;

			CASE(OGS_SBI_RESOURCE_NAME_CONFIGURE_UP)
				SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
                    rv = lmf_nlmf_handle_upconfig(stream, &message);
                    if (rv != OGS_OK) {
                        ogs_error("lmf_nlmf_handle_upconfig() failed"); // response is sent within the handler function.
                    }
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert(true ==
                        ogs_sbi_server_send_error(stream,
                            OGS_SBI_HTTP_STATUS_FORBIDDEN, &message,
                            "Invalid HTTP method", message.h.method, NULL));
                END
                break;

			CASE(OGS_SBI_RESOURCE_NAME_UP_SUBSCRIPTIONS)
				SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
                    rv = lmf_nlmf_handle_upsubscribe(stream, &message);
                    if (rv != OGS_OK) {
                        ogs_error("lmf_nlmf_handle_subscribe() failed"); // response is sent within the handler function.
                    }
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert(true ==
                        ogs_sbi_server_send_error(stream,
                            OGS_SBI_HTTP_STATUS_FORBIDDEN, &message,
                            "Invalid HTTP method", message.h.method, NULL));
                END
                break;

            //TODO: add more resources (TS 29.572, 6.1.3) here.

            DEFAULT
                ogs_error("Invalid resource name [%s]",
                        message.h.resource.component[0]);
                ogs_assert(true ==
                    ogs_sbi_server_send_error(stream,
                        OGS_SBI_HTTP_STATUS_BAD_REQUEST, &message,
                        "Invalid resource name",
                        message.h.resource.component[0], NULL));
            END
            break;

        DEFAULT
            ogs_error("Unknown service name [%s]", message.h.service.name);
            ogs_assert(true ==
                ogs_sbi_server_send_error(stream,
                    OGS_SBI_HTTP_STATUS_BAD_REQUEST, &message,
                    "Unknown service name", message.h.service.name, NULL));
        END

        /* In lib/sbi/server.c, notify_completed() releases 'request' buffer. */
        ogs_sbi_message_free(&message);
        break;

    case OGS_EVENT_SBI_CLIENT:
        ogs_assert(e->h.sbi.response);
        ogs_assert(e->h.sbi.data);

		memset(&sbi_params, 0, sizeof(lmf_sbi_params_t));

        /* Parse SBI response message */
        rv = ogs_sbi_parse_response(&message, e->h.sbi.response);
        if (rv != OGS_OK) {
            ogs_error("cannot parse HTTP response");
            ogs_sbi_message_free(&message);
            ogs_sbi_response_free(e->h.sbi.response);
            break;
        }

        if (strcmp(message.h.api.version, OGS_SBI_API_V1) != 0) {
            ogs_error("Not supported version [%s]", message.h.api.version);
            ogs_sbi_message_free(&message);
            ogs_sbi_response_free(e->h.sbi.response);
            break;
        }

        SWITCH(message.h.service.name)

        /* AMF communication service */
		CASE(OGS_SBI_SERVICE_NAME_NAMF_COMM)
            /* Find SBI transaction */
            sbi_xact_id = OGS_POINTER_TO_UINT(e->h.sbi.data);
            ogs_assert(sbi_xact_id >= OGS_MIN_POOL_ID &&
                        sbi_xact_id <= OGS_MAX_POOL_ID);

            sbi_xact = ogs_sbi_xact_find_by_id(sbi_xact_id);
            if (!sbi_xact) {
               ogs_error("SBI transaction has already been removed [%d]",
                        sbi_xact_id);
               break;
            }

            /* Check, if this transaction ID belongs to a LR or a LCS-UP context */
            if ((location_request = lmf_location_request_try_find_by_id(sbi_xact->sbi_object_id)) != NULL &&
                            location_request->xact && location_request->xact->id == sbi_xact_id)
            {
                sbi_params.type = LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST;
                sbi_params.location_request = location_request;
                supi = location_request->supi;
            }

            else if((lcs_up_context = lmf_find_lcs_up_context_by_id(sbi_xact->sbi_object_id)) != NULL &&
                               lcs_up_context->xact && lcs_up_context->xact->id == sbi_xact_id)
            {
                sbi_params.type = LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT;
                sbi_params.lcs_up_context = lcs_up_context;
                supi = lcs_up_context->supi;
            }
            else {
                ogs_error("No target data stucture found for HTTP response with ID %d.", sbi_xact_id);
                ogs_sbi_xact_remove(sbi_xact);
                break;
            }

            SWITCH(message.h.resource.component[0])
                /* /ue-contexts */
                CASE(OGS_SBI_RESOURCE_NAME_UE_CONTEXTS)
                    /* /ue-contexts/imsi-.../n1-n2-messages */
                    SWITCH(message.h.resource.component[2])
                    CASE(OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES)
                        SWITCH(message.h.method)
                        CASE(OGS_SBI_HTTP_METHOD_POST)
                            /* /ue-contexts/imsi-.../n1-n2-messages/subscriptions */
                           SWITCH(message.h.resource.component[3])
                            CASE(OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS)
                                ogs_debug("[%s] Handling N1/N2 subscription response (xact ID=%d)", supi, sbi_xact_id);
                                if(e->h.sbi.response->status == OGS_SBI_HTTP_STATUS_CREATED)
                                {
                                    lmf_namf_handle_n1n2_subscription_response(
                                        OGS_OK, &message, &sbi_params, sbi_xact_id);
                                }
                                else
                                {
                                    lmf_namf_handle_n1n2_subscription_response(
                                        OGS_ERROR, &message, &sbi_params, sbi_xact_id);
                                }
                                break;
                            DEFAULT
                                /* Fallback: If no subscription response was received,
                                    we assume a N1N2 message transfer response... */
                                if(e->h.sbi.response->status == OGS_SBI_HTTP_STATUS_ACCEPTED ||
                                    e->h.sbi.response->status == OGS_SBI_HTTP_STATUS_OK)
                                {
                                    //TODO: handle N1N2MessageResponseData IE
                                }
                                else
                                {
                                    ogs_warn("[%s] N1N2MessageTransfer failed (status=%d)", supi, e->h.sbi.response->status);
                                }
                            END
                            break;

                        DEFAULT
                            ogs_error("Invalid HTTP method [%s]", message.h.method);
                        END
                        break;

                    DEFAULT
                        ogs_error("Unknown AMF resource [/%s/%s]", OGS_SBI_RESOURCE_NAME_UE_CONTEXTS, message.h.resource.component[2]);
                    END
                    break;

                DEFAULT
                    ogs_error("Unknown AMF resource [%s]", message.h.resource.component[0] ? message.h.resource.component[0] : "Unknown");
                END
                break;

            /* Remove SBI transaction */
            ogs_sbi_xact_remove(sbi_xact);
            break;

        /* NRF management service */
        CASE(OGS_SBI_SERVICE_NAME_NNRF_NFM)
            SWITCH(message.h.resource.component[0])
            CASE(OGS_SBI_RESOURCE_NAME_NF_INSTANCES)
                /* For NRF NFM responses, e->h.sbi.data is the nf_instance pointer */
                nf_instance = e->h.sbi.data;
                ogs_assert(nf_instance);

    /*
     * Guard against dispatching to an FSM that may have been finalized
     * by an asynchronous shutdown triggered by SIGTERM.
     *
     * In init.c's event_termination(), which can be invoked asynchronously
     * when the process receives SIGTERM, we iterate over all NF instances:
     *     ogs_list_for_each(&ogs_sbi_self()->nf_instance_list, nf_instance)
     *         ogs_sbi_nf_fsm_fini(nf_instance);
     * and call ogs_fsm_fini() on each instance's FSM. That finalizes the FSM
     * and its state is reset to zero.
     *
     * After event_termination(), any incoming SBI response—such as an NRF
     * client callback arriving after deregistration—would otherwise be
     * dispatched into a dead FSM and trigger an assertion failure.
     *
     * To avoid this, we check OGS_FSM_STATE(&nf_instance->sm):
     *   - If non-zero, the FSM is still active and can safely handle the event.
     *   - If zero, the FSM has already been finalized by event_termination(),
     *     so we log and drop the event to allow graceful shutdown.
     */
                if (OGS_FSM_STATE(&nf_instance->sm)) {
                    e->h.sbi.message = &message;
                    ogs_fsm_dispatch(&nf_instance->sm, e);
                    /* FSM processes message but doesn't free it - we must free both */
                } else {
                    ogs_error("NF instance FSM has been finalized");
                }

                break;

            CASE(OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS)
                subscription_data = e->h.sbi.data;
                ogs_assert(subscription_data);

                SWITCH(message.h.method)
                CASE(OGS_SBI_HTTP_METHOD_POST)
                    if (message.res_status == OGS_SBI_HTTP_STATUS_CREATED ||
                        message.res_status == OGS_SBI_HTTP_STATUS_OK) {
                        ogs_nnrf_nfm_handle_nf_status_subscribe(
                                subscription_data, &message);
                    } else {
                        ogs_error("HTTP response error : %d",
                                message.res_status);
                    }
                    break;

                CASE(OGS_SBI_HTTP_METHOD_PATCH)
                    if (message.res_status == OGS_SBI_HTTP_STATUS_OK ||
                        message.res_status ==
                            OGS_SBI_HTTP_STATUS_NO_CONTENT) {
                        ogs_nnrf_nfm_handle_nf_status_update(
                                subscription_data, &message);
                    } else {
                        ogs_error("[%s] HTTP response error [%d]",
                                subscription_data->id ?
                                    subscription_data->id : "Unknown",
                                message.res_status);
                    }
                    break;

                CASE(OGS_SBI_HTTP_METHOD_DELETE)
                    if (message.res_status ==
                            OGS_SBI_HTTP_STATUS_NO_CONTENT)
                        ogs_info("[%s] Subscription deleted",
                                subscription_data->id ?
                                    subscription_data->id : "Unknown");
                    else
                        ogs_error("[%s] HTTP response error [%d]",
                                subscription_data->id ?
                                    subscription_data->id : "Unknown",
                                message.res_status);

                    ogs_sbi_subscription_data_remove(subscription_data);
                    break;

                DEFAULT
                    ogs_error("Invalid HTTP method [%s]", message.h.method);
                    ogs_assert_if_reached();
                END
                break;

            DEFAULT
                ogs_error("Unknown NRF resource [%s]",
                        message.h.resource.component[0] ?
                            message.h.resource.component[0] : "Unknown");
                ogs_assert_if_reached();
            END
            break;

        DEFAULT
            ogs_error("Unknown service name [%s]", message.h.service.name);
            ogs_assert_if_reached();
        END

        /* Free received response message */
        ogs_sbi_message_free(&message);
        ogs_sbi_response_free(e->h.sbi.response);
        break;

     case OGS_EVENT_SBI_TIMER:
        switch (e->h.timer_id) {
        case OGS_TIMER_NF_INSTANCE_REGISTRATION_INTERVAL:
        case OGS_TIMER_NF_INSTANCE_HEARTBEAT_INTERVAL:
        case OGS_TIMER_NF_INSTANCE_NO_HEARTBEAT:
        case OGS_TIMER_NF_INSTANCE_VALIDITY:
            nf_instance = e->h.sbi.data;
            ogs_assert(nf_instance);
            ogs_assert(OGS_FSM_STATE(&nf_instance->sm));

            /* Update load for self instance if this is a heartbeat for self */
            if (nf_instance == ogs_sbi_self()->nf_instance) {
                ogs_sbi_self()->nf_instance->load =
                    ogs_list_count(&lmf_self()->location_request_list);
            }

            ogs_fsm_dispatch(&nf_instance->sm, e);
            if (OGS_FSM_CHECK(&nf_instance->sm, ogs_sbi_nf_state_exception))
                ogs_error("[%s:%s] State machine exception [%d]",
                        OpenAPI_nf_type_ToString(nf_instance->nf_type),
                        nf_instance->id, e->h.timer_id);
            break;

     	case OGS_TIMER_SBI_CLIENT_WAIT:
            sbi_xact_id = OGS_POINTER_TO_UINT(e->h.sbi.data);
            ogs_assert(sbi_xact_id >= OGS_MIN_POOL_ID &&
                    sbi_xact_id <= OGS_MAX_POOL_ID);

            sbi_xact = ogs_sbi_xact_find_by_id(sbi_xact_id);
            if (!sbi_xact) {
                ogs_error("SBI transaction has already been removed [%d]",
                        sbi_xact_id);
                break;
            }

            location_request_id = sbi_xact->sbi_object_id;
            ogs_sbi_xact_remove(sbi_xact);

            if (location_request_id > 0) {
                location_request =
                    lmf_location_request_try_find_by_id(location_request_id);
            }
            if (!location_request) {
                ogs_error("Location request has already been removed [%d]",
                        location_request_id);
                break;
            }

            stream = ogs_sbi_stream_find_by_id(location_request->stream_id);
            ogs_error("[%s] SBI request timed out while waiting for AMF",
                    location_request->supi ? location_request->supi : "Unknown");
            if (stream) {
                ogs_assert(true == ogs_sbi_server_send_error(stream,
                        OGS_SBI_HTTP_STATUS_GATEWAY_TIMEOUT,
                        NULL, "AMF discovery timed out",
                        "Unable to reach AMF via NRF/SCP", NULL));
            } else {
                ogs_error("STREAM has already been removed [%d]",
                        location_request->stream_id);
            }

            location_request->xact = NULL;
            lmf_location_request_remove(location_request);
		    break;

		default:
            ogs_error("Unknown timer event [%s]", lmf_timer_get_name(e->h.timer_id));
            break;
        }
        break;

     /* Events that are related to UPP will be forwarded to its state machine */
	 case LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT:
	 case LMF_EVENT_UPP_TIMER:
	 case LMF_EVENT_UPP_MESSAGE:
        lcs_up_context = lmf_find_lcs_up_context_by_id(e->binding_id);
        if (!lcs_up_context) {
            ogs_error("[%s] LCS-UP context with ID=%d not found.", lmf_event_get_name(e), e->binding_id);
            break;
        }

        if(OGS_FSM_STATE(&lcs_up_context->sm))
		{
			/* Forward event to UPP's state machine */
        	ogs_fsm_dispatch(&lcs_up_context->sm, e);

			/* Check, if LCS-UP context shall be removed */
			if(lcs_up_context->terminate)
			{
				ogs_warn("[%s] LCS-UP context with ID=%d will be removed.", lcs_up_context->supi, lcs_up_context->id);
				ogs_fsm_fini(&lcs_up_context->sm, e); //terminate the state machine

				/* If @stream_id is set, send UpConfig response to AMF */
				if(lcs_up_context->stream_id && (stream = ogs_sbi_stream_find_by_id(lcs_up_context->stream_id)) != NULL)
				{
					ogs_assert(true == ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR, NULL, "UPP-CM handling failed", NULL, NULL));
				}

				lmf_remove_lcs_up_context(lcs_up_context);
			}
		}
        break;

	 /* Events that are related to LPP will be forwarded to its state machine */
	 case LMF_EVENT_LPP_TIMER:
	 case LMF_EVENT_LPP_MESSAGE_CP:
	 case LMF_EVENT_LPP_MESSAGE_UP:
	 case LMF_EVENT_LPP_REQUEST_CAPABILITIES:
		location_request = lmf_location_request_find_by_id(e->lr_id);

		if(OGS_FSM_STATE(&location_request->lpp.sm))
		{
			/* Forward event to LPP's state machine */
			ogs_fsm_dispatch(&location_request->lpp.sm, e);

			/* Check, if state machine shall terminate */
			if(location_request->lpp.terminate)
			{
				ogs_warn("[%s] LPP state machine terminates. Remove location request with ID=%d.", location_request->supi, location_request->id);
				ogs_fsm_fini(&location_request->lpp.sm, e);

				/* If stream ID is still set, we return an error cause */
				if(location_request->stream_id && (stream = ogs_sbi_stream_find_by_id(location_request->stream_id)) != NULL)
				{
					ogs_assert(true == ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                    	NULL, "Location determination failed", NULL, NULL));
				}

				/* Remove LR context */
				lmf_location_request_remove(location_request);
			}
		}

		break;

     default:
        ogs_error("Unknown event %s", lmf_event_get_name(e));
        break;
   }
}
