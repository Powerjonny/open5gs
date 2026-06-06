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

#include "context.h"
#include "namf-build.h"
#include "sbi-path.h"

static lmf_context_t self;

int __lmf_log_domain;

static OGS_POOL(lmf_location_request_pool, lmf_location_request_t);
static OGS_POOL(lmf_lcs_up_context_pool, lmf_lcs_up_context_t);
static OGS_POOL(lmf_subscription_pool, lmf_subscription_t);

static int context_initialized = 0;

static int max_num_of_location_request = 0;
static int max_num_of_subscriptions = 0;
//static int max_num_of_upp_connection = 8; //TODO: allow setting this value via config file in future!

void lmf_context_init(void)
{
    ogs_assert(context_initialized == 0);

    /* Initialize LMF context */
    memset(&self, 0, sizeof(lmf_context_t));

    ogs_log_install_domain(&__lmf_log_domain, "lmf", ogs_core()->log.level);
    ogs_log_install_domain(&__ogs_lpp_domain, "lpp", ogs_core()->log.level);
    ogs_log_install_domain(&__ogs_nrppa_domain, "nrppa", ogs_core()->log.level);
	ogs_log_install_domain(&__ogs_upp_domain, "upp", ogs_core()->log.level);

#define MAX_NUM_OF_LOCATION_REQUEST 32
#define MAX_NUM_OF_SUBSCRIPTIONS 32
    max_num_of_location_request = ogs_global_conf()->max.ue * MAX_NUM_OF_LOCATION_REQUEST;
    ogs_pool_init(&lmf_location_request_pool, max_num_of_location_request);
	ogs_pool_init(&lmf_lcs_up_context_pool, ogs_global_conf()->max.ue);	//one LCS-UP connection per UE
	max_num_of_subscriptions = ogs_global_conf()->max.ue * MAX_NUM_OF_SUBSCRIPTIONS;
	ogs_pool_init(&lmf_subscription_pool, max_num_of_subscriptions); //32 subscriptions per UE

    ogs_list_init(&self.location_request_list);
	ogs_list_init(&self.subscriptions);
	ogs_list_init(&self.lcs_up_context_list);

	memset(&self.lcsup_server, 0, sizeof(lmf_lcs_up_server_t));

    context_initialized = 1;
}

void lmf_context_final(void)
{
    ogs_assert(context_initialized == 1);

    context_initialized = 0;
}

lmf_context_t *lmf_self(void)
{
    return &self;
}

static int lmf_context_prepare(void)
{
    return OGS_OK;
}

static int lmf_context_validation(void)
{
    return OGS_OK;
}

/* Build NF Info IE for NRF registration */
int lmf_context_nf_info(void)
{
    ogs_sbi_nf_instance_t *nf_instance = NULL;
    ogs_sbi_nf_info_t *nf_info = NULL;

    nf_instance = ogs_sbi_self()->nf_instance;
    ogs_assert(nf_instance);

    nf_info = ogs_sbi_nf_info_add(
                &nf_instance->nf_info_list, OpenAPI_nf_type_LMF);
    ogs_assert(nf_info);

    nf_info->lmf.lmf_id = ogs_strdup(NF_INSTANCE_ID(ogs_sbi_self()->nf_instance));
	ogs_assert(nf_info->lmf.lmf_id);
	nf_info->lmf.lcs_up_support = true; //we support LCS over user plane

	return OGS_OK;
}

