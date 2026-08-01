/*
 * pro_se_capability_ue.h
 *
 *
 */

#ifndef _OpenAPI_pro_se_capability_ue_H_
#define _OpenAPI_pro_se_capability_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_pro_se_capability_ue_NULL = 0,
	       OpenAPI_pro_se_capability_ue_PROSE_DD,
	       OpenAPI_pro_se_capability_ue_PROSE_DC,
	       OpenAPI_pro_se_capability_ue_PROSE_L2_U2N_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_L3_U2N_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_L2_REMOTE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_L3_REMOTE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_L2_U2U_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_L3_U2U_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_L2_END_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_L3_END_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L2_U2N_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L3_U2N_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L2_REMOTE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L3_REMOTE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L2_INTERMEDIATE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L3_INTERMEDIATE_UE,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L3_U2U_RELAY,
	       OpenAPI_pro_se_capability_ue_PROSE_MH_L3_END_UE }
OpenAPI_pro_se_capability_ue_e;

char * OpenAPI_pro_se_capability_ue_ToString(
	OpenAPI_pro_se_capability_ue_e pro_se_capability_ue);

OpenAPI_pro_se_capability_ue_e OpenAPI_pro_se_capability_ue_FromString(
	char *pro_se_capability_ue);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pro_se_capability_ue_H_ */
