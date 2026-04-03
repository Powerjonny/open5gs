#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "add_event_notify_datas.h"

OpenAPI_add_event_notify_datas_t *OpenAPI_add_event_notify_datas_create(
	OpenAPI_list_t *add_event_notify_datas) {
	OpenAPI_add_event_notify_datas_t *add_event_notify_datas_local_var =
		ogs_malloc(sizeof(OpenAPI_add_event_notify_datas_t));
	ogs_assert(add_event_notify_datas_local_var);

	add_event_notify_datas_local_var->add_event_notify_datas =
		add_event_notify_datas;

	return add_event_notify_datas_local_var;
}

void OpenAPI_add_event_notify_datas_free(
	OpenAPI_add_event_notify_datas_t *add_event_notify_datas) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == add_event_notify_datas) {
		return;
	}
	if(add_event_notify_datas->add_event_notify_datas) {
		OpenAPI_list_for_each(
			add_event_notify_datas->add_event_notify_datas, node) {
			OpenAPI_event_notify_data_free(node->data);
		}
		OpenAPI_list_free(
			add_event_notify_datas->add_event_notify_datas);
		add_event_notify_datas->add_event_notify_datas = NULL;
	}
	ogs_free(add_event_notify_datas);
}

cJSON *OpenAPI_add_event_notify_datas_convertToJSON(
	OpenAPI_add_event_notify_datas_t *add_event_notify_datas) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(add_event_notify_datas == NULL) {
		ogs_error(
			"OpenAPI_add_event_notify_datas_convertToJSON() failed [AddEventNotifyDatas]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(add_event_notify_datas->add_event_notify_datas) {
		cJSON *add_event_notify_datasList = cJSON_AddArrayToObject(item,
		                                                           "addEventNotifyDatas");
		if(add_event_notify_datasList == NULL) {
			ogs_error(
				"OpenAPI_add_event_notify_datas_convertToJSON() failed [add_event_notify_datas]");
			goto end;
		}
		OpenAPI_list_for_each(
			add_event_notify_datas->add_event_notify_datas, node) {
			cJSON *itemLocal =
				OpenAPI_event_notify_data_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_add_event_notify_datas_convertToJSON() failed [add_event_notify_datas]");
				goto end;
			}
			cJSON_AddItemToArray(add_event_notify_datasList,
			                     itemLocal);
		}
	}

end:
	return item;
}

OpenAPI_add_event_notify_datas_t *OpenAPI_add_event_notify_datas_parseFromJSON(
	cJSON *add_event_notify_datasJSON) {
	OpenAPI_add_event_notify_datas_t *add_event_notify_datas_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *add_event_notify_datas = NULL;
	OpenAPI_list_t *add_event_notify_datasList = NULL;
	add_event_notify_datas =
		cJSON_GetObjectItemCaseSensitive(add_event_notify_datasJSON,
		                                 "addEventNotifyDatas");
	if(add_event_notify_datas) {
		cJSON *add_event_notify_datas_local = NULL;
		if(!cJSON_IsArray(add_event_notify_datas)) {
			ogs_error(
				"OpenAPI_add_event_notify_datas_parseFromJSON() failed [add_event_notify_datas]");
			goto end;
		}

		add_event_notify_datasList = OpenAPI_list_create();

		cJSON_ArrayForEach(add_event_notify_datas_local,
		                   add_event_notify_datas) {
			if(!cJSON_IsObject(add_event_notify_datas_local)) {
				ogs_error(
					"OpenAPI_add_event_notify_datas_parseFromJSON() failed [add_event_notify_datas]");
				goto end;
			}
			OpenAPI_event_notify_data_t *add_event_notify_datasItem
			        = OpenAPI_event_notify_data_parseFromJSON(
					  add_event_notify_datas_local);
			if(!add_event_notify_datasItem) {
				ogs_error("No add_event_notify_datasItem");
				goto end;
			}
			OpenAPI_list_add(add_event_notify_datasList,
			                 add_event_notify_datasItem);
		}
	}

	add_event_notify_datas_local_var =
		OpenAPI_add_event_notify_datas_create(
			add_event_notify_datas ? add_event_notify_datasList :
			NULL
			);

	return add_event_notify_datas_local_var;
end:
	if(add_event_notify_datasList) {
		OpenAPI_list_for_each(add_event_notify_datasList, node) {
			OpenAPI_event_notify_data_free(node->data);
		}
		OpenAPI_list_free(add_event_notify_datasList);
		add_event_notify_datasList = NULL;
	}
	return NULL;
}

OpenAPI_add_event_notify_datas_t *OpenAPI_add_event_notify_datas_copy(
	OpenAPI_add_event_notify_datas_t	*dst,
	OpenAPI_add_event_notify_datas_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_add_event_notify_datas_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_add_event_notify_datas_convertToJSON() failed");
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

	OpenAPI_add_event_notify_datas_free(dst);
	dst = OpenAPI_add_event_notify_datas_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
