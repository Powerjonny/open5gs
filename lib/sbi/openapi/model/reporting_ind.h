/*
 * reporting_ind.h
 *
 * Indicates whether the UE is allowed to generate and send the event report inside or outside the event report allowed(expected) area. Possible values are: - INSIDE_REPORTING: Reporting when UE is inside the event report allowed/expected area. - OUTSIDE_REPORTING: Reporting when UE is outside the event report allowed/expected area.
 */

#ifndef _OpenAPI_reporting_ind_H_
#define _OpenAPI_reporting_ind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "reporting_ind_any_of.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_reporting_ind_s OpenAPI_reporting_ind_t;
typedef struct OpenAPI_reporting_ind_s {} OpenAPI_reporting_ind_t;

OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_create();
void OpenAPI_reporting_ind_free(OpenAPI_reporting_ind_t *reporting_ind);
OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_parseFromJSON(
	cJSON *reporting_indJSON);
cJSON *OpenAPI_reporting_ind_convertToJSON(
	OpenAPI_reporting_ind_t *reporting_ind);
OpenAPI_reporting_ind_t *OpenAPI_reporting_ind_copy(
	OpenAPI_reporting_ind_t *dst, OpenAPI_reporting_ind_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_reporting_ind_H_ */
