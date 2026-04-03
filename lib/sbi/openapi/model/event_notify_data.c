#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "event_notify_data.h"

OpenAPI_event_notify_data_t *OpenAPI_event_notify_data_create(
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
	OpenAPI_integrity_result_t *integrity_result) {
	OpenAPI_event_notify_data_t *event_notify_data_local_var =
		ogs_malloc(sizeof(OpenAPI_event_notify_data_t));
	ogs_assert(event_notify_data_local_var);

	event_notify_data_local_var->reported_event_type = reported_event_type;
	event_notify_data_local_var->supi = supi;
	event_notify_data_local_var->gpsi = gpsi;
	event_notify_data_local_var->hgmlc_call_back_uri = hgmlc_call_back_uri;
	event_notify_data_local_var->ldr_reference = ldr_reference;
	event_notify_data_local_var->lir_reference = lir_reference;
	event_notify_data_local_var->location_estimate = location_estimate;
	event_notify_data_local_var->is_age_of_location_estimate =
		is_age_of_location_estimate;
	event_notify_data_local_var->age_of_location_estimate =
		age_of_location_estimate;
	event_notify_data_local_var->timestamp_of_location_estimate =
		timestamp_of_location_estimate;
	event_notify_data_local_var->civic_address = civic_address;
	event_notify_data_local_var->local_location_estimate =
		local_location_estimate;
	event_notify_data_local_var->positioning_data_list =
		positioning_data_list;
	event_notify_data_local_var->gnss_positioning_data_list =
		gnss_positioning_data_list;
	event_notify_data_local_var->serving_lm_fidentification =
		serving_lm_fidentification;
	event_notify_data_local_var->termination_cause = termination_cause;
	event_notify_data_local_var->velocity_estimate = velocity_estimate;
	event_notify_data_local_var->is_altitude = is_altitude;
	event_notify_data_local_var->altitude = altitude;
	event_notify_data_local_var->achieved_qos = achieved_qos;
	event_notify_data_local_var->supported_features = supported_features;
	event_notify_data_local_var->indoor_outdoor_ind = indoor_outdoor_ind;
	event_notify_data_local_var->ha_gnss_metrics = ha_gnss_metrics;
	event_notify_data_local_var->los_nlos_measure_ind =
		los_nlos_measure_ind;
	event_notify_data_local_var->is_up_loc_rep_stat_af =
		is_up_loc_rep_stat_af;
	event_notify_data_local_var->up_loc_rep_stat_af = up_loc_rep_stat_af;
	event_notify_data_local_var->related_applicationlayer_id =
		related_applicationlayer_id;
	event_notify_data_local_var->distance_direction = distance_direction;
	event_notify_data_local_var->_2d_relative_location =
		_2d_relative_location;
	event_notify_data_local_var->_3d_relative_location =
		_3d_relative_location;
	event_notify_data_local_var->relative_velocity = relative_velocity;
	event_notify_data_local_var->integrity_result = integrity_result;

	return event_notify_data_local_var;
}

