#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "failure.h"

OpenAPI_failure_t *OpenAPI_failure_create() {
	OpenAPI_failure_t *failure_local_var =
		ogs_malloc(sizeof(OpenAPI_failure_t));
	ogs_assert(failure_local_var);


	return failure_local_var;
}

void OpenAPI_failure_free(OpenAPI_failure_t *failure) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == failure) {
		return;
	}
	ogs_free(failure);
}

cJSON *OpenAPI_failure_convertToJSON(OpenAPI_failure_t *failure) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(failure == NULL) {
		ogs_error("OpenAPI_failure_convertToJSON() failed [Failure]");
		return NULL;
	}

	item = cJSON_CreateObject();
end:
	return item;
}

OpenAPI_failure_t *OpenAPI_failure_parseFromJSON(cJSON *failureJSON) {
	OpenAPI_failure_t *failure_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	failure_local_var = OpenAPI_failure_create(
		);

	return failure_local_var;
end:
	return NULL;
}

OpenAPI_failure_t *OpenAPI_failure_copy(OpenAPI_failure_t	*dst,
                                        OpenAPI_failure_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_failure_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_failure_convertToJSON() failed");
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

	OpenAPI_failure_free(dst);
	dst = OpenAPI_failure_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
