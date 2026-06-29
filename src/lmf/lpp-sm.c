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
#include "namf-build.h"
#include "sbi-path.h"

#include "lpp-build.h"
#include "lpp-path.h"

void lpp_state_initial(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

    OGS_FSM_TRAN(s, &lpp_state_operational);
}

void lpp_state_final(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

	lmf_sm_debug(e);
}

void lpp_state_operational(ogs_fsm_t *s, lmf_event_t *e)
{
	int rv;
	bool is_cp = false;
	lmf_location_request_t *location_request = NULL;
	lmf_subscribe_params_t params;
	lmf_sbi_params_t sbi_params;

	ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

    location_request = lmf_location_request_find_by_id(e->lr_id);
    ogs_assert(location_request);

start:
    switch (e->h.id) {
	    case OGS_FSM_ENTRY_SIG:
			/* If there is already a LPP message that was included in a LR */
            if(e->message)
            {
                location_request->lpp.message = e->message;
				e->message = 0;
            }

			/*
	         * If there is no N1 subscription for the target UE,
    	     * we subscribe to AMF to get notifications of received LPP messages
        	 */
	        ogs_assert(location_request->supi);
	        if(location_request->lpp.subscription == NULL &&
    	       (location_request->lpp.subscription = lmf_find_subscription(location_request->supi, NULL, true)) == NULL)
        	{
            	memset(&params, 0, sizeof(params));
            	params.n1 = OpenAPI_n1_message_class_LPP;

	            memset(&sbi_params, 0, sizeof(sbi_params));
    	        sbi_params.type = LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST;
        	    sbi_params.location_request = location_request;

            	rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, NULL,(ogs_sbi_request_t *(*)(lmf_sbi_params_t *, void *))lmf_namf_build_n1n2_message_subscribe,
	                	&sbi_params, &params);

	            if(rv != OGS_OK)
    	        {
        	        ogs_error("[%s] Subscription for N1 messages (LPP) failed.", location_request->supi);

	                /* Terminate this state machine to remove the LCS-UP context */
    	            location_request->lpp.terminate = true;
        	    }

				/* Store transaction ID for response */
                location_request->lpp.xact_id = location_request->xact->id;

	            break;
    	    }

        	else if(location_request->lpp.subscription->sid == NULL)
        	{
            	/*
         	     * N1 subscription was sent but no response has been currently received.
            	 * Therefore, we have to wait. ;-)
           		 */
	            break;
    	    }

			/* If we have already a N1 subscription, we can directly process LR's LPP message! */
			else if(location_request->lpp.message)
			{
				e->h.id = LMF_EVENT_LPP_MESSAGE_CP;
				e->message = location_request->lpp.message;
				location_request->lpp.message = 0;
				goto start;
			}

			/* Otherwise, we fall through to request the target UE's capabilities */

		case LMF_EVENT_LPP_REQUEST_CAPABILITIES:

			/* Resetting timer for LPP over CP */
	        CLEAR_LMF_LR_TIMER(location_request->lpp_cp);

			/* We store the encoded LPP message if we have to retransmit it. */
        	location_request->lpp_cp.pkbuf = lpp_build_request_capabilities_full(&location_request->lpp.session, true);
	        ogs_assert(location_request->lpp_cp.pkbuf);

	        rv = lpp_send_to_amf(location_request, location_request->lpp_cp.pkbuf, LMF_TIMER_LPP);
    	    ogs_expect(rv == OGS_OK);
        	ogs_assert(rv != OGS_ERROR);

            break;

    	case OGS_FSM_EXIT_SIG:
        	break;

		case LMF_EVENT_LPP_MESSAGE_CP:
			is_cp = true;
			//TODO: Realize/Check reliable transport of received message. Then fall through to XXX_UP event. ;-)

		case LMF_EVENT_LPP_MESSAGE_UP:
			ogs_assert(e->message);
			ogs_info("LPP message received via %s (%d B).", (is_cp) ? "control plane" : "user plane", e->message->len);
			//TODO: Is @is_cp = true, adding of LPP message header with fields for reliable transport!
			break;

		case LMF_EVENT_LPP_TIMER:
	        switch (e->h.timer_id) {
    	        case LMF_TIMER_LPP:
 	               if (location_request->lpp_cp.retry_count >=
    	                lmf_timer_cfg(LMF_TIMER_LPP)->max_count) {
        	            ogs_warn("[%s] Retransmission of LPP message via control plane failed. "
            	            "Stop retransmission", location_request->supi);

                	    CLEAR_LMF_LR_TIMER(location_request->lpp_cp);

    	                /*
        	             * TS 37.355, 4.3.4.1:
            	         *
                	     * When an LPP message which requires acknowledgement is sent and not acknowledged,
						 * it is resent by the sender following a timeout period up to three times.
               		     */
                    	 location_request->lpp.terminate = true; //the caller frees everything (because ogs_fsm_dispatch checks state transition. So we can not remove everythi>
	                } else {
         	           /* Retransmission of the last LPP message */
            	        location_request->lpp_cp.retry_count++;
                    	ogs_assert(location_request->lpp_cp.pkbuf);
                	    ogs_info("[%s] Retransmission %d/%d of last LPP message", location_request->supi, location_request->lpp_cp.retry_count, lmf_timer_cfg(LMF_TIMER_LPP)->max_count);
                    	rv = lpp_send_to_amf(location_request, location_request->lpp_cp.pkbuf, LMF_TIMER_LPP);
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

	/* Free received encoded LPP message if present */
	if(e->message)
	{
		ogs_pkbuf_free(e->message);
	}
}
