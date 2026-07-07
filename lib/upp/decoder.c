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

int ogs_upp_decode_uplink_lcs_transport(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0, size;

	ogs_assert(message);
	ogs_assert(pkbuf);

	if(pkbuf->len < 7)
	{
		ogs_error("Too less data to be decoded (Uplink LCS-UP Transport)");
		return 0;
	}

	/* Message body is set to LCS-UPP */
	message->present = OGS_UPP_MESSAGE_PRESENT_LCS;

	/* Copy first 2 octets to target structure */
	size = 2;
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));

    memcpy(&message->type, pkbuf->data - size, 1);
	memcpy(&message->lcs.ul_lcs_up_transport.payload_container_type, pkbuf->data - size + 1, 1);
	decoded += 2;

	/* Convert payload container length (network byte order) */
	message->lcs.ul_lcs_up_transport.payload.length = (pkbuf->data[0] << 8 | pkbuf->data[1]);
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));
    decoded += 2;

	/* Check payload container size and copy it to message buffer */
	size = message->lcs.ul_lcs_up_transport.payload.length;
	ogs_assert(size && ogs_pkbuf_pull(pkbuf, size));
	memcpy(message->lcs.ul_lcs_up_transport.payload.contents, pkbuf->data - size, size);
	decoded += size;

	/* LCS Session Identity IE */
	size = 1;
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));
	memcpy(&message->lcs.ul_lcs_up_transport.session_identity.length, pkbuf->data - size, size);

	size = message->lcs.ul_lcs_up_transport.session_identity.length;
	ogs_assert(size && ogs_pkbuf_pull(pkbuf, size));

	memcpy(message->lcs.ul_lcs_up_transport.session_identity.identity, pkbuf->data - size, size);
	decoded += size;

	return decoded;
}

int ogs_upp_decode_connection_binding_request(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0, size;

	ogs_assert(message);
    ogs_assert(pkbuf);

	if(pkbuf->len < 2 + UPP_CM_LCS_UP_BINDING_ID_MIN)
    {
        ogs_error("Too less data to be decoded (Connection Binding Request).");
        return 0;
    }

    /* Message body is set to LCS-UPP */
    message->present = OGS_UPP_MESSAGE_PRESENT_LCS;

    /* Copy first 6 octets to target structure */
    size = 2 + UPP_CM_LCS_UP_BINDING_ID_MIN;
    ogs_assert(ogs_pkbuf_pull(pkbuf, size));

    memcpy(&message->type, pkbuf->data - size, 1);
    memcpy(&message->lcs.binding_request, pkbuf->data - size + 1, size - 1);
    decoded += size;

	return decoded;
}

int ogs_upp_decode_connection_establishment_failure(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0, size;

	ogs_assert(message);
    ogs_assert(pkbuf);

	if(pkbuf->len < 2)
	{
		ogs_error("Too less data to be decoded (Connection Establishment Failure).");
		return 0;
	}

    /* Message body is set to UPP-CM */
    message->present = OGS_UPP_MESSAGE_PRESENT_CM;

	/* This message type consists always of two octets */
	size = 2;
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));

	memcpy(&message->type, pkbuf->data - size, 1);
    memcpy(&message->cm.connection_establishment_failure.cause.value, pkbuf->data - size + 1, size - 1);
    decoded += size;

	return decoded;
}

int ogs_upp_decode_connection_release_request(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0, size;

	ogs_assert(message);
    ogs_assert(pkbuf);

	if(!pkbuf->len)
	{
		ogs_error("Too less data to be decoded (Connection Release Request).");
		return 0;
	}

    /* Message body is set to UPP-CM */
    message->present = OGS_UPP_MESSAGE_PRESENT_CM;

	/* Copy message type */
	size = 1;
	ogs_assert(ogs_pkbuf_pull(pkbuf, size));

    memcpy(&message->type, pkbuf->data - size, size);
	decoded++;

	/* Check if optional Failure Cause IE is included */
	size = 2;
	if(ogs_pkbuf_pull(pkbuf, size) == NULL)
    {
        return decoded;
    }
	message->cm.connection_release_request.present |= UPP_CM_CONN_RELEASE_REQUEST_FAILURE_CAUSE_PRESENT;
	memcpy(&message->cm.connection_release_request.cause, pkbuf->data - size, size);
	decoded += size;

	return decoded;
}

int ogs_upp_decode_connection_modification_reject(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0, size;

    ogs_assert(message);
    ogs_assert(pkbuf);

    if(pkbuf->len < 2)
    {
        ogs_error("Too less data to be decoded (Connection Modification Reject).");
        return 0;
    }

    /* Message body is set to UPP-CM */
    message->present = OGS_UPP_MESSAGE_PRESENT_CM;

    /* This message type consists always of two octets */
    size = 2;
    ogs_assert(ogs_pkbuf_pull(pkbuf, size));

    memcpy(&message->type, pkbuf->data - size, 1);
    memcpy(&message->cm.connection_modification_reject.cause.value, pkbuf->data - size + 1, size - 1);
    decoded += size;

    return decoded;
}
