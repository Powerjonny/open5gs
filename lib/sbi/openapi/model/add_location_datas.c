#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "add_location_datas.h"

OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_create(
	OpenAPI_list_t *add_location_datas) {
	OpenAPI_add_location_datas_t *add_location_datas_local_var =
		ogs_malloc(sizeof(OpenAPI_add_location_datas_t));
	ogs_assert(add_location_datas_local_var);

	add_location_datas_local_var->add_location_datas = add_location_datas;

	return add_location_datas_local_var;
}

void OpenAPI_add_location_datas_free(
	OpenAPI_add_location_datas_t *add_location_datas) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == add_location_datas) {
		return;
	}
	if(add_location_datas->add_location_datas) {
		OpenAPI_list_for_each(add_location_datas->add_location_datas,
		                      node) {
			OpenAPI_location_data_free(node->data);
		}
		OpenAPI_list_free(add_location_datas->add_location_datas);
		add_location_datas->add_location_datas = NULL;
	}
	ogs_free(add_location_datas);
}

cJSON *OpenAPI_add_location_datas_convertToJSON(
	OpenAPI_add_location_datas_t *add_location_datas) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(add_location_datas == NULL) {
		ogs_error(
			"OpenAPI_add_location_datas_convertToJSON() failed [AddLocationDatas]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(add_location_datas->add_location_datas) {
		cJSON *add_location_datasList = cJSON_AddArrayToObject(item,
		                                                       "addLocationDatas");
		if(add_location_datasList == NULL) {
			ogs_error(
				"OpenAPI_add_location_datas_convertToJSON() failed [add_location_datas]");
			goto end;
		}
		OpenAPI_list_for_each(add_location_datas->add_location_datas,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_location_data_convertToJSON(node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_add_location_datas_convertToJSON() failed [add_location_datas]");
				goto end;
			}
			cJSON_AddItemToArray(add_location_datasList, itemLocal);
		}
	}

end:
	return item;
}

OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_parseFromJSON(
	cJSON *add_location_datasJSON) {
	OpenAPI_add_location_datas_t *add_location_datas_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *add_location_datas = NULL;
	OpenAPI_list_t *add_location_datasList = NULL;
	add_location_datas =
		cJSON_GetObjectItemCaseSensitive(add_location_datasJSON,
		                                 "addLocationDatas");
	if(add_location_datas) {
		cJSON *add_location_datas_local = NULL;
		if(!cJSON_IsArray(add_location_datas)) {
			ogs_error(
				"OpenAPI_add_location_datas_parseFromJSON() failed [add_location_datas]");
			goto end;
		}

		add_location_datasList = OpenAPI_list_create();

		cJSON_ArrayForEach(add_location_datas_local,
		                   add_location_datas) {
			if(!cJSON_IsObject(add_location_datas_local)) {
				ogs_error(
					"OpenAPI_add_location_datas_parseFromJSON() failed [add_location_datas]");
				goto end;
			}
			OpenAPI_location_data_t *add_location_datasItem =
				OpenAPI_location_data_parseFromJSON(
					add_location_datas_local);
			if(!add_location_datasItem) {
				ogs_error("No add_location_datasItem");
				goto end;
			}
			OpenAPI_list_add(add_location_datasList,
			                 add_location_datasItem);
		}
	}

	add_location_datas_local_var = OpenAPI_add_location_datas_create(
		add_location_datas ? add_location_datasList : NULL
		);

	return add_location_datas_local_var;
end:
	if(add_location_datasList) {
		OpenAPI_list_for_each(add_location_datasList, node) {
			OpenAPI_location_data_free(node->data);
		}
		OpenAPI_list_free(add_location_datasList);
		add_location_datasList = NULL;
	}
	return NULL;
}

OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_copy(
	OpenAPI_add_location_datas_t *dst, OpenAPI_add_location_datas_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_add_location_datas_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_add_location_datas_convertToJSON() failed");
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

	OpenAPI_add_location_datas_free(dst);
	dst = OpenAPI_add_location_datas_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
