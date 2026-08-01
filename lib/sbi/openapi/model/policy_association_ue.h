/*
 * policy_association_ue.h
 *
 *
 */

#ifndef _OpenAPI_policy_association_ue_H_
#define _OpenAPI_policy_association_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "charging_information.h"
#include "n2_info_content.h"
#include "pcf_ue_callback_info.h"
#include "pdu_session_info.h"
#include "policy_association_request_ue.h"
#include "policy_status.h"
#include "presence_info.h"
#include "request_trigger_ue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_policy_association_ue_s OpenAPI_policy_association_ue_t;
typedef struct OpenAPI_policy_association_ue_s {
	struct OpenAPI_policy_association_request_ue_s *request;
	char *ue_policy;
	struct OpenAPI_n2_info_content_s *n2_pc5_pol;
	struct OpenAPI_n2_info_content_s *n2_pc5_pol_a2x;
	struct OpenAPI_n2_info_content_s *n2_pc5_pro_se_pol;
	OpenAPI_list_t *triggers;
	OpenAPI_list_t *pras;
	OpenAPI_policy_status_e andsp_del_ind;
	bool is_andsp_ind;
	int andsp_ind;
	OpenAPI_list_t *pdu_sessions;
	struct OpenAPI_charging_information_s *chf_info;
	char *chf_group_id;
	char *supp_feat;
	struct OpenAPI_n2_info_content_s *n2_pc5_rspp_pol;
	bool is_pcf_ue_info_null;
	struct OpenAPI_pcf_ue_callback_info_s *pcf_ue_info;
	OpenAPI_list_t *match_pdus;
} OpenAPI_policy_association_ue_t;

OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_create(
	OpenAPI_policy_association_request_ue_t *request, char *ue_policy,
	OpenAPI_n2_info_content_t *n2_pc5_pol,
	OpenAPI_n2_info_content_t *n2_pc5_pol_a2x,
	OpenAPI_n2_info_content_t *n2_pc5_pro_se_pol, OpenAPI_list_t *triggers,
	OpenAPI_list_t *pras, OpenAPI_policy_status_e andsp_del_ind,
	bool is_andsp_ind, int andsp_ind, OpenAPI_list_t *pdu_sessions,
	OpenAPI_charging_information_t *chf_info, char *chf_group_id,
	char *supp_feat, OpenAPI_n2_info_content_t *n2_pc5_rspp_pol,
	bool is_pcf_ue_info_null, OpenAPI_pcf_ue_callback_info_t *pcf_ue_info,
	OpenAPI_list_t *match_pdus);
void OpenAPI_policy_association_ue_free(
	OpenAPI_policy_association_ue_t *policy_association_ue);
OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_parseFromJSON(
	cJSON *policy_association_ueJSON);
cJSON *OpenAPI_policy_association_ue_convertToJSON(
	OpenAPI_policy_association_ue_t *policy_association_ue);
OpenAPI_policy_association_ue_t *OpenAPI_policy_association_ue_copy(
	OpenAPI_policy_association_ue_t *dst,
	OpenAPI_policy_association_ue_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_association_ue_H_ */
