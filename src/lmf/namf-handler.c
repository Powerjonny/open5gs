#include "namf-handler.h"

void lmf_namf_handle_n1n2_subscription_response(
        int status, ogs_sbi_message_t *message, void *data, ogs_pool_id_t xact_id)
{
	int rv;
	bool is_lr = true;
    lmf_sbi_params_t *params = NULL;
	lmf_subscription_t *subscription = NULL, **ref = NULL;
	const char *msg;

	char *supi = NULL;

    ogs_assert(message);
    ogs_assert(data);
	ogs_assert(xact_id);

    params = data;

	if(status != OGS_OK)
	{
		goto err;
	}

	/* Get subscription and SUPI references */
	switch(params->type)
	{
		case LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST:
			if(!params->location_request)
			{
				ogs_error("LR context not passed to N1N2 subscription handler.");
				goto err;
			}

			/* Find out, which subscription is the right (LPP or NRPPa) > Assumption: Subscription contains either N1 or N2 ... */
			if(xact_id == params->location_request->lpp.xact_id)
			{
				subscription = params->location_request->lpp.subscription;
				ref = &params->location_request->lpp.subscription;
				params->location_request->lpp.xact_id = 0;
				msg = "N1";
			}
			else if(xact_id == params->location_request->nrppa.xact_id)
			{
				subscription = params->location_request->nrppa.subscription;
                ref = &params->location_request->nrppa.subscription;
				params->location_request->nrppa.xact_id = 0;
				msg = "N2";
			}
			params->location_request->xact = NULL;
			supi = params->location_request->supi;
			ogs_assert(supi);

			break;

		case LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT:
			if(!params->lcs_up_context || !params->lcs_up_context->subscription)
            {
                ogs_error("No suitable subscription found in LCS-UP context that can be updated.");
                goto err;
            }
			subscription = params->lcs_up_context->subscription;
            ref = &params->lcs_up_context->subscription;
            supi = params->lcs_up_context->supi;
			params->lcs_up_context->xact = NULL;
            ogs_assert(supi);
			msg = "N1";
			is_lr = false;

			break;

		default:
			ogs_error("Invalid parameter type has been passed (%.2x).", params->type);
			goto err;
	}

	/*
	 * Processing of HTTP response
	 */
	if(!message->http.location) {
        ogs_error("[%s] HTTP header field 'Location' of UeN1N2Subscription response message is missing.", supi);
		goto err;
    }

	if(!message->UeN1N2SubscriptionCreated || !message->UeN1N2SubscriptionCreated->n1n2_notify_subscription_id)
	{
		ogs_error("[%s] UeN1N2InfoSubscriptionCreated IE is missing/invalid.", supi);
		goto err;
	}

	/* Update the corresponding subscription created before */
	subscription->uri = ogs_strdup(message->http.location);
	ogs_assert(subscription->uri);
	subscription->sid = ogs_strdup(message->UeN1N2SubscriptionCreated->n1n2_notify_subscription_id);
	ogs_assert(subscription->sid);

	ogs_info("[%s] Subscription for %s created [AMF:%s]", supi, msg, subscription->uri);

	/*
	 * Depending on subscription's message class and the passed parameter @params, we should trigger new events here:
	 * >> N1:
	 * @params is of type Location Request:
	 *	=> If UPP is not supported, init event LMF_EVENT_LPP_MESSAGE if LPP message(s) were received during determine-location request. If no LPP message was included:
     *     Init event LMF_EVENT_LPP_REQUEST_CAPABILITIES. Otherwise, we shall wait until LCS-UPP connection is established.
	 *
	 * @params is of type LCS-UP context: Trigger LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT
	 *
	 * >> N2: TODO
	 */
	if(subscription->is_n1)
	{
		/* If N1 subscription was triggered by a LCS-UP context, we have to start LCS-UP connection establishment */
		if(!is_lr)
		{
			if(!params->lcs_up_context)
			{
				ogs_error("[%s] LCS-UP context is missing after successful subscription (UPP-CM).", supi);
				goto err;
			}

			/* Trigger CONNECTION ESTABLISHMENT event */
			lmf_event_t *e = NULL;

   			e = lmf_event_new(LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT);
   			ogs_assert(e);
   			e->binding_id = params->lcs_up_context->id;

   			rv = ogs_queue_push(ogs_app()->queue, e);
  			if (rv != OGS_OK) {
       			ogs_error("ogs_queue_push() failed: %d", (int)rv);
       			ogs_event_free(e);

				goto err;
    		}
		}

		/*
		 * Otherwise, the N1 subscription was triggered by a LR. Therefore, we initialize LPP message exchange.
		 */
		else
		{
			lmf_event_t *e = NULL;

			/* If there is a pending LPP message from the origin LR, we trigger the LMF_EVENT_LPP_MESSAGE_CP */
			if(params->location_request->lpp.message)
			{
				e = lmf_event_new(LMF_EVENT_LPP_MESSAGE_CP);
				e->message = params->location_request->lpp.message;
				params->location_request->lpp.message = 0;
			}

			else
			{
				/* Trigger LMF_EVENT_LPP_REQUEST_CAPABILITIES event */
            	e = lmf_event_new(LMF_EVENT_LPP_REQUEST_CAPABILITIES);
				e->message = 0;
			}
            ogs_assert(e);
            e->lr_id = params->location_request->id;

            rv = ogs_queue_push(ogs_app()->queue, e);
            if (rv != OGS_OK) {
                ogs_error("ogs_queue_push() failed: %d", (int)rv);
                ogs_event_free(e);

                goto err;
            }
		}
	}

	//TODO: Add else branch if actions for N2 message class shall be added.

	return;

err:
	if(subscription)
	{
		lmf_remove_subscription(subscription);
		*ref = NULL; //clear reference in target structure
	}

	//TODO: depending on @params->type, we should trigger new events here ...
	/* Send error response to client */
	//lmf_location_request_cancel(location_request, "N1/N2 subscription failed", OGS_SBI_HTTP_STATUS_BAD_REQUEST);
}


