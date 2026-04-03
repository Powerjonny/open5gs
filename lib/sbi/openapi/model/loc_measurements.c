#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "loc_measurements.h"

OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_create(char *loc_info) {
	OpenAPI_loc_measurements_t *loc_measurements_local_var =
		ogs_malloc(sizeof(OpenAPI_loc_measurements_t));
	ogs_assert(loc_measurements_local_var);

	loc_measurements_local_var->loc_info = loc_info;

	return loc_measurements_local_var;
}

void OpenAPI_loc_measurements_free(
	OpenAPI_loc_measurements_t *loc_measurements) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == loc_measurements) {
		return;
	}
	if(loc_measurements->loc_info) {
		ogs_free(loc_measurements->loc_info);
		loc_measurements->loc_info = NULL;
	}
	ogs_free(loc_measurements);
}

cJSON *OpenAPI_loc_measurements_convertToJSON(
	OpenAPI_loc_measurements_t *loc_measurements) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(loc_measurements == NULL) {
		ogs_error(
			"OpenAPI_loc_measurements_convertToJSON() failed [LocMeasurements]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(loc_measurements->loc_info) {
		if(cJSON_AddStringToObject(item, "locInfo",
		                           loc_measurements->loc_info) == NULL)
		{
			ogs_error(
				"OpenAPI_loc_measurements_convertToJSON() failed [loc_info]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_parseFromJSON(
	cJSON *loc_measurementsJSON) {
	OpenAPI_loc_measurements_t *loc_measurements_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *loc_info = NULL;
	loc_info = cJSON_GetObjectItemCaseSensitive(loc_measurementsJSON,
	                                            "locInfo");
	if(loc_info) {
		if(!cJSON_IsString(loc_info) &&
		   !cJSON_IsNull(loc_info))
		{
			ogs_error(
				"OpenAPI_loc_measurements_parseFromJSON() failed [loc_info]");
			goto end;
		}
	}

	loc_measurements_local_var = OpenAPI_loc_measurements_create(
		loc_info &&
		!cJSON_IsNull(loc_info) ? ogs_strdup(loc_info->valuestring) :
		NULL
		);

	return loc_measurements_local_var;
end:
	return NULL;
}

OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_copy(
	OpenAPI_loc_measurements_t *dst, OpenAPI_loc_measurements_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_loc_measurements_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_loc_measurements_convertToJSON() failed");
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

	OpenAPI_loc_measurements_free(dst);
	dst = OpenAPI_loc_measurements_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
