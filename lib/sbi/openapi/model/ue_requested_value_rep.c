#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ue_requested_value_rep.h"

OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_create(
	OpenAPI_user_location_t *user_loc, OpenAPI_list_t *pra_statuses,
	OpenAPI_plmn_id_nid_t *plmn_id, OpenAPI_cm_state_t *connect_state,
	OpenAPI_list_t *conf_snssais,
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category,
	OpenAPI_list_t *ursp_enf_rep, OpenAPI_list_t *lbo_roam_info,
	OpenAPI_list_t *access_types, OpenAPI_list_t *rat_types) {
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep_local_var =
		ogs_malloc(sizeof(OpenAPI_ue_requested_value_rep_t));
	ogs_assert(ue_requested_value_rep_local_var);

	ue_requested_value_rep_local_var->user_loc = user_loc;
	ue_requested_value_rep_local_var->pra_statuses = pra_statuses;
	ue_requested_value_rep_local_var->plmn_id = plmn_id;
	ue_requested_value_rep_local_var->connect_state = connect_state;
	ue_requested_value_rep_local_var->conf_snssais = conf_snssais;
	ue_requested_value_rep_local_var->sat_backhaul_category =
		sat_backhaul_category;
	ue_requested_value_rep_local_var->ursp_enf_rep = ursp_enf_rep;
	ue_requested_value_rep_local_var->lbo_roam_info = lbo_roam_info;
	ue_requested_value_rep_local_var->access_types = access_types;
	ue_requested_value_rep_local_var->rat_types = rat_types;

	return ue_requested_value_rep_local_var;
}

