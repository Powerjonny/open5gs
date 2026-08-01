#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lbo_roaming_information.h"

OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_create(
	bool is_lbo_roam_allowed, int lbo_roam_allowed, char *dnn,
	OpenAPI_snssai_t *snssai) {
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information_local_var =
		ogs_malloc(sizeof(OpenAPI_lbo_roaming_information_t));
	ogs_assert(lbo_roaming_information_local_var);

	lbo_roaming_information_local_var->is_lbo_roam_allowed =
		is_lbo_roam_allowed;
	lbo_roaming_information_local_var->lbo_roam_allowed = lbo_roam_allowed;
	lbo_roaming_information_local_var->dnn = dnn;
	lbo_roaming_information_local_var->snssai = snssai;

	return lbo_roaming_information_local_var;
}

void OpenAPI_lbo_roaming_information_free(
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == lbo_roaming_information) {
		return;
	}
	if(lbo_roaming_information->dnn) {
		ogs_free(lbo_roaming_information->dnn);
		lbo_roaming_information->dnn = NULL;
	}
	if(lbo_roaming_information->snssai) {
		OpenAPI_snssai_free(lbo_roaming_information->snssai);
		lbo_roaming_information->snssai = NULL;
	}
	ogs_free(lbo_roaming_information);
}

cJSON *OpenAPI_lbo_roaming_information_convertToJSON(
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(lbo_roaming_information == NULL) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [LboRoamingInformation]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(lbo_roaming_information->is_lbo_roam_allowed) {
		if(cJSON_AddBoolToObject(item, "lboRoamAllowed",
		                         lbo_roaming_information->
		                         lbo_roam_allowed) == NULL)
		{
			ogs_error(
				"OpenAPI_lbo_roaming_information_convertToJSON() failed [lbo_roam_allowed]");
			goto end;
		}
	}

	if(!lbo_roaming_information->dnn) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [dnn]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "dnn",
	                           lbo_roaming_information->dnn) == NULL)
	{
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [dnn]");
		goto end;
	}

	if(!lbo_roaming_information->snssai) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [snssai]");
		return NULL;
	}
	cJSON *snssai_local_JSON =
		OpenAPI_snssai_convertToJSON(lbo_roaming_information->snssai);
	if(snssai_local_JSON == NULL) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [snssai]");
		goto end;
	}
	cJSON_AddItemToObject(item, "snssai", snssai_local_JSON);
	if(item->child == NULL) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed [snssai]");
		goto end;
	}

end:
	return item;
}

OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_parseFromJSON
        (cJSON *lbo_roaming_informationJSON) {
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *lbo_roam_allowed = NULL;
	cJSON *dnn = NULL;
	cJSON *snssai = NULL;
	OpenAPI_snssai_t *snssai_local_nonprim = NULL;
	lbo_roam_allowed =
		cJSON_GetObjectItemCaseSensitive(lbo_roaming_informationJSON,
		                                 "lboRoamAllowed");
	if(lbo_roam_allowed) {
		if(!cJSON_IsBool(lbo_roam_allowed)) {
			ogs_error(
				"OpenAPI_lbo_roaming_information_parseFromJSON() failed [lbo_roam_allowed]");
			goto end;
		}
	}

	dnn = cJSON_GetObjectItemCaseSensitive(lbo_roaming_informationJSON,
	                                       "dnn");
	if(!dnn) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_parseFromJSON() failed [dnn]");
		goto end;
	}
	if(!cJSON_IsString(dnn)) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_parseFromJSON() failed [dnn]");
		goto end;
	}

	snssai = cJSON_GetObjectItemCaseSensitive(lbo_roaming_informationJSON,
	                                          "snssai");
	if(!snssai) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_parseFromJSON() failed [snssai]");
		goto end;
	}
	snssai_local_nonprim = OpenAPI_snssai_parseFromJSON(snssai);
	if(!snssai_local_nonprim) {
		ogs_error("OpenAPI_snssai_parseFromJSON failed [snssai]");
		goto end;
	}

	lbo_roaming_information_local_var =
		OpenAPI_lbo_roaming_information_create(
			lbo_roam_allowed ? true : false,
			lbo_roam_allowed ? lbo_roam_allowed->valueint : 0,
			ogs_strdup(dnn->valuestring),
			snssai_local_nonprim
			);

	return lbo_roaming_information_local_var;
end:
	if(snssai_local_nonprim) {
		OpenAPI_snssai_free(snssai_local_nonprim);
		snssai_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_copy(
	OpenAPI_lbo_roaming_information_t	*dst,
	OpenAPI_lbo_roaming_information_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_lbo_roaming_information_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_lbo_roaming_information_convertToJSON() failed");
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

	OpenAPI_lbo_roaming_information_free(dst);
	dst = OpenAPI_lbo_roaming_information_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
