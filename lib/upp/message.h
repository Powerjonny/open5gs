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

#if !defined(OGS_UPP_INSIDE) && !defined(OGS_UPP_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_UPP_MESSAGE_H
#define OGS_UPP_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * LCS UPP message types
 *
 * see: TS 24.572, 11.1.3
 */
#define LCS_UPP_UL_LCS_TRANSPORT 0x41
#define LCS_UPP_DL_LCS_TRANSPORT 0x42
#define LCS_UPP_CONN_BINDING_REQUEST 0x43
#define LCS_UPP_CONN_BINDING_ACCEPT 0x44
#define LCS_UPP_CONN_BINDING_REJECT 0x45

/* 10.2.1 UL LCS-UP TRANSPORT */
typedef struct ogs_upp_lcs_uplink_lcs_up_transport_s
{
	ogs_upp_lcs_payload_type_t payload_container_type;
	ogs_upp_lcs_payload_t payload;
	ogs_upp_lcs_session_identity_t session_identity;
} ogs_upp_lcs_uplink_lcs_up_transport_t;

/* 10.2.2 DL LCS-UP TRANSPORT */
typedef struct ogs_upp_lcs_downlink_lcs_up_transport_s
{
	ogs_upp_lcs_payload_type_t payload_container_type;
    ogs_upp_lcs_payload_t payload;
    ogs_upp_lcs_session_identity_t session_identity;
} ogs_upp_lcs_downlink_lcs_up_transport_t;

/* 10.2.3 LCS-UP CONNECTION BINDING REQUEST */
typedef struct ogs_upp_lcs_connection_binding_request_s
{
	ogs_upp_cm_lcs_up_binding_id_t binding_id;
} ogs_upp_lcs_connection_binding_request_t;

/*
 * ogs_upp_lcs_message - 5G User Plane Protocol Location Services message
 *
 * see: TS 24.572, 10.2
 */
typedef struct ogs_upp_lcs_message_s
{
	union {
		ogs_upp_lcs_uplink_lcs_up_transport_t ul_lcs_up_transport;
		ogs_upp_lcs_downlink_lcs_up_transport_t dl_lcs_up_transport;
		ogs_upp_lcs_connection_binding_request_t binding_request;
	};
} ogs_upp_lcs_message_t;

/*
 * UPP CM message types
 *
 * see: TS 24.572, 11.1.3
 */
#define UPP_CM_CONN_ESTABLISHMENT_COMMAND 0xc1
#define UPP_CM_CONN_ESTABLISHMENT_COMPLETE 0xc2
#define UPP_CM_CONN_ESTABLISHMENT_FAILURE 0xc3
#define UPP_CM_CONN_ESTABLISHMENT_REQUEST 0xc4
#define UPP_CM_CONN_ESTABLISHMENT_REJECT 0xc5
#define UPP_CM_CONN_RELEASE_COMMAND 0xc6
#define UPP_CM_CONN_RELEASE_COMPLETE 0xc7
#define UPP_CM_CONN_RELEASE_REQUEST 0xc8
#define UPP_CM_CONN_MODIFICATION_COMMAND 0xc9
#define UPP_CM_CONN_MODIFICATION_COMPLETE 0xca
#define UPP_CM_CONN_MODIFICATION_REJECT 0xcb

/* 10.3.1 CONNECTION ESTABLISHMENT COMMAND */
#define UPP_CM_CONN_ESTABLISHMENT_COMMAND_ROUTING_ID_PRESENT (1 << 0)
typedef struct ogs_upp_cm_connection_establishment_command_s
{
	uint8_t present;
	ogs_upp_cm_lcs_up_binding_id_t binding_id;
	ogs_upp_cm_lcs_up_address_t address;
	ogs_upp_cm_lmf_routing_id_t routing_id;
} ogs_upp_cm_connection_establishment_command_t;

/* 10.3.3 CONNECTION ESTABLISHMENT FAILURE */
typedef struct ogs_upp_cm_connection_establishment_failure_s
{
	ogs_upp_cm_failure_cause_t cause;
} ogs_upp_cm_connection_establishment_failure_t;

/* 10.3.5 CONNECTION ESTABLISHMENT REJECT */
#define UPP_CM_CONN_ESTABLISHMENT_REJECT_BACKOFF_TIMER_PRESENT (1 << 0)
typedef struct ogs_upp_cm_connection_establishment_reject_s
{
	uint8_t present;
	ogs_upp_cm_back_off_timer_t backoff_timer;
} ogs_upp_cm_connection_establishment_reject_t;

/* 10.3.6 CONNECTION RELEASE COMMAND */
#define UPP_CM_CONN_RELEASE_COMMAND_BACKOFF_TIMER_PRESENT UPP_CM_CONN_ESTABLISHMENT_REJECT_BACKOFF_TIMER_PRESENT
typedef ogs_upp_cm_connection_establishment_reject_t ogs_upp_cm_connection_release_command_t;

/* 10.3.8 CONNECTION RELEASE REQUEST */
#define UPP_CM_CONN_RELEASE_REQUEST_FAILURE_CAUSE_PRESENT (1 << 0)
typedef struct ogs_upp_cm_connection_release_request_s
{
	uint8_t present;
	ogs_upp_cm_failure_cause_t cause;
} ogs_upp_cm_connection_release_request_t;

/* 10.3.9 CONNECTION MODIFICATION COMMAND */
#define UPP_CM_CONN_MODIFICATION_COMMAND_ROUTING_ID_PRESENT UPP_CM_CONN_ESTABLISHMENT_COMMAND_ROUTING_ID_PRESENT
typedef struct ogs_upp_cm_connection_modification_command_s
{
	uint8_t present;
	ogs_upp_cm_lmf_routing_id_t routing_id;
} ogs_upp_cm_connection_modification_command_t;

/* 10.3.11 CONNECTION MODIFICATION REJECT */
typedef struct ogs_upp_cm_connection_modification_reject_s
{
	ogs_upp_cm_failure_cause_t cause;
} ogs_upp_cm_connection_modification_reject_t;

/*
 * ogs_upp_cm_message - 5G User Plane Protocol Connection Management message
 *
 * see: 3GPP TS 24.572, 10.3
 */
typedef struct ogs_upp_cm_message_s
{
	union {
		ogs_upp_cm_connection_establishment_command_t connection_establishment_command;
		ogs_upp_cm_connection_establishment_failure_t connection_establishment_failure;
		ogs_upp_cm_connection_establishment_reject_t connection_establishment_reject;
		ogs_upp_cm_connection_release_command_t connection_release_command;
		ogs_upp_cm_connection_release_request_t connection_release_request;
		ogs_upp_cm_connection_modification_command_t connection_modification_command;
		ogs_upp_cm_connection_modification_reject_t connection_modification_reject;
	};
} ogs_upp_cm_message_t;

/*
 * User Plane Positioning Protocol message (TS 24.572)
 */
#define OGS_UPP_MESSAGE_PRESENT_LCS 0x01
#define OGS_UPP_MESSAGE_PRESENT_CM  0x02
typedef struct ogs_upp_message_s {
	uint8_t type;
    uint8_t present;
    union {
        ogs_upp_lcs_message_t lcs;
        ogs_upp_cm_message_t cm;
    };
} ogs_upp_message_t;


/* Encoding/Decoding functions */
int ogs_upp_decode(ogs_upp_message_t *message, ogs_pkbuf_t *pkbuf);
int ogs_upp_encode(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);

#ifdef __cplusplus
}
#endif

#endif /* OGS_UPP_MESSAGE_H */
