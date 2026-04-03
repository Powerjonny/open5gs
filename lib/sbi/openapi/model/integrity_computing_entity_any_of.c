#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integrity_computing_entity_any_of.h"

char * OpenAPI_integrity_computing_entity_any_of_ToString(
	OpenAPI_integrity_computing_entity_any_of_e
	integrity_computing_entity_any_of) {
	const char *integrity_computing_entity_any_ofArray[] = { "NULL", "UE",
		                                                 "LMF",
		                                                 "BOTH" };
	size_t sizeofArray = sizeof(integrity_computing_entity_any_ofArray) /
	                     sizeof(integrity_computing_entity_any_ofArray[0]);
	if(integrity_computing_entity_any_of < sizeofArray) {
		return (char *) integrity_computing_entity_any_ofArray[
			integrity_computing_entity_any_of];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_integrity_computing_entity_any_of_e
OpenAPI_integrity_computing_entity_any_of_FromString(
	char *integrity_computing_entity_any_of) {
	int stringToReturn = 0;
	const char *integrity_computing_entity_any_ofArray[] = { "NULL", "UE",
		                                                 "LMF",
		                                                 "BOTH" };
	size_t sizeofArray = sizeof(integrity_computing_entity_any_ofArray) /
	                     sizeof(integrity_computing_entity_any_ofArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(integrity_computing_entity_any_of,
		          integrity_computing_entity_any_ofArray[stringToReturn])
		   == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
