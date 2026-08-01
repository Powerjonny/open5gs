/*
 * policy_association_request_ue.h
 *
 * Represents information that the NF service consumer provides when requesting the creation of a policy association.
 */

#ifndef _OpenAPI_policy_association_request_ue_H_
#define _OpenAPI_policy_association_request_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "a2x_capability.h"
#include "access_type.h"
#include "configured_snssai.h"
#include "guami.h"
#include "lbo_roaming_information.h"
#include "non3gpp_access.h"
#include "pc5_capability.h"
#include "plmn_id_nid.h"
#include "pro_se_capability_ue.h"
#include "rang_sl_capability.h"
#include "rat_type.h"
#include "satellite_backhaul_category.h"
#include "slice_specific_n3g_node_selection_capability.h"
#include "ue_policy_parameters.h"
#include "user_location.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_policy_association_request_ue_s
        OpenAPI_policy_association_request_ue_t;
typedef struct OpenAPI_policy_association_request_ue_s {
	char *notification_uri;
	OpenAPI_list_t *alt_notif_ipv4_addrs;
	OpenAPI_list_t *alt_notif_ipv6_addrs;
	OpenAPI_list_t *alt_notif_fqdns;
	char *supi;
	char *gpsi;
	OpenAPI_access_type_e access_type;
	OpenAPI_list_t *access_types;
	char *pei;
	struct OpenAPI_user_location_s *user_loc;
	char *time_zone;
	struct OpenAPI_plmn_id_nid_s *serving_plmn;
	OpenAPI_rat_type_e rat_type;
	OpenAPI_list_t *rat_types;
	OpenAPI_list_t *group_ids;
	char *h_pcf_id;
	char *h_pcf_uri;
	char *h_pcf_set_id;
	char *ue_pol_req;
	struct OpenAPI_guami_s *guami;
	char *service_name;
	char *serving_nf_id;
	OpenAPI_pc5_capability_e pc5_capab;
	OpenAPI_list_t *a2x_capab;
	OpenAPI_list_t *pro_se_capab;
	OpenAPI_list_t *conf_snssais;
	OpenAPI_non3gpp_access_e n3g_node_re_sel;
	OpenAPI_slice_specific_n3g_node_selection_capability_e
	        slice_n3g_node_sel_cap;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category;
	bool is__5gs_to_eps_mob;
	int _5gs_to_eps_mob;
	OpenAPI_list_t *vps_ue_pol_guidance;
	OpenAPI_list_t *lbo_roam_info;
	char *supp_feat;
	OpenAPI_list_t *rang_sl_capab;
} OpenAPI_policy_association_request_ue_t;

OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_create(char *notification_uri,
                                             OpenAPI_list_t *
                                             alt_notif_ipv4_addrs,
                                             OpenAPI_list_t *
                                             alt_notif_ipv6_addrs,
                                             OpenAPI_list_t *alt_notif_fqdns,
                                             char *supi, char *gpsi,
                                             OpenAPI_access_type_e access_type,
                                             OpenAPI_list_t *access_types,
                                             char *pei,
                                             OpenAPI_user_location_t *user_loc,
                                             char *time_zone,
                                             OpenAPI_plmn_id_nid_t *serving_plmn,
                                             OpenAPI_rat_type_e rat_type,
                                             OpenAPI_list_t *rat_types,
                                             OpenAPI_list_t *group_ids,
                                             char *h_pcf_id, char *h_pcf_uri,
                                             char *h_pcf_set_id,
                                             char *ue_pol_req,
                                             OpenAPI_guami_t *guami,
                                             char *service_name,
                                             char *serving_nf_id,
                                             OpenAPI_pc5_capability_e pc5_capab,
                                             OpenAPI_list_t *a2x_capab,
                                             OpenAPI_list_t *pro_se_capab,
                                             OpenAPI_list_t *conf_snssais,
                                             OpenAPI_non3gpp_access_e
                                             n3g_node_re_sel,
                                             OpenAPI_slice_specific_n3g_node_selection_capability_e
                                             slice_n3g_node_sel_cap,
                                             OpenAPI_satellite_backhaul_category_e
                                             sat_backhaul_category,
                                             bool is__5gs_to_eps_mob,
                                             int _5gs_to_eps_mob,
                                             OpenAPI_list_t *vps_ue_pol_guidance,
                                             OpenAPI_list_t *lbo_roam_info,
                                             char *supp_feat,
                                             OpenAPI_list_t *rang_sl_capab);
void OpenAPI_policy_association_request_ue_free(
	OpenAPI_policy_association_request_ue_t *policy_association_request_ue);
OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_parseFromJSON(
	cJSON *policy_association_request_ueJSON);
cJSON *OpenAPI_policy_association_request_ue_convertToJSON(
	OpenAPI_policy_association_request_ue_t *policy_association_request_ue);
OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_copy(
	OpenAPI_policy_association_request_ue_t *dst,
	OpenAPI_policy_association_request_ue_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_association_request_ue_H_ */
