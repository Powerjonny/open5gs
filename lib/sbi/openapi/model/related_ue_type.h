/*
 * related_ue_type.h
 *
 *
 */

#ifndef _OpenAPI_related_ue_type_H_
#define _OpenAPI_related_ue_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_related_ue_type_NULL = 0,
	       OpenAPI_related_ue_type_LOCATED_UE,
	       OpenAPI_related_ue_type_REFERENCE_UE } OpenAPI_related_ue_type_e;

char * OpenAPI_related_ue_type_ToString(
	OpenAPI_related_ue_type_e related_ue_type);

OpenAPI_related_ue_type_e OpenAPI_related_ue_type_FromString(
	char *related_ue_type);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_related_ue_type_H_ */
