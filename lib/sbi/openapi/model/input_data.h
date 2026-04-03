/*
 * input_data.h
 *
 * Information within Determine Location Request.
 */

#ifndef _OpenAPI_input_data_H_
#define _OpenAPI_input_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "additional_ue_info.h"
#include "area_event_info.h"
#include "ecgi.h"
#include "external_client_type.h"
#include "input_data_reporting_ind.h"
#include "integrity_requirements.h"
#include "lcs_broadcast_assistance_types_data.h"
#include "lcs_priority.h"
#include "ldr_type.h"
#include "location_qo_s.h"
#include "lp_hap_type.h"
#include "mapped_location_qo_s_eps.h"
#include "mbsr_info.h"
#include "motion_event_info.h"
#include "ncgi.h"
#include "periodic_event_info.h"
#include "ranging_sl_result.h"
#include "ref_to_binary_data.h"
#include "related_ue.h"
#include "reporting_access_type.h"
#include "reporting_area.h"
#include "sl_positioning_capability.h"
#include "supported_gad_shapes.h"
#include "tnap_id.h"
#include "twap_id.h"
#include "ue_connectivity_state.h"
#include "ue_lcs_capability.h"
#include "ue_location_service_ind.h"
#include "ue_up_positioning_capabilities.h"
#include "up_cum_evt_rpt_criteria.h"
#include "up_loc_rep_addr_af.h"
#include "velocity_requested.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_input_data_s OpenAPI_input_data_t;
typedef enum { OpenAPI_input_data_UEUNAWAREIND_NULL = 0,
	       OpenAPI_input_data_UEUNAWAREIND__true }
OpenAPI_input_data_ue_unaware_ind_e;

char * OpenAPI_input_data_ue_unaware_ind_ToString(
	OpenAPI_input_data_ue_unaware_ind_e ue_unaware_ind);

OpenAPI_input_data_ue_unaware_ind_e OpenAPI_input_data_ue_unaware_ind_FromString
        (char *ue_unaware_ind);
typedef enum { OpenAPI_input_data_MWABSUPPORTIND_NULL = 0,
	       OpenAPI_input_data_MWABSUPPORTIND__true }
OpenAPI_input_data_mwab_support_ind_e;

char * OpenAPI_input_data_mwab_support_ind_ToString(
	OpenAPI_input_data_mwab_support_ind_e mwab_support_ind);

OpenAPI_input_data_mwab_support_ind_e
OpenAPI_input_data_mwab_support_ind_FromString(char *mwab_support_ind);
typedef struct OpenAPI_input_data_s {
	OpenAPI_external_client_type_e external_client_type;
	char *correlation_id;
	char *amf_id;
	struct OpenAPI_location_qo_s_s *location_qo_s;
	OpenAPI_list_t *supported_gad_shapes;
	char *supi;
	char *pei;
	char *gpsi;
	OpenAPI_list_t *requested_ranging_sl_result;
	OpenAPI_list_t *related_ues;
	struct OpenAPI_ecgi_s *ecgi;
	struct OpenAPI_ecgi_s *ecgi_on_second_node;
	struct OpenAPI_ncgi_s *ncgi;
	struct OpenAPI_ncgi_s *ncgi_on_second_node;
	OpenAPI_lcs_priority_e priority;
	OpenAPI_velocity_requested_e velocity_requested;
	struct OpenAPI_ue_lcs_capability_s *ue_lcs_cap;
	bool is_lcs_service_type;
	int lcs_service_type;
	OpenAPI_ldr_type_e ldr_type;
	char *hgmlc_call_back_uri;
	char *lir_gmlc_call_back_uri;
	char *vgmlc_address;
	char *ldr_reference;
	char *lir_reference;
	struct OpenAPI_periodic_event_info_s *periodic_event_info;
	struct OpenAPI_area_event_info_s *area_event_info;
	struct OpenAPI_motion_event_info_s *motion_event_info;
	OpenAPI_list_t *reporting_access_types;
	struct OpenAPI_ue_connectivity_state_s *ue_connectivity_states;
	OpenAPI_ue_location_service_ind_e ue_location_service_ind;
	struct OpenAPI_lcs_broadcast_assistance_types_data_s *
	        mo_assistance_data_types;
	struct OpenAPI_ref_to_binary_data_s *lpp_message;
	OpenAPI_list_t *lpp_message_ext;
	char *supported_features;
	char *ue_positioning_cap;
	struct OpenAPI_tnap_id_s *tnap_id;
	struct OpenAPI_twap_id_s *twap_id;
	bool is_ue_country_det_ind;
	int ue_country_det_ind;
	char *scheduled_loc_time;
	bool is_reliable_loc_req;
	int reliable_loc_req;
	OpenAPI_list_t *evt_rpt_allowed_areas;
	OpenAPI_input_data_ue_unaware_ind_e ue_unaware_ind;
	bool is_intermediate_location_ind;
	int intermediate_location_ind;
	bool is_max_resp_time;
	int max_resp_time;
	OpenAPI_lp_hap_type_e lp_hap_type;
	OpenAPI_list_t *ue_up_pos_caps;
	struct OpenAPI_input_data_reporting_ind_s *reporting_ind;
	struct OpenAPI_mbsr_info_s *mbsr_info;
	OpenAPI_input_data_mwab_support_ind_e mwab_support_ind;
	struct OpenAPI_integrity_requirements_s *integrity_requirements;
	struct OpenAPI_up_loc_rep_addr_af_s *up_loc_rep_addr_af;
	struct OpenAPI_up_cum_evt_rpt_criteria_s *up_cum_evt_rpt_criteria;
	struct OpenAPI_mapped_location_qo_s_eps_s *mapped_qo_s_eps;
	struct OpenAPI_additional_ue_info_s *additional_ue_info;
	bool is_coordinate_id;
	int coordinate_id;
	char *ranging_sl_capability;
	OpenAPI_list_t *sl_positioning_capabilities;
} OpenAPI_input_data_t;

