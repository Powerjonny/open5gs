/*
 * non3gpp_access.h
 *
 *
 */

#ifndef _OpenAPI_non3gpp_access_H_
#define _OpenAPI_non3gpp_access_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_non3gpp_access_NULL = 0, OpenAPI_non3gpp_access_N3IWF,
	       OpenAPI_non3gpp_access_TNGF } OpenAPI_non3gpp_access_e;

char * OpenAPI_non3gpp_access_ToString(OpenAPI_non3gpp_access_e non3gpp_access);

OpenAPI_non3gpp_access_e OpenAPI_non3gpp_access_FromString(
	char *non3gpp_access);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_non3gpp_access_H_ */
