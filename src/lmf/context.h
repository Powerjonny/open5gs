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

#ifndef LMF_CONTEXT_H
#define LMF_CONTEXT_H

#include "ogs-app.h"
#include "ogs-sbi.h"

#include "ogs-lpp.h"
#include "ogs-nrppa.h"
#include "ogs-upp.h"

#include "lmf-sm.h"
#include "timer.h"

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int __lmf_log_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __lmf_log_domain

typedef enum {
	LMF_LCS_UP_SERVER_BASE_TCP = 0,
	LMF_LCS_UP_SERVER_BASE_QUIC,
	MAX_NUM_OF_LCS_UP_SERVER_BASE
} lmf_lcs_up_base_e;

typedef struct lmf_lcs_up_server_s {
    lmf_lcs_up_base_e base;
	bool initialized;

	int family;
	char *iface_name;
	char *private_key;
	char *cert_file;

	ogs_thread_t *thread;				/* Thread reference of waiting server */

    ogs_sock_t *sock;
	ogs_sockaddr_t addr;

	ogs_time_t timeout;					/* Timeout [ms] for LCS-UP connection establishment (TLS handshake, LCS-UP Binding Request) */

    WOLFSSL_CTX *ctx;
} lmf_lcs_up_server_t;

typedef struct lmf_context_s {
    ogs_list_t location_request_list;  	/* Active location requests */
	ogs_list_t subscriptions;			/* Active subscriptions for N1/N2 message notifications via AMF */
	ogs_list_t lcs_up_context_list;		/* Active LCS-UP connections */
	lmf_lcs_up_server_t lcsup_server;	/* Server for LCS-UP interactions */
} lmf_context_t;

/* Helper structures to pass multiple parameters as void* */
typedef struct lmf_subscribe_params_s
{
    OpenAPI_n1_message_class_e n1;
    OpenAPI_n2_information_class_e n2;
} lmf_subscribe_params_t;

typedef struct lmf_n1n2_message_params_s
{
    struct {
        OpenAPI_n1_message_class_e type;
        ogs_pkbuf_t *pkbuf;
    } n1;

    struct {
        OpenAPI_n2_information_class_e type;
        ogs_pkbuf_t *pkbuf;
    } n2;
} lmf_n1n2_message_params_t;

/*
 * UE Positioning methods in NG-RAN (TS 38.305)
 */
typedef enum {
	POS_UNSET = 0,
	POS_A_GNSS,
	POS_OTDOA,
	POS_ECID,
	POS_WLAN,
	POS_BLE,
	POS_TBS,
	POS_SENSOR,
	POS_NR_ECID,
	POS_M_RTT,
	POS_DL_AOD,
	POS_DL_TDOA,
	POS_UL_TDOA,
	POS_UL_AOA,
	POS_SL_RTT,
	POS_SL_AOA,
	POS_SL_TDOA,
	POS_SL_TOA,
	POS_DL_AIML,
	POS_LAST_ITEM
} pos_method_e;

/* N1/N2 subscription structure of a target UE */
typedef struct lmf_subscription_s {
	ogs_lnode_t lnode;

	char *supi;								/* SUPI of corresponding UE */
	char *amf_id;							/* NF ID of target AMF */

	ogs_pool_id_t id;						/* Internal ID */

	bool is_n1;								/* true, if subscription is for N1 messages */

	char *uri;								/* HTTP header.location entry */
	char *sid;								/* subscription ID on AMF side */
} lmf_subscription_t;

/* TLS context of secure LCS-UP connection */
typedef struct lmf_tls_context_s {
	lmf_lcs_up_base_e base;
	void *handle;
	ogs_sock_t *sock;
	ogs_poll_t *recv;
} lmf_tls_context_t;

/*
 * LCS-UP context structure of a target UE
 *
 * TS 23.273, 6.18.0:
 *
 * UE may have multiple LCS-UPP connections, UE shall have maximum one
 * LCS-UPP connection towards each LMF.
 */
