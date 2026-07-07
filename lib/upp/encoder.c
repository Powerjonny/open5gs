/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock.de>
 *
 * This file is part of Open5GS.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "ogs-upp.h"

int ogs_upp_encode_downlink_lcs_transport(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	uint8_t b = 0;
	uint16_t len = 0;
	int encoded = 0, size;

	ogs_assert(pkbuf);
	ogs_assert(message);

	/* Initially, we need at least 2 octets */
	size = 2;
	ogs_assert(message->type == LCS_UPP_DL_LCS_TRANSPORT
				&& message->present == OGS_UPP_MESSAGE_PRESENT_LCS
				&& ogs_pkbuf_pull(pkbuf, size));

	memcpy(pkbuf->data - size, &message->type, 1);
	b = (message->lcs.dl_lcs_up_transport.payload_container_type.value & 0x0F);
	memcpy(pkbuf->data - 1, &b, 1);
	encoded += size;

	/* Payload container IE */
	size = sizeof(uint16_t) + message->lcs.dl_lcs_up_transport.payload.length;
	ogs_info("LCS-UPP DL TRANSPORT: Payload length => %d B, payload container size: %d B (pkbuf size: %d B).\n", message->lcs.dl_lcs_up_transport.payload.length, size, pkbuf->len);
	ogs_assert(message->lcs.dl_lcs_up_transport.payload.length &&
				ogs_pkbuf_pull(pkbuf, size));

	len = htons(message->lcs.dl_lcs_up_transport.payload.length);
	memcpy(pkbuf->data - size, &len, sizeof(uint16_t));
	memcpy(pkbuf->data - size + sizeof(uint16_t), message->lcs.dl_lcs_up_transport.payload.contents, message->lcs.dl_lcs_up_transport.payload.length);
	encoded += size;

	/* LCS Session Identity IE */
	size = sizeof(uint8_t) + message->lcs.dl_lcs_up_transport.session_identity.length;
	ogs_assert(message->lcs.dl_lcs_up_transport.session_identity.length && ogs_pkbuf_pull(pkbuf, size));

	memcpy(pkbuf->data - size, &message->lcs.dl_lcs_up_transport.session_identity.length, sizeof(uint8_t));
	memcpy(pkbuf->data - size + sizeof(uint8_t), message->lcs.dl_lcs_up_transport.session_identity.identity, message->lcs.dl_lcs_up_transport.session_identity.length);
	encoded += size;

	return encoded;
}

int ogs_upp_encode_connection_establishment_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	int encoded = 0, size;

	ogs_assert(pkbuf);
	ogs_assert(message);

	/* Initially, we need at least 2 octets */
    size = 2;
    ogs_assert(message->type == UPP_CM_CONN_ESTABLISHMENT_COMMAND
                && message->present == OGS_UPP_MESSAGE_PRESENT_CM
                && ogs_pkbuf_pull(pkbuf, size));

    memcpy(pkbuf->data - size, &message->type, 1);

	/* LCS-UP binding ID IE */
	memcpy(pkbuf->data - size + 1, &message->cm.connection_establishment_command.binding_id.length, 1);
	encoded += size;

	size = message->cm.connection_establishment_command.binding_id.length;
	ogs_assert(size >= UPP_CM_LCS_UP_BINDING_ID_MIN
				&& ogs_pkbuf_pull(pkbuf, size));

	memcpy(pkbuf->data - size, message->cm.connection_establishment_command.binding_id.binding_id, size);
	encoded += size;

	/* LMF LCS-UP address IE */
	switch(message->cm.connection_establishment_command.address.type)
	{
		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4:
			ogs_assert(message->cm.connection_establishment_command.address.length == 5);
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV6:
			ogs_assert(message->cm.connection_establishment_command.address.length == 17);
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4V6:
			ogs_assert(message->cm.connection_establishment_command.address.length == 21);
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_FQDN:
			ogs_assert(message->cm.connection_establishment_command.address.length >= 2);
			break;

		default:
			ogs_error("Invalid LMF LCS-UP address type (0x%.2x)", message->cm.connection_establishment_command.address.type);
			return encoded;
	}
	size = 1 + message->cm.connection_establishment_command.address.length;
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));
	memcpy(pkbuf->data - size, &message->cm.connection_establishment_command.address, size);
	encoded += size;

	/* Source LMF Routing ID IE (optional) */
	if(message->cm.connection_establishment_command.present & UPP_CM_CONN_ESTABLISHMENT_COMMAND_ROUTING_ID_PRESENT)
	{
		size = 2 + message->cm.connection_establishment_command.routing_id.length;
		ogs_assert(message->cm.connection_establishment_command.routing_id.length
					&& message->cm.connection_establishment_command.routing_id.iei == UPP_CM_LMF_ROUTING_ID_IEI
					&& ogs_pkbuf_pull(pkbuf, size));
		memcpy(pkbuf->data - size, &message->cm.connection_establishment_command.routing_id, size);
		encoded += size;
	}

	return encoded;
}

