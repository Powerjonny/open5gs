#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ursp_enforcement_pdu_session.h"

OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_create(char *ursp_enf_info,
                                            OpenAPI_ssc_mode_e ssc_mode,
                                            char *ue_req_dnn,
                                            OpenAPI_pdu_session_type_e
                                            ue_req_pdu_session_type, char *dnn,
                                            OpenAPI_snssai_t *snssai) {
	OpenAPI_ursp_enforcement_pdu_session_t *
	        ursp_enforcement_pdu_session_local_var =
		ogs_malloc(sizeof(OpenAPI_ursp_enforcement_pdu_session_t));
	ogs_assert(ursp_enforcement_pdu_session_local_var);

	ursp_enforcement_pdu_session_local_var->ursp_enf_info = ursp_enf_info;
	ursp_enforcement_pdu_session_local_var->ssc_mode = ssc_mode;
	ursp_enforcement_pdu_session_local_var->ue_req_dnn = ue_req_dnn;
	ursp_enforcement_pdu_session_local_var->ue_req_pdu_session_type =
		ue_req_pdu_session_type;
	ursp_enforcement_pdu_session_local_var->dnn = dnn;
	ursp_enforcement_pdu_session_local_var->snssai = snssai;

	return ursp_enforcement_pdu_session_local_var;
}

void OpenAPI_ursp_enforcement_pdu_session_free(
	OpenAPI_ursp_enforcement_pdu_session_t *ursp_enforcement_pdu_session) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ursp_enforcement_pdu_session) {
		return;
	}
	if(ursp_enforcement_pdu_session->ursp_enf_info) {
		ogs_free(ursp_enforcement_pdu_session->ursp_enf_info);
		ursp_enforcement_pdu_session->ursp_enf_info = NULL;
	}
	if(ursp_enforcement_pdu_session->ue_req_dnn) {
		ogs_free(ursp_enforcement_pdu_session->ue_req_dnn);
		ursp_enforcement_pdu_session->ue_req_dnn = NULL;
	}
	if(ursp_enforcement_pdu_session->dnn) {
		ogs_free(ursp_enforcement_pdu_session->dnn);
		ursp_enforcement_pdu_session->dnn = NULL;
	}
	if(ursp_enforcement_pdu_session->snssai) {
		OpenAPI_snssai_free(ursp_enforcement_pdu_session->snssai);
		ursp_enforcement_pdu_session->snssai = NULL;
	}
	ogs_free(ursp_enforcement_pdu_session);
}

