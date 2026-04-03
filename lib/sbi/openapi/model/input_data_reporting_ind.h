/*
 * input_data_reporting_ind.h
 *
 *
 */

#ifndef _OpenAPI_input_data_reporting_ind_H_
#define _OpenAPI_input_data_reporting_ind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_input_data_reporting_ind_s
        OpenAPI_input_data_reporting_ind_t;
typedef struct OpenAPI_input_data_reporting_ind_s {}
OpenAPI_input_data_reporting_ind_t;

OpenAPI_input_data_reporting_ind_t *OpenAPI_input_data_reporting_ind_create(void);
void OpenAPI_input_data_reporting_ind_free(
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind);
OpenAPI_input_data_reporting_ind_t *
OpenAPI_input_data_reporting_ind_parseFromJSON(
	cJSON *input_data_reporting_indJSON);
cJSON *OpenAPI_input_data_reporting_ind_convertToJSON(
	OpenAPI_input_data_reporting_ind_t *input_data_reporting_ind);
OpenAPI_input_data_reporting_ind_t *OpenAPI_input_data_reporting_ind_copy(
	OpenAPI_input_data_reporting_ind_t	*dst,
	OpenAPI_input_data_reporting_ind_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_input_data_reporting_ind_H_ */
