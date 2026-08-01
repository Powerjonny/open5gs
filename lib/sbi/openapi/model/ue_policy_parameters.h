/*
 * ue_policy_parameters.h
 *
 * Contains the service parameters used to guide the VPLMN-specific URSP rule determination.
 */

#ifndef _OpenAPI_ue_policy_parameters_H_
#define _OpenAPI_ue_policy_parameters_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "event.h"
#include "ursp_rule_request.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ue_policy_parameters_s OpenAPI_ue_policy_parameters_t;
typedef struct OpenAPI_ue_policy_parameters_s {
	OpenAPI_list_t *ursp_guidance;
	bool is_delivery_events_null;
	OpenAPI_list_t *delivery_events;
} OpenAPI_ue_policy_parameters_t;

OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_create(
	OpenAPI_list_t *ursp_guidance, bool is_delivery_events_null,
	OpenAPI_list_t *delivery_events);
void OpenAPI_ue_policy_parameters_free(
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters);
OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_parseFromJSON(
	cJSON *ue_policy_parametersJSON);
cJSON *OpenAPI_ue_policy_parameters_convertToJSON(
	OpenAPI_ue_policy_parameters_t *ue_policy_parameters);
OpenAPI_ue_policy_parameters_t *OpenAPI_ue_policy_parameters_copy(
	OpenAPI_ue_policy_parameters_t	*dst,
	OpenAPI_ue_policy_parameters_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_policy_parameters_H_ */
