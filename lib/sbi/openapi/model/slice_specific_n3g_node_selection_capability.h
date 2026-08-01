/*
 * slice_specific_n3g_node_selection_capability.h
 *
 *
 */

#ifndef _OpenAPI_slice_specific_n3g_node_selection_capability_H_
#define _OpenAPI_slice_specific_n3g_node_selection_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_slice_specific_n3g_node_selection_capability_NULL = 0,
	       OpenAPI_slice_specific_n3g_node_selection_capability_ONLY_N3IWF_SS_SEL,
	       OpenAPI_slice_specific_n3g_node_selection_capability_ONLY_TNGF_SS_SEL,
	       OpenAPI_slice_specific_n3g_node_selection_capability_TNGF_N3IWF_SS_SEL }
OpenAPI_slice_specific_n3g_node_selection_capability_e;

char * OpenAPI_slice_specific_n3g_node_selection_capability_ToString(
	OpenAPI_slice_specific_n3g_node_selection_capability_e
	slice_specific_n3g_node_selection_capability);

OpenAPI_slice_specific_n3g_node_selection_capability_e
OpenAPI_slice_specific_n3g_node_selection_capability_FromString(
	char *slice_specific_n3g_node_selection_capability);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_slice_specific_n3g_node_selection_capability_H_ */
