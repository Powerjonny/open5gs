#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ue_policy_parameters.h"

OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_create(
	OpenAPI_list_t *ursp_guidance, bool is_delivery_events_null,
	OpenAPI_list_t *delivery_events) {
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters_local_var =
		ogs_malloc(sizeof(OpenAPI_ue_policy_parameters_t));
	ogs_assert(ue_policy_parameters_local_var);

	ue_policy_parameters_local_var->ursp_guidance = ursp_guidance;
	ue_policy_parameters_local_var->is_delivery_events_null =
		is_delivery_events_null;
	ue_policy_parameters_local_var->delivery_events = delivery_events;

	return ue_policy_parameters_local_var;
}

void OpenAPI_ue_policy_parameters_free(
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == ue_policy_parameters) {
		return;
	}
	if(ue_policy_parameters->ursp_guidance) {
		OpenAPI_list_for_each(ue_policy_parameters->ursp_guidance,
		                      node) {
			OpenAPI_ursp_rule_request_free(node->data);
		}
		OpenAPI_list_free(ue_policy_parameters->ursp_guidance);
		ue_policy_parameters->ursp_guidance = NULL;
	}
	if(ue_policy_parameters->delivery_events) {
		OpenAPI_list_for_each(ue_policy_parameters->delivery_events,
		                      node) {
			OpenAPI_event_free(node->data);
		}
		OpenAPI_list_free(ue_policy_parameters->delivery_events);
		ue_policy_parameters->delivery_events = NULL;
	}
	ogs_free(ue_policy_parameters);
}

cJSON *OpenAPI_ue_policy_parameters_convertToJSON(
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(ue_policy_parameters == NULL) {
		ogs_error(
			"OpenAPI_ue_policy_parameters_convertToJSON() failed [UePolicyParameters]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(ue_policy_parameters->ursp_guidance) {
		cJSON *ursp_guidanceList = cJSON_AddArrayToObject(item,
		                                                  "urspGuidance");
		if(ursp_guidanceList == NULL) {
			ogs_error(
				"OpenAPI_ue_policy_parameters_convertToJSON() failed [ursp_guidance]");
			goto end;
		}
		OpenAPI_list_for_each(ue_policy_parameters->ursp_guidance,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_ursp_rule_request_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_ue_policy_parameters_convertToJSON() failed [ursp_guidance]");
				goto end;
			}
			cJSON_AddItemToArray(ursp_guidanceList, itemLocal);
		}
	}

	if(ue_policy_parameters->delivery_events) {
		cJSON *delivery_eventsList = cJSON_AddArrayToObject(item,
		                                                    "deliveryEvents");
		if(delivery_eventsList == NULL) {
			ogs_error(
				"OpenAPI_ue_policy_parameters_convertToJSON() failed [delivery_events]");
			goto end;
		}
		OpenAPI_list_for_each(ue_policy_parameters->delivery_events,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_event_convertToJSON(node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_ue_policy_parameters_convertToJSON() failed [delivery_events]");
				goto end;
			}
			cJSON_AddItemToArray(delivery_eventsList, itemLocal);
		}
	} else if(ue_policy_parameters->is_delivery_events_null) {
		if(cJSON_AddNullToObject(item, "deliveryEvents") == NULL) {
			ogs_error(
				"OpenAPI_ue_policy_parameters_convertToJSON() failed [delivery_events]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_parseFromJSON(
	cJSON *ue_policy_parametersJSON) {
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *ursp_guidance = NULL;
	OpenAPI_list_t *ursp_guidanceList = NULL;
	cJSON *delivery_events = NULL;
	OpenAPI_list_t *delivery_eventsList = NULL;
	ursp_guidance =
		cJSON_GetObjectItemCaseSensitive(ue_policy_parametersJSON,
		                                 "urspGuidance");
	if(ursp_guidance) {
		cJSON *ursp_guidance_local = NULL;
		if(!cJSON_IsArray(ursp_guidance)) {
			ogs_error(
				"OpenAPI_ue_policy_parameters_parseFromJSON() failed [ursp_guidance]");
			goto end;
		}

		ursp_guidanceList = OpenAPI_list_create();

		cJSON_ArrayForEach(ursp_guidance_local, ursp_guidance) {
			if(!cJSON_IsObject(ursp_guidance_local)) {
				ogs_error(
					"OpenAPI_ue_policy_parameters_parseFromJSON() failed [ursp_guidance]");
				goto end;
			}
			OpenAPI_ursp_rule_request_t *ursp_guidanceItem =
				OpenAPI_ursp_rule_request_parseFromJSON(
					ursp_guidance_local);
			if(!ursp_guidanceItem) {
				ogs_error("No ursp_guidanceItem");
				goto end;
			}
			OpenAPI_list_add(ursp_guidanceList, ursp_guidanceItem);
		}
	}

	delivery_events =
		cJSON_GetObjectItemCaseSensitive(ue_policy_parametersJSON,
		                                 "deliveryEvents");
	if(delivery_events) {
		if(!cJSON_IsNull(delivery_events)) {
			cJSON *delivery_events_local = NULL;
			if(!cJSON_IsArray(delivery_events)) {
				ogs_error(
					"OpenAPI_ue_policy_parameters_parseFromJSON() failed [delivery_events]");
				goto end;
			}

			delivery_eventsList = OpenAPI_list_create();

			cJSON_ArrayForEach(delivery_events_local,
			                   delivery_events) {
				if(!cJSON_IsObject(delivery_events_local)) {
					ogs_error(
						"OpenAPI_ue_policy_parameters_parseFromJSON() failed [delivery_events]");
					goto end;
				}
				OpenAPI_event_t *delivery_eventsItem =
					OpenAPI_event_parseFromJSON(
						delivery_events_local);
				if(!delivery_eventsItem) {
					ogs_error("No delivery_eventsItem");
					goto end;
				}
				OpenAPI_list_add(delivery_eventsList,
				                 delivery_eventsItem);
			}
		}
	}

	ue_policy_parameters_local_var = OpenAPI_ue_policy_parameters_create(
		ursp_guidance ? ursp_guidanceList : NULL,
		delivery_events &&
		cJSON_IsNull(delivery_events) ? true : false,
		delivery_events ? delivery_eventsList : NULL
		);

	return ue_policy_parameters_local_var;
end:
	if(ursp_guidanceList) {
		OpenAPI_list_for_each(ursp_guidanceList, node) {
			OpenAPI_ursp_rule_request_free(node->data);
		}
		OpenAPI_list_free(ursp_guidanceList);
		ursp_guidanceList = NULL;
	}
	if(delivery_eventsList) {
		OpenAPI_list_for_each(delivery_eventsList, node) {
			OpenAPI_event_free(node->data);
		}
		OpenAPI_list_free(delivery_eventsList);
		delivery_eventsList = NULL;
	}
	return NULL;
}

OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_copy(
	OpenAPI_ue_policy_parameters_t	*dst,
	OpenAPI_ue_policy_parameters_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_ue_policy_parameters_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_ue_policy_parameters_convertToJSON() failed");
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

	OpenAPI_ue_policy_parameters_free(dst);
	dst = OpenAPI_ue_policy_parameters_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
