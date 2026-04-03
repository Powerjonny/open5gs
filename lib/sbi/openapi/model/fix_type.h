/*
 * fix_type.h
 *
 *
 */

#ifndef _OpenAPI_fix_type_H_
#define _OpenAPI_fix_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_fix_type_NULL = 0, OpenAPI_fix_type_CARRIER_PHASE_FLOAT,
	       OpenAPI_fix_type_CARRIER_PHASE_FIX } OpenAPI_fix_type_e;

char * OpenAPI_fix_type_ToString(OpenAPI_fix_type_e fix_type);

OpenAPI_fix_type_e OpenAPI_fix_type_FromString(char *fix_type);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_fix_type_H_ */