void lmf_namf_handle_n1n2_message_transfer_response(ogs_sbi_message_t *message, void *data)
{
    lmf_sbi_params_t *params = NULL;
    ogs_pool_id_t id;
    char *supi = NULL;
    const char *type;

    ogs_assert(message);
    ogs_assert(data);

    /* Get passed LCS context */
    params = (lmf_sbi_params_t*) data;

    switch(params->type)
    {
        case LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST:
            if(!params->location_request)
            {
                ogs_error("LR context is missing in N1N2 message transfer response handler.");
                return;
            }
            id = params->location_request->id;
            type = "LR context";
            supi = params->location_request->supi;
            ogs_assert(supi);

            break;

        case LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT:
            if(!params->lcs_up_context)
            {
                ogs_error("LCS-UP context is missing for N1N2 message transfer handling.");
                return;
            }
            id = params->lcs_up_context->id;
            type = "LCS-UP context";
            supi = params->lcs_up_context->supi;
            ogs_assert(supi);

            break;

        default:
            ogs_error("Invalid parameter type has been passed to N1N2MessageTransfer response handler (%.2x).", params->type);
            return;
    }


    /* Check received SBI response message */
    if(!message->N1N2MessageTransferRspData)
    {
        ogs_error("[%s] N1N2MessageTransferRspData IE is missing.", supi);
    }

    ogs_info("[%s] N1N2MessageTransfer for %s (ID=%d) received with cause %s.", supi, type, id, OpenAPI_n1_n2_message_transfer_cause_ToString(message->N1N2MessageTransferRspData->cause));

    return;
}

