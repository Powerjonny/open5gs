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
        lmf_location_request_t *location_request, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	ogs_sbi_server_t *server = NULL;
    ogs_sbi_header_t header;

	lmf_subscribe_params_t *params = NULL;

	OpenAPI_ue_n1_n2_info_subscription_create_data_t subscr;

	ogs_assert(location_request);
	ogs_assert(data);
	ogs_assert(location_request->supi);

	/*
     * Initialize message header with path: /namf-comm/v1/ue-contexts/imsi-.../n1-n2-messages/subscriptions
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;

	message.h.resource.component[1] = (char*)location_request->supi;
	ogs_assert(message.h.resource.component[1]);
	message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES;
	message.h.resource.component[3] = (char *)OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS;

	/*
     * Initialize JSON body via UeN1N2InfoSubscriptionCreateData IE
     */
    memset(&subscr, 0, sizeof(OpenAPI_ue_n1_n2_info_subscription_create_data_t));
    message.UeN1N2Subscription = &subscr;
	subscr.nf_id = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance);

	/* Get target N1/N2 message classes that has to be subscribed to */
	params = (lmf_subscribe_params_t*) data;

	/*
	 * Generate Callback URI depending on desired N1 message class:
	 * /nlmf-loc/v1/<N1_class>/imsi-...
	 *
	 * where N1_class is one of: LPP, UPP_CM .
	 */
	if(location_request->ue_lcs_cap.lpp && params->n1 == OpenAPI_n1_message_class_LPP && !location_request->lpp.subscription)
	{
		ogs_list_for_each(&ogs_sbi_self()->server_list, server) {
            memset(&header, 0, sizeof(header));
            header.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
            header.api.version = (char *)OGS_SBI_API_V1;
            header.resource.component[0] = (char *)"lpp";
            header.resource.component[1] = (char*)location_request->supi;

			subscr.n1_message_class = params->n1;
			subscr.n1_notify_callback_uri = ogs_sbi_server_uri(server, &header);
            if (subscr.n1_notify_callback_uri) {
                ogs_info("[%s] Built callback URI for LPP notification: %s",
                        location_request->supi, subscr.n1_notify_callback_uri);
                break;
            }
        }

		if(!subscr.n1_notify_callback_uri)
        {
            ogs_error("[%s] Failed to build callback URI for LPP notifications!", location_request->supi);
            return NULL;
        }
	}

	else if(location_request->ue_lcs_cap.lcsupp && params->n1 == OpenAPI_n1_message_class_UPP_CM && !location_request->upp.subscription)
	{
		ogs_list_for_each(&ogs_sbi_self()->server_list, server) {
            memset(&header, 0, sizeof(header));
            header.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
            header.api.version = (char *)OGS_SBI_API_V1;
            header.resource.component[0] = (char *)"upp-cm";
            header.resource.component[1] = (char*)location_request->supi;

            subscr.n1_message_class = params->n1;
            subscr.n1_notify_callback_uri = ogs_sbi_server_uri(server, &header);
            if (subscr.n1_notify_callback_uri) {
                ogs_info("[%s] Built callback URI for UPP-CM notification: %s",
                        location_request->supi, subscr.n1_notify_callback_uri);
                break;
            }
        }

		if(!subscr.n1_notify_callback_uri)
		{
			ogs_error("[%s] Failed to build callback URI for UPP notifications!", location_request->supi);
            return NULL;
		}
	}

	else
	{
		ogs_warn("[%s] Subscription of N1 messages (%s) is ignored.", location_request->supi, OpenAPI_n1_message_class_ToString(params->n1));
	}

	/*
	 * Subscribe for N2 information (NRPPa): /nlmf-loc/v1/nrppa/imsi-...
	 */
	if(!location_request->nrppa.subscription && params->n2 == OpenAPI_n2_information_class_NRPPa)
	{
		subscr.n2_information_class = OpenAPI_n2_information_class_NRPPa;
		ogs_list_for_each(&ogs_sbi_self()->server_list, server) {
            	memset(&header, 0, sizeof(header));
            	header.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
            	header.api.version = (char *)OGS_SBI_API_V1;
        	    header.resource.component[0] = (char *)"nrppa";
    	        header.resource.component[1] = (char*)location_request->supi;

	            subscr.n2_notify_callback_uri = ogs_sbi_server_uri(server, &header);
	            if (subscr.n2_notify_callback_uri) {
	                ogs_info("[%s] Built callback URI for NRPPa notification: %s",
	                        location_request->supi, subscr.n2_notify_callback_uri);
	            }
		}

		if(!subscr.n2_notify_callback_uri)
        {
            ogs_error("[%s] Failed to build callback URI for NRPPa notifications!", location_request->supi);

			if(subscr.n1_notify_callback_uri)
			{
				ogs_free(subscr.n1_notify_callback_uri);
			}
            return NULL;
        }
	}

	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

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
        lmf_location_request_t *location_request, void *data)
{

	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	lmf_subscription_t *subscription = NULL;

    ogs_assert(location_request);
    ogs_assert(data);
    ogs_assert(location_request->supi);

	subscription = data;

	/*
     * Initialize message header with path: /namf-comm/v1/ue-contexts/imsi-.../n1-n2-messages/subscriptions/<ID>
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_DELETE;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;

    message.h.resource.component[1] = (char*)location_request->supi;
    ogs_assert(message.h.resource.component[1]);
    message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_N1_N2_MESSAGES;
    message.h.resource.component[3] = (char *)OGS_SBI_RESOURCE_NAME_SUBSCRIPTIONS;
	message.h.resource.component[4] = subscription->id;

	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

	return request;
}
