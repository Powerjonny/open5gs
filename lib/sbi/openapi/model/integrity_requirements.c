#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integrity_requirements.h"

OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_create(
	bool is_time_to_alert, int time_to_alert, bool is_target_integrity_risk,
	int target_integrity_risk, OpenAPI_alert_limit_t *alert_limit) {
	OpenAPI_integrity_requirements_t *integrity_requirements_local_var =
		ogs_malloc(sizeof(OpenAPI_integrity_requirements_t));
	ogs_assert(integrity_requirements_local_var);

	integrity_requirements_local_var->is_time_to_alert = is_time_to_alert;
	integrity_requirements_local_var->time_to_alert = time_to_alert;
	integrity_requirements_local_var->is_target_integrity_risk =
		is_target_integrity_risk;
	integrity_requirements_local_var->target_integrity_risk =
		target_integrity_risk;
	integrity_requirements_local_var->alert_limit = alert_limit;

	return integrity_requirements_local_var;
}

void OpenAPI_integrity_requirements_free(
	OpenAPI_integrity_requirements_t *integrity_requirements) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == integrity_requirements) {
		return;
	}
	if(integrity_requirements->alert_limit) {
		OpenAPI_alert_limit_free(integrity_requirements->alert_limit);
		integrity_requirements->alert_limit = NULL;
	}
	ogs_free(integrity_requirements);
}

cJSON *OpenAPI_integrity_requirements_convertToJSON(
	OpenAPI_integrity_requirements_t *integrity_requirements) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(integrity_requirements == NULL) {
		ogs_error(
			"OpenAPI_integrity_requirements_convertToJSON() failed [IntegrityRequirements]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(integrity_requirements->is_time_to_alert) {
		if(cJSON_AddNumberToObject(item, "timeToAlert",
		                           integrity_requirements->time_to_alert)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_integrity_requirements_convertToJSON() failed [time_to_alert]");
			goto end;
		}
	}

	if(integrity_requirements->is_target_integrity_risk) {
		if(cJSON_AddNumberToObject(item, "targetIntegrityRisk",
		                           integrity_requirements->
		                           target_integrity_risk) == NULL)
		{
			ogs_error(
				"OpenAPI_integrity_requirements_convertToJSON() failed [target_integrity_risk]");
			goto end;
		}
	}

	if(integrity_requirements->alert_limit) {
		cJSON *alert_limit_local_JSON =
			OpenAPI_alert_limit_convertToJSON(
				integrity_requirements->alert_limit);
		if(alert_limit_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_integrity_requirements_convertToJSON() failed [alert_limit]");
			goto end;
		}
		cJSON_AddItemToObject(item, "alertLimit",
		                      alert_limit_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_integrity_requirements_convertToJSON() failed [alert_limit]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_parseFromJSON(
	cJSON *integrity_requirementsJSON) {
	OpenAPI_integrity_requirements_t *integrity_requirements_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *time_to_alert = NULL;
	cJSON *target_integrity_risk = NULL;
	cJSON *alert_limit = NULL;
	OpenAPI_alert_limit_t *alert_limit_local_nonprim = NULL;
	time_to_alert =
		cJSON_GetObjectItemCaseSensitive(integrity_requirementsJSON,
		                                 "timeToAlert");
	if(time_to_alert) {
		if(!cJSON_IsNumber(time_to_alert)) {
			ogs_error(
				"OpenAPI_integrity_requirements_parseFromJSON() failed [time_to_alert]");
			goto end;
		}
	}

	target_integrity_risk =
		cJSON_GetObjectItemCaseSensitive(integrity_requirementsJSON,
		                                 "targetIntegrityRisk");
	if(target_integrity_risk) {
		if(!cJSON_IsNumber(target_integrity_risk)) {
			ogs_error(
				"OpenAPI_integrity_requirements_parseFromJSON() failed [target_integrity_risk]");
			goto end;
		}
	}

	alert_limit =
		cJSON_GetObjectItemCaseSensitive(integrity_requirementsJSON,
		                                 "alertLimit");
	if(alert_limit) {
		alert_limit_local_nonprim =
			OpenAPI_alert_limit_parseFromJSON(alert_limit);
		if(!alert_limit_local_nonprim) {
			ogs_error(
				"OpenAPI_alert_limit_parseFromJSON failed [alert_limit]");
			goto end;
		}
	}

	integrity_requirements_local_var =
		OpenAPI_integrity_requirements_create(
			time_to_alert ? true : false,
			time_to_alert ? time_to_alert->valuedouble : 0,
			target_integrity_risk ? true : false,
			target_integrity_risk ?
			target_integrity_risk->valuedouble : 0,
			alert_limit ? alert_limit_local_nonprim : NULL
			);

	return integrity_requirements_local_var;
end:
	if(alert_limit_local_nonprim) {
		OpenAPI_alert_limit_free(alert_limit_local_nonprim);
		alert_limit_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_copy(
	OpenAPI_integrity_requirements_t	*dst,
	OpenAPI_integrity_requirements_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_integrity_requirements_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_integrity_requirements_convertToJSON() failed");
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

	OpenAPI_integrity_requirements_free(dst);
	dst = OpenAPI_integrity_requirements_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
