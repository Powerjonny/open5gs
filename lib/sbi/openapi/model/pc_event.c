#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pc_event.h"

OpenAPI_pc_event_t *OpenAPI_pc_event_create() {
	OpenAPI_pc_event_t *pc_event_local_var =
		ogs_malloc(sizeof(OpenAPI_pc_event_t));
	ogs_assert(pc_event_local_var);


	return pc_event_local_var;
}

void OpenAPI_pc_event_free(OpenAPI_pc_event_t *pc_event) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == pc_event) {
		return;
	}
	ogs_free(pc_event);
}

cJSON *OpenAPI_pc_event_convertToJSON(OpenAPI_pc_event_t *pc_event) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(pc_event == NULL) {
		ogs_error("OpenAPI_pc_event_convertToJSON() failed [PcEvent]");
		return NULL;
	}

	item = cJSON_CreateObject();
end:
	return item;
}

OpenAPI_pc_event_t *OpenAPI_pc_event_parseFromJSON(cJSON *pc_eventJSON) {
	OpenAPI_pc_event_t *pc_event_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	pc_event_local_var = OpenAPI_pc_event_create(
		);

	return pc_event_local_var;
end:
	return NULL;
}

OpenAPI_pc_event_t *OpenAPI_pc_event_copy(OpenAPI_pc_event_t	*dst,
                                          OpenAPI_pc_event_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_pc_event_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_pc_event_convertToJSON() failed");
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

	OpenAPI_pc_event_free(dst);
	dst = OpenAPI_pc_event_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
