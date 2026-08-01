#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "failure_one_of.h"

char * OpenAPI_failure_one_of_ToString(
	OpenAPI_failure_one_of_e failure_one_of) {
	const char *failure_one_ofArray[] = { "NULL", "UNSPECIFIED",
		                              "UE_NOT_REACHABLE", "UNKNOWN",
		                              "UE_TEMP_UNREACHABLE" };
	size_t sizeofArray = sizeof(failure_one_ofArray) /
	                     sizeof(failure_one_ofArray[0]);
	if(failure_one_of < sizeofArray) {
		return (char *) failure_one_ofArray[failure_one_of];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_failure_one_of_e OpenAPI_failure_one_of_FromString(
	char *failure_one_of) {
	int stringToReturn = 0;
	const char *failure_one_ofArray[] = { "NULL", "UNSPECIFIED",
		                              "UE_NOT_REACHABLE", "UNKNOWN",
		                              "UE_TEMP_UNREACHABLE" };
	size_t sizeofArray = sizeof(failure_one_ofArray) /
	                     sizeof(failure_one_ofArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(failure_one_of,
		          failure_one_ofArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
