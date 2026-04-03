#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "location_data_ext.h"

char *OpenAPI_remote_ue_indlocation_data_ext_ToString(
	OpenAPI_location_data_ext_remote_ue_ind_e remote_ue_ind) {
	const char *remote_ue_indArray[] = { "NULL", "true" };
	size_t sizeofArray = sizeof(remote_ue_indArray) /
	                     sizeof(remote_ue_indArray[0]);
	if(remote_ue_ind < sizeofArray) {
		return (char *) remote_ue_indArray[remote_ue_ind];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_location_data_ext_remote_ue_ind_e
OpenAPI_remote_ue_indlocation_data_ext_FromString(char *remote_ue_ind) {
	int stringToReturn = 0;
	const char *remote_ue_indArray[] = { "NULL", "true" };
	size_t sizeofArray = sizeof(remote_ue_indArray) /
	                     sizeof(remote_ue_indArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(remote_ue_ind,
		          remote_ue_indArray[stringToReturn]) == 0)
		{
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
char *OpenAPI_nrppa_periodic_indlocation_data_ext_ToString(
	OpenAPI_location_data_ext_nrppa_periodic_ind_e nrppa_periodic_ind) {
	const char *nrppa_periodic_indArray[] = { "NULL", "true" };
	size_t sizeofArray = sizeof(nrppa_periodic_indArray) /
	                     sizeof(nrppa_periodic_indArray[0]);
	if(nrppa_periodic_ind < sizeofArray) {
		return (char *) nrppa_periodic_indArray[nrppa_periodic_ind];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_location_data_ext_nrppa_periodic_ind_e
OpenAPI_nrppa_periodic_indlocation_data_ext_FromString(
	char *nrppa_periodic_ind) {
	int stringToReturn = 0;
	const char *nrppa_periodic_indArray[] = { "NULL", "true" };
	size_t sizeofArray = sizeof(nrppa_periodic_indArray) /
	                     sizeof(nrppa_periodic_indArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(nrppa_periodic_ind,
		          nrppa_periodic_indArray[stringToReturn]) == 0)
		{
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
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
	OpenAPI_list_t *add_location_datas) {
	OpenAPI_location_data_ext_t *location_data_ext_local_var =
		ogs_malloc(sizeof(OpenAPI_location_data_ext_t));
	ogs_assert(location_data_ext_local_var);

	location_data_ext_local_var->location_estimate = location_estimate;
	location_data_ext_local_var->accuracy_fulfilment_indicator =
		accuracy_fulfilment_indicator;
	location_data_ext_local_var->is_age_of_location_estimate =
		is_age_of_location_estimate;
	location_data_ext_local_var->age_of_location_estimate =
		age_of_location_estimate;
	location_data_ext_local_var->timestamp_of_location_estimate =
		timestamp_of_location_estimate;
	location_data_ext_local_var->velocity_estimate = velocity_estimate;
	location_data_ext_local_var->civic_address = civic_address;
	location_data_ext_local_var->local_location_estimate =
		local_location_estimate;
	location_data_ext_local_var->positioning_data_list =
		positioning_data_list;
	location_data_ext_local_var->gnss_positioning_data_list =
		gnss_positioning_data_list;
	location_data_ext_local_var->ecgi = ecgi;
	location_data_ext_local_var->ncgi = ncgi;
	location_data_ext_local_var->remote_ue_ind = remote_ue_ind;
	location_data_ext_local_var->is_altitude = is_altitude;
	location_data_ext_local_var->altitude = altitude;
	location_data_ext_local_var->is_barometric_pressure =
		is_barometric_pressure;
	location_data_ext_local_var->barometric_pressure = barometric_pressure;
	location_data_ext_local_var->serving_lmf_identification =
		serving_lmf_identification;
	location_data_ext_local_var->ue_positioning_cap = ue_positioning_cap;
	location_data_ext_local_var->ue_area_ind = ue_area_ind;
	location_data_ext_local_var->supported_features = supported_features;
	location_data_ext_local_var->achieved_qos = achieved_qos;
	location_data_ext_local_var->is_direct_report_ind =
		is_direct_report_ind;
	location_data_ext_local_var->direct_report_ind = direct_report_ind;
	location_data_ext_local_var->indoor_outdoor_ind = indoor_outdoor_ind;
	location_data_ext_local_var->accepted_periodic_event_info =
		accepted_periodic_event_info;
	location_data_ext_local_var->ha_gnss_metrics = ha_gnss_metrics;
	location_data_ext_local_var->los_nlos_measure_ind =
		los_nlos_measure_ind;
	location_data_ext_local_var->related_applicationlayer_id =
		related_applicationlayer_id;
	location_data_ext_local_var->distance_direction = distance_direction;
	location_data_ext_local_var->_2d_relative_location =
		_2d_relative_location;
	location_data_ext_local_var->_3d_relative_location =
		_3d_relative_location;
	location_data_ext_local_var->relative_velocity = relative_velocity;
	location_data_ext_local_var->ranging_sl_capability =
		ranging_sl_capability;
	location_data_ext_local_var->integrity_result = integrity_result;
	location_data_ext_local_var->nrppa_periodic_ind = nrppa_periodic_ind;
	location_data_ext_local_var->add_location_datas = add_location_datas;

	return location_data_ext_local_var;
}

void OpenAPI_location_data_ext_free(
	OpenAPI_location_data_ext_t *location_data_ext) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == location_data_ext) {
		return;
	}
	if(location_data_ext->location_estimate) {
		OpenAPI_geographic_area_free(
			location_data_ext->location_estimate);
		location_data_ext->location_estimate = NULL;
	}
	if(location_data_ext->timestamp_of_location_estimate) {
		ogs_free(location_data_ext->timestamp_of_location_estimate);
		location_data_ext->timestamp_of_location_estimate = NULL;
	}
	if(location_data_ext->velocity_estimate) {
		OpenAPI_velocity_estimate_free(
			location_data_ext->velocity_estimate);
		location_data_ext->velocity_estimate = NULL;
	}
	if(location_data_ext->civic_address) {
		OpenAPI_civic_address_free(location_data_ext->civic_address);
		location_data_ext->civic_address = NULL;
	}
	if(location_data_ext->local_location_estimate) {
		OpenAPI_local_area_free(
			location_data_ext->local_location_estimate);
		location_data_ext->local_location_estimate = NULL;
	}
	if(location_data_ext->positioning_data_list) {
		OpenAPI_list_for_each(location_data_ext->positioning_data_list,
		                      node) {
			OpenAPI_positioning_method_and_usage_free(node->data);
		}
		OpenAPI_list_free(location_data_ext->positioning_data_list);
		location_data_ext->positioning_data_list = NULL;
	}
	if(location_data_ext->gnss_positioning_data_list) {
		OpenAPI_list_for_each(
			location_data_ext->gnss_positioning_data_list, node) {
			OpenAPI_gnss_positioning_method_and_usage_free(
				node->data);
		}
		OpenAPI_list_free(
			location_data_ext->gnss_positioning_data_list);
		location_data_ext->gnss_positioning_data_list = NULL;
	}
	if(location_data_ext->ecgi) {
		OpenAPI_ecgi_free(location_data_ext->ecgi);
		location_data_ext->ecgi = NULL;
	}
	if(location_data_ext->ncgi) {
		OpenAPI_ncgi_free(location_data_ext->ncgi);
		location_data_ext->ncgi = NULL;
	}
	if(location_data_ext->serving_lmf_identification) {
		ogs_free(location_data_ext->serving_lmf_identification);
		location_data_ext->serving_lmf_identification = NULL;
	}
	if(location_data_ext->ue_positioning_cap) {
		ogs_free(location_data_ext->ue_positioning_cap);
		location_data_ext->ue_positioning_cap = NULL;
	}
	if(location_data_ext->ue_area_ind) {
		OpenAPI_ue_area_indication_free(location_data_ext->ue_area_ind);
		location_data_ext->ue_area_ind = NULL;
	}
	if(location_data_ext->supported_features) {
		ogs_free(location_data_ext->supported_features);
		location_data_ext->supported_features = NULL;
	}
	if(location_data_ext->achieved_qos) {
		OpenAPI_minor_location_qo_s_free(
			location_data_ext->achieved_qos);
		location_data_ext->achieved_qos = NULL;
	}
	if(location_data_ext->accepted_periodic_event_info) {
		OpenAPI_periodic_event_info_free(
			location_data_ext->accepted_periodic_event_info);
		location_data_ext->accepted_periodic_event_info = NULL;
	}
	if(location_data_ext->ha_gnss_metrics) {
		OpenAPI_high_accuracy_gnss_metrics_free(
			location_data_ext->ha_gnss_metrics);
		location_data_ext->ha_gnss_metrics = NULL;
	}
	if(location_data_ext->related_applicationlayer_id) {
		ogs_free(location_data_ext->related_applicationlayer_id);
		location_data_ext->related_applicationlayer_id = NULL;
	}
	if(location_data_ext->distance_direction) {
		OpenAPI_range_direction_free(
			location_data_ext->distance_direction);
		location_data_ext->distance_direction = NULL;
	}
	if(location_data_ext->_2d_relative_location) {
		OpenAPI_model_2_d_relative_location_free(
			location_data_ext->_2d_relative_location);
		location_data_ext->_2d_relative_location = NULL;
	}
	if(location_data_ext->_3d_relative_location) {
		OpenAPI_model_3_d_relative_location_free(
			location_data_ext->_3d_relative_location);
		location_data_ext->_3d_relative_location = NULL;
	}
	if(location_data_ext->relative_velocity) {
		OpenAPI_velocity_estimate_free(
			location_data_ext->relative_velocity);
		location_data_ext->relative_velocity = NULL;
	}
	if(location_data_ext->ranging_sl_capability) {
		ogs_free(location_data_ext->ranging_sl_capability);
		location_data_ext->ranging_sl_capability = NULL;
	}
	if(location_data_ext->integrity_result) {
		OpenAPI_integrity_result_free(
			location_data_ext->integrity_result);
		location_data_ext->integrity_result = NULL;
	}
	if(location_data_ext->add_location_datas) {
		OpenAPI_list_for_each(location_data_ext->add_location_datas,
		                      node) {
			OpenAPI_location_data_free(node->data);
		}
		OpenAPI_list_free(location_data_ext->add_location_datas);
		location_data_ext->add_location_datas = NULL;
	}
	ogs_free(location_data_ext);
}

cJSON *OpenAPI_location_data_ext_convertToJSON(
	OpenAPI_location_data_ext_t *location_data_ext) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(location_data_ext == NULL) {
		ogs_error(
			"OpenAPI_location_data_ext_convertToJSON() failed [LocationDataExt]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!location_data_ext->location_estimate) {
		ogs_error(
			"OpenAPI_location_data_ext_convertToJSON() failed [location_estimate]");
		return NULL;
	}
	cJSON *location_estimate_local_JSON =
		OpenAPI_geographic_area_convertToJSON(
			location_data_ext->location_estimate);
	if(location_estimate_local_JSON == NULL) {
		ogs_error(
			"OpenAPI_location_data_ext_convertToJSON() failed [location_estimate]");
		goto end;
	}
	cJSON_AddItemToObject(item, "locationEstimate",
	                      location_estimate_local_JSON);
	if(item->child == NULL) {
		ogs_error(
			"OpenAPI_location_data_ext_convertToJSON() failed [location_estimate]");
		goto end;
	}

	if(location_data_ext->accuracy_fulfilment_indicator !=
	   OpenAPI_accuracy_fulfilment_indicator_NULL)
	{
		if(cJSON_AddStringToObject(item, "accuracyFulfilmentIndicator",
		                           OpenAPI_accuracy_fulfilment_indicator_ToString
		                                   (location_data_ext->
		                                   accuracy_fulfilment_indicator))
		   == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [accuracy_fulfilment_indicator]");
			goto end;
		}
	}

	if(location_data_ext->is_age_of_location_estimate) {
		if(cJSON_AddNumberToObject(item, "ageOfLocationEstimate",
		                           location_data_ext->
		                           age_of_location_estimate) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [age_of_location_estimate]");
			goto end;
		}
	}

	if(location_data_ext->timestamp_of_location_estimate) {
		if(cJSON_AddStringToObject(item, "timestampOfLocationEstimate",
		                           location_data_ext->
		                           timestamp_of_location_estimate) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [timestamp_of_location_estimate]");
			goto end;
		}
	}

	if(location_data_ext->velocity_estimate) {
		cJSON *velocity_estimate_local_JSON =
			OpenAPI_velocity_estimate_convertToJSON(
				location_data_ext->velocity_estimate);
		if(velocity_estimate_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [velocity_estimate]");
			goto end;
		}
		cJSON_AddItemToObject(item, "velocityEstimate",
		                      velocity_estimate_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [velocity_estimate]");
			goto end;
		}
	}

	if(location_data_ext->civic_address) {
		cJSON *civic_address_local_JSON =
			OpenAPI_civic_address_convertToJSON(
				location_data_ext->civic_address);
		if(civic_address_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [civic_address]");
			goto end;
		}
		cJSON_AddItemToObject(item, "civicAddress",
		                      civic_address_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [civic_address]");
			goto end;
		}
	}

	if(location_data_ext->local_location_estimate) {
		cJSON *local_location_estimate_local_JSON =
			OpenAPI_local_area_convertToJSON(
				location_data_ext->local_location_estimate);
		if(local_location_estimate_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [local_location_estimate]");
			goto end;
		}
		cJSON_AddItemToObject(item, "localLocationEstimate",
		                      local_location_estimate_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [local_location_estimate]");
			goto end;
		}
	}

	if(location_data_ext->positioning_data_list) {
		cJSON *positioning_data_listList = cJSON_AddArrayToObject(item,
		                                                          "positioningDataList");
		if(positioning_data_listList == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [positioning_data_list]");
			goto end;
		}
		OpenAPI_list_for_each(location_data_ext->positioning_data_list,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_positioning_method_and_usage_convertToJSON
				        (node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_location_data_ext_convertToJSON() failed [positioning_data_list]");
				goto end;
			}
			cJSON_AddItemToArray(positioning_data_listList,
			                     itemLocal);
		}
	}

	if(location_data_ext->gnss_positioning_data_list) {
		cJSON *gnss_positioning_data_listList =
			cJSON_AddArrayToObject(item, "gnssPositioningDataList");
		if(gnss_positioning_data_listList == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [gnss_positioning_data_list]");
			goto end;
		}
		OpenAPI_list_for_each(
			location_data_ext->gnss_positioning_data_list, node) {
			cJSON *itemLocal =
				OpenAPI_gnss_positioning_method_and_usage_convertToJSON
				        (node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_location_data_ext_convertToJSON() failed [gnss_positioning_data_list]");
				goto end;
			}
			cJSON_AddItemToArray(gnss_positioning_data_listList,
			                     itemLocal);
		}
	}

	if(location_data_ext->ecgi) {
		cJSON *ecgi_local_JSON =
			OpenAPI_ecgi_convertToJSON(location_data_ext->ecgi);
		if(ecgi_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ecgi]");
			goto end;
		}
		cJSON_AddItemToObject(item, "ecgi", ecgi_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ecgi]");
			goto end;
		}
	}

	if(location_data_ext->ncgi) {
		cJSON *ncgi_local_JSON =
			OpenAPI_ncgi_convertToJSON(location_data_ext->ncgi);
		if(ncgi_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ncgi]");
			goto end;
		}
		cJSON_AddItemToObject(item, "ncgi", ncgi_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ncgi]");
			goto end;
		}
	}

	if(location_data_ext->remote_ue_ind !=
	   OpenAPI_location_data_ext_REMOTEUEIND_NULL)
	{
		if(cJSON_AddStringToObject(item, "remoteUeInd",
		                           OpenAPI_remote_ue_indlocation_data_ext_ToString
		                                   (location_data_ext->
		                                   remote_ue_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [remote_ue_ind]");
			goto end;
		}
	}

	if(location_data_ext->is_altitude) {
		if(cJSON_AddNumberToObject(item, "altitude",
		                           location_data_ext->altitude) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [altitude]");
			goto end;
		}
	}

	if(location_data_ext->is_barometric_pressure) {
		if(cJSON_AddNumberToObject(item, "barometricPressure",
		                           location_data_ext->
		                           barometric_pressure) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [barometric_pressure]");
			goto end;
		}
	}

	if(location_data_ext->serving_lmf_identification) {
		if(cJSON_AddStringToObject(item, "servingLMFIdentification",
		                           location_data_ext->
		                           serving_lmf_identification) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [serving_lmf_identification]");
			goto end;
		}
	}

	if(location_data_ext->ue_positioning_cap) {
		if(cJSON_AddStringToObject(item, "uePositioningCap",
		                           location_data_ext->ue_positioning_cap)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ue_positioning_cap]");
			goto end;
		}
	}

	if(location_data_ext->ue_area_ind) {
		cJSON *ue_area_ind_local_JSON =
			OpenAPI_ue_area_indication_convertToJSON(
				location_data_ext->ue_area_ind);
		if(ue_area_ind_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ue_area_ind]");
			goto end;
		}
		cJSON_AddItemToObject(item, "ueAreaInd",
		                      ue_area_ind_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ue_area_ind]");
			goto end;
		}
	}

	if(location_data_ext->supported_features) {
		if(cJSON_AddStringToObject(item, "supportedFeatures",
		                           location_data_ext->supported_features)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [supported_features]");
			goto end;
		}
	}

	if(location_data_ext->achieved_qos) {
		cJSON *achieved_qos_local_JSON =
			OpenAPI_minor_location_qo_s_convertToJSON(
				location_data_ext->achieved_qos);
		if(achieved_qos_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [achieved_qos]");
			goto end;
		}
		cJSON_AddItemToObject(item, "achievedQos",
		                      achieved_qos_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [achieved_qos]");
			goto end;
		}
	}

	if(location_data_ext->is_direct_report_ind) {
		if(cJSON_AddBoolToObject(item, "directReportInd",
		                         location_data_ext->direct_report_ind)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [direct_report_ind]");
			goto end;
		}
	}

	if(location_data_ext->indoor_outdoor_ind !=
	   OpenAPI_indoor_outdoor_ind_NULL)
	{
		if(cJSON_AddStringToObject(item, "indoorOutdoorInd",
		                           OpenAPI_indoor_outdoor_ind_ToString(
						   location_data_ext->
						   indoor_outdoor_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [indoor_outdoor_ind]");
			goto end;
		}
	}

	if(location_data_ext->accepted_periodic_event_info) {
		cJSON *accepted_periodic_event_info_local_JSON =
			OpenAPI_periodic_event_info_convertToJSON(
				location_data_ext->accepted_periodic_event_info);
		if(accepted_periodic_event_info_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [accepted_periodic_event_info]");
			goto end;
		}
		cJSON_AddItemToObject(item, "acceptedPeriodicEventInfo",
		                      accepted_periodic_event_info_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [accepted_periodic_event_info]");
			goto end;
		}
	}

	if(location_data_ext->ha_gnss_metrics) {
		cJSON *ha_gnss_metrics_local_JSON =
			OpenAPI_high_accuracy_gnss_metrics_convertToJSON(
				location_data_ext->ha_gnss_metrics);
		if(ha_gnss_metrics_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ha_gnss_metrics]");
			goto end;
		}
		cJSON_AddItemToObject(item, "haGnssMetrics",
		                      ha_gnss_metrics_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ha_gnss_metrics]");
			goto end;
		}
	}

	if(location_data_ext->los_nlos_measure_ind !=
	   OpenAPI_los_nlos_measure_ind_NULL)
	{
		if(cJSON_AddStringToObject(item, "losNlosMeasureInd",
		                           OpenAPI_los_nlos_measure_ind_ToString
		                                   (location_data_ext->
		                                   los_nlos_measure_ind)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [los_nlos_measure_ind]");
			goto end;
		}
	}

	if(location_data_ext->related_applicationlayer_id) {
		if(cJSON_AddStringToObject(item, "relatedApplicationlayerId",
		                           location_data_ext->
		                           related_applicationlayer_id) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [related_applicationlayer_id]");
			goto end;
		}
	}

	if(location_data_ext->distance_direction) {
		cJSON *distance_direction_local_JSON =
			OpenAPI_range_direction_convertToJSON(
				location_data_ext->distance_direction);
		if(distance_direction_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [distance_direction]");
			goto end;
		}
		cJSON_AddItemToObject(item, "distanceDirection",
		                      distance_direction_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [distance_direction]");
			goto end;
		}
	}

	if(location_data_ext->_2d_relative_location) {
		cJSON *_2d_relative_location_local_JSON =
			OpenAPI_model_2_d_relative_location_convertToJSON(
				location_data_ext->_2d_relative_location);
		if(_2d_relative_location_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [_2d_relative_location]");
			goto end;
		}
		cJSON_AddItemToObject(item, "2dRelativeLocation",
		                      _2d_relative_location_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [_2d_relative_location]");
			goto end;
		}
	}

	if(location_data_ext->_3d_relative_location) {
		cJSON *_3d_relative_location_local_JSON =
			OpenAPI_model_3_d_relative_location_convertToJSON(
				location_data_ext->_3d_relative_location);
		if(_3d_relative_location_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [_3d_relative_location]");
			goto end;
		}
		cJSON_AddItemToObject(item, "3dRelativeLocation",
		                      _3d_relative_location_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [_3d_relative_location]");
			goto end;
		}
	}

	if(location_data_ext->relative_velocity) {
		cJSON *relative_velocity_local_JSON =
			OpenAPI_velocity_estimate_convertToJSON(
				location_data_ext->relative_velocity);
		if(relative_velocity_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [relative_velocity]");
			goto end;
		}
		cJSON_AddItemToObject(item, "relativeVelocity",
		                      relative_velocity_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [relative_velocity]");
			goto end;
		}
	}

	if(location_data_ext->ranging_sl_capability) {
		if(cJSON_AddStringToObject(item, "rangingSlCapability",
		                           location_data_ext->
		                           ranging_sl_capability) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [ranging_sl_capability]");
			goto end;
		}
	}

	if(location_data_ext->integrity_result) {
		cJSON *integrity_result_local_JSON =
			OpenAPI_integrity_result_convertToJSON(
				location_data_ext->integrity_result);
		if(integrity_result_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [integrity_result]");
			goto end;
		}
		cJSON_AddItemToObject(item, "integrityResult",
		                      integrity_result_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [integrity_result]");
			goto end;
		}
	}

	if(location_data_ext->nrppa_periodic_ind !=
	   OpenAPI_location_data_ext_NRPPAPERIODICIND_NULL)
	{
		if(cJSON_AddStringToObject(item, "nrppaPeriodicInd",
		                           OpenAPI_nrppa_periodic_indlocation_data_ext_ToString
		                                   (location_data_ext->
		                                   nrppa_periodic_ind)) == NULL)
		{
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [nrppa_periodic_ind]");
			goto end;
		}
	}

	if(location_data_ext->add_location_datas) {
		cJSON *add_location_datasList = cJSON_AddArrayToObject(item,
		                                                       "addLocationDatas");
		if(add_location_datasList == NULL) {
			ogs_error(
				"OpenAPI_location_data_ext_convertToJSON() failed [add_location_datas]");
			goto end;
		}
		OpenAPI_list_for_each(location_data_ext->add_location_datas,
		                      node) {
			cJSON *itemLocal =
				OpenAPI_location_data_convertToJSON(node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_location_data_ext_convertToJSON() failed [add_location_datas]");
				goto end;
			}
			cJSON_AddItemToArray(add_location_datasList, itemLocal);
		}
	}

end:
	return item;
}

OpenAPI_location_data_ext_t *OpenAPI_location_data_ext_parseFromJSON(
	cJSON *location_data_extJSON) {
	OpenAPI_location_data_ext_t *location_data_ext_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *location_estimate = NULL;
	OpenAPI_geographic_area_t *location_estimate_local_nonprim = NULL;
	cJSON *accuracy_fulfilment_indicator = NULL;
	OpenAPI_accuracy_fulfilment_indicator_e
	        accuracy_fulfilment_indicatorVariable = 0;
	cJSON *age_of_location_estimate = NULL;
	cJSON *timestamp_of_location_estimate = NULL;
	cJSON *velocity_estimate = NULL;
	OpenAPI_velocity_estimate_t *velocity_estimate_local_nonprim = NULL;
	cJSON *civic_address = NULL;
	OpenAPI_civic_address_t *civic_address_local_nonprim = NULL;
	cJSON *local_location_estimate = NULL;
	OpenAPI_local_area_t *local_location_estimate_local_nonprim = NULL;
	cJSON *positioning_data_list = NULL;
	OpenAPI_list_t *positioning_data_listList = NULL;
	cJSON *gnss_positioning_data_list = NULL;
	OpenAPI_list_t *gnss_positioning_data_listList = NULL;
	cJSON *ecgi = NULL;
	OpenAPI_ecgi_t *ecgi_local_nonprim = NULL;
	cJSON *ncgi = NULL;
	OpenAPI_ncgi_t *ncgi_local_nonprim = NULL;
	cJSON *remote_ue_ind = NULL;
	OpenAPI_location_data_ext_remote_ue_ind_e remote_ue_indVariable = 0;
	cJSON *altitude = NULL;
	cJSON *barometric_pressure = NULL;
	cJSON *serving_lmf_identification = NULL;
	cJSON *ue_positioning_cap = NULL;
	cJSON *ue_area_ind = NULL;
	OpenAPI_ue_area_indication_t *ue_area_ind_local_nonprim = NULL;
	cJSON *supported_features = NULL;
	cJSON *achieved_qos = NULL;
	OpenAPI_minor_location_qo_s_t *achieved_qos_local_nonprim = NULL;
	cJSON *direct_report_ind = NULL;
	cJSON *indoor_outdoor_ind = NULL;
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_indVariable = 0;
	cJSON *accepted_periodic_event_info = NULL;
	OpenAPI_periodic_event_info_t *
	        accepted_periodic_event_info_local_nonprim = NULL;
	cJSON *ha_gnss_metrics = NULL;
	OpenAPI_high_accuracy_gnss_metrics_t *ha_gnss_metrics_local_nonprim =
		NULL;
	cJSON *los_nlos_measure_ind = NULL;
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_indVariable = 0;
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
	cJSON *ranging_sl_capability = NULL;
	cJSON *integrity_result = NULL;
	OpenAPI_integrity_result_t *integrity_result_local_nonprim = NULL;
	cJSON *nrppa_periodic_ind = NULL;
	OpenAPI_location_data_ext_nrppa_periodic_ind_e
	        nrppa_periodic_indVariable = 0;
	cJSON *add_location_datas = NULL;
	OpenAPI_list_t *add_location_datasList = NULL;
	location_estimate =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "locationEstimate");
	if(!location_estimate) {
		ogs_error(
			"OpenAPI_location_data_ext_parseFromJSON() failed [location_estimate]");
		goto end;
	}
	location_estimate_local_nonprim =
		OpenAPI_geographic_area_parseFromJSON(location_estimate);
	if(!location_estimate_local_nonprim) {
		ogs_error(
			"OpenAPI_geographic_area_parseFromJSON failed [location_estimate]");
		goto end;
	}

	accuracy_fulfilment_indicator =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "accuracyFulfilmentIndicator");
	if(accuracy_fulfilment_indicator) {
		if(!cJSON_IsString(accuracy_fulfilment_indicator)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [accuracy_fulfilment_indicator]");
			goto end;
		}
		accuracy_fulfilment_indicatorVariable =
			OpenAPI_accuracy_fulfilment_indicator_FromString(
				accuracy_fulfilment_indicator->valuestring);
	}

	age_of_location_estimate =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "ageOfLocationEstimate");
	if(age_of_location_estimate) {
		if(!cJSON_IsNumber(age_of_location_estimate)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [age_of_location_estimate]");
			goto end;
		}
	}

	timestamp_of_location_estimate =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "timestampOfLocationEstimate");
	if(timestamp_of_location_estimate) {
		if(!cJSON_IsString(timestamp_of_location_estimate) &&
		   !cJSON_IsNull(timestamp_of_location_estimate))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [timestamp_of_location_estimate]");
			goto end;
		}
	}

	velocity_estimate =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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

	civic_address = cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "positioningDataList");
	if(positioning_data_list) {
		cJSON *positioning_data_list_local = NULL;
		if(!cJSON_IsArray(positioning_data_list)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [positioning_data_list]");
			goto end;
		}

		positioning_data_listList = OpenAPI_list_create();

		cJSON_ArrayForEach(positioning_data_list_local,
		                   positioning_data_list) {
			if(!cJSON_IsObject(positioning_data_list_local)) {
				ogs_error(
					"OpenAPI_location_data_ext_parseFromJSON() failed [positioning_data_list]");
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "gnssPositioningDataList");
	if(gnss_positioning_data_list) {
		cJSON *gnss_positioning_data_list_local = NULL;
		if(!cJSON_IsArray(gnss_positioning_data_list)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [gnss_positioning_data_list]");
			goto end;
		}

		gnss_positioning_data_listList = OpenAPI_list_create();

		cJSON_ArrayForEach(gnss_positioning_data_list_local,
		                   gnss_positioning_data_list) {
			if(!cJSON_IsObject(gnss_positioning_data_list_local)) {
				ogs_error(
					"OpenAPI_location_data_ext_parseFromJSON() failed [gnss_positioning_data_list]");
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

	ecgi = cJSON_GetObjectItemCaseSensitive(location_data_extJSON, "ecgi");
	if(ecgi) {
		ecgi_local_nonprim = OpenAPI_ecgi_parseFromJSON(ecgi);
		if(!ecgi_local_nonprim) {
			ogs_error("OpenAPI_ecgi_parseFromJSON failed [ecgi]");
			goto end;
		}
	}

	ncgi = cJSON_GetObjectItemCaseSensitive(location_data_extJSON, "ncgi");
	if(ncgi) {
		ncgi_local_nonprim = OpenAPI_ncgi_parseFromJSON(ncgi);
		if(!ncgi_local_nonprim) {
			ogs_error("OpenAPI_ncgi_parseFromJSON failed [ncgi]");
			goto end;
		}
	}

	remote_ue_ind = cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
	                                                 "remoteUeInd");
	if(remote_ue_ind) {
		if(!cJSON_IsString(remote_ue_ind)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [remote_ue_ind]");
			goto end;
		}
		remote_ue_indVariable =
			OpenAPI_remote_ue_indlocation_data_ext_FromString(
				remote_ue_ind->valuestring);
	}

	altitude = cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
	                                            "altitude");
	if(altitude) {
		if(!cJSON_IsNumber(altitude)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [altitude]");
			goto end;
		}
	}

	barometric_pressure =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "barometricPressure");
	if(barometric_pressure) {
		if(!cJSON_IsNumber(barometric_pressure)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [barometric_pressure]");
			goto end;
		}
	}

	serving_lmf_identification =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "servingLMFIdentification");
	if(serving_lmf_identification) {
		if(!cJSON_IsString(serving_lmf_identification) &&
		   !cJSON_IsNull(serving_lmf_identification))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [serving_lmf_identification]");
			goto end;
		}
	}

	ue_positioning_cap =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "uePositioningCap");
	if(ue_positioning_cap) {
		if(!cJSON_IsString(ue_positioning_cap) &&
		   !cJSON_IsNull(ue_positioning_cap))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [ue_positioning_cap]");
			goto end;
		}
	}

	ue_area_ind = cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
	                                               "ueAreaInd");
	if(ue_area_ind) {
		ue_area_ind_local_nonprim =
			OpenAPI_ue_area_indication_parseFromJSON(ue_area_ind);
		if(!ue_area_ind_local_nonprim) {
			ogs_error(
				"OpenAPI_ue_area_indication_parseFromJSON failed [ue_area_ind]");
			goto end;
		}
	}

	supported_features =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "supportedFeatures");
	if(supported_features) {
		if(!cJSON_IsString(supported_features) &&
		   !cJSON_IsNull(supported_features))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [supported_features]");
			goto end;
		}
	}

	achieved_qos = cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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

	direct_report_ind =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "directReportInd");
	if(direct_report_ind) {
		if(!cJSON_IsBool(direct_report_ind)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [direct_report_ind]");
			goto end;
		}
	}

	indoor_outdoor_ind =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "indoorOutdoorInd");
	if(indoor_outdoor_ind) {
		if(!cJSON_IsString(indoor_outdoor_ind)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [indoor_outdoor_ind]");
			goto end;
		}
		indoor_outdoor_indVariable =
			OpenAPI_indoor_outdoor_ind_FromString(
				indoor_outdoor_ind->valuestring);
	}

	accepted_periodic_event_info =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "acceptedPeriodicEventInfo");
	if(accepted_periodic_event_info) {
		accepted_periodic_event_info_local_nonprim =
			OpenAPI_periodic_event_info_parseFromJSON(
				accepted_periodic_event_info);
		if(!accepted_periodic_event_info_local_nonprim) {
			ogs_error(
				"OpenAPI_periodic_event_info_parseFromJSON failed [accepted_periodic_event_info]");
			goto end;
		}
	}

	ha_gnss_metrics =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "losNlosMeasureInd");
	if(los_nlos_measure_ind) {
		if(!cJSON_IsString(los_nlos_measure_ind)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [los_nlos_measure_ind]");
			goto end;
		}
		los_nlos_measure_indVariable =
			OpenAPI_los_nlos_measure_ind_FromString(
				los_nlos_measure_ind->valuestring);
	}

	related_applicationlayer_id =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "relatedApplicationlayerId");
	if(related_applicationlayer_id) {
		if(!cJSON_IsString(related_applicationlayer_id) &&
		   !cJSON_IsNull(related_applicationlayer_id))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [related_applicationlayer_id]");
			goto end;
		}
	}

	distance_direction =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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

	ranging_sl_capability =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "rangingSlCapability");
	if(ranging_sl_capability) {
		if(!cJSON_IsString(ranging_sl_capability) &&
		   !cJSON_IsNull(ranging_sl_capability))
		{
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [ranging_sl_capability]");
			goto end;
		}
	}

	integrity_result =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
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

	nrppa_periodic_ind =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "nrppaPeriodicInd");
	if(nrppa_periodic_ind) {
		if(!cJSON_IsString(nrppa_periodic_ind)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [nrppa_periodic_ind]");
			goto end;
		}
		nrppa_periodic_indVariable =
			OpenAPI_nrppa_periodic_indlocation_data_ext_FromString(
				nrppa_periodic_ind->valuestring);
	}

	add_location_datas =
		cJSON_GetObjectItemCaseSensitive(location_data_extJSON,
		                                 "addLocationDatas");
	if(add_location_datas) {
		cJSON *add_location_datas_local = NULL;
		if(!cJSON_IsArray(add_location_datas)) {
			ogs_error(
				"OpenAPI_location_data_ext_parseFromJSON() failed [add_location_datas]");
			goto end;
		}

		add_location_datasList = OpenAPI_list_create();

		cJSON_ArrayForEach(add_location_datas_local,
		                   add_location_datas) {
			if(!cJSON_IsObject(add_location_datas_local)) {
				ogs_error(
					"OpenAPI_location_data_ext_parseFromJSON() failed [add_location_datas]");
				goto end;
			}
			OpenAPI_location_data_t *add_location_datasItem =
				OpenAPI_location_data_parseFromJSON(
					add_location_datas_local);
			if(!add_location_datasItem) {
				ogs_error("No add_location_datasItem");
				goto end;
			}
			OpenAPI_list_add(add_location_datasList,
			                 add_location_datasItem);
		}
	}

	location_data_ext_local_var = OpenAPI_location_data_ext_create(
		location_estimate_local_nonprim,
		accuracy_fulfilment_indicator ?
		accuracy_fulfilment_indicatorVariable : 0,
		age_of_location_estimate ? true : false,
		age_of_location_estimate ?
		age_of_location_estimate->valuedouble : 0,
		timestamp_of_location_estimate &&
		!cJSON_IsNull(timestamp_of_location_estimate) ?
		ogs_strdup(timestamp_of_location_estimate->valuestring) : NULL,
		velocity_estimate ? velocity_estimate_local_nonprim : NULL,
		civic_address ? civic_address_local_nonprim : NULL,
		local_location_estimate ?
		local_location_estimate_local_nonprim : NULL,
		positioning_data_list ? positioning_data_listList : NULL,
		gnss_positioning_data_list ? gnss_positioning_data_listList :
		NULL,
		ecgi ? ecgi_local_nonprim : NULL,
		ncgi ? ncgi_local_nonprim : NULL,
		remote_ue_ind ? remote_ue_indVariable : 0,
		altitude ? true : false,
		altitude ? altitude->valuedouble : 0,
		barometric_pressure ? true : false,
		barometric_pressure ? barometric_pressure->valuedouble : 0,
		serving_lmf_identification &&
		!cJSON_IsNull(serving_lmf_identification) ?
		ogs_strdup(serving_lmf_identification->valuestring) : NULL,
		ue_positioning_cap &&
		!cJSON_IsNull(ue_positioning_cap) ?
		ogs_strdup(ue_positioning_cap->valuestring) : NULL,
		ue_area_ind ? ue_area_ind_local_nonprim : NULL,
		supported_features &&
		!cJSON_IsNull(supported_features) ?
		ogs_strdup(supported_features->valuestring) : NULL,
		achieved_qos ? achieved_qos_local_nonprim : NULL,
		direct_report_ind ? true : false,
		direct_report_ind ? direct_report_ind->valueint : 0,
		indoor_outdoor_ind ? indoor_outdoor_indVariable : 0,
		accepted_periodic_event_info ?
		accepted_periodic_event_info_local_nonprim : NULL,
		ha_gnss_metrics ? ha_gnss_metrics_local_nonprim : NULL,
		los_nlos_measure_ind ? los_nlos_measure_indVariable : 0,
		related_applicationlayer_id &&
		!cJSON_IsNull(related_applicationlayer_id) ?
		ogs_strdup(related_applicationlayer_id->valuestring) : NULL,
		distance_direction ? distance_direction_local_nonprim : NULL,
		_2d_relative_location ? _2d_relative_location_local_nonprim :
		NULL,
		_3d_relative_location ? _3d_relative_location_local_nonprim :
		NULL,
		relative_velocity ? relative_velocity_local_nonprim : NULL,
		ranging_sl_capability &&
		!cJSON_IsNull(ranging_sl_capability) ?
		ogs_strdup(ranging_sl_capability->valuestring) : NULL,
		integrity_result ? integrity_result_local_nonprim : NULL,
		nrppa_periodic_ind ? nrppa_periodic_indVariable : 0,
		add_location_datas ? add_location_datasList : NULL
		);

	return location_data_ext_local_var;
