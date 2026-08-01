#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "termination_notification_ue.h"

OpenAPI_termination_notification_ue_t *
OpenAPI_termination_notification_ue_create(
	char *resource_uri,
	OpenAPI_policy_association_release_cause_ue_e
	cause) {
	OpenAPI_termination_notification_ue_t *
	        termination_notification_ue_local_var =
		ogs_malloc(sizeof(OpenAPI_termination_notification_ue_t));
	ogs_assert(termination_notification_ue_local_var);

	termination_notification_ue_local_var->resource_uri = resource_uri;
	termination_notification_ue_local_var->cause = cause;

	return termination_notification_ue_local_var;
}

void OpenAPI_termination_notification_ue_free(
	OpenAPI_termination_notification_ue_t *termination_notification_ue) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == termination_notification_ue) {
		return;
	}
	if(termination_notification_ue->resource_uri) {
		ogs_free(termination_notification_ue->resource_uri);
		termination_notification_ue->resource_uri = NULL;
	}
	ogs_free(termination_notification_ue);
}

cJSON *OpenAPI_termination_notification_ue_convertToJSON(
	OpenAPI_termination_notification_ue_t *termination_notification_ue) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(termination_notification_ue == NULL) {
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed [TerminationNotificationUE]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!termination_notification_ue->resource_uri) {
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed [resource_uri]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "resourceUri",
	                           termination_notification_ue->resource_uri) ==
	   NULL)
	{
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed [resource_uri]");
		goto end;
	}

	if(termination_notification_ue->cause ==
	   OpenAPI_policy_association_release_cause_ue_NULL)
	{
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed [cause]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "cause",
	                           OpenAPI_policy_association_release_cause_ue_ToString
	                                   (termination_notification_ue->cause))
	   == NULL)
	{
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed [cause]");
		goto end;
	}

end:
	return item;
}

OpenAPI_termination_notification_ue_t *
OpenAPI_termination_notification_ue_parseFromJSON(
	cJSON *termination_notification_ueJSON) {
	OpenAPI_termination_notification_ue_t *
	        termination_notification_ue_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *resource_uri = NULL;
	cJSON *cause = NULL;
	OpenAPI_policy_association_release_cause_ue_e causeVariable = 0;
	resource_uri =
		cJSON_GetObjectItemCaseSensitive(
			termination_notification_ueJSON, "resourceUri");
	if(!resource_uri) {
		ogs_error(
			"OpenAPI_termination_notification_ue_parseFromJSON() failed [resource_uri]");
		goto end;
	}
	if(!cJSON_IsString(resource_uri)) {
		ogs_error(
			"OpenAPI_termination_notification_ue_parseFromJSON() failed [resource_uri]");
		goto end;
	}

	cause =
		cJSON_GetObjectItemCaseSensitive(
			termination_notification_ueJSON, "cause");
	if(!cause) {
		ogs_error(
			"OpenAPI_termination_notification_ue_parseFromJSON() failed [cause]");
		goto end;
	}
	if(!cJSON_IsString(cause)) {
		ogs_error(
			"OpenAPI_termination_notification_ue_parseFromJSON() failed [cause]");
		goto end;
	}
	causeVariable =
		OpenAPI_policy_association_release_cause_ue_FromString(
			cause->valuestring);

	termination_notification_ue_local_var =
		OpenAPI_termination_notification_ue_create(
			ogs_strdup(resource_uri->valuestring),
			causeVariable
			);

	return termination_notification_ue_local_var;
end:
	return NULL;
}

OpenAPI_termination_notification_ue_t *OpenAPI_termination_notification_ue_copy(
	OpenAPI_termination_notification_ue_t	*dst,
	OpenAPI_termination_notification_ue_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_termination_notification_ue_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_termination_notification_ue_convertToJSON() failed");
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

	OpenAPI_termination_notification_ue_free(dst);
	dst = OpenAPI_termination_notification_ue_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
