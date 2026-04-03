#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sl_positioning_capability.h"

char * OpenAPI_sl_positioning_capability_ToString(
	OpenAPI_sl_positioning_capability_e sl_positioning_capability) {
	const char *sl_positioning_capabilityArray[] = { "NULL", "V2X",
		                                         "5G_PROSE" };
	size_t sizeofArray = sizeof(sl_positioning_capabilityArray) /
	                     sizeof(sl_positioning_capabilityArray[0]);
	if(sl_positioning_capability < sizeofArray) {
		return (char *) sl_positioning_capabilityArray[
			sl_positioning_capability];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_sl_positioning_capability_e OpenAPI_sl_positioning_capability_FromString
        (char *sl_positioning_capability) {
	int stringToReturn = 0;
	const char *sl_positioning_capabilityArray[] = { "NULL", "V2X",
		                                         "5G_PROSE" };
	size_t sizeofArray = sizeof(sl_positioning_capabilityArray) /
	                     sizeof(sl_positioning_capabilityArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(sl_positioning_capability,
		          sl_positioning_capabilityArray[stringToReturn]) ==
		   0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
