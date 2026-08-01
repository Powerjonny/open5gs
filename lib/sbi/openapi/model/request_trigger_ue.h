/*
 * request_trigger_ue.h
 *
 *
 */

#ifndef _OpenAPI_request_trigger_ue_H_
#define _OpenAPI_request_trigger_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_request_trigger_ue_NULL = 0,
	       OpenAPI_request_trigger_ue_LOC_CH,
	       OpenAPI_request_trigger_ue_PRA_CH,
	       OpenAPI_request_trigger_ue_UE_POLICY,
	       OpenAPI_request_trigger_ue_PLMN_CH,
	       OpenAPI_request_trigger_ue_CON_STATE_CH,
	       OpenAPI_request_trigger_ue_GROUP_ID_LIST_CHG,
	       OpenAPI_request_trigger_ue_UE_CAP_CH,
	       OpenAPI_request_trigger_ue_SAT_CATEGORY_CHG,
	       OpenAPI_request_trigger_ue_NON_3GPP_NODE_RESELECTION,
	       OpenAPI_request_trigger_ue_CONF_NSSAI_CH,
	       OpenAPI_request_trigger_ue_LBO_INFO_CH,
	       OpenAPI_request_trigger_ue_FEAT_RENEG,
	       OpenAPI_request_trigger_ue_URSP_ENF_INFO,
	       OpenAPI_request_trigger_ue_ACCESS_TYPE_CH }
OpenAPI_request_trigger_ue_e;

char * OpenAPI_request_trigger_ue_ToString(
	OpenAPI_request_trigger_ue_e request_trigger_ue);

OpenAPI_request_trigger_ue_e OpenAPI_request_trigger_ue_FromString(
	char *request_trigger_ue);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_request_trigger_ue_H_ */
