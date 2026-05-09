#include "namf-handler.h"

int lmf_namf_handle_n1n2_subscription_response(
        int status, ogs_sbi_response_t *response, void *data)
{
	int rv;
    ogs_sbi_message_t message;
    lmf_location_request_t *location_request = NULL;
	lmf_subscription_t *subscription = NULL;

    ogs_assert(response);
    ogs_assert(data);

    location_request = data;

	if(status != OGS_OK)
	{
err:
		/* Send error response to client */
        ogs_sbi_stream_t *stream = ogs_sbi_stream_find_by_id(location_request->stream_id);
        if (stream) {
            ogs_sbi_server_send_error(stream,
                    OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                    NULL, "N1/N2 subscription failed",
                    "Subscription not possible", NULL);
        }
		else {
            ogs_error("[%s] Stream ID=%d not found for error response",
                    location_request->supi, location_request->stream_id);
        }

		/* Remove location request */
        lmf_location_request_remove(location_request);
        return OGS_ERROR;
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
	subscription->uri = strdup(message.http.location);
	ogs_assert(subscription->uri);
	subscription->id = strdup(message.UeN1N2SubscriptionCreated->n1n2_notify_subscription_id);

	ogs_list_add(&location_request->subscriptions, subscription);

	ogs_info("[%s] Subscription created [AMF:%s]", location_request->supi, subscription->uri);

	/*
	 * Free allocated memory
	 */
	ogs_sbi_message_free(&message);
	ogs_sbi_response_free(response);

	return OGS_OK;
}

int lmf_namf_handle_lpp_notification(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{

	return OGS_OK;
}

int lmf_namf_handle_upp_notification(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{

	return OGS_OK;
}

int lmf_namf_handle_nrppa_notification(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{

	return OGS_OK;
}
