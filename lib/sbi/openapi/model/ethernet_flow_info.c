#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ethernet_flow_info.h"

OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_create(
	OpenAPI_list_t *eth_flows, int flow_number) {
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info_local_var =
		ogs_malloc(sizeof(OpenAPI_ethernet_flow_info_t));
	ogs_assert(ethernet_flow_info_local_var);

	ethernet_flow_info_local_var->eth_flows = eth_flows;
	ethernet_flow_info_local_var->flow_number = flow_number;

	return ethernet_flow_info_local_var;
}

void OpenAPI_ethernet_flow_info_free(
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ethernet_flow_info) {
		return;
	}
	if(ethernet_flow_info->eth_flows) {
		OpenAPI_list_for_each(ethernet_flow_info->eth_flows, node) {
			OpenAPI_eth_flow_description_free(node->data);
		}
		OpenAPI_list_free(ethernet_flow_info->eth_flows);
		ethernet_flow_info->eth_flows = NULL;
	}
	ogs_free(ethernet_flow_info);
}

cJSON *OpenAPI_ethernet_flow_info_convertToJSON(
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ethernet_flow_info == NULL) {
		ogs_error(
			"OpenAPI_ethernet_flow_info_convertToJSON() failed [EthernetFlowInfo]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(ethernet_flow_info->eth_flows) {
		cJSON *eth_flowsList = cJSON_AddArrayToObject(item, "ethFlows");
		if(eth_flowsList == NULL) {
			ogs_error(
				"OpenAPI_ethernet_flow_info_convertToJSON() failed [eth_flows]");
			goto end;
		}
		OpenAPI_list_for_each(ethernet_flow_info->eth_flows, node) {
			cJSON *itemLocal =
				OpenAPI_eth_flow_description_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_ethernet_flow_info_convertToJSON() failed [eth_flows]");
				goto end;
			}
			cJSON_AddItemToArray(eth_flowsList, itemLocal);
		}
	}

	if(cJSON_AddNumberToObject(item, "flowNumber",
	                           ethernet_flow_info->flow_number) == NULL)
	{
		ogs_error(
			"OpenAPI_ethernet_flow_info_convertToJSON() failed [flow_number]");
		goto end;
	}

end:
	return item;
}

OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_parseFromJSON(
	cJSON *ethernet_flow_infoJSON) {
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *eth_flows = NULL;
	OpenAPI_list_t *eth_flowsList = NULL;
	cJSON *flow_number = NULL;
	eth_flows = cJSON_GetObjectItemCaseSensitive(ethernet_flow_infoJSON,
	                                             "ethFlows");
	if(eth_flows) {
		cJSON *eth_flows_local = NULL;
		if(!cJSON_IsArray(eth_flows)) {
			ogs_error(
				"OpenAPI_ethernet_flow_info_parseFromJSON() failed [eth_flows]");
			goto end;
		}

		eth_flowsList = OpenAPI_list_create();

		cJSON_ArrayForEach(eth_flows_local, eth_flows) {
			if(!cJSON_IsObject(eth_flows_local)) {
				ogs_error(
					"OpenAPI_ethernet_flow_info_parseFromJSON() failed [eth_flows]");
				goto end;
			}
			OpenAPI_eth_flow_description_t *eth_flowsItem =
				OpenAPI_eth_flow_description_parseFromJSON(
					eth_flows_local);
			if(!eth_flowsItem) {
				ogs_error("No eth_flowsItem");
				goto end;
			}
			OpenAPI_list_add(eth_flowsList, eth_flowsItem);
		}
	}

	flow_number = cJSON_GetObjectItemCaseSensitive(ethernet_flow_infoJSON,
	                                               "flowNumber");
	if(!flow_number) {
		ogs_error(
			"OpenAPI_ethernet_flow_info_parseFromJSON() failed [flow_number]");
		goto end;
	}
	if(!cJSON_IsNumber(flow_number)) {
		ogs_error(
			"OpenAPI_ethernet_flow_info_parseFromJSON() failed [flow_number]");
		goto end;
	}

	ethernet_flow_info_local_var = OpenAPI_ethernet_flow_info_create(
		eth_flows ? eth_flowsList : NULL,

		flow_number->valuedouble
		);

	return ethernet_flow_info_local_var;
end:
	if(eth_flowsList) {
		OpenAPI_list_for_each(eth_flowsList, node) {
			OpenAPI_eth_flow_description_free(node->data);
		}
		OpenAPI_list_free(eth_flowsList);
		eth_flowsList = NULL;
	}
	return NULL;
}

OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_copy(
	OpenAPI_ethernet_flow_info_t *dst, OpenAPI_ethernet_flow_info_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ethernet_flow_info_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_ethernet_flow_info_convertToJSON() failed");
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

	OpenAPI_ethernet_flow_info_free(dst);
	dst = OpenAPI_ethernet_flow_info_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
