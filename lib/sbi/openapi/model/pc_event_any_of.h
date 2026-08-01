/*
 * pc_event_any_of.h
 *
 *
 */

#ifndef _OpenAPI_pc_event_any_of_H_
#define _OpenAPI_pc_event_any_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_pc_event_any_of_NULL = 0,
	       OpenAPI_pc_event_any_of_AC_TY_CH,
	       OpenAPI_pc_event_any_of_PLMN_CH, OpenAPI_pc_event_any_of_SAC_CH,
	       OpenAPI_pc_event_any_of_SAT_CATEGORY_CH,
	       OpenAPI_pc_event_any_of_SUCCESS_UE_POL_DEL_SP,
	       OpenAPI_pc_event_any_of_UNSUCCESS_UE_POL_DEL_SP }
OpenAPI_pc_event_any_of_e;

char * OpenAPI_pc_event_any_of_ToString(
	OpenAPI_pc_event_any_of_e pc_event_any_of);

OpenAPI_pc_event_any_of_e OpenAPI_pc_event_any_of_FromString(
	char *pc_event_any_of);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pc_event_any_of_H_ */
