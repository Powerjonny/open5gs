#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "reporting_ind.h"

OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_create() {
	OpenAPI_reporting_ind_t *reporting_ind_local_var =
		ogs_malloc(sizeof(OpenAPI_reporting_ind_t));
	ogs_assert(reporting_ind_local_var);


	return reporting_ind_local_var;
}

void OpenAPI_reporting_ind_free(OpenAPI_reporting_ind_t *reporting_ind) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == reporting_ind) {
		return;
	}
	ogs_free(reporting_ind);
}

cJSON *OpenAPI_reporting_ind_convertToJSON(
	OpenAPI_reporting_ind_t *reporting_ind) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(reporting_ind == NULL) {
		ogs_error(
			"OpenAPI_reporting_ind_convertToJSON() failed [ReportingInd]");
		return NULL;
	}

	item = cJSON_CreateObject();
end:
	return item;
}

OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_parseFromJSON(
	cJSON *reporting_indJSON) {
	OpenAPI_reporting_ind_t *reporting_ind_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	reporting_ind_local_var = OpenAPI_reporting_ind_create(
		);

	return reporting_ind_local_var;
end:
	return NULL;
}

OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_copy(
	OpenAPI_reporting_ind_t *dst, OpenAPI_reporting_ind_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_reporting_ind_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_reporting_ind_convertToJSON() failed");
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

	OpenAPI_reporting_ind_free(dst);
	dst = OpenAPI_reporting_ind_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
