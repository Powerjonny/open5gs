#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "non3gpp_access.h"

char * OpenAPI_non3gpp_access_ToString(
	OpenAPI_non3gpp_access_e non3gpp_access) {
	const char *non3gpp_accessArray[] = { "NULL", "N3IWF", "TNGF" };
	size_t sizeofArray = sizeof(non3gpp_accessArray) /
	                     sizeof(non3gpp_accessArray[0]);
	if(non3gpp_access < sizeofArray) {
		return (char *) non3gpp_accessArray[non3gpp_access];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_non3gpp_access_e OpenAPI_non3gpp_access_FromString(
	char *non3gpp_access) {
	int stringToReturn = 0;
	const char *non3gpp_accessArray[] = { "NULL", "N3IWF", "TNGF" };
	size_t sizeofArray = sizeof(non3gpp_accessArray) /
	                     sizeof(non3gpp_accessArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(non3gpp_access,
		          non3gpp_accessArray[stringToReturn]) == 0)
		{
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
