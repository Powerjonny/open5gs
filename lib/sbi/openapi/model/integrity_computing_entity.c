#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integrity_computing_entity.h"

OpenAPI_integrity_computing_entity_t *OpenAPI_integrity_computing_entity_create()
{
	OpenAPI_integrity_computing_entity_t *
	        integrity_computing_entity_local_var =
		ogs_malloc(sizeof(OpenAPI_integrity_computing_entity_t));
	ogs_assert(integrity_computing_entity_local_var);


	return integrity_computing_entity_local_var;
}

void OpenAPI_integrity_computing_entity_free(
	OpenAPI_integrity_computing_entity_t *integrity_computing_entity) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == integrity_computing_entity) {
		return;
	}
	ogs_free(integrity_computing_entity);
}

cJSON *OpenAPI_integrity_computing_entity_convertToJSON(
	OpenAPI_integrity_computing_entity_t *integrity_computing_entity) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(integrity_computing_entity == NULL) {
		ogs_error(
			"OpenAPI_integrity_computing_entity_convertToJSON() failed [IntegrityComputingEntity]");
		return NULL;
	}

	item = cJSON_CreateObject();
end:
	return item;
}

OpenAPI_integrity_computing_entity_t *
OpenAPI_integrity_computing_entity_parseFromJSON(
	cJSON *integrity_computing_entityJSON) {
	OpenAPI_integrity_computing_entity_t *
	        integrity_computing_entity_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	integrity_computing_entity_local_var =
		OpenAPI_integrity_computing_entity_create(
			);

	return integrity_computing_entity_local_var;
end:
	return NULL;
}

OpenAPI_integrity_computing_entity_t *OpenAPI_integrity_computing_entity_copy(
	OpenAPI_integrity_computing_entity_t	*dst,
	OpenAPI_integrity_computing_entity_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_integrity_computing_entity_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_integrity_computing_entity_convertToJSON() failed");
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

	OpenAPI_integrity_computing_entity_free(dst);
	dst = OpenAPI_integrity_computing_entity_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
