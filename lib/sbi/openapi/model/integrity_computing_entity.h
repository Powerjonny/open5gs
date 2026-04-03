/*
 * integrity_computing_entity.h
 *
 * Integrity Computing Entity. Possible values are: - UE: The integrity result was calculated (and determined) by UE. - LMF: The integrity result was calculated (and determined) by LMF. - BOTH: The integrity result was calculated (and determined) by both UE and LMF.
 */

#ifndef _OpenAPI_integrity_computing_entity_H_
#define _OpenAPI_integrity_computing_entity_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "integrity_computing_entity_any_of.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_integrity_computing_entity_s
        OpenAPI_integrity_computing_entity_t;
typedef struct OpenAPI_integrity_computing_entity_s {}
OpenAPI_integrity_computing_entity_t;

OpenAPI_integrity_computing_entity_t *OpenAPI_integrity_computing_entity_create(void);
void OpenAPI_integrity_computing_entity_free(
	OpenAPI_integrity_computing_entity_t *integrity_computing_entity);
OpenAPI_integrity_computing_entity_t *
OpenAPI_integrity_computing_entity_parseFromJSON(
	cJSON *integrity_computing_entityJSON);
cJSON *OpenAPI_integrity_computing_entity_convertToJSON(
	OpenAPI_integrity_computing_entity_t *integrity_computing_entity);
OpenAPI_integrity_computing_entity_t *OpenAPI_integrity_computing_entity_copy(
	OpenAPI_integrity_computing_entity_t	*dst,
	OpenAPI_integrity_computing_entity_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_integrity_computing_entity_H_ */
