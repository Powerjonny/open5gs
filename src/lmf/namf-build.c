/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
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

#include "namf-build.h"

ogs_sbi_request_t *lmf_namf_build_n1n2_message_subscribe(
        lmf_sbi_params_t *sbi_params, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	ogs_sbi_server_t *server = NULL;
    ogs_sbi_header_t header;

	lmf_subscribe_params_t *params = NULL;
	lmf_subscription_t **ref = NULL;

	char *supi = NULL;
	bool has_lpp = false, has_upp = false, is_n1 = false;

	OpenAPI_ue_n1_n2_info_subscription_create_data_t subscr;

	ogs_assert(sbi_params);
	ogs_assert(data);

	/* Get target N1/N2 message classes that has to be subscribed to */
    params = (lmf_subscribe_params_t*) data;

	/* Get data from @sbi_params */
	switch(sbi_params->type)
    {
        case LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST:
			if(!sbi_params->location_request ||
			   (params->n1 == OpenAPI_n1_message_class_LPP && sbi_params->location_request->lpp.subscription) ||
			   (params->n2 == OpenAPI_n2_information_class_NRPPa && sbi_params->location_request->nrppa.subscription))
            {
                ogs_error("Invalid SBI data structure (LR) has been passed.");
                return NULL;
            }
			supi = sbi_params->location_request->supi;
			has_lpp = sbi_params->location_request->ue_lcs_cap.lpp;

			if(params->n1 == OpenAPI_n1_message_class_LPP)
			{
				ref = &sbi_params->location_request->lpp.subscription;
			}
			else if(params->n2 == OpenAPI_n2_information_class_NRPPa)
			{
				ref = &sbi_params->location_request->nrppa.subscription;
			}
			else
			{
				ogs_warn("[%s] Unsupported message class detected.", supi);
				return NULL;
			}

			break;

		case LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT:
			if(!sbi_params->lcs_up_context || sbi_params->lcs_up_context->subscription)
			{
				 ogs_error("Invalid SBI data structure (LCS-UP) has been passed.");
	             return NULL;
			}
			has_upp = true; //if there is a LCS-UP context, UPP is definitely supported.
			supi = sbi_params->lcs_up_context->supi;
			ref = &sbi_params->lcs_up_context->subscription;
			break;

		default:
			ogs_error("Invalid parameter type has been passed (%.2x).", sbi_params->type);
			return NULL;
	}
	ogs_assert(supi);
	ogs_assert(ref);

	/*
     * Initialize message header with path: /namf-comm/v1/ue-contexts/imsi-.../n1-n2-messages/subscriptions
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;

	message.h.resource.component[1] = (char*)supi;
	ogs_assert(message.h.resource.component[1]);
	message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES;
	message.h.resource.component[3] = (char *)OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS;

	/*
     * Initialize JSON body via UeN1N2InfoSubscriptionCreateData IE
     */
    memset(&subscr, 0, sizeof(OpenAPI_ue_n1_n2_info_subscription_create_data_t));
    message.UeN1N2Subscription = &subscr;
	subscr.nf_id = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance);

	/*
	 * Generate Callback URI for a desired N1 message class (LPP, UPP-CM):
	 * /nlmf-loc/v1/n1-notify
	 */
	if((has_lpp && params->n1 == OpenAPI_n1_message_class_LPP) ||
	   (has_upp && params->n1 == OpenAPI_n1_message_class_UPP_CM))
	{
		ogs_list_for_each(&ogs_sbi_self()->server_list, server) {
            memset(&header, 0, sizeof(header));
            header.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
            header.api.version = (char *)OGS_SBI_API_V1;
            header.resource.component[0] = (char *)"n1-notify";

			subscr.n1_message_class = params->n1;
			subscr.n1_notify_callback_uri = ogs_sbi_server_uri(server, &header);
            if (subscr.n1_notify_callback_uri) {
                ogs_debug("[%s] Built callback URI for N1 notifications: %s",
                        supi, subscr.n1_notify_callback_uri);
                break;
            }
        }

		if(!subscr.n1_notify_callback_uri)
        {
            ogs_error("[%s] Failed to build callback URI for N1 notifications!", supi);
            return NULL;
        }

		is_n1 = true;
	}

	else
	{
		ogs_warn("[%s] Subscription of N1 messages (%s) is ignored.", supi, OpenAPI_n1_message_class_ToString(params->n1));
	}

	/*
	 * Subscribe for N2 information (NRPPa): /nlmf-loc/v1/n2-notify
	 */
	if(params->n2 == OpenAPI_n2_information_class_NRPPa)
	{
		subscr.n2_information_class = OpenAPI_n2_information_class_NRPPa;
		ogs_list_for_each(&ogs_sbi_self()->server_list, server) {
            	memset(&header, 0, sizeof(header));
            	header.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
            	header.api.version = (char *)OGS_SBI_API_V1;
        	    header.resource.component[0] = (char *)"n2-notify";

	            subscr.n2_notify_callback_uri = ogs_sbi_server_uri(server, &header);
	            if (subscr.n2_notify_callback_uri) {
	                ogs_debug("[%s] Built callback URI for N2 notification: %s",
	                        supi, subscr.n2_notify_callback_uri);
	            }
		}

		if(!subscr.n2_notify_callback_uri)
        {
            ogs_error("[%s] Failed to build callback URI for N2 notifications!", supi);

			if(subscr.n1_notify_callback_uri)
			{
				ogs_free(subscr.n1_notify_callback_uri);
			}
            return NULL;
        }

		is_n1 = false;
	}

	/* Create subscription and assign it to the target destination */
    if((*ref = lmf_create_subscription(supi, is_n1)) == NULL)
	{
		request = NULL;
		goto end;
	}

	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

