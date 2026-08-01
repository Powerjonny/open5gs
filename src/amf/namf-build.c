/*
 * Copyright (C) 2019-2025 by Sukchan Lee <acetcom@gmail.com>
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

static char* ogs_guti_to_string(ogs_nas_5gs_guti_t *nas_guti)
{
    ogs_plmn_id_t plmn_id;
    char plmn_id_buff[OGS_PLMNIDSTRLEN];
    char *amf_id = NULL;
    char *tmsi = NULL;
    char *guti = NULL;

    ogs_assert(nas_guti);

    memset(&plmn_id, 0, sizeof(plmn_id));
    ogs_nas_to_plmn_id(&plmn_id, &nas_guti->nas_plmn_id);
    amf_id = ogs_amf_id_to_string(&nas_guti->amf_id);
    tmsi = ogs_uint32_to_0string(nas_guti->m_tmsi);

    guti = ogs_msprintf("5g-guti-%s%s%s",
            ogs_plmn_id_to_string(&plmn_id, plmn_id_buff),
            amf_id,
            tmsi);

    /* TS29.518 6.1.3.2.2 Guti pattern (27 or 28 characters):
    "5g-guti-[0-9]{5,6}[0-9a-fA-F]{14}" */
    ogs_assert(strlen(guti) == (OGS_MAX_5G_GUTI_LEN - 1) ||
            (strlen(guti)) == OGS_MAX_5G_GUTI_LEN);

    ogs_free(amf_id);
    ogs_free(tmsi);

    return guti;
}

static char* amf_ue_to_context_id(amf_ue_t *amf_ue)
{
    char *ue_context_id = NULL;

    if (amf_ue->supi) {
        ue_context_id = ogs_strdup(amf_ue->supi);
    } else {
        ue_context_id = ogs_guti_to_string(&amf_ue->old_guti);
    }

    return ue_context_id;
}

ogs_sbi_request_t *amf_namf_comm_build_ue_context_transfer(
        amf_ue_t *amf_ue, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
    OpenAPI_ue_context_transfer_req_data_t UeContextTransferReqData;
    char *ue_context_id = NULL;

    ogs_assert(amf_ue);
    ogs_assert(amf_ue->nas.access_type);
    ogs_assert(amf_ue->nas.registration.value);

    ue_context_id = amf_ue_to_context_id(amf_ue);
    ogs_assert(ue_context_id);

    memset(&UeContextTransferReqData, 0, sizeof(UeContextTransferReqData));
    UeContextTransferReqData.access_type = amf_ue->nas.access_type;
    UeContextTransferReqData.reason = amf_ue->nas.registration.value;

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;
    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;
    message.h.resource.component[1] = ue_context_id;
    message.h.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_TRANSFER;
    message.UeContextTransferReqData = &UeContextTransferReqData;

    request = ogs_sbi_build_request(&message);
    ogs_expect(request);

    if (ue_context_id)
        ogs_free(ue_context_id);

    return request;
}

ogs_sbi_request_t *amf_namf_comm_build_registration_status_update(
        amf_ue_t *amf_ue, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    OpenAPI_ue_reg_status_update_req_data_t UeRegStatusUpdateReqData;
    char *ue_context_id = NULL;

    ogs_assert(amf_ue);
    ogs_assert(data);

    ue_context_id = ogs_guti_to_string(&amf_ue->old_guti);
    ogs_assert(ue_context_id);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NAMF_COMM;
    message.h.api.version = (char *)OGS_SBI_API_V1;
    message.h.resource.component[0] =
            (char *)OGS_SBI_RESOURCE_NAME_UE_CONTEXTS;
    message.h.resource.component[1] = ue_context_id;
    message.h.resource.component[2] =
            (char *)OGS_SBI_RESOURCE_NAME_TRANSFER_UPDATE;
    message.UeRegStatusUpdateReqData = &UeRegStatusUpdateReqData;

    memset(&UeRegStatusUpdateReqData, 0, sizeof(UeRegStatusUpdateReqData));

    UeRegStatusUpdateReqData.transfer_status = OGS_POINTER_TO_UINT(data);
    /*
     * TS 29.518
     * 5.2.2.2.2 Registration Status Update
     * If any network slice(s) become no longer available and there are PDU
     * Session(s) associated with them, the target AMF shall include these
     * PDU session(s) in the toReleaseSessionList attribute in the payload.
     */
    if (UeRegStatusUpdateReqData.transfer_status ==
                OpenAPI_ue_context_transfer_status_TRANSFERRED) {
        ogs_assert(amf_ue->to_release_session_list); /* For safety */
        if (amf_ue->to_release_session_list->count) {
            UeRegStatusUpdateReqData.to_release_session_list =
                    amf_ue->to_release_session_list;
        }
    }

    request = ogs_sbi_build_request(&message);
    ogs_expect(request);

    if (ue_context_id)
        ogs_free(ue_context_id);

    return request;
}

