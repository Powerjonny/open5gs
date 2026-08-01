#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rang_sl_capability.h"

char * OpenAPI_rang_sl_capability_ToString(
	OpenAPI_rang_sl_capability_e rang_sl_capability) {
	const char *rang_sl_capabilityArray[] = { "NULL", "PC5_RANGING_SL" };
	size_t sizeofArray = sizeof(rang_sl_capabilityArray) /
	                     sizeof(rang_sl_capabilityArray[0]);
	if(rang_sl_capability < sizeofArray) {
		return (char *) rang_sl_capabilityArray[rang_sl_capability];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_rang_sl_capability_e OpenAPI_rang_sl_capability_FromString(
	char *rang_sl_capability) {
	int stringToReturn = 0;
	const char *rang_sl_capabilityArray[] = { "NULL", "PC5_RANGING_SL" };
	size_t sizeofArray = sizeof(rang_sl_capabilityArray) /
	                     sizeof(rang_sl_capabilityArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(rang_sl_capability,
		          rang_sl_capabilityArray[stringToReturn]) == 0)
		{
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
