/*
 * ranging_sl_result.h
 *
 *
 */

#ifndef _OpenAPI_ranging_sl_result_H_
#define _OpenAPI_ranging_sl_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_ranging_sl_result_NULL = 0,
	       OpenAPI_ranging_sl_result_ABSOLUTE_LOCATION,
	       OpenAPI_ranging_sl_result_RELATIVE_LOCATION,
	       OpenAPI_ranging_sl_result_RANGING_DIRECTION,
	       OpenAPI_ranging_sl_result_RANGING,
	       OpenAPI_ranging_sl_result_DIRECTION,
	       OpenAPI_ranging_sl_result_VELOCITY,
	       OpenAPI_ranging_sl_result_RELATIVE_VELOCITY }
OpenAPI_ranging_sl_result_e;

char * OpenAPI_ranging_sl_result_ToString(
	OpenAPI_ranging_sl_result_e ranging_sl_result);

OpenAPI_ranging_sl_result_e OpenAPI_ranging_sl_result_FromString(
	char *ranging_sl_result);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ranging_sl_result_H_ */
