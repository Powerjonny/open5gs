#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "up_loc_rep_addr_af.h"

OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_create(
	OpenAPI_list_t *ipv4_addrs, OpenAPI_list_t *ipv6_addrs, char *fqdn) {
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af_local_var =
		ogs_malloc(sizeof(OpenAPI_up_loc_rep_addr_af_t));
	ogs_assert(up_loc_rep_addr_af_local_var);

	up_loc_rep_addr_af_local_var->ipv4_addrs = ipv4_addrs;
	up_loc_rep_addr_af_local_var->ipv6_addrs = ipv6_addrs;
	up_loc_rep_addr_af_local_var->fqdn = fqdn;

	return up_loc_rep_addr_af_local_var;
}

void OpenAPI_up_loc_rep_addr_af_free(
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == up_loc_rep_addr_af) {
		return;
	}
	if(up_loc_rep_addr_af->ipv4_addrs) {
		OpenAPI_list_for_each(up_loc_rep_addr_af->ipv4_addrs, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(up_loc_rep_addr_af->ipv4_addrs);
		up_loc_rep_addr_af->ipv4_addrs = NULL;
	}
	if(up_loc_rep_addr_af->ipv6_addrs) {
		OpenAPI_list_for_each(up_loc_rep_addr_af->ipv6_addrs, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(up_loc_rep_addr_af->ipv6_addrs);
		up_loc_rep_addr_af->ipv6_addrs = NULL;
	}
	if(up_loc_rep_addr_af->fqdn) {
		ogs_free(up_loc_rep_addr_af->fqdn);
		up_loc_rep_addr_af->fqdn = NULL;
	}
	ogs_free(up_loc_rep_addr_af);
}

cJSON *OpenAPI_up_loc_rep_addr_af_convertToJSON(
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(up_loc_rep_addr_af == NULL) {
		ogs_error(
			"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [UpLocRepAddrAf]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(up_loc_rep_addr_af->ipv4_addrs) {
		cJSON *ipv4_addrsList = cJSON_AddArrayToObject(item,
		                                               "ipv4Addrs");
		if(ipv4_addrsList == NULL) {
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [ipv4_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(up_loc_rep_addr_af->ipv4_addrs, node) {
			if(cJSON_AddStringToObject(ipv4_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [ipv4_addrs]");
				goto end;
			}
		}
	}

	if(up_loc_rep_addr_af->ipv6_addrs) {
		cJSON *ipv6_addrsList = cJSON_AddArrayToObject(item,
		                                               "ipv6Addrs");
		if(ipv6_addrsList == NULL) {
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [ipv6_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(up_loc_rep_addr_af->ipv6_addrs, node) {
			if(cJSON_AddStringToObject(ipv6_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [ipv6_addrs]");
				goto end;
			}
		}
	}

	if(up_loc_rep_addr_af->fqdn) {
		if(cJSON_AddStringToObject(item, "fqdn",
		                           up_loc_rep_addr_af->fqdn) == NULL)
		{
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_convertToJSON() failed [fqdn]");
			goto end;
		}
	}

end:
	return item;
}

OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_parseFromJSON(
	cJSON *up_loc_rep_addr_afJSON) {
	OpenAPI_up_loc_rep_addr_af_t *up_loc_rep_addr_af_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *ipv4_addrs = NULL;
	OpenAPI_list_t *ipv4_addrsList = NULL;
	cJSON *ipv6_addrs = NULL;
	OpenAPI_list_t *ipv6_addrsList = NULL;
	cJSON *fqdn = NULL;
	ipv4_addrs = cJSON_GetObjectItemCaseSensitive(up_loc_rep_addr_afJSON,
	                                              "ipv4Addrs");
	if(ipv4_addrs) {
		cJSON *ipv4_addrs_local = NULL;
		if(!cJSON_IsArray(ipv4_addrs)) {
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_parseFromJSON() failed [ipv4_addrs]");
			goto end;
		}

		ipv4_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(ipv4_addrs_local, ipv4_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(ipv4_addrs_local)) {
				ogs_error(
					"OpenAPI_up_loc_rep_addr_af_parseFromJSON() failed [ipv4_addrs]");
				goto end;
			}
			OpenAPI_list_add(ipv4_addrsList,
			                 ogs_strdup(
						 ipv4_addrs_local->valuestring));
		}
	}

	ipv6_addrs = cJSON_GetObjectItemCaseSensitive(up_loc_rep_addr_afJSON,
	                                              "ipv6Addrs");
	if(ipv6_addrs) {
		cJSON *ipv6_addrs_local = NULL;
		if(!cJSON_IsArray(ipv6_addrs)) {
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_parseFromJSON() failed [ipv6_addrs]");
			goto end;
		}

		ipv6_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(ipv6_addrs_local, ipv6_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(ipv6_addrs_local)) {
				ogs_error(
					"OpenAPI_up_loc_rep_addr_af_parseFromJSON() failed [ipv6_addrs]");
				goto end;
			}
			OpenAPI_list_add(ipv6_addrsList,
			                 ogs_strdup(
						 ipv6_addrs_local->valuestring));
		}
	}

	fqdn = cJSON_GetObjectItemCaseSensitive(up_loc_rep_addr_afJSON, "fqdn");
	if(fqdn) {
		if(!cJSON_IsString(fqdn) &&
		   !cJSON_IsNull(fqdn))
		{
			ogs_error(
				"OpenAPI_up_loc_rep_addr_af_parseFromJSON() failed [fqdn]");
			goto end;
		}
	}

	up_loc_rep_addr_af_local_var = OpenAPI_up_loc_rep_addr_af_create(
		ipv4_addrs ? ipv4_addrsList : NULL,
		ipv6_addrs ? ipv6_addrsList : NULL,
		fqdn &&
		!cJSON_IsNull(fqdn) ? ogs_strdup(fqdn->valuestring) : NULL
		);

	return up_loc_rep_addr_af_local_var;
end:
	if(ipv4_addrsList) {
		OpenAPI_list_for_each(ipv4_addrsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(ipv4_addrsList);
		ipv4_addrsList = NULL;
	}
	if(ipv6_addrsList) {
		OpenAPI_list_for_each(ipv6_addrsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(ipv6_addrsList);
		ipv6_addrsList = NULL;
	}
	return NULL;
}

OpenAPI_up_loc_rep_addr_af_t *OpenAPI_up_loc_rep_addr_af_copy(
	OpenAPI_up_loc_rep_addr_af_t *dst, OpenAPI_up_loc_rep_addr_af_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_up_loc_rep_addr_af_convertToJSON(src);
	if(!item) {
		ogs_error("OpenAPI_up_loc_rep_addr_af_convertToJSON() failed");
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

	OpenAPI_up_loc_rep_addr_af_free(dst);
	dst = OpenAPI_up_loc_rep_addr_af_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
