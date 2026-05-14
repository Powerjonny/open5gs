#include "namf-handler.h"

void lmf_namf_handle_n1n2_subscription_response(
        int status, ogs_sbi_response_t *response, void *data, ogs_pool_id_t xact_id)
{
	int rv;
    ogs_sbi_message_t message;
    lmf_location_request_t *location_request = NULL;
	lmf_subscription_t *subscription = NULL;
	const char *msg;

    ogs_assert(response);
    ogs_assert(data);

    location_request = data;

	if(status != OGS_OK)
	{
		goto err;
	}

	/*
	 * Processing of HTTP response
	 */
	memset(&message, 0, sizeof(message));
    if (ogs_sbi_parse_response(&message, response) != OGS_OK) {
		ogs_error("[%s] HTTP header field 'Location' of UeN1N2Subscription response message is missing.",
                    location_request->supi);
        goto err;
	}

	if(!message.http.location) {
        ogs_error("[%s] HTTP header field 'Location' of UeN1N2Subscription response message is missing.",
               location_request->supi);
		goto err;
    }

	if(!message.UeN1N2SubscriptionCreated || !message.UeN1N2SubscriptionCreated->n1n2_notify_subscription_id)
	{
		ogs_error("[%s] UeN1N2InfoSubscriptionCreated IE is missing/invalid.", location_request->supi);
		goto err;
	}

	subscription = ogs_calloc(1, sizeof(lmf_subscription_t));
	ogs_assert(subscription);
	subscription->uri = ogs_strdup(message.http.location);
	ogs_assert(subscription->uri);
	subscription->id = ogs_strdup(message.UeN1N2SubscriptionCreated->n1n2_notify_subscription_id);

	/* Check which message class belongs to the subscription */
	if(location_request->lpp.xact_id == xact_id)
	{
		location_request->lpp.subscription = subscription;
		location_request->lpp.xact_id = 0;
		msg = "LPP";

		//TODO: If UPP is not supported, init event LMF_EVENT_LPP_MESSAGE if LPP message(s) were received during determine-location request. If no LPP message was included:
		//TODO: Init event LMF_EVENT_LPP_REQUEST_CAPABILITIES. Otherwise, we shall wait until UP connection is established.
	}

	else if(location_request->upp.xact_id == xact_id)
	{
		location_request->upp.subscription = subscription;
        location_request->upp.xact_id = 0;
        msg = "UPP";

		/* Trigger event LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT here for upp.sm ;-) */
		lmf_event_t *e = NULL;

	    e = lmf_event_new(LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT);
    	ogs_assert(e);
		e->lr_id = location_request->id;

	    rv = ogs_queue_push(ogs_app()->queue, e);
    	if (rv != OGS_OK) {
        	ogs_error("ogs_queue_push() failed: %d", (int)rv);
        	ogs_event_free(e);

			goto err;
    	}

	}

	else if(location_request->nrppa.xact_id == xact_id)
	{
		location_request->nrppa.subscription = subscription;
    	location_request->nrppa.xact_id = 0;
        msg = "NRPPa";
	}

	else
	{
		ogs_error("[%s] Subscription does not belong to any expected message class.", location_request->supi);
		goto err;
	}

	ogs_info("[%s] Subscription for %s created [AMF:%s]", location_request->supi, msg, subscription->uri);

	/*
	 * Free allocated memory
	 */
	ogs_sbi_message_free(&message);
	ogs_sbi_response_free(response);

	return;

err:
	if(subscription)
	{
		if(subscription->uri)
		{
			ogs_free(subscription->uri);
		}

		if(subscription->id)
		{
			ogs_free(subscription->id);
		}

		ogs_free(subscription);
	}

	ogs_sbi_message_free(&message);
    ogs_sbi_response_free(response);

	/* Send error response to client */
	lmf_location_request_cancel(location_request, "N1/N2 subscription failed", OGS_SBI_HTTP_STATUS_BAD_REQUEST);
}
