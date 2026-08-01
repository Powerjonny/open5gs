/*
 * failure_one_of.h
 *
 *
 */

#ifndef _OpenAPI_failure_one_of_H_
#define _OpenAPI_failure_one_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_failure_one_of_NULL = 0,
	       OpenAPI_failure_one_of_UNSPECIFIED,
	       OpenAPI_failure_one_of_UE_NOT_REACHABLE,
	       OpenAPI_failure_one_of_UNKNOWN,
	       OpenAPI_failure_one_of_UE_TEMP_UNREACHABLE }
OpenAPI_failure_one_of_e;

char * OpenAPI_failure_one_of_ToString(OpenAPI_failure_one_of_e failure_one_of);

OpenAPI_failure_one_of_e OpenAPI_failure_one_of_FromString(
	char *failure_one_of);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_failure_one_of_H_ */
