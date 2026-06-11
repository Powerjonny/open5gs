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

#include "ogs-upp.h"

int __ogs_upp_domain;

int ogs_upp_decode(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf)
{
	int decoded = 0;

	ogs_assert(message);
	ogs_assert(pkbuf);

	if(!pkbuf->len)
	{
		ogs_error("Input buffer does not contain any data.");
		return 0;
	}

	/* Initialize UPP message structure */
	memset(message, 0, sizeof(ogs_upp_message_t));

	/* Further handling depends on UPP message type (1st octet) */
	switch(pkbuf->data[0])
	{
		/* Some message types only consist of a single byte.
			Therefore, we can end here. */
		case UPP_CM_CONN_ESTABLISHMENT_COMPLETE:
		case UPP_CM_CONN_ESTABLISHMENT_REQUEST:
		case UPP_CM_CONN_RELEASE_COMPLETE:
		case UPP_CM_CONN_MODIFICATION_COMPLETE:
			message->type = pkbuf->data[0];
			decoded++;
			break;

		/* LCS-UPP message types */
		case LCS_UPP_UL_LCS_TRANSPORT:
			decoded += ogs_upp_decode_uplink_lcs_transport(message, pkbuf);
			break;

		case LCS_UPP_CONN_BINDING_REQUEST:
			decoded += ogs_upp_decode_connection_binding_request(message, pkbuf);
			break;

		/* UPP-CM message types */
		case UPP_CM_CONN_ESTABLISHMENT_FAILURE:
			decoded += ogs_upp_decode_connection_establishment_failure(message, pkbuf);
			break;

		case UPP_CM_CONN_RELEASE_REQUEST:
			decoded += ogs_upp_decode_connection_release_request(message, pkbuf);
			break;

		case UPP_CM_CONN_MODIFICATION_REJECT:
			decoded += ogs_upp_decode_connection_modification_reject(message, pkbuf);
			break;

		/* Message types with wrong direction */
		case LCS_UPP_DL_LCS_TRANSPORT:
		case LCS_UPP_CONN_BINDING_ACCEPT:
		case LCS_UPP_CONN_BINDING_REJECT:
		case UPP_CM_CONN_ESTABLISHMENT_COMMAND:
		case UPP_CM_CONN_ESTABLISHMENT_REJECT:
		case UPP_CM_CONN_RELEASE_COMMAND:
		case UPP_CM_CONN_MODIFICATION_COMMAND:
			ogs_error("Message type 0x%.2x can not be decoded on network side.", message->type);
			break;

		default:
			ogs_error("Unknown message type (0x%.2x)", message->type);
			break;
	}

	return decoded;
}

int ogs_upp_encode(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message)
{
	int encoded = 0;

    ogs_assert(message);
	ogs_assert(pkbuf);

	if(!pkbuf->len)
    {
        ogs_error("Input buffer is too small for encoding.");
        return 0;
    }

	/* Further handling depends on UPP message type (1st octet) */
    switch(message->type)
    {
        /* Some message types only consist of a single byte.
            Therefore, we can end here. */
        case LCS_UPP_CONN_BINDING_ACCEPT:
        case LCS_UPP_CONN_BINDING_REJECT:
			ogs_assert(ogs_pkbuf_pull(pkbuf, 1));
			memcpy(pkbuf->data - 1, &message->type, 1);
			encoded++;
            break;

        /* LCS-UPP message types */
        case LCS_UPP_DL_LCS_TRANSPORT:
            encoded += ogs_upp_encode_downlink_lcs_transport(pkbuf, message);
            break;

        /* UPP-CM message types */
        case UPP_CM_CONN_ESTABLISHMENT_COMMAND:
			encoded += ogs_upp_encode_connection_establishment_command(pkbuf, message);
            break;

        case UPP_CM_CONN_ESTABLISHMENT_REJECT:
			encoded += ogs_upp_encode_connection_establishment_reject(pkbuf, message);
            break;

        case UPP_CM_CONN_RELEASE_COMMAND:
			encoded += ogs_upp_encode_connection_release_command(pkbuf, message);
            break;

        case UPP_CM_CONN_MODIFICATION_COMMAND:
			encoded += ogs_upp_encode_connection_modification_command(pkbuf, message);
            break;

		/* Message types with wrong direction */
		case LCS_UPP_UL_LCS_TRANSPORT:
		case LCS_UPP_CONN_BINDING_REQUEST:
		case UPP_CM_CONN_ESTABLISHMENT_COMPLETE:
		case UPP_CM_CONN_ESTABLISHMENT_FAILURE:
		case UPP_CM_CONN_ESTABLISHMENT_REQUEST:
		case UPP_CM_CONN_RELEASE_COMPLETE:
		case UPP_CM_CONN_RELEASE_REQUEST:
		case UPP_CM_CONN_MODIFICATION_COMPLETE:
		case UPP_CM_CONN_MODIFICATION_REJECT:
			ogs_error("Message type 0x%.2x can not be encoded on network side.", message->type);
			break;

        default:
            ogs_error("Unknown message type (0x%.2x)", message->type);
            break;
    }

	return encoded;
}

const char*
ogs_upp_get_message_name(uint8_t type)
{
    switch(type)
    {
        case UPP_CM_CONN_ESTABLISHMENT_COMMAND:
            return "USER PLANE CONNECTION ESTABLISHMENT COMMAND";

        case UPP_CM_CONN_ESTABLISHMENT_COMPLETE:
            return "USER PLANE CONNECTION ESTABLISHMENT COMPLETE";

        case UPP_CM_CONN_ESTABLISHMENT_FAILURE:
            return "USER PLANE CONNECTION ESTABLISHMENT FAILURE";

        case UPP_CM_CONN_ESTABLISHMENT_REQUEST:
            return "USER PLANE CONNECTION ESTABLISHMENT REQUEST";

        case UPP_CM_CONN_ESTABLISHMENT_REJECT:
            return "USER PLANE CONNECTION ESTABLISHMENT REJECT";

        case UPP_CM_CONN_RELEASE_COMMAND:
            return "USER PLANE CONNECTION RELEASE COMMAND";

        case UPP_CM_CONN_RELEASE_COMPLETE:
            return "USER PLANE CONNECTION RELEASE COMPLETE";

        case UPP_CM_CONN_RELEASE_REQUEST:
            return "USER PLANE CONNECTION RELEASE REQUEST";

        case UPP_CM_CONN_MODIFICATION_COMMAND:
            return "USER PLANE CONNECTION MODIFICATION COMMAND";

        case UPP_CM_CONN_MODIFICATION_COMPLETE:
            return "USER PLANE CONNECTION MODIFICATION COMPLETE";

        case UPP_CM_CONN_MODIFICATION_REJECT:
            return "USER PLANE CONNECTION MODIFICATION REJECT";

        case LCS_UPP_UL_LCS_TRANSPORT:
            return "UL LCS-UP TRANSPORT";

        case LCS_UPP_DL_LCS_TRANSPORT:
            return "DL LCS-UP TRANSPORT";

        case LCS_UPP_CONN_BINDING_REQUEST:
            return "LCS-UP CONNECTION BINDING REQUEST";

        case LCS_UPP_CONN_BINDING_ACCEPT:
            return "LCS-UP CONNECTION BINDING ACCEPT";

        case LCS_UPP_CONN_BINDING_REJECT:
            return "LCS-UP CONNECTION BINDING REJECT";

        default:
            return "UNKNOWN";
    }
}
