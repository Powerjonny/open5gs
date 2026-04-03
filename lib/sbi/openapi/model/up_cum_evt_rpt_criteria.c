#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "up_cum_evt_rpt_criteria.h"

OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_create(
	bool is_evt_rpt_time_criteria, int evt_rpt_time_criteria,
	bool is_evt_rpt_count_criteria, int evt_rpt_count_criteria) {
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria_local_var =
		ogs_malloc(sizeof(OpenAPI_up_cum_evt_rpt_criteria_t));
	ogs_assert(up_cum_evt_rpt_criteria_local_var);

	up_cum_evt_rpt_criteria_local_var->is_evt_rpt_time_criteria =
		is_evt_rpt_time_criteria;
	up_cum_evt_rpt_criteria_local_var->evt_rpt_time_criteria =
		evt_rpt_time_criteria;
	up_cum_evt_rpt_criteria_local_var->is_evt_rpt_count_criteria =
		is_evt_rpt_count_criteria;
	up_cum_evt_rpt_criteria_local_var->evt_rpt_count_criteria =
		evt_rpt_count_criteria;

	return up_cum_evt_rpt_criteria_local_var;
}

void OpenAPI_up_cum_evt_rpt_criteria_free(
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == up_cum_evt_rpt_criteria) {
		return;
	}
	ogs_free(up_cum_evt_rpt_criteria);
}

cJSON *OpenAPI_up_cum_evt_rpt_criteria_convertToJSON(
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(up_cum_evt_rpt_criteria == NULL) {
		ogs_error(
			"OpenAPI_up_cum_evt_rpt_criteria_convertToJSON() failed [UpCumEvtRptCriteria]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(up_cum_evt_rpt_criteria->is_evt_rpt_time_criteria) {
		if(cJSON_AddNumberToObject(item, "evtRptTimeCriteria",
		                           up_cum_evt_rpt_criteria->
		                           evt_rpt_time_criteria) == NULL)
		{
			ogs_error(
				"OpenAPI_up_cum_evt_rpt_criteria_convertToJSON() failed [evt_rpt_time_criteria]");
			goto end;
		}
	}

	if(up_cum_evt_rpt_criteria->is_evt_rpt_count_criteria) {
		if(cJSON_AddNumberToObject(item, "evtRptCountCriteria",
		                           up_cum_evt_rpt_criteria->
		                           evt_rpt_count_criteria) == NULL)
		{
			ogs_error(
				"OpenAPI_up_cum_evt_rpt_criteria_convertToJSON() failed [evt_rpt_count_criteria]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_parseFromJSON
        (cJSON *up_cum_evt_rpt_criteriaJSON) {
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *evt_rpt_time_criteria = NULL;
	cJSON *evt_rpt_count_criteria = NULL;
	evt_rpt_time_criteria =
		cJSON_GetObjectItemCaseSensitive(up_cum_evt_rpt_criteriaJSON,
		                                 "evtRptTimeCriteria");
	if(evt_rpt_time_criteria) {
		if(!cJSON_IsNumber(evt_rpt_time_criteria)) {
			ogs_error(
				"OpenAPI_up_cum_evt_rpt_criteria_parseFromJSON() failed [evt_rpt_time_criteria]");
			goto end;
		}
	}

	evt_rpt_count_criteria =
		cJSON_GetObjectItemCaseSensitive(up_cum_evt_rpt_criteriaJSON,
		                                 "evtRptCountCriteria");
	if(evt_rpt_count_criteria) {
		if(!cJSON_IsNumber(evt_rpt_count_criteria)) {
			ogs_error(
				"OpenAPI_up_cum_evt_rpt_criteria_parseFromJSON() failed [evt_rpt_count_criteria]");
			goto end;
		}
	}

	up_cum_evt_rpt_criteria_local_var =
		OpenAPI_up_cum_evt_rpt_criteria_create(
			evt_rpt_time_criteria ? true : false,
			evt_rpt_time_criteria ?
			evt_rpt_time_criteria->valuedouble : 0,
			evt_rpt_count_criteria ? true : false,
			evt_rpt_count_criteria ?
			evt_rpt_count_criteria->valuedouble : 0
			);

	return up_cum_evt_rpt_criteria_local_var;
end:
	return NULL;
}

OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_copy(
	OpenAPI_up_cum_evt_rpt_criteria_t	*dst,
	OpenAPI_up_cum_evt_rpt_criteria_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_up_cum_evt_rpt_criteria_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_up_cum_evt_rpt_criteria_convertToJSON() failed");
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

	OpenAPI_up_cum_evt_rpt_criteria_free(dst);
	dst = OpenAPI_up_cum_evt_rpt_criteria_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
