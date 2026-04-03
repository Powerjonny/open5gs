#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_limit.h"

OpenAPI_alert_limit_t *OpenAPI_alert_limit_create(
	int horizontal_protection_level, bool is_vertical_protection_level,
	int vertical_protection_level) {
	OpenAPI_alert_limit_t *alert_limit_local_var =
		ogs_malloc(sizeof(OpenAPI_alert_limit_t));
	ogs_assert(alert_limit_local_var);

	alert_limit_local_var->horizontal_protection_level =
		horizontal_protection_level;
	alert_limit_local_var->is_vertical_protection_level =
		is_vertical_protection_level;
	alert_limit_local_var->vertical_protection_level =
		vertical_protection_level;

	return alert_limit_local_var;
}

void OpenAPI_alert_limit_free(OpenAPI_alert_limit_t *alert_limit) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == alert_limit) {
		return;
	}
	ogs_free(alert_limit);
}

cJSON *OpenAPI_alert_limit_convertToJSON(OpenAPI_alert_limit_t *alert_limit) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(alert_limit == NULL) {
		ogs_error(
			"OpenAPI_alert_limit_convertToJSON() failed [AlertLimit]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(cJSON_AddNumberToObject(item, "horizontalProtectionLevel",
	                           alert_limit->horizontal_protection_level) ==
	   NULL)
	{
		ogs_error(
			"OpenAPI_alert_limit_convertToJSON() failed [horizontal_protection_level]");
		goto end;
	}

	if(alert_limit->is_vertical_protection_level) {
		if(cJSON_AddNumberToObject(item, "verticalProtectionLevel",
		                           alert_limit->
		                           vertical_protection_level) == NULL)
		{
			ogs_error(
				"OpenAPI_alert_limit_convertToJSON() failed [vertical_protection_level]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_alert_limit_t *OpenAPI_alert_limit_parseFromJSON(
	cJSON *alert_limitJSON) {
	OpenAPI_alert_limit_t *alert_limit_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *horizontal_protection_level = NULL;
	cJSON *vertical_protection_level = NULL;
	horizontal_protection_level =
		cJSON_GetObjectItemCaseSensitive(alert_limitJSON,
		                                 "horizontalProtectionLevel");
	if(!horizontal_protection_level) {
		ogs_error(
			"OpenAPI_alert_limit_parseFromJSON() failed [horizontal_protection_level]");
		goto end;
	}
	if(!cJSON_IsNumber(horizontal_protection_level)) {
		ogs_error(
			"OpenAPI_alert_limit_parseFromJSON() failed [horizontal_protection_level]");
		goto end;
	}

	vertical_protection_level =
		cJSON_GetObjectItemCaseSensitive(alert_limitJSON,
		                                 "verticalProtectionLevel");
	if(vertical_protection_level) {
		if(!cJSON_IsNumber(vertical_protection_level)) {
			ogs_error(
				"OpenAPI_alert_limit_parseFromJSON() failed [vertical_protection_level]");
			goto end;
		}
	}

	alert_limit_local_var = OpenAPI_alert_limit_create(

		horizontal_protection_level->valuedouble,
		vertical_protection_level ? true : false,
		vertical_protection_level ?
		vertical_protection_level->valuedouble : 0
		);

	return alert_limit_local_var;
end:
	return NULL;
}

OpenAPI_alert_limit_t *OpenAPI_alert_limit_copy(OpenAPI_alert_limit_t	*dst,
                                                OpenAPI_alert_limit_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_alert_limit_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_alert_limit_convertToJSON() failed");
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

	OpenAPI_alert_limit_free(dst);
	dst = OpenAPI_alert_limit_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
