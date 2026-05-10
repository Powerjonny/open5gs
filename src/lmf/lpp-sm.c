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
	lmf_location_request_t *location_request = NULL;
	lmf_subscribe_params_t params;

	ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

    location_request = lmf_location_request_find_by_id(e->lr_id);
    ogs_assert(location_request);

    switch (e->h.id) {
    case OGS_FSM_ENTRY_SIG:
		/* We subscribe to AMF to get notifications of received LPP messages */
		memset(&params, 0, sizeof(params));
		params.n1 = OpenAPI_n1_message_class_LPP;
		rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, NULL,(ogs_sbi_request_t *(*)(lmf_location_request_t *, void *))lmf_namf_build_n1n2_message_subscribe,
	            location_request, &params);

		if(rv != OGS_OK)
		{
			ogs_error("[%s] Subscription request for N1 messages (LPP) could not be sent.", location_request->supi);
			OGS_FSM_TRAN(s, &lpp_state_exception);
		}

		/* Store transaction ID for response */
		location_request->lpp.xact_id = location_request->xact->id;

		ogs_info("[%s] Subscription for N1 messages (LPP) was sent to AMF (xact ID=%d)", location_request->supi, location_request->lpp.xact_id);
        break;
    case OGS_FSM_EXIT_SIG:
		/* We unsubscribe to AMF to stop sending LPP notifications */
		if(location_request->lpp.subscription)
		{
			rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, NULL,(ogs_sbi_request_t *(*)(lmf_location_request_t *, void *))lmf_namf_build_n1n2_message_unsubscribe,
            	location_request, location_request->lpp.subscription);

	        if (rv != OGS_OK) {
    	        ogs_error("[%s] lmf_amf_sbi_discover_and_send() failed: %d",
        	            location_request->supi ? location_request->supi : "Unknown", rv);
				OGS_FSM_TRAN(s, &lpp_state_exception);
        	}

			/* Store transaction ID for response */
			location_request->lpp.xact_id = location_request->xact->id;

			/*
    	     * Free allocated memory
        	 */
        	if(location_request->lpp.subscription)
        	{
            	if(location_request->lpp.subscription->uri)
            	{
                	ogs_free(location_request->lpp.subscription->uri);
            	}
            	if(location_request->lpp.subscription->id)
            	{
                	ogs_free(location_request->lpp.subscription->id);
            	}

        	    ogs_free(location_request->lpp.subscription);
    	        location_request->lpp.subscription = 0;
	        }
		}
        break;

	default:
		ogs_error("Unknown event %s", lmf_event_get_name(e));
		break;
	}
}

void lpp_state_exception(ogs_fsm_t *s, lmf_event_t *e)
{
	lmf_location_request_t *location_request = NULL;

    ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

	location_request = lmf_location_request_find_by_id(e->lr_id);
    ogs_assert(location_request);

//TODO: Add a solution to leave this state, e.g. by setting a timer to resend a Subscription message to AMF.
    switch (e->h.id) {
    case OGS_FSM_ENTRY_SIG:
		ogs_error("[%s] -- Reached exception state for LPP --", location_request->supi);
        break;
    case OGS_FSM_EXIT_SIG:
        break;
    default:
        ogs_error("Unknown event %s", lmf_event_get_name(e));
        break;
    }
}
