#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pdu_session_information.h"

OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_create(
	OpenAPI_snssai_t *snssai, char *dnn, char *ue_ipv4, char *ue_ipv6,
	char *ip_domain, char *ue_mac) {
	OpenAPI_pdu_session_information_t *pdu_session_information_local_var =
		ogs_malloc(sizeof(OpenAPI_pdu_session_information_t));
	ogs_assert(pdu_session_information_local_var);

	pdu_session_information_local_var->snssai = snssai;
	pdu_session_information_local_var->dnn = dnn;
	pdu_session_information_local_var->ue_ipv4 = ue_ipv4;
	pdu_session_information_local_var->ue_ipv6 = ue_ipv6;
	pdu_session_information_local_var->ip_domain = ip_domain;
	pdu_session_information_local_var->ue_mac = ue_mac;

	return pdu_session_information_local_var;
}

void OpenAPI_pdu_session_information_free(
	OpenAPI_pdu_session_information_t *pdu_session_information) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == pdu_session_information) {
		return;
	}
	if(pdu_session_information->snssai) {
		OpenAPI_snssai_free(pdu_session_information->snssai);
		pdu_session_information->snssai = NULL;
	}
	if(pdu_session_information->dnn) {
		ogs_free(pdu_session_information->dnn);
		pdu_session_information->dnn = NULL;
	}
	if(pdu_session_information->ue_ipv4) {
		ogs_free(pdu_session_information->ue_ipv4);
		pdu_session_information->ue_ipv4 = NULL;
	}
	if(pdu_session_information->ue_ipv6) {
		ogs_free(pdu_session_information->ue_ipv6);
		pdu_session_information->ue_ipv6 = NULL;
	}
	if(pdu_session_information->ip_domain) {
		ogs_free(pdu_session_information->ip_domain);
		pdu_session_information->ip_domain = NULL;
	}
	if(pdu_session_information->ue_mac) {
		ogs_free(pdu_session_information->ue_mac);
		pdu_session_information->ue_mac = NULL;
	}
	ogs_free(pdu_session_information);
}

