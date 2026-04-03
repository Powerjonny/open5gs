/*
 * up_notify_data.h
 *
 * UP Subscription
 */

#ifndef _OpenAPI_up_notify_data_H_
#define _OpenAPI_up_notify_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "up_connection_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_up_notify_data_s OpenAPI_up_notify_data_t;
typedef struct OpenAPI_up_notify_data_s {
	char *notif_correlation_id;
	OpenAPI_up_connection_status_e up_connection_status;
	char *target_lmfid;
} OpenAPI_up_notify_data_t;

OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_create(
	char				*notif_correlation_id,
	OpenAPI_up_connection_status_e	up_connection_status,
	char				*target_lmfid);
void OpenAPI_up_notify_data_free(OpenAPI_up_notify_data_t *up_notify_data);
OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_parseFromJSON(
	cJSON *up_notify_dataJSON);
cJSON *OpenAPI_up_notify_data_convertToJSON(
	OpenAPI_up_notify_data_t *up_notify_data);
OpenAPI_up_notify_data_t *OpenAPI_up_notify_data_copy(
	OpenAPI_up_notify_data_t *dst, OpenAPI_up_notify_data_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_up_notify_data_H_ */
