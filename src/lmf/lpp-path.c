/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock.de>
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
#include "lpp-path.h"
#include "namf-build.h"
#include "sbi-path.h"

int lpp_send_to_amf(lmf_location_request_t *request, ogs_pkbuf_t *pkbuf, lmf_timer_e timer_id)
{
	int rv = OGS_OK;
	lmf_n1n2_message_params_t params;
	ogs_sbi_discovery_option_t *discovery_option = NULL;
	ogs_sbi_nf_instance_t *nf_instance = NULL;
	lmf_sbi_params_t sbi_params;

	ogs_assert(request);
	ogs_assert(pkbuf);

	/* Create parameter structure to build SBI message */
	memset(&params, 0, sizeof(lmf_n1n2_message_params_t));
	params.n1.type = OpenAPI_n1_message_class_LPP;
	params.n1.pkbuf = pkbuf;

	memset(&sbi_params, 0, sizeof(lmf_sbi_params_t));
	sbi_params.type = LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST;
	sbi_params.location_request = request;

	/* Build and send SBI message to AMF via NRF */
	if(!request->amf_id)
	{
		goto send;
	}

	discovery_option = ogs_sbi_discovery_option_new();
	if(!discovery_option)
	{
		ogs_warn("[%s] LPP message transfer to AMF is done without discovery option.", request->supi);
		goto send;
	}

	nf_instance = ogs_sbi_nf_instance_find(request->amf_id);
    if (nf_instance && nf_instance->nf_type == OpenAPI_nf_type_AMF) {
        ogs_sbi_discovery_option_set_target_nf_instance_id(discovery_option, request->amf_id);
    }

send:
	rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, discovery_option, (ogs_sbi_request_t *(*)(lmf_sbi_params_t *, void *))lmf_namf_build_n1_message_transfer, &sbi_params, &params);

	/* Start corresponding timer if provided */
    if(rv == OGS_OK && timer_id == LMF_TIMER_LPP)
	{
        ogs_timer_start(request->lpp_cp.timer, lmf_timer_cfg(timer_id)->duration);
    }

	return rv;
}

/*
 * lpp_send_to_ue - transmit an encoded LPP message to UE via secure LCS user plane connection
 *
 * @context: corresponding LCS-UP context
 * @pkbuf: encoded LPP message to be transmitted
 *
 * return: OGS_OK on success, OGS_ERROR otherwise
 */
int
lpp_send_to_ue(lmf_lcs_up_context_t *context, ogs_pkbuf_t *pkbuf, ogs_pool_id_t lcs_id)
{
	int rv;
	uint32_t size = 0;
	char *tmp;
	ogs_pkbuf_t *message = NULL;
	ogs_upp_message_t upp;
	ogs_upp_lcs_lpp_payload_t *lpp = NULL;

	ogs_assert(context);
	ogs_assert(pkbuf);
	ogs_assert(pkbuf->len);
	ogs_assert(lcs_id);

	if(context->status != OpenAPI_up_connection_status_ESTABLISHED)
	{
		ogs_error("[%s] Can not send LPP message over user plane due to invalid connection status (%s).",
			context->supi, OpenAPI_up_connection_status_ToString(context->status));
		return OGS_ERROR;
	}
	else if(!context->tls || !context->tls->handle)
	{
		ogs_error("[%s] Can not sent LPP message over user plane due to missing TLS context.", context->supi);
		return OGS_ERROR;
	}

	/* Build DL LCS-UP TRANSPORT message with included LPP payload */
	memset(&upp, 0, sizeof(ogs_upp_message_t));
	upp.type = LCS_UPP_DL_LCS_TRANSPORT;
	upp.present = OGS_UPP_MESSAGE_PRESENT_LCS;
	upp.lcs.dl_lcs_up_transport.payload_container_type.value = LCS_UPP_PAYLOAD_TYPE_LPP;
	upp.lcs.dl_lcs_up_transport.payload.length = pkbuf->len + 2; //the encoder converts this value to network byte order!
	ogs_assert(pkbuf->len + 2 <= LCS_UPP_PAYLOAD_MAX);

	/* Include a single LPP message */
	lpp = (ogs_upp_lcs_lpp_payload_t*) upp.lcs.dl_lcs_up_transport.payload.contents;
	lpp->length = htons(pkbuf->len);
	memcpy(lpp->message, pkbuf->data, pkbuf->len);

	/* Adding Session Identity IE by using the LCS Correlation Identifier */
	tmp = ogs_msprintf("%d", lcs_id);
	ogs_assert(tmp);
	upp.lcs.dl_lcs_up_transport.session_identity.length = strlen(tmp);
	memcpy(upp.lcs.dl_lcs_up_transport.session_identity.identity, tmp, strlen(tmp));

	/* Create target pkbuf structure */
	size = 1 + 1 + 2 + pkbuf->len + 2 + 1 + strlen(tmp); // message type (1) + payload type (1) + payload IE (length = 2, data = LPP message + its length (2)) + Session Identity (length = 1, data = @tmp)
	message = ogs_pkbuf_alloc(NULL, size);
	ogs_assert(message);
    ogs_pkbuf_put(message, size);
	ogs_free(tmp);

	/* Encode LCS-UPP message */
	rv = ogs_upp_encode(message, &upp);
	if(rv != size)
	{
		ogs_error("[%s] DL LCS-UP TRANSPORT message could not be encoded (%d != %d)", context->supi, rv, size);
		ogs_pkbuf_free(message);
		return OGS_ERROR;
	}

	ogs_assert(ogs_pkbuf_push(message, rv));
    message->len = rv;

	/*
	 * Send LCS-UPP message to UE over secure LCS user plane connection
	 */
	if((rv = wolfSSL_write(context->tls->handle, message->data, message->len)) <= 0)
	{
		ogs_error("[%s] LPP message could not be sent to UE.", context->supi);
		ogs_pkbuf_free(message);
		return OGS_ERROR;
	}

	if(rv != message->len)
	{
		ogs_warn("[%s] LPP message was not completely sent to UE (%d/%d B).", context->supi, rv, message->len);
		ogs_pkbuf_free(message);
		return OGS_ERROR;
	}

	ogs_info("[%s] DL LCS-UP TRANSPORT message (included LPP message with %d B) was sent to UE (%d B).", context->supi, pkbuf->len, message->len);

	/* Free encoded LCS-UPP message */
	ogs_pkbuf_free(message);

	return OGS_OK;
}
