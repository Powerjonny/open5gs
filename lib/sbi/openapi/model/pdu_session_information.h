/*
 * pdu_session_information.h
 *
 * Represents PDU session identification information.
 */

#ifndef _OpenAPI_pdu_session_information_H_
#define _OpenAPI_pdu_session_information_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "snssai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_pdu_session_information_s
        OpenAPI_pdu_session_information_t;
typedef struct OpenAPI_pdu_session_information_s {
	struct OpenAPI_snssai_s *snssai;
	char *dnn;
	char *ue_ipv4;
	char *ue_ipv6;
	char *ip_domain;
	char *ue_mac;
} OpenAPI_pdu_session_information_t;

OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_create(
	OpenAPI_snssai_t *snssai, char *dnn, char *ue_ipv4, char *ue_ipv6,
	char *ip_domain, char *ue_mac);
void OpenAPI_pdu_session_information_free(
	OpenAPI_pdu_session_information_t *pdu_session_information);
OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_parseFromJSON
        (cJSON *pdu_session_informationJSON);
cJSON *OpenAPI_pdu_session_information_convertToJSON(
	OpenAPI_pdu_session_information_t *pdu_session_information);
OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_copy(
	OpenAPI_pdu_session_information_t	*dst,
	OpenAPI_pdu_session_information_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_pdu_session_information_H_ */
