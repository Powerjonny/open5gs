#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_status.h"

char * OpenAPI_policy_status_ToString(OpenAPI_policy_status_e policy_status) {
	const char *policy_statusArray[] = { "NULL", "CONFIGURED",
		                             "NOT_CONFIGURED" };
	size_t sizeofArray = sizeof(policy_statusArray) /
	                     sizeof(policy_statusArray[0]);
	if(policy_status < sizeofArray) {
		return (char *) policy_statusArray[policy_status];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_policy_status_e OpenAPI_policy_status_FromString(char *policy_status) {
	int stringToReturn = 0;
	const char *policy_statusArray[] = { "NULL", "CONFIGURED",
		                             "NOT_CONFIGURED" };
	size_t sizeofArray = sizeof(policy_statusArray) /
	                     sizeof(policy_statusArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(policy_status,
		          policy_statusArray[stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
