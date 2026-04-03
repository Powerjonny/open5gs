#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integrity_result.h"

OpenAPI_integrity_result_t *OpenAPI_integrity_result_create(
	OpenAPI_integrity_computing_entity_t *computing_entity,
	OpenAPI_integrity_protection_level_t *protection_level,
	bool is_integrity_req_met_ind, int integrity_req_met_ind,
	bool is_achieved_tir, int achieved_tir) {
	OpenAPI_integrity_result_t *integrity_result_local_var =
		ogs_malloc(sizeof(OpenAPI_integrity_result_t));
	ogs_assert(integrity_result_local_var);

	integrity_result_local_var->computing_entity = computing_entity;
	integrity_result_local_var->protection_level = protection_level;
	integrity_result_local_var->is_integrity_req_met_ind =
		is_integrity_req_met_ind;
	integrity_result_local_var->integrity_req_met_ind =
		integrity_req_met_ind;
	integrity_result_local_var->is_achieved_tir = is_achieved_tir;
	integrity_result_local_var->achieved_tir = achieved_tir;

	return integrity_result_local_var;
}

void OpenAPI_integrity_result_free(
	OpenAPI_integrity_result_t *integrity_result) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == integrity_result) {
		return;
	}
	if(integrity_result->computing_entity) {
		OpenAPI_integrity_computing_entity_free(
			integrity_result->computing_entity);
		integrity_result->computing_entity = NULL;
	}
	if(integrity_result->protection_level) {
		OpenAPI_integrity_protection_level_free(
			integrity_result->protection_level);
		integrity_result->protection_level = NULL;
	}
	ogs_free(integrity_result);
}

cJSON *OpenAPI_integrity_result_convertToJSON(
	OpenAPI_integrity_result_t *integrity_result) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(integrity_result == NULL) {
		ogs_error(
			"OpenAPI_integrity_result_convertToJSON() failed [IntegrityResult]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(integrity_result->computing_entity) {
		cJSON *computing_entity_local_JSON =
			OpenAPI_integrity_computing_entity_convertToJSON(
				integrity_result->computing_entity);
		if(computing_entity_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [computing_entity]");
			goto end;
		}
		cJSON_AddItemToObject(item, "computingEntity",
		                      computing_entity_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [computing_entity]");
			goto end;
		}
	}

	if(integrity_result->protection_level) {
		cJSON *protection_level_local_JSON =
			OpenAPI_integrity_protection_level_convertToJSON(
				integrity_result->protection_level);
		if(protection_level_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [protection_level]");
			goto end;
		}
		cJSON_AddItemToObject(item, "protectionLevel",
		                      protection_level_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [protection_level]");
			goto end;
		}
	}

	if(integrity_result->is_integrity_req_met_ind) {
		if(cJSON_AddBoolToObject(item, "integrityReqMetInd",
		                         integrity_result->integrity_req_met_ind)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [integrity_req_met_ind]");
			goto end;
		}
	}

	if(integrity_result->is_achieved_tir) {
		if(cJSON_AddNumberToObject(item, "achievedTir",
		                           integrity_result->achieved_tir) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_integrity_result_convertToJSON() failed [achieved_tir]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_integrity_result_t *OpenAPI_integrity_result_parseFromJSON(
	cJSON *integrity_resultJSON) {
	OpenAPI_integrity_result_t *integrity_result_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *computing_entity = NULL;
	OpenAPI_integrity_computing_entity_t *computing_entity_local_nonprim =
		NULL;
	cJSON *protection_level = NULL;
	OpenAPI_integrity_protection_level_t *protection_level_local_nonprim =
		NULL;
	cJSON *integrity_req_met_ind = NULL;
	cJSON *achieved_tir = NULL;
	computing_entity =
		cJSON_GetObjectItemCaseSensitive(integrity_resultJSON,
		                                 "computingEntity");
	if(computing_entity) {
		computing_entity_local_nonprim =
			OpenAPI_integrity_computing_entity_parseFromJSON(
				computing_entity);
		if(!computing_entity_local_nonprim) {
			ogs_error(
				"OpenAPI_integrity_computing_entity_parseFromJSON failed [computing_entity]");
			goto end;
		}
	}

	protection_level =
		cJSON_GetObjectItemCaseSensitive(integrity_resultJSON,
		                                 "protectionLevel");
	if(protection_level) {
		protection_level_local_nonprim =
			OpenAPI_integrity_protection_level_parseFromJSON(
				protection_level);
		if(!protection_level_local_nonprim) {
			ogs_error(
				"OpenAPI_integrity_protection_level_parseFromJSON failed [protection_level]");
			goto end;
		}
	}

	integrity_req_met_ind =
		cJSON_GetObjectItemCaseSensitive(integrity_resultJSON,
		                                 "integrityReqMetInd");
	if(integrity_req_met_ind) {
		if(!cJSON_IsBool(integrity_req_met_ind)) {
			ogs_error(
				"OpenAPI_integrity_result_parseFromJSON() failed [integrity_req_met_ind]");
			goto end;
		}
	}

	achieved_tir = cJSON_GetObjectItemCaseSensitive(integrity_resultJSON,
	                                                "achievedTir");
	if(achieved_tir) {
		if(!cJSON_IsNumber(achieved_tir)) {
			ogs_error(
				"OpenAPI_integrity_result_parseFromJSON() failed [achieved_tir]");
			goto end;
		}
	}

	integrity_result_local_var = OpenAPI_integrity_result_create(
		computing_entity ? computing_entity_local_nonprim : NULL,
		protection_level ? protection_level_local_nonprim : NULL,
		integrity_req_met_ind ? true : false,
		integrity_req_met_ind ? integrity_req_met_ind->valueint : 0,
		achieved_tir ? true : false,
		achieved_tir ? achieved_tir->valuedouble : 0
		);

	return integrity_result_local_var;
end:
	if(computing_entity_local_nonprim) {
		OpenAPI_integrity_computing_entity_free(
			computing_entity_local_nonprim);
		computing_entity_local_nonprim = NULL;
	}
	if(protection_level_local_nonprim) {
		OpenAPI_integrity_protection_level_free(
			protection_level_local_nonprim);
		protection_level_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_integrity_result_t *OpenAPI_integrity_result_copy(
	OpenAPI_integrity_result_t *dst, OpenAPI_integrity_result_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_integrity_result_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_integrity_result_convertToJSON() failed");
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

	OpenAPI_integrity_result_free(dst);
	dst = OpenAPI_integrity_result_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