void OpenAPI_event_notify_data_free(
	OpenAPI_event_notify_data_t *event_notify_data) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == event_notify_data) {
		return;
	}
	if(event_notify_data->supi) {
		ogs_free(event_notify_data->supi);
		event_notify_data->supi = NULL;
	}
	if(event_notify_data->gpsi) {
		ogs_free(event_notify_data->gpsi);
		event_notify_data->gpsi = NULL;
	}
	if(event_notify_data->hgmlc_call_back_uri) {
		ogs_free(event_notify_data->hgmlc_call_back_uri);
		event_notify_data->hgmlc_call_back_uri = NULL;
	}
	if(event_notify_data->ldr_reference) {
		ogs_free(event_notify_data->ldr_reference);
		event_notify_data->ldr_reference = NULL;
	}
	if(event_notify_data->lir_reference) {
		ogs_free(event_notify_data->lir_reference);
		event_notify_data->lir_reference = NULL;
	}
	if(event_notify_data->location_estimate) {
		OpenAPI_geographic_area_free(
			event_notify_data->location_estimate);
		event_notify_data->location_estimate = NULL;
	}
	if(event_notify_data->timestamp_of_location_estimate) {
		ogs_free(event_notify_data->timestamp_of_location_estimate);
		event_notify_data->timestamp_of_location_estimate = NULL;
	}
	if(event_notify_data->civic_address) {
		OpenAPI_civic_address_free(event_notify_data->civic_address);
		event_notify_data->civic_address = NULL;
	}
	if(event_notify_data->local_location_estimate) {
		OpenAPI_local_area_free(
			event_notify_data->local_location_estimate);
		event_notify_data->local_location_estimate = NULL;
	}
	if(event_notify_data->positioning_data_list) {
		OpenAPI_list_for_each(event_notify_data->positioning_data_list,
		                      node) {
			OpenAPI_positioning_method_and_usage_free(node->data);
		}
		OpenAPI_list_free(event_notify_data->positioning_data_list);
		event_notify_data->positioning_data_list = NULL;
	}
	if(event_notify_data->gnss_positioning_data_list) {
		OpenAPI_list_for_each(
			event_notify_data->gnss_positioning_data_list, node) {
			OpenAPI_gnss_positioning_method_and_usage_free(
				node->data);
		}
		OpenAPI_list_free(
			event_notify_data->gnss_positioning_data_list);
		event_notify_data->gnss_positioning_data_list = NULL;
	}
	if(event_notify_data->serving_lm_fidentification) {
		ogs_free(event_notify_data->serving_lm_fidentification);
		event_notify_data->serving_lm_fidentification = NULL;
	}
	if(event_notify_data->velocity_estimate) {
		OpenAPI_velocity_estimate_free(
			event_notify_data->velocity_estimate);
		event_notify_data->velocity_estimate = NULL;
	}
	if(event_notify_data->achieved_qos) {
		OpenAPI_minor_location_qo_s_free(
			event_notify_data->achieved_qos);
		event_notify_data->achieved_qos = NULL;
	}
	if(event_notify_data->supported_features) {
		ogs_free(event_notify_data->supported_features);
		event_notify_data->supported_features = NULL;
	}
	if(event_notify_data->ha_gnss_metrics) {
		OpenAPI_high_accuracy_gnss_metrics_free(
			event_notify_data->ha_gnss_metrics);
		event_notify_data->ha_gnss_metrics = NULL;
	}
	if(event_notify_data->related_applicationlayer_id) {
		ogs_free(event_notify_data->related_applicationlayer_id);
		event_notify_data->related_applicationlayer_id = NULL;
	}
	if(event_notify_data->distance_direction) {
		OpenAPI_range_direction_free(
			event_notify_data->distance_direction);
		event_notify_data->distance_direction = NULL;
	}
	if(event_notify_data->_2d_relative_location) {
		OpenAPI_model_2_d_relative_location_free(
			event_notify_data->_2d_relative_location);
		event_notify_data->_2d_relative_location = NULL;
	}
	if(event_notify_data->_3d_relative_location) {
		OpenAPI_model_3_d_relative_location_free(
			event_notify_data->_3d_relative_location);
		event_notify_data->_3d_relative_location = NULL;
	}
	if(event_notify_data->relative_velocity) {
		OpenAPI_velocity_estimate_free(
			event_notify_data->relative_velocity);
		event_notify_data->relative_velocity = NULL;
	}
	if(event_notify_data->integrity_result) {
		OpenAPI_integrity_result_free(
			event_notify_data->integrity_result);
		event_notify_data->integrity_result = NULL;
	}
	ogs_free(event_notify_data);
}

