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
#include "upp-build.h"

ogs_pkbuf_t*
upp_build_connection_establishment_command(ogs_pool_id_t binding_id, ogs_upp_cm_lcs_up_address_t *address, ogs_upp_cm_lmf_routing_id_t *routing_id)
{
	ogs_pkbuf_t *pkbuf = NULL;
	ogs_upp_message_t message;
	ogs_upp_cm_connection_establishment_command_t *cm = NULL;
	int encoded = 0;

	ogs_assert(binding_id);
	ogs_assert(address);

	/* Allocate a new pkbuf structure */
	pkbuf = ogs_pkbuf_alloc(NULL, sizeof(ogs_upp_message_t));

	if(!pkbuf)
	{
		ogs_error("ogs_pkbuf_alloc failed");
		return NULL;
	}

	/* Set size to maximum UPP message size */
	ogs_pkbuf_put(pkbuf, sizeof(ogs_upp_message_t));

	/* Initialize UPP message */
	memset(&message, 0, sizeof(ogs_upp_message_t));

	message.type = UPP_CM_CONN_ESTABLISHMENT_COMMAND;
	message.present = OGS_UPP_MESSAGE_PRESENT_CM;
	cm = &message.cm.connection_establishment_command;

	/* Binding ID IE */
	cm->binding_id.length = sizeof(binding_id);
	binding_id = htonl(binding_id); //network byte order
	memcpy(cm->binding_id.binding_id, &binding_id, sizeof(binding_id));

	/* LMF LCS-UP address IE */
	memcpy(&cm->address, address, sizeof(ogs_upp_cm_lcs_up_address_t));

	/* Source LMF Routing ID (optional) */
	if(routing_id)
	{
		cm->present |= UPP_CM_CONN_ESTABLISHMENT_COMMAND_ROUTING_ID_PRESENT;
		memcpy(&cm->routing_id, routing_id, sizeof(ogs_upp_cm_lmf_routing_id_t));
	}

	/* Encode UPP message */
	encoded = ogs_upp_encode_connection_establishment_command(pkbuf, &message);
	ogs_assert(encoded);

	/* Align data pointer of pkbuf + reset length */
	ogs_assert(ogs_pkbuf_push(pkbuf, encoded));
    pkbuf->len = encoded;

	ogs_debug("CONNECTION ESTABLISHMENT COMMAND message successfully encoded (%d B).", encoded);

	return pkbuf;
}

ogs_pkbuf_t* upp_build_connection_establishment_reject(ogs_upp_cm_back_off_timer_t *timer)
{
	ogs_pkbuf_t *pkbuf = NULL;
    ogs_upp_message_t message;
    ogs_upp_cm_connection_establishment_reject_t *rej = NULL;
    int encoded = 0;

    /* Allocate a new pkbuf structure */
    pkbuf = ogs_pkbuf_alloc(NULL, sizeof(ogs_upp_message_t));

    if(!pkbuf)
    {
        ogs_error("ogs_pkbuf_alloc failed");
        return NULL;
    }

    /* Set size to maximum UPP message size */
    ogs_pkbuf_put(pkbuf, sizeof(ogs_upp_message_t));

    /* Initialize UPP message */
    memset(&message, 0, sizeof(ogs_upp_message_t));
	message.type = UPP_CM_CONN_ESTABLISHMENT_REJECT;
    message.present = OGS_UPP_MESSAGE_PRESENT_CM;
    rej = &message.cm.connection_establishment_reject;

	/* Back-off Timer IE (optional) */
    if(timer)
    {
        rej->present = UPP_CM_CONN_ESTABLISHMENT_REJECT_BACKOFF_TIMER_PRESENT;
        memcpy(&rej->backoff_timer, timer, sizeof(ogs_upp_cm_back_off_timer_t));
        rej->backoff_timer.iei = UPP_CM_BACK_OFF_TIMER_IEI;
    }

	/* Encode UPP-CM message */
    encoded = ogs_upp_encode(pkbuf, &message);

    if(timer && encoded != 4)
    {
        ogs_error("Encoding of CONNECTION ESTABLISHMENT REJECT message with optional IE failed (%d/4 B).", encoded);
        ogs_pkbuf_free(pkbuf);
        return NULL;
    }
    else if(!timer && encoded != 1)
    {
        ogs_error("Encoding of CONNECTION ESTABLISHMENT REJECT message without optional IE failed (%d/1 B).", encoded);
        ogs_pkbuf_free(pkbuf);
        return NULL;
    }

    /* Align data pointer of pkbuf + reset length */
    ogs_assert(ogs_pkbuf_push(pkbuf, encoded));
    pkbuf->len = encoded;

    ogs_debug("CONNECTION ESTABLISHMENT REJECT message successfully encoded (%d B).", encoded);

    return pkbuf;

}

ogs_pkbuf_t* upp_build_connection_release_command(ogs_upp_cm_back_off_timer_t *timer)
{
	ogs_pkbuf_t *pkbuf = NULL;
    ogs_upp_message_t message;
	ogs_upp_cm_connection_release_command_t *cmd = NULL;
	int encoded = 0;

	/* Allocate a new pkbuf structure */
    pkbuf = ogs_pkbuf_alloc(NULL, sizeof(ogs_upp_message_t));

    if(!pkbuf)
    {
        ogs_error("ogs_pkbuf_alloc failed");
        return NULL;
    }

    /* Set size to maximum UPP message size */
    ogs_pkbuf_put(pkbuf, sizeof(ogs_upp_message_t));

    /* Initialize UPP message */
    memset(&message, 0, sizeof(ogs_upp_message_t));

    message.type = UPP_CM_CONN_RELEASE_COMMAND;
    message.present = OGS_UPP_MESSAGE_PRESENT_CM;
    cmd = &message.cm.connection_release_command;

	/* Back-off Timer IE (optional) */
	if(timer)
	{
		cmd->present = UPP_CM_CONN_RELEASE_COMMAND_BACKOFF_TIMER_PRESENT;
		memcpy(&cmd->backoff_timer, timer, sizeof(ogs_upp_cm_back_off_timer_t));
		cmd->backoff_timer.iei = UPP_CM_BACK_OFF_TIMER_IEI;
	}

	/* Encode UPP-CM message */
	encoded = ogs_upp_encode(pkbuf, &message);

	if(timer && encoded != 4)
	{
		ogs_error("Encoding of CONNECTION RELEASE COMMAND message with optional IE failed (%d/4 B).", encoded);
		ogs_pkbuf_free(pkbuf);
		return NULL;
	}
	else if(!timer && encoded != 1)
	{
		ogs_error("Encoding of CONNECTION RELEASE COMMAND message without optional IE failed (%d/1 B).", encoded);
		ogs_pkbuf_free(pkbuf);
        return NULL;
	}

	/* Align data pointer of pkbuf + reset length */
    ogs_assert(ogs_pkbuf_push(pkbuf, encoded));
    pkbuf->len = encoded;

	ogs_debug("CONNECTION RELEASE COMMAND message successfully encoded (%d B).", encoded);

	return pkbuf;
}
