#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_association_release_cause_ue.h"

char * OpenAPI_policy_association_release_cause_ue_ToString(
	OpenAPI_policy_association_release_cause_ue_e
	policy_association_release_cause_ue) {
	const char *policy_association_release_cause_ueArray[] = { "NULL",
		                                                   "UNSPECIFIED",
		                                                   "UE_SUBSCRIPTION",
		                                                   "INSUFFICIENT_RES" };
	size_t sizeofArray = sizeof(policy_association_release_cause_ueArray) /
	                     sizeof(policy_association_release_cause_ueArray[0]);
	if(policy_association_release_cause_ue < sizeofArray) {
		return (char *) policy_association_release_cause_ueArray[
			policy_association_release_cause_ue];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_policy_association_release_cause_ue_e
OpenAPI_policy_association_release_cause_ue_FromString(
	char *policy_association_release_cause_ue) {
	int stringToReturn = 0;
	const char *policy_association_release_cause_ueArray[] = { "NULL",
		                                                   "UNSPECIFIED",
		                                                   "UE_SUBSCRIPTION",
		                                                   "INSUFFICIENT_RES" };
	size_t sizeofArray = sizeof(policy_association_release_cause_ueArray) /
	                     sizeof(policy_association_release_cause_ueArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(policy_association_release_cause_ue,
		          policy_association_release_cause_ueArray[
				  stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
