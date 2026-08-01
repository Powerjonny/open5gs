/*
 * ue_policy_transfer_failure_cause.h
 *
 * UE Policy Transfer Failure Cause.
 */

#ifndef _OpenAPI_ue_policy_transfer_failure_cause_H_
#define _OpenAPI_ue_policy_transfer_failure_cause_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "n1_n2_mess_transfer_error_reply.h"
#include "n1_n2_message_transfer_cause.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ue_policy_transfer_failure_cause_s
        OpenAPI_ue_policy_transfer_failure_cause_t;
typedef struct OpenAPI_ue_policy_transfer_failure_cause_s {}
OpenAPI_ue_policy_transfer_failure_cause_t;

OpenAPI_ue_policy_transfer_failure_cause_t *
OpenAPI_ue_policy_transfer_failure_cause_create();
void OpenAPI_ue_policy_transfer_failure_cause_free(
	OpenAPI_ue_policy_transfer_failure_cause_t *
	ue_policy_transfer_failure_cause);
OpenAPI_ue_policy_transfer_failure_cause_t *
OpenAPI_ue_policy_transfer_failure_cause_parseFromJSON(
	cJSON *ue_policy_transfer_failure_causeJSON);
cJSON *OpenAPI_ue_policy_transfer_failure_cause_convertToJSON(
	OpenAPI_ue_policy_transfer_failure_cause_t *
	ue_policy_transfer_failure_cause);
OpenAPI_ue_policy_transfer_failure_cause_t *
OpenAPI_ue_policy_transfer_failure_cause_copy(
	OpenAPI_ue_policy_transfer_failure_cause_t	*dst,
	OpenAPI_ue_policy_transfer_failure_cause_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ue_policy_transfer_failure_cause_H_ */
