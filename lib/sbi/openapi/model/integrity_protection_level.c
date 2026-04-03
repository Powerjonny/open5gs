#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integrity_protection_level.h"

OpenAPI_integrity_protection_level_t *OpenAPI_integrity_protection_level_create(
	int horizontal_protection_level, bool is_vertical_protection_level,
	int vertical_protection_level) {
	OpenAPI_integrity_protection_level_t *
	        integrity_protection_level_local_var =
		ogs_malloc(sizeof(OpenAPI_integrity_protection_level_t));
	ogs_assert(integrity_protection_level_local_var);

	integrity_protection_level_local_var->horizontal_protection_level =
		horizontal_protection_level;
	integrity_protection_level_local_var->is_vertical_protection_level =
		is_vertical_protection_level;
	integrity_protection_level_local_var->vertical_protection_level =
		vertical_protection_level;

	return integrity_protection_level_local_var;
}

void OpenAPI_integrity_protection_level_free(
	OpenAPI_integrity_protection_level_t *integrity_protection_level) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == integrity_protection_level) {
		return;
	}
	ogs_free(integrity_protection_level);
}

cJSON *OpenAPI_integrity_protection_level_convertToJSON(
	OpenAPI_integrity_protection_level_t *integrity_protection_level) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(integrity_protection_level == NULL) {
		ogs_error(
			"OpenAPI_integrity_protection_level_convertToJSON() failed [IntegrityProtectionLevel]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(cJSON_AddNumberToObject(item, "horizontalProtectionLevel",
	                           integrity_protection_level->
	                           horizontal_protection_level) == NULL)
	{
		ogs_error(
			"OpenAPI_integrity_protection_level_convertToJSON() failed [horizontal_protection_level]");
		goto end;
	}

	if(integrity_protection_level->is_vertical_protection_level) {
		if(cJSON_AddNumberToObject(item, "verticalProtectionLevel",
		                           integrity_protection_level->
		                           vertical_protection_level) == NULL)
		{
			ogs_error(
				"OpenAPI_integrity_protection_level_convertToJSON() failed [vertical_protection_level]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_integrity_protection_level_t *
OpenAPI_integrity_protection_level_parseFromJSON(
	cJSON *integrity_protection_levelJSON) {
	OpenAPI_integrity_protection_level_t *
	        integrity_protection_level_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *horizontal_protection_level = NULL;
	cJSON *vertical_protection_level = NULL;
	horizontal_protection_level =
		cJSON_GetObjectItemCaseSensitive(integrity_protection_levelJSON,
		                                 "horizontalProtectionLevel");
	if(!horizontal_protection_level) {
		ogs_error(
			"OpenAPI_integrity_protection_level_parseFromJSON() failed [horizontal_protection_level]");
		goto end;
	}
	if(!cJSON_IsNumber(horizontal_protection_level)) {
		ogs_error(
			"OpenAPI_integrity_protection_level_parseFromJSON() failed [horizontal_protection_level]");
		goto end;
	}

	vertical_protection_level =
		cJSON_GetObjectItemCaseSensitive(integrity_protection_levelJSON,
		                                 "verticalProtectionLevel");
	if(vertical_protection_level) {
		if(!cJSON_IsNumber(vertical_protection_level)) {
			ogs_error(
				"OpenAPI_integrity_protection_level_parseFromJSON() failed [vertical_protection_level]");
			goto end;
		}
	}

	integrity_protection_level_local_var =
		OpenAPI_integrity_protection_level_create(

			horizontal_protection_level->valuedouble,
			vertical_protection_level ? true : false,
			vertical_protection_level ?
			vertical_protection_level->valuedouble : 0
			);

	return integrity_protection_level_local_var;
end:
	return NULL;
}

OpenAPI_integrity_protection_level_t *OpenAPI_integrity_protection_level_copy(
	OpenAPI_integrity_protection_level_t	*dst,
	OpenAPI_integrity_protection_level_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_integrity_protection_level_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_integrity_protection_level_convertToJSON() failed");
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

	OpenAPI_integrity_protection_level_free(dst);
	dst = OpenAPI_integrity_protection_level_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
