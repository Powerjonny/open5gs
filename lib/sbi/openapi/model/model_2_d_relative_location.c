#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "model_2_d_relative_location.h"

OpenAPI_model_2_d_relative_location_t *
OpenAPI_model_2_d_relative_location_create(bool is_semi_minor, float semi_minor,
                                           bool is_semi_major, float semi_major,
                                           bool is_orientation_angle,
                                           int orientation_angle) {
	OpenAPI_model_2_d_relative_location_t *
	        model_2_d_relative_location_local_var =
		ogs_malloc(sizeof(OpenAPI_model_2_d_relative_location_t));
	ogs_assert(model_2_d_relative_location_local_var);

	model_2_d_relative_location_local_var->is_semi_minor = is_semi_minor;
	model_2_d_relative_location_local_var->semi_minor = semi_minor;
	model_2_d_relative_location_local_var->is_semi_major = is_semi_major;
	model_2_d_relative_location_local_var->semi_major = semi_major;
	model_2_d_relative_location_local_var->is_orientation_angle =
		is_orientation_angle;
	model_2_d_relative_location_local_var->orientation_angle =
		orientation_angle;

	return model_2_d_relative_location_local_var;
}

void OpenAPI_model_2_d_relative_location_free(
	OpenAPI_model_2_d_relative_location_t *model_2_d_relative_location) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == model_2_d_relative_location) {
		return;
	}
	ogs_free(model_2_d_relative_location);
}

cJSON *OpenAPI_model_2_d_relative_location_convertToJSON(
	OpenAPI_model_2_d_relative_location_t *model_2_d_relative_location) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(model_2_d_relative_location == NULL) {
		ogs_error(
			"OpenAPI_model_2_d_relative_location_convertToJSON() failed [2DRelativeLocation]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(model_2_d_relative_location->is_semi_minor) {
		if(cJSON_AddNumberToObject(item, "semiMinor",
		                           model_2_d_relative_location->
		                           semi_minor) == NULL)
		{
			ogs_error(
				"OpenAPI_model_2_d_relative_location_convertToJSON() failed [semi_minor]");
			goto end;
		}
	}

	if(model_2_d_relative_location->is_semi_major) {
		if(cJSON_AddNumberToObject(item, "semiMajor",
		                           model_2_d_relative_location->
		                           semi_major) == NULL)
		{
			ogs_error(
				"OpenAPI_model_2_d_relative_location_convertToJSON() failed [semi_major]");
			goto end;
		}
	}

	if(model_2_d_relative_location->is_orientation_angle) {
		if(cJSON_AddNumberToObject(item, "orientationAngle",
		                           model_2_d_relative_location->
		                           orientation_angle) == NULL)
		{
			ogs_error(
				"OpenAPI_model_2_d_relative_location_convertToJSON() failed [orientation_angle]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_model_2_d_relative_location_t *
OpenAPI_model_2_d_relative_location_parseFromJSON(
	cJSON *model_2_d_relative_locationJSON) {
	OpenAPI_model_2_d_relative_location_t *
	        model_2_d_relative_location_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *semi_minor = NULL;
	cJSON *semi_major = NULL;
	cJSON *orientation_angle = NULL;
	semi_minor =
		cJSON_GetObjectItemCaseSensitive(
			model_2_d_relative_locationJSON, "semiMinor");
	if(semi_minor) {
		if(!cJSON_IsNumber(semi_minor)) {
			ogs_error(
				"OpenAPI_model_2_d_relative_location_parseFromJSON() failed [semi_minor]");
			goto end;
		}
	}

	semi_major =
		cJSON_GetObjectItemCaseSensitive(
			model_2_d_relative_locationJSON, "semiMajor");
	if(semi_major) {
		if(!cJSON_IsNumber(semi_major)) {
			ogs_error(
				"OpenAPI_model_2_d_relative_location_parseFromJSON() failed [semi_major]");
			goto end;
		}
	}

	orientation_angle =
		cJSON_GetObjectItemCaseSensitive(
			model_2_d_relative_locationJSON, "orientationAngle");
	if(orientation_angle) {
		if(!cJSON_IsNumber(orientation_angle)) {
			ogs_error(
				"OpenAPI_model_2_d_relative_location_parseFromJSON() failed [orientation_angle]");
			goto end;
		}
	}

	model_2_d_relative_location_local_var =
		OpenAPI_model_2_d_relative_location_create(
			semi_minor ? true : false,
			semi_minor ? semi_minor->valuedouble : 0,
			semi_major ? true : false,
			semi_major ? semi_major->valuedouble : 0,
			orientation_angle ? true : false,
			orientation_angle ? orientation_angle->valuedouble : 0
			);

	return model_2_d_relative_location_local_var;
end:
	return NULL;
}

OpenAPI_model_2_d_relative_location_t *OpenAPI_model_2_d_relative_location_copy(
	OpenAPI_model_2_d_relative_location_t	*dst,
	OpenAPI_model_2_d_relative_location_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_model_2_d_relative_location_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_model_2_d_relative_location_convertToJSON() failed");
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

	OpenAPI_model_2_d_relative_location_free(dst);
	dst = OpenAPI_model_2_d_relative_location_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