int ogs_upp_encode_connection_establishment_reject(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	int encoded = 0, size;

	ogs_assert(pkbuf);
	ogs_assert(message);

	/* Initially, we need at least one octet */
    size = 1;
    ogs_assert(message->type == UPP_CM_CONN_ESTABLISHMENT_REJECT
                && message->present == OGS_UPP_MESSAGE_PRESENT_CM
                && ogs_pkbuf_pull(pkbuf, size));

    memcpy(pkbuf->data - size, &message->type, 1);
	encoded++;

	/* Back-off timer IE (optional) */
	if(message->cm.connection_establishment_reject.present & UPP_CM_CONN_ESTABLISHMENT_REJECT_BACKOFF_TIMER_PRESENT)
	{
		size = 3;
		ogs_assert(ogs_pkbuf_pull(pkbuf, size));

		memcpy(pkbuf->data - size, &message->cm.connection_establishment_reject.backoff_timer, size);
		encoded += size;
	}

	return encoded;
}

int ogs_upp_encode_connection_release_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	int encoded = 0, size;

    ogs_assert(pkbuf);
    ogs_assert(message);

    /* Initially, we need at least one octet */
    size = 1;
    ogs_assert(message->type == UPP_CM_CONN_RELEASE_COMMAND
                && message->present == OGS_UPP_MESSAGE_PRESENT_CM
                && ogs_pkbuf_pull(pkbuf, size));

    memcpy(pkbuf->data - size, &message->type, 1);
    encoded++;

    /* Back-off timer IE (optional) */
    if(message->cm.connection_release_command.present & UPP_CM_CONN_RELEASE_COMMAND_BACKOFF_TIMER_PRESENT)
    {
        size = 3;
        ogs_assert(ogs_pkbuf_pull(pkbuf, size));

        memcpy(pkbuf->data - size, &message->cm.connection_release_command.backoff_timer, size);
        encoded += size;
    }

    return encoded;
}

int ogs_upp_encode_connection_modification_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	int encoded = 0, size;

    ogs_assert(pkbuf);
    ogs_assert(message);

    /* Initially, we need at least one octet */
    size = 1;
    ogs_assert(message->type == UPP_CM_CONN_MODIFICATION_COMMAND
                && message->present == OGS_UPP_MESSAGE_PRESENT_CM
                && ogs_pkbuf_pull(pkbuf, size));

    memcpy(pkbuf->data - size, &message->type, 1);
    encoded++;

	/* Source LMF routing ID IE (optional) */
    if(message->cm.connection_modification_command.present & UPP_CM_CONN_MODIFICATION_COMMAND_ROUTING_ID_PRESENT)
    {
        size = 2 + message->cm.connection_modification_command.routing_id.length;
        ogs_assert(message->cm.connection_modification_command.routing_id.length
                    && message->cm.connection_modification_command.routing_id.iei == UPP_CM_LMF_ROUTING_ID_IEI
                    && ogs_pkbuf_pull(pkbuf, size));
        memcpy(pkbuf->data - size, &message->cm.connection_modification_command.routing_id, size);
        encoded += size;
    }

    return encoded;
}
