/*
 * policy_status.h
 *
 *
 */

#ifndef _OpenAPI_policy_status_H_
#define _OpenAPI_policy_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_policy_status_NULL = 0, OpenAPI_policy_status_CONFIGURED,
	       OpenAPI_policy_status_NOT_CONFIGURED } OpenAPI_policy_status_e;

char * OpenAPI_policy_status_ToString(OpenAPI_policy_status_e policy_status);

OpenAPI_policy_status_e OpenAPI_policy_status_FromString(char *policy_status);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_status_H_ */