ogs_sbi_request_t *amf_namf_comm_build_n1_message_notification(
        amf_ue_t *amf_ue, ogs_pkbuf_t *pkbuf, ogs_pool_id_t subscription_id, const char *cb_uri, OpenAPI_n1_message_class_e n1_class, ogs_pool_id_t lcs_correlation_id)
{
	int rv;
	const char *content_id = "n1-message";
	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
	OpenAPI_n1_message_notification_t n1_notification;
	OpenAPI_n1_message_container_t n1_message_container;
	OpenAPI_ref_to_binary_data_t n1_binary;

	ogs_assert(amf_ue);
	ogs_assert(amf_ue->supi);
	ogs_assert(pkbuf);
	ogs_assert(cb_uri);
	ogs_assert(n1_class);

	/* Initialize message header based on callback URI */
	memset(&message, 0, sizeof(message));
	message.http.custom.callback = (char *) OGS_SBI_CALLBACK_NAMF_COMMUNICATION_N1_MESSAGE_NOTIFY; /* TS 29.500, Table 5.2.3.2.1-1 */
	{
		ogs_sbi_header_t header;
        memset(&header, 0, sizeof(header));
        header.uri = (char *)cb_uri;
        header.method = (char *)OGS_SBI_HTTP_METHOD_POST;

        rv = ogs_sbi_parse_header(&message, &header);
        if (rv != OGS_OK) {
            ogs_error("Failed to parse callback URI: %s", cb_uri);
            goto end;
        }

		/* Ensure service name is set (should be NLMF_LOC for LMF callbacks) */
        if (!message.h.service.name) {
            ogs_error("No service name in callback URI: %s", cb_uri);
            message.h.method = NULL;  /* Constant string, not allocated */
            message.h.uri = NULL;     /* From callback_uri parameter, not allocated */
            ogs_sbi_header_free(&message.h);
            ogs_sbi_message_free(&message);
            goto end;
        }
	}

	/* Initialize message JSON body */
	memset(&n1_notification, 0, sizeof(n1_notification));
	memset(&n1_message_container, 0, sizeof(OpenAPI_n1_message_container_t));
	message.N1Notification = &n1_notification;
	n1_notification.n1_message_container = &n1_message_container;

	/* Subscription ID if available, "implicit" otherwise ~> TS 29.518, 6.1.6.2.16 */
	if(subscription_id)
	{
		n1_notification.n1_notify_subscription_id = ogs_msprintf("%d", subscription_id);
	}
	else
	{
		n1_notification.n1_notify_subscription_id = ogs_strdup("implicit");
	}
	ogs_assert(subscription_id);

	/* N1 message container */
	n1_message_container.n1_message_class = n1_class;
	n1_message_container.nf_id = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance);
	n1_message_container.n1_message_content = &n1_binary;
    memset(&n1_binary, 0, sizeof(n1_binary));
    n1_binary.content_id = (char*) content_id;

	/* Adding N1 binary data to multipart body */
	message.part[message.num_of_part].content_type = (char *)OGS_SBI_CONTENT_5GNAS_TYPE;
    message.part[message.num_of_part].content_id = (char*) content_id;
    message.part[message.num_of_part].pkbuf = pkbuf;
	message.num_of_part++;

	/* If N1 message class == LPP: Adding LCS Correlation Identifier */
	if(n1_class == OpenAPI_n1_message_class_LPP)
	{
		if(!lcs_correlation_id)
		{
			ogs_error("[%s] LPP message can not be forwarded to LMF due to a missing LCS Correlation Identifier.", amf_ue->supi);
			goto end;
		}

		n1_notification.lcs_correlation_id = ogs_msprintf("%d", lcs_correlation_id);
	}

	/* If N1 message class == UPP-CM: Adding UE's SUPI */
	if(n1_class == OpenAPI_n1_message_class_UPP_CM)
	{
		n1_notification.supi = amf_ue->supi;
	}

	request = ogs_sbi_build_request(&message);
    ogs_expect(request);

end:
	/* Free allocated resources */
	if(n1_notification.n1_notify_subscription_id)
	{
		ogs_free(n1_notification.n1_notify_subscription_id);
	}

	if(n1_notification.lcs_correlation_id)
	{
		ogs_free(n1_notification.lcs_correlation_id);
	}

	if(pkbuf && !request)
	{
		ogs_pkbuf_free(pkbuf);
	}

	message.h.method = NULL;
    message.h.uri = NULL;

    ogs_sbi_header_free(&message.h);

	return request;
}
