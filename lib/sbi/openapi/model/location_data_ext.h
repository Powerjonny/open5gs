/*
 * location_data_ext.h
 *
 * Extended Location Data for UEs
 */

#ifndef _OpenAPI_location_data_ext_H_
#define _OpenAPI_location_data_ext_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "accuracy_fulfilment_indicator.h"
#include "civic_address.h"
#include "ecgi.h"
#include "geographic_area.h"
#include "gnss_positioning_method_and_usage.h"
#include "high_accuracy_gnss_metrics.h"
#include "indoor_outdoor_ind.h"
#include "integrity_result.h"
#include "local_area.h"
#include "location_data.h"
#include "los_nlos_measure_ind.h"
#include "minor_location_qo_s.h"
#include "model_2_d_relative_location.h"
#include "model_3_d_relative_location.h"
#include "ncgi.h"
#include "periodic_event_info.h"
#include "positioning_method_and_usage.h"
#include "range_direction.h"
#include "ue_area_indication.h"
#include "velocity_estimate.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_location_data_ext_s OpenAPI_location_data_ext_t;
typedef enum { OpenAPI_location_data_ext_REMOTEUEIND_NULL = 0,
	       OpenAPI_location_data_ext_REMOTEUEIND__true }
OpenAPI_location_data_ext_remote_ue_ind_e;

char * OpenAPI_location_data_ext_remote_ue_ind_ToString(
	OpenAPI_location_data_ext_remote_ue_ind_e remote_ue_ind);

OpenAPI_location_data_ext_remote_ue_ind_e
OpenAPI_location_data_ext_remote_ue_ind_FromString(char *remote_ue_ind);
typedef enum { OpenAPI_location_data_ext_NRPPAPERIODICIND_NULL = 0,
	       OpenAPI_location_data_ext_NRPPAPERIODICIND__true }
OpenAPI_location_data_ext_nrppa_periodic_ind_e;

char * OpenAPI_location_data_ext_nrppa_periodic_ind_ToString(
	OpenAPI_location_data_ext_nrppa_periodic_ind_e nrppa_periodic_ind);

OpenAPI_location_data_ext_nrppa_periodic_ind_e
OpenAPI_location_data_ext_nrppa_periodic_ind_FromString(
	char *nrppa_periodic_ind);
typedef struct OpenAPI_location_data_ext_s {
	struct OpenAPI_geographic_area_s *location_estimate;
	OpenAPI_accuracy_fulfilment_indicator_e accuracy_fulfilment_indicator;
	bool is_age_of_location_estimate;
	int age_of_location_estimate;
	char *timestamp_of_location_estimate;
	struct OpenAPI_velocity_estimate_s *velocity_estimate;
	struct OpenAPI_civic_address_s *civic_address;
	struct OpenAPI_local_area_s *local_location_estimate;
	OpenAPI_list_t *positioning_data_list;
	OpenAPI_list_t *gnss_positioning_data_list;
	struct OpenAPI_ecgi_s *ecgi;
	struct OpenAPI_ncgi_s *ncgi;
	OpenAPI_location_data_ext_remote_ue_ind_e remote_ue_ind;
	bool is_altitude;
	double altitude;
	bool is_barometric_pressure;
	int barometric_pressure;
	char *serving_lmf_identification;
	char *ue_positioning_cap;
	struct OpenAPI_ue_area_indication_s *ue_area_ind;
	char *supported_features;
	struct OpenAPI_minor_location_qo_s_s *achieved_qos;
	bool is_direct_report_ind;
	int direct_report_ind;
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind;
	struct OpenAPI_periodic_event_info_s *accepted_periodic_event_info;
	struct OpenAPI_high_accuracy_gnss_metrics_s *ha_gnss_metrics;
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind;
	char *related_applicationlayer_id;
	struct OpenAPI_range_direction_s *distance_direction;
	struct OpenAPI_model_2_d_relative_location_s *_2d_relative_location;
	struct OpenAPI_model_3_d_relative_location_s *_3d_relative_location;
	struct OpenAPI_velocity_estimate_s *relative_velocity;
	char *ranging_sl_capability;
	struct OpenAPI_integrity_result_s *integrity_result;
	OpenAPI_location_data_ext_nrppa_periodic_ind_e nrppa_periodic_ind;
	OpenAPI_list_t *add_location_datas;
} OpenAPI_location_data_ext_t;

OpenAPI_location_data_ext_t *OpenAPI_location_data_ext_create(
	OpenAPI_geographic_area_t *location_estimate,
	OpenAPI_accuracy_fulfilment_indicator_e accuracy_fulfilment_indicator,
	bool is_age_of_location_estimate, int age_of_location_estimate,
	char *timestamp_of_location_estimate,
	OpenAPI_velocity_estimate_t *velocity_estimate,
	OpenAPI_civic_address_t *civic_address,
	OpenAPI_local_area_t *local_location_estimate,
	OpenAPI_list_t *positioning_data_list,
	OpenAPI_list_t *gnss_positioning_data_list, OpenAPI_ecgi_t *ecgi,
	OpenAPI_ncgi_t *ncgi,
	OpenAPI_location_data_ext_remote_ue_ind_e remote_ue_ind,
	bool is_altitude, double altitude, bool is_barometric_pressure,
	int barometric_pressure, char *serving_lmf_identification,
	char *ue_positioning_cap, OpenAPI_ue_area_indication_t *ue_area_ind,
	char *supported_features, OpenAPI_minor_location_qo_s_t *achieved_qos,
	bool is_direct_report_ind, int direct_report_ind,
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind,
	OpenAPI_periodic_event_info_t *accepted_periodic_event_info,
	OpenAPI_high_accuracy_gnss_metrics_t *ha_gnss_metrics,
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind,
	char *related_applicationlayer_id,
	OpenAPI_range_direction_t *distance_direction,
	OpenAPI_model_2_d_relative_location_t *_2d_relative_location,
	OpenAPI_model_3_d_relative_location_t *_3d_relative_location,
	OpenAPI_velocity_estimate_t *relative_velocity,
	char *ranging_sl_capability,
	OpenAPI_integrity_result_t *integrity_result,
	OpenAPI_location_data_ext_nrppa_periodic_ind_e nrppa_periodic_ind,
	OpenAPI_list_t *add_location_datas);
void OpenAPI_location_data_ext_free(
	OpenAPI_location_data_ext_t *location_data_ext);
OpenAPI_location_data_ext_t *OpenAPI_location_data_ext_parseFromJSON(
	cJSON *location_data_extJSON);
cJSON *OpenAPI_location_data_ext_convertToJSON(
	OpenAPI_location_data_ext_t *location_data_ext);
OpenAPI_location_data_ext_t *OpenAPI_location_data_ext_copy(
	OpenAPI_location_data_ext_t *dst, OpenAPI_location_data_ext_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_location_data_ext_H_ */
