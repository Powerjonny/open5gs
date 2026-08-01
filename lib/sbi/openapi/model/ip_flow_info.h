/*
 * ip_flow_info.h
 *
 * Identifies an UL/DL IP flow.
 */

#ifndef _OpenAPI_ip_flow_info_H_
#define _OpenAPI_ip_flow_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ip_flow_info_s OpenAPI_ip_flow_info_t;
typedef struct OpenAPI_ip_flow_info_s {
	OpenAPI_list_t *ip_flows;
	int flow_number;
} OpenAPI_ip_flow_info_t;

OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_create(
	OpenAPI_list_t *ip_flows,
	int
	flow_number);
void OpenAPI_ip_flow_info_free(OpenAPI_ip_flow_info_t *ip_flow_info);
OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_parseFromJSON(
	cJSON *ip_flow_infoJSON);
cJSON *OpenAPI_ip_flow_info_convertToJSON(OpenAPI_ip_flow_info_t *ip_flow_info);
OpenAPI_ip_flow_info_t *OpenAPI_ip_flow_info_copy(
	OpenAPI_ip_flow_info_t	*dst,
	OpenAPI_ip_flow_info_t
	                        *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ip_flow_info_H_ */
