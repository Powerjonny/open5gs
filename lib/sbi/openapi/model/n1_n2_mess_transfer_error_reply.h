/*
 * n1_n2_mess_transfer_error_reply.h
 *
 *
 */

#ifndef _OpenAPI_n1_n2_mess_transfer_error_reply_H_
#define _OpenAPI_n1_n2_mess_transfer_error_reply_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_n1_n2_mess_transfer_error_reply_NULL = 0,
	       OpenAPI_n1_n2_mess_transfer_error_reply_UE_NOT_REACHABLE,
	       OpenAPI_n1_n2_mess_transfer_error_reply_UNSPECIFIED }
OpenAPI_n1_n2_mess_transfer_error_reply_e;

char * OpenAPI_n1_n2_mess_transfer_error_reply_ToString(
	OpenAPI_n1_n2_mess_transfer_error_reply_e
	n1_n2_mess_transfer_error_reply);

OpenAPI_n1_n2_mess_transfer_error_reply_e
OpenAPI_n1_n2_mess_transfer_error_reply_FromString(
	char *n1_n2_mess_transfer_error_reply);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_n1_n2_mess_transfer_error_reply_H_ */
