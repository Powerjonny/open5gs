/*
 * Copyright (C) 2025 by Juraj Elias <juraj.elias@gmail.com>
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

#ifndef LMF_EVENT_H
#define LMF_EVENT_H

#include "ogs-proto.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LMF_EVENT_BASE = OGS_MAX_NUM_OF_PROTO_EVENT,

	LMF_EVENT_UPP_MESSAGE,					/* triggered when a UPP message has been received */
	LMF_EVENT_UPP_TIMER,					/* triggered when a UPP related timer is set/expired */
	LMF_EVENT_UPP_CONNECTION_ESTABLISHMENT,	/* triggered when N1 notifications were successfully subscribed to AMF and we are in disconnected state OR
											   the AMF invokes the Nlmf_Location_UPConfig Request service operation (TS 24.572, 6.2.2.1) */
	LMF_EVENT_UPP_CONNECTION_RELEASE,		/* triggered when a the inactivity timer of an active LCS-UP connection expires OR a CONNECTION RELEASE REQUEST
											   has been received from a UE */

	LMF_EVENT_LPP_MESSAGE_CP,				/* triggered when a LPP message has been received via control plane (e.g. as part of a MO-LR) */
	LMF_EVENT_LPP_MESSAGE_UP,				/* triggered when a LPP message has been received via user plane */
	LMF_EVENT_LPP_REQUEST_CAPABILITIES,		/* triggered when LPP notifications were successfully subscribed to AMF and no LPP message has been previously received */
/*    LMF_EVENT_NGAP_MESSAGE,
    AMF_EVENT_NGAP_TIMER,
    AMF_EVENT_NGAP_LO_ACCEPT,
    AMF_EVENT_NGAP_LO_SCTP_COMM_UP,
    AMF_EVENT_NGAP_LO_CONNREFUSED,

    AMF_EVENT_5GMM_MESSAGE,
    AMF_EVENT_5GMM_TIMER,
    AMF_EVENT_5GSM_MESSAGE,
    AMF_EVENT_5GSM_TIMER,*/

    MAX_NUM_OF_LMF_EVENT,

} lmf_event_e;

typedef struct lmf_event_s {
    ogs_event_t h;

	ogs_pool_id_t lr_id;		/* ID of a target location request */
	ogs_pool_id_t binding_id;	/* Binding ID of a target LCS-UP context */
	ogs_pkbuf_t *message;		/* Received N1 message from AMF */

} lmf_event_t;

OGS_STATIC_ASSERT(OGS_EVENT_SIZE >= sizeof(lmf_event_t));

lmf_event_t *lmf_event_new(int id);
const char *lmf_event_get_name(lmf_event_t *e);

#ifdef __cplusplus
}
#endif

#endif /* LMF_EVENT_H */
