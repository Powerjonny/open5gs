#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mapped_location_qo_s_eps.h"

OpenAPI_mapped_location_qo_s_eps_t *OpenAPI_mapped_location_qo_s_eps_create(
	float h_accuracy, bool is_v_accuracy, float v_accuracy) {
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps_local_var =
		ogs_malloc(sizeof(OpenAPI_mapped_location_qo_s_eps_t));
	ogs_assert(mapped_location_qo_s_eps_local_var);

	mapped_location_qo_s_eps_local_var->h_accuracy = h_accuracy;
	mapped_location_qo_s_eps_local_var->is_v_accuracy = is_v_accuracy;
	mapped_location_qo_s_eps_local_var->v_accuracy = v_accuracy;

	return mapped_location_qo_s_eps_local_var;
}

void OpenAPI_mapped_location_qo_s_eps_free(
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == mapped_location_qo_s_eps) {
		return;
	}
	ogs_free(mapped_location_qo_s_eps);
}

cJSON *OpenAPI_mapped_location_qo_s_eps_convertToJSON(
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(mapped_location_qo_s_eps == NULL) {
		ogs_error(
			"OpenAPI_mapped_location_qo_s_eps_convertToJSON() failed [MappedLocationQoSEps]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(cJSON_AddNumberToObject(item, "hAccuracy",
	                           mapped_location_qo_s_eps->h_accuracy) ==
	   NULL)
	{
		ogs_error(
			"OpenAPI_mapped_location_qo_s_eps_convertToJSON() failed [h_accuracy]");
		goto end;
	}

	if(mapped_location_qo_s_eps->is_v_accuracy) {
		if(cJSON_AddNumberToObject(item, "vAccuracy",
		                           mapped_location_qo_s_eps->v_accuracy)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_mapped_location_qo_s_eps_convertToJSON() failed [v_accuracy]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_mapped_location_qo_s_eps_t *
OpenAPI_mapped_location_qo_s_eps_parseFromJSON(
	cJSON *mapped_location_qo_s_epsJSON) {
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *h_accuracy = NULL;
	cJSON *v_accuracy = NULL;
	h_accuracy =
		cJSON_GetObjectItemCaseSensitive(mapped_location_qo_s_epsJSON,
		                                 "hAccuracy");
	if(!h_accuracy) {
		ogs_error(
			"OpenAPI_mapped_location_qo_s_eps_parseFromJSON() failed [h_accuracy]");
		goto end;
	}
	if(!cJSON_IsNumber(h_accuracy)) {
		ogs_error(
			"OpenAPI_mapped_location_qo_s_eps_parseFromJSON() failed [h_accuracy]");
		goto end;
	}

	v_accuracy =
		cJSON_GetObjectItemCaseSensitive(mapped_location_qo_s_epsJSON,
		                                 "vAccuracy");
	if(v_accuracy) {
		if(!cJSON_IsNumber(v_accuracy)) {
			ogs_error(
				"OpenAPI_mapped_location_qo_s_eps_parseFromJSON() failed [v_accuracy]");
			goto end;
		}
	}

	mapped_location_qo_s_eps_local_var =
		OpenAPI_mapped_location_qo_s_eps_create(

			h_accuracy->valuedouble,
			v_accuracy ? true : false,
			v_accuracy ? v_accuracy->valuedouble : 0
			);

	return mapped_location_qo_s_eps_local_var;
end:
	return NULL;
}

OpenAPI_mapped_location_qo_s_eps_t *OpenAPI_mapped_location_qo_s_eps_copy(
	OpenAPI_mapped_location_qo_s_eps_t	*dst,
	OpenAPI_mapped_location_qo_s_eps_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_mapped_location_qo_s_eps_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_mapped_location_qo_s_eps_convertToJSON() failed");
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

	OpenAPI_mapped_location_qo_s_eps_free(dst);
	dst = OpenAPI_mapped_location_qo_s_eps_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
