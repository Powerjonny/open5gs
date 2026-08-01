/*
 * pc5_capability.h
 *
 *
 */

#ifndef _OpenAPI_pc5_capability_H_
#define _OpenAPI_pc5_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_pc5_capability_NULL = 0, OpenAPI_pc5_capability_LTE_PC5,
	       OpenAPI_pc5_capability_NR_PC5,
	       OpenAPI_pc5_capability_LTE_NR_PC5 } OpenAPI_pc5_capability_e;

char * OpenAPI_pc5_capability_ToString(OpenAPI_pc5_capability_e pc5_capability);

OpenAPI_pc5_capability_e OpenAPI_pc5_capability_FromString(
	char *pc5_capability);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pc5_capability_H_ */
