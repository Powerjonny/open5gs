/*
 * indoor_outdoor_ind.h
 *
 *
 */

#ifndef _OpenAPI_indoor_outdoor_ind_H_
#define _OpenAPI_indoor_outdoor_ind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_indoor_outdoor_ind_NULL = 0,
	       OpenAPI_indoor_outdoor_ind_INDOOR,
	       OpenAPI_indoor_outdoor_ind_OUTDOOR } OpenAPI_indoor_outdoor_ind_e;

char * OpenAPI_indoor_outdoor_ind_ToString(
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind);

OpenAPI_indoor_outdoor_ind_e OpenAPI_indoor_outdoor_ind_FromString(
	char *indoor_outdoor_ind);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_indoor_outdoor_ind_H_ */
