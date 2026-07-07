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
#include "lpp-handler.h"

/*
 * verifyLPPMessage - check LPP message header
 *
 * @message: received LPP message to be verified.
 * @is_cp: true, if @message was received via control plane.
 * @is_idle: true, if this state machine is in idle state.
 *
 * return: true, if verfication was successful, false otherwise.
 */
static bool
verifyLPPMessage(ogs_lpp_message_t *message, ogs_lpp_session_t *session, bool is_cp, bool is_idle)
{
    ogs_assert(message);
	ogs_assert(session);

    /*
     * User plane messages need always a message body
     * because acknowledgments are not needed.
     */
    if(!is_cp && (!message->lpp_MessageBody || !message->lpp_MessageBody->choice.c1))
    {
        ogs_error("Received a LPP message via user plane without message body.");
        return false;
    }

    /* Control Plane only: acknowledgement check */
    else if(is_cp && message->acknowledgement && message->acknowledgement->ackIndicator)
    {
		if(is_idle)
		{
			ogs_error("Received acknowledgement for LPP message in idle state.");
			return false;
		}

        /* Check received acknowledgment number */
        if(session->sqn_tx != *message->acknowledgement->ackIndicator)
        {
            ogs_error("Acknowledgment mismatch: %ld (received) != %ld (expected).", *message->acknowledgement->ackIndicator, session->sqn_tx);
            return false;
        }

		//TODO: If we are waiting for an acknowledge, we have to indicate here that we have received it now.

        /* If message is just an acknowledgement (no message body), check state and return */
        if((!message->lpp_MessageBody || !message->lpp_MessageBody->choice.c1))
        {
            return true;
        }
    }

    /* Check, if acknowledgment is requested for control plane exchange */
    if(is_cp && (!message->acknowledgement || !message->acknowledgement->ackRequested))
    {
        ogs_warn("No acknowledgement requested for control plane usage. Ignoring...");
    }

    /* Check transaction */
    if(!message->transactionID)
    {
        /*
         * TS 37.355, 6.2:
         *
         * transactionID field of LPP-Message structure:
         *  This field is omitted if an lpp-MessageBody is not present (i.e. in an LPP message sent only to acknowledge a
         *  previously received message) or if it is not available to the transmitting entity (e.g., in an LPP-Error message triggered
         *  by a message that could not be parsed). If present, this field shall be ignored at a receiver in an LPP message for
         *  which the lpp-MessageBody is not present.
         */
        if(!is_idle &&
           message->lpp_MessageBody->choice.c1->present == LPP_LPP_MessageBody__c1_PR_error)
        {
            goto sqn;
        }

        ogs_error("Transaction ID is not included, but expected.");
        return false;
    }

	/* First transaction ever */
    if(session->transaction.transactionNumber < 0)
    {
        /* Therefore, the LMF must be the initiator! */
        if(message->transactionID->initiator != LPP_Initiator_locationServer)
        {
            ogs_error("No ongoing transaction, but new transaction was not initiated by the LMF.");
            return false;
        }
        session->transaction.initiator = LPP_Initiator_locationServer;
        session->transaction.transactionNumber = message->transactionID->transactionNumber;

        ogs_info("New transaction initiated by location server with ID=%ld.", session->transaction.transactionNumber);
    }

    else if(!session->transaction_completed)
    {
        /* There is an ongoing transaction. Check transaction values */
        if(session->transaction.transactionNumber != message->transactionID->transactionNumber ||
           session->transaction.initiator != message->transactionID->initiator)
        {
            ogs_error("Transaction ID mismatch: [%ld,%ld] expected, [%ld,%ld] received.", session->transaction.initiator, session->transaction.transactionNumber, message->transactionID->initiator, message->transactionID->transactionNumber);
            return false;
        }
    }

    else
    {
        /* A new transaction has been initiated. */
        if(is_cp && !is_idle)
        {
            ogs_error("A LPP message with a new transaction was received, but previous ACK was not received.");
            return false;
        }

        if(message->transactionID->initiator != LPP_Initiator_locationServer)
        {
            ogs_error("No ongoing transaction, but new transaction was not initiated by the LMF.");
            return false;
        }
        session->transaction.initiator = LPP_Initiator_locationServer;
        session->transaction.transactionNumber = message->transactionID->transactionNumber;

        ogs_info("New transaction initiated by location server with ID=%ld.", session->transaction.transactionNumber);
		session->transaction_completed = false;
    }

	/* If transaction end is indicated, we have to update the LPP session. */
	if(message->endTransaction)
	{
		session->transaction_completed = true;
	}

sqn:
    /* Sequence number check: Duplicate detection (CP only) */
    if(is_cp)
    {
        if(!message->sequenceNumber)
        {
            ogs_error("Sequence number is missing.");
            return false;
        }

        else if(*message->sequenceNumber == session->sqn_rx)
        {
            session->duplicate_detected = true;
            ogs_warn("Duplicated LPP message detected with SQN=%ld.", session->sqn_rx);
        }

        else
        {
            /* Store new sequence number */
            session->sqn_rx = *message->sequenceNumber;
        }
    }

    return true;
}