void OpenAPI_ue_requested_value_rep_free(
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ue_requested_value_rep) {
		return;
	}
	if(ue_requested_value_rep->user_loc) {
		OpenAPI_user_location_free(ue_requested_value_rep->user_loc);
		ue_requested_value_rep->user_loc = NULL;
	}
	if(ue_requested_value_rep->pra_statuses) {
		OpenAPI_list_for_each(ue_requested_value_rep->pra_statuses,
		                      node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(ue_requested_value_rep->pra_statuses);
		ue_requested_value_rep->pra_statuses = NULL;
	}
	if(ue_requested_value_rep->plmn_id) {
		OpenAPI_plmn_id_nid_free(ue_requested_value_rep->plmn_id);
		ue_requested_value_rep->plmn_id = NULL;
	}
	if(ue_requested_value_rep->connect_state) {
		OpenAPI_cm_state_free(ue_requested_value_rep->connect_state);
		ue_requested_value_rep->connect_state = NULL;
	}
	if(ue_requested_value_rep->conf_snssais) {
		OpenAPI_list_for_each(ue_requested_value_rep->conf_snssais,
		                      node) {
			OpenAPI_configured_snssai_free(node->data);
		}
		OpenAPI_list_free(ue_requested_value_rep->conf_snssais);
		ue_requested_value_rep->conf_snssais = NULL;
	}
	if(ue_requested_value_rep->ursp_enf_rep) {
		OpenAPI_list_for_each(ue_requested_value_rep->ursp_enf_rep,
		                      node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ursp_enforcement_pdu_session_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(ue_requested_value_rep->ursp_enf_rep);
		ue_requested_value_rep->ursp_enf_rep = NULL;
	}
	if(ue_requested_value_rep->lbo_roam_info) {
		OpenAPI_list_for_each(ue_requested_value_rep->lbo_roam_info,
		                      node) {
			OpenAPI_lbo_roaming_information_free(node->data);
		}
		OpenAPI_list_free(ue_requested_value_rep->lbo_roam_info);
		ue_requested_value_rep->lbo_roam_info = NULL;
	}
	if(ue_requested_value_rep->access_types) {
		OpenAPI_list_free(ue_requested_value_rep->access_types);
		ue_requested_value_rep->access_types = NULL;
	}
	if(ue_requested_value_rep->rat_types) {
		OpenAPI_list_free(ue_requested_value_rep->rat_types);
		ue_requested_value_rep->rat_types = NULL;
	}
	ogs_free(ue_requested_value_rep);
}

cJSON *OpenAPI_ue_requested_value_rep_convertToJSON(
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ue_requested_value_rep == NULL) {
		ogs_error(
			"OpenAPI_ue_requested_value_rep_convertToJSON() failed [UeRequestedValueRep]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(ue_requested_value_rep->user_loc) {
		cJSON *user_loc_local_JSON =
			OpenAPI_user_location_convertToJSON(
				ue_requested_value_rep->user_loc);
		if(user_loc_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [user_loc]");
			goto end;
		}
		cJSON_AddItemToObject(item, "userLoc", user_loc_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [user_loc]");
			goto end;
		}
	}

	if(ue_requested_value_rep->pra_statuses) {
		cJSON *pra_statuses = cJSON_AddObjectToObject(item,
		                                              "praStatuses");
		if(pra_statuses == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [pra_statuses]");
			goto end;
		}
		cJSON *localMapObject = pra_statuses;
		if(ue_requested_value_rep->pra_statuses) {
			OpenAPI_list_for_each(
				ue_requested_value_rep->pra_statuses, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [pra_statuses]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [pra_statuses]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_presence_info_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(ue_requested_value_rep->plmn_id) {
		cJSON *plmn_id_local_JSON =
			OpenAPI_plmn_id_nid_convertToJSON(
				ue_requested_value_rep->plmn_id);
		if(plmn_id_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [plmn_id]");
			goto end;
		}
		cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [plmn_id]");
			goto end;
		}
	}

	if(ue_requested_value_rep->connect_state) {
		cJSON *connect_state_local_JSON =
			OpenAPI_cm_state_convertToJSON(
				ue_requested_value_rep->connect_state);
		if(connect_state_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [connect_state]");
			goto end;
		}
		cJSON_AddItemToObject(item, "connectState",
		                      connect_state_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [connect_state]");
			goto end;
		}
	}

	if(ue_requested_value_rep->conf_snssais) {
		cJSON *conf_snssaisList = cJSON_AddArrayToObject(item,
		                                                 "confSnssais");
		if(conf_snssaisList == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [conf_snssais]");
			goto end;
		}
		OpenAPI_list_for_each(ue_requested_value_rep->conf_snssais,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_configured_snssai_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_convertToJSON() failed [conf_snssais]");
				goto end;
			}
			cJSON_AddItemToArray(conf_snssaisList, itemLocal);
		}
	}

	if(ue_requested_value_rep->sat_backhaul_category !=
	   OpenAPI_satellite_backhaul_category_NULL)
	{
		if(cJSON_AddStringToObject(item, "satBackhaulCategory",
		                           OpenAPI_satellite_backhaul_category_ToString
		                                   (ue_requested_value_rep->
		                                   sat_backhaul_category)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [sat_backhaul_category]");
			goto end;
		}
	}

	if(ue_requested_value_rep->ursp_enf_rep) {
		cJSON *ursp_enf_rep = cJSON_AddObjectToObject(item,
		                                              "urspEnfRep");
		if(ursp_enf_rep == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [ursp_enf_rep]");
			goto end;
		}
		cJSON *localMapObject = ursp_enf_rep;
		if(ue_requested_value_rep->ursp_enf_rep) {
			OpenAPI_list_for_each(
				ue_requested_value_rep->ursp_enf_rep, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [ursp_enf_rep]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [ursp_enf_rep]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_ursp_enforcement_pdu_session_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(ue_requested_value_rep->lbo_roam_info) {
		cJSON *lbo_roam_infoList = cJSON_AddArrayToObject(item,
		                                                  "lboRoamInfo");
		if(lbo_roam_infoList == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [lbo_roam_info]");
			goto end;
		}
		OpenAPI_list_for_each(ue_requested_value_rep->lbo_roam_info,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_lbo_roaming_information_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_convertToJSON() failed [lbo_roam_info]");
				goto end;
			}
			cJSON_AddItemToArray(lbo_roam_infoList, itemLocal);
		}
	}

	if(ue_requested_value_rep->access_types != OpenAPI_access_type_NULL) {
		cJSON *access_typesList = cJSON_AddArrayToObject(item,
		                                                 "accessTypes");
		if(access_typesList == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [access_types]");
			goto end;
		}
		OpenAPI_list_for_each(ue_requested_value_rep->access_types,
		                      node) {
			if(cJSON_AddStringToObject(access_typesList, "",
			                           OpenAPI_access_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_ue_requested_value_rep_convertToJSON() failed [access_types]");
				goto end;
			}
		}
	}

	if(ue_requested_value_rep->rat_types != OpenAPI_rat_type_NULL) {
		cJSON *rat_typesList = cJSON_AddArrayToObject(item, "ratTypes");
		if(rat_typesList == NULL) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_convertToJSON() failed [rat_types]");
			goto end;
		}
		OpenAPI_list_for_each(ue_requested_value_rep->rat_types, node) {
			if(cJSON_AddStringToObject(rat_typesList, "",
			                           OpenAPI_rat_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_ue_requested_value_rep_convertToJSON() failed [rat_types]");
				goto end;
			}
		}
	}

end:
	return item;
}

OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_parseFromJSON(
	cJSON *ue_requested_value_repJSON) {
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *user_loc = NULL;
	OpenAPI_user_location_t *user_loc_local_nonprim = NULL;
	cJSON *pra_statuses = NULL;
	OpenAPI_list_t *pra_statusesList = NULL;
	cJSON *plmn_id = NULL;
	OpenAPI_plmn_id_nid_t *plmn_id_local_nonprim = NULL;
	cJSON *connect_state = NULL;
	OpenAPI_cm_state_t *connect_state_local_nonprim = NULL;
	cJSON *conf_snssais = NULL;
	OpenAPI_list_t *conf_snssaisList = NULL;
	cJSON *sat_backhaul_category = NULL;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_categoryVariable = 0;
	cJSON *ursp_enf_rep = NULL;
	OpenAPI_list_t *ursp_enf_repList = NULL;
	cJSON *lbo_roam_info = NULL;
	OpenAPI_list_t *lbo_roam_infoList = NULL;
	cJSON *access_types = NULL;
	OpenAPI_list_t *access_typesList = NULL;
	cJSON *rat_types = NULL;
	OpenAPI_list_t *rat_typesList = NULL;
	user_loc = cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
	                                            "userLoc");
	if(user_loc) {
		user_loc_local_nonprim =
			OpenAPI_user_location_parseFromJSON(user_loc);
		if(!user_loc_local_nonprim) {
			ogs_error(
				"OpenAPI_user_location_parseFromJSON failed [user_loc]");
			goto end;
		}
	}

	pra_statuses =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "praStatuses");
	if(pra_statuses) {
		cJSON *pra_statuses_local_map = NULL;
		if(!cJSON_IsObject(pra_statuses) &&
		   !cJSON_IsNull(pra_statuses))
		{
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [pra_statuses]");
			goto end;
		}
		if(cJSON_IsObject(pra_statuses)) {
			pra_statusesList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(pra_statuses_local_map,
			                   pra_statuses) {
				cJSON *localMapObject = pra_statuses_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_presence_info_parseFromJSON
						        (localMapObject));
				} else if(cJSON_IsNull(localMapObject)) {
					localMapKeyPair =
						OpenAPI_map_create(ogs_strdup(
									   localMapObject
									   ->
									   string),
						                   NULL);
				} else {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(pra_statusesList,
				                 localMapKeyPair);
			}
		}
	}

	plmn_id = cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
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

	connect_state =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "connectState");
	if(connect_state) {
		connect_state_local_nonprim =
			OpenAPI_cm_state_parseFromJSON(connect_state);
		if(!connect_state_local_nonprim) {
			ogs_error(
				"OpenAPI_cm_state_parseFromJSON failed [connect_state]");
			goto end;
		}
	}

	conf_snssais =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "confSnssais");
	if(conf_snssais) {
		cJSON *conf_snssais_local = NULL;
		if(!cJSON_IsArray(conf_snssais)) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [conf_snssais]");
			goto end;
		}

		conf_snssaisList = OpenAPI_list_create();

		cJSON_ArrayForEach(conf_snssais_local, conf_snssais) {
			if(!cJSON_IsObject(conf_snssais_local)) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [conf_snssais]");
				goto end;
			}
			OpenAPI_configured_snssai_t *conf_snssaisItem =
				OpenAPI_configured_snssai_parseFromJSON(
					conf_snssais_local);
			if(!conf_snssaisItem) {
				ogs_error("No conf_snssaisItem");
				goto end;
			}
			OpenAPI_list_add(conf_snssaisList, conf_snssaisItem);
		}
	}

	sat_backhaul_category =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "satBackhaulCategory");
	if(sat_backhaul_category) {
		if(!cJSON_IsString(sat_backhaul_category)) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [sat_backhaul_category]");
			goto end;
		}
		sat_backhaul_categoryVariable =
			OpenAPI_satellite_backhaul_category_FromString(
				sat_backhaul_category->valuestring);
	}

	ursp_enf_rep =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "urspEnfRep");
	if(ursp_enf_rep) {
		cJSON *ursp_enf_rep_local_map = NULL;
		if(!cJSON_IsObject(ursp_enf_rep) &&
		   !cJSON_IsNull(ursp_enf_rep))
		{
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [ursp_enf_rep]");
			goto end;
		}
		if(cJSON_IsObject(ursp_enf_rep)) {
			ursp_enf_repList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(ursp_enf_rep_local_map,
			                   ursp_enf_rep) {
				cJSON *localMapObject = ursp_enf_rep_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_ursp_enforcement_pdu_session_parseFromJSON
						        (localMapObject));
				} else if(cJSON_IsNull(localMapObject)) {
					localMapKeyPair =
						OpenAPI_map_create(ogs_strdup(
									   localMapObject
									   ->
									   string),
						                   NULL);
				} else {
					ogs_error(
						"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(ursp_enf_repList,
				                 localMapKeyPair);
			}
		}
	}

	lbo_roam_info =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "lboRoamInfo");
	if(lbo_roam_info) {
		cJSON *lbo_roam_info_local = NULL;
		if(!cJSON_IsArray(lbo_roam_info)) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [lbo_roam_info]");
			goto end;
		}

		lbo_roam_infoList = OpenAPI_list_create();

		cJSON_ArrayForEach(lbo_roam_info_local, lbo_roam_info) {
			if(!cJSON_IsObject(lbo_roam_info_local)) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [lbo_roam_info]");
				goto end;
			}
			OpenAPI_lbo_roaming_information_t *lbo_roam_infoItem =
				OpenAPI_lbo_roaming_information_parseFromJSON(
					lbo_roam_info_local);
			if(!lbo_roam_infoItem) {
				ogs_error("No lbo_roam_infoItem");
				goto end;
			}
			OpenAPI_list_add(lbo_roam_infoList, lbo_roam_infoItem);
		}
	}

	access_types =
		cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
		                                 "accessTypes");
	if(access_types) {
		cJSON *access_types_local = NULL;
		if(!cJSON_IsArray(access_types)) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [access_types]");
			goto end;
		}

		access_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(access_types_local, access_types) {
			OpenAPI_access_type_e localEnum =
				OpenAPI_access_type_NULL;
			if(!cJSON_IsString(access_types_local)) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [access_types]");
				goto end;
			}
			localEnum =
				OpenAPI_access_type_FromString(
					access_types_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"access_types\" is not supported. Ignoring it ...",
					access_types_local->valuestring);
			} else {
				OpenAPI_list_add(access_typesList,
				                 (void *) localEnum);
			}
		}
		if(access_typesList->count == 0) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed: Expected access_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	rat_types = cJSON_GetObjectItemCaseSensitive(ue_requested_value_repJSON,
	                                             "ratTypes");
	if(rat_types) {
		cJSON *rat_types_local = NULL;
		if(!cJSON_IsArray(rat_types)) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [rat_types]");
			goto end;
		}

		rat_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(rat_types_local, rat_types) {
			OpenAPI_rat_type_e localEnum = OpenAPI_rat_type_NULL;
			if(!cJSON_IsString(rat_types_local)) {
				ogs_error(
					"OpenAPI_ue_requested_value_rep_parseFromJSON() failed [rat_types]");
				goto end;
			}
			localEnum =
				OpenAPI_rat_type_FromString(
					rat_types_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"rat_types\" is not supported. Ignoring it ...",
					rat_types_local->valuestring);
			} else {
				OpenAPI_list_add(rat_typesList,
				                 (void *) localEnum);
			}
		}
		if(rat_typesList->count == 0) {
			ogs_error(
				"OpenAPI_ue_requested_value_rep_parseFromJSON() failed: Expected rat_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	ue_requested_value_rep_local_var =
		OpenAPI_ue_requested_value_rep_create(
			user_loc ? user_loc_local_nonprim : NULL,
			pra_statuses ? pra_statusesList : NULL,
			plmn_id ? plmn_id_local_nonprim : NULL,
			connect_state ? connect_state_local_nonprim : NULL,
			conf_snssais ? conf_snssaisList : NULL,
			sat_backhaul_category ? sat_backhaul_categoryVariable :
			0,
			ursp_enf_rep ? ursp_enf_repList : NULL,
			lbo_roam_info ? lbo_roam_infoList : NULL,
			access_types ? access_typesList : NULL,
			rat_types ? rat_typesList : NULL
			);

	return ue_requested_value_rep_local_var;
end:
	if(user_loc_local_nonprim) {
		OpenAPI_user_location_free(user_loc_local_nonprim);
		user_loc_local_nonprim = NULL;
	}
	if(pra_statusesList) {
		OpenAPI_list_for_each(pra_statusesList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(pra_statusesList);
		pra_statusesList = NULL;
	}
	if(plmn_id_local_nonprim) {
		OpenAPI_plmn_id_nid_free(plmn_id_local_nonprim);
		plmn_id_local_nonprim = NULL;
	}
	if(connect_state_local_nonprim) {
		OpenAPI_cm_state_free(connect_state_local_nonprim);
		connect_state_local_nonprim = NULL;
	}
	if(conf_snssaisList) {
		OpenAPI_list_for_each(conf_snssaisList, node) {
			OpenAPI_configured_snssai_free(node->data);
		}
		OpenAPI_list_free(conf_snssaisList);
		conf_snssaisList = NULL;
	}
	if(ursp_enf_repList) {
		OpenAPI_list_for_each(ursp_enf_repList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ursp_enforcement_pdu_session_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(ursp_enf_repList);
		ursp_enf_repList = NULL;
	}
	if(lbo_roam_infoList) {
		OpenAPI_list_for_each(lbo_roam_infoList, node) {
			OpenAPI_lbo_roaming_information_free(node->data);
		}
		OpenAPI_list_free(lbo_roam_infoList);
		lbo_roam_infoList = NULL;
	}
	if(access_typesList) {
		OpenAPI_list_free(access_typesList);
		access_typesList = NULL;
	}
	if(rat_typesList) {
		OpenAPI_list_free(rat_typesList);
		rat_typesList = NULL;
	}
	return NULL;
}

OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_copy(
	OpenAPI_ue_requested_value_rep_t	*dst,
	OpenAPI_ue_requested_value_rep_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ue_requested_value_rep_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_ue_requested_value_rep_convertToJSON() failed");
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

	OpenAPI_ue_requested_value_rep_free(dst);
	dst = OpenAPI_ue_requested_value_rep_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
