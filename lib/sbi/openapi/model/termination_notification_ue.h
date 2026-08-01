/*
 * termination_notification_ue.h
 *
 * Represents a request to terminate a policy association that the PCF provides in a notification.
 */

#ifndef _OpenAPI_termination_notification_ue_H_
#define _OpenAPI_termination_notification_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "policy_association_release_cause_ue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_termination_notification_ue_s
        OpenAPI_termination_notification_ue_t;
typedef struct OpenAPI_termination_notification_ue_s {
	char *resource_uri;
	OpenAPI_policy_association_release_cause_ue_e cause;
} OpenAPI_termination_notification_ue_t;

OpenAPI_termination_notification_ue_t *
OpenAPI_termination_notification_ue_create(
	char *resource_uri,
	OpenAPI_policy_association_release_cause_ue_e
	cause);
void OpenAPI_termination_notification_ue_free(
	OpenAPI_termination_notification_ue_t *termination_notification_ue);
OpenAPI_termination_notification_ue_t *
OpenAPI_termination_notification_ue_parseFromJSON(
	cJSON *termination_notification_ueJSON);
cJSON *OpenAPI_termination_notification_ue_convertToJSON(
	OpenAPI_termination_notification_ue_t *termination_notification_ue);
OpenAPI_termination_notification_ue_t *OpenAPI_termination_notification_ue_copy(
	OpenAPI_termination_notification_ue_t	*dst,
	OpenAPI_termination_notification_ue_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_termination_notification_ue_H_ */
