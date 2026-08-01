/*
 * policy_association_update_request_ue.h
 *
 * Represents Information that the NF service consumer provides when requesting the update of a policy association.
 */

#ifndef _OpenAPI_policy_association_update_request_ue_H_
#define _OpenAPI_policy_association_update_request_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "a2x_capability.h"
#include "access_type.h"
#include "cm_state.h"
#include "configured_snssai.h"
#include "guami.h"
#include "lbo_roaming_information.h"
#include "non3gpp_access.h"
#include "pc5_capability.h"
#include "plmn_id_nid.h"
#include "presence_info.h"
#include "pro_se_capability_ue.h"
#include "rang_sl_capability.h"
#include "rat_type.h"
#include "request_trigger_ue.h"
#include "satellite_backhaul_category.h"
#include "slice_specific_n3g_node_selection_capability.h"
#include "ue_policy_parameters.h"
#include "ue_policy_transfer_failure_notification.h"
#include "ursp_enforcement_pdu_session.h"
#include "user_location.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_policy_association_update_request_ue_s
        OpenAPI_policy_association_update_request_ue_t;
typedef struct OpenAPI_policy_association_update_request_ue_s {
	char *notification_uri;
	OpenAPI_list_t *alt_notif_ipv4_addrs;
	OpenAPI_list_t *alt_notif_ipv6_addrs;
	OpenAPI_list_t *alt_notif_fqdns;
	OpenAPI_list_t *triggers;
	OpenAPI_list_t *pra_statuses;
	struct OpenAPI_user_location_s *user_loc;
	char *ue_pol_del_result;
	struct OpenAPI_ue_policy_transfer_failure_notification_s *
	        ue_pol_trans_fail_notif;
	char *ue_pol_req;
	struct OpenAPI_guami_s *guami;
	char *serving_nf_id;
	struct OpenAPI_plmn_id_nid_s *plmn_id;
	struct OpenAPI_cm_state_s *connect_state;
	OpenAPI_list_t *group_ids;
	OpenAPI_pc5_capability_e pc5_capab;
	OpenAPI_list_t *a2x_capab;
	OpenAPI_list_t *pro_se_capab;
	OpenAPI_list_t *conf_snssais;
	OpenAPI_non3gpp_access_e n3g_node_re_sel;
	OpenAPI_slice_specific_n3g_node_selection_capability_e
	        slice_n3g_node_sel_cap;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category;
	OpenAPI_list_t *ursp_enf_rep;
	bool is_vps_ue_pol_guidance_null;
	OpenAPI_list_t *vps_ue_pol_guidance;
	OpenAPI_list_t *lbo_roam_info;
	OpenAPI_list_t *access_types;
	OpenAPI_list_t *rat_types;
	char *supp_feat;
	OpenAPI_list_t *rang_sl_capab;
} OpenAPI_policy_association_update_request_ue_t;

OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_create(char *notification_uri,
                                                    OpenAPI_list_t *
                                                    alt_notif_ipv4_addrs,
                                                    OpenAPI_list_t *
                                                    alt_notif_ipv6_addrs,
                                                    OpenAPI_list_t *
                                                    alt_notif_fqdns,
                                                    OpenAPI_list_t	*
                                                        triggers,
                                                    OpenAPI_list_t	*
                                                        pra_statuses,
                                                    OpenAPI_user_location_t *
                                                    user_loc,
                                                    char		*
                                                                        ue_pol_del_result,
                                                    OpenAPI_ue_policy_transfer_failure_notification_t
                                                    *
                                                                        ue_pol_trans_fail_notif,
                                                    char		*
                                                                        ue_pol_req,
                                                    OpenAPI_guami_t	*guami,
                                                    char		*
                                                    serving_nf_id,
                                                    OpenAPI_plmn_id_nid_t *
                                                    plmn_id,
                                                    OpenAPI_cm_state_t *
                                                    connect_state,
                                                    OpenAPI_list_t *group_ids,
                                                    OpenAPI_pc5_capability_e
                                                    pc5_capab,
                                                    OpenAPI_list_t
                                                        *a2x_capab,
                                                    OpenAPI_list_t
                                                        *pro_se_capab,
                                                    OpenAPI_list_t
                                                        *conf_snssais,
                                                    OpenAPI_non3gpp_access_e
                                                    n3g_node_re_sel,
                                                    OpenAPI_slice_specific_n3g_node_selection_capability_e
                                                    slice_n3g_node_sel_cap,
                                                    OpenAPI_satellite_backhaul_category_e
                                                    sat_backhaul_category,
                                                    OpenAPI_list_t *ursp_enf_rep,
                                                    bool
                                                    is_vps_ue_pol_guidance_null,
                                                    OpenAPI_list_t *
                                                    vps_ue_pol_guidance,
                                                    OpenAPI_list_t *
                                                    lbo_roam_info,
                                                    OpenAPI_list_t	*
                                                        access_types,
                                                    OpenAPI_list_t	*
                                                        rat_types,
                                                    char		*
                                                        supp_feat,
                                                    OpenAPI_list_t	*
                                                        rang_sl_capab);
void OpenAPI_policy_association_update_request_ue_free(
	OpenAPI_policy_association_update_request_ue_t *
	policy_association_update_request_ue);
OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_parseFromJSON(
	cJSON *policy_association_update_request_ueJSON);
cJSON *OpenAPI_policy_association_update_request_ue_convertToJSON(
	OpenAPI_policy_association_update_request_ue_t *
	policy_association_update_request_ue);
OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_copy(
	OpenAPI_policy_association_update_request_ue_t	*dst,
	OpenAPI_policy_association_update_request_ue_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_association_update_request_ue_H_ */
