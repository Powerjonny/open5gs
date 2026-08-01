#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_identification.h"

OpenAPI_service_identification_t *OpenAPI_service_identification_create(
	OpenAPI_list_t *serv_eth_flows, OpenAPI_list_t *serv_ip_flows,
	char *af_app_id) {
	OpenAPI_service_identification_t *service_identification_local_var =
		ogs_malloc(sizeof(OpenAPI_service_identification_t));
	ogs_assert(service_identification_local_var);

	service_identification_local_var->serv_eth_flows = serv_eth_flows;
	service_identification_local_var->serv_ip_flows = serv_ip_flows;
	service_identification_local_var->af_app_id = af_app_id;

	return service_identification_local_var;
}

void OpenAPI_service_identification_free(
	OpenAPI_service_identification_t *service_identification) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == service_identification) {
		return;
	}
	if(service_identification->serv_eth_flows) {
		OpenAPI_list_for_each(service_identification->serv_eth_flows,
		                      node) {
			OpenAPI_ethernet_flow_info_free(node->data);
		}
		OpenAPI_list_free(service_identification->serv_eth_flows);
		service_identification->serv_eth_flows = NULL;
	}
	if(service_identification->serv_ip_flows) {
		OpenAPI_list_for_each(service_identification->serv_ip_flows,
		                      node) {
			OpenAPI_ip_flow_info_free(node->data);
		}
		OpenAPI_list_free(service_identification->serv_ip_flows);
		service_identification->serv_ip_flows = NULL;
	}
	if(service_identification->af_app_id) {
		ogs_free(service_identification->af_app_id);
		service_identification->af_app_id = NULL;
	}
	ogs_free(service_identification);
}

