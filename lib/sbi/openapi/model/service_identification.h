/*
 * service_identification.h
 *
 * Identifies the service to which the subscription applies.
 */

#ifndef _OpenAPI_service_identification_H_
#define _OpenAPI_service_identification_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ethernet_flow_info.h"
#include "ip_flow_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_service_identification_s OpenAPI_service_identification_t;
typedef struct OpenAPI_service_identification_s {
	OpenAPI_list_t *serv_eth_flows;
	OpenAPI_list_t *serv_ip_flows;
	char *af_app_id;
} OpenAPI_service_identification_t;

OpenAPI_service_identification_t *OpenAPI_service_identification_create(
	OpenAPI_list_t *serv_eth_flows, OpenAPI_list_t *serv_ip_flows,
	char *af_app_id);
void OpenAPI_service_identification_free(
	OpenAPI_service_identification_t *service_identification);
OpenAPI_service_identification_t *OpenAPI_service_identification_parseFromJSON(
	cJSON *service_identificationJSON);
cJSON *OpenAPI_service_identification_convertToJSON(
	OpenAPI_service_identification_t *service_identification);
OpenAPI_service_identification_t *OpenAPI_service_identification_copy(
	OpenAPI_service_identification_t	*dst,
	OpenAPI_service_identification_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_service_identification_H_ */