int lmf_context_parse_config(void)
{
    int rv;
    yaml_document_t *document = NULL;
    ogs_yaml_iter_t root_iter;
	int idx = 0;

    document = ogs_app()->document;
    ogs_assert(document);

    rv = lmf_context_prepare();
    if (rv != OGS_OK) return rv;

    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);

		if((!strcmp(root_key, "lmf")) && (idx++ == ogs_app()->config_section_id))
		{
			ogs_yaml_iter_t lmf_iter;
            ogs_yaml_iter_recurse(&root_iter, &lmf_iter);
            while (ogs_yaml_iter_next(&lmf_iter)) {
				const char *lmf_key = ogs_yaml_iter_key(&lmf_iter);
                ogs_assert(lmf_key);

				/* LCS-UP section */
				if (!strcmp(lmf_key, "lcs-up")) {
					ogs_yaml_iter_t lcsup_iter;
                    ogs_yaml_iter_recurse(&lmf_iter, &lcsup_iter);
                    while (ogs_yaml_iter_next(&lcsup_iter)) {
                        const char *lcsup_key = ogs_yaml_iter_key(&lcsup_iter);
                        ogs_assert(lcsup_key);

						/* Subsection server */
						if (!strcmp(lcsup_key, "server")) {
                            ogs_yaml_iter_t server_iter;
                            ogs_yaml_iter_recurse(&lcsup_iter, &server_iter);

							while (ogs_yaml_iter_next(&server_iter)) {
								const char *server_key = ogs_yaml_iter_key(&server_iter);
		                        ogs_assert(server_key);

								/* Target interface name */
								if(!strcmp(server_key, "interface"))
								{
									self.lcsup_server.iface_name = ogs_strdup(ogs_yaml_iter_value(&server_iter));
									ogs_assert(self.lcsup_server.iface_name);
								}

								/* LCS-UP address family */
								else if(!strcmp(server_key, "family"))
								{
									const char *family = ogs_yaml_iter_value(&server_iter);
									switch(atoi(family)) //if wrong input, atoi(3) returns zero (AF_INET).
									{
										case 0:
											self.lcsup_server.family = AF_INET;
											break;

										case 1:
											self.lcsup_server.family = AF_INET6;
											break;

										case 2:
											//TODO: handle FQDN here...
											ogs_warn("FQDN is currently not handled in LCS-UP section.");
											break;

										default:
											ogs_warn("Unknown family identifier (%d). Use 0 (AF_INET) as default.", atoi(family));
											break;
									}
								}

								/* TLS subsection */
								else if(!strcmp(server_key, "tls"))
								{
									ogs_yaml_iter_t tls_iter;
 		                            ogs_yaml_iter_recurse(&server_iter, &tls_iter);

     		                       while (ogs_yaml_iter_next(&tls_iter)) {
            		                    const char *tls_key = ogs_yaml_iter_key(&tls_iter);
                    		            ogs_assert(tls_key);

										/* TLS base */
										if(!strcmp(tls_key, "base"))
                                		{
											const char *base = ogs_yaml_iter_value(&tls_iter);

											if(atoi(base) < 0 || atoi(base) >= MAX_NUM_OF_LCS_UP_SERVER_BASE)
											{
												ogs_warn("TLS base is invalid (%s). Use TCP as default.", base);
												self.lcsup_server.base = LMF_LCS_UP_SERVER_BASE_TCP;
											}
											else
											{
												self.lcsup_server.base = atoi(base);
											}
										}

										/* TLS server's private key */
										else if(!strcmp(tls_key, "private_key"))
										{
											self.lcsup_server.private_key = ogs_strdup(ogs_yaml_iter_value(&tls_iter));
		                                    ogs_assert(self.lcsup_server.private_key);
										}

										/* TLS server's certificate */
										else if(!strcmp(tls_key, "cert"))
                                        {
                                            self.lcsup_server.cert_file = ogs_strdup(ogs_yaml_iter_value(&tls_iter));
                                            ogs_assert(self.lcsup_server.cert_file);
                                        }

										else
										{
											ogs_warn("Unknown key in LCS-UP section detected: %s", tls_key);
										}
									}

								}

							}
						}
					}

				}
			}
		}
    }

    rv = lmf_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}

/* ##################################################################### */
/* ######################## LOCATION REQUEST ########################### */
/* ##################################################################### */

lmf_location_request_t *lmf_location_request_add(void)
{
    lmf_location_request_t *location_request = NULL;

    ogs_pool_alloc(&lmf_location_request_pool, &location_request);
    ogs_assert(location_request);
    memset(location_request, 0, sizeof *location_request);

    location_request->id = ogs_pool_index(&lmf_location_request_pool, location_request);
    ogs_assert(location_request->id > 0 && location_request->id <= max_num_of_location_request);

    /* Initialize SBI object */
    ogs_list_init(&location_request->sbi.xact_list);

    /* Initialize stream_id to invalid */
    location_request->stream_id = OGS_INVALID_POOL_ID;

    ogs_list_add(&self.location_request_list, location_request);

    return location_request;
}