typedef struct lmf_lcs_up_context_s {
	ogs_lnode_t lnode;

	ogs_sbi_object_t sbi;                   /* SBI object for transactions */
	ogs_sbi_xact_t *xact;                   /* Transaction for AMF communication */

	char *supi;								/* SUPI of corresponding UE */
	char *amf_id;							/* NF ID of target AMF if known */

	ogs_pool_id_t stream_id;				/* >0 if LCS-UP context has been initialized by UpConfig request from AMF (UE-initiated) */
	char *amf_cb_uri;
	ogs_sbi_client_t *client;				/* AMF notification client for LCS-UP context updates */
	ogs_pool_id_t correlation_id;			/* Correlation ID for AMF notifications */

	ogs_pool_id_t id;						/* Binding ID of LCS-UP connection */
	ogs_upp_cm_lcs_up_address_t address;	/* LMF LCS-UP address */

	lmf_subscription_t *subscription;		/* N1 subscription for UPP-CM notifications */

	OpenAPI_up_connection_status_e status;  /* LCS-UP connection status */

	struct
    {
        bool lpp;   	                     /* LPP is supported (TS 37.355) */
        bool mlcs_up;       	             /* Multiple LCS-UP connections are supported (TS 24.572) */
    } ue_cap;

	ogs_fsm_t sm;							/* State machine for UPP-CM handling */
	bool terminate;							/* flag to indicate the termination of @sm */
	bool init_release;					    /* flag to indicate if LCS-UP connection release procedure has been initiated (TS 24.572, 6.2.1.2) */

	lmf_tls_context_t *tls;					/* TLS context of secure LCS-UP connection */
	ogs_upp_message_t *message;			    /* UL LCS-UP TRANSPORT message, if received before the LCS-UP connection has been established. */

	ogs_upp_cm_failure_cause_t release_cause; /* Failure Cause IE, if received during UE-initiated LCS-UP connection release procedure */

	struct {								/* Timer for UPP-CM (TS 24.572, Table 12.3.2) */
        ogs_pkbuf_t     *pkbuf;
        ogs_timer_t     *timer;
        uint32_t        retry_count;
    } t5010, t5012, t5015, inactivity;

	/* Macros for timer management */
#define CLEAR_LCS_UP_ALL_TIMERS(__lCS) \
    do { \
		CLEAR_LCS_UP_TIMER((__lCS)->t5010); \
        CLEAR_LCS_UP_TIMER((__lCS)->t5012); \
		CLEAR_LCS_UP_TIMER((__lCS)->t5015); \
		CLEAR_LCS_UP_TIMER((__lCS)->inactivity); \
    } while(0);
#define CLEAR_LCS_UP_TIMER(__lCS_TIMER) \
    do { \
        ogs_timer_stop((__lCS_TIMER).timer); \
        if ((__lCS_TIMER).pkbuf) { \
            ogs_pkbuf_free((__lCS_TIMER).pkbuf); \
            (__lCS_TIMER).pkbuf = NULL; \
        } \
        (__lCS_TIMER).retry_count = 0; \
    } while(0);

} lmf_lcs_up_context_t;

typedef struct lmf_location_request_s {
    ogs_lnode_t lnode;

    ogs_sbi_object_t sbi;                /* SBI object for transactions */
    ogs_pool_id_t id;
	ogs_pool_id_t correlation_id;		 /* LCS Correlation Identifier */

    char *supi;                          /* UE SUPI */
    char *amf_id;                        /* AMF instance ID */
    ogs_nr_cgi_t nr_cgi;				 /* Serving NR cell identity */

    struct
    {
		bool lpp;						 /* LPP is supported (TS 37.355) */
		bool lcsupp;			 		 /* LCS via user plane is supported (TS 24.572) */
		bool mlcs_up;			 		 /* Multiple LCS-UP connections are supported (TS 24.572) */
    } ue_lcs_cap;

    bool is_molr;			 			 /* true if location request is a MO-LR */
    OpenAPI_ue_location_service_ind_e lcs_service_type;	/* LCS Service Indicator (Location estimate or requesting assistance data) */

    ogs_sbi_message_t *input_message;    /* Location request input message */
    pos_method_e pos_method;             /* ECID, OTDOA, etc. */

    ogs_sbi_xact_t *xact;                /* Transaction for AMF communication */

	/* LPP context */
	struct
	{
		ogs_pool_id_t xact_id;			  					/* transaction ID to assign correct response */
		lmf_subscription_t *subscription; 					/* subscription for LPP notifications (reference to @context.subscriptions) */
		ogs_fsm_t sm;					  					/* state machine for LPP handling */
		bool terminate;                   					/* flag to indicate the termination of @sm */
		ogs_pkbuf_t *message;			  					/* pending LPP message from received LR */

		ogs_lpp_session_t session;		  					/* control information of current LPP session */
		LPP_ProvideCapabilities_r9_IEs_t *capabilities;	  	/* UE's capabilities */

		bool user_plane;									/* true, if LPP messages are exchanged over user plane */
	} lpp;

	/* UPP context */
	struct
	{
		lmf_lcs_up_context_t *ctx; 		  /* LCS-UP context (reference to @context.lcs_up_context_list) */
	} upp;

    /* NRPPa context */
	struct
	{
		ogs_pool_id_t xact_id;		 	  /* ID of subscription request */
		lmf_subscription_t *subscription; /* subscription */
		ogs_fsm_t sm;					  /* state machine for NRPPa handling */
    	uint32_t measurement_id;          /* NRPPa measurement ID */
    	ogs_pkbuf_t *nrppa_pdu;           /* NRPPa PDU data */
	} nrppa;

    /* Location result */
    ogs_sbi_message_t *output_message;   /* Location response message */

    /* Callback */
    ogs_sbi_client_t *client;            /* Client for callback */

    /* Stream reference for async response (stored as stream_id) */
    ogs_pool_id_t stream_id;             /* Stream ID for async response */

	/* Timer */
#define CLEAR_LMF_ALL_TIMERS(__lMF) \
    do { \
        CLEAR_LMF_LR_TIMER((__lMF)->lpp_cp); \
    } while(0);
#define CLEAR_LMF_LR_TIMER(__lMF_TIMER) \
    do { \
        ogs_timer_stop((__lMF_TIMER).timer); \
        if ((__lMF_TIMER).pkbuf) { \
            ogs_pkbuf_free((__lMF_TIMER).pkbuf); \
            (__lMF_TIMER).pkbuf = NULL; \
        } \
        (__lMF_TIMER).retry_count = 0; \
    } while(0);
    struct {
        ogs_pkbuf_t     *pkbuf;
        ogs_timer_t     *timer;
        uint32_t        retry_count;
    } lpp_cp;

} lmf_location_request_t;

