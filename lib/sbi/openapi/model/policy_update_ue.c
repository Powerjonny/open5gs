#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_update_ue.h"

OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_create(
	char *resource_uri,
	char	    *
	ue_policy,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pol,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pol_a2x,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pro_se_pol,
	bool
	is_triggers_null,
	OpenAPI_list_t *
	triggers,
	bool		is_pras_null,
	OpenAPI_list_t	*pras,
	OpenAPI_policy_status_e
	andsp_del_ind,
	OpenAPI_list_t *deliv_report,
	bool
	is_pdu_sessions_null,
	OpenAPI_list_t *pdu_sessions, bool is_pcf_ue_info_null,
	OpenAPI_pcf_ue_callback_info_t *pcf_ue_info, bool is_match_pdus_null,
	OpenAPI_list_t *match_pdus, char *supp_feat,
	OpenAPI_n2_info_content_t *n2_pc5_rspp_pol) {
	OpenAPI_policy_update_ue_t *policy_update_ue_local_var =
		ogs_malloc(sizeof(OpenAPI_policy_update_ue_t));
	ogs_assert(policy_update_ue_local_var);

	policy_update_ue_local_var->resource_uri = resource_uri;
	policy_update_ue_local_var->ue_policy = ue_policy;
	policy_update_ue_local_var->n2_pc5_pol = n2_pc5_pol;
	policy_update_ue_local_var->n2_pc5_pol_a2x = n2_pc5_pol_a2x;
	policy_update_ue_local_var->n2_pc5_pro_se_pol = n2_pc5_pro_se_pol;
	policy_update_ue_local_var->is_triggers_null = is_triggers_null;
	policy_update_ue_local_var->triggers = triggers;
	policy_update_ue_local_var->is_pras_null = is_pras_null;
	policy_update_ue_local_var->pras = pras;
	policy_update_ue_local_var->andsp_del_ind = andsp_del_ind;
	policy_update_ue_local_var->deliv_report = deliv_report;
	policy_update_ue_local_var->is_pdu_sessions_null = is_pdu_sessions_null;
	policy_update_ue_local_var->pdu_sessions = pdu_sessions;
	policy_update_ue_local_var->is_pcf_ue_info_null = is_pcf_ue_info_null;
	policy_update_ue_local_var->pcf_ue_info = pcf_ue_info;
	policy_update_ue_local_var->is_match_pdus_null = is_match_pdus_null;
	policy_update_ue_local_var->match_pdus = match_pdus;
	policy_update_ue_local_var->supp_feat = supp_feat;
	policy_update_ue_local_var->n2_pc5_rspp_pol = n2_pc5_rspp_pol;

	return policy_update_ue_local_var;
}

