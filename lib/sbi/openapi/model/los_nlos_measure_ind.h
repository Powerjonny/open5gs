/*
 * los_nlos_measure_ind.h
 *
 *
 */

#ifndef _OpenAPI_los_nlos_measure_ind_H_
#define _OpenAPI_los_nlos_measure_ind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_los_nlos_measure_ind_NULL = 0,
	       OpenAPI_los_nlos_measure_ind_LOS,
	       OpenAPI_los_nlos_measure_ind_NLOS }
OpenAPI_los_nlos_measure_ind_e;

char * OpenAPI_los_nlos_measure_ind_ToString(
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind);

OpenAPI_los_nlos_measure_ind_e OpenAPI_los_nlos_measure_ind_FromString(
	char *los_nlos_measure_ind);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_los_nlos_measure_ind_H_ */
