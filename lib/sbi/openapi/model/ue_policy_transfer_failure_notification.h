/*
 * ue_policy_transfer_failure_notification.h
 *
 * Represents information on the failure of a UE policy transfer to the UE because the UE is not reachable.
 */

#ifndef _OpenAPI_ue_policy_transfer_failure_notification_H_
#define _OpenAPI_ue_policy_transfer_failure_notification_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ue_policy_transfer_failure_cause.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ue_policy_transfer_failure_notification_s
        OpenAPI_ue_policy_transfer_failure_notification_t;
typedef struct OpenAPI_ue_policy_transfer_failure_notification_s {
	struct OpenAPI_ue_policy_transfer_failure_cause_s *cause;
	bool is_retry_after;
	int retry_after;
	OpenAPI_list_t *ptis;
} OpenAPI_ue_policy_transfer_failure_notification_t;

OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_create(
	OpenAPI_ue_policy_transfer_failure_cause_t *cause, bool is_retry_after,
	int retry_after, OpenAPI_list_t *ptis);
void OpenAPI_ue_policy_transfer_failure_notification_free(
	OpenAPI_ue_policy_transfer_failure_notification_t *
	ue_policy_transfer_failure_notification);
OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON(
	cJSON *ue_policy_transfer_failure_notificationJSON);
cJSON *OpenAPI_ue_policy_transfer_failure_notification_convertToJSON(
	OpenAPI_ue_policy_transfer_failure_notification_t *
	ue_policy_transfer_failure_notification);
OpenAPI_ue_policy_transfer_failure_notification_t *
OpenAPI_ue_policy_transfer_failure_notification_copy(
	OpenAPI_ue_policy_transfer_failure_notification_t	*dst,
	OpenAPI_ue_policy_transfer_failure_notification_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_policy_transfer_failure_notification_H_ */
