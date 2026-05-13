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

#if !defined(OGS_UPP_INSIDE) && !defined(OGS_UPP_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_UPP_TYPES_H
#define OGS_UPP_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* 11.2.1 LCS-UP payload (LV-E, 3-65537) */
#define LCS_UPP_PAYLOAD_MAX 65535
typedef struct ogs_upp_lcs_payload_s
{
	uint16_t length;
	uint8_t contents[LCS_UPP_PAYLOAD_MAX];
} ogs_upp_lcs_payload_t;

/*... helper structure, if multiple LPP messages are included */
typedef struct ogs_upp_lcs_lpp_payload_s
{
	uint16_t length;
	uint8_t message[LCS_UPP_PAYLOAD_MAX-2];
} ogs_upp_lcs_lpp_payload_t;

/* 11.2.2 LCS-UP payload type (V, 1/2) */
#define LCS_UPP_PAYLOAD_TYPE_LPP 0x1
#define LCS_UPP_PAYLOAD_TYPE_LCS 0x2
typedef struct ogs_upp_lcs_payload_type_s
{
    ED2(uint8_t spare:4;, uint8_t value:4;)
} __attribute__ ((packed)) ogs_upp_lcs_payload_type_t;

/* 11.2.3 LCS session identity (LV, 2-256) */
#define LCS_UPP_SESSION_IDENTITY_MAX 255
typedef struct ogs_upp_lcs_session_identity_s
{
	uint8_t length;
	uint8_t identity[LCS_UPP_SESSION_IDENTITY_MAX];
} ogs_upp_lcs_session_identity_t;

/* 11.3.1 LMF LCS-UP address (LV, 3-256) */
#define UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4   0x01
#define UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV6   0x02
#define UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4V6 0x03
#define UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_FQDN   0x04 /* FQDN encoding: TS 23.003, 19.4.2.1 */

#define UPP_CM_LMF_LCS_UP_ADDRESS_MAX 254
typedef struct ogs_upp_cm_lcs_up_address_s
{
	uint8_t length;
	uint8_t type;
	uint8_t address[UPP_CM_LMF_LCS_UP_ADDRESS_MAX];
} ogs_upp_cm_lcs_up_address_t;

int ogs_upp_lookup_lcs_up_address(ogs_upp_cm_lcs_up_address_t *address, int port);

/* 11.3.2 Back-off timer (GPRS timer 3, TLV, TS 24.008: 10.5.7.4a) */
#define UPP_CM_BACK_OFF_TIMER_IEI 0x10

#define UPP_CM_BACK_OFF_TIMER_UNIT_TEN_MINUTES     0b000
#define UPP_CM_BACK_OFF_TIMER_UNIT_ONE_HOUR        0b001
#define UPP_CM_BACK_OFF_TIMER_UNIT_TEN_HOURS       0b010
#define UPP_CM_BACK_OFF_TIMER_UNIT_TWO_SECONDS     0b011
#define UPP_CM_BACK_OFF_TIMER_UNIT_THIRTY_SECONDS  0b100
#define UPP_CM_BACK_OFF_TIMER_UNIT_ONE_MINUTE      0b101
#define UPP_CM_BACK_OFF_TIMER_UNIT_DEACTIVATED     0b111 /* value 0b110 is not applicable to UPP */
typedef struct ogs_upp_cm_back_off_timer_s
{
	uint8_t iei;
	uint8_t length;
	ED2(uint8_t unit:3;, uint8_t value:5;)
} __attribute__ ((packed)) ogs_upp_cm_back_off_timer_t;

/* 11.3.3 Failure cause */
#define UPP_CM_FAILURE_CAUSE_IEI 0x21 /* TV format is only used for CONNECTION RELEASE REQUEST */

#define UPP_CM_FAILURE_CAUSE_PDU_SESSION_FAILURE                0x01
#define UPP_CM_FAILURE_CAUSE_TLS_CONNECTION_FAILURE	            0x02
#define UPP_CM_FAILURE_CAUSE_LCS_UP_CONNECTION_BINDING_FAILURE  0x03
#define UPP_CM_FAILURE_CAUSE_USER_PLANE_NOT_AVAILABLE           0x04
#define UPP_CM_FAILURE_CAUSE_SOURCE_LCS_UP_CONNECTION_NOT_FOUND 0x05
#define UPP_CM_FAILURE_CAUSE_PROTOCOL_ERROR						0x6F
typedef struct ogs_upp_cm_failure_cause_s
{
	uint8_t iei;
	uint8_t value;
} ogs_upp_cm_failure_cause_t;

/* 11.3.4 LCS-UP binding ID (LV, 5-256) */
#define UPP_CM_LCS_UP_BINDING_ID_MIN 4
#define UPP_CM_LCS_UP_BINDING_ID_MAX 255
typedef struct ogs_upp_cm_lcs_up_binding_id_s
{
	uint8_t length;
	uint8_t binding_id[UPP_CM_LCS_UP_BINDING_ID_MAX]; //at least 4 octets has to be used
} ogs_upp_cm_lcs_up_binding_id_t;

/* 11.3.5 LMF routing ID */
#define UPP_CM_LMF_ROUTING_ID_IEI 0x22
#define UPP_CM_LMF_ROUTING_ID_MAX 256
typedef struct ogs_upp_cm_lmf_routing_id_s
{
	uint8_t iei;
	uint8_t length;
	uint8_t routing_id[UPP_CM_LMF_ROUTING_ID_MAX];
} ogs_upp_cm_lmf_routing_id_t;

#ifdef __cplusplus
}
#endif

#endif /* OGS_UPP_TYPES_H */
