/*
 * integrity_requirements.h
 *
 * integrity requirements.
 */

#ifndef _OpenAPI_integrity_requirements_H_
#define _OpenAPI_integrity_requirements_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "alert_limit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_integrity_requirements_s OpenAPI_integrity_requirements_t;
typedef struct OpenAPI_integrity_requirements_s {
	bool is_time_to_alert;
	int time_to_alert;
	bool is_target_integrity_risk;
	int target_integrity_risk;
	struct OpenAPI_alert_limit_s *alert_limit;
} OpenAPI_integrity_requirements_t;

OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_create(
	bool is_time_to_alert, int time_to_alert, bool is_target_integrity_risk,
	int target_integrity_risk, OpenAPI_alert_limit_t *alert_limit);
void OpenAPI_integrity_requirements_free(
	OpenAPI_integrity_requirements_t *integrity_requirements);
OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_parseFromJSON(
	cJSON *integrity_requirementsJSON);
cJSON *OpenAPI_integrity_requirements_convertToJSON(
	OpenAPI_integrity_requirements_t *integrity_requirements);
OpenAPI_integrity_requirements_t *OpenAPI_integrity_requirements_copy(
	OpenAPI_integrity_requirements_t	*dst,
	OpenAPI_integrity_requirements_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_integrity_requirements_H_ */
