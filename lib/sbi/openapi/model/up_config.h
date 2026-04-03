/*
 * up_config.h
 *
 * UP Config
 */

#ifndef _OpenAPI_up_config_H_
#define _OpenAPI_up_config_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "lcs_up_connection_ind.h"
#include "ue_up_positioning_capabilities.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_up_config_s OpenAPI_up_config_t;
typedef struct OpenAPI_up_config_s {
	char *up_notify_call_back_uri;
	char *notif_correlation_id;
	char *supi;
	char *gpsi;
	bool is_amf_reallocation_ind;
	int amf_reallocation_ind;
	OpenAPI_lcs_up_connection_ind_e lcs_up_connection_ind;
	char *target_lmfid;
	OpenAPI_list_t *ue_up_pos_caps;
} OpenAPI_up_config_t;

OpenAPI_up_config_t *OpenAPI_up_config_create(char *up_notify_call_back_uri,
                                              char *notif_correlation_id,
                                              char *supi, char *gpsi,
                                              bool is_amf_reallocation_ind,
                                              int amf_reallocation_ind,
                                              OpenAPI_lcs_up_connection_ind_e
                                              lcs_up_connection_ind,
                                              char *target_lmfid,
                                              OpenAPI_list_t *ue_up_pos_caps);
void OpenAPI_up_config_free(OpenAPI_up_config_t *up_config);
OpenAPI_up_config_t *OpenAPI_up_config_parseFromJSON(cJSON *up_configJSON);
cJSON *OpenAPI_up_config_convertToJSON(OpenAPI_up_config_t *up_config);
OpenAPI_up_config_t *OpenAPI_up_config_copy(OpenAPI_up_config_t *dst,
                                            OpenAPI_up_config_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_up_config_H_ */
