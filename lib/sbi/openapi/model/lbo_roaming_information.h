/*
 * lbo_roaming_information.h
 *
 * Contains LBO roaming information for a DNN and S-NSSAI.
 */

#ifndef _OpenAPI_lbo_roaming_information_H_
#define _OpenAPI_lbo_roaming_information_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "snssai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_lbo_roaming_information_s
        OpenAPI_lbo_roaming_information_t;
typedef struct OpenAPI_lbo_roaming_information_s {
	bool is_lbo_roam_allowed;
	int lbo_roam_allowed;
	char *dnn;
	struct OpenAPI_snssai_s *snssai;
} OpenAPI_lbo_roaming_information_t;

OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_create(
	bool is_lbo_roam_allowed, int lbo_roam_allowed, char *dnn,
	OpenAPI_snssai_t *snssai);
void OpenAPI_lbo_roaming_information_free(
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information);
OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_parseFromJSON
        (cJSON *lbo_roaming_informationJSON);
cJSON *OpenAPI_lbo_roaming_information_convertToJSON(
	OpenAPI_lbo_roaming_information_t *lbo_roaming_information);
OpenAPI_lbo_roaming_information_t *OpenAPI_lbo_roaming_information_copy(
	OpenAPI_lbo_roaming_information_t	*dst,
	OpenAPI_lbo_roaming_information_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_lbo_roaming_information_H_ */
