/*
 * loc_measurement_req.h
 *
 * Location Measurement Request.
 */

#ifndef _OpenAPI_loc_measurement_req_H_
#define _OpenAPI_loc_measurement_req_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ecgi.h"
#include "geographic_area.h"
#include "ncgi.h"
#include "positioning_method.h"
#include "time_windows_nrppa.h"
#include "trp_parameter.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_loc_measurement_req_s OpenAPI_loc_measurement_req_t;
typedef struct OpenAPI_loc_measurement_req_s {
	struct OpenAPI_ncgi_s *ncgi;
	struct OpenAPI_ecgi_s *ecgi;
	struct OpenAPI_geographic_area_s *pre_calcu_loc_estimate;
	char *timestamp_of_pre_calcu_loc_estimate;
	OpenAPI_list_t *time_windows;
	struct OpenAPI_time_windows_nrppa_s *time_windows_nrppa;
	OpenAPI_positioning_method_e method;
	OpenAPI_list_t *trp_parameters;
} OpenAPI_loc_measurement_req_t;

OpenAPI_loc_measurement_req_t *OpenAPI_loc_measurement_req_create(
	OpenAPI_ncgi_t *ncgi, OpenAPI_ecgi_t *ecgi,
	OpenAPI_geographic_area_t *pre_calcu_loc_estimate,
	char *timestamp_of_pre_calcu_loc_estimate, OpenAPI_list_t *time_windows,
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa,
	OpenAPI_positioning_method_e method, OpenAPI_list_t *trp_parameters);
void OpenAPI_loc_measurement_req_free(
	OpenAPI_loc_measurement_req_t *loc_measurement_req);
OpenAPI_loc_measurement_req_t *OpenAPI_loc_measurement_req_parseFromJSON(
	cJSON *loc_measurement_reqJSON);
cJSON *OpenAPI_loc_measurement_req_convertToJSON(
	OpenAPI_loc_measurement_req_t *loc_measurement_req);
OpenAPI_loc_measurement_req_t *OpenAPI_loc_measurement_req_copy(
	OpenAPI_loc_measurement_req_t *dst, OpenAPI_loc_measurement_req_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_loc_measurement_req_H_ */
