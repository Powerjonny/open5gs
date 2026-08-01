/*
 * failure.h
 *
 * Possible values are: - UNSPECIFIED: Indicates the PCF received the UE sent UE policy delivery service cause #111   (Protocol error, unspecified). - UE_NOT_REACHABLE: Indicates the PCF received the notification from the AMF that the UE is   not reachable. - UNKNOWN: Indicates unknown reasons upon no response from the UE, e.g. UPDS message type is   not defined or not implemented by the UE, or not compatible with the UPDS state, in which   the UE shall ignore the UPDS message. - UE_TEMP_UNREACHABLE: Indicates the PCF received the notification from the AMF that the UE   is not reachable but the PCF will retry again.
 */

#ifndef _OpenAPI_failure_H_
#define _OpenAPI_failure_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "failure_one_of.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_failure_s OpenAPI_failure_t;
typedef struct OpenAPI_failure_s {} OpenAPI_failure_t;

OpenAPI_failure_t *OpenAPI_failure_create();
void OpenAPI_failure_free(OpenAPI_failure_t *failure);
OpenAPI_failure_t *OpenAPI_failure_parseFromJSON(cJSON *failureJSON);
cJSON *OpenAPI_failure_convertToJSON(OpenAPI_failure_t *failure);
OpenAPI_failure_t *OpenAPI_failure_copy(OpenAPI_failure_t	*dst,
                                        OpenAPI_failure_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_failure_H_ */
