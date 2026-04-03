/*
 * alert_limit.h
 *
 * Alert Limit.
 */

#ifndef _OpenAPI_alert_limit_H_
#define _OpenAPI_alert_limit_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_alert_limit_s OpenAPI_alert_limit_t;
typedef struct OpenAPI_alert_limit_s {
	int horizontal_protection_level;
	bool is_vertical_protection_level;
	int vertical_protection_level;
} OpenAPI_alert_limit_t;

OpenAPI_alert_limit_t *OpenAPI_alert_limit_create(
	int horizontal_protection_level, bool is_vertical_protection_level,
	int vertical_protection_level);
void OpenAPI_alert_limit_free(OpenAPI_alert_limit_t *alert_limit);
OpenAPI_alert_limit_t *OpenAPI_alert_limit_parseFromJSON(
	cJSON *alert_limitJSON);
cJSON *OpenAPI_alert_limit_convertToJSON(OpenAPI_alert_limit_t *alert_limit);
OpenAPI_alert_limit_t *OpenAPI_alert_limit_copy(OpenAPI_alert_limit_t	*dst,
                                                OpenAPI_alert_limit_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_alert_limit_H_ */