/* Data plane switch for LPP transmissions (default: control plane) */
#define LMF_LR_SWITCH_TO_UP(lR) { \
	if((lR)->upp.ctx && (lR)->upp.ctx->status == OpenAPI_up_connection_status_ESTABLISHED) \
	{ \
		(lR)->lpp.user_plane = true; \
		ogs_info("[%s] Switched to user plane for LPP message exchange (LR ID=%d).", (lR)->supi, (lR)->correlation_id); \
	} \
}

#define LMF_LR_SWITCH_TO_CP(lR) { \
	if((lR)->lpp.user_plane) \
	{ \
		(lR)->lpp.user_plane = false; \
	} \
}

/*
 * Generic parameter structure to pass different
 * data types to lmf_amf_sbi_discover_and_send.
 */
#define LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST 0x01
#define LMF_SBI_PARAMS_TYPE_LCS_UP_CONTEXT   0x02
typedef struct lmf_sbi_params_s {
    uint8_t type;
    union {
        lmf_location_request_t *location_request;
        lmf_lcs_up_context_t *lcs_up_context;
    };
} lmf_sbi_params_t;


void lmf_context_init(void);
void lmf_context_final(void);
lmf_context_t *lmf_self(void);

int lmf_context_parse_config(void);

int lmf_context_nf_info(void);

const char* lmf_pos_method_to_string(pos_method_e method);

/* Location request management */
lmf_location_request_t *lmf_location_request_add(void);
void lmf_location_request_remove(lmf_location_request_t *location_request);
void lmf_location_request_remove_all(void);
void lmf_location_request_cancel(lmf_location_request_t *location_request, const char *message, int result_code);

lmf_location_request_t *lmf_location_request_find_by_id(ogs_pool_id_t id);
lmf_location_request_t *lmf_location_request_try_find_by_id(ogs_pool_id_t id);
lmf_location_request_t *lmf_location_request_find_by_supi(const char *supi);
lmf_location_request_t *lmf_location_request_find_by_lcs_id(ogs_pool_id_t id);

/* Subscription management */
lmf_subscription_t* lmf_create_subscription(const char *supi, bool is_n1);
void lmf_remove_subscription(lmf_subscription_t *subscription);

lmf_subscription_t* lmf_find_subscription(const char *supi, const char *amf_id, bool is_n1);
lmf_subscription_t* lmf_find_subscription_by_subscription_id(const char *id);

/* LCS-UP context management */
lmf_lcs_up_context_t* lmf_create_lcs_up_context(const char *supi, bool lpp, bool mlcs_up);
void lmf_remove_lcs_up_context(lmf_lcs_up_context_t *ctx);

lmf_lcs_up_context_t* lmf_find_lcs_up_context_by_id(ogs_pool_id_t id);
lmf_lcs_up_context_t* lmf_find_lcs_up_context_by_supi(const char *supi);

void lmf_lcs_up_context_terminate_tls(lmf_lcs_up_context_t *context);

/* LCS-UP server management */
int lmf_init_lcsup_server(void);
lmf_lcs_up_server_t* lmf_get_lcs_up_server_instance(void);

#ifdef __cplusplus
}
#endif

#endif /* LMF_CONTEXT_H */