end:
	/*
	 * Free allocated memory
	 */
	if(subscr.n1_notify_callback_uri)
	{
		ogs_free(subscr.n1_notify_callback_uri);
	}

	if(subscr.n2_notify_callback_uri)
	{
		ogs_free(subscr.n2_notify_callback_uri);
	}

	return request;
}

ogs_sbi_request_t *lmf_namf_build_n1n2_message_unsubscribe(
        lmf_sbi_params_t *params, void *data)
{

	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	lmf_subscription_t *subscription = NULL;

	char *supi = NULL;

    ogs_assert(params);
    ogs_assert(data);

	subscription = data;
	ogs_assert(subscription->sid);

	switch(params->type)
    {
        case LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST:
            if(!params->location_request)
            {
                ogs_error("Invalid SBI data structure (LR) has been passed.");
                return NULL;
            }
            supi = params->location_request->supi;
			break;

		case LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT:
			if(!params->lcs_up_context)
			{
				ogs_error("Invalid SBI data structure (LCS-UP) has been passed.");
                return NULL;
			}
			supi = params->lcs_up_context->supi;
			break;

		default:
			ogs_error("Invalid parameter type has been passed (%.2x).", params->type);
            return NULL;
	}
	ogs_assert(supi);

	/*
     * Initialize message header with path: /namf-comm/v1/ue-contexts/imsi-.../n1-n2-messages/subscriptions/<ID>
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_DELETE;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;

    message.h.resource.component[1] = (char*)supi;
    ogs_assert(message.h.resource.component[1]);
    message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES;
    message.h.resource.component[3] = (char *)OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS;
	message.h.resource.component[4] = subscription->sid;

	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

	return request;
}


ogs_sbi_request_t *lmf_namf_build_n1_message_transfer(lmf_sbi_params_t *sbi_params, void *data)
{
	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	const char *content_id = "n1-message";

   	OpenAPI_n1_n2_message_transfer_req_data_t req_data;
	OpenAPI_n1_message_container_t n1_container;
	OpenAPI_ref_to_binary_data_t n1_binary;

	lmf_n1n2_message_params_t *params = NULL;

	bool has_mlcs_up = false;
	char *supi = NULL;
	ogs_pool_id_t id = 0;

	ogs_assert(sbi_params);
	ogs_assert(data);

	/* Get N1 data */
	params = (lmf_n1n2_message_params_t*) data;
	ogs_assert(params->n1.type && params->n1.pkbuf);

	/* Get required parameters from @sbi_params */
	switch(sbi_params->type)
    {
        case LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST:
            if(!sbi_params->location_request || params->n1.type != OpenAPI_n1_message_class_LPP)
            {
                ogs_error("Invalid SBI data structure (LR) has been passed.");
                return NULL;
            }
            supi = sbi_params->location_request->supi;
			id = sbi_params->location_request->id;
            break;

        case LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT:
            if(!sbi_params->lcs_up_context || params->n1.type != OpenAPI_n1_message_class_UPP_CM)
            {
                ogs_error("Invalid SBI data structure (LCS-UP) has been passed.");
                return NULL;
            }
            supi = sbi_params->lcs_up_context->supi;
			has_mlcs_up = sbi_params->lcs_up_context->ue_cap.mlcs_up;
            break;

        default:
            ogs_error("Invalid parameter type has been passed (%.2x).", sbi_params->type);
            return NULL;
    }
	ogs_assert(supi);

	/*
     * Initialize message header with path: /namf-comm/v1/ue-contexts/imsi-.../n1-n2-messages
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;
    message.h.resource.component[1] = (char*)supi;
    message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES;

	/* Initialize message body for target N1 message */
	message.N1N2MessageTransferReqData = &req_data;
	memset(&req_data, 0, sizeof(OpenAPI_n1_n2_message_transfer_req_data_t));

	req_data.n1_message_container = &n1_container;
	memset(&n1_container, 0, sizeof(OpenAPI_n1_message_container_t));

	/* Adding specific parameters depending on message type */
	switch(params->n1.type)
	{
		case OpenAPI_n1_message_class_LPP:
			req_data.lcs_correlation_id = ogs_msprintf("%d", id); //we set the LR ID as LCS ID. Maybe, we must change is later ...
			break;

		case OpenAPI_n1_message_class_UPP_CM:
			/* TS 29.518, 6.1.6.2.18: If UE supports multiple LCS-UP connections, this IE is included only. */
			if(has_mlcs_up)
			{
				req_data.serving_lmf_identification = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance); // we set the NF ID as identification. Maybe, we must change this later ~> TS 23.003, 28.20.4
			}
			break;

		default:
			ogs_warn("N1 message class %s is currently not handled.", OpenAPI_n1_message_class_ToString(params->n1.type));
			return NULL;
	}
	n1_container.n1_message_class = params->n1.type;
	n1_container.nf_id = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance);

	/* Adding content ID related data */
	n1_container.n1_message_content = &n1_binary;
	memset(&n1_binary, 0, sizeof(n1_binary));
	n1_binary.content_id = (char*) content_id;

	/* Adding N1 binary data to multipart body */
	message.part[message.num_of_part].content_type = (char *)OGS_SBI_CONTENT_5GNAS_TYPE;
    message.part[message.num_of_part].content_id = (char*) content_id;
    message.part[message.num_of_part].pkbuf = ogs_pkbuf_copy(params->n1.pkbuf); //create a copy, because we need it maybe for retransmission ~> copied pkbuf is freed with SBI message. ;-)
    message.num_of_part++;

    request = ogs_sbi_build_request(&message);
    ogs_expect(request);

	/*
     * Free allocated memory
     */
	if(req_data.lcs_correlation_id)
	{
		ogs_free(req_data.lcs_correlation_id);
	}

	if(message.part[message.num_of_part-1].pkbuf)
	{
		ogs_pkbuf_free(message.part[message.num_of_part-1].pkbuf);
	}

	return request;
}

