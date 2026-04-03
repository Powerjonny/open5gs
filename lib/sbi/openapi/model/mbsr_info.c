#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mbsr_info.h"

OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_create(OpenAPI_ncgi_t	*ncgi,
                                              OpenAPI_ecgi_t	*ecgi) {
	OpenAPI_mbsr_info_t *mbsr_info_local_var =
		ogs_malloc(sizeof(OpenAPI_mbsr_info_t));
	ogs_assert(mbsr_info_local_var);

	mbsr_info_local_var->ncgi = ncgi;
	mbsr_info_local_var->ecgi = ecgi;

	return mbsr_info_local_var;
}

void OpenAPI_mbsr_info_free(OpenAPI_mbsr_info_t *mbsr_info) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == mbsr_info) {
		return;
	}
	if(mbsr_info->ncgi) {
		OpenAPI_ncgi_free(mbsr_info->ncgi);
		mbsr_info->ncgi = NULL;
	}
	if(mbsr_info->ecgi) {
		OpenAPI_ecgi_free(mbsr_info->ecgi);
		mbsr_info->ecgi = NULL;
	}
	ogs_free(mbsr_info);
}

cJSON *OpenAPI_mbsr_info_convertToJSON(OpenAPI_mbsr_info_t *mbsr_info) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(mbsr_info == NULL) {
		ogs_error(
			"OpenAPI_mbsr_info_convertToJSON() failed [MbsrInfo]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(mbsr_info->ncgi) {
		cJSON *ncgi_local_JSON =
			OpenAPI_ncgi_convertToJSON(mbsr_info->ncgi);
		if(ncgi_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_mbsr_info_convertToJSON() failed [ncgi]");
			goto end;
		}
		cJSON_AddItemToObject(item, "ncgi", ncgi_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_mbsr_info_convertToJSON() failed [ncgi]");
			goto end;
		}
	}

	if(mbsr_info->ecgi) {
		cJSON *ecgi_local_JSON =
			OpenAPI_ecgi_convertToJSON(mbsr_info->ecgi);
		if(ecgi_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_mbsr_info_convertToJSON() failed [ecgi]");
			goto end;
		}
		cJSON_AddItemToObject(item, "ecgi", ecgi_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_mbsr_info_convertToJSON() failed [ecgi]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_parseFromJSON(cJSON *mbsr_infoJSON) {
	OpenAPI_mbsr_info_t *mbsr_info_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *ncgi = NULL;
	OpenAPI_ncgi_t *ncgi_local_nonprim = NULL;
	cJSON *ecgi = NULL;
	OpenAPI_ecgi_t *ecgi_local_nonprim = NULL;
	ncgi = cJSON_GetObjectItemCaseSensitive(mbsr_infoJSON, "ncgi");
	if(ncgi) {
		ncgi_local_nonprim = OpenAPI_ncgi_parseFromJSON(ncgi);
		if(!ncgi_local_nonprim) {
			ogs_error("OpenAPI_ncgi_parseFromJSON failed [ncgi]");
			goto end;
		}
	}

	ecgi = cJSON_GetObjectItemCaseSensitive(mbsr_infoJSON, "ecgi");
	if(ecgi) {
		ecgi_local_nonprim = OpenAPI_ecgi_parseFromJSON(ecgi);
		if(!ecgi_local_nonprim) {
			ogs_error("OpenAPI_ecgi_parseFromJSON failed [ecgi]");
			goto end;
		}
	}

	mbsr_info_local_var = OpenAPI_mbsr_info_create(
		ncgi ? ncgi_local_nonprim : NULL,
		ecgi ? ecgi_local_nonprim : NULL
		);

	return mbsr_info_local_var;
end:
	if(ncgi_local_nonprim) {
		OpenAPI_ncgi_free(ncgi_local_nonprim);
		ncgi_local_nonprim = NULL;
	}
	if(ecgi_local_nonprim) {
		OpenAPI_ecgi_free(ecgi_local_nonprim);
		ecgi_local_nonprim = NULL;
	}
	return NULL;
}

OpenAPI_mbsr_info_t *OpenAPI_mbsr_info_copy(OpenAPI_mbsr_info_t *dst,
                                            OpenAPI_mbsr_info_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_mbsr_info_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_mbsr_info_convertToJSON() failed");
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

	OpenAPI_mbsr_info_free(dst);
	dst = OpenAPI_mbsr_info_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
