#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pc_event_any_of.h"

char * OpenAPI_pc_event_any_of_ToString(
	OpenAPI_pc_event_any_of_e pc_event_any_of) {
	const char *pc_event_any_ofArray[] = { "NULL", "AC_TY_CH", "PLMN_CH",
		                               "SAC_CH", "SAT_CATEGORY_CH",
		                               "SUCCESS_UE_POL_DEL_SP",
		                               "UNSUCCESS_UE_POL_DEL_SP" };
	size_t sizeofArray = sizeof(pc_event_any_ofArray) /
	                     sizeof(pc_event_any_ofArray[0]);
	if(pc_event_any_of < sizeofArray) {
		return (char *) pc_event_any_ofArray[pc_event_any_of];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_pc_event_any_of_e OpenAPI_pc_event_any_of_FromString(
	char *pc_event_any_of) {
	int stringToReturn = 0;
	const char *pc_event_any_ofArray[] = { "NULL", "AC_TY_CH", "PLMN_CH",
		                               "SAC_CH", "SAT_CATEGORY_CH",
		                               "SUCCESS_UE_POL_DEL_SP",
		                               "UNSUCCESS_UE_POL_DEL_SP" };
	size_t sizeofArray = sizeof(pc_event_any_ofArray) /
	                     sizeof(pc_event_any_ofArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(pc_event_any_of,
		          pc_event_any_ofArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
