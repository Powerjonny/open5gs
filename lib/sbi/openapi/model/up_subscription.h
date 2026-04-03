/*
 * up_subscription.h
 *
 * UP Subscription
 */

#ifndef _OpenAPI_up_subscription_H_
#define _OpenAPI_up_subscription_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_up_subscription_s OpenAPI_up_subscription_t;
typedef struct OpenAPI_up_subscription_s {
	char *up_notify_call_back_uri;
	char *notif_correlation_id;
	char *supi;
	char *gpsi;
} OpenAPI_up_subscription_t;

OpenAPI_up_subscription_t *OpenAPI_up_subscription_create(
	char *up_notify_call_back_uri, char *notif_correlation_id, char *supi,
	char *gpsi);
void OpenAPI_up_subscription_free(OpenAPI_up_subscription_t *up_subscription);
OpenAPI_up_subscription_t *OpenAPI_up_subscription_parseFromJSON(
	cJSON *up_subscriptionJSON);
cJSON *OpenAPI_up_subscription_convertToJSON(
	OpenAPI_up_subscription_t *up_subscription);
OpenAPI_up_subscription_t *OpenAPI_up_subscription_copy(
	OpenAPI_up_subscription_t *dst, OpenAPI_up_subscription_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_up_subscription_H_ */
