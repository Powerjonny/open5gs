/*
 * sl_positioning_capability.h
 *
 *
 */

#ifndef _OpenAPI_sl_positioning_capability_H_
#define _OpenAPI_sl_positioning_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_sl_positioning_capability_NULL = 0,
	       OpenAPI_sl_positioning_capability_V2X,
	       OpenAPI_sl_positioning_capability__5G_PROSE }
OpenAPI_sl_positioning_capability_e;

char * OpenAPI_sl_positioning_capability_ToString(
	OpenAPI_sl_positioning_capability_e sl_positioning_capability);

OpenAPI_sl_positioning_capability_e OpenAPI_sl_positioning_capability_FromString
        (char *sl_positioning_capability);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_sl_positioning_capability_H_ */
