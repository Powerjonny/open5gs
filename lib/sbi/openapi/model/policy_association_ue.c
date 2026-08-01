#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_association_ue.h"

OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_create(
	OpenAPI_policy_association_request_ue_t *request, char *ue_policy,
	OpenAPI_n2_info_content_t *n2_pc5_pol,
	OpenAPI_n2_info_content_t *n2_pc5_pol_a2x,
	OpenAPI_n2_info_content_t *n2_pc5_pro_se_pol, OpenAPI_list_t *triggers,
	OpenAPI_list_t *pras, OpenAPI_policy_status_e andsp_del_ind,
	bool is_andsp_ind, int andsp_ind, OpenAPI_list_t *pdu_sessions,
	OpenAPI_charging_information_t *chf_info, char *chf_group_id,
	char *supp_feat, OpenAPI_n2_info_content_t *n2_pc5_rspp_pol,
	bool is_pcf_ue_info_null, OpenAPI_pcf_ue_callback_info_t *pcf_ue_info,
	OpenAPI_list_t *match_pdus) {
	OpenAPI_policy_association_ue_t *policy_association_ue_local_var =
		ogs_malloc(sizeof(OpenAPI_policy_association_ue_t));
	ogs_assert(policy_association_ue_local_var);

	policy_association_ue_local_var->request = request;
	policy_association_ue_local_var->ue_policy = ue_policy;
	policy_association_ue_local_var->n2_pc5_pol = n2_pc5_pol;
	policy_association_ue_local_var->n2_pc5_pol_a2x = n2_pc5_pol_a2x;
	policy_association_ue_local_var->n2_pc5_pro_se_pol = n2_pc5_pro_se_pol;
	policy_association_ue_local_var->triggers = triggers;
	policy_association_ue_local_var->pras = pras;
	policy_association_ue_local_var->andsp_del_ind = andsp_del_ind;
	policy_association_ue_local_var->is_andsp_ind = is_andsp_ind;
	policy_association_ue_local_var->andsp_ind = andsp_ind;
	policy_association_ue_local_var->pdu_sessions = pdu_sessions;
	policy_association_ue_local_var->chf_info = chf_info;
	policy_association_ue_local_var->chf_group_id = chf_group_id;
	policy_association_ue_local_var->supp_feat = supp_feat;
	policy_association_ue_local_var->n2_pc5_rspp_pol = n2_pc5_rspp_pol;
	policy_association_ue_local_var->is_pcf_ue_info_null =
		is_pcf_ue_info_null;
	policy_association_ue_local_var->pcf_ue_info = pcf_ue_info;
	policy_association_ue_local_var->match_pdus = match_pdus;

	return policy_association_ue_local_var;
}

