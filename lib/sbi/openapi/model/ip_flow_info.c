#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ip_flow_info.h"

OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_create(
	OpenAPI_list_t *ip_flows,
	int
	flow_number) {
	OpenAPI_ip_flow_info_t *ip_flow_info_local_var =
		ogs_malloc(sizeof(OpenAPI_ip_flow_info_t));
	ogs_assert(ip_flow_info_local_var);

	ip_flow_info_local_var->ip_flows = ip_flows;
	ip_flow_info_local_var->flow_number = flow_number;

	return ip_flow_info_local_var;
}

void OpenAPI_ip_flow_info_free(OpenAPI_ip_flow_info_t *ip_flow_info) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ip_flow_info) {
		return;
	}
	if(ip_flow_info->ip_flows) {
		OpenAPI_list_for_each(ip_flow_info->ip_flows, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(ip_flow_info->ip_flows);
		ip_flow_info->ip_flows = NULL;
	}
	ogs_free(ip_flow_info);
}

cJSON *OpenAPI_ip_flow_info_convertToJSON(
	OpenAPI_ip_flow_info_t *ip_flow_info) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ip_flow_info == NULL) {
		ogs_error(
			"OpenAPI_ip_flow_info_convertToJSON() failed [IpFlowInfo]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(ip_flow_info->ip_flows) {
		cJSON *ip_flowsList = cJSON_AddArrayToObject(item, "ipFlows");
		if(ip_flowsList == NULL) {
			ogs_error(
				"OpenAPI_ip_flow_info_convertToJSON() failed [ip_flows]");
			goto end;
		}
		OpenAPI_list_for_each(ip_flow_info->ip_flows, node) {
			if(cJSON_AddStringToObject(ip_flowsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_ip_flow_info_convertToJSON() failed [ip_flows]");
				goto end;
			}
		}
	}

	if(cJSON_AddNumberToObject(item, "flowNumber",
	                           ip_flow_info->flow_number) == NULL)
	{
		ogs_error(
			"OpenAPI_ip_flow_info_convertToJSON() failed [flow_number]");
		goto end;
	}

end:
	return item;
}

OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_parseFromJSON(
	cJSON *ip_flow_infoJSON) {
	OpenAPI_ip_flow_info_t *ip_flow_info_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *ip_flows = NULL;
	OpenAPI_list_t *ip_flowsList = NULL;
	cJSON *flow_number = NULL;
	ip_flows = cJSON_GetObjectItemCaseSensitive(ip_flow_infoJSON,
	                                            "ipFlows");
	if(ip_flows) {
		cJSON *ip_flows_local = NULL;
		if(!cJSON_IsArray(ip_flows)) {
			ogs_error(
				"OpenAPI_ip_flow_info_parseFromJSON() failed [ip_flows]");
			goto end;
		}

		ip_flowsList = OpenAPI_list_create();

		cJSON_ArrayForEach(ip_flows_local, ip_flows) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(ip_flows_local)) {
				ogs_error(
					"OpenAPI_ip_flow_info_parseFromJSON() failed [ip_flows]");
				goto end;
			}
			OpenAPI_list_add(ip_flowsList,
			                 ogs_strdup(
						 ip_flows_local->valuestring));
		}
	}

	flow_number = cJSON_GetObjectItemCaseSensitive(ip_flow_infoJSON,
	                                               "flowNumber");
	if(!flow_number) {
		ogs_error(
			"OpenAPI_ip_flow_info_parseFromJSON() failed [flow_number]");
		goto end;
	}
	if(!cJSON_IsNumber(flow_number)) {
		ogs_error(
			"OpenAPI_ip_flow_info_parseFromJSON() failed [flow_number]");
		goto end;
	}

	ip_flow_info_local_var = OpenAPI_ip_flow_info_create(
		ip_flows ? ip_flowsList : NULL,

		flow_number->valuedouble
		);

	return ip_flow_info_local_var;
end:
	if(ip_flowsList) {
		OpenAPI_list_for_each(ip_flowsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(ip_flowsList);
		ip_flowsList = NULL;
	}
	return NULL;
}

OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_copy(
	OpenAPI_ip_flow_info_t	*dst,
	OpenAPI_ip_flow_info_t
	                        *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ip_flow_info_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_ip_flow_info_convertToJSON() failed");
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

	OpenAPI_ip_flow_info_free(dst);
	dst = OpenAPI_ip_flow_info_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
