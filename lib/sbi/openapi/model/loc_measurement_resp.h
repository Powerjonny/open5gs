/*
 * loc_measurement_resp.h
 *
 * Location Measurement Response.
 */

#ifndef _OpenAPI_loc_measurement_resp_H_
#define _OpenAPI_loc_measurement_resp_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "loc_measurements.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_loc_measurement_resp_s OpenAPI_loc_measurement_resp_t;
typedef struct OpenAPI_loc_measurement_resp_s {
	OpenAPI_list_t *loc_measurements;
} OpenAPI_loc_measurement_resp_t;

OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_create(
	OpenAPI_list_t *loc_measurements);
void OpenAPI_loc_measurement_resp_free(
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp);
OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_parseFromJSON(
	cJSON *loc_measurement_respJSON);
cJSON *OpenAPI_loc_measurement_resp_convertToJSON(
	OpenAPI_loc_measurement_resp_t *loc_measurement_resp);
OpenAPI_loc_measurement_resp_t *OpenAPI_loc_measurement_resp_copy(
	OpenAPI_loc_measurement_resp_t	*dst,
	OpenAPI_loc_measurement_resp_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_loc_measurement_resp_H_ */
