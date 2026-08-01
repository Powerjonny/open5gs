/*
 * pc_event_notification.h
 *
 * Represents the information reported for a Policy Control event.
 */

#ifndef _OpenAPI_pc_event_notification_H_
#define _OpenAPI_pc_event_notification_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "access_type.h"
#include "additional_access_info.h"
#include "an_gw_address.h"
#include "failure.h"
#include "pc_event.h"
#include "pdu_session_information.h"
#include "plmn_id_nid.h"
#include "rat_type.h"
#include "satellite_backhaul_category.h"
#include "service_area_coverage_info.h"
#include "service_identification.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_pc_event_notification_s OpenAPI_pc_event_notification_t;
typedef struct OpenAPI_pc_event_notification_s {
	struct OpenAPI_pc_event_s *event;
	OpenAPI_access_type_e acc_type;
	struct OpenAPI_additional_access_info_s *add_access_info;
	struct OpenAPI_additional_access_info_s *rel_access_info;
	struct OpenAPI_an_gw_address_s *an_gw_addr;
	OpenAPI_rat_type_e rat_type;
	struct OpenAPI_plmn_id_nid_s *plmn_id;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category;
	struct OpenAPI_service_area_coverage_info_s *applied_cov;
	char *supi;
	char *gpsi;
	char *time_stamp;
	struct OpenAPI_pdu_session_information_s *pdu_session_info;
	struct OpenAPI_service_identification_s *rep_services;
	struct OpenAPI_failure_s *deliv_failure;
} OpenAPI_pc_event_notification_t;

OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_create(
	OpenAPI_pc_event_t *event, OpenAPI_access_type_e acc_type,
	OpenAPI_additional_access_info_t *add_access_info,
	OpenAPI_additional_access_info_t *rel_access_info,
	OpenAPI_an_gw_address_t *an_gw_addr, OpenAPI_rat_type_e rat_type,
	OpenAPI_plmn_id_nid_t *plmn_id,
	OpenAPI_satellite_backhaul_category_e sat_backhaul_category,
	OpenAPI_service_area_coverage_info_t *applied_cov, char *supi,
	char *gpsi, char *time_stamp,
	OpenAPI_pdu_session_information_t *pdu_session_info,
	OpenAPI_service_identification_t *rep_services,
	OpenAPI_failure_t *deliv_failure);
void OpenAPI_pc_event_notification_free(
	OpenAPI_pc_event_notification_t *pc_event_notification);
OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_parseFromJSON(
	cJSON *pc_event_notificationJSON);
cJSON *OpenAPI_pc_event_notification_convertToJSON(
	OpenAPI_pc_event_notification_t *pc_event_notification);
OpenAPI_pc_event_notification_t *OpenAPI_pc_event_notification_copy(
	OpenAPI_pc_event_notification_t *dst,
	OpenAPI_pc_event_notification_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pc_event_notification_H_ */
