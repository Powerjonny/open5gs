/*
 * ethernet_flow_info.h
 *
 * Identifies an UL/DL ethernet flow.
 */

#ifndef _OpenAPI_ethernet_flow_info_H_
#define _OpenAPI_ethernet_flow_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "eth_flow_description.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ethernet_flow_info_s OpenAPI_ethernet_flow_info_t;
typedef struct OpenAPI_ethernet_flow_info_s {
	OpenAPI_list_t *eth_flows;
	int flow_number;
} OpenAPI_ethernet_flow_info_t;

OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_create(
	OpenAPI_list_t *eth_flows, int flow_number);
void OpenAPI_ethernet_flow_info_free(
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info);
OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_parseFromJSON(
	cJSON *ethernet_flow_infoJSON);
cJSON *OpenAPI_ethernet_flow_info_convertToJSON(
	OpenAPI_ethernet_flow_info_t *ethernet_flow_info);
OpenAPI_ethernet_flow_info_t *OpenAPI_ethernet_flow_info_copy(
	OpenAPI_ethernet_flow_info_t *dst, OpenAPI_ethernet_flow_info_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ethernet_flow_info_H_ */
