#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "up_config.h"

OpenAPI_up_config_t *OpenAPI_up_config_create(char *up_notify_call_back_uri,
                                              char *notif_correlation_id,
                                              char *supi, char *gpsi,
                                              bool is_amf_reallocation_ind,
                                              int amf_reallocation_ind,
                                              OpenAPI_lcs_up_connection_ind_e
                                              lcs_up_connection_ind,
                                              char *target_lmfid,
                                              OpenAPI_list_t *ue_up_pos_caps) {
	OpenAPI_up_config_t *up_config_local_var =
		ogs_malloc(sizeof(OpenAPI_up_config_t));
	ogs_assert(up_config_local_var);

	up_config_local_var->up_notify_call_back_uri = up_notify_call_back_uri;
	up_config_local_var->notif_correlation_id = notif_correlation_id;
	up_config_local_var->supi = supi;
	up_config_local_var->gpsi = gpsi;
	up_config_local_var->is_amf_reallocation_ind = is_amf_reallocation_ind;
	up_config_local_var->amf_reallocation_ind = amf_reallocation_ind;
	up_config_local_var->lcs_up_connection_ind = lcs_up_connection_ind;
	up_config_local_var->target_lmfid = target_lmfid;
	up_config_local_var->ue_up_pos_caps = ue_up_pos_caps;

	return up_config_local_var;
}

void OpenAPI_up_config_free(OpenAPI_up_config_t *up_config) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == up_config) {
		return;
	}
	if(up_config->up_notify_call_back_uri) {
		ogs_free(up_config->up_notify_call_back_uri);
		up_config->up_notify_call_back_uri = NULL;
	}
	if(up_config->notif_correlation_id) {
		ogs_free(up_config->notif_correlation_id);
		up_config->notif_correlation_id = NULL;
	}
	if(up_config->supi) {
		ogs_free(up_config->supi);
		up_config->supi = NULL;
	}
	if(up_config->gpsi) {
		ogs_free(up_config->gpsi);
		up_config->gpsi = NULL;
	}
	if(up_config->target_lmfid) {
		ogs_free(up_config->target_lmfid);
		up_config->target_lmfid = NULL;
	}
	if(up_config->ue_up_pos_caps) {
		OpenAPI_list_free(up_config->ue_up_pos_caps);
		up_config->ue_up_pos_caps = NULL;
	}
	ogs_free(up_config);
}

