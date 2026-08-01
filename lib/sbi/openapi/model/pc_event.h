/*
 * pc_event.h
 *
 * Represents the policy control events that can be subscribed.
 */

#ifndef _OpenAPI_pc_event_H_
#define _OpenAPI_pc_event_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "pc_event_any_of.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_pc_event_s OpenAPI_pc_event_t;
typedef struct OpenAPI_pc_event_s {} OpenAPI_pc_event_t;

OpenAPI_pc_event_t *OpenAPI_pc_event_create();
void OpenAPI_pc_event_free(OpenAPI_pc_event_t *pc_event);
OpenAPI_pc_event_t *OpenAPI_pc_event_parseFromJSON(cJSON *pc_eventJSON);
cJSON *OpenAPI_pc_event_convertToJSON(OpenAPI_pc_event_t *pc_event);
OpenAPI_pc_event_t *OpenAPI_pc_event_copy(OpenAPI_pc_event_t	*dst,
                                          OpenAPI_pc_event_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pc_event_H_ */
