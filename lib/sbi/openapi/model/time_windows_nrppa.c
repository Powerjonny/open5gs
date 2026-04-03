#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "time_windows_nrppa.h"

OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_create(
	char *measurement_list, char *srs_list) {
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa_local_var =
		ogs_malloc(sizeof(OpenAPI_time_windows_nrppa_t));
	ogs_assert(time_windows_nrppa_local_var);

	time_windows_nrppa_local_var->measurement_list = measurement_list;
	time_windows_nrppa_local_var->srs_list = srs_list;

	return time_windows_nrppa_local_var;
}

void OpenAPI_time_windows_nrppa_free(
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == time_windows_nrppa) {
		return;
	}
	if(time_windows_nrppa->measurement_list) {
		ogs_free(time_windows_nrppa->measurement_list);
		time_windows_nrppa->measurement_list = NULL;
	}
	if(time_windows_nrppa->srs_list) {
		ogs_free(time_windows_nrppa->srs_list);
		time_windows_nrppa->srs_list = NULL;
	}
	ogs_free(time_windows_nrppa);
}

cJSON *OpenAPI_time_windows_nrppa_convertToJSON(
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(time_windows_nrppa == NULL) {
		ogs_error(
			"OpenAPI_time_windows_nrppa_convertToJSON() failed [TimeWindowsNrppa]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(time_windows_nrppa->measurement_list) {
		if(cJSON_AddStringToObject(item, "measurementList",
		                           time_windows_nrppa->measurement_list)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_time_windows_nrppa_convertToJSON() failed [measurement_list]");
			goto end;
		}
	}

	if(time_windows_nrppa->srs_list) {
		if(cJSON_AddStringToObject(item, "srsList",
		                           time_windows_nrppa->srs_list) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_time_windows_nrppa_convertToJSON() failed [srs_list]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_parseFromJSON(
	cJSON *time_windows_nrppaJSON) {
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *measurement_list = NULL;
	cJSON *srs_list = NULL;
	measurement_list =
		cJSON_GetObjectItemCaseSensitive(time_windows_nrppaJSON,
		                                 "measurementList");
	if(measurement_list) {
		if(!cJSON_IsString(measurement_list) &&
		   !cJSON_IsNull(measurement_list))
		{
			ogs_error(
				"OpenAPI_time_windows_nrppa_parseFromJSON() failed [measurement_list]");
			goto end;
		}
	}

	srs_list = cJSON_GetObjectItemCaseSensitive(time_windows_nrppaJSON,
	                                            "srsList");
	if(srs_list) {
		if(!cJSON_IsString(srs_list) &&
		   !cJSON_IsNull(srs_list))
		{
			ogs_error(
				"OpenAPI_time_windows_nrppa_parseFromJSON() failed [srs_list]");
			goto end;
		}
	}

	time_windows_nrppa_local_var = OpenAPI_time_windows_nrppa_create(
		measurement_list &&
		!cJSON_IsNull(measurement_list) ?
		ogs_strdup(measurement_list->valuestring) : NULL,
		srs_list &&
		!cJSON_IsNull(srs_list) ? ogs_strdup(srs_list->valuestring) :
		NULL
		);

	return time_windows_nrppa_local_var;
end:
	return NULL;
}

OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_copy(
	OpenAPI_time_windows_nrppa_t *dst, OpenAPI_time_windows_nrppa_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_time_windows_nrppa_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_time_windows_nrppa_convertToJSON() failed");
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

	OpenAPI_time_windows_nrppa_free(dst);
	dst = OpenAPI_time_windows_nrppa_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
