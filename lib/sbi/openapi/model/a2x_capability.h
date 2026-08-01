/*
 * a2x_capability.h
 *
 *
 */

#ifndef _OpenAPI_a2x_capability_H_
#define _OpenAPI_a2x_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_a2x_capability_NULL = 0,
	       OpenAPI_a2x_capability_EUTRA_PC5, OpenAPI_a2x_capability_NR_PC5,
	       OpenAPI_a2x_capability_UU } OpenAPI_a2x_capability_e;

char * OpenAPI_a2x_capability_ToString(OpenAPI_a2x_capability_e a2x_capability);

OpenAPI_a2x_capability_e OpenAPI_a2x_capability_FromString(
	char *a2x_capability);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_a2x_capability_H_ */
