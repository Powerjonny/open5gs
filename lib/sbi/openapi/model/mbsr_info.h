/*
 * mbsr_info.h
 *
 * MBSR Information
 */

#ifndef _OpenAPI_mbsr_info_H_
#define _OpenAPI_mbsr_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ecgi.h"
#include "ncgi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_mbsr_info_s OpenAPI_mbsr_info_t;
typedef struct OpenAPI_mbsr_info_s {
	struct OpenAPI_ncgi_s *ncgi;
	struct OpenAPI_ecgi_s *ecgi;
} OpenAPI_mbsr_info_t;

OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_create(OpenAPI_ncgi_t	*ncgi,
                                              OpenAPI_ecgi_t	*ecgi);
void OpenAPI_mbsr_info_free(OpenAPI_mbsr_info_t *mbsr_info);
OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_parseFromJSON(cJSON *mbsr_infoJSON);
cJSON *OpenAPI_mbsr_info_convertToJSON(OpenAPI_mbsr_info_t *mbsr_info);
OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_copy(OpenAPI_mbsr_info_t *dst,
                                            OpenAPI_mbsr_info_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_mbsr_info_H_ */
