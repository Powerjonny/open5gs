/*
 * policy_association_release_cause_ue.h
 *
 *
 */

#ifndef _OpenAPI_policy_association_release_cause_ue_H_
#define _OpenAPI_policy_association_release_cause_ue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_policy_association_release_cause_ue_NULL = 0,
	       OpenAPI_policy_association_release_cause_ue_UNSPECIFIED,
	       OpenAPI_policy_association_release_cause_ue_UE_SUBSCRIPTION,
	       OpenAPI_policy_association_release_cause_ue_INSUFFICIENT_RES }
OpenAPI_policy_association_release_cause_ue_e;

char * OpenAPI_policy_association_release_cause_ue_ToString(
	OpenAPI_policy_association_release_cause_ue_e
	policy_association_release_cause_ue);

OpenAPI_policy_association_release_cause_ue_e
OpenAPI_policy_association_release_cause_ue_FromString(
	char *policy_association_release_cause_ue);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_policy_association_release_cause_ue_H_ */