void lmf_location_request_remove(lmf_location_request_t *location_request)
{
	lmf_event_t e;

    ogs_assert(location_request);

	/* Shutdown state machines (LPP, UPP-CM, NRPPa) if enabled */
    if(location_request->ue_lcs_cap.lpp)
    {
        memset(&e, 0, sizeof(lmf_event_t));
        e.lr_id = location_request->id;
        ogs_fsm_fini(&location_request->lpp.sm, &e);
    }

#if 0
    if(location_request->ue_lcs_cap.lcsupp)
    {
        memset(&e, 0, sizeof(lmf_event_t));
        e.lr_id = location_request->id;
        ogs_fsm_fini(&location_request->upp.sm, &e);

		/* Remove LCS-UP connection */
		if(location_request->upp.connection)
		{
			//TODO: Invoke LCS-UP connection release command here.
			ogs_pool_id_free(&lmf_upp_connection_pool, location_request->upp.connection);
		}
    }
#endif
	//TODO: if NRPPa state machine is added, we have to stop it here!
#if 0
	/* Delete all Timers */
    CLEAR_LMF_ALL_TIMERS(location_request);
    ogs_timer_delete(location_request->t5012.timer);
#endif

    ogs_list_remove(&self.location_request_list, location_request);

    /* Clear xact pointer first to avoid double-free when ogs_sbi_xact_remove_all is called */
    location_request->xact = NULL;

    if (location_request->supi)
        ogs_free(location_request->supi);
    if (location_request->amf_id)
        ogs_free(location_request->amf_id);

    if (location_request->input_message) {
        /* Free InputData explicitly before freeing message */
        if (location_request->input_message->InputData) {
            OpenAPI_input_data_free(location_request->input_message->InputData);
            location_request->input_message->InputData = NULL;
        }
        ogs_sbi_message_free(location_request->input_message);
        ogs_free(location_request->input_message);
    }
    if (location_request->output_message) {
        ogs_sbi_message_free(location_request->output_message);
        ogs_free(location_request->output_message);
    }
    if (location_request->nrppa.nrppa_pdu)
	{
        ogs_pkbuf_free(location_request->nrppa.nrppa_pdu);
	}

    /* ogs_sbi_xact_remove_all will remove and free all xacts (including the one we stored in xact) */
    ogs_sbi_xact_remove_all(&location_request->sbi);
    ogs_sbi_object_free(&location_request->sbi);

    ogs_pool_id_free(&lmf_location_request_pool, location_request);
}

void lmf_location_request_remove_all(void)
{
    lmf_location_request_t *location_request = NULL, *next_location_request = NULL;

    ogs_list_for_each_safe(&self.location_request_list, next_location_request, location_request)
        lmf_location_request_remove(location_request);
}

void lmf_location_request_cancel(lmf_location_request_t *location_request, const char *message, int result_code)
{
	const char *ptr;
	ogs_sbi_stream_t *stream = NULL;
	ogs_assert(location_request);

	/* Send error response to client */
    stream = ogs_sbi_stream_find_by_id(location_request->stream_id);
    if (stream) {
		if(!message)
		{
			ptr = "Service determine-location failed";
		}
		else
		{
			ptr = message;
		}

        ogs_sbi_server_send_error(stream,
                    result_code,
                    NULL, ptr,
                    ptr, NULL);
    }
    else {
        ogs_error("[%s] Stream ID=%d not found for error response",
                location_request->supi, location_request->stream_id);
    }

	ogs_info("[%s] Remove Location Request", location_request->supi);

    /* Remove location request */
    lmf_location_request_remove(location_request);
}

static lmf_location_request_t *lmf_location_request_lookup(ogs_pool_id_t id)
{
    lmf_location_request_t *location_request = NULL;

    if (id <= 0 || id > max_num_of_location_request)
        return NULL;

    location_request = ogs_pool_find(&lmf_location_request_pool, id);
    if (!location_request)
        return NULL;

    return location_request;
}

lmf_location_request_t *lmf_location_request_find_by_id(ogs_pool_id_t id)
{
    lmf_location_request_t *location_request = NULL;

    location_request = lmf_location_request_lookup(id);
    ogs_assert(location_request);

    return location_request;
}

lmf_location_request_t *lmf_location_request_try_find_by_id(ogs_pool_id_t id)
{
    return lmf_location_request_lookup(id);
}

lmf_location_request_t *lmf_location_request_find_by_supi(const char *supi)
{
    lmf_location_request_t *location_request = NULL;

    ogs_assert(supi);

    ogs_list_for_each(&self.location_request_list, location_request) {
        if (location_request->supi &&
            strcmp(location_request->supi, supi) == 0)
            return location_request;
    }

    return NULL;
}

/* ##################################################################### */
/* ########################## SUBSCRIPTION ############################# */
/* ##################################################################### */

