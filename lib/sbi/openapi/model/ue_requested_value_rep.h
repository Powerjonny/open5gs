/*
 * ue_requested_value_rep.h
 *
 * Contains the current applicable values corresponding to the policy control request triggers.
 */

#ifndef _OpenAPI_ue_requested_value_rep_H_
#define _OpenAPI_ue_requested_value_rep_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "access_type.h"
#include "cm_state.h"
#include "configured_snssai.h"
#include "lbo_roaming_information.h"
#include "plmn_id_nid.h"
#include "presence_info.h"
#include "rat_type.h"
#include "satellite_backhaul_category.h"
#include "ursp_enforcement_pdu_session.h"
#include "user_location.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ue_requested_value_rep_s OpenAPI_ue_requested_value_rep_t;
typedef struct OpenAPI_ue_requested_value_rep_s {
	struct OpenAPI_user_location_s *user_loc;
	OpenAPI_list_t *pra_statuses;
	struct OpenAPI_plmn_id_nid_s *plmn_id;
	struct OpenAPI_cm_state_s *connect_state;
	OpenAPI_list_t *conf_snssais;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category;
	OpenAPI_list_t *ursp_enf_rep;
	OpenAPI_list_t *lbo_roam_info;
	OpenAPI_list_t *access_types;
	OpenAPI_list_t *rat_types;
} OpenAPI_ue_requested_value_rep_t;

OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_create(
	OpenAPI_user_location_t *user_loc, OpenAPI_list_t *pra_statuses,
	OpenAPI_plmn_id_nid_t *plmn_id, OpenAPI_cm_state_t *connect_state,
	OpenAPI_list_t *conf_snssais,
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category,
	OpenAPI_list_t *ursp_enf_rep, OpenAPI_list_t *lbo_roam_info,
	OpenAPI_list_t *access_types, OpenAPI_list_t *rat_types);
void OpenAPI_ue_requested_value_rep_free(
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep);
OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_parseFromJSON(
	cJSON *ue_requested_value_repJSON);
cJSON *OpenAPI_ue_requested_value_rep_convertToJSON(
	OpenAPI_ue_requested_value_rep_t *ue_requested_value_rep);
OpenAPI_ue_requested_value_rep_t *OpenAPI_ue_requested_value_rep_copy(
	OpenAPI_ue_requested_value_rep_t	*dst,
	OpenAPI_ue_requested_value_rep_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_requested_value_rep_H_ */