void OpenAPI_policy_association_ue_free(
	OpenAPI_policy_association_ue_t *policy_association_ue) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == policy_association_ue) {
		return;
	}
	if(policy_association_ue->request) {
		OpenAPI_policy_association_request_ue_free(
			policy_association_ue->request);
		policy_association_ue->request = NULL;
	}
	if(policy_association_ue->ue_policy) {
		ogs_free(policy_association_ue->ue_policy);
		policy_association_ue->ue_policy = NULL;
	}
	if(policy_association_ue->n2_pc5_pol) {
		OpenAPI_n2_info_content_free(policy_association_ue->n2_pc5_pol);
		policy_association_ue->n2_pc5_pol = NULL;
	}
	if(policy_association_ue->n2_pc5_pol_a2x) {
		OpenAPI_n2_info_content_free(
			policy_association_ue->n2_pc5_pol_a2x);
		policy_association_ue->n2_pc5_pol_a2x = NULL;
	}
	if(policy_association_ue->n2_pc5_pro_se_pol) {
		OpenAPI_n2_info_content_free(
			policy_association_ue->n2_pc5_pro_se_pol);
		policy_association_ue->n2_pc5_pro_se_pol = NULL;
	}
	if(policy_association_ue->triggers) {
		OpenAPI_list_free(policy_association_ue->triggers);
		policy_association_ue->triggers = NULL;
	}
	if(policy_association_ue->pras) {
		OpenAPI_list_for_each(policy_association_ue->pras, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(policy_association_ue->pras);
		policy_association_ue->pras = NULL;
	}
	if(policy_association_ue->pdu_sessions) {
		OpenAPI_list_for_each(policy_association_ue->pdu_sessions,
		                      node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(policy_association_ue->pdu_sessions);
		policy_association_ue->pdu_sessions = NULL;
	}
	if(policy_association_ue->chf_info) {
		OpenAPI_charging_information_free(
			policy_association_ue->chf_info);
		policy_association_ue->chf_info = NULL;
	}
	if(policy_association_ue->chf_group_id) {
		ogs_free(policy_association_ue->chf_group_id);
		policy_association_ue->chf_group_id = NULL;
	}
	if(policy_association_ue->supp_feat) {
		ogs_free(policy_association_ue->supp_feat);
		policy_association_ue->supp_feat = NULL;
	}
	if(policy_association_ue->n2_pc5_rspp_pol) {
		OpenAPI_n2_info_content_free(
			policy_association_ue->n2_pc5_rspp_pol);
		policy_association_ue->n2_pc5_rspp_pol = NULL;
	}
	if(policy_association_ue->pcf_ue_info) {
		OpenAPI_pcf_ue_callback_info_free(
			policy_association_ue->pcf_ue_info);
		policy_association_ue->pcf_ue_info = NULL;
	}
	if(policy_association_ue->match_pdus) {
		OpenAPI_list_for_each(policy_association_ue->match_pdus, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(policy_association_ue->match_pdus);
		policy_association_ue->match_pdus = NULL;
	}
	ogs_free(policy_association_ue);
}

cJSON *OpenAPI_policy_association_ue_convertToJSON(
	OpenAPI_policy_association_ue_t *policy_association_ue) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(policy_association_ue == NULL) {
		ogs_error(
			"OpenAPI_policy_association_ue_convertToJSON() failed [PolicyAssociationUE]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(policy_association_ue->request) {
		cJSON *request_local_JSON =
			OpenAPI_policy_association_request_ue_convertToJSON(
				policy_association_ue->request);
		if(request_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [request]");
			goto end;
		}
		cJSON_AddItemToObject(item, "request", request_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [request]");
			goto end;
		}
	}

	if(policy_association_ue->ue_policy) {
		if(cJSON_AddStringToObject(item, "uePolicy",
		                           policy_association_ue->ue_policy) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [ue_policy]");
			goto end;
		}
	}

	if(policy_association_ue->n2_pc5_pol) {
		cJSON *n2_pc5_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_association_ue->n2_pc5_pol);
		if(n2_pc5_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5Pol", n2_pc5_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pol]");
			goto end;
		}
	}

	if(policy_association_ue->n2_pc5_pol_a2x) {
		cJSON *n2_pc5_pol_a2x_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_association_ue->n2_pc5_pol_a2x);
		if(n2_pc5_pol_a2x_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pol_a2x]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5PolA2x",
		                      n2_pc5_pol_a2x_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pol_a2x]");
			goto end;
		}
	}

	if(policy_association_ue->n2_pc5_pro_se_pol) {
		cJSON *n2_pc5_pro_se_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_association_ue->n2_pc5_pro_se_pol);
		if(n2_pc5_pro_se_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pro_se_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5ProSePol",
		                      n2_pc5_pro_se_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_pro_se_pol]");
			goto end;
		}
	}

	if(policy_association_ue->triggers != OpenAPI_request_trigger_ue_NULL) {
		cJSON *triggersList = cJSON_AddArrayToObject(item, "triggers");
		if(triggersList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [triggers]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_ue->triggers, node) {
			if(cJSON_AddStringToObject(triggersList, "",
			                           OpenAPI_request_trigger_ue_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_ue_convertToJSON() failed [triggers]");
				goto end;
			}
		}
	}

	if(policy_association_ue->pras) {
		cJSON *pras = cJSON_AddObjectToObject(item, "pras");
		if(pras == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [pras]");
			goto end;
		}
		cJSON *localMapObject = pras;
		if(policy_association_ue->pras) {
			OpenAPI_list_for_each(policy_association_ue->pras,
			                      node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_association_ue_convertToJSON() failed [pras]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_association_ue_convertToJSON() failed [pras]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_presence_info_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_association_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(policy_association_ue->andsp_del_ind != OpenAPI_policy_status_NULL) {
		if(cJSON_AddStringToObject(item, "andspDelInd",
		                           OpenAPI_policy_status_ToString(
						   policy_association_ue->
						   andsp_del_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [andsp_del_ind]");
			goto end;
		}
	}

	if(policy_association_ue->is_andsp_ind) {
		if(cJSON_AddBoolToObject(item, "andspInd",
		                         policy_association_ue->andsp_ind) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [andsp_ind]");
			goto end;
		}
	}

	if(policy_association_ue->pdu_sessions) {
		cJSON *pdu_sessionsList = cJSON_AddArrayToObject(item,
		                                                 "pduSessions");
		if(pdu_sessionsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [pdu_sessions]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_ue->pdu_sessions,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_pdu_session_info_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_ue_convertToJSON() failed [pdu_sessions]");
				goto end;
			}
			cJSON_AddItemToArray(pdu_sessionsList, itemLocal);
		}
	}

	if(policy_association_ue->chf_info) {
		cJSON *chf_info_local_JSON =
			OpenAPI_charging_information_convertToJSON(
				policy_association_ue->chf_info);
		if(chf_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [chf_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "chfInfo", chf_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [chf_info]");
			goto end;
		}
	}

	if(policy_association_ue->chf_group_id) {
		if(cJSON_AddStringToObject(item, "chfGroupId",
		                           policy_association_ue->chf_group_id)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [chf_group_id]");
			goto end;
		}
	}

	if(!policy_association_ue->supp_feat) {
		ogs_error(
			"OpenAPI_policy_association_ue_convertToJSON() failed [supp_feat]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "suppFeat",
	                           policy_association_ue->supp_feat) == NULL)
	{
		ogs_error(
			"OpenAPI_policy_association_ue_convertToJSON() failed [supp_feat]");
		goto end;
	}

	if(policy_association_ue->n2_pc5_rspp_pol) {
		cJSON *n2_pc5_rspp_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_association_ue->n2_pc5_rspp_pol);
		if(n2_pc5_rspp_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_rspp_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5RsppPol",
		                      n2_pc5_rspp_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [n2_pc5_rspp_pol]");
			goto end;
		}
	}

	if(policy_association_ue->pcf_ue_info) {
		cJSON *pcf_ue_info_local_JSON =
			OpenAPI_pcf_ue_callback_info_convertToJSON(
				policy_association_ue->pcf_ue_info);
		if(pcf_ue_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "pcfUeInfo",
		                      pcf_ue_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
	} else if(policy_association_ue->is_pcf_ue_info_null) {
		if(cJSON_AddNullToObject(item, "pcfUeInfo") == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
	}

	if(policy_association_ue->match_pdus) {
		cJSON *match_pdusList = cJSON_AddArrayToObject(item,
		                                               "matchPdus");
		if(match_pdusList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_ue_convertToJSON() failed [match_pdus]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_ue->match_pdus, node) {
			cJSON *itemLocal =
				OpenAPI_pdu_session_info_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_ue_convertToJSON() failed [match_pdus]");
				goto end;
			}
			cJSON_AddItemToArray(match_pdusList, itemLocal);
		}
	}

end:
	return item;
}

OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_parseFromJSON(
	cJSON *policy_association_ueJSON) {
	OpenAPI_policy_association_ue_t *policy_association_ue_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *request = NULL;
	OpenAPI_policy_association_request_ue_t *request_local_nonprim = NULL;
	cJSON *ue_policy = NULL;
	cJSON *n2_pc5_pol = NULL;
	OpenAPI_n2_info_content_t *n2_pc5_pol_local_nonprim = NULL;
	cJSON *n2_pc5_pol_a2x = NULL;
	OpenAPI_n2_info_content_t *n2_pc5_pol_a2x_local_nonprim = NULL;
	cJSON *n2_pc5_pro_se_pol = NULL;
	OpenAPI_n2_info_content_t *n2_pc5_pro_se_pol_local_nonprim = NULL;
	cJSON *triggers = NULL;
	OpenAPI_list_t *triggersList = NULL;
	cJSON *pras = NULL;
	OpenAPI_list_t *prasList = NULL;
	cJSON *andsp_del_ind = NULL;
	OpenAPI_policy_status_e andsp_del_indVariable = 0;
	cJSON *andsp_ind = NULL;
	cJSON *pdu_sessions = NULL;
	OpenAPI_list_t *pdu_sessionsList = NULL;
	cJSON *chf_info = NULL;
	OpenAPI_charging_information_t *chf_info_local_nonprim = NULL;
	cJSON *chf_group_id = NULL;
	cJSON *supp_feat = NULL;
	cJSON *n2_pc5_rspp_pol = NULL;
	OpenAPI_n2_info_content_t *n2_pc5_rspp_pol_local_nonprim = NULL;
	cJSON *pcf_ue_info = NULL;
	OpenAPI_pcf_ue_callback_info_t *pcf_ue_info_local_nonprim = NULL;
	cJSON *match_pdus = NULL;
	OpenAPI_list_t *match_pdusList = NULL;
	request = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                           "request");
	if(request) {
		request_local_nonprim =
			OpenAPI_policy_association_request_ue_parseFromJSON(
				request);
		if(!request_local_nonprim) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON failed [request]");
			goto end;
		}
	}

	ue_policy = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                             "uePolicy");
	if(ue_policy) {
		if(!cJSON_IsString(ue_policy) &&
		   !cJSON_IsNull(ue_policy))
		{
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [ue_policy]");
			goto end;
		}
	}

	n2_pc5_pol = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                              "n2Pc5Pol");
	if(n2_pc5_pol) {
		n2_pc5_pol_local_nonprim =
			OpenAPI_n2_info_content_parseFromJSON(n2_pc5_pol);
		if(!n2_pc5_pol_local_nonprim) {
			ogs_error(
				"OpenAPI_n2_info_content_parseFromJSON failed [n2_pc5_pol]");
			goto end;
		}
	}

	n2_pc5_pol_a2x =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "n2Pc5PolA2x");
	if(n2_pc5_pol_a2x) {
		n2_pc5_pol_a2x_local_nonprim =
			OpenAPI_n2_info_content_parseFromJSON(n2_pc5_pol_a2x);
		if(!n2_pc5_pol_a2x_local_nonprim) {
			ogs_error(
				"OpenAPI_n2_info_content_parseFromJSON failed [n2_pc5_pol_a2x]");
			goto end;
		}
	}

	n2_pc5_pro_se_pol =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "n2Pc5ProSePol");
	if(n2_pc5_pro_se_pol) {
		n2_pc5_pro_se_pol_local_nonprim =
			OpenAPI_n2_info_content_parseFromJSON(
				n2_pc5_pro_se_pol);
		if(!n2_pc5_pro_se_pol_local_nonprim) {
			ogs_error(
				"OpenAPI_n2_info_content_parseFromJSON failed [n2_pc5_pro_se_pol]");
			goto end;
		}
	}

	triggers = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                            "triggers");
	if(triggers) {
		cJSON *triggers_local = NULL;
		if(!cJSON_IsArray(triggers)) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [triggers]");
			goto end;
		}

		triggersList = OpenAPI_list_create();

		cJSON_ArrayForEach(triggers_local, triggers) {
			OpenAPI_request_trigger_ue_e localEnum =
				OpenAPI_request_trigger_ue_NULL;
			if(!cJSON_IsString(triggers_local)) {
				ogs_error(
					"OpenAPI_policy_association_ue_parseFromJSON() failed [triggers]");
				goto end;
			}
			localEnum =
				OpenAPI_request_trigger_ue_FromString(
					triggers_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"triggers\" is not supported. Ignoring it ...",
					triggers_local->valuestring);
			} else {
				OpenAPI_list_add(triggersList,
				                 (void *) localEnum);
			}
		}
		if(triggersList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed: Expected triggersList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	pras = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                        "pras");
	if(pras) {
		cJSON *pras_local_map = NULL;
		if(!cJSON_IsObject(pras) &&
		   !cJSON_IsNull(pras))
		{
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [pras]");
			goto end;
		}
		if(cJSON_IsObject(pras)) {
			prasList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(pras_local_map, pras) {
				cJSON *localMapObject = pras_local_map;
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
						"OpenAPI_policy_association_ue_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(prasList, localMapKeyPair);
			}
		}
	}

	andsp_del_ind =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "andspDelInd");
	if(andsp_del_ind) {
		if(!cJSON_IsString(andsp_del_ind)) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [andsp_del_ind]");
			goto end;
		}
		andsp_del_indVariable =
			OpenAPI_policy_status_FromString(
				andsp_del_ind->valuestring);
	}

	andsp_ind = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                             "andspInd");
	if(andsp_ind) {
		if(!cJSON_IsBool(andsp_ind)) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [andsp_ind]");
			goto end;
		}
	}

	pdu_sessions =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "pduSessions");
	if(pdu_sessions) {
		cJSON *pdu_sessions_local = NULL;
		if(!cJSON_IsArray(pdu_sessions)) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [pdu_sessions]");
			goto end;
		}

		pdu_sessionsList = OpenAPI_list_create();

		cJSON_ArrayForEach(pdu_sessions_local, pdu_sessions) {
			if(!cJSON_IsObject(pdu_sessions_local)) {
				ogs_error(
					"OpenAPI_policy_association_ue_parseFromJSON() failed [pdu_sessions]");
				goto end;
			}
			OpenAPI_pdu_session_info_t *pdu_sessionsItem =
				OpenAPI_pdu_session_info_parseFromJSON(
					pdu_sessions_local);
			if(!pdu_sessionsItem) {
				ogs_error("No pdu_sessionsItem");
				goto end;
			}
			OpenAPI_list_add(pdu_sessionsList, pdu_sessionsItem);
		}
	}

	chf_info = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                            "chfInfo");
	if(chf_info) {
		chf_info_local_nonprim =
			OpenAPI_charging_information_parseFromJSON(chf_info);
		if(!chf_info_local_nonprim) {
			ogs_error(
				"OpenAPI_charging_information_parseFromJSON failed [chf_info]");
			goto end;
		}
	}

	chf_group_id =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "chfGroupId");
	if(chf_group_id) {
		if(!cJSON_IsString(chf_group_id) &&
		   !cJSON_IsNull(chf_group_id))
		{
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [chf_group_id]");
			goto end;
		}
	}

	supp_feat = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                             "suppFeat");
	if(!supp_feat) {
		ogs_error(
			"OpenAPI_policy_association_ue_parseFromJSON() failed [supp_feat]");
		goto end;
	}
	if(!cJSON_IsString(supp_feat)) {
		ogs_error(
			"OpenAPI_policy_association_ue_parseFromJSON() failed [supp_feat]");
		goto end;
	}

	n2_pc5_rspp_pol =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "n2Pc5RsppPol");
	if(n2_pc5_rspp_pol) {
		n2_pc5_rspp_pol_local_nonprim =
			OpenAPI_n2_info_content_parseFromJSON(n2_pc5_rspp_pol);
		if(!n2_pc5_rspp_pol_local_nonprim) {
			ogs_error(
				"OpenAPI_n2_info_content_parseFromJSON failed [n2_pc5_rspp_pol]");
			goto end;
		}
	}

	pcf_ue_info =
		cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
		                                 "pcfUeInfo");
	if(pcf_ue_info) {
		if(!cJSON_IsNull(pcf_ue_info)) {
			pcf_ue_info_local_nonprim =
				OpenAPI_pcf_ue_callback_info_parseFromJSON(
					pcf_ue_info);
			if(!pcf_ue_info_local_nonprim) {
				ogs_error(
					"OpenAPI_pcf_ue_callback_info_parseFromJSON failed [pcf_ue_info]");
				goto end;
			}
		}
	}

	match_pdus = cJSON_GetObjectItemCaseSensitive(policy_association_ueJSON,
	                                              "matchPdus");
	if(match_pdus) {
		cJSON *match_pdus_local = NULL;
		if(!cJSON_IsArray(match_pdus)) {
			ogs_error(
				"OpenAPI_policy_association_ue_parseFromJSON() failed [match_pdus]");
			goto end;
		}

		match_pdusList = OpenAPI_list_create();

		cJSON_ArrayForEach(match_pdus_local, match_pdus) {
			if(!cJSON_IsObject(match_pdus_local)) {
				ogs_error(
					"OpenAPI_policy_association_ue_parseFromJSON() failed [match_pdus]");
				goto end;
			}
			OpenAPI_pdu_session_info_t *match_pdusItem =
				OpenAPI_pdu_session_info_parseFromJSON(
					match_pdus_local);
			if(!match_pdusItem) {
				ogs_error("No match_pdusItem");
				goto end;
			}
			OpenAPI_list_add(match_pdusList, match_pdusItem);
		}
	}

	policy_association_ue_local_var = OpenAPI_policy_association_ue_create(
		request ? request_local_nonprim : NULL,
		ue_policy &&
		!cJSON_IsNull(ue_policy) ? ogs_strdup(ue_policy->valuestring) :
		NULL,
		n2_pc5_pol ? n2_pc5_pol_local_nonprim : NULL,
		n2_pc5_pol_a2x ? n2_pc5_pol_a2x_local_nonprim : NULL,
		n2_pc5_pro_se_pol ? n2_pc5_pro_se_pol_local_nonprim : NULL,
		triggers ? triggersList : NULL,
		pras ? prasList : NULL,
		andsp_del_ind ? andsp_del_indVariable : 0,
		andsp_ind ? true : false,
		andsp_ind ? andsp_ind->valueint : 0,
		pdu_sessions ? pdu_sessionsList : NULL,
		chf_info ? chf_info_local_nonprim : NULL,
		chf_group_id &&
		!cJSON_IsNull(chf_group_id) ?
		ogs_strdup(chf_group_id->valuestring) : NULL,
		ogs_strdup(supp_feat->valuestring),
		n2_pc5_rspp_pol ? n2_pc5_rspp_pol_local_nonprim : NULL,
		pcf_ue_info &&
		cJSON_IsNull(pcf_ue_info) ? true : false,
		pcf_ue_info ? pcf_ue_info_local_nonprim : NULL,
		match_pdus ? match_pdusList : NULL
		);

	return policy_association_ue_local_var;
