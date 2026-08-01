/*
 * ue_policy_notification.h
 *
 * Contains the delivery outcome of VPLMN-specific URSP rules.
 */

#ifndef _OpenAPI_ue_policy_notification_H_
#define _OpenAPI_ue_policy_notification_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "pc_event_notification.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ue_policy_notification_s OpenAPI_ue_policy_notification_t;
typedef struct OpenAPI_ue_policy_notification_s {
	OpenAPI_list_t *event_notifs;
} OpenAPI_ue_policy_notification_t;

OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_create(
	OpenAPI_list_t *event_notifs);
void OpenAPI_ue_policy_notification_free(
	OpenAPI_ue_policy_notification_t *ue_policy_notification);
OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_parseFromJSON(
	cJSON *ue_policy_notificationJSON);
cJSON *OpenAPI_ue_policy_notification_convertToJSON(
	OpenAPI_ue_policy_notification_t *ue_policy_notification);
OpenAPI_ue_policy_notification_t *OpenAPI_ue_policy_notification_copy(
	OpenAPI_ue_policy_notification_t	*dst,
	OpenAPI_ue_policy_notification_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_policy_notification_H_ */
