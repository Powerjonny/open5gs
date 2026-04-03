/*
 * related_ue.h
 *
 * Related UE Information
 */

#ifndef _OpenAPI_related_ue_H_
#define _OpenAPI_related_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "related_ue_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_related_ue_s OpenAPI_related_ue_t;
typedef struct OpenAPI_related_ue_s {
	char *applicationlayer_id;
	OpenAPI_related_ue_type_e related_ue_type;
} OpenAPI_related_ue_t;

OpenAPI_related_ue_t *OpenAPI_related_ue_create(
	char *applicationlayer_id,
	OpenAPI_related_ue_type_e
	related_ue_type);
void OpenAPI_related_ue_free(OpenAPI_related_ue_t *related_ue);
OpenAPI_related_ue_t *OpenAPI_related_ue_parseFromJSON(cJSON *related_ueJSON);
cJSON *OpenAPI_related_ue_convertToJSON(OpenAPI_related_ue_t *related_ue);
OpenAPI_related_ue_t *OpenAPI_related_ue_copy(OpenAPI_related_ue_t	*dst,
                                              OpenAPI_related_ue_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_related_ue_H_ */