int lmf_namf_handle_n1_message_notify(ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
	int rv;
	OpenAPI_n1_message_notification_t *n1_notification = NULL;
	OpenAPI_n1_message_container_t *n1MessageContainer = NULL;
    OpenAPI_ref_to_binary_data_t *n1MessageContent = NULL;
	ogs_pkbuf_t *pkbuf = NULL;
	ogs_sbi_response_t *response = NULL;
	ogs_sbi_message_t message;

	lmf_subscription_t *subscription = NULL;
	lmf_lcs_up_context_t *context = NULL;
	lmf_location_request_t *location_request = NULL;
	lmf_event_t *e = NULL;

	ogs_assert(stream);
	ogs_assert(recvmsg);

	/* Get N1MessageNotification IE from SBI message */
	n1_notification = recvmsg->N1Notification;
	if(!n1_notification)
	{
		ogs_error("No N1MessageNotification IE in N1 notification included.");
		goto err;
	}

	/* Check for mandatory IEs */
	if(!n1_notification->n1_notify_subscription_id)
	{
		ogs_error("Subscription ID is missing in N1 message notification.");
		goto err;
	}
	else if((n1MessageContainer = n1_notification->n1_message_container) == NULL)
	{
		ogs_error("N1 message container is not included in N1 message notification.");
		goto err;
	}

	/* Looking for target subscription if explicit */
	if(strcmp(n1_notification->n1_notify_subscription_id, "implicit") != 0 &&
		(subscription = lmf_find_subscription_by_subscription_id(n1_notification->n1_notify_subscription_id)) == NULL)
	{
		ogs_error("No suitable subscription found for ID=%s during N1 message notification.", n1_notification->n1_notify_subscription_id);
		goto err;
	}

	/* Extract included N1 message payload */
	n1MessageContent = n1MessageContainer->n1_message_content;
    if (!n1MessageContent || !n1MessageContent->content_id) {
    	ogs_error("No n1MessageContent");
        goto err;
    }

    pkbuf = ogs_sbi_find_part_by_content_id(recvmsg, n1MessageContent->content_id);
    if (!pkbuf) {
    	ogs_error("No N1 content in N1 message notification found.");
        goto err;
    }

	/* Further actions depend on N1 message class */
	switch(n1MessageContainer->n1_message_class)
	{
		case OpenAPI_n1_message_class_LPP:
			if(!n1_notification->lcs_correlation_id)
			{
				ogs_error("No LCS Correlation ID for LPP message notification included.");
				goto err;
			}

			if((location_request = lmf_location_request_find_by_lcs_id(atoi(n1_notification->lcs_correlation_id))) == NULL)
			{
				ogs_error("No LR found for LCS Correlation identifier %s.", n1_notification->lcs_correlation_id);
				goto err;
			}

			/* Forward LPP message to the corresponding state machine */
			e = lmf_event_new(LMF_EVENT_LPP_MESSAGE_CP);
            ogs_assert(e);
			e->lr_id = location_request->id;
			e->message = ogs_pkbuf_copy(pkbuf);

			rv = ogs_queue_push(ogs_app()->queue, e);
            if (rv != OGS_OK) {
                ogs_error("ogs_queue_push() failed: %d", (int)rv);
                ogs_pkbuf_free(e->message);
                ogs_event_free(e);

                goto err;
            }

			break;

		case OpenAPI_n1_message_class_UPP_CM:
			/* Get and compare SUPI of target UE */
			if(!n1_notification->supi)
			{
				ogs_error("N1 message notification (UPP-CM) does not contain a SUPI.");
				goto err;
			}
			else if(subscription && strcmp(subscription->supi, n1_notification->supi) != 0)
			{
				ogs_error("[%s] SUPI in N1 message notification does not match (%s).", subscription->supi, subscription->supi);
				goto err;
			}

			/* Looking for target LCS-UP context */
			if((context = lmf_find_lcs_up_context_by_supi(n1_notification->supi)) == NULL)
			{
				ogs_error("[%s] No LCS-UP context found for target UE.", n1_notification->supi);
				goto err;
			}

			/* Forward UPP-CM message to the corresponding state machine */
			e = lmf_event_new(LMF_EVENT_UPP_MESSAGE);
            ogs_assert(e);
            e->binding_id = context->id;
			e->message = ogs_pkbuf_copy(pkbuf); /*@pkbuf is freed when @recvmsg is freed */

            rv = ogs_queue_push(ogs_app()->queue, e);
            if (rv != OGS_OK) {
                ogs_error("ogs_queue_push() failed: %d", (int)rv);
				ogs_pkbuf_free(e->message);
                ogs_event_free(e);

                goto err;
            }

			break;

		default:
			ogs_warn("N1 message type %s is currently not handled during N1 notifications.", OpenAPI_n1_message_class_ToString(n1MessageContainer->n1_message_class));
			goto err;
	}

	/* Send response to AMF TS 29.518, 5.2.2.3.5 */
	memset(&message, 0, sizeof(message));
    response = ogs_sbi_build_response(&message, OGS_SBI_HTTP_STATUS_NO_CONTENT);
    ogs_assert(response);
    ogs_assert(true == ogs_sbi_server_send_response(stream, response));

	return OGS_OK;

err:
	ogs_assert(true ==
       ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
       recvmsg, "N1 notification handling failed", NULL, NULL));

	return OGS_ERROR;
}