cJSON *OpenAPI_up_config_convertToJSON(OpenAPI_up_config_t *up_config) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(up_config == NULL) {
		ogs_error(
			"OpenAPI_up_config_convertToJSON() failed [UpConfig]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!up_config->up_notify_call_back_uri) {
		ogs_error(
			"OpenAPI_up_config_convertToJSON() failed [up_notify_call_back_uri]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "upNotifyCallBackUri",
	                           up_config->up_notify_call_back_uri) == NULL)
	{
		ogs_error(
			"OpenAPI_up_config_convertToJSON() failed [up_notify_call_back_uri]");
		goto end;
	}

	if(!up_config->notif_correlation_id) {
		ogs_error(
			"OpenAPI_up_config_convertToJSON() failed [notif_correlation_id]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "notifCorrelationId",
	                           up_config->notif_correlation_id) == NULL)
	{
		ogs_error(
			"OpenAPI_up_config_convertToJSON() failed [notif_correlation_id]");
		goto end;
	}

	if(up_config->supi) {
		if(cJSON_AddStringToObject(item, "supi",
		                           up_config->supi) == NULL)
		{
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [supi]");
			goto end;
		}
	}

	if(up_config->gpsi) {
		if(cJSON_AddStringToObject(item, "gpsi",
		                           up_config->gpsi) == NULL)
		{
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [gpsi]");
			goto end;
		}
	}

	if(up_config->is_amf_reallocation_ind) {
		if(cJSON_AddBoolToObject(item, "amfReallocationInd",
		                         up_config->amf_reallocation_ind) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [amf_reallocation_ind]");
			goto end;
		}
	}

	if(up_config->lcs_up_connection_ind !=
	   OpenAPI_lcs_up_connection_ind_NULL)
	{
		if(cJSON_AddStringToObject(item, "lcsUpConnectionInd",
		                           OpenAPI_lcs_up_connection_ind_ToString
		                                   (up_config->
		                                   lcs_up_connection_ind)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [lcs_up_connection_ind]");
			goto end;
		}
	}

	if(up_config->target_lmfid) {
		if(cJSON_AddStringToObject(item, "targetLMFId",
		                           up_config->target_lmfid) == NULL)
		{
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [target_lmfid]");
			goto end;
		}
	}

	if(up_config->ue_up_pos_caps !=
	   OpenAPI_ue_up_positioning_capabilities_NULL)
	{
		cJSON *ue_up_pos_capsList = cJSON_AddArrayToObject(item,
		                                                   "ueUpPosCaps");
		if(ue_up_pos_capsList == NULL) {
			ogs_error(
				"OpenAPI_up_config_convertToJSON() failed [ue_up_pos_caps]");
			goto end;
		}
		OpenAPI_list_for_each(up_config->ue_up_pos_caps, node) {
			if(cJSON_AddStringToObject(ue_up_pos_capsList, "",
			                           OpenAPI_ue_up_positioning_capabilities_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_up_config_convertToJSON() failed [ue_up_pos_caps]");
				goto end;
			}
		}
	}

end:
	return item;
}

OpenAPI_up_config_t *OpenAPI_up_config_parseFromJSON(cJSON *up_configJSON) {
	OpenAPI_up_config_t *up_config_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *up_notify_call_back_uri = NULL;
	cJSON *notif_correlation_id = NULL;
	cJSON *supi = NULL;
	cJSON *gpsi = NULL;
	cJSON *amf_reallocation_ind = NULL;
	cJSON *lcs_up_connection_ind = NULL;
	OpenAPI_lcs_up_connection_ind_e lcs_up_connection_indVariable = 0;
	cJSON *target_lmfid = NULL;
	cJSON *ue_up_pos_caps = NULL;
	OpenAPI_list_t *ue_up_pos_capsList = NULL;
	up_notify_call_back_uri =
		cJSON_GetObjectItemCaseSensitive(up_configJSON,
		                                 "upNotifyCallBackUri");
	if(!up_notify_call_back_uri) {
		ogs_error(
			"OpenAPI_up_config_parseFromJSON() failed [up_notify_call_back_uri]");
		goto end;
	}
	if(!cJSON_IsString(up_notify_call_back_uri)) {
		ogs_error(
			"OpenAPI_up_config_parseFromJSON() failed [up_notify_call_back_uri]");
		goto end;
	}

	notif_correlation_id = cJSON_GetObjectItemCaseSensitive(up_configJSON,
	                                                        "notifCorrelationId");
	if(!notif_correlation_id) {
		ogs_error(
			"OpenAPI_up_config_parseFromJSON() failed [notif_correlation_id]");
		goto end;
	}
	if(!cJSON_IsString(notif_correlation_id)) {
		ogs_error(
			"OpenAPI_up_config_parseFromJSON() failed [notif_correlation_id]");
		goto end;
	}

	supi = cJSON_GetObjectItemCaseSensitive(up_configJSON, "supi");
	if(supi) {
		if(!cJSON_IsString(supi) &&
		   !cJSON_IsNull(supi))
		{
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [supi]");
			goto end;
		}
	}

	gpsi = cJSON_GetObjectItemCaseSensitive(up_configJSON, "gpsi");
	if(gpsi) {
		if(!cJSON_IsString(gpsi) &&
		   !cJSON_IsNull(gpsi))
		{
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [gpsi]");
			goto end;
		}
	}

	amf_reallocation_ind = cJSON_GetObjectItemCaseSensitive(up_configJSON,
	                                                        "amfReallocationInd");
	if(amf_reallocation_ind) {
		if(!cJSON_IsBool(amf_reallocation_ind)) {
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [amf_reallocation_ind]");
			goto end;
		}
	}

	lcs_up_connection_ind = cJSON_GetObjectItemCaseSensitive(up_configJSON,
	                                                         "lcsUpConnectionInd");
	if(lcs_up_connection_ind) {
		if(!cJSON_IsString(lcs_up_connection_ind)) {
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [lcs_up_connection_ind]");
			goto end;
		}
		lcs_up_connection_indVariable =
			OpenAPI_lcs_up_connection_ind_FromString(
				lcs_up_connection_ind->valuestring);
	}

	target_lmfid = cJSON_GetObjectItemCaseSensitive(up_configJSON,
	                                                "targetLMFId");
	if(target_lmfid) {
		if(!cJSON_IsString(target_lmfid) &&
		   !cJSON_IsNull(target_lmfid))
		{
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [target_lmfid]");
			goto end;
		}
	}

	ue_up_pos_caps = cJSON_GetObjectItemCaseSensitive(up_configJSON,
	                                                  "ueUpPosCaps");
	if(ue_up_pos_caps) {
		cJSON *ue_up_pos_caps_local = NULL;
		if(!cJSON_IsArray(ue_up_pos_caps)) {
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed [ue_up_pos_caps]");
			goto end;
		}

		ue_up_pos_capsList = OpenAPI_list_create();

		cJSON_ArrayForEach(ue_up_pos_caps_local, ue_up_pos_caps) {
			OpenAPI_ue_up_positioning_capabilities_e localEnum =
				OpenAPI_ue_up_positioning_capabilities_NULL;
			if(!cJSON_IsString(ue_up_pos_caps_local)) {
				ogs_error(
					"OpenAPI_up_config_parseFromJSON() failed [ue_up_pos_caps]");
				goto end;
			}
			localEnum =
				OpenAPI_ue_up_positioning_capabilities_FromString
				        (ue_up_pos_caps_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"ue_up_pos_caps\" is not supported. Ignoring it ...",
					ue_up_pos_caps_local->valuestring);
			} else {
				OpenAPI_list_add(ue_up_pos_capsList,
				                 (void *) localEnum);
			}
		}
		if(ue_up_pos_capsList->count == 0) {
			ogs_error(
				"OpenAPI_up_config_parseFromJSON() failed: Expected ue_up_pos_capsList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	up_config_local_var = OpenAPI_up_config_create(
		ogs_strdup(up_notify_call_back_uri->valuestring),
		ogs_strdup(notif_correlation_id->valuestring),
		supi &&
		!cJSON_IsNull(supi) ? ogs_strdup(supi->valuestring) : NULL,
		gpsi &&
		!cJSON_IsNull(gpsi) ? ogs_strdup(gpsi->valuestring) : NULL,
		amf_reallocation_ind ? true : false,
		amf_reallocation_ind ? amf_reallocation_ind->valueint : 0,
		lcs_up_connection_ind ? lcs_up_connection_indVariable : 0,
		target_lmfid &&
		!cJSON_IsNull(target_lmfid) ?
		ogs_strdup(target_lmfid->valuestring) : NULL,
		ue_up_pos_caps ? ue_up_pos_capsList : NULL
		);

	return up_config_local_var;
end:
	if(ue_up_pos_capsList) {
		OpenAPI_list_free(ue_up_pos_capsList);
		ue_up_pos_capsList = NULL;
	}
	return NULL;
}

OpenAPI_up_config_t *OpenAPI_up_config_copy(OpenAPI_up_config_t *dst,
                                            OpenAPI_up_config_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_up_config_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_up_config_convertToJSON() failed");
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

	OpenAPI_up_config_free(dst);
	dst = OpenAPI_up_config_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