end:
	if(request_local_nonprim) {
		OpenAPI_policy_association_request_ue_free(
			request_local_nonprim);
		request_local_nonprim = NULL;
	}
	if(n2_pc5_pol_local_nonprim) {
		OpenAPI_n2_info_content_free(n2_pc5_pol_local_nonprim);
		n2_pc5_pol_local_nonprim = NULL;
	}
	if(n2_pc5_pol_a2x_local_nonprim) {
		OpenAPI_n2_info_content_free(n2_pc5_pol_a2x_local_nonprim);
		n2_pc5_pol_a2x_local_nonprim = NULL;
	}
	if(n2_pc5_pro_se_pol_local_nonprim) {
		OpenAPI_n2_info_content_free(n2_pc5_pro_se_pol_local_nonprim);
		n2_pc5_pro_se_pol_local_nonprim = NULL;
	}
	if(triggersList) {
		OpenAPI_list_free(triggersList);
		triggersList = NULL;
	}
	if(prasList) {
		OpenAPI_list_for_each(prasList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(prasList);
		prasList = NULL;
	}
	if(pdu_sessionsList) {
		OpenAPI_list_for_each(pdu_sessionsList, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(pdu_sessionsList);
		pdu_sessionsList = NULL;
	}
	if(chf_info_local_nonprim) {
		OpenAPI_charging_information_free(chf_info_local_nonprim);
		chf_info_local_nonprim = NULL;
	}
	if(n2_pc5_rspp_pol_local_nonprim) {
		OpenAPI_n2_info_content_free(n2_pc5_rspp_pol_local_nonprim);
		n2_pc5_rspp_pol_local_nonprim = NULL;
	}
	if(pcf_ue_info_local_nonprim) {
		OpenAPI_pcf_ue_callback_info_free(pcf_ue_info_local_nonprim);
		pcf_ue_info_local_nonprim = NULL;
	}
	if(match_pdusList) {
		OpenAPI_list_for_each(match_pdusList, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(match_pdusList);
		match_pdusList = NULL;
	}
	return NULL;
}

OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_copy(
	OpenAPI_policy_association_ue_t *dst,
	OpenAPI_policy_association_ue_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_policy_association_ue_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_policy_association_ue_convertToJSON() failed");
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

	OpenAPI_policy_association_ue_free(dst);
	dst = OpenAPI_policy_association_ue_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
