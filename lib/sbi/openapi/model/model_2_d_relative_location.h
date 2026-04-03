/*
 * model_2_d_relative_location.h
 *
 * Represents a relative 2D location with uncertainty ellipse.
 */

#ifndef _OpenAPI_model_2_d_relative_location_H_
#define _OpenAPI_model_2_d_relative_location_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_model_2_d_relative_location_s
        OpenAPI_model_2_d_relative_location_t;
typedef struct OpenAPI_model_2_d_relative_location_s {
	bool is_semi_minor;
	float semi_minor;
	bool is_semi_major;
	float semi_major;
	bool is_orientation_angle;
	int orientation_angle;
} OpenAPI_model_2_d_relative_location_t;

OpenAPI_model_2_d_relative_location_t *
OpenAPI_model_2_d_relative_location_create(bool is_semi_minor, float semi_minor,
                                           bool is_semi_major, float semi_major,
                                           bool is_orientation_angle,
                                           int orientation_angle);
void OpenAPI_model_2_d_relative_location_free(
	OpenAPI_model_2_d_relative_location_t *model_2_d_relative_location);
OpenAPI_model_2_d_relative_location_t *
OpenAPI_model_2_d_relative_location_parseFromJSON(
	cJSON *model_2_d_relative_locationJSON);
cJSON *OpenAPI_model_2_d_relative_location_convertToJSON(
	OpenAPI_model_2_d_relative_location_t *model_2_d_relative_location);
OpenAPI_model_2_d_relative_location_t *OpenAPI_model_2_d_relative_location_copy(
	OpenAPI_model_2_d_relative_location_t	*dst,
	OpenAPI_model_2_d_relative_location_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_model_2_d_relative_location_H_ */
