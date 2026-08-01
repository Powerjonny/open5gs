#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pc_event_notification.h"

OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_create(
	OpenAPI_pc_event_t *event, OpenAPI_access_type_e acc_type,
	OpenAPI_additional_access_info_t *add_access_info,
	OpenAPI_additional_access_info_t *rel_access_info,
	OpenAPI_an_gw_address_t *an_gw_addr, OpenAPI_rat_type_e rat_type,
	OpenAPI_plmn_id_nid_t *plmn_id,
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category,
	OpenAPI_service_area_coverage_info_t *applied_cov, char *supi,
	char *gpsi, char *time_stamp,
	OpenAPI_pdu_session_information_t *pdu_session_info,
	OpenAPI_service_identification_t *rep_services,
	OpenAPI_failure_t *deliv_failure) {
	OpenAPI_pc_event_notification_t *pc_event_notification_local_var =
		ogs_malloc(sizeof(OpenAPI_pc_event_notification_t));
	ogs_assert(pc_event_notification_local_var);

	pc_event_notification_local_var->event = event;
	pc_event_notification_local_var->acc_type = acc_type;
	pc_event_notification_local_var->add_access_info = add_access_info;
	pc_event_notification_local_var->rel_access_info = rel_access_info;
	pc_event_notification_local_var->an_gw_addr = an_gw_addr;
	pc_event_notification_local_var->rat_type = rat_type;
	pc_event_notification_local_var->plmn_id = plmn_id;
	pc_event_notification_local_var->sat_backhaul_category =
		sat_backhaul_category;
	pc_event_notification_local_var->applied_cov = applied_cov;
	pc_event_notification_local_var->supi = supi;
	pc_event_notification_local_var->gpsi = gpsi;
	pc_event_notification_local_var->time_stamp = time_stamp;
	pc_event_notification_local_var->pdu_session_info = pdu_session_info;
	pc_event_notification_local_var->rep_services = rep_services;
	pc_event_notification_local_var->deliv_failure = deliv_failure;

	return pc_event_notification_local_var;
}

void OpenAPI_pc_event_notification_free(
	OpenAPI_pc_event_notification_t *pc_event_notification) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == pc_event_notification) {
		return;
	}
	if(pc_event_notification->event) {
		OpenAPI_pc_event_free(pc_event_notification->event);
		pc_event_notification->event = NULL;
	}
	if(pc_event_notification->add_access_info) {
		OpenAPI_additional_access_info_free(
			pc_event_notification->add_access_info);
		pc_event_notification->add_access_info = NULL;
	}
	if(pc_event_notification->rel_access_info) {
		OpenAPI_additional_access_info_free(
			pc_event_notification->rel_access_info);
		pc_event_notification->rel_access_info = NULL;
	}
	if(pc_event_notification->an_gw_addr) {
		OpenAPI_an_gw_address_free(pc_event_notification->an_gw_addr);
		pc_event_notification->an_gw_addr = NULL;
	}
	if(pc_event_notification->plmn_id) {
		OpenAPI_plmn_id_nid_free(pc_event_notification->plmn_id);
		pc_event_notification->plmn_id = NULL;
	}
	if(pc_event_notification->applied_cov) {
		OpenAPI_service_area_coverage_info_free(
			pc_event_notification->applied_cov);
		pc_event_notification->applied_cov = NULL;
	}
	if(pc_event_notification->supi) {
		ogs_free(pc_event_notification->supi);
		pc_event_notification->supi = NULL;
	}
	if(pc_event_notification->gpsi) {
		ogs_free(pc_event_notification->gpsi);
		pc_event_notification->gpsi = NULL;
	}
	if(pc_event_notification->time_stamp) {
		ogs_free(pc_event_notification->time_stamp);
		pc_event_notification->time_stamp = NULL;
	}
	if(pc_event_notification->pdu_session_info) {
		OpenAPI_pdu_session_information_free(
			pc_event_notification->pdu_session_info);
		pc_event_notification->pdu_session_info = NULL;
	}
	if(pc_event_notification->rep_services) {
		OpenAPI_service_identification_free(
			pc_event_notification->rep_services);
		pc_event_notification->rep_services = NULL;
	}
	if(pc_event_notification->deliv_failure) {
		OpenAPI_failure_free(pc_event_notification->deliv_failure);
		pc_event_notification->deliv_failure = NULL;
	}
	ogs_free(pc_event_notification);
}

