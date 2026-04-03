/*
 * add_location_context.h
 *
 * Information within Location context(s).
 */

#ifndef _OpenAPI_add_location_context_H_
#define _OpenAPI_add_location_context_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "area_event_info.h"
#include "event_report_message.h"
#include "event_reporting_status.h"
#include "indoor_outdoor_ind.h"
#include "ldr_type.h"
#include "location_qo_s.h"
#include "los_nlos_measure_ind.h"
#include "motion_event_info.h"
#include "periodic_event_info.h"
#include "ue_location_info.h"
#include "up_cum_evt_rpt_criteria.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_add_location_context_s OpenAPI_add_location_context_t;
typedef enum { OpenAPI_add_location_context_LCSUPPEXISTIND_NULL = 0,
	       OpenAPI_add_location_context_LCSUPPEXISTIND__true }
OpenAPI_add_location_context_lcs_upp_exist_ind_e;

char * OpenAPI_add_location_context_lcs_upp_exist_ind_ToString(
	OpenAPI_add_location_context_lcs_upp_exist_ind_e lcs_upp_exist_ind);

OpenAPI_add_location_context_lcs_upp_exist_ind_e
OpenAPI_add_location_context_lcs_upp_exist_ind_FromString(
	char *lcs_upp_exist_ind);
typedef struct OpenAPI_add_location_context_s {
	struct OpenAPI_location_qo_s_s *location_qo_s;
	OpenAPI_ldr_type_e ldr_type;
	char *hgmlc_call_back_uri;
	char *ldr_reference;
	struct OpenAPI_periodic_event_info_s *periodic_event_info;
	struct OpenAPI_area_event_info_s *area_event_info;
	struct OpenAPI_motion_event_info_s *motion_event_info;
	struct OpenAPI_event_report_message_s *event_report_message;
	struct OpenAPI_event_reporting_status_s *event_reporting_status;
	struct OpenAPI_ue_location_info_s *ue_location_info;
	char *scheduled_loc_time;
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind;
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind;
	struct OpenAPI_up_cum_evt_rpt_criteria_s *up_cum_evt_rpt_criteria;
	OpenAPI_add_location_context_lcs_upp_exist_ind_e lcs_upp_exist_ind;
} OpenAPI_add_location_context_t;

OpenAPI_add_location_context_t *OpenAPI_add_location_context_create(
	OpenAPI_location_qo_s_t *location_qo_s, OpenAPI_ldr_type_e ldr_type,
	char *hgmlc_call_back_uri, char *ldr_reference,
	OpenAPI_periodic_event_info_t *periodic_event_info,
	OpenAPI_area_event_info_t *area_event_info,
	OpenAPI_motion_event_info_t *motion_event_info,
	OpenAPI_event_report_message_t *event_report_message,
	OpenAPI_event_reporting_status_t *event_reporting_status,
	OpenAPI_ue_location_info_t *ue_location_info, char *scheduled_loc_time,
	OpenAPI_indoor_outdoor_ind_e indoor_outdoor_ind,
	OpenAPI_los_nlos_measure_ind_e los_nlos_measure_ind,
	OpenAPI_up_cum_evt_rpt_criteria_t *up_cum_evt_rpt_criteria,
	OpenAPI_add_location_context_lcs_upp_exist_ind_e lcs_upp_exist_ind);
void OpenAPI_add_location_context_free(
	OpenAPI_add_location_context_t *add_location_context);
OpenAPI_add_location_context_t *OpenAPI_add_location_context_parseFromJSON(
	cJSON *add_location_contextJSON);
cJSON *OpenAPI_add_location_context_convertToJSON(
	OpenAPI_add_location_context_t *add_location_context);
OpenAPI_add_location_context_t *OpenAPI_add_location_context_copy(
	OpenAPI_add_location_context_t	*dst,
	OpenAPI_add_location_context_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_add_location_context_H_ */
