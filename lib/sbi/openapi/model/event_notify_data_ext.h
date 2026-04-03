/*
 * event_notify_data_ext.h
 *
 * Extended Event Notify Data for UEs
 */

#ifndef _OpenAPI_event_notify_data_ext_H_
#define _OpenAPI_event_notify_data_ext_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "civic_address.h"
#include "event_notify_data.h"
#include "geographic_area.h"
#include "gnss_positioning_method_and_usage.h"
#include "high_accuracy_gnss_metrics.h"
#include "indoor_outdoor_ind.h"
#include "integrity_result.h"
#include "local_area.h"
#include "los_nlos_measure_ind.h"
#include "minor_location_qo_s.h"
#include "model_2_d_relative_location.h"
#include "model_3_d_relative_location.h"
#include "positioning_method_and_usage.h"
#include "range_direction.h"
#include "reported_event_type.h"
#include "termination_cause.h"
#include "velocity_estimate.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_event_notify_data_ext_s OpenAPI_event_notify_data_ext_t;
typedef struct OpenAPI_event_notify_data_ext_s {
	OpenAPI_reported_event_type_e reported_event_type;
	char *supi;
	char *gpsi;
	char *hgmlc_call_back_uri;
	char *ldr_reference;
	char *lir_reference;
	struct OpenAPI_geographic_area_s *location_estimate;
	bool is_age_of_location_estimate;
	int age_of_location_estimate;
	char *timestamp_of_location_estimate;
	struct OpenAPI_civic_address_s *civic_address;
	struct OpenAPI_local_area_s *local_location_estimate;
	OpenAPI_list_t *positioning_data_list;
	OpenAPI_list_t *gnss_positioning_data_list;
	char *serving_lm_fidentification;
	OpenAPI_termination_cause_e termination_cause;
	struct OpenAPI_velocity_estimate_s *velocity_estimate;
	bool is_altitude;
	double altitude;
	struct OpenAPI_minor_location_qo_s_s *achieved_qos;
	char *supported_features;
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind;
	struct OpenAPI_high_accuracy_gnss_metrics_s *ha_gnss_metrics;
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind;
	bool is_up_loc_rep_stat_af;
	int up_loc_rep_stat_af;
	char *related_applicationlayer_id;
	struct OpenAPI_range_direction_s *distance_direction;
	struct OpenAPI_model_2_d_relative_location_s *_2d_relative_location;
	struct OpenAPI_model_3_d_relative_location_s *_3d_relative_location;
	struct OpenAPI_velocity_estimate_s *relative_velocity;
	struct OpenAPI_integrity_result_s *integrity_result;
	OpenAPI_list_t *add_event_notify_datas;
} OpenAPI_event_notify_data_ext_t;

OpenAPI_event_notify_data_ext_t *OpenAPI_event_notify_data_ext_create(
	OpenAPI_reported_event_type_e reported_event_type, char *supi,
	char *gpsi, char *hgmlc_call_back_uri, char *ldr_reference,
	char *lir_reference, OpenAPI_geographic_area_t *location_estimate,
	bool is_age_of_location_estimate, int age_of_location_estimate,
	char *timestamp_of_location_estimate,
	OpenAPI_civic_address_t *civic_address,
	OpenAPI_local_area_t *local_location_estimate,
	OpenAPI_list_t *positioning_data_list,
	OpenAPI_list_t *gnss_positioning_data_list,
	char *serving_lm_fidentification,
	OpenAPI_termination_cause_e termination_cause,
	OpenAPI_velocity_estimate_t *velocity_estimate, bool is_altitude,
	double altitude, OpenAPI_minor_location_qo_s_t *achieved_qos,
	char *supported_features,
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind,
	OpenAPI_high_accuracy_gnss_metrics_t *ha_gnss_metrics,
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind,
	bool is_up_loc_rep_stat_af, int up_loc_rep_stat_af,
	char *related_applicationlayer_id,
	OpenAPI_range_direction_t *distance_direction,
	OpenAPI_model_2_d_relative_location_t *_2d_relative_location,
	OpenAPI_model_3_d_relative_location_t *_3d_relative_location,
	OpenAPI_velocity_estimate_t *relative_velocity,
	OpenAPI_integrity_result_t *integrity_result,
	OpenAPI_list_t *add_event_notify_datas);
void OpenAPI_event_notify_data_ext_free(
	OpenAPI_event_notify_data_ext_t *event_notify_data_ext);
OpenAPI_event_notify_data_ext_t *OpenAPI_event_notify_data_ext_parseFromJSON(
	cJSON *event_notify_data_extJSON);
cJSON *OpenAPI_event_notify_data_ext_convertToJSON(
	OpenAPI_event_notify_data_ext_t *event_notify_data_ext);
OpenAPI_event_notify_data_ext_t *OpenAPI_event_notify_data_ext_copy(
	OpenAPI_event_notify_data_ext_t *dst,
	OpenAPI_event_notify_data_ext_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_event_notify_data_ext_H_ */
