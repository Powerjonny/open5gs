#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "slice_specific_n3g_node_selection_capability.h"

char * OpenAPI_slice_specific_n3g_node_selection_capability_ToString(
	OpenAPI_slice_specific_n3g_node_selection_capability_e
	slice_specific_n3g_node_selection_capability) {
	const char *slice_specific_n3g_node_selection_capabilityArray[] =
	{ "NULL", "ONLY_N3IWF_SS_SEL", "ONLY_TNGF_SS_SEL",
	  "TNGF_N3IWF_SS_SEL" };
	size_t sizeofArray =
		sizeof(slice_specific_n3g_node_selection_capabilityArray) /
		sizeof(slice_specific_n3g_node_selection_capabilityArray[0]);
	if(slice_specific_n3g_node_selection_capability < sizeofArray) {
		return (char *)
		       slice_specific_n3g_node_selection_capabilityArray[
			slice_specific_n3g_node_selection_capability];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_slice_specific_n3g_node_selection_capability_e
OpenAPI_slice_specific_n3g_node_selection_capability_FromString(
	char *slice_specific_n3g_node_selection_capability) {
	int stringToReturn = 0;
	const char *slice_specific_n3g_node_selection_capabilityArray[] =
	{ "NULL", "ONLY_N3IWF_SS_SEL", "ONLY_TNGF_SS_SEL",
	  "TNGF_N3IWF_SS_SEL" };
	size_t sizeofArray =
		sizeof(slice_specific_n3g_node_selection_capabilityArray) /
		sizeof(slice_specific_n3g_node_selection_capabilityArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(slice_specific_n3g_node_selection_capability,
		          slice_specific_n3g_node_selection_capabilityArray[
				  stringToReturn]) == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
