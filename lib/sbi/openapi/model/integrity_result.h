/*
 * integrity_result.h
 *
 * Integrity Result.
 */

#ifndef _OpenAPI_integrity_result_H_
#define _OpenAPI_integrity_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "integrity_computing_entity.h"
#include "integrity_protection_level.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_integrity_result_s OpenAPI_integrity_result_t;
typedef struct OpenAPI_integrity_result_s {
	struct OpenAPI_integrity_computing_entity_s *computing_entity;
	struct OpenAPI_integrity_protection_level_s *protection_level;
	bool is_integrity_req_met_ind;
	int integrity_req_met_ind;
	bool is_achieved_tir;
	int achieved_tir;
} OpenAPI_integrity_result_t;

OpenAPI_integrity_result_t *OpenAPI_integrity_result_create(
	OpenAPI_integrity_computing_entity_t *computing_entity,
	OpenAPI_integrity_protection_level_t *protection_level,
	bool is_integrity_req_met_ind, int integrity_req_met_ind,
	bool is_achieved_tir, int achieved_tir);
void OpenAPI_integrity_result_free(
	OpenAPI_integrity_result_t *integrity_result);
OpenAPI_integrity_result_t *OpenAPI_integrity_result_parseFromJSON(
	cJSON *integrity_resultJSON);
cJSON *OpenAPI_integrity_result_convertToJSON(
	OpenAPI_integrity_result_t *integrity_result);
OpenAPI_integrity_result_t *OpenAPI_integrity_result_copy(
	OpenAPI_integrity_result_t *dst, OpenAPI_integrity_result_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_integrity_result_H_ */
