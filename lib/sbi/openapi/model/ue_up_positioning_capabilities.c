#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ue_up_positioning_capabilities.h"

char * OpenAPI_ue_up_positioning_capabilities_ToString(
	OpenAPI_ue_up_positioning_capabilities_e ue_up_positioning_capabilities)
{
	const char *ue_up_positioning_capabilitiesArray[] = { "NULL", "LCS_UPP",
		                                              "SUPL",
		                                              "MULTIPLE_LCS_UPP" };
	size_t sizeofArray = sizeof(ue_up_positioning_capabilitiesArray) /
	                     sizeof(ue_up_positioning_capabilitiesArray[0]);
	if(ue_up_positioning_capabilities < sizeofArray) {
		return (char *) ue_up_positioning_capabilitiesArray[
			ue_up_positioning_capabilities];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_ue_up_positioning_capabilities_e
OpenAPI_ue_up_positioning_capabilities_FromString(
	char *ue_up_positioning_capabilities) {
	int stringToReturn = 0;
	const char *ue_up_positioning_capabilitiesArray[] = { "NULL", "LCS_UPP",
		                                              "SUPL",
		                                              "MULTIPLE_LCS_UPP" };
	size_t sizeofArray = sizeof(ue_up_positioning_capabilitiesArray) /
	                     sizeof(ue_up_positioning_capabilitiesArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(ue_up_positioning_capabilities,
		          ue_up_positioning_capabilitiesArray[stringToReturn])
		   == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