OpenAPI_input_data_t *OpenAPI_input_data_create(
	OpenAPI_external_client_type_e external_client_type,
	char *correlation_id, char *amf_id,
	OpenAPI_location_qo_s_t *location_qo_s,
	OpenAPI_list_t *supported_gad_shapes, char *supi, char *pei, char *gpsi,
	OpenAPI_list_t *requested_ranging_sl_result,
	OpenAPI_list_t *related_ues, OpenAPI_ecgi_t *ecgi,
	OpenAPI_ecgi_t *ecgi_on_second_node, OpenAPI_ncgi_t *ncgi,
	OpenAPI_ncgi_t *ncgi_on_second_node, OpenAPI_lcs_priority_e priority,
	OpenAPI_velocity_requested_e velocity_requested,
	OpenAPI_ue_lcs_capability_t *ue_lcs_cap, bool is_lcs_service_type,
	int lcs_service_type, OpenAPI_ldr_type_e ldr_type,
	char *hgmlc_call_back_uri, char *lir_gmlc_call_back_uri,
	char *vgmlc_address, char *ldr_reference, char *lir_reference,
	OpenAPI_periodic_event_info_t *periodic_event_info,
	OpenAPI_area_event_info_t *area_event_info,
	OpenAPI_motion_event_info_t *motion_event_info,
	OpenAPI_list_t *reporting_access_types,
	OpenAPI_ue_connectivity_state_t *ue_connectivity_states,
	OpenAPI_ue_location_service_ind_e ue_location_service_ind,
	OpenAPI_lcs_broadcast_assistance_types_data_t *mo_assistance_data_types,
	OpenAPI_ref_to_binary_data_t *lpp_message,
	OpenAPI_list_t *lpp_message_ext, char *supported_features,
	char *ue_positioning_cap, OpenAPI_tnap_id_t *tnap_id,
	OpenAPI_twap_id_t *twap_id, bool is_ue_country_det_ind,
	int ue_country_det_ind, char *scheduled_loc_time,
	bool is_reliable_loc_req, int reliable_loc_req,
	OpenAPI_list_t *evt_rpt_allowed_areas,
	OpenAPI_input_data_ue_unaware_ind_e ue_unaware_ind,
	bool is_intermediate_location_ind, int intermediate_location_ind,
	bool is_max_resp_time, int max_resp_time,
	OpenAPI_lp_hap_type_e lp_hap_type, OpenAPI_list_t *ue_up_pos_caps,
	OpenAPI_input_data_reporting_ind_t *reporting_ind,
	OpenAPI_mbsr_info_t *mbsr_info,
	OpenAPI_input_data_mwab_support_ind_e mwab_support_ind,
	OpenAPI_integrity_requirements_t *integrity_requirements,
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af,
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria,
	OpenAPI_mapped_location_qo_s_eps_t *mapped_qo_s_eps,
	OpenAPI_additional_ue_info_t *additional_ue_info, bool is_coordinate_id,
	int coordinate_id, char *ranging_sl_capability,
	OpenAPI_list_t *sl_positioning_capabilities);
void OpenAPI_input_data_free(OpenAPI_input_data_t *input_data);
OpenAPI_input_data_t *OpenAPI_input_data_parseFromJSON(cJSON *input_dataJSON);
cJSON *OpenAPI_input_data_convertToJSON(OpenAPI_input_data_t *input_data);
OpenAPI_input_data_t *OpenAPI_input_data_copy(OpenAPI_input_data_t	*dst,
                                              OpenAPI_input_data_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_input_data_H_ */