cJSON *OpenAPI_ursp_enforcement_pdu_session_convertToJSON(
	OpenAPI_ursp_enforcement_pdu_session_t *ursp_enforcement_pdu_session) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ursp_enforcement_pdu_session == NULL) {
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [UrspEnforcementPduSession]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!ursp_enforcement_pdu_session->ursp_enf_info) {
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [ursp_enf_info]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "urspEnfInfo",
	                           ursp_enforcement_pdu_session->ursp_enf_info)
	   == NULL)
	{
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [ursp_enf_info]");
		goto end;
	}

	if(ursp_enforcement_pdu_session->ssc_mode != OpenAPI_ssc_mode_NULL) {
		if(cJSON_AddStringToObject(item, "sscMode",
		                           OpenAPI_ssc_mode_ToString(
						   ursp_enforcement_pdu_session
						   ->ssc_mode)) == NULL)
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [ssc_mode]");
			goto end;
		}
	}

	if(ursp_enforcement_pdu_session->ue_req_dnn) {
		if(cJSON_AddStringToObject(item, "ueReqDnn",
		                           ursp_enforcement_pdu_session->
		                           ue_req_dnn) == NULL)
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [ue_req_dnn]");
			goto end;
		}
	}

	if(ursp_enforcement_pdu_session->ue_req_pdu_session_type !=
	   OpenAPI_pdu_session_type_NULL)
	{
		if(cJSON_AddStringToObject(item, "ueReqPduSessionType",
		                           OpenAPI_pdu_session_type_ToString(
						   ursp_enforcement_pdu_session
						   ->ue_req_pdu_session_type))
		   == NULL)
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [ue_req_pdu_session_type]");
			goto end;
		}
	}

	if(ursp_enforcement_pdu_session->dnn) {
		if(cJSON_AddStringToObject(item, "dnn",
		                           ursp_enforcement_pdu_session->dnn) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [dnn]");
			goto end;
		}
	}

	if(ursp_enforcement_pdu_session->snssai) {
		cJSON *snssai_local_JSON =
			OpenAPI_snssai_convertToJSON(
				ursp_enforcement_pdu_session->snssai);
		if(snssai_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [snssai]");
			goto end;
		}
		cJSON_AddItemToObject(item, "snssai", snssai_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed [snssai]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_parseFromJSON(
	cJSON *ursp_enforcement_pdu_sessionJSON) {
	OpenAPI_ursp_enforcement_pdu_session_t *
	        ursp_enforcement_pdu_session_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *ursp_enf_info = NULL;
	cJSON *ssc_mode = NULL;
	OpenAPI_ssc_mode_e ssc_modeVariable = 0;
	cJSON *ue_req_dnn = NULL;
	cJSON *ue_req_pdu_session_type = NULL;
	OpenAPI_pdu_session_type_e ue_req_pdu_session_typeVariable = 0;
	cJSON *dnn = NULL;
	cJSON *snssai = NULL;
	OpenAPI_snssai_t *snssai_local_nonprim = NULL;
	ursp_enf_info =
		cJSON_GetObjectItemCaseSensitive(
			ursp_enforcement_pdu_sessionJSON, "urspEnfInfo");
	if(!ursp_enf_info) {
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [ursp_enf_info]");
		goto end;
	}
	if(!cJSON_IsString(ursp_enf_info)) {
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [ursp_enf_info]");
		goto end;
	}

	ssc_mode =
		cJSON_GetObjectItemCaseSensitive(
			ursp_enforcement_pdu_sessionJSON, "sscMode");
	if(ssc_mode) {
		if(!cJSON_IsString(ssc_mode)) {
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [ssc_mode]");
			goto end;
		}
		ssc_modeVariable =
			OpenAPI_ssc_mode_FromString(ssc_mode->valuestring);
	}

	ue_req_dnn =
		cJSON_GetObjectItemCaseSensitive(
			ursp_enforcement_pdu_sessionJSON, "ueReqDnn");
	if(ue_req_dnn) {
		if(!cJSON_IsString(ue_req_dnn) &&
		   !cJSON_IsNull(ue_req_dnn))
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [ue_req_dnn]");
			goto end;
		}
	}

	ue_req_pdu_session_type =
		cJSON_GetObjectItemCaseSensitive(
			ursp_enforcement_pdu_sessionJSON,
			"ueReqPduSessionType");
	if(ue_req_pdu_session_type) {
		if(!cJSON_IsString(ue_req_pdu_session_type)) {
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [ue_req_pdu_session_type]");
			goto end;
		}
		ue_req_pdu_session_typeVariable =
			OpenAPI_pdu_session_type_FromString(
				ue_req_pdu_session_type->valuestring);
	}

	dnn = cJSON_GetObjectItemCaseSensitive(ursp_enforcement_pdu_sessionJSON,
	                                       "dnn");
	if(dnn) {
		if(!cJSON_IsString(dnn) &&
		   !cJSON_IsNull(dnn))
		{
			ogs_error(
				"OpenAPI_ursp_enforcement_pdu_session_parseFromJSON() failed [dnn]");
			goto end;
		}
	}

	snssai =
		cJSON_GetObjectItemCaseSensitive(
			ursp_enforcement_pdu_sessionJSON, "snssai");
	if(snssai) {
		snssai_local_nonprim = OpenAPI_snssai_parseFromJSON(snssai);
		if(!snssai_local_nonprim) {
			ogs_error(
				"OpenAPI_snssai_parseFromJSON failed [snssai]");
			goto end;
		}
	}

	ursp_enforcement_pdu_session_local_var =
		OpenAPI_ursp_enforcement_pdu_session_create(
			ogs_strdup(ursp_enf_info->valuestring),
			ssc_mode ? ssc_modeVariable : 0,
			ue_req_dnn &&
			!cJSON_IsNull(ue_req_dnn) ?
			ogs_strdup(ue_req_dnn->valuestring) : NULL,
			ue_req_pdu_session_type ?
			ue_req_pdu_session_typeVariable : 0,
			dnn &&
			!cJSON_IsNull(dnn) ? ogs_strdup(dnn->valuestring) :
			NULL,
			snssai ? snssai_local_nonprim : NULL
			);

	return ursp_enforcement_pdu_session_local_var;
end:
	if(snssai_local_nonprim) {
		OpenAPI_snssai_free(snssai_local_nonprim);
		snssai_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_copy(
	OpenAPI_ursp_enforcement_pdu_session_t	*dst,
	OpenAPI_ursp_enforcement_pdu_session_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ursp_enforcement_pdu_session_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_ursp_enforcement_pdu_session_convertToJSON() failed");
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

	OpenAPI_ursp_enforcement_pdu_session_free(dst);
	dst = OpenAPI_ursp_enforcement_pdu_session_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