end:
	if(location_estimate_local_nonprim) {
		OpenAPI_geographic_area_free(location_estimate_local_nonprim);
		location_estimate_local_nonprim = NULL;
	}
	if(velocity_estimate_local_nonprim) {
		OpenAPI_velocity_estimate_free(velocity_estimate_local_nonprim);
		velocity_estimate_local_nonprim = NULL;
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
	if(ecgi_local_nonprim) {
		OpenAPI_ecgi_free(ecgi_local_nonprim);
		ecgi_local_nonprim = NULL;
	}
	if(ncgi_local_nonprim) {
		OpenAPI_ncgi_free(ncgi_local_nonprim);
		ncgi_local_nonprim = NULL;
	}
	if(ue_area_ind_local_nonprim) {
		OpenAPI_ue_area_indication_free(ue_area_ind_local_nonprim);
		ue_area_ind_local_nonprim = NULL;
	}
	if(achieved_qos_local_nonprim) {
		OpenAPI_minor_location_qo_s_free(achieved_qos_local_nonprim);
		achieved_qos_local_nonprim = NULL;
	}
	if(accepted_periodic_event_info_local_nonprim) {
		OpenAPI_periodic_event_info_free(
			accepted_periodic_event_info_local_nonprim);
		accepted_periodic_event_info_local_nonprim = NULL;
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
	if(add_location_datasList) {
		OpenAPI_list_for_each(add_location_datasList, node) {
			OpenAPI_location_data_free(node->data);
		}
		OpenAPI_list_free(add_location_datasList);
		add_location_datasList = NULL;
	}
	return NULL;
}

OpenAPI_location_data_ext_t *OpenAPI_location_data_ext_copy(
	OpenAPI_location_data_ext_t *dst, OpenAPI_location_data_ext_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_location_data_ext_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_location_data_ext_convertToJSON() failed");
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

	OpenAPI_location_data_ext_free(dst);
	dst = OpenAPI_location_data_ext_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
