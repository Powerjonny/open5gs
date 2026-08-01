#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "request_trigger_ue.h"

char * OpenAPI_request_trigger_ue_ToString(
	OpenAPI_request_trigger_ue_e request_trigger_ue) {
	const char *request_trigger_ueArray[] = { "NULL", "LOC_CH", "PRA_CH",
		                                  "UE_POLICY", "PLMN_CH",
		                                  "CON_STATE_CH",
		                                  "GROUP_ID_LIST_CHG",
		                                  "UE_CAP_CH",
		                                  "SAT_CATEGORY_CHG",
		                                  "NON_3GPP_NODE_RESELECTION",
		                                  "CONF_NSSAI_CH",
		                                  "LBO_INFO_CH", "FEAT_RENEG",
		                                  "URSP_ENF_INFO",
		                                  "ACCESS_TYPE_CH" };
	size_t sizeofArray = sizeof(request_trigger_ueArray) /
	                     sizeof(request_trigger_ueArray[0]);
	if(request_trigger_ue < sizeofArray) {
		return (char *) request_trigger_ueArray[request_trigger_ue];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_request_trigger_ue_e OpenAPI_request_trigger_ue_FromString(
	char *request_trigger_ue) {
	int stringToReturn = 0;
	const char *request_trigger_ueArray[] = { "NULL", "LOC_CH", "PRA_CH",
		                                  "UE_POLICY", "PLMN_CH",
		                                  "CON_STATE_CH",
		                                  "GROUP_ID_LIST_CHG",
		                                  "UE_CAP_CH",
		                                  "SAT_CATEGORY_CHG",
		                                  "NON_3GPP_NODE_RESELECTION",
		                                  "CONF_NSSAI_CH",
		                                  "LBO_INFO_CH", "FEAT_RENEG",
		                                  "URSP_ENF_INFO",
		                                  "ACCESS_TYPE_CH" };
	size_t sizeofArray = sizeof(request_trigger_ueArray) /
	                     sizeof(request_trigger_ueArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(request_trigger_ue,
		          request_trigger_ueArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
