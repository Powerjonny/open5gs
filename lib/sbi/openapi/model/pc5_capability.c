#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pc5_capability.h"

char * OpenAPI_pc5_capability_ToString(
	OpenAPI_pc5_capability_e pc5_capability) {
	const char *pc5_capabilityArray[] = { "NULL", "LTE_PC5", "NR_PC5",
		                              "LTE_NR_PC5" };
	size_t sizeofArray = sizeof(pc5_capabilityArray) /
	                     sizeof(pc5_capabilityArray[0]);
	if(pc5_capability < sizeofArray) {
		return (char *) pc5_capabilityArray[pc5_capability];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_pc5_capability_e OpenAPI_pc5_capability_FromString(
	char *pc5_capability) {
	int stringToReturn = 0;
	const char *pc5_capabilityArray[] = { "NULL", "LTE_PC5", "NR_PC5",
		                              "LTE_NR_PC5" };
	size_t sizeofArray = sizeof(pc5_capabilityArray) /
	                     sizeof(pc5_capabilityArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(pc5_capability,
		          pc5_capabilityArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
