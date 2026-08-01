/*
 * ursp_enforcement_pdu_session.h
 *
 * Represents URSP rule enforcement information for a PDU session.
 */

#ifndef _OpenAPI_ursp_enforcement_pdu_session_H_
#define _OpenAPI_ursp_enforcement_pdu_session_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "pdu_session_type.h"
#include "snssai.h"
#include "ssc_mode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ursp_enforcement_pdu_session_s
        OpenAPI_ursp_enforcement_pdu_session_t;
typedef struct OpenAPI_ursp_enforcement_pdu_session_s {
	char *ursp_enf_info;
	OpenAPI_ssc_mode_e ssc_mode;
	char *ue_req_dnn;
	OpenAPI_pdu_session_type_e ue_req_pdu_session_type;
	char *dnn;
	struct OpenAPI_snssai_s *snssai;
} OpenAPI_ursp_enforcement_pdu_session_t;

OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_create(char *ursp_enf_info,
                                            OpenAPI_ssc_mode_e ssc_mode,
                                            char *ue_req_dnn,
                                            OpenAPI_pdu_session_type_e
                                            ue_req_pdu_session_type, char *dnn,
                                            OpenAPI_snssai_t *snssai);
void OpenAPI_ursp_enforcement_pdu_session_free(
	OpenAPI_ursp_enforcement_pdu_session_t *ursp_enforcement_pdu_session);
OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_parseFromJSON(
	cJSON *ursp_enforcement_pdu_sessionJSON);
cJSON *OpenAPI_ursp_enforcement_pdu_session_convertToJSON(
	OpenAPI_ursp_enforcement_pdu_session_t *ursp_enforcement_pdu_session);
OpenAPI_ursp_enforcement_pdu_session_t *
OpenAPI_ursp_enforcement_pdu_session_copy(
	OpenAPI_ursp_enforcement_pdu_session_t	*dst,
	OpenAPI_ursp_enforcement_pdu_session_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ursp_enforcement_pdu_session_H_ */