void lpp_state_initial(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

    OGS_FSM_TRAN(s, &lpp_state_idle);
}

void lpp_state_final(ogs_fsm_t *s, lmf_event_t *e)
{
    ogs_assert(s);

	lmf_sm_debug(e);
}

void lpp_state_idle(ogs_fsm_t *s, lmf_event_t *e)
{
	int rv;
	bool is_cp = false, is_ack = false; //@is_ack: true, if the LPP response message is just an acknowledgement...
	lmf_location_request_t *location_request = NULL;
	lmf_subscribe_params_t params;
	lmf_sbi_params_t sbi_params;

	ogs_lpp_message_t message;

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

			/* Otherwise, we fall through to request the target UE's capabilities if they are unknown. */
			if(location_request->lpp.capabilities)
			{
				//TODO: For research tests, we return here and send response to AMF for location determination.
				//TODO: In future, we do other things probably here ... :-)

				ogs_sbi_message_t sendmsg;
	            ogs_sbi_response_t *response = NULL;
				ogs_sbi_stream_t *stream = NULL;

    	        /* Build response message for assumption: UE requested assistance data */
				if(location_request->stream_id && (stream = ogs_sbi_stream_find_by_id(location_request->stream_id)) != NULL)
				{
					memset(&sendmsg, 0, sizeof(sendmsg));
            	    response = ogs_sbi_build_response(&sendmsg, OGS_SBI_HTTP_STATUS_NO_CONTENT);
                	ogs_assert(response);
                	ogs_assert(true == ogs_sbi_server_send_response(stream, response));
					location_request->stream_id = 0;
				}

				location_request->lpp.terminate = true;
				break;
			}

		case LMF_EVENT_LPP_REQUEST_CAPABILITIES:

			/* Resetting timer for LPP over CP */
	        CLEAR_LMF_LR_TIMER(location_request->lpp_cp);

			/* We store the encoded LPP message if we have to retransmit it. */
        	location_request->lpp_cp.pkbuf = lpp_build_request_capabilities_full(&location_request->lpp.session, !location_request->lpp.user_plane);
	        ogs_assert(location_request->lpp_cp.pkbuf);

			if(!location_request->lpp.user_plane)
			{
	        	rv = lpp_send_to_amf(location_request, location_request->lpp_cp.pkbuf, LMF_TIMER_LPP);
				location_request->lpp.session.sqn_tx++;
			}
			else
			{
				rv = lpp_send_to_ue(location_request->upp.ctx, location_request->lpp_cp.pkbuf, location_request->correlation_id);
				ogs_pkbuf_free(location_request->lpp_cp.pkbuf); //we do not have to retransmit due to user plane usage!
				location_request->lpp_cp.pkbuf = 0;
			}
    	    ogs_expect(rv == OGS_OK);
        	ogs_assert(rv != OGS_ERROR);

			/* State transition: IDLE => WAITING */
			OGS_FSM_TRAN(s, &lpp_state_waiting);

            break;

    	case OGS_FSM_EXIT_SIG:
        	break;

		case LMF_EVENT_LPP_MESSAGE_CP:
			is_cp = true;

		case LMF_EVENT_LPP_MESSAGE_UP:
			ogs_assert(e->message);
			ogs_info("LPP message received via %s (%d B).", (is_cp) ? "control plane" : "user plane", e->message->len);

			/* Decoding of LPP message */
			rv = ogs_lpp_decode(&message, e->message);
			if(rv != OGS_OK)
			{
				break;
			}

			ogs_pkbuf_free(e->message);
			e->message = 0;

			/* Check LPP message header depending on the current data plane */
			if(!verifyLPPMessage(&message, &location_request->lpp.session, is_cp, true))
			{
				ogs_lpp_free(&message);
				break;
			}

			/* Break, if message is just an acknowledgement that is not possible in idle state */
            if(is_cp && !message.lpp_MessageBody)
            {
                ogs_error("[%s] LPP acknowledgement received in IDLE state.", location_request->supi);
				ogs_lpp_free(&message);
				break;
            }

            /* Duplicate detected, acknowledge and end. */
            if(is_cp && location_request->lpp.session.duplicate_detected)
            {
                location_request->lpp.session.duplicate_detected = false;
                goto end;
            }

			/* Next steps depend on the LPP message type */
			switch(message.lpp_MessageBody->choice.c1->present)
            {
				case LPP_LPP_MessageBody__c1_PR_provideCapabilities:
					rv = lmf_handle_provide_capabilities_message(&message, location_request);

					/* In error case: We are sending an error message back. */
					if(rv != OGS_OK)
					{
						e->message = lpp_build_error_message(&location_request->lpp.session, LPP_CommonIEsError__errorCause_lppMessageBodyError, is_cp);
						ogs_assert(e->message);
					}
					break;

				case LPP_LPP_MessageBody__c1_PR_requestAssistanceData:
					ogs_warn("LPP RequestAssistanceData message is currently not handled.");
					break;

				case LPP_LPP_MessageBody__c1_PR_provideLocationInformation:
					ogs_warn("LPP ProvideLocationInformation message is currently not handled.");
					break;

				case LPP_LPP_MessageBody__c1_PR_abort:
                    ogs_warn("LPP Abort message is currently not handled.");
                    break;

                case LPP_LPP_MessageBody__c1_PR_error:
                    ogs_warn("LPP Error message is currently not handled.");
                    break;

				default:
					ogs_warn("[%s] Unknown LPP message type received (%d).", location_request->supi, message.lpp_MessageBody->choice.c1->present);
					break;
			}
end:
			ogs_lpp_free(&message);

			/* If we are on control plane and do not have a response message, we generate an acknowledgement only */
            if(is_cp && !e->message)
            {
                /*
                 * Generate ACK LPP message and send it to the UE. Here, we do not have to retransmit,
                 * because an acknowledge is not acknowledged. :-)
                 */
                e->message = lpp_build_acknowledgement_message(&location_request->lpp.session);
                ogs_assert(e->message);
				is_ack = true;
            }

			/* Send LPP response message to target UE */
            if(e->message)
            {
                if(is_cp)
                {
					/* Store encoded LPP response message in LR if it is not just an acknowledgement. */
					if(!is_ack)
					{
						location_request->lpp_cp.pkbuf = e->message;
						e->message = 0;

						rv = lpp_send_to_amf(location_request, location_request->lpp_cp.pkbuf, LMF_TIMER_LPP);
						location_request->lpp.session.sqn_tx++;

						OGS_FSM_TRAN(s, &lpp_state_waiting);
					}

					else
					{
						/* Just an acknowledgement. Do not set the retransmission timer. */
						rv = lpp_send_to_amf(location_request, e->message, 0);
					}
				}

				else
				{
					rv = lpp_send_to_ue(location_request->upp.ctx, e->message, location_request->correlation_id);

					/* If transaction is not marked as completed, we go back to waiting state. */
					if(!location_request->lpp.session.transaction_completed)
					{
						OGS_FSM_TRAN(s, &lpp_state_waiting);
					}
				}

				ogs_expect(rv == OGS_OK);
                ogs_assert(rv != OGS_ERROR);
			}

			break;

		/* This timer expires only when a LPP message was sent over control plane */
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
                	    ogs_info("[%s] Retransmission %d/%d of LPP message (SQN=%ld)", location_request->supi, location_request->lpp_cp.retry_count, lmf_timer_cfg(LMF_TIMER_LPP)->max_count, location_request->lpp.session.sqn_tx);
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
		e->message = 0;
	}
}

