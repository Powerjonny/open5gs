/*
 * rang_sl_capability.h
 *
 *
 */

#ifndef _OpenAPI_rang_sl_capability_H_
#define _OpenAPI_rang_sl_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_rang_sl_capability_NULL = 0,
	       OpenAPI_rang_sl_capability_PC5_RANGING_SL }
OpenAPI_rang_sl_capability_e;

char * OpenAPI_rang_sl_capability_ToString(
	OpenAPI_rang_sl_capability_e rang_sl_capability);

OpenAPI_rang_sl_capability_e OpenAPI_rang_sl_capability_FromString(
	char *rang_sl_capability);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_rang_sl_capability_H_ */
