/*
 * integrity_computing_entity_any_of.h
 *
 *
 */

#ifndef _OpenAPI_integrity_computing_entity_any_of_H_
#define _OpenAPI_integrity_computing_entity_any_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_integrity_computing_entity_any_of_NULL = 0,
	       OpenAPI_integrity_computing_entity_any_of_UE,
	       OpenAPI_integrity_computing_entity_any_of_LMF,
	       OpenAPI_integrity_computing_entity_any_of_BOTH }
OpenAPI_integrity_computing_entity_any_of_e;

char * OpenAPI_integrity_computing_entity_any_of_ToString(
	OpenAPI_integrity_computing_entity_any_of_e
	integrity_computing_entity_any_of);

OpenAPI_integrity_computing_entity_any_of_e
OpenAPI_integrity_computing_entity_any_of_FromString(
	char *integrity_computing_entity_any_of);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_integrity_computing_entity_any_of_H_ */