cJSON *OpenAPI_pc_event_notification_convertToJSON(
	OpenAPI_pc_event_notification_t *pc_event_notification) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(pc_event_notification == NULL) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [PcEventNotification]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!pc_event_notification->event) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [event]");
		return NULL;
	}
	cJSON *event_local_JSON =
		OpenAPI_pc_event_convertToJSON(pc_event_notification->event);
	if(event_local_JSON == NULL) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [event]");
		goto end;
	}
	cJSON_AddItemToObject(item, "event", event_local_JSON);
	if(item->child == NULL) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [event]");
		goto end;
	}

	if(pc_event_notification->acc_type != OpenAPI_access_type_NULL) {
		if(cJSON_AddStringToObject(item, "accType",
		                           OpenAPI_access_type_ToString(
						   pc_event_notification->
						   acc_type)) == NULL)
		{
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [acc_type]");
			goto end;
		}
	}

	if(pc_event_notification->add_access_info) {
		cJSON *add_access_info_local_JSON =
			OpenAPI_additional_access_info_convertToJSON(
				pc_event_notification->add_access_info);
		if(add_access_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [add_access_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "addAccessInfo",
		                      add_access_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [add_access_info]");
			goto end;
		}
	}

	if(pc_event_notification->rel_access_info) {
		cJSON *rel_access_info_local_JSON =
			OpenAPI_additional_access_info_convertToJSON(
				pc_event_notification->rel_access_info);
		if(rel_access_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [rel_access_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "relAccessInfo",
		                      rel_access_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [rel_access_info]");
			goto end;
		}
	}

	if(pc_event_notification->an_gw_addr) {
		cJSON *an_gw_addr_local_JSON =
			OpenAPI_an_gw_address_convertToJSON(
				pc_event_notification->an_gw_addr);
		if(an_gw_addr_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [an_gw_addr]");
			goto end;
		}
		cJSON_AddItemToObject(item, "anGwAddr", an_gw_addr_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [an_gw_addr]");
			goto end;
		}
	}

	if(pc_event_notification->rat_type != OpenAPI_rat_type_NULL) {
		if(cJSON_AddStringToObject(item, "ratType",
		                           OpenAPI_rat_type_ToString(
						   pc_event_notification->
						   rat_type)) == NULL)
		{
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [rat_type]");
			goto end;
		}
	}

	if(pc_event_notification->plmn_id) {
		cJSON *plmn_id_local_JSON =
			OpenAPI_plmn_id_nid_convertToJSON(
				pc_event_notification->plmn_id);
		if(plmn_id_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [plmn_id]");
			goto end;
		}
		cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [plmn_id]");
			goto end;
		}
	}

	if(pc_event_notification->sat_backhaul_category !=
	   OpenAPI_satellite_backhaul_category_NULL)
	{
		if(cJSON_AddStringToObject(item, "satBackhaulCategory",
		                           OpenAPI_satellite_backhaul_category_ToString
		                                   (pc_event_notification->
		                                   sat_backhaul_category)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [sat_backhaul_category]");
			goto end;
		}
	}

	if(pc_event_notification->applied_cov) {
		cJSON *applied_cov_local_JSON =
			OpenAPI_service_area_coverage_info_convertToJSON(
				pc_event_notification->applied_cov);
		if(applied_cov_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [applied_cov]");
			goto end;
		}
		cJSON_AddItemToObject(item, "appliedCov",
		                      applied_cov_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [applied_cov]");
			goto end;
		}
	}

	if(pc_event_notification->supi) {
		if(cJSON_AddStringToObject(item, "supi",
		                           pc_event_notification->supi) == NULL)
		{
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [supi]");
			goto end;
		}
	}

	if(pc_event_notification->gpsi) {
		if(cJSON_AddStringToObject(item, "gpsi",
		                           pc_event_notification->gpsi) == NULL)
		{
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [gpsi]");
			goto end;
		}
	}

	if(!pc_event_notification->time_stamp) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [time_stamp]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "timeStamp",
	                           pc_event_notification->time_stamp) == NULL)
	{
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed [time_stamp]");
		goto end;
	}

	if(pc_event_notification->pdu_session_info) {
		cJSON *pdu_session_info_local_JSON =
			OpenAPI_pdu_session_information_convertToJSON(
				pc_event_notification->pdu_session_info);
		if(pdu_session_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [pdu_session_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "pduSessionInfo",
		                      pdu_session_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [pdu_session_info]");
			goto end;
		}
	}

	if(pc_event_notification->rep_services) {
		cJSON *rep_services_local_JSON =
			OpenAPI_service_identification_convertToJSON(
				pc_event_notification->rep_services);
		if(rep_services_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [rep_services]");
			goto end;
		}
		cJSON_AddItemToObject(item, "repServices",
		                      rep_services_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [rep_services]");
			goto end;
		}
	}

	if(pc_event_notification->deliv_failure) {
		cJSON *deliv_failure_local_JSON =
			OpenAPI_failure_convertToJSON(
				pc_event_notification->deliv_failure);
		if(deliv_failure_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [deliv_failure]");
			goto end;
		}
		cJSON_AddItemToObject(item, "delivFailure",
		                      deliv_failure_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_pc_event_notification_convertToJSON() failed [deliv_failure]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_parseFromJSON(
	cJSON *pc_event_notificationJSON) {
	OpenAPI_pc_event_notification_t *pc_event_notification_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *event = NULL;
	OpenAPI_pc_event_t *event_local_nonprim = NULL;
	cJSON *acc_type = NULL;
	OpenAPI_access_type_e acc_typeVariable = 0;
	cJSON *add_access_info = NULL;
	OpenAPI_additional_access_info_t *add_access_info_local_nonprim = NULL;
	cJSON *rel_access_info = NULL;
	OpenAPI_additional_access_info_t *rel_access_info_local_nonprim = NULL;
	cJSON *an_gw_addr = NULL;
	OpenAPI_an_gw_address_t *an_gw_addr_local_nonprim = NULL;
	cJSON *rat_type = NULL;
	OpenAPI_rat_type_e rat_typeVariable = 0;
	cJSON *plmn_id = NULL;
	OpenAPI_plmn_id_nid_t *plmn_id_local_nonprim = NULL;
	cJSON *sat_backhaul_category = NULL;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_categoryVariable = 0;
	cJSON *applied_cov = NULL;
	OpenAPI_service_area_coverage_info_t *applied_cov_local_nonprim = NULL;
	cJSON *supi = NULL;
	cJSON *gpsi = NULL;
	cJSON *time_stamp = NULL;
	cJSON *pdu_session_info = NULL;
	OpenAPI_pdu_session_information_t *pdu_session_info_local_nonprim =
		NULL;
	cJSON *rep_services = NULL;
	OpenAPI_service_identification_t *rep_services_local_nonprim = NULL;
	cJSON *deliv_failure = NULL;
	OpenAPI_failure_t *deliv_failure_local_nonprim = NULL;
	event = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                         "event");
	if(!event) {
		ogs_error(
			"OpenAPI_pc_event_notification_parseFromJSON() failed [event]");
		goto end;
	}
	event_local_nonprim = OpenAPI_pc_event_parseFromJSON(event);
	if(!event_local_nonprim) {
		ogs_error("OpenAPI_pc_event_parseFromJSON failed [event]");
		goto end;
	}

	acc_type = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                            "accType");
	if(acc_type) {
		if(!cJSON_IsString(acc_type)) {
			ogs_error(
				"OpenAPI_pc_event_notification_parseFromJSON() failed [acc_type]");
			goto end;
		}
		acc_typeVariable =
			OpenAPI_access_type_FromString(acc_type->valuestring);
	}

	add_access_info =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "addAccessInfo");
	if(add_access_info) {
		add_access_info_local_nonprim =
			OpenAPI_additional_access_info_parseFromJSON(
				add_access_info);
		if(!add_access_info_local_nonprim) {
			ogs_error(
				"OpenAPI_additional_access_info_parseFromJSON failed [add_access_info]");
			goto end;
		}
	}

	rel_access_info =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "relAccessInfo");
	if(rel_access_info) {
		rel_access_info_local_nonprim =
			OpenAPI_additional_access_info_parseFromJSON(
				rel_access_info);
		if(!rel_access_info_local_nonprim) {
			ogs_error(
				"OpenAPI_additional_access_info_parseFromJSON failed [rel_access_info]");
			goto end;
		}
	}

	an_gw_addr = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                              "anGwAddr");
	if(an_gw_addr) {
		an_gw_addr_local_nonprim =
			OpenAPI_an_gw_address_parseFromJSON(an_gw_addr);
		if(!an_gw_addr_local_nonprim) {
			ogs_error(
				"OpenAPI_an_gw_address_parseFromJSON failed [an_gw_addr]");
			goto end;
		}
	}

	rat_type = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                            "ratType");
	if(rat_type) {
		if(!cJSON_IsString(rat_type)) {
			ogs_error(
				"OpenAPI_pc_event_notification_parseFromJSON() failed [rat_type]");
			goto end;
		}
		rat_typeVariable =
			OpenAPI_rat_type_FromString(rat_type->valuestring);
	}

	plmn_id = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                           "plmnId");
	if(plmn_id) {
		plmn_id_local_nonprim =
			OpenAPI_plmn_id_nid_parseFromJSON(plmn_id);
		if(!plmn_id_local_nonprim) {
			ogs_error(
				"OpenAPI_plmn_id_nid_parseFromJSON failed [plmn_id]");
			goto end;
		}
	}

	sat_backhaul_category =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "satBackhaulCategory");
	if(sat_backhaul_category) {
		if(!cJSON_IsString(sat_backhaul_category)) {
			ogs_error(
				"OpenAPI_pc_event_notification_parseFromJSON() failed [sat_backhaul_category]");
			goto end;
		}
		sat_backhaul_categoryVariable =
			OpenAPI_satellite_backhaul_category_FromString(
				sat_backhaul_category->valuestring);
	}

	applied_cov =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "appliedCov");
	if(applied_cov) {
		applied_cov_local_nonprim =
			OpenAPI_service_area_coverage_info_parseFromJSON(
				applied_cov);
		if(!applied_cov_local_nonprim) {
			ogs_error(
				"OpenAPI_service_area_coverage_info_parseFromJSON failed [applied_cov]");
			goto end;
		}
	}

	supi = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                        "supi");
	if(supi) {
		if(!cJSON_IsString(supi) &&
		   !cJSON_IsNull(supi))
		{
			ogs_error(
				"OpenAPI_pc_event_notification_parseFromJSON() failed [supi]");
			goto end;
		}
	}

	gpsi = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                        "gpsi");
	if(gpsi) {
		if(!cJSON_IsString(gpsi) &&
		   !cJSON_IsNull(gpsi))
		{
			ogs_error(
				"OpenAPI_pc_event_notification_parseFromJSON() failed [gpsi]");
			goto end;
		}
	}

	time_stamp = cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
	                                              "timeStamp");
	if(!time_stamp) {
		ogs_error(
			"OpenAPI_pc_event_notification_parseFromJSON() failed [time_stamp]");
		goto end;
	}
	if(!cJSON_IsString(time_stamp) &&
	   !cJSON_IsNull(time_stamp))
	{
		ogs_error(
			"OpenAPI_pc_event_notification_parseFromJSON() failed [time_stamp]");
		goto end;
	}

	pdu_session_info =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "pduSessionInfo");
	if(pdu_session_info) {
		pdu_session_info_local_nonprim =
			OpenAPI_pdu_session_information_parseFromJSON(
				pdu_session_info);
		if(!pdu_session_info_local_nonprim) {
			ogs_error(
				"OpenAPI_pdu_session_information_parseFromJSON failed [pdu_session_info]");
			goto end;
		}
	}

	rep_services =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "repServices");
	if(rep_services) {
		rep_services_local_nonprim =
			OpenAPI_service_identification_parseFromJSON(
				rep_services);
		if(!rep_services_local_nonprim) {
			ogs_error(
				"OpenAPI_service_identification_parseFromJSON failed [rep_services]");
			goto end;
		}
	}

	deliv_failure =
		cJSON_GetObjectItemCaseSensitive(pc_event_notificationJSON,
		                                 "delivFailure");
	if(deliv_failure) {
		deliv_failure_local_nonprim =
			OpenAPI_failure_parseFromJSON(deliv_failure);
		if(!deliv_failure_local_nonprim) {
			ogs_error(
				"OpenAPI_failure_parseFromJSON failed [deliv_failure]");
			goto end;
		}
	}

	pc_event_notification_local_var = OpenAPI_pc_event_notification_create(
		event_local_nonprim,
		acc_type ? acc_typeVariable : 0,
		add_access_info ? add_access_info_local_nonprim : NULL,
		rel_access_info ? rel_access_info_local_nonprim : NULL,
		an_gw_addr ? an_gw_addr_local_nonprim : NULL,
		rat_type ? rat_typeVariable : 0,
		plmn_id ? plmn_id_local_nonprim : NULL,
		sat_backhaul_category ? sat_backhaul_categoryVariable : 0,
		applied_cov ? applied_cov_local_nonprim : NULL,
		supi &&
		!cJSON_IsNull(supi) ? ogs_strdup(supi->valuestring) : NULL,
		gpsi &&
		!cJSON_IsNull(gpsi) ? ogs_strdup(gpsi->valuestring) : NULL,
		ogs_strdup(time_stamp->valuestring),
		pdu_session_info ? pdu_session_info_local_nonprim : NULL,
		rep_services ? rep_services_local_nonprim : NULL,
		deliv_failure ? deliv_failure_local_nonprim : NULL
		);

	return pc_event_notification_local_var;