lmf_subscription_t* lmf_create_subscription(const char *supi, bool is_n1, void* type) {

	lmf_subscription_t *subscription = NULL;

	ogs_assert(supi);
	ogs_assert(type);

	/* Allocate a new subscription entry */
	ogs_pool_alloc(&lmf_subscription_pool, &subscription);
    ogs_assert(subscription);
    memset(subscription, 0, sizeof(lmf_subscription_t));

    subscription->id = ogs_pool_index(&lmf_subscription_pool, subscription);
    ogs_assert(subscription->id > 0 && subscription->id <= max_num_of_subscriptions);

	/* Initialize created subscription */
	subscription->supi = ogs_strdup(supi);
	ogs_assert(subscription->supi);
	subscription->is_n1 = is_n1;

	if(is_n1)
	{
		subscription->n1 = (OpenAPI_n1_message_class_e) type;
	}
	else
	{
		subscription->n2 = (OpenAPI_n2_information_class_e) type;
	}

	/* Adding subscription to LMF's internal list */
	ogs_list_add(&self.subscriptions, subscription);

	return subscription;
}


void lmf_remove_subscription(lmf_subscription_t *subscription) {

	ogs_assert(subscription);

	/* Remove target subscription from list */
	ogs_list_remove(&self.subscriptions, subscription);

	/* Free allocated memory */
	if(subscription->supi)
	{
		ogs_free(subscription->supi);
	}

	if(subscription->amf_id)
	{
		ogs_free(subscription->amf_id);
	}

	if(subscription->uri)
	{
		ogs_free(subscription->uri);
	}

	if(subscription->sid)
	{
		ogs_free(subscription->sid);
	}

	ogs_pool_id_free(&lmf_subscription_pool, subscription);
}

lmf_subscription_t* lmf_find_subscription(const char *supi, const char *amf_id, bool is_n1, uint8_t type)
{
	lmf_subscription_t *subscription = NULL;

	ogs_assert(supi);
	ogs_assert(type);

	ogs_list_for_each(&self.subscriptions, subscription) {
        if (subscription->supi &&
            strcmp(subscription->supi, supi) == 0)
		{
			/* Case I: N1 message subscription is needed */
			if(is_n1)
			{
				if(subscription->n1 == type)
				{
					/* Case I-I: AMF ID is provided */
					if(amf_id)
					{
						if(strcmp(subscription->amf_id, amf_id) == 0)
						{
							return subscription;
						}
					}

					/* Case I-II: AMF ID is not provided */
					else
					{
						return subscription;
					}
				}
			}

			/* Case II: N2 message subscription is needed */
			else
			{
				if(subscription->n2 == type)
				{
					/* Case II-I: AMF ID is provided */
                    if(amf_id)
                    {
                        if(strcmp(subscription->amf_id, amf_id) == 0)
                        {
                            return subscription;
                        }
                    }

                    /* Case II-II: AMF ID is not provided */
                    else
                    {
                        return subscription;
                    }
				}
			}
		}
    }

	return NULL;
}

/* ##################################################################### */
/* ########################## LCS-UP CONTEXT ########################### */
/* ##################################################################### */
lmf_lcs_up_context_t* lmf_create_lcs_up_context(const char *supi, bool lpp, bool mlcs_up) {

	lmf_lcs_up_context_t *ctx = NULL;
	lmf_event_t e;

	ogs_assert(supi);

	/* Check first, if a LCS-UP context already exists */
	if((ctx = lmf_find_lcs_up_context_by_supi(supi)) != NULL)
	{
		ogs_warn("[%s] LCS-UP context already exists (ID=%d).", supi, ctx->id);
		return NULL;
	}

	/* Allocate a new LCS-UP context */
	ogs_pool_alloc(&lmf_lcs_up_context_pool, &ctx);
    ogs_assert(ctx);
    memset(ctx, 0, sizeof(lmf_lcs_up_context_t));

    ctx->id = ogs_pool_index(&lmf_lcs_up_context_pool, ctx);
    ogs_assert(ctx->id > 0 && ctx->id <= ogs_global_conf()->max.ue);

	/* Assign SUPI to created LCS-UP context */
	ctx->supi = ogs_strdup(supi);
	ctx->ue_cap.lpp = lpp;
	ctx->ue_cap.mlcs_up = mlcs_up;

	/* Adding all timers */
    ctx->t5012.timer = ogs_timer_add(
            ogs_app()->timer_mgr, lmf_timer_t5012_expire,
            OGS_UINT_TO_POINTER(ctx->id));
    if (!ctx->t5012.timer) {
        ogs_error("ogs_timer_add() failed");
		ogs_free(ctx->supi);
		ogs_pool_id_free(&lmf_lcs_up_context_pool, ctx);
        return NULL;
    }
    ctx->t5012.pkbuf = NULL;
    ctx->t5012.retry_count = 0;

	/* Initialize SBI object */
    ogs_list_init(&ctx->sbi.xact_list);

	/* Adding to LMF's internal list */
	ogs_list_add(&self.lcs_up_context_list, ctx);

	/* Initialize LCS-UP context's state machine */
	memset(&e, 0, sizeof(lmf_event_t));
	e.binding_id = ctx->id;
	ogs_fsm_init(&ctx->sm, upp_state_initial, upp_state_final, &e);

	return ctx;
}

