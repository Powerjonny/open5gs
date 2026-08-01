#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ue_policy_notification.h"

OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_create(
	OpenAPI_list_t *event_notifs) {
	OpenAPI_ue_policy_notification_t *ue_policy_notification_local_var =
		ogs_malloc(sizeof(OpenAPI_ue_policy_notification_t));
	ogs_assert(ue_policy_notification_local_var);

	ue_policy_notification_local_var->event_notifs = event_notifs;

	return ue_policy_notification_local_var;
}

void OpenAPI_ue_policy_notification_free(
	OpenAPI_ue_policy_notification_t *ue_policy_notification) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ue_policy_notification) {
		return;
	}
	if(ue_policy_notification->event_notifs) {
		OpenAPI_list_for_each(ue_policy_notification->event_notifs,
		                      node) {
			OpenAPI_pc_event_notification_free(node->data);
		}
		OpenAPI_list_free(ue_policy_notification->event_notifs);
		ue_policy_notification->event_notifs = NULL;
	}
	ogs_free(ue_policy_notification);
}

cJSON *OpenAPI_ue_policy_notification_convertToJSON(
	OpenAPI_ue_policy_notification_t *ue_policy_notification) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ue_policy_notification == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_notification_convertToJSON() failed [UePolicyNotification]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!ue_policy_notification->event_notifs) {
		ogs_error(
			"OpenAPI_ue_policy_notification_convertToJSON() failed [event_notifs]");
		return NULL;
	}
	cJSON *event_notifsList = cJSON_AddArrayToObject(item, "eventNotifs");
	if(event_notifsList == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_notification_convertToJSON() failed [event_notifs]");
		goto end;
	}
	OpenAPI_list_for_each(ue_policy_notification->event_notifs, node) {
		cJSON *itemLocal =
			OpenAPI_pc_event_notification_convertToJSON(node->data);
		if(itemLocal == NULL) {
			ogs_error(
				"OpenAPI_ue_policy_notification_convertToJSON() failed [event_notifs]");
			goto end;
		}
		cJSON_AddItemToArray(event_notifsList, itemLocal);
	}

end:
	return item;
}

OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_parseFromJSON(
	cJSON *ue_policy_notificationJSON) {
	OpenAPI_ue_policy_notification_t *ue_policy_notification_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *event_notifs = NULL;
	OpenAPI_list_t *event_notifsList = NULL;
	event_notifs =
		cJSON_GetObjectItemCaseSensitive(ue_policy_notificationJSON,
		                                 "eventNotifs");
	if(!event_notifs) {
		ogs_error(
			"OpenAPI_ue_policy_notification_parseFromJSON() failed [event_notifs]");
		goto end;
	}
	cJSON *event_notifs_local = NULL;
	if(!cJSON_IsArray(event_notifs)) {
		ogs_error(
			"OpenAPI_ue_policy_notification_parseFromJSON() failed [event_notifs]");
		goto end;
	}

	event_notifsList = OpenAPI_list_create();

	cJSON_ArrayForEach(event_notifs_local, event_notifs) {
		if(!cJSON_IsObject(event_notifs_local)) {
			ogs_error(
				"OpenAPI_ue_policy_notification_parseFromJSON() failed [event_notifs]");
			goto end;
		}
		OpenAPI_pc_event_notification_t *event_notifsItem =
			OpenAPI_pc_event_notification_parseFromJSON(
				event_notifs_local);
		if(!event_notifsItem) {
			ogs_error("No event_notifsItem");
			goto end;
		}
		OpenAPI_list_add(event_notifsList, event_notifsItem);
	}

	ue_policy_notification_local_var =
		OpenAPI_ue_policy_notification_create(
			event_notifsList
			);

	return ue_policy_notification_local_var;
end:
	if(event_notifsList) {
		OpenAPI_list_for_each(event_notifsList, node) {
			OpenAPI_pc_event_notification_free(node->data);
		}
		OpenAPI_list_free(event_notifsList);
		event_notifsList = NULL;
	}
	return NULL;
}

OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_copy(
	OpenAPI_ue_policy_notification_t	*dst,
	OpenAPI_ue_policy_notification_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ue_policy_notification_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_ue_policy_notification_convertToJSON() failed");
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

	OpenAPI_ue_policy_notification_free(dst);
	dst = OpenAPI_ue_policy_notification_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
