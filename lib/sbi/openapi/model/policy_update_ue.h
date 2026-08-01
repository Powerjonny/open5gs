/*
 * policy_update_ue.h
 *
 * Represents updated policies that the PCF provides in a notification or in the reply to an Update Request.
 */

#ifndef _OpenAPI_policy_update_ue_H_
#define _OpenAPI_policy_update_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "n2_info_content.h"
#include "pcf_ue_callback_info.h"
#include "pdu_session_info.h"
#include "policy_status.h"
#include "presence_info_rm.h"
#include "request_trigger_ue.h"
#include "ue_policy_notification.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_policy_update_ue_s OpenAPI_policy_update_ue_t;
typedef struct OpenAPI_policy_update_ue_s {
	char *resource_uri;
	char *ue_policy;
	struct OpenAPI_n2_info_content_s *n2_pc5_pol;
	struct OpenAPI_n2_info_content_s *n2_pc5_pol_a2x;
	struct OpenAPI_n2_info_content_s *n2_pc5_pro_se_pol;
	bool is_triggers_null;
	OpenAPI_list_t *triggers;
	bool is_pras_null;
	OpenAPI_list_t *pras;
	OpenAPI_policy_status_e andsp_del_ind;
	OpenAPI_list_t *deliv_report;
	bool is_pdu_sessions_null;
	OpenAPI_list_t *pdu_sessions;
	bool is_pcf_ue_info_null;
	struct OpenAPI_pcf_ue_callback_info_s *pcf_ue_info;
	bool is_match_pdus_null;
	OpenAPI_list_t *match_pdus;
	char *supp_feat;
	struct OpenAPI_n2_info_content_s *n2_pc5_rspp_pol;
} OpenAPI_policy_update_ue_t;

OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_create(
	char *resource_uri,
	char	    *
	ue_policy,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pol,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pol_a2x,
	OpenAPI_n2_info_content_t
	*
	n2_pc5_pro_se_pol,
	bool
	is_triggers_null,
	OpenAPI_list_t *
	triggers,
	bool		is_pras_null,
	OpenAPI_list_t	*pras,
	OpenAPI_policy_status_e
	andsp_del_ind,
	OpenAPI_list_t *deliv_report,
	bool
	is_pdu_sessions_null,
	OpenAPI_list_t *pdu_sessions, bool is_pcf_ue_info_null,
	OpenAPI_pcf_ue_callback_info_t *pcf_ue_info, bool is_match_pdus_null,
	OpenAPI_list_t *match_pdus, char *supp_feat,
	OpenAPI_n2_info_content_t *n2_pc5_rspp_pol);
void OpenAPI_policy_update_ue_free(
	OpenAPI_policy_update_ue_t *policy_update_ue);
OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_parseFromJSON(
	cJSON *policy_update_ueJSON);
cJSON *OpenAPI_policy_update_ue_convertToJSON(
	OpenAPI_policy_update_ue_t *policy_update_ue);
OpenAPI_policy_update_ue_t *OpenAPI_policy_update_ue_copy(
	OpenAPI_policy_update_ue_t *dst, OpenAPI_policy_update_ue_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_update_ue_H_ */
