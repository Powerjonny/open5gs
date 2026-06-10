#include "namf-handler.h"

void lmf_namf_handle_n1n2_subscription_response(
        int status, ogs_sbi_response_t *response, void *data, ogs_pool_id_t xact_id)
{
	int rv;
	bool is_lr = true;
    ogs_sbi_message_t message;
    lmf_sbi_params_t *params = NULL;
	lmf_subscription_t *subscription = NULL, **ref = NULL;
	const char *msg;

	char *supi = NULL;

    ogs_assert(response);
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
				ogs_error("No suitable subscription found in LR that can be updated.");
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
	memset(&message, 0, sizeof(message));
    if (ogs_sbi_parse_response(&message, response) != OGS_OK) {
		ogs_error("[%s] UeN1N2Subscription response message is invalid.", supi);
        goto err;
	}

	if(!message.http.location) {
        ogs_error("[%s] HTTP header field 'Location' of UeN1N2Subscription response message is missing.", supi);
		goto err;
    }

	if(!message.UeN1N2SubscriptionCreated || !message.UeN1N2SubscriptionCreated->n1n2_notify_subscription_id)
	{
		ogs_error("[%s] UeN1N2InfoSubscriptionCreated IE is missing/invalid.", supi);
		goto err;
	}

	/* Update the corresponding subscription created before */
	subscription->uri = ogs_strdup(message.http.location);
	ogs_assert(subscription->uri);
	subscription->sid = ogs_strdup(message.UeN1N2SubscriptionCreated->n1n2_notify_subscription_id);
	ogs_assert(subscription->sid);

	ogs_info("[%s] Subscription for %s created [AMF:%s]", supi, msg, subscription->uri);

	/*
	 * Free allocated memory
	 */
	ogs_sbi_message_free(&message);
	ogs_sbi_response_free(response);

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
		/* If N1 subscription was triggered by a LCS-UP context, we have to initialize LCS-UP connection establishment */
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
		 * Otherwise, the N1 subscription was triggered by a LR. Therefore, we have to check if UPP is supported. If so, we have to trigger UP connection establishment as above.
		 * Otherwise, we initialize LPP message exchange.
		 */
		else
		{
			ogs_warn("[%s] N1 Subscription based on a LR is currently not handled.", supi);
			//TODO: If UPP is not supported, init event LMF_EVENT_LPP_MESSAGE if LPP message(s) were received during determine-location request. If no LPP message was included:
	        //TODO: Init event LMF_EVENT_LPP_REQUEST_CAPABILITIES. Otherwise, we shall wait until UP connection is established.
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

	/* Free allocated resources */
	ogs_sbi_message_free(&message);
    ogs_sbi_response_free(response);

	//TODO: depending on @params->type, we should trigger new events here ...
	/* Send error response to client */
	//lmf_location_request_cancel(location_request, "N1/N2 subscription failed", OGS_SBI_HTTP_STATUS_BAD_REQUEST);
}
