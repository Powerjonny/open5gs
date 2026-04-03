/*
 * integrity_protection_level.h
 *
 * Integrity Protection Level.
 */

#ifndef _OpenAPI_integrity_protection_level_H_
#define _OpenAPI_integrity_protection_level_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_integrity_protection_level_s
        OpenAPI_integrity_protection_level_t;
typedef struct OpenAPI_integrity_protection_level_s {
	int horizontal_protection_level;
	bool is_vertical_protection_level;
	int vertical_protection_level;
} OpenAPI_integrity_protection_level_t;

OpenAPI_integrity_protection_level_t *OpenAPI_integrity_protection_level_create(
	int horizontal_protection_level, bool is_vertical_protection_level,
	int vertical_protection_level);
void OpenAPI_integrity_protection_level_free(
	OpenAPI_integrity_protection_level_t *integrity_protection_level);
OpenAPI_integrity_protection_level_t *
OpenAPI_integrity_protection_level_parseFromJSON(
	cJSON *integrity_protection_levelJSON);
cJSON *OpenAPI_integrity_protection_level_convertToJSON(
	OpenAPI_integrity_protection_level_t *integrity_protection_level);
OpenAPI_integrity_protection_level_t *OpenAPI_integrity_protection_level_copy(
	OpenAPI_integrity_protection_level_t	*dst,
	OpenAPI_integrity_protection_level_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_integrity_protection_level_H_ */