cJSON *OpenAPI_pdu_session_information_convertToJSON(
	OpenAPI_pdu_session_information_t *pdu_session_information) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(pdu_session_information == NULL) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [PduSessionInformation]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!pdu_session_information->snssai) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [snssai]");
		return NULL;
	}
	cJSON *snssai_local_JSON =
		OpenAPI_snssai_convertToJSON(pdu_session_information->snssai);
	if(snssai_local_JSON == NULL) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [snssai]");
		goto end;
	}
	cJSON_AddItemToObject(item, "snssai", snssai_local_JSON);
	if(item->child == NULL) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [snssai]");
		goto end;
	}

	if(!pdu_session_information->dnn) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [dnn]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "dnn",
	                           pdu_session_information->dnn) == NULL)
	{
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed [dnn]");
		goto end;
	}

	if(pdu_session_information->ue_ipv4) {
		if(cJSON_AddStringToObject(item, "ueIpv4",
		                           pdu_session_information->ue_ipv4) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_pdu_session_information_convertToJSON() failed [ue_ipv4]");
			goto end;
		}
	}

	if(pdu_session_information->ue_ipv6) {
		if(cJSON_AddStringToObject(item, "ueIpv6",
		                           pdu_session_information->ue_ipv6) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_pdu_session_information_convertToJSON() failed [ue_ipv6]");
			goto end;
		}
	}

	if(pdu_session_information->ip_domain) {
		if(cJSON_AddStringToObject(item, "ipDomain",
		                           pdu_session_information->ip_domain)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_pdu_session_information_convertToJSON() failed [ip_domain]");
			goto end;
		}
	}

	if(pdu_session_information->ue_mac) {
		if(cJSON_AddStringToObject(item, "ueMac",
		                           pdu_session_information->ue_mac) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_pdu_session_information_convertToJSON() failed [ue_mac]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_parseFromJSON
        (cJSON *pdu_session_informationJSON) {
	OpenAPI_pdu_session_information_t *pdu_session_information_local_var =
		NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *snssai = NULL;
	OpenAPI_snssai_t *snssai_local_nonprim = NULL;
	cJSON *dnn = NULL;
	cJSON *ue_ipv4 = NULL;
	cJSON *ue_ipv6 = NULL;
	cJSON *ip_domain = NULL;
	cJSON *ue_mac = NULL;
	snssai = cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
	                                          "snssai");
	if(!snssai) {
		ogs_error(
			"OpenAPI_pdu_session_information_parseFromJSON() failed [snssai]");
		goto end;
	}
	snssai_local_nonprim = OpenAPI_snssai_parseFromJSON(snssai);
	if(!snssai_local_nonprim) {
		ogs_error("OpenAPI_snssai_parseFromJSON failed [snssai]");
		goto end;
	}

	dnn = cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
	                                       "dnn");
	if(!dnn) {
		ogs_error(
			"OpenAPI_pdu_session_information_parseFromJSON() failed [dnn]");
		goto end;
	}
	if(!cJSON_IsString(dnn)) {
		ogs_error(
			"OpenAPI_pdu_session_information_parseFromJSON() failed [dnn]");
		goto end;
	}

	ue_ipv4 = cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
	                                           "ueIpv4");
	if(ue_ipv4) {
		if(!cJSON_IsString(ue_ipv4) &&
		   !cJSON_IsNull(ue_ipv4))
		{
			ogs_error(
				"OpenAPI_pdu_session_information_parseFromJSON() failed [ue_ipv4]");
			goto end;
		}
	}

	ue_ipv6 = cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
	                                           "ueIpv6");
	if(ue_ipv6) {
		if(!cJSON_IsString(ue_ipv6) &&
		   !cJSON_IsNull(ue_ipv6))
		{
			ogs_error(
				"OpenAPI_pdu_session_information_parseFromJSON() failed [ue_ipv6]");
			goto end;
		}
	}

	ip_domain =
		cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
		                                 "ipDomain");
	if(ip_domain) {
		if(!cJSON_IsString(ip_domain) &&
		   !cJSON_IsNull(ip_domain))
		{
			ogs_error(
				"OpenAPI_pdu_session_information_parseFromJSON() failed [ip_domain]");
			goto end;
		}
	}

	ue_mac = cJSON_GetObjectItemCaseSensitive(pdu_session_informationJSON,
	                                          "ueMac");
	if(ue_mac) {
		if(!cJSON_IsString(ue_mac) &&
		   !cJSON_IsNull(ue_mac))
		{
			ogs_error(
				"OpenAPI_pdu_session_information_parseFromJSON() failed [ue_mac]");
			goto end;
		}
	}

	pdu_session_information_local_var =
		OpenAPI_pdu_session_information_create(
			snssai_local_nonprim,
			ogs_strdup(dnn->valuestring),
			ue_ipv4 &&
			!cJSON_IsNull(ue_ipv4) ?
			ogs_strdup(ue_ipv4->valuestring) :
			NULL,
			ue_ipv6 &&
			!cJSON_IsNull(ue_ipv6) ?
			ogs_strdup(ue_ipv6->valuestring) :
			NULL,
			ip_domain &&
			!cJSON_IsNull(ip_domain) ?
			ogs_strdup(ip_domain->valuestring) :
			NULL,
			ue_mac &&
			!cJSON_IsNull(ue_mac) ?
			ogs_strdup(ue_mac->valuestring) : NULL
			);

	return pdu_session_information_local_var;
end:
	if(snssai_local_nonprim) {
		OpenAPI_snssai_free(snssai_local_nonprim);
		snssai_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_pdu_session_information_t *OpenAPI_pdu_session_information_copy(
	OpenAPI_pdu_session_information_t	*dst,
	OpenAPI_pdu_session_information_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_pdu_session_information_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_pdu_session_information_convertToJSON() failed");
		return NULL;
	}

	content = cJSON_Print(item);
	cJSON_Delete(item);

	if(!content) {
		ogs_error("cJSON_Print() failed");
		return NULL;
	}

	item = cJSON_Parse(content);
	ogs_free(content);
	if(!item) {
		ogs_error("cJSON_Parse() failed");
		return NULL;
	}

	OpenAPI_pdu_session_information_free(dst);
	dst = OpenAPI_pdu_session_information_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