/* NOTE: This functions should be called when the state machine receives
 * its termination event via ogs_fsm_fini(&ctx->sm,...). */
void lmf_remove_lcs_up_context(lmf_lcs_up_context_t *ctx)
{
	lmf_location_request_t *lr = NULL;

	ogs_assert(ctx);

	/* Remove LCS-UP context from list */
	ogs_list_remove(&self.lcs_up_context_list, ctx);

	/* Delete all Timers */
    CLEAR_LCS_UP_ALL_TIMERS(ctx);
    ogs_timer_delete(ctx->t5012.timer);

	/* Remove reference on LR, if available */
	if((lr = lmf_location_request_find_by_supi(ctx->supi)) != NULL)
	{
		lr->upp.ctx = NULL;
	}

	/* Free allocated memory */
	if(ctx->supi)
	{
		ogs_free(ctx->supi);
	}

	/* ogs_sbi_xact_remove_all will remove and free all xacts (including the one we stored in xact) */
    ogs_sbi_xact_remove_all(&ctx->sbi);
    ogs_sbi_object_free(&ctx->sbi);

	ogs_pool_id_free(&lmf_lcs_up_context_pool, ctx);
}

lmf_lcs_up_context_t* lmf_find_lcs_up_context_by_id(ogs_pool_id_t id)
{
	lmf_lcs_up_context_t *ctx = NULL;

	ctx = ogs_pool_find(&lmf_lcs_up_context_pool, id);

	return ctx;
}

lmf_lcs_up_context_t* lmf_find_lcs_up_context_by_supi(const char *supi)
{
	lmf_lcs_up_context_t *ctx = NULL;
    ogs_assert(supi);

    /* Loop over internal LCS-UP context list */
    ogs_list_for_each(&self.lcs_up_context_list, ctx) {
        if(ctx->supi && strcmp(ctx->supi, supi) == 0)
        {
            return ctx;
        }
    }

    return NULL;
}

//TODO: If this call is successful, we sent a LCS-UP CONNECTION BINDING ACCEPT message back to the UE.
//      Otherwise, we destroy the TLS context and send a LCS-UP CONNECTION BINDING REJECT to the UE.
int lmf_update_lcs_up_context_by_tls(ogs_pool_id_t id, lmf_tls_context_t *tls)
{
	lmf_lcs_up_context_t *ctx = NULL;

	ogs_assert(tls);
	ogs_assert(id);

	ctx = ogs_pool_find(&lmf_lcs_up_context_pool, id);

	if(ctx)
	{
		if(ctx->tls)
		{
			ogs_error("[%s] LCS-UP context with ID=%d has already an TLS context.", ctx->supi, ctx->id);
			return OGS_ERROR;
		}

		ctx->tls = tls;

        return OGS_OK;
	}

	return OGS_ERROR;
}



/* ##################################################################### */
/* ############################### MISC ################################ */
/* ##################################################################### */
const char*
lmf_pos_method_to_string(pos_method_e method)
{
	switch(method)
	{
		case POS_A_GNSS:
			return "Assisted GNSS";
		case POS_OTDOA:
			return "Observed Time Difference of Arrival (OTDOA)";
		case POS_ECID:
			return "Enhanced Cell ID (ECID)";
        	case POS_WLAN:
			return "WLAN-based";
		case POS_BLE:
			return "Bluetooth-based";
		case POS_TBS:
			return "Terrestrial Beacon System (TBS)";
		case POS_SENSOR:
			return "Sensor-based";
		case POS_NR_ECID:
			return "NR Enhanced Cell ID (NR ECID)";
		case POS_M_RTT:
			return "Muli-Round Trip Time (Multi-RTT)";
		case POS_DL_AOD:
			return "Downlink Angle-of-Departure (DL-AoD)";
        	case POS_DL_TDOA:
			return "Downlink Time Difference of Arrival (DL-TDoA)";
        	case POS_UL_TDOA:
			return "Uplink Time Difference of Arrival (UL-TDoA)";
        	case POS_UL_AOA:
			return "Uplink Angle-of-Arrival (UL-AoA)";
		case POS_SL_RTT:
			return "Sidelink Round Trip Time (SL-RTT)";
		case POS_SL_AOA:
			return "Sidelink Angle-of-Arrival (SL-AoA)";
        	case POS_SL_TDOA:
			return "Sidelink Time Difference of Arrival (SL-TDoA)";
        	case POS_SL_TOA:
			return "Sidelink Time of Arrival (SL-ToA)";
        	case POS_DL_AIML:
			return "Downlink AI/ML positioning";
		default:
			return "(unset)";
	}
}


