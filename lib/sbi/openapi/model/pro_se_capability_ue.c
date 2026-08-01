#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pro_se_capability_ue.h"

char * OpenAPI_pro_se_capability_ue_ToString(
	OpenAPI_pro_se_capability_ue_e pro_se_capability_ue) {
	const char *pro_se_capability_ueArray[] = { "NULL", "PROSE_DD",
		                                    "PROSE_DC",
		                                    "PROSE_L2_U2N_RELAY",
		                                    "PROSE_L3_U2N_RELAY",
		                                    "PROSE_L2_REMOTE_UE",
		                                    "PROSE_L3_REMOTE_UE",
		                                    "PROSE_L2_U2U_RELAY",
		                                    "PROSE_L3_U2U_RELAY",
		                                    "PROSE_L2_END_UE",
		                                    "PROSE_L3_END_UE",
		                                    "PROSE_MH_L2_U2N_RELAY",
		                                    "PROSE_MH_L3_U2N_RELAY",
		                                    "PROSE_MH_L2_REMOTE_UE",
		                                    "PROSE_MH_L3_REMOTE_UE",
		                                    "PROSE_MH_L2_INTERMEDIATE_UE",
		                                    "PROSE_MH_L3_INTERMEDIATE_UE",
		                                    "PROSE_MH_L3_U2U_RELAY",
		                                    "PROSE_MH_L3_END_UE" };
	size_t sizeofArray = sizeof(pro_se_capability_ueArray) /
	                     sizeof(pro_se_capability_ueArray[0]);
	if(pro_se_capability_ue < sizeofArray) {
		return (char *) pro_se_capability_ueArray[pro_se_capability_ue];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_pro_se_capability_ue_e OpenAPI_pro_se_capability_ue_FromString(
	char *pro_se_capability_ue) {
	int stringToReturn = 0;
	const char *pro_se_capability_ueArray[] = { "NULL", "PROSE_DD",
		                                    "PROSE_DC",
		                                    "PROSE_L2_U2N_RELAY",
		                                    "PROSE_L3_U2N_RELAY",
		                                    "PROSE_L2_REMOTE_UE",
		                                    "PROSE_L3_REMOTE_UE",
		                                    "PROSE_L2_U2U_RELAY",
		                                    "PROSE_L3_U2U_RELAY",
		                                    "PROSE_L2_END_UE",
		                                    "PROSE_L3_END_UE",
		                                    "PROSE_MH_L2_U2N_RELAY",
		                                    "PROSE_MH_L3_U2N_RELAY",
		                                    "PROSE_MH_L2_REMOTE_UE",
		                                    "PROSE_MH_L3_REMOTE_UE",
		                                    "PROSE_MH_L2_INTERMEDIATE_UE",
		                                    "PROSE_MH_L3_INTERMEDIATE_UE",
		                                    "PROSE_MH_L3_U2U_RELAY",
		                                    "PROSE_MH_L3_END_UE" };
	size_t sizeofArray = sizeof(pro_se_capability_ueArray) /
	                     sizeof(pro_se_capability_ueArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(pro_se_capability_ue,
		          pro_se_capability_ueArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
