#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ue_policy_transfer_failure_notification.h"

OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_create(
	OpenAPI_ue_policy_transfer_failure_cause_t *cause, bool is_retry_after,
	int retry_after, OpenAPI_list_t *ptis) {
	OpenAPI_ue_policy_transfer_failure_notification_t *
	        ue_policy_transfer_failure_notification_local_var =
		ogs_malloc(
			sizeof(OpenAPI_ue_policy_transfer_failure_notification_t));
	ogs_assert(ue_policy_transfer_failure_notification_local_var);

	ue_policy_transfer_failure_notification_local_var->cause = cause;
	ue_policy_transfer_failure_notification_local_var->is_retry_after =
		is_retry_after;
	ue_policy_transfer_failure_notification_local_var->retry_after =
		retry_after;
	ue_policy_transfer_failure_notification_local_var->ptis = ptis;

	return ue_policy_transfer_failure_notification_local_var;
}

void OpenAPI_ue_policy_transfer_failure_notification_free(
	OpenAPI_ue_policy_transfer_failure_notification_t *
	ue_policy_transfer_failure_notification) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ue_policy_transfer_failure_notification) {
		return;
	}
	if(ue_policy_transfer_failure_notification->cause) {
		OpenAPI_ue_policy_transfer_failure_cause_free(
			ue_policy_transfer_failure_notification->cause);
		ue_policy_transfer_failure_notification->cause = NULL;
	}
	if(ue_policy_transfer_failure_notification->ptis) {
		OpenAPI_list_for_each(
			ue_policy_transfer_failure_notification->ptis, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			ue_policy_transfer_failure_notification->ptis);
		ue_policy_transfer_failure_notification->ptis = NULL;
	}
	ogs_free(ue_policy_transfer_failure_notification);
}

cJSON *OpenAPI_ue_policy_transfer_failure_notification_convertToJSON(
	OpenAPI_ue_policy_transfer_failure_notification_t *
	ue_policy_transfer_failure_notification) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ue_policy_transfer_failure_notification == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [UePolicyTransferFailureNotification]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!ue_policy_transfer_failure_notification->cause) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [cause]");
		return NULL;
	}
	cJSON *cause_local_JSON =
		OpenAPI_ue_policy_transfer_failure_cause_convertToJSON(
			ue_policy_transfer_failure_notification->cause);
	if(cause_local_JSON == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [cause]");
		goto end;
	}
	cJSON_AddItemToObject(item, "cause", cause_local_JSON);
	if(item->child == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [cause]");
		goto end;
	}

	if(ue_policy_transfer_failure_notification->is_retry_after) {
		if(cJSON_AddNumberToObject(item, "retryAfter",
		                           ue_policy_transfer_failure_notification
		                           ->retry_after) == NULL)
		{
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [retry_after]");
			goto end;
		}
	}

	if(!ue_policy_transfer_failure_notification->ptis) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [ptis]");
		return NULL;
	}
	cJSON *ptisList = cJSON_AddArrayToObject(item, "ptis");
	if(ptisList == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [ptis]");
		goto end;
	}
	OpenAPI_list_for_each(ue_policy_transfer_failure_notification->ptis,
	                      node) {
		if(node->data == NULL) {
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [ptis]");
			goto end;
		}
		if(cJSON_AddNumberToObject(ptisList, "",
		                           *(double *) node->data) == NULL)
		{
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed [ptis]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON(
	cJSON *ue_policy_transfer_failure_notificationJSON) {
	OpenAPI_ue_policy_transfer_failure_notification_t *
	        ue_policy_transfer_failure_notification_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *cause = NULL;
	OpenAPI_ue_policy_transfer_failure_cause_t *cause_local_nonprim = NULL;
	cJSON *retry_after = NULL;
	cJSON *ptis = NULL;
	OpenAPI_list_t *ptisList = NULL;
	cause =
		cJSON_GetObjectItemCaseSensitive(
			ue_policy_transfer_failure_notificationJSON, "cause");
	if(!cause) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [cause]");
		goto end;
	}
	cause_local_nonprim =
		OpenAPI_ue_policy_transfer_failure_cause_parseFromJSON(cause);
	if(!cause_local_nonprim) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_cause_parseFromJSON failed [cause]");
		goto end;
	}

	retry_after =
		cJSON_GetObjectItemCaseSensitive(
			ue_policy_transfer_failure_notificationJSON,
			"retryAfter");
	if(retry_after) {
		if(!cJSON_IsNumber(retry_after)) {
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [retry_after]");
			goto end;
		}
	}

	ptis =
		cJSON_GetObjectItemCaseSensitive(
			ue_policy_transfer_failure_notificationJSON, "ptis");
	if(!ptis) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [ptis]");
		goto end;
	}
	cJSON *ptis_local = NULL;
	if(!cJSON_IsArray(ptis)) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [ptis]");
		goto end;
	}

	ptisList = OpenAPI_list_create();

	cJSON_ArrayForEach(ptis_local, ptis) {
		double *localDouble = NULL;
		int *localInt = NULL;
		if(!cJSON_IsNumber(ptis_local)) {
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [ptis]");
			goto end;
		}
		localDouble = (double *) ogs_calloc(1, sizeof(double));
		if(!localDouble) {
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON() failed [ptis]");
			goto end;
		}
		*localDouble = ptis_local->valuedouble;
		OpenAPI_list_add(ptisList, localDouble);
	}

	ue_policy_transfer_failure_notification_local_var =
		OpenAPI_ue_policy_transfer_failure_notification_create(
			cause_local_nonprim,
			retry_after ? true : false,
			retry_after ? retry_after->valuedouble : 0,
			ptisList
			);

	return ue_policy_transfer_failure_notification_local_var;
end:
	if(cause_local_nonprim) {
		OpenAPI_ue_policy_transfer_failure_cause_free(
			cause_local_nonprim);
		cause_local_nonprim = NULL;
	}
	if(ptisList) {
		OpenAPI_list_for_each(ptisList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(ptisList);
		ptisList = NULL;
	}
	return NULL;
}

OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_copy(
	OpenAPI_ue_policy_transfer_failure_notification_t	*dst,
	OpenAPI_ue_policy_transfer_failure_notification_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item =
		OpenAPI_ue_policy_transfer_failure_notification_convertToJSON(
			src);
	if(!item) {
		ogs_error(
			"OpenAPI_ue_policy_transfer_failure_notification_convertToJSON() failed");
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

	OpenAPI_ue_policy_transfer_failure_notification_free(dst);
	dst =
		OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON(
			item);
	cJSON_Delete(item);

	return dst;
}
