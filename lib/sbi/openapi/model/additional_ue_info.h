/*
 * additional_ue_info.h
 *
 * MBSR UE or MWAB UE Information
 */

#ifndef _OpenAPI_additional_ue_info_H_
#define _OpenAPI_additional_ue_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ncgi.h"
#include "tai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_additional_ue_info_s OpenAPI_additional_ue_info_t;
typedef struct OpenAPI_additional_ue_info_s {
	struct OpenAPI_ncgi_s *ncgi;
	struct OpenAPI_tai_s *tai;
} OpenAPI_additional_ue_info_t;

OpenAPI_additional_ue_info_t *OpenAPI_additional_ue_info_create(
	OpenAPI_ncgi_t *ncgi, OpenAPI_tai_t *tai);
void OpenAPI_additional_ue_info_free(
	OpenAPI_additional_ue_info_t *additional_ue_info);
OpenAPI_additional_ue_info_t *OpenAPI_additional_ue_info_parseFromJSON(
	cJSON *additional_ue_infoJSON);
cJSON *OpenAPI_additional_ue_info_convertToJSON(
	OpenAPI_additional_ue_info_t *additional_ue_info);
OpenAPI_additional_ue_info_t *OpenAPI_additional_ue_info_copy(
	OpenAPI_additional_ue_info_t *dst, OpenAPI_additional_ue_info_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_additional_ue_info_H_ */
