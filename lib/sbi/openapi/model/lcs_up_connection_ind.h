/*
 * lcs_up_connection_ind.h
 *
 *
 */

#ifndef _OpenAPI_lcs_up_connection_ind_H_
#define _OpenAPI_lcs_up_connection_ind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_lcs_up_connection_ind_NULL = 0,
	       OpenAPI_lcs_up_connection_ind_TERMINATION,
	       OpenAPI_lcs_up_connection_ind_SETUP }
OpenAPI_lcs_up_connection_ind_e;

char * OpenAPI_lcs_up_connection_ind_ToString(
	OpenAPI_lcs_up_connection_ind_e lcs_up_connection_ind);

OpenAPI_lcs_up_connection_ind_e OpenAPI_lcs_up_connection_ind_FromString(
	char *lcs_up_connection_ind);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_lcs_up_connection_ind_H_ */
