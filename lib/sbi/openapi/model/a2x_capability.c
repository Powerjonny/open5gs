#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "a2x_capability.h"

char * OpenAPI_a2x_capability_ToString(
	OpenAPI_a2x_capability_e a2x_capability) {
	const char *a2x_capabilityArray[] = { "NULL", "EUTRA_PC5", "NR_PC5",
		                              "UU" };
	size_t sizeofArray = sizeof(a2x_capabilityArray) /
	                     sizeof(a2x_capabilityArray[0]);
	if(a2x_capability < sizeofArray) {
		return (char *) a2x_capabilityArray[a2x_capability];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_a2x_capability_e OpenAPI_a2x_capability_FromString(
	char *a2x_capability) {
	int stringToReturn = 0;
	const char *a2x_capabilityArray[] = { "NULL", "EUTRA_PC5", "NR_PC5",
		                              "UU" };
	size_t sizeofArray = sizeof(a2x_capabilityArray) /
	                     sizeof(a2x_capabilityArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(a2x_capability,
		          a2x_capabilityArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