void OpenAPI_policy_update_ue_free(
	OpenAPI_policy_update_ue_t *policy_update_ue) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == policy_update_ue) {
		return;
	}
	if(policy_update_ue->resource_uri) {
		ogs_free(policy_update_ue->resource_uri);
		policy_update_ue->resource_uri = NULL;
	}
	if(policy_update_ue->ue_policy) {
		ogs_free(policy_update_ue->ue_policy);
		policy_update_ue->ue_policy = NULL;
	}
	if(policy_update_ue->n2_pc5_pol) {
		OpenAPI_n2_info_content_free(policy_update_ue->n2_pc5_pol);
		policy_update_ue->n2_pc5_pol = NULL;
	}
	if(policy_update_ue->n2_pc5_pol_a2x) {
		OpenAPI_n2_info_content_free(policy_update_ue->n2_pc5_pol_a2x);
		policy_update_ue->n2_pc5_pol_a2x = NULL;
	}
	if(policy_update_ue->n2_pc5_pro_se_pol) {
		OpenAPI_n2_info_content_free(
			policy_update_ue->n2_pc5_pro_se_pol);
		policy_update_ue->n2_pc5_pro_se_pol = NULL;
	}
	if(policy_update_ue->triggers) {
		OpenAPI_list_free(policy_update_ue->triggers);
		policy_update_ue->triggers = NULL;
	}
	if(policy_update_ue->pras) {
		OpenAPI_list_for_each(policy_update_ue->pras, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_rm_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(policy_update_ue->pras);
		policy_update_ue->pras = NULL;
	}
	if(policy_update_ue->deliv_report) {
		OpenAPI_list_for_each(policy_update_ue->deliv_report, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ue_policy_notification_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(policy_update_ue->deliv_report);
		policy_update_ue->deliv_report = NULL;
	}
	if(policy_update_ue->pdu_sessions) {
		OpenAPI_list_for_each(policy_update_ue->pdu_sessions, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(policy_update_ue->pdu_sessions);
		policy_update_ue->pdu_sessions = NULL;
	}
	if(policy_update_ue->pcf_ue_info) {
		OpenAPI_pcf_ue_callback_info_free(
			policy_update_ue->pcf_ue_info);
		policy_update_ue->pcf_ue_info = NULL;
	}
	if(policy_update_ue->match_pdus) {
		OpenAPI_list_for_each(policy_update_ue->match_pdus, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(policy_update_ue->match_pdus);
		policy_update_ue->match_pdus = NULL;
	}
	if(policy_update_ue->supp_feat) {
		ogs_free(policy_update_ue->supp_feat);
		policy_update_ue->supp_feat = NULL;
	}
	if(policy_update_ue->n2_pc5_rspp_pol) {
		OpenAPI_n2_info_content_free(policy_update_ue->n2_pc5_rspp_pol);
		policy_update_ue->n2_pc5_rspp_pol = NULL;
	}
	ogs_free(policy_update_ue);
}

cJSON *OpenAPI_policy_update_ue_convertToJSON(
	OpenAPI_policy_update_ue_t *policy_update_ue) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(policy_update_ue == NULL) {
		ogs_error(
			"OpenAPI_policy_update_ue_convertToJSON() failed [PolicyUpdateUE]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!policy_update_ue->resource_uri) {
		ogs_error(
			"OpenAPI_policy_update_ue_convertToJSON() failed [resource_uri]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "resourceUri",
	                           policy_update_ue->resource_uri) == NULL)
	{
		ogs_error(
			"OpenAPI_policy_update_ue_convertToJSON() failed [resource_uri]");
		goto end;
	}

	if(policy_update_ue->ue_policy) {
		if(cJSON_AddStringToObject(item, "uePolicy",
		                           policy_update_ue->ue_policy) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [ue_policy]");
			goto end;
		}
	}

	if(policy_update_ue->n2_pc5_pol) {
		cJSON *n2_pc5_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_update_ue->n2_pc5_pol);
		if(n2_pc5_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5Pol", n2_pc5_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pol]");
			goto end;
		}
	}

	if(policy_update_ue->n2_pc5_pol_a2x) {
		cJSON *n2_pc5_pol_a2x_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_update_ue->n2_pc5_pol_a2x);
		if(n2_pc5_pol_a2x_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pol_a2x]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5PolA2x",
		                      n2_pc5_pol_a2x_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pol_a2x]");
			goto end;
		}
	}

	if(policy_update_ue->n2_pc5_pro_se_pol) {
		cJSON *n2_pc5_pro_se_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_update_ue->n2_pc5_pro_se_pol);
		if(n2_pc5_pro_se_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pro_se_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5ProSePol",
		                      n2_pc5_pro_se_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_pro_se_pol]");
			goto end;
		}
	}

	if(policy_update_ue->triggers != OpenAPI_request_trigger_ue_NULL) {
		cJSON *triggersList = cJSON_AddArrayToObject(item, "triggers");
		if(triggersList == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [triggers]");
			goto end;
		}
		OpenAPI_list_for_each(policy_update_ue->triggers, node) {
			if(cJSON_AddStringToObject(triggersList, "",
			                           OpenAPI_request_trigger_ue_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_update_ue_convertToJSON() failed [triggers]");
				goto end;
			}
		}
	} else if(policy_update_ue->is_triggers_null) {
		if(cJSON_AddNullToObject(item, "triggers") == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [triggers]");
			goto end;
		}
	}

	if(policy_update_ue->pras) {
		cJSON *pras = cJSON_AddObjectToObject(item, "pras");
		if(pras == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pras]");
			goto end;
		}
		cJSON *localMapObject = pras;
		if(policy_update_ue->pras) {
			OpenAPI_list_for_each(policy_update_ue->pras, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [pras]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [pras]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_presence_info_rm_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	} else if(policy_update_ue->is_pras_null) {
		if(cJSON_AddNullToObject(item, "pras") == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pras]");
			goto end;
		}
	}

	if(policy_update_ue->andsp_del_ind != OpenAPI_policy_status_NULL) {
		if(cJSON_AddStringToObject(item, "andspDelInd",
		                           OpenAPI_policy_status_ToString(
						   policy_update_ue->
						   andsp_del_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [andsp_del_ind]");
			goto end;
		}
	}

	if(policy_update_ue->deliv_report) {
		cJSON *deliv_report = cJSON_AddObjectToObject(item,
		                                              "delivReport");
		if(deliv_report == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [deliv_report]");
			goto end;
		}
		cJSON *localMapObject = deliv_report;
		if(policy_update_ue->deliv_report) {
			OpenAPI_list_for_each(policy_update_ue->deliv_report,
			                      node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [deliv_report]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [deliv_report]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_ue_policy_notification_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_update_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(policy_update_ue->pdu_sessions) {
		cJSON *pdu_sessionsList = cJSON_AddArrayToObject(item,
		                                                 "pduSessions");
		if(pdu_sessionsList == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pdu_sessions]");
			goto end;
		}
		OpenAPI_list_for_each(policy_update_ue->pdu_sessions, node) {
			cJSON *itemLocal =
				OpenAPI_pdu_session_info_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_update_ue_convertToJSON() failed [pdu_sessions]");
				goto end;
			}
			cJSON_AddItemToArray(pdu_sessionsList, itemLocal);
		}
	} else if(policy_update_ue->is_pdu_sessions_null) {
		if(cJSON_AddNullToObject(item, "pduSessions") == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pdu_sessions]");
			goto end;
		}
	}

	if(policy_update_ue->pcf_ue_info) {
		cJSON *pcf_ue_info_local_JSON =
			OpenAPI_pcf_ue_callback_info_convertToJSON(
				policy_update_ue->pcf_ue_info);
		if(pcf_ue_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "pcfUeInfo",
		                      pcf_ue_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
	} else if(policy_update_ue->is_pcf_ue_info_null) {
		if(cJSON_AddNullToObject(item, "pcfUeInfo") == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [pcf_ue_info]");
			goto end;
		}
	}

	if(policy_update_ue->match_pdus) {
		cJSON *match_pdusList = cJSON_AddArrayToObject(item,
		                                               "matchPdus");
		if(match_pdusList == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [match_pdus]");
			goto end;
		}
		OpenAPI_list_for_each(policy_update_ue->match_pdus, node) {
			cJSON *itemLocal =
				OpenAPI_pdu_session_info_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_update_ue_convertToJSON() failed [match_pdus]");
				goto end;
			}
			cJSON_AddItemToArray(match_pdusList, itemLocal);
		}
	} else if(policy_update_ue->is_match_pdus_null) {
		if(cJSON_AddNullToObject(item, "matchPdus") == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [match_pdus]");
			goto end;
		}
	}

	if(policy_update_ue->supp_feat) {
		if(cJSON_AddStringToObject(item, "suppFeat",
		                           policy_update_ue->supp_feat) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [supp_feat]");
			goto end;
		}
	}

	if(policy_update_ue->n2_pc5_rspp_pol) {
		cJSON *n2_pc5_rspp_pol_local_JSON =
			OpenAPI_n2_info_content_convertToJSON(
				policy_update_ue->n2_pc5_rspp_pol);
		if(n2_pc5_rspp_pol_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_rspp_pol]");
			goto end;
		}
		cJSON_AddItemToObject(item, "n2Pc5RsppPol",
		                      n2_pc5_rspp_pol_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_update_ue_convertToJSON() failed [n2_pc5_rspp_pol]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_parseFromJSON(
	cJSON *policy_update_ueJSON) {
	OpenAPI_policy_update_ue_t *policy_update_ue_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *resource_uri = NULL;
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
	cJSON *deliv_report = NULL;
	OpenAPI_list_t *deliv_reportList = NULL;
	cJSON *pdu_sessions = NULL;
	OpenAPI_list_t *pdu_sessionsList = NULL;
	cJSON *pcf_ue_info = NULL;
	OpenAPI_pcf_ue_callback_info_t *pcf_ue_info_local_nonprim = NULL;
	cJSON *match_pdus = NULL;
	OpenAPI_list_t *match_pdusList = NULL;
	cJSON *supp_feat = NULL;
	cJSON *n2_pc5_rspp_pol = NULL;
	OpenAPI_n2_info_content_t *n2_pc5_rspp_pol_local_nonprim = NULL;
	resource_uri = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                                "resourceUri");
	if(!resource_uri) {
		ogs_error(
			"OpenAPI_policy_update_ue_parseFromJSON() failed [resource_uri]");
		goto end;
	}
	if(!cJSON_IsString(resource_uri)) {
		ogs_error(
			"OpenAPI_policy_update_ue_parseFromJSON() failed [resource_uri]");
		goto end;
	}

	ue_policy = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                             "uePolicy");
	if(ue_policy) {
		if(!cJSON_IsString(ue_policy) &&
		   !cJSON_IsNull(ue_policy))
		{
			ogs_error(
				"OpenAPI_policy_update_ue_parseFromJSON() failed [ue_policy]");
			goto end;
		}
	}

	n2_pc5_pol = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
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

	n2_pc5_pol_a2x = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
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
		cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
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

	triggers = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                            "triggers");
	if(triggers) {
		if(!cJSON_IsNull(triggers)) {
			cJSON *triggers_local = NULL;
			if(!cJSON_IsArray(triggers)) {
				ogs_error(
					"OpenAPI_policy_update_ue_parseFromJSON() failed [triggers]");
				goto end;
			}

			triggersList = OpenAPI_list_create();

			cJSON_ArrayForEach(triggers_local, triggers) {
				OpenAPI_request_trigger_ue_e localEnum =
					OpenAPI_request_trigger_ue_NULL;
				if(!cJSON_IsString(triggers_local)) {
					ogs_error(
						"OpenAPI_policy_update_ue_parseFromJSON() failed [triggers]");
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
					"OpenAPI_policy_update_ue_parseFromJSON() failed: Expected triggersList to not be empty (after ignoring unsupported enum values).");
				goto end;
			}
		}
	}

	pras = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON, "pras");
	if(pras) {
		if(!cJSON_IsNull(pras)) {
			cJSON *pras_local_map = NULL;
			if(!cJSON_IsObject(pras) &&
			   !cJSON_IsNull(pras))
			{
				ogs_error(
					"OpenAPI_policy_update_ue_parseFromJSON() failed [pras]");
				goto end;
			}
			if(cJSON_IsObject(pras)) {
				prasList = OpenAPI_list_create();
				OpenAPI_map_t *localMapKeyPair = NULL;
				cJSON_ArrayForEach(pras_local_map, pras) {
					cJSON *localMapObject = pras_local_map;
					if(cJSON_IsObject(localMapObject)) {
						localMapKeyPair =
							OpenAPI_map_create(
								ogs_strdup(
									localMapObject
									->string),
								OpenAPI_presence_info_rm_parseFromJSON
								(
									localMapObject));
					} else if(cJSON_IsNull(
							  localMapObject))
					{
						localMapKeyPair =
							OpenAPI_map_create(
								ogs_strdup(
									localMapObject
									->string),
								NULL);
					} else {
						ogs_error(
							"OpenAPI_policy_update_ue_parseFromJSON() failed [inner]");
						goto end;
					}
					OpenAPI_list_add(prasList,
					                 localMapKeyPair);
				}
			}
		}
	}

	andsp_del_ind = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                                 "andspDelInd");
	if(andsp_del_ind) {
		if(!cJSON_IsString(andsp_del_ind)) {
			ogs_error(
				"OpenAPI_policy_update_ue_parseFromJSON() failed [andsp_del_ind]");
			goto end;
		}
		andsp_del_indVariable =
			OpenAPI_policy_status_FromString(
				andsp_del_ind->valuestring);
	}

	deliv_report = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                                "delivReport");
	if(deliv_report) {
		cJSON *deliv_report_local_map = NULL;
		if(!cJSON_IsObject(deliv_report) &&
		   !cJSON_IsNull(deliv_report))
		{
			ogs_error(
				"OpenAPI_policy_update_ue_parseFromJSON() failed [deliv_report]");
			goto end;
		}
		if(cJSON_IsObject(deliv_report)) {
			deliv_reportList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(deliv_report_local_map,
			                   deliv_report) {
				cJSON *localMapObject = deliv_report_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_ue_policy_notification_parseFromJSON
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
						"OpenAPI_policy_update_ue_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(deliv_reportList,
				                 localMapKeyPair);
			}
		}
	}

	pdu_sessions = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                                "pduSessions");
	if(pdu_sessions) {
		if(!cJSON_IsNull(pdu_sessions)) {
			cJSON *pdu_sessions_local = NULL;
			if(!cJSON_IsArray(pdu_sessions)) {
				ogs_error(
					"OpenAPI_policy_update_ue_parseFromJSON() failed [pdu_sessions]");
				goto end;
			}

			pdu_sessionsList = OpenAPI_list_create();

			cJSON_ArrayForEach(pdu_sessions_local, pdu_sessions) {
				if(!cJSON_IsObject(pdu_sessions_local)) {
					ogs_error(
						"OpenAPI_policy_update_ue_parseFromJSON() failed [pdu_sessions]");
					goto end;
				}
				OpenAPI_pdu_session_info_t *pdu_sessionsItem =
					OpenAPI_pdu_session_info_parseFromJSON(
						pdu_sessions_local);
				if(!pdu_sessionsItem) {
					ogs_error("No pdu_sessionsItem");
					goto end;
				}
				OpenAPI_list_add(pdu_sessionsList,
				                 pdu_sessionsItem);
			}
		}
	}

	pcf_ue_info = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
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

	match_pdus = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                              "matchPdus");
	if(match_pdus) {
		if(!cJSON_IsNull(match_pdus)) {
			cJSON *match_pdus_local = NULL;
			if(!cJSON_IsArray(match_pdus)) {
				ogs_error(
					"OpenAPI_policy_update_ue_parseFromJSON() failed [match_pdus]");
				goto end;
			}

			match_pdusList = OpenAPI_list_create();

			cJSON_ArrayForEach(match_pdus_local, match_pdus) {
				if(!cJSON_IsObject(match_pdus_local)) {
					ogs_error(
						"OpenAPI_policy_update_ue_parseFromJSON() failed [match_pdus]");
					goto end;
				}
				OpenAPI_pdu_session_info_t *match_pdusItem =
					OpenAPI_pdu_session_info_parseFromJSON(
						match_pdus_local);
				if(!match_pdusItem) {
					ogs_error("No match_pdusItem");
					goto end;
				}
				OpenAPI_list_add(match_pdusList,
				                 match_pdusItem);
			}
		}
	}

	supp_feat = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
	                                             "suppFeat");
	if(supp_feat) {
		if(!cJSON_IsString(supp_feat) &&
		   !cJSON_IsNull(supp_feat))
		{
			ogs_error(
				"OpenAPI_policy_update_ue_parseFromJSON() failed [supp_feat]");
			goto end;
		}
	}

	n2_pc5_rspp_pol = cJSON_GetObjectItemCaseSensitive(policy_update_ueJSON,
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

	policy_update_ue_local_var = OpenAPI_policy_update_ue_create(
		ogs_strdup(resource_uri->valuestring),
		ue_policy &&
		!cJSON_IsNull(ue_policy) ? ogs_strdup(ue_policy->valuestring) :
		NULL,
		n2_pc5_pol ? n2_pc5_pol_local_nonprim : NULL,
		n2_pc5_pol_a2x ? n2_pc5_pol_a2x_local_nonprim : NULL,
		n2_pc5_pro_se_pol ? n2_pc5_pro_se_pol_local_nonprim : NULL,
		triggers &&
		cJSON_IsNull(triggers) ? true : false,
		triggers ? triggersList : NULL,
		pras &&
		cJSON_IsNull(pras) ? true : false,
		pras ? prasList : NULL,
		andsp_del_ind ? andsp_del_indVariable : 0,
		deliv_report ? deliv_reportList : NULL,
		pdu_sessions &&
		cJSON_IsNull(pdu_sessions) ? true : false,
		pdu_sessions ? pdu_sessionsList : NULL,
		pcf_ue_info &&
		cJSON_IsNull(pcf_ue_info) ? true : false,
		pcf_ue_info ? pcf_ue_info_local_nonprim : NULL,
		match_pdus &&
		cJSON_IsNull(match_pdus) ? true : false,
		match_pdus ? match_pdusList : NULL,
		supp_feat &&
		!cJSON_IsNull(supp_feat) ? ogs_strdup(supp_feat->valuestring) :
		NULL,
		n2_pc5_rspp_pol ? n2_pc5_rspp_pol_local_nonprim : NULL
		);

	return policy_update_ue_local_var;
end:
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
			OpenAPI_presence_info_rm_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(prasList);
		prasList = NULL;
	}
	if(deliv_reportList) {
		OpenAPI_list_for_each(deliv_reportList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ue_policy_notification_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(deliv_reportList);
		deliv_reportList = NULL;
	}
	if(pdu_sessionsList) {
		OpenAPI_list_for_each(pdu_sessionsList, node) {
			OpenAPI_pdu_session_info_free(node->data);
		}
		OpenAPI_list_free(pdu_sessionsList);
		pdu_sessionsList = NULL;
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
	if(n2_pc5_rspp_pol_local_nonprim) {
		OpenAPI_n2_info_content_free(n2_pc5_rspp_pol_local_nonprim);
		n2_pc5_rspp_pol_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_copy(
	OpenAPI_policy_update_ue_t *dst, OpenAPI_policy_update_ue_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_policy_update_ue_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_policy_update_ue_convertToJSON() failed");
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

	OpenAPI_policy_update_ue_free(dst);
	dst = OpenAPI_policy_update_ue_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