cJSON *OpenAPI_event_notify_data_convertToJSON(
	OpenAPI_event_notify_data_t *event_notify_data) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(event_notify_data == NULL) {
		ogs_error(
			"OpenAPI_event_notify_data_convertToJSON() failed [EventNotifyData]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(event_notify_data->reported_event_type ==
	   OpenAPI_reported_event_type_NULL)
	{
		ogs_error(
			"OpenAPI_event_notify_data_convertToJSON() failed [reported_event_type]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "reportedEventType",
	                           OpenAPI_reported_event_type_ToString(
					   event_notify_data->
					   reported_event_type)) == NULL)
	{
		ogs_error(
			"OpenAPI_event_notify_data_convertToJSON() failed [reported_event_type]");
		goto end;
	}

	if(event_notify_data->supi) {
		if(cJSON_AddStringToObject(item, "supi",
		                           event_notify_data->supi) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [supi]");
			goto end;
		}
	}

	if(event_notify_data->gpsi) {
		if(cJSON_AddStringToObject(item, "gpsi",
		                           event_notify_data->gpsi) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [gpsi]");
			goto end;
		}
	}

	if(event_notify_data->hgmlc_call_back_uri) {
		if(cJSON_AddStringToObject(item, "hgmlcCallBackURI",
		                           event_notify_data->
		                           hgmlc_call_back_uri) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [hgmlc_call_back_uri]");
			goto end;
		}
	}

	if(!event_notify_data->ldr_reference) {
		ogs_error(
			"OpenAPI_event_notify_data_convertToJSON() failed [ldr_reference]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "ldrReference",
	                           event_notify_data->ldr_reference) == NULL)
	{
		ogs_error(
			"OpenAPI_event_notify_data_convertToJSON() failed [ldr_reference]");
		goto end;
	}

	if(event_notify_data->lir_reference) {
		if(cJSON_AddStringToObject(item, "lirReference",
		                           event_notify_data->lir_reference) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [lir_reference]");
			goto end;
		}
	}

	if(event_notify_data->location_estimate) {
		cJSON *location_estimate_local_JSON =
			OpenAPI_geographic_area_convertToJSON(
				event_notify_data->location_estimate);
		if(location_estimate_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [location_estimate]");
			goto end;
		}
		cJSON_AddItemToObject(item, "locationEstimate",
		                      location_estimate_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [location_estimate]");
			goto end;
		}
	}

	if(event_notify_data->is_age_of_location_estimate) {
		if(cJSON_AddNumberToObject(item, "ageOfLocationEstimate",
		                           event_notify_data->
		                           age_of_location_estimate) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [age_of_location_estimate]");
			goto end;
		}
	}

	if(event_notify_data->timestamp_of_location_estimate) {
		if(cJSON_AddStringToObject(item, "timestampOfLocationEstimate",
		                           event_notify_data->
		                           timestamp_of_location_estimate) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [timestamp_of_location_estimate]");
			goto end;
		}
	}

	if(event_notify_data->civic_address) {
		cJSON *civic_address_local_JSON =
			OpenAPI_civic_address_convertToJSON(
				event_notify_data->civic_address);
		if(civic_address_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [civic_address]");
			goto end;
		}
		cJSON_AddItemToObject(item, "civicAddress",
		                      civic_address_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [civic_address]");
			goto end;
		}
	}

	if(event_notify_data->local_location_estimate) {
		cJSON *local_location_estimate_local_JSON =
			OpenAPI_local_area_convertToJSON(
				event_notify_data->local_location_estimate);
		if(local_location_estimate_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [local_location_estimate]");
			goto end;
		}
		cJSON_AddItemToObject(item, "localLocationEstimate",
		                      local_location_estimate_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [local_location_estimate]");
			goto end;
		}
	}

	if(event_notify_data->positioning_data_list) {
		cJSON *positioning_data_listList = cJSON_AddArrayToObject(item,
		                                                          "positioningDataList");
		if(positioning_data_listList == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [positioning_data_list]");
			goto end;
		}
		OpenAPI_list_for_each(event_notify_data->positioning_data_list,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_positioning_method_and_usage_convertToJSON
				        (node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_event_notify_data_convertToJSON() failed [positioning_data_list]");
				goto end;
			}
			cJSON_AddItemToArray(positioning_data_listList,
			                     itemLocal);
		}
	}

	if(event_notify_data->gnss_positioning_data_list) {
		cJSON *gnss_positioning_data_listList =
			cJSON_AddArrayToObject(item, "gnssPositioningDataList");
		if(gnss_positioning_data_listList == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [gnss_positioning_data_list]");
			goto end;
		}
		OpenAPI_list_for_each(
			event_notify_data->gnss_positioning_data_list, node) {
			cJSON *itemLocal =
				OpenAPI_gnss_positioning_method_and_usage_convertToJSON
				        (node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_event_notify_data_convertToJSON() failed [gnss_positioning_data_list]");
				goto end;
			}
			cJSON_AddItemToArray(gnss_positioning_data_listList,
			                     itemLocal);
		}
	}

	if(event_notify_data->serving_lm_fidentification) {
		if(cJSON_AddStringToObject(item, "servingLMFidentification",
		                           event_notify_data->
		                           serving_lm_fidentification) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [serving_lm_fidentification]");
			goto end;
		}
	}

	if(event_notify_data->termination_cause !=
	   OpenAPI_termination_cause_NULL)
	{
		if(cJSON_AddStringToObject(item, "terminationCause",
		                           OpenAPI_termination_cause_ToString(
						   event_notify_data->
						   termination_cause)) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [termination_cause]");
			goto end;
		}
	}

	if(event_notify_data->velocity_estimate) {
		cJSON *velocity_estimate_local_JSON =
			OpenAPI_velocity_estimate_convertToJSON(
				event_notify_data->velocity_estimate);
		if(velocity_estimate_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [velocity_estimate]");
			goto end;
		}
		cJSON_AddItemToObject(item, "velocityEstimate",
		                      velocity_estimate_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [velocity_estimate]");
			goto end;
		}
	}

	if(event_notify_data->is_altitude) {
		if(cJSON_AddNumberToObject(item, "altitude",
		                           event_notify_data->altitude) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [altitude]");
			goto end;
		}
	}

	if(event_notify_data->achieved_qos) {
		cJSON *achieved_qos_local_JSON =
			OpenAPI_minor_location_qo_s_convertToJSON(
				event_notify_data->achieved_qos);
		if(achieved_qos_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [achieved_qos]");
			goto end;
		}
		cJSON_AddItemToObject(item, "achievedQos",
		                      achieved_qos_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [achieved_qos]");
			goto end;
		}
	}

	if(event_notify_data->supported_features) {
		if(cJSON_AddStringToObject(item, "supportedFeatures",
		                           event_notify_data->supported_features)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [supported_features]");
			goto end;
		}
	}

	if(event_notify_data->indoor_outdoor_ind !=
	   OpenAPI_indoor_outdoor_ind_NULL)
	{
		if(cJSON_AddStringToObject(item, "indoorOutdoorInd",
		                           OpenAPI_indoor_outdoor_ind_ToString(
						   event_notify_data->
						   indoor_outdoor_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [indoor_outdoor_ind]");
			goto end;
		}
	}

	if(event_notify_data->ha_gnss_metrics) {
		cJSON *ha_gnss_metrics_local_JSON =
			OpenAPI_high_accuracy_gnss_metrics_convertToJSON(
				event_notify_data->ha_gnss_metrics);
		if(ha_gnss_metrics_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [ha_gnss_metrics]");
			goto end;
		}
		cJSON_AddItemToObject(item, "haGnssMetrics",
		                      ha_gnss_metrics_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [ha_gnss_metrics]");
			goto end;
		}
	}

	if(event_notify_data->los_nlos_measure_ind !=
	   OpenAPI_los_nlos_measure_ind_NULL)
	{
		if(cJSON_AddStringToObject(item, "losNlosMeasureInd",
		                           OpenAPI_los_nlos_measure_ind_ToString
		                                   (event_notify_data->
		                                   los_nlos_measure_ind)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [los_nlos_measure_ind]");
			goto end;
		}
	}

	if(event_notify_data->is_up_loc_rep_stat_af) {
		if(cJSON_AddNumberToObject(item, "upLocRepStatAf",
		                           event_notify_data->up_loc_rep_stat_af)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [up_loc_rep_stat_af]");
			goto end;
		}
	}

	if(event_notify_data->related_applicationlayer_id) {
		if(cJSON_AddStringToObject(item, "relatedApplicationlayerId",
		                           event_notify_data->
		                           related_applicationlayer_id) == NULL)
		{
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [related_applicationlayer_id]");
			goto end;
		}
	}

	if(event_notify_data->distance_direction) {
		cJSON *distance_direction_local_JSON =
			OpenAPI_range_direction_convertToJSON(
				event_notify_data->distance_direction);
		if(distance_direction_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [distance_direction]");
			goto end;
		}
		cJSON_AddItemToObject(item, "distanceDirection",
		                      distance_direction_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [distance_direction]");
			goto end;
		}
	}

	if(event_notify_data->_2d_relative_location) {
		cJSON *_2d_relative_location_local_JSON =
			OpenAPI_model_2_d_relative_location_convertToJSON(
				event_notify_data->_2d_relative_location);
		if(_2d_relative_location_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [_2d_relative_location]");
			goto end;
		}
		cJSON_AddItemToObject(item, "2dRelativeLocation",
		                      _2d_relative_location_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [_2d_relative_location]");
			goto end;
		}
	}

	if(event_notify_data->_3d_relative_location) {
		cJSON *_3d_relative_location_local_JSON =
			OpenAPI_model_3_d_relative_location_convertToJSON(
				event_notify_data->_3d_relative_location);
		if(_3d_relative_location_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [_3d_relative_location]");
			goto end;
		}
		cJSON_AddItemToObject(item, "3dRelativeLocation",
		                      _3d_relative_location_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [_3d_relative_location]");
			goto end;
		}
	}

	if(event_notify_data->relative_velocity) {
		cJSON *relative_velocity_local_JSON =
			OpenAPI_velocity_estimate_convertToJSON(
				event_notify_data->relative_velocity);
		if(relative_velocity_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [relative_velocity]");
			goto end;
		}
		cJSON_AddItemToObject(item, "relativeVelocity",
		                      relative_velocity_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [relative_velocity]");
			goto end;
		}
	}

	if(event_notify_data->integrity_result) {
		cJSON *integrity_result_local_JSON =
			OpenAPI_integrity_result_convertToJSON(
				event_notify_data->integrity_result);
		if(integrity_result_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [integrity_result]");
			goto end;
		}
		cJSON_AddItemToObject(item, "integrityResult",
		                      integrity_result_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_event_notify_data_convertToJSON() failed [integrity_result]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_event_notify_data_t *OpenAPI_event_notify_data_parseFromJSON(
	cJSON *event_notify_dataJSON) {
	OpenAPI_event_notify_data_t *event_notify_data_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *reported_event_type = NULL;
	OpenAPI_reported_event_type_e reported_event_typeVariable = 0;
	cJSON *supi = NULL;
	cJSON *gpsi = NULL;
	cJSON *hgmlc_call_back_uri = NULL;
	cJSON *ldr_reference = NULL;
	cJSON *lir_reference = NULL;
	cJSON *location_estimate = NULL;
	OpenAPI_geographic_area_t *location_estimate_local_nonprim = NULL;
	cJSON *age_of_location_estimate = NULL;
	cJSON *timestamp_of_location_estimate = NULL;
	cJSON *civic_address = NULL;
	OpenAPI_civic_address_t *civic_address_local_nonprim = NULL;
	cJSON *local_location_estimate = NULL;
	OpenAPI_local_area_t *local_location_estimate_local_nonprim = NULL;
	cJSON *positioning_data_list = NULL;
	OpenAPI_list_t *positioning_data_listList = NULL;
	cJSON *gnss_positioning_data_list = NULL;
	OpenAPI_list_t *gnss_positioning_data_listList = NULL;
	cJSON *serving_lm_fidentification = NULL;
	cJSON *termination_cause = NULL;
	OpenAPI_termination_cause_e termination_causeVariable = 0;
	cJSON *velocity_estimate = NULL;
	OpenAPI_velocity_estimate_t *velocity_estimate_local_nonprim = NULL;
	cJSON *altitude = NULL;
	cJSON *achieved_qos = NULL;
	OpenAPI_minor_location_qo_s_t *achieved_qos_local_nonprim = NULL;
	cJSON *supported_features = NULL;
	cJSON *indoor_outdoor_ind = NULL;
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_indVariable = 0;
	cJSON *ha_gnss_metrics = NULL;
	OpenAPI_high_accuracy_gnss_metrics_t *ha_gnss_metrics_local_nonprim =
		NULL;
	cJSON *los_nlos_measure_ind = NULL;
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_indVariable = 0;
	cJSON *up_loc_rep_stat_af = NULL;
	cJSON *related_applicationlayer_id = NULL;
	cJSON *distance_direction = NULL;
	OpenAPI_range_direction_t *distance_direction_local_nonprim = NULL;
	cJSON *_2d_relative_location = NULL;
	OpenAPI_model_2_d_relative_location_t *
	        _2d_relative_location_local_nonprim = NULL;
	cJSON *_3d_relative_location = NULL;
	OpenAPI_model_3_d_relative_location_t *
	        _3d_relative_location_local_nonprim = NULL;
	cJSON *relative_velocity = NULL;
	OpenAPI_velocity_estimate_t *relative_velocity_local_nonprim = NULL;
	cJSON *integrity_result = NULL;
	OpenAPI_integrity_result_t *integrity_result_local_nonprim = NULL;
	reported_event_type =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "reportedEventType");
	if(!reported_event_type) {
		ogs_error(
			"OpenAPI_event_notify_data_parseFromJSON() failed [reported_event_type]");
		goto end;
	}
	if(!cJSON_IsString(reported_event_type)) {
		ogs_error(
			"OpenAPI_event_notify_data_parseFromJSON() failed [reported_event_type]");
		goto end;
	}
	reported_event_typeVariable =
		OpenAPI_reported_event_type_FromString(
			reported_event_type->valuestring);

	supi = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON, "supi");
	if(supi) {
		if(!cJSON_IsString(supi) &&
		   !cJSON_IsNull(supi))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [supi]");
			goto end;
		}
	}

	gpsi = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON, "gpsi");
	if(gpsi) {
		if(!cJSON_IsString(gpsi) &&
		   !cJSON_IsNull(gpsi))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [gpsi]");
			goto end;
		}
	}

	hgmlc_call_back_uri =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "hgmlcCallBackURI");
	if(hgmlc_call_back_uri) {
		if(!cJSON_IsString(hgmlc_call_back_uri) &&
		   !cJSON_IsNull(hgmlc_call_back_uri))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [hgmlc_call_back_uri]");
			goto end;
		}
	}

	ldr_reference = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
	                                                 "ldrReference");
	if(!ldr_reference) {
		ogs_error(
			"OpenAPI_event_notify_data_parseFromJSON() failed [ldr_reference]");
		goto end;
	}
	if(!cJSON_IsString(ldr_reference)) {
		ogs_error(
			"OpenAPI_event_notify_data_parseFromJSON() failed [ldr_reference]");
		goto end;
	}

	lir_reference = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
	                                                 "lirReference");
	if(lir_reference) {
		if(!cJSON_IsString(lir_reference) &&
		   !cJSON_IsNull(lir_reference))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [lir_reference]");
			goto end;
		}
	}

	location_estimate =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "locationEstimate");
	if(location_estimate) {
		location_estimate_local_nonprim =
			OpenAPI_geographic_area_parseFromJSON(
				location_estimate);
		if(!location_estimate_local_nonprim) {
			ogs_error(
				"OpenAPI_geographic_area_parseFromJSON failed [location_estimate]");
			goto end;
		}
	}

	age_of_location_estimate =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "ageOfLocationEstimate");
	if(age_of_location_estimate) {
		if(!cJSON_IsNumber(age_of_location_estimate)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [age_of_location_estimate]");
			goto end;
		}
	}

	timestamp_of_location_estimate =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "timestampOfLocationEstimate");
	if(timestamp_of_location_estimate) {
		if(!cJSON_IsString(timestamp_of_location_estimate) &&
		   !cJSON_IsNull(timestamp_of_location_estimate))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [timestamp_of_location_estimate]");
			goto end;
		}
	}

	civic_address = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
	                                                 "civicAddress");
	if(civic_address) {
		civic_address_local_nonprim =
			OpenAPI_civic_address_parseFromJSON(civic_address);
		if(!civic_address_local_nonprim) {
			ogs_error(
				"OpenAPI_civic_address_parseFromJSON failed [civic_address]");
			goto end;
		}
	}

	local_location_estimate =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "localLocationEstimate");
	if(local_location_estimate) {
		local_location_estimate_local_nonprim =
			OpenAPI_local_area_parseFromJSON(
				local_location_estimate);
		if(!local_location_estimate_local_nonprim) {
			ogs_error(
				"OpenAPI_local_area_parseFromJSON failed [local_location_estimate]");
			goto end;
		}
	}

	positioning_data_list =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "positioningDataList");
	if(positioning_data_list) {
		cJSON *positioning_data_list_local = NULL;
		if(!cJSON_IsArray(positioning_data_list)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [positioning_data_list]");
			goto end;
		}

		positioning_data_listList = OpenAPI_list_create();

		cJSON_ArrayForEach(positioning_data_list_local,
		                   positioning_data_list) {
			if(!cJSON_IsObject(positioning_data_list_local)) {
				ogs_error(
					"OpenAPI_event_notify_data_parseFromJSON() failed [positioning_data_list]");
				goto end;
			}
			OpenAPI_positioning_method_and_usage_t *
			        positioning_data_listItem =
				OpenAPI_positioning_method_and_usage_parseFromJSON
				        (positioning_data_list_local);
			if(!positioning_data_listItem) {
				ogs_error("No positioning_data_listItem");
				goto end;
			}
			OpenAPI_list_add(positioning_data_listList,
			                 positioning_data_listItem);
		}
	}

	gnss_positioning_data_list =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "gnssPositioningDataList");
	if(gnss_positioning_data_list) {
		cJSON *gnss_positioning_data_list_local = NULL;
		if(!cJSON_IsArray(gnss_positioning_data_list)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [gnss_positioning_data_list]");
			goto end;
		}

		gnss_positioning_data_listList = OpenAPI_list_create();

		cJSON_ArrayForEach(gnss_positioning_data_list_local,
		                   gnss_positioning_data_list) {
			if(!cJSON_IsObject(gnss_positioning_data_list_local)) {
				ogs_error(
					"OpenAPI_event_notify_data_parseFromJSON() failed [gnss_positioning_data_list]");
				goto end;
			}
			OpenAPI_gnss_positioning_method_and_usage_t *
			        gnss_positioning_data_listItem =
				OpenAPI_gnss_positioning_method_and_usage_parseFromJSON
				        (gnss_positioning_data_list_local);
			if(!gnss_positioning_data_listItem) {
				ogs_error("No gnss_positioning_data_listItem");
				goto end;
			}
			OpenAPI_list_add(gnss_positioning_data_listList,
			                 gnss_positioning_data_listItem);
		}
	}

	serving_lm_fidentification =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "servingLMFidentification");
	if(serving_lm_fidentification) {
		if(!cJSON_IsString(serving_lm_fidentification) &&
		   !cJSON_IsNull(serving_lm_fidentification))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [serving_lm_fidentification]");
			goto end;
		}
	}

	termination_cause =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "terminationCause");
	if(termination_cause) {
		if(!cJSON_IsString(termination_cause)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [termination_cause]");
			goto end;
		}
		termination_causeVariable =
			OpenAPI_termination_cause_FromString(
				termination_cause->valuestring);
	}

	velocity_estimate =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "velocityEstimate");
	if(velocity_estimate) {
		velocity_estimate_local_nonprim =
			OpenAPI_velocity_estimate_parseFromJSON(
				velocity_estimate);
		if(!velocity_estimate_local_nonprim) {
			ogs_error(
				"OpenAPI_velocity_estimate_parseFromJSON failed [velocity_estimate]");
			goto end;
		}
	}

	altitude = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
	                                            "altitude");
	if(altitude) {
		if(!cJSON_IsNumber(altitude)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [altitude]");
			goto end;
		}
	}

	achieved_qos = cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
	                                                "achievedQos");
	if(achieved_qos) {
		achieved_qos_local_nonprim =
			OpenAPI_minor_location_qo_s_parseFromJSON(achieved_qos);
		if(!achieved_qos_local_nonprim) {
			ogs_error(
				"OpenAPI_minor_location_qo_s_parseFromJSON failed [achieved_qos]");
			goto end;
		}
	}

	supported_features =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "supportedFeatures");
	if(supported_features) {
		if(!cJSON_IsString(supported_features) &&
		   !cJSON_IsNull(supported_features))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [supported_features]");
			goto end;
		}
	}

	indoor_outdoor_ind =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "indoorOutdoorInd");
	if(indoor_outdoor_ind) {
		if(!cJSON_IsString(indoor_outdoor_ind)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [indoor_outdoor_ind]");
			goto end;
		}
		indoor_outdoor_indVariable =
			OpenAPI_indoor_outdoor_ind_FromString(
				indoor_outdoor_ind->valuestring);
	}

	ha_gnss_metrics =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "haGnssMetrics");
	if(ha_gnss_metrics) {
		ha_gnss_metrics_local_nonprim =
			OpenAPI_high_accuracy_gnss_metrics_parseFromJSON(
				ha_gnss_metrics);
		if(!ha_gnss_metrics_local_nonprim) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON failed [ha_gnss_metrics]");
			goto end;
		}
	}

	los_nlos_measure_ind =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "losNlosMeasureInd");
	if(los_nlos_measure_ind) {
		if(!cJSON_IsString(los_nlos_measure_ind)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [los_nlos_measure_ind]");
			goto end;
		}
		los_nlos_measure_indVariable =
			OpenAPI_los_nlos_measure_ind_FromString(
				los_nlos_measure_ind->valuestring);
	}

	up_loc_rep_stat_af =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "upLocRepStatAf");
	if(up_loc_rep_stat_af) {
		if(!cJSON_IsNumber(up_loc_rep_stat_af)) {
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [up_loc_rep_stat_af]");
			goto end;
		}
	}

	related_applicationlayer_id =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "relatedApplicationlayerId");
	if(related_applicationlayer_id) {
		if(!cJSON_IsString(related_applicationlayer_id) &&
		   !cJSON_IsNull(related_applicationlayer_id))
		{
			ogs_error(
				"OpenAPI_event_notify_data_parseFromJSON() failed [related_applicationlayer_id]");
			goto end;
		}
	}

	distance_direction =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "distanceDirection");
	if(distance_direction) {
		distance_direction_local_nonprim =
			OpenAPI_range_direction_parseFromJSON(
				distance_direction);
		if(!distance_direction_local_nonprim) {
			ogs_error(
				"OpenAPI_range_direction_parseFromJSON failed [distance_direction]");
			goto end;
		}
	}

	_2d_relative_location =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "2dRelativeLocation");
	if(_2d_relative_location) {
		_2d_relative_location_local_nonprim =
			OpenAPI_model_2_d_relative_location_parseFromJSON(
				_2d_relative_location);
		if(!_2d_relative_location_local_nonprim) {
			ogs_error(
				"OpenAPI_model_2_d_relative_location_parseFromJSON failed [_2d_relative_location]");
			goto end;
		}
	}

	_3d_relative_location =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "3dRelativeLocation");
	if(_3d_relative_location) {
		_3d_relative_location_local_nonprim =
			OpenAPI_model_3_d_relative_location_parseFromJSON(
				_3d_relative_location);
		if(!_3d_relative_location_local_nonprim) {
			ogs_error(
				"OpenAPI_model_3_d_relative_location_parseFromJSON failed [_3d_relative_location]");
			goto end;
		}
	}

	relative_velocity =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "relativeVelocity");
	if(relative_velocity) {
		relative_velocity_local_nonprim =
			OpenAPI_velocity_estimate_parseFromJSON(
				relative_velocity);
		if(!relative_velocity_local_nonprim) {
			ogs_error(
				"OpenAPI_velocity_estimate_parseFromJSON failed [relative_velocity]");
			goto end;
		}
	}

	integrity_result =
		cJSON_GetObjectItemCaseSensitive(event_notify_dataJSON,
		                                 "integrityResult");
	if(integrity_result) {
		integrity_result_local_nonprim =
			OpenAPI_integrity_result_parseFromJSON(
				integrity_result);
		if(!integrity_result_local_nonprim) {
			ogs_error(
				"OpenAPI_integrity_result_parseFromJSON failed [integrity_result]");
			goto end;
		}
	}

	event_notify_data_local_var = OpenAPI_event_notify_data_create(
		reported_event_typeVariable,
		supi &&
		!cJSON_IsNull(supi) ? ogs_strdup(supi->valuestring) : NULL,
		gpsi &&
		!cJSON_IsNull(gpsi) ? ogs_strdup(gpsi->valuestring) : NULL,
		hgmlc_call_back_uri &&
		!cJSON_IsNull(hgmlc_call_back_uri) ?
		ogs_strdup(hgmlc_call_back_uri->valuestring) : NULL,
		ogs_strdup(ldr_reference->valuestring),
		lir_reference &&
		!cJSON_IsNull(lir_reference) ?
		ogs_strdup(lir_reference->valuestring) : NULL,
		location_estimate ? location_estimate_local_nonprim : NULL,
		age_of_location_estimate ? true : false,
		age_of_location_estimate ?
		age_of_location_estimate->valuedouble : 0,
		timestamp_of_location_estimate &&
		!cJSON_IsNull(timestamp_of_location_estimate) ?
		ogs_strdup(timestamp_of_location_estimate->valuestring) : NULL,
		civic_address ? civic_address_local_nonprim : NULL,
		local_location_estimate ?
		local_location_estimate_local_nonprim : NULL,
		positioning_data_list ? positioning_data_listList : NULL,
		gnss_positioning_data_list ? gnss_positioning_data_listList :
		NULL,
		serving_lm_fidentification &&
		!cJSON_IsNull(serving_lm_fidentification) ?
		ogs_strdup(serving_lm_fidentification->valuestring) : NULL,
		termination_cause ? termination_causeVariable : 0,
		velocity_estimate ? velocity_estimate_local_nonprim : NULL,
		altitude ? true : false,
		altitude ? altitude->valuedouble : 0,
		achieved_qos ? achieved_qos_local_nonprim : NULL,
		supported_features &&
		!cJSON_IsNull(supported_features) ?
		ogs_strdup(supported_features->valuestring) : NULL,
		indoor_outdoor_ind ? indoor_outdoor_indVariable : 0,
		ha_gnss_metrics ? ha_gnss_metrics_local_nonprim : NULL,
		los_nlos_measure_ind ? los_nlos_measure_indVariable : 0,
		up_loc_rep_stat_af ? true : false,
		up_loc_rep_stat_af ? up_loc_rep_stat_af->valuedouble : 0,
		related_applicationlayer_id &&
		!cJSON_IsNull(related_applicationlayer_id) ?
		ogs_strdup(related_applicationlayer_id->valuestring) : NULL,
		distance_direction ? distance_direction_local_nonprim : NULL,
		_2d_relative_location ? _2d_relative_location_local_nonprim :
		NULL,
		_3d_relative_location ? _3d_relative_location_local_nonprim :
		NULL,
		relative_velocity ? relative_velocity_local_nonprim : NULL,
		integrity_result ? integrity_result_local_nonprim : NULL
		);

	return event_notify_data_local_var;
