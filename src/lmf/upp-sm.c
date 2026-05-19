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
	lmf_event_t ee;

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
sub:
        /*
		 * If there is no subscription for the target UE in terms of UPP-CM,
		 * we subscribe to AMF to get notifications of received UPP messages
		 */
		ogs_assert(context->supi);
		if(context->subscription == NULL &&
		   (context->subscription = lmf_find_subscription(context->supi, NULL, true, OpenAPI_n1_message_class_UPP_CM)) == NULL)
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

				/* Shutdown this state machine and remove LCS-UP context */
				memset(&ee, 0, sizeof(lmf_event_t));
                ee.binding_id = context->id;
                ogs_fsm_fini(&context->sm, &ee);    //this removes the LCS-UP context
        	}
			else
			{
	        	ogs_info("[%s] Subscription for N1 messages (UPP) was sent to AMF (xact ID=%d)", context->supi, context->xact->id);
			}

			break;
		}

		/* Otherwise, we go to the CONNECTION_ESTABLISHMENT event below */

	case LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT:
		if(context->subscription == NULL &&
           (context->subscription = lmf_find_subscription(context->supi, NULL, true, OpenAPI_n1_message_class_UPP_CM)) == NULL)
		{
			ogs_warn("[%s] Missing subscription for UPP-CM messages - doing this first.", context->supi);
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

		/* Assign LMF LCS-UP address */
		context->address.type = UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4;
		rv = ogs_upp_lookup_lcs_up_address(&context->address, OGS_UPP_LMF_PORT);
		ogs_expect(rv == OGS_OK);
		ogs_assert(rv != OGS_ERROR);

		/* We store the encoded message if we have to retransmit it. */
		context->t5012.pkbuf = upp_build_connection_establishment_command(context->id, &context->address, NULL);
		ogs_assert(context->t5012.pkbuf);

		rv = upp_send_to_amf(context, context->t5012.pkbuf, LMF_TIMER_T5012);
		ogs_expect(rv == OGS_OK);
        ogs_assert(rv != OGS_ERROR);

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
