#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "high_accuracy_gnss_metrics.h"

OpenAPI_high_accuracy_gnss_metrics_t *OpenAPI_high_accuracy_gnss_metrics_create(
	bool is_nr_of_used_satellites, int nr_of_used_satellites, bool is_hdopi,
	int hdopi, bool is_pdopi, int pdopi, bool is_age, int age,
	OpenAPI_fix_type_e fix_type) {
	OpenAPI_high_accuracy_gnss_metrics_t *
	        high_accuracy_gnss_metrics_local_var =
		ogs_malloc(sizeof(OpenAPI_high_accuracy_gnss_metrics_t));
	ogs_assert(high_accuracy_gnss_metrics_local_var);

	high_accuracy_gnss_metrics_local_var->is_nr_of_used_satellites =
		is_nr_of_used_satellites;
	high_accuracy_gnss_metrics_local_var->nr_of_used_satellites =
		nr_of_used_satellites;
	high_accuracy_gnss_metrics_local_var->is_hdopi = is_hdopi;
	high_accuracy_gnss_metrics_local_var->hdopi = hdopi;
	high_accuracy_gnss_metrics_local_var->is_pdopi = is_pdopi;
	high_accuracy_gnss_metrics_local_var->pdopi = pdopi;
	high_accuracy_gnss_metrics_local_var->is_age = is_age;
	high_accuracy_gnss_metrics_local_var->age = age;
	high_accuracy_gnss_metrics_local_var->fix_type = fix_type;

	return high_accuracy_gnss_metrics_local_var;
}

void OpenAPI_high_accuracy_gnss_metrics_free(
	OpenAPI_high_accuracy_gnss_metrics_t *high_accuracy_gnss_metrics) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == high_accuracy_gnss_metrics) {
		return;
	}
	ogs_free(high_accuracy_gnss_metrics);
}

cJSON *OpenAPI_high_accuracy_gnss_metrics_convertToJSON(
	OpenAPI_high_accuracy_gnss_metrics_t *high_accuracy_gnss_metrics) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(high_accuracy_gnss_metrics == NULL) {
		ogs_error(
			"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [HighAccuracyGnssMetrics]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(high_accuracy_gnss_metrics->is_nr_of_used_satellites) {
		if(cJSON_AddNumberToObject(item, "nrOfUsedSatellites",
		                           high_accuracy_gnss_metrics->
		                           nr_of_used_satellites) == NULL)
		{
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [nr_of_used_satellites]");
			goto end;
		}
	}

	if(high_accuracy_gnss_metrics->is_hdopi) {
		if(cJSON_AddNumberToObject(item, "hdopi",
		                           high_accuracy_gnss_metrics->hdopi) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [hdopi]");
			goto end;
		}
	}

	if(high_accuracy_gnss_metrics->is_pdopi) {
		if(cJSON_AddNumberToObject(item, "pdopi",
		                           high_accuracy_gnss_metrics->pdopi) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [pdopi]");
			goto end;
		}
	}

	if(high_accuracy_gnss_metrics->is_age) {
		if(cJSON_AddNumberToObject(item, "age",
		                           high_accuracy_gnss_metrics->age) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [age]");
			goto end;
		}
	}

	if(high_accuracy_gnss_metrics->fix_type != OpenAPI_fix_type_NULL) {
		if(cJSON_AddStringToObject(item, "fixType",
		                           OpenAPI_fix_type_ToString(
						   high_accuracy_gnss_metrics->
						   fix_type)) == NULL)
		{
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed [fix_type]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_high_accuracy_gnss_metrics_t *
OpenAPI_high_accuracy_gnss_metrics_parseFromJSON(
	cJSON *high_accuracy_gnss_metricsJSON) {
	OpenAPI_high_accuracy_gnss_metrics_t *
	        high_accuracy_gnss_metrics_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *nr_of_used_satellites = NULL;
	cJSON *hdopi = NULL;
	cJSON *pdopi = NULL;
	cJSON *age = NULL;
	cJSON *fix_type = NULL;
	OpenAPI_fix_type_e fix_typeVariable = 0;
	nr_of_used_satellites =
		cJSON_GetObjectItemCaseSensitive(high_accuracy_gnss_metricsJSON,
		                                 "nrOfUsedSatellites");
	if(nr_of_used_satellites) {
		if(!cJSON_IsNumber(nr_of_used_satellites)) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON() failed [nr_of_used_satellites]");
			goto end;
		}
	}

	hdopi = cJSON_GetObjectItemCaseSensitive(high_accuracy_gnss_metricsJSON,
	                                         "hdopi");
	if(hdopi) {
		if(!cJSON_IsNumber(hdopi)) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON() failed [hdopi]");
			goto end;
		}
	}

	pdopi = cJSON_GetObjectItemCaseSensitive(high_accuracy_gnss_metricsJSON,
	                                         "pdopi");
	if(pdopi) {
		if(!cJSON_IsNumber(pdopi)) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON() failed [pdopi]");
			goto end;
		}
	}

	age = cJSON_GetObjectItemCaseSensitive(high_accuracy_gnss_metricsJSON,
	                                       "age");
	if(age) {
		if(!cJSON_IsNumber(age)) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON() failed [age]");
			goto end;
		}
	}

	fix_type =
		cJSON_GetObjectItemCaseSensitive(high_accuracy_gnss_metricsJSON,
		                                 "fixType");
	if(fix_type) {
		if(!cJSON_IsString(fix_type)) {
			ogs_error(
				"OpenAPI_high_accuracy_gnss_metrics_parseFromJSON() failed [fix_type]");
			goto end;
		}
		fix_typeVariable =
			OpenAPI_fix_type_FromString(fix_type->valuestring);
	}

	high_accuracy_gnss_metrics_local_var =
		OpenAPI_high_accuracy_gnss_metrics_create(
			nr_of_used_satellites ? true : false,
			nr_of_used_satellites ?
			nr_of_used_satellites->valuedouble : 0,
			hdopi ? true : false,
			hdopi ? hdopi->valuedouble : 0,
			pdopi ? true : false,
			pdopi ? pdopi->valuedouble : 0,
			age ? true : false,
			age ? age->valuedouble : 0,
			fix_type ? fix_typeVariable : 0
			);

	return high_accuracy_gnss_metrics_local_var;
end:
	return NULL;
}

OpenAPI_high_accuracy_gnss_metrics_t *OpenAPI_high_accuracy_gnss_metrics_copy(
	OpenAPI_high_accuracy_gnss_metrics_t	*dst,
	OpenAPI_high_accuracy_gnss_metrics_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_high_accuracy_gnss_metrics_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_high_accuracy_gnss_metrics_convertToJSON() failed");
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

	OpenAPI_high_accuracy_gnss_metrics_free(dst);
	dst = OpenAPI_high_accuracy_gnss_metrics_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
