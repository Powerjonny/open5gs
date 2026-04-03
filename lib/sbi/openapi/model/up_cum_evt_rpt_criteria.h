/*
 * up_cum_evt_rpt_criteria.h
 *
 * Criteria for sending cumulative events reports over control plane
 */

#ifndef _OpenAPI_up_cum_evt_rpt_criteria_H_
#define _OpenAPI_up_cum_evt_rpt_criteria_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_up_cum_evt_rpt_criteria_s
        OpenAPI_up_cum_evt_rpt_criteria_t;
typedef struct OpenAPI_up_cum_evt_rpt_criteria_s {
	bool is_evt_rpt_time_criteria;
	int evt_rpt_time_criteria;
	bool is_evt_rpt_count_criteria;
	int evt_rpt_count_criteria;
} OpenAPI_up_cum_evt_rpt_criteria_t;

OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_create(
	bool is_evt_rpt_time_criteria, int evt_rpt_time_criteria,
	bool is_evt_rpt_count_criteria, int evt_rpt_count_criteria);
void OpenAPI_up_cum_evt_rpt_criteria_free(
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria);
OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_parseFromJSON
        (cJSON *up_cum_evt_rpt_criteriaJSON);
cJSON *OpenAPI_up_cum_evt_rpt_criteria_convertToJSON(
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria);
OpenAPI_up_cum_evt_rpt_criteria_t *OpenAPI_up_cum_evt_rpt_criteria_copy(
	OpenAPI_up_cum_evt_rpt_criteria_t	*dst,
	OpenAPI_up_cum_evt_rpt_criteria_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_up_cum_evt_rpt_criteria_H_ */
