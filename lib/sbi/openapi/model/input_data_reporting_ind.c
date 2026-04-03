#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "input_data_reporting_ind.h"

OpenAPI_input_data_reporting_ind_t *OpenAPI_input_data_reporting_ind_create() {
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind_local_var =
		ogs_malloc(sizeof(OpenAPI_input_data_reporting_ind_t));
	ogs_assert(input_data_reporting_ind_local_var);


	return input_data_reporting_ind_local_var;
}

void OpenAPI_input_data_reporting_ind_free(
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == input_data_reporting_ind) {
		return;
	}
	ogs_free(input_data_reporting_ind);
}

cJSON *OpenAPI_input_data_reporting_ind_convertToJSON(
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(input_data_reporting_ind == NULL) {
		ogs_error(
			"OpenAPI_input_data_reporting_ind_convertToJSON() failed [InputData_reportingInd]");
		return NULL;
	}

	item = cJSON_CreateObject();
end:
	return item;
}

OpenAPI_input_data_reporting_ind_t *
OpenAPI_input_data_reporting_ind_parseFromJSON(
	cJSON *input_data_reporting_indJSON) {
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	input_data_reporting_ind_local_var =
		OpenAPI_input_data_reporting_ind_create(
			);

	return input_data_reporting_ind_local_var;
end:
	return NULL;
}

OpenAPI_input_data_reporting_ind_t *OpenAPI_input_data_reporting_ind_copy(
	OpenAPI_input_data_reporting_ind_t	*dst,
	OpenAPI_input_data_reporting_ind_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_input_data_reporting_ind_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_input_data_reporting_ind_convertToJSON() failed");
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

	OpenAPI_input_data_reporting_ind_free(dst);
	dst = OpenAPI_input_data_reporting_ind_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