end:
	if(location_estimate_local_nonprim) {
		OpenAPI_geographic_area_free(location_estimate_local_nonprim);
		location_estimate_local_nonprim = NULL;
	}
	if(civic_address_local_nonprim) {
		OpenAPI_civic_address_free(civic_address_local_nonprim);
		civic_address_local_nonprim = NULL;
	}
	if(local_location_estimate_local_nonprim) {
		OpenAPI_local_area_free(local_location_estimate_local_nonprim);
		local_location_estimate_local_nonprim = NULL;
	}
	if(positioning_data_listList) {
		OpenAPI_list_for_each(positioning_data_listList, node) {
			OpenAPI_positioning_method_and_usage_free(node->data);
		}
		OpenAPI_list_free(positioning_data_listList);
		positioning_data_listList = NULL;
	}
	if(gnss_positioning_data_listList) {
		OpenAPI_list_for_each(gnss_positioning_data_listList, node) {
			OpenAPI_gnss_positioning_method_and_usage_free(
				node->data);
		}
		OpenAPI_list_free(gnss_positioning_data_listList);
		gnss_positioning_data_listList = NULL;
	}
	if(velocity_estimate_local_nonprim) {
		OpenAPI_velocity_estimate_free(velocity_estimate_local_nonprim);
		velocity_estimate_local_nonprim = NULL;
	}
	if(achieved_qos_local_nonprim) {
		OpenAPI_minor_location_qo_s_free(achieved_qos_local_nonprim);
		achieved_qos_local_nonprim = NULL;
	}
	if(ha_gnss_metrics_local_nonprim) {
		OpenAPI_high_accuracy_gnss_metrics_free(
			ha_gnss_metrics_local_nonprim);
		ha_gnss_metrics_local_nonprim = NULL;
	}
	if(distance_direction_local_nonprim) {
		OpenAPI_range_direction_free(distance_direction_local_nonprim);
		distance_direction_local_nonprim = NULL;
	}
	if(_2d_relative_location_local_nonprim) {
		OpenAPI_model_2_d_relative_location_free(
			_2d_relative_location_local_nonprim);
		_2d_relative_location_local_nonprim = NULL;
	}
	if(_3d_relative_location_local_nonprim) {
		OpenAPI_model_3_d_relative_location_free(
			_3d_relative_location_local_nonprim);
		_3d_relative_location_local_nonprim = NULL;
	}
	if(relative_velocity_local_nonprim) {
		OpenAPI_velocity_estimate_free(relative_velocity_local_nonprim);
		relative_velocity_local_nonprim = NULL;
	}
	if(integrity_result_local_nonprim) {
		OpenAPI_integrity_result_free(integrity_result_local_nonprim);
		integrity_result_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_event_notify_data_t *OpenAPI_event_notify_data_copy(
	OpenAPI_event_notify_data_t *dst, OpenAPI_event_notify_data_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_event_notify_data_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_event_notify_data_convertToJSON() failed");
		return NULL;
	}

	content = cJSON_Print(item);
	cJSON_Delete(item);

	if(!content) {
		ogs_error("cJSON_Print() failed");
		return NULL;
	}

	item = cJSON_Parse(content);
	ogs_free(content);
	if(!item) {
		ogs_error("cJSON_Parse() failed");
		return NULL;
	}

	OpenAPI_event_notify_data_free(dst);
	dst = OpenAPI_event_notify_data_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
