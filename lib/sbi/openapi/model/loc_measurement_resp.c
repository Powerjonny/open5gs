#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "loc_measurement_resp.h"

OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_create(
	OpenAPI_list_t *loc_measurements) {
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp_local_var =
		ogs_malloc(sizeof(OpenAPI_loc_measurement_resp_t));
	ogs_assert(loc_measurement_resp_local_var);

	loc_measurement_resp_local_var->loc_measurements = loc_measurements;

	return loc_measurement_resp_local_var;
}

void OpenAPI_loc_measurement_resp_free(
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == loc_measurement_resp) {
		return;
	}
	if(loc_measurement_resp->loc_measurements) {
		OpenAPI_list_for_each(loc_measurement_resp->loc_measurements,
		                      node) {
			OpenAPI_loc_measurements_free(node->data);
		}
		OpenAPI_list_free(loc_measurement_resp->loc_measurements);
		loc_measurement_resp->loc_measurements = NULL;
	}
	ogs_free(loc_measurement_resp);
}

cJSON *OpenAPI_loc_measurement_resp_convertToJSON(
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(loc_measurement_resp == NULL) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_convertToJSON() failed [LocMeasurementResp]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!loc_measurement_resp->loc_measurements) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_convertToJSON() failed [loc_measurements]");
		return NULL;
	}
	cJSON *loc_measurementsList = cJSON_AddArrayToObject(item,
	                                                     "locMeasurements");
	if(loc_measurementsList == NULL) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_convertToJSON() failed [loc_measurements]");
		goto end;
	}
	OpenAPI_list_for_each(loc_measurement_resp->loc_measurements, node) {
		cJSON *itemLocal =
			OpenAPI_loc_measurements_convertToJSON(node->data);
		if(itemLocal == NULL) {
			ogs_error(
				"OpenAPI_loc_measurement_resp_convertToJSON() failed [loc_measurements]");
			goto end;
		}
		cJSON_AddItemToArray(loc_measurementsList, itemLocal);
	}

end:
	return item;
}

OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_parseFromJSON(
	cJSON *loc_measurement_respJSON) {
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *loc_measurements = NULL;
	OpenAPI_list_t *loc_measurementsList = NULL;
	loc_measurements =
		cJSON_GetObjectItemCaseSensitive(loc_measurement_respJSON,
		                                 "locMeasurements");
	if(!loc_measurements) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_parseFromJSON() failed [loc_measurements]");
		goto end;
	}
	cJSON *loc_measurements_local = NULL;
	if(!cJSON_IsArray(loc_measurements)) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_parseFromJSON() failed [loc_measurements]");
		goto end;
	}

	loc_measurementsList = OpenAPI_list_create();

	cJSON_ArrayForEach(loc_measurements_local, loc_measurements) {
		if(!cJSON_IsObject(loc_measurements_local)) {
			ogs_error(
				"OpenAPI_loc_measurement_resp_parseFromJSON() failed [loc_measurements]");
			goto end;
		}
		OpenAPI_loc_measurements_t *loc_measurementsItem =
			OpenAPI_loc_measurements_parseFromJSON(
				loc_measurements_local);
		if(!loc_measurementsItem) {
			ogs_error("No loc_measurementsItem");
			goto end;
		}
		OpenAPI_list_add(loc_measurementsList, loc_measurementsItem);
	}

	loc_measurement_resp_local_var = OpenAPI_loc_measurement_resp_create(
		loc_measurementsList
		);

	return loc_measurement_resp_local_var;
end:
	if(loc_measurementsList) {
		OpenAPI_list_for_each(loc_measurementsList, node) {
			OpenAPI_loc_measurements_free(node->data);
		}
		OpenAPI_list_free(loc_measurementsList);
		loc_measurementsList = NULL;
	}
	return NULL;
}

OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_copy(
	OpenAPI_loc_measurement_resp_t	*dst,
	OpenAPI_loc_measurement_resp_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_loc_measurement_resp_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_loc_measurement_resp_convertToJSON() failed");
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

	OpenAPI_loc_measurement_resp_free(dst);
	dst = OpenAPI_loc_measurement_resp_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
