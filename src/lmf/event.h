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

	LMF_EVENT_UPP_MESSAGE,

	LMF_EVENT_LPP_MESSAGE,
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

	ogs_pool_id_t lr_id;

} lmf_event_t;

OGS_STATIC_ASSERT(OGS_EVENT_SIZE >= sizeof(lmf_event_t));

lmf_event_t *lmf_event_new(int id);
const char *lmf_event_get_name(lmf_event_t *e);

#ifdef __cplusplus
}
#endif

#endif /* LMF_EVENT_H */
