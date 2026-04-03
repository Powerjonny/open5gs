/*
 * reporting_ind_any_of.h
 *
 *
 */

#ifndef _OpenAPI_reporting_ind_any_of_H_
#define _OpenAPI_reporting_ind_any_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_reporting_ind_any_of_NULL = 0,
	       OpenAPI_reporting_ind_any_of_INSIDE_REPORTING,
	       OpenAPI_reporting_ind_any_of_OUTSIDE_REPORTING }
OpenAPI_reporting_ind_any_of_e;

char * OpenAPI_reporting_ind_any_of_ToString(
	OpenAPI_reporting_ind_any_of_e reporting_ind_any_of);

OpenAPI_reporting_ind_any_of_e OpenAPI_reporting_ind_any_of_FromString(
	char *reporting_ind_any_of);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_reporting_ind_any_of_H_ */
