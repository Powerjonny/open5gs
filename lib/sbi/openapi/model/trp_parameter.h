/*
 * trp_parameter.h
 *
 * The identifiers of TRPs if the network assisted positioning is used
 */

#ifndef _OpenAPI_trp_parameter_H_
#define _OpenAPI_trp_parameter_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "global_ran_node_id.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_trp_parameter_s OpenAPI_trp_parameter_t;
typedef struct OpenAPI_trp_parameter_s {
	OpenAPI_list_t *trp_ids;
	struct OpenAPI_global_ran_node_id_s *global_gnb_id;
} OpenAPI_trp_parameter_t;

OpenAPI_trp_parameter_t *OpenAPI_trp_parameter_create(
	OpenAPI_list_t	*trp_ids,
	OpenAPI_global_ran_node_id_t
	                *global_gnb_id);
void OpenAPI_trp_parameter_free(OpenAPI_trp_parameter_t *trp_parameter);
OpenAPI_trp_parameter_t *OpenAPI_trp_parameter_parseFromJSON(
	cJSON *trp_parameterJSON);
cJSON *OpenAPI_trp_parameter_convertToJSON(
	OpenAPI_trp_parameter_t *trp_parameter);
OpenAPI_trp_parameter_t *OpenAPI_trp_parameter_copy(
	OpenAPI_trp_parameter_t *dst, OpenAPI_trp_parameter_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_trp_parameter_H_ */