/* Handler that is triggered when a client request has been arrived */
static void lmf_ue_request_arrived(short when, ogs_socket_t fd, void *data)
{
    ogs_sock_t *sock = NULL;

    ogs_assert(fd != INVALID_SOCKET);
    sock = data;
    ogs_assert(sock);

    //TODO: accept UE and waiting for TLS negotiation by putting the new socket to the global pollset.

}

int lmf_init_lcsup_server()
{
    int rv = OGS_OK;

	/* Check, if LCS-UP server instance has been initialized */
	if(!self.lcsup_server.iface_name ||
	   !self.lcsup_server.private_key ||
	   !self.lcsup_server.cert_file ||
	   !self.lcsup_server.family)
	{
		ogs_warn("LCS-UP server instance has not been initialized via config file.");
		return rv;
	}

    /* Initialize server address structure */
    memset(&self.lcsup_server.addr, 0, sizeof(self.lcsup_server.addr));
    rv = ogs_get_address_by_interface_name(self.lcsup_server.iface_name, &self.lcsup_server.addr, self.lcsup_server.family);
    if(rv != OGS_OK)
    {
        return OGS_ERROR;
    }
    self.lcsup_server.addr.ogs_sin_port = htons(OGS_UPP_LMF_PORT);

    /* Initialize wolfSSL library */
    wolfSSL_Init();
	if((self.lcsup_server.ctx = wolfSSL_CTX_new(wolfTLSv1_3_server_method())) == NULL)
	{
		ogs_error("wolfSSL context could not be created.");
		wolfSSL_Cleanup();
		return OGS_ERROR;
	}

	/*
	 * Adding TLS certificate and private key
	 */
	if(wolfSSL_CTX_use_certificate_chain_file(self.lcsup_server.ctx, self.lcsup_server.cert_file) != SSL_SUCCESS)
	{
		ogs_error("TLS certificate %s could not be added to wolfSSL context.", self.lcsup_server.cert_file);
		wolfSSL_CTX_free(self.lcsup_server.ctx);
		wolfSSL_Cleanup();
        return OGS_ERROR;
	}

	if(wolfSSL_CTX_use_PrivateKey_file(self.lcsup_server.ctx, self.lcsup_server.private_key, SSL_FILETYPE_PEM) != SSL_SUCCESS)
	{
		ogs_error("Private key %s could not be added to wolfSSL context.", self.lcsup_server.private_key);
		wolfSSL_CTX_free(self.lcsup_server.ctx);
		wolfSSL_Cleanup();
        return OGS_ERROR;
	}

    /* Start LCS-UP server on port 65402 */
	if(self.lcsup_server.base == LMF_LCS_UP_SERVER_BASE_TCP)
	{
    	self.lcsup_server.sock = ogs_tcp_server(&self.lcsup_server.addr, NULL);
	}
	else
	{
		ogs_error("QUIC is currently not supported.");
		wolfSSL_CTX_free(self.lcsup_server.ctx);
		wolfSSL_Cleanup();
		return OGS_ERROR;
	}
    ogs_assert(self.lcsup_server.sock);

    /* Add listen socket to LMF's global pollset */
    self.lcsup_server.connect = ogs_pollset_add(ogs_app()->pollset, OGS_POLLIN, self.lcsup_server.sock->fd, lmf_ue_request_arrived, self.lcsup_server.sock);

	/* Set initialized flag to true */
	self.lcsup_server.initialized = true;

	ogs_info("LCS-UP server successfully initialized (base=%d, family=%d, IP address=%s)", self.lcsup_server.base, self.lcsup_server.family, inet_ntoa(self.lcsup_server.addr.sin.sin_addr));

    return OGS_OK;
}

lmf_lcs_up_server_t* lmf_get_lcs_up_server_instance(void)
{
	return &self.lcsup_server;
}
