#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "up_notify_data.h"

OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_create(
	char				*notif_correlation_id,
	OpenAPI_up_connection_status_e	up_connection_status,
	char				*target_lmfid) {
	OpenAPI_up_notify_data_t *up_notify_data_local_var =
		ogs_malloc(sizeof(OpenAPI_up_notify_data_t));
	ogs_assert(up_notify_data_local_var);

	up_notify_data_local_var->notif_correlation_id = notif_correlation_id;
	up_notify_data_local_var->up_connection_status = up_connection_status;
	up_notify_data_local_var->target_lmfid = target_lmfid;

	return up_notify_data_local_var;
}

void OpenAPI_up_notify_data_free(OpenAPI_up_notify_data_t *up_notify_data) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == up_notify_data) {
		return;
	}
	if(up_notify_data->notif_correlation_id) {
		ogs_free(up_notify_data->notif_correlation_id);
		up_notify_data->notif_correlation_id = NULL;
	}
	if(up_notify_data->target_lmfid) {
		ogs_free(up_notify_data->target_lmfid);
		up_notify_data->target_lmfid = NULL;
	}
	ogs_free(up_notify_data);
}

cJSON *OpenAPI_up_notify_data_convertToJSON(
	OpenAPI_up_notify_data_t *up_notify_data) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(up_notify_data == NULL) {
		ogs_error(
			"OpenAPI_up_notify_data_convertToJSON() failed [UpNotifyData]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!up_notify_data->notif_correlation_id) {
		ogs_error(
			"OpenAPI_up_notify_data_convertToJSON() failed [notif_correlation_id]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "notifCorrelationId",
	                           up_notify_data->notif_correlation_id) ==
	   NULL)
	{
		ogs_error(
			"OpenAPI_up_notify_data_convertToJSON() failed [notif_correlation_id]");
		goto end;
	}

	if(up_notify_data->up_connection_status ==
	   OpenAPI_up_connection_status_NULL)
	{
		ogs_error(
			"OpenAPI_up_notify_data_convertToJSON() failed [up_connection_status]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "upConnectionStatus",
	                           OpenAPI_up_connection_status_ToString(
					   up_notify_data->up_connection_status))
	   == NULL)
	{
		ogs_error(
			"OpenAPI_up_notify_data_convertToJSON() failed [up_connection_status]");
		goto end;
	}

	if(up_notify_data->target_lmfid) {
		if(cJSON_AddStringToObject(item, "targetLMFId",
		                           up_notify_data->target_lmfid) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_up_notify_data_convertToJSON() failed [target_lmfid]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_parseFromJSON(
	cJSON *up_notify_dataJSON) {
	OpenAPI_up_notify_data_t *up_notify_data_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *notif_correlation_id = NULL;
	cJSON *up_connection_status = NULL;
	OpenAPI_up_connection_status_e up_connection_statusVariable = 0;
	cJSON *target_lmfid = NULL;
	notif_correlation_id =
		cJSON_GetObjectItemCaseSensitive(up_notify_dataJSON,
		                                 "notifCorrelationId");
	if(!notif_correlation_id) {
		ogs_error(
			"OpenAPI_up_notify_data_parseFromJSON() failed [notif_correlation_id]");
		goto end;
	}
	if(!cJSON_IsString(notif_correlation_id)) {
		ogs_error(
			"OpenAPI_up_notify_data_parseFromJSON() failed [notif_correlation_id]");
		goto end;
	}

	up_connection_status =
		cJSON_GetObjectItemCaseSensitive(up_notify_dataJSON,
		                                 "upConnectionStatus");
	if(!up_connection_status) {
		ogs_error(
			"OpenAPI_up_notify_data_parseFromJSON() failed [up_connection_status]");
		goto end;
	}
	if(!cJSON_IsString(up_connection_status)) {
		ogs_error(
			"OpenAPI_up_notify_data_parseFromJSON() failed [up_connection_status]");
		goto end;
	}
	up_connection_statusVariable =
		OpenAPI_up_connection_status_FromString(
			up_connection_status->valuestring);

	target_lmfid = cJSON_GetObjectItemCaseSensitive(up_notify_dataJSON,
	                                                "targetLMFId");
	if(target_lmfid) {
		if(!cJSON_IsString(target_lmfid) &&
		   !cJSON_IsNull(target_lmfid))
		{
			ogs_error(
				"OpenAPI_up_notify_data_parseFromJSON() failed [target_lmfid]");
			goto end;
		}
	}

	up_notify_data_local_var = OpenAPI_up_notify_data_create(
		ogs_strdup(notif_correlation_id->valuestring),
		up_connection_statusVariable,
		target_lmfid &&
		!cJSON_IsNull(target_lmfid) ?
		ogs_strdup(target_lmfid->valuestring) : NULL
		);

	return up_notify_data_local_var;
end:
	return NULL;
}

OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_copy(
	OpenAPI_up_notify_data_t *dst, OpenAPI_up_notify_data_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_up_notify_data_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_up_notify_data_convertToJSON() failed");
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

	OpenAPI_up_notify_data_free(dst);
	dst = OpenAPI_up_notify_data_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