end:
	if(event_local_nonprim) {
		OpenAPI_pc_event_free(event_local_nonprim);
		event_local_nonprim = NULL;
	}
	if(add_access_info_local_nonprim) {
		OpenAPI_additional_access_info_free(
			add_access_info_local_nonprim);
		add_access_info_local_nonprim = NULL;
	}
	if(rel_access_info_local_nonprim) {
		OpenAPI_additional_access_info_free(
			rel_access_info_local_nonprim);
		rel_access_info_local_nonprim = NULL;
	}
	if(an_gw_addr_local_nonprim) {
		OpenAPI_an_gw_address_free(an_gw_addr_local_nonprim);
		an_gw_addr_local_nonprim = NULL;
	}
	if(plmn_id_local_nonprim) {
		OpenAPI_plmn_id_nid_free(plmn_id_local_nonprim);
		plmn_id_local_nonprim = NULL;
	}
	if(applied_cov_local_nonprim) {
		OpenAPI_service_area_coverage_info_free(
			applied_cov_local_nonprim);
		applied_cov_local_nonprim = NULL;
	}
	if(pdu_session_info_local_nonprim) {
		OpenAPI_pdu_session_information_free(
			pdu_session_info_local_nonprim);
		pdu_session_info_local_nonprim = NULL;
	}
	if(rep_services_local_nonprim) {
		OpenAPI_service_identification_free(rep_services_local_nonprim);
		rep_services_local_nonprim = NULL;
	}
	if(deliv_failure_local_nonprim) {
		OpenAPI_failure_free(deliv_failure_local_nonprim);
		deliv_failure_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_copy(
	OpenAPI_pc_event_notification_t *dst,
	OpenAPI_pc_event_notification_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_pc_event_notification_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_pc_event_notification_convertToJSON() failed");
		return NULL;
	}

	content = cJSON_Print(item);
	cJSON_Delete(item);

	if(!content) {
		ogs_error("cJSON_Print() failed");
		return NULL;
	}

	item = cJSON_Parse(content);
	ogs_free(content);
	if(!item) {
		ogs_error("cJSON_Parse() failed");
		return NULL;
	}

	OpenAPI_pc_event_notification_free(dst);
	dst = OpenAPI_pc_event_notification_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