void lpp_state_waiting(ogs_fsm_t *s, lmf_event_t *e)
{
    int rv;
    bool is_cp = false, is_ack = false;
    lmf_location_request_t *location_request = NULL;
	ogs_lpp_message_t message;

    ogs_assert(s);
    ogs_assert(e);

    lmf_sm_debug(e);

    location_request = lmf_location_request_find_by_id(e->lr_id);
    ogs_assert(location_request);

	switch (e->h.id) {
        case OGS_FSM_ENTRY_SIG:
			break;

		case OGS_FSM_EXIT_SIG:
            break;

		case LMF_EVENT_LPP_MESSAGE_CP:
            is_cp = true;

        case LMF_EVENT_LPP_MESSAGE_UP:
            ogs_assert(e->message);
            ogs_info("LPP message received via %s (%d B).", (is_cp) ? "control plane" : "user plane", e->message->len);

			/* Stop timer to prevent retransmission of last LPP message */
			CLEAR_LMF_LR_TIMER(location_request->lpp_cp);

			/* Decoding of LPP message */
            rv = ogs_lpp_decode(&message, e->message);
            if(rv != OGS_OK)
            {
                break;
            }

            ogs_pkbuf_free(e->message);
            e->message = 0;

            /* Check LPP message header depending on the current data plane */
            if(!verifyLPPMessage(&message, &location_request->lpp.session, is_cp, false))
            {
                ogs_lpp_free(&message);
				break;
            }

            /* Break, if message is just an acknowledgement */
            if(is_cp && !message.lpp_MessageBody)
            {
                OGS_FSM_TRAN(s, &lpp_state_idle);
                ogs_lpp_free(&message);
				break;
            }

            /* Duplicate detected, acknowledge and end. */
            if(is_cp && location_request->lpp.session.duplicate_detected)
            {
                location_request->lpp.session.duplicate_detected = false;
                goto end;
            }

			/* Next steps depend on the LPP message type */
            switch(message.lpp_MessageBody->choice.c1->present)
            {
                case LPP_LPP_MessageBody__c1_PR_provideCapabilities:
					rv = lmf_handle_provide_capabilities_message(&message, location_request);

                    /* In error case: We are sending an error message back. */
                    if(rv != OGS_OK)
                    {
                        e->message = lpp_build_error_message(&location_request->lpp.session, LPP_CommonIEsError__errorCause_lppMessageBodyError, is_cp);
                        ogs_assert(e->message);
                    }
                    break;

                case LPP_LPP_MessageBody__c1_PR_requestAssistanceData:
                    ogs_warn("LPP RequestAssistanceData message is currently not handled.");
                    break;

                case LPP_LPP_MessageBody__c1_PR_provideLocationInformation:
                    ogs_warn("LPP ProvideLocationInformation message is currently not handled.");
                    break;

                case LPP_LPP_MessageBody__c1_PR_abort:
                    ogs_warn("LPP Abort message is currently not handled.");
                    break;

                case LPP_LPP_MessageBody__c1_PR_error:
                    ogs_warn("LPP Error message is currently not handled.");
                    break;

                default:
                    ogs_warn("[%s] Unknown LPP message type received (%d).", location_request->supi, message.lpp_MessageBody->choice.c1->present);
                    break;
            }

end:
			ogs_lpp_free(&message);

			/* If we are on control plane and do not have a response message, we generate an acknowledgement only */
            if(is_cp && !e->message)
            {
                /*
                 * Generate ACK LPP message and send it to the UE. Here, we do not have to retransmit,
                 * because an acknowledge is not acknowledged. :-)
                 */
                e->message = lpp_build_acknowledgement_message(&location_request->lpp.session);
                ogs_assert(e->message);
                is_ack = true;

				/* Go back to idle state afterwards */
				OGS_FSM_TRAN(s, &lpp_state_idle);
            }

            /* Send LPP response message to target UE */
            if(e->message)
            {
                if(is_cp)
                {
                    /* Store encoded LPP response message in LR if it is not just an acknowledgement. */
                    if(!is_ack)
                    {
                        location_request->lpp_cp.pkbuf = e->message;
                        e->message = 0;

                        rv = lpp_send_to_amf(location_request, location_request->lpp_cp.pkbuf, LMF_TIMER_LPP);
                    }

                    else
                    {
                        /* Just an acknowledgement. Do not set the retransmission timer. */
                        rv = lpp_send_to_amf(location_request, e->message, 0);
                    }
                }

                else
                {
					rv = lpp_send_to_ue(location_request->upp.ctx, e->message, location_request->correlation_id);

					/* If transaction is marked as completed, we go back to idle state. */
                    if(location_request->lpp.session.transaction_completed)
                    {
                        OGS_FSM_TRAN(s, &lpp_state_idle);
                    }
                }

				ogs_expect(rv == OGS_OK);
                ogs_assert(rv != OGS_ERROR);
            }

			else
			{
				OGS_FSM_TRAN(s, &lpp_state_idle);
			}

            break;

		/* This timer expires only when a LPP message was sent over control plane */
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
                         location_request->lpp.terminate = true; //the caller frees everything (because ogs_fsm_dispatch checks state transition. So we can n>
                    } else {
                       /* Retransmission of the last LPP message */
                        location_request->lpp_cp.retry_count++;
                        ogs_assert(location_request->lpp_cp.pkbuf);
                        ogs_info("[%s] Retransmission %d/%d of LPP message (SQN=%ld)", location_request->supi, location_request->lpp_cp.retry_count, lmf_timer_cfg(LMF_TIMER_LPP)->max_count, location_request->lpp.session.sqn_tx);
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
        e->message = 0;
    }
}
