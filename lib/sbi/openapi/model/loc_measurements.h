/*
 * loc_measurements.h
 *
 * PRU Location Measurements.
 */

#ifndef _OpenAPI_loc_measurements_H_
#define _OpenAPI_loc_measurements_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_loc_measurements_s OpenAPI_loc_measurements_t;
typedef struct OpenAPI_loc_measurements_s {
	char *loc_info;
} OpenAPI_loc_measurements_t;

OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_create(char *loc_info);
void OpenAPI_loc_measurements_free(
	OpenAPI_loc_measurements_t *loc_measurements);
OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_parseFromJSON(
	cJSON *loc_measurementsJSON);
cJSON *OpenAPI_loc_measurements_convertToJSON(
	OpenAPI_loc_measurements_t *loc_measurements);
OpenAPI_loc_measurements_t *OpenAPI_loc_measurements_copy(
	OpenAPI_loc_measurements_t *dst, OpenAPI_loc_measurements_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_loc_measurements_H_ */
