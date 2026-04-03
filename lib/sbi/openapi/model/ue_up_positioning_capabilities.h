/*
 * ue_up_positioning_capabilities.h
 *
 *
 */

#ifndef _OpenAPI_ue_up_positioning_capabilities_H_
#define _OpenAPI_ue_up_positioning_capabilities_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_ue_up_positioning_capabilities_NULL = 0,
	       OpenAPI_ue_up_positioning_capabilities_LCS_UPP,
	       OpenAPI_ue_up_positioning_capabilities_SUPL,
	       OpenAPI_ue_up_positioning_capabilities_MULTIPLE_LCS_UPP }
OpenAPI_ue_up_positioning_capabilities_e;

char * OpenAPI_ue_up_positioning_capabilities_ToString(
	OpenAPI_ue_up_positioning_capabilities_e ue_up_positioning_capabilities);

OpenAPI_ue_up_positioning_capabilities_e
OpenAPI_ue_up_positioning_capabilities_FromString(
	char *ue_up_positioning_capabilities);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_up_positioning_capabilities_H_ */