cJSON *OpenAPI_service_identification_convertToJSON(
	OpenAPI_service_identification_t *service_identification) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(service_identification == NULL) {
		ogs_error(
			"OpenAPI_service_identification_convertToJSON() failed [ServiceIdentification]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(service_identification->serv_eth_flows) {
		cJSON *serv_eth_flowsList = cJSON_AddArrayToObject(item,
		                                                   "servEthFlows");
		if(serv_eth_flowsList == NULL) {
			ogs_error(
				"OpenAPI_service_identification_convertToJSON() failed [serv_eth_flows]");
			goto end;
		}
		OpenAPI_list_for_each(service_identification->serv_eth_flows,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_ethernet_flow_info_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_service_identification_convertToJSON() failed [serv_eth_flows]");
				goto end;
			}
			cJSON_AddItemToArray(serv_eth_flowsList, itemLocal);
		}
	}

	if(service_identification->serv_ip_flows) {
		cJSON *serv_ip_flowsList = cJSON_AddArrayToObject(item,
		                                                  "servIpFlows");
		if(serv_ip_flowsList == NULL) {
			ogs_error(
				"OpenAPI_service_identification_convertToJSON() failed [serv_ip_flows]");
			goto end;
		}
		OpenAPI_list_for_each(service_identification->serv_ip_flows,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_ip_flow_info_convertToJSON(node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_service_identification_convertToJSON() failed [serv_ip_flows]");
				goto end;
			}
			cJSON_AddItemToArray(serv_ip_flowsList, itemLocal);
		}
	}

	if(service_identification->af_app_id) {
		if(cJSON_AddStringToObject(item, "afAppId",
		                           service_identification->af_app_id) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_service_identification_convertToJSON() failed [af_app_id]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_service_identification_t *OpenAPI_service_identification_parseFromJSON(
	cJSON *service_identificationJSON) {
	OpenAPI_service_identification_t *service_identification_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *serv_eth_flows = NULL;
	OpenAPI_list_t *serv_eth_flowsList = NULL;
	cJSON *serv_ip_flows = NULL;
	OpenAPI_list_t *serv_ip_flowsList = NULL;
	cJSON *af_app_id = NULL;
	serv_eth_flows =
		cJSON_GetObjectItemCaseSensitive(service_identificationJSON,
		                                 "servEthFlows");
	if(serv_eth_flows) {
		cJSON *serv_eth_flows_local = NULL;
		if(!cJSON_IsArray(serv_eth_flows)) {
			ogs_error(
				"OpenAPI_service_identification_parseFromJSON() failed [serv_eth_flows]");
			goto end;
		}

		serv_eth_flowsList = OpenAPI_list_create();

		cJSON_ArrayForEach(serv_eth_flows_local, serv_eth_flows) {
			if(!cJSON_IsObject(serv_eth_flows_local)) {
				ogs_error(
					"OpenAPI_service_identification_parseFromJSON() failed [serv_eth_flows]");
				goto end;
			}
			OpenAPI_ethernet_flow_info_t *serv_eth_flowsItem =
				OpenAPI_ethernet_flow_info_parseFromJSON(
					serv_eth_flows_local);
			if(!serv_eth_flowsItem) {
				ogs_error("No serv_eth_flowsItem");
				goto end;
			}
			OpenAPI_list_add(serv_eth_flowsList,
			                 serv_eth_flowsItem);
		}
	}

	serv_ip_flows =
		cJSON_GetObjectItemCaseSensitive(service_identificationJSON,
		                                 "servIpFlows");
	if(serv_ip_flows) {
		cJSON *serv_ip_flows_local = NULL;
		if(!cJSON_IsArray(serv_ip_flows)) {
			ogs_error(
				"OpenAPI_service_identification_parseFromJSON() failed [serv_ip_flows]");
			goto end;
		}

		serv_ip_flowsList = OpenAPI_list_create();

		cJSON_ArrayForEach(serv_ip_flows_local, serv_ip_flows) {
			if(!cJSON_IsObject(serv_ip_flows_local)) {
				ogs_error(
					"OpenAPI_service_identification_parseFromJSON() failed [serv_ip_flows]");
				goto end;
			}
			OpenAPI_ip_flow_info_t *serv_ip_flowsItem =
				OpenAPI_ip_flow_info_parseFromJSON(
					serv_ip_flows_local);
			if(!serv_ip_flowsItem) {
				ogs_error("No serv_ip_flowsItem");
				goto end;
			}
			OpenAPI_list_add(serv_ip_flowsList, serv_ip_flowsItem);
		}
	}

	af_app_id = cJSON_GetObjectItemCaseSensitive(service_identificationJSON,
	                                             "afAppId");
	if(af_app_id) {
		if(!cJSON_IsString(af_app_id) &&
		   !cJSON_IsNull(af_app_id))
		{
			ogs_error(
				"OpenAPI_service_identification_parseFromJSON() failed [af_app_id]");
			goto end;
		}
	}

	service_identification_local_var =
		OpenAPI_service_identification_create(
			serv_eth_flows ? serv_eth_flowsList : NULL,
			serv_ip_flows ? serv_ip_flowsList : NULL,
			af_app_id &&
			!cJSON_IsNull(af_app_id) ?
			ogs_strdup(af_app_id->valuestring) :
			NULL
			);

	return service_identification_local_var;
end:
	if(serv_eth_flowsList) {
		OpenAPI_list_for_each(serv_eth_flowsList, node) {
			OpenAPI_ethernet_flow_info_free(node->data);
		}
		OpenAPI_list_free(serv_eth_flowsList);
		serv_eth_flowsList = NULL;
	}
	if(serv_ip_flowsList) {
		OpenAPI_list_for_each(serv_ip_flowsList, node) {
			OpenAPI_ip_flow_info_free(node->data);
		}
		OpenAPI_list_free(serv_ip_flowsList);
		serv_ip_flowsList = NULL;
	}
	return NULL;
}

OpenAPI_service_identification_t *OpenAPI_service_identification_copy(
	OpenAPI_service_identification_t	*dst,
	OpenAPI_service_identification_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_service_identification_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_service_identification_convertToJSON() failed");
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

	OpenAPI_service_identification_free(dst);
	dst = OpenAPI_service_identification_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
