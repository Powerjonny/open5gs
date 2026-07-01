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

#if !defined(OGS_LPP_INSIDE) && !defined(OGS_LPP_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_LPP_MESSAGE_H
#define OGS_LPP_MESSAGE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LPP_LPP_Message ogs_lpp_message_t;

typedef struct ogs_lpp_session_s {
    LPP_SequenceNumber_t sqn_tx;			 /* last sequence number used for transmission of a LPP message towards the UE */
	LPP_SequenceNumber_t sqn_rx;   			 /* last sequence number that was used by the UE to transmit a LPP message */
	LPP_LPP_TransactionID_t transaction; 	 /* current transaction between LMF and UE */
	bool duplicate_detected;                 /* true, if a LPP message has been received twice (CP only) */
} ogs_lpp_session_t;

int ogs_lpp_decode(ogs_lpp_message_t *message, ogs_pkbuf_t *pkbuf);
ogs_pkbuf_t *ogs_lpp_encode(ogs_lpp_message_t *message);
void ogs_lpp_free(ogs_lpp_message_t *message);

#ifdef __cplusplus
}
#endif

#endif

