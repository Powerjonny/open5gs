/*
 * up_loc_rep_addr_af.h
 *
 * Represents the user plane addressing information.
 */

#ifndef _OpenAPI_up_loc_rep_addr_af_H_
#define _OpenAPI_up_loc_rep_addr_af_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_up_loc_rep_addr_af_s OpenAPI_up_loc_rep_addr_af_t;
typedef struct OpenAPI_up_loc_rep_addr_af_s {
	OpenAPI_list_t *ipv4_addrs;
	OpenAPI_list_t *ipv6_addrs;
	char *fqdn;
} OpenAPI_up_loc_rep_addr_af_t;

OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_create(
	OpenAPI_list_t *ipv4_addrs, OpenAPI_list_t *ipv6_addrs, char *fqdn);
void OpenAPI_up_loc_rep_addr_af_free(
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af);
OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_parseFromJSON(
	cJSON *up_loc_rep_addr_afJSON);
cJSON *OpenAPI_up_loc_rep_addr_af_convertToJSON(
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af);
OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_copy(
	OpenAPI_up_loc_rep_addr_af_t *dst, OpenAPI_up_loc_rep_addr_af_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_up_loc_rep_addr_af_H_ */
