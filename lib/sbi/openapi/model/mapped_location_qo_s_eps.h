/*
 * mapped_location_qo_s_eps.h
 *
 * Mapped Location QoS for EPS.
 */

#ifndef _OpenAPI_mapped_location_qo_s_eps_H_
#define _OpenAPI_mapped_location_qo_s_eps_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_mapped_location_qo_s_eps_s
        OpenAPI_mapped_location_qo_s_eps_t;
typedef struct OpenAPI_mapped_location_qo_s_eps_s {
	float h_accuracy;
	bool is_v_accuracy;
	float v_accuracy;
} OpenAPI_mapped_location_qo_s_eps_t;

OpenAPI_mapped_location_qo_s_eps_t *OpenAPI_mapped_location_qo_s_eps_create(
	float h_accuracy, bool is_v_accuracy, float v_accuracy);
void OpenAPI_mapped_location_qo_s_eps_free(
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps);
OpenAPI_mapped_location_qo_s_eps_t *
OpenAPI_mapped_location_qo_s_eps_parseFromJSON(
	cJSON *mapped_location_qo_s_epsJSON);
cJSON *OpenAPI_mapped_location_qo_s_eps_convertToJSON(
	OpenAPI_mapped_location_qo_s_eps_t *mapped_location_qo_s_eps);
OpenAPI_mapped_location_qo_s_eps_t *OpenAPI_mapped_location_qo_s_eps_copy(
	OpenAPI_mapped_location_qo_s_eps_t	*dst,
	OpenAPI_mapped_location_qo_s_eps_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_mapped_location_qo_s_eps_H_ */