ogs_sbi_request_t *lmf_namf_build_lcsup_notification(lmf_lcs_up_context_t *context, const char *target_lmf)
{
	int rv;
	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

	OpenAPI_up_notify_data_t UpNotifyData;

	ogs_assert(context);
    ogs_assert(context->status);
    ogs_assert(context->correlation_id);
    ogs_assert(context->amf_cb_uri);

	/*
     * TS 29.572, 6.1.6.2.49:
     *
     * This IE [@target_lmf] may be present if the UpConnectionStatus is set to "MOVE".
     */
    if(!target_lmf && context->status == OpenAPI_up_connection_status_MOVE)
    {
        return NULL;
    }

	/* Initialize message header based on callback URI */
    memset(&message, 0, sizeof(message));
    message.http.custom.callback = (char *) OGS_SBI_CALLBACK_NLMF_LOCATION_UP_NOTIFY; /* TS 29.500, Table 5.2.3.2.1-1 */
    {
        ogs_sbi_header_t header;
        memset(&header, 0, sizeof(header));
        header.uri = (char *)context->amf_cb_uri;
        header.method = (char *)OGS_SBI_HTTP_METHOD_POST;

        rv = ogs_sbi_parse_header(&message, &header);
        if (rv != OGS_OK) {
            ogs_error("Failed to parse callback URI: %s", context->amf_cb_uri);
            return NULL;
        }

        /* Ensure service name is set (should be NLMF_LOC for LMF callbacks) */
        if (!message.h.service.name) {
            ogs_error("No service name in callback URI: %s", context->amf_cb_uri);
            message.h.method = NULL;  /* Constant string, not allocated */
            message.h.uri = NULL;     /* From callback_uri parameter, not allocated */
            ogs_sbi_header_free(&message.h);
            ogs_sbi_message_free(&message);
            return NULL;
        }
    }

	/* Initialize JSON Body */
	memset(&UpNotifyData, 0, sizeof(UpNotifyData));
	message.UpNotifyData = &UpNotifyData;
	UpNotifyData.notif_correlation_id = ogs_msprintf("%d", context->correlation_id);
	ogs_assert(UpNotifyData.notif_correlation_id);
	UpNotifyData.up_connection_status = context->status;
	UpNotifyData.target_lmfid = (char*)target_lmf;

	/* Build SBI request message */
	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

	/* Free allocated resources */
	if(UpNotifyData.notif_correlation_id)
	{
		ogs_free(UpNotifyData.notif_correlation_id);
	}

	message.h.method = NULL;
    message.h.uri = NULL;
    ogs_sbi_header_free(&message.h);

	return request;
}
