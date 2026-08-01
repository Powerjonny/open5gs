#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_association_request_ue.h"

OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_create(char *notification_uri,
                                             OpenAPI_list_t *
                                             alt_notif_ipv4_addrs,
                                             OpenAPI_list_t *
                                             alt_notif_ipv6_addrs,
                                             OpenAPI_list_t *alt_notif_fqdns,
                                             char *supi, char *gpsi,
                                             OpenAPI_access_type_e access_type,
                                             OpenAPI_list_t *access_types,
                                             char *pei,
                                             OpenAPI_user_location_t *user_loc,
                                             char *time_zone,
                                             OpenAPI_plmn_id_nid_t *serving_plmn,
                                             OpenAPI_rat_type_e rat_type,
                                             OpenAPI_list_t *rat_types,
                                             OpenAPI_list_t *group_ids,
                                             char *h_pcf_id, char *h_pcf_uri,
                                             char *h_pcf_set_id,
                                             char *ue_pol_req,
                                             OpenAPI_guami_t *guami,
                                             char *service_name,
                                             char *serving_nf_id,
                                             OpenAPI_pc5_capability_e pc5_capab,
                                             OpenAPI_list_t *a2x_capab,
                                             OpenAPI_list_t *pro_se_capab,
                                             OpenAPI_list_t *conf_snssais,
                                             OpenAPI_non3gpp_access_e
                                             n3g_node_re_sel,
                                             OpenAPI_slice_specific_n3g_node_selection_capability_e
                                             slice_n3g_node_sel_cap,
                                             OpenAPI_satellite_backhaul_category_e
                                             sat_backhaul_category,
                                             bool is__5gs_to_eps_mob,
                                             int _5gs_to_eps_mob,
                                             OpenAPI_list_t *vps_ue_pol_guidance,
                                             OpenAPI_list_t *lbo_roam_info,
                                             char *supp_feat,
                                             OpenAPI_list_t *rang_sl_capab) {
	OpenAPI_policy_association_request_ue_t *
	        policy_association_request_ue_local_var =
		ogs_malloc(sizeof(OpenAPI_policy_association_request_ue_t));
	ogs_assert(policy_association_request_ue_local_var);

	policy_association_request_ue_local_var->notification_uri =
		notification_uri;
	policy_association_request_ue_local_var->alt_notif_ipv4_addrs =
		alt_notif_ipv4_addrs;
	policy_association_request_ue_local_var->alt_notif_ipv6_addrs =
		alt_notif_ipv6_addrs;
	policy_association_request_ue_local_var->alt_notif_fqdns =
		alt_notif_fqdns;
	policy_association_request_ue_local_var->supi = supi;
	policy_association_request_ue_local_var->gpsi = gpsi;
	policy_association_request_ue_local_var->access_type = access_type;
	policy_association_request_ue_local_var->access_types = access_types;
	policy_association_request_ue_local_var->pei = pei;
	policy_association_request_ue_local_var->user_loc = user_loc;
	policy_association_request_ue_local_var->time_zone = time_zone;
	policy_association_request_ue_local_var->serving_plmn = serving_plmn;
	policy_association_request_ue_local_var->rat_type = rat_type;
	policy_association_request_ue_local_var->rat_types = rat_types;
	policy_association_request_ue_local_var->group_ids = group_ids;
	policy_association_request_ue_local_var->h_pcf_id = h_pcf_id;
	policy_association_request_ue_local_var->h_pcf_uri = h_pcf_uri;
	policy_association_request_ue_local_var->h_pcf_set_id = h_pcf_set_id;
	policy_association_request_ue_local_var->ue_pol_req = ue_pol_req;
	policy_association_request_ue_local_var->guami = guami;
	policy_association_request_ue_local_var->service_name = service_name;
	policy_association_request_ue_local_var->serving_nf_id = serving_nf_id;
	policy_association_request_ue_local_var->pc5_capab = pc5_capab;
	policy_association_request_ue_local_var->a2x_capab = a2x_capab;
	policy_association_request_ue_local_var->pro_se_capab = pro_se_capab;
	policy_association_request_ue_local_var->conf_snssais = conf_snssais;
	policy_association_request_ue_local_var->n3g_node_re_sel =
		n3g_node_re_sel;
	policy_association_request_ue_local_var->slice_n3g_node_sel_cap =
		slice_n3g_node_sel_cap;
	policy_association_request_ue_local_var->sat_backhaul_category =
		sat_backhaul_category;
	policy_association_request_ue_local_var->is__5gs_to_eps_mob =
		is__5gs_to_eps_mob;
	policy_association_request_ue_local_var->_5gs_to_eps_mob =
		_5gs_to_eps_mob;
	policy_association_request_ue_local_var->vps_ue_pol_guidance =
		vps_ue_pol_guidance;
	policy_association_request_ue_local_var->lbo_roam_info = lbo_roam_info;
	policy_association_request_ue_local_var->supp_feat = supp_feat;
	policy_association_request_ue_local_var->rang_sl_capab = rang_sl_capab;

	return policy_association_request_ue_local_var;
}

void OpenAPI_policy_association_request_ue_free(
	OpenAPI_policy_association_request_ue_t *policy_association_request_ue)
{
	OpenAPI_lnode_t *node = NULL;

	if(NULL == policy_association_request_ue) {
		return;
	}
	if(policy_association_request_ue->notification_uri) {
		ogs_free(policy_association_request_ue->notification_uri);
		policy_association_request_ue->notification_uri = NULL;
	}
	if(policy_association_request_ue->alt_notif_ipv4_addrs) {
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_ipv4_addrs,
			node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_request_ue->alt_notif_ipv4_addrs);
		policy_association_request_ue->alt_notif_ipv4_addrs = NULL;
	}
	if(policy_association_request_ue->alt_notif_ipv6_addrs) {
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_ipv6_addrs,
			node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_request_ue->alt_notif_ipv6_addrs);
		policy_association_request_ue->alt_notif_ipv6_addrs = NULL;
	}
	if(policy_association_request_ue->alt_notif_fqdns) {
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_fqdns, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_request_ue->alt_notif_fqdns);
		policy_association_request_ue->alt_notif_fqdns = NULL;
	}
	if(policy_association_request_ue->supi) {
		ogs_free(policy_association_request_ue->supi);
		policy_association_request_ue->supi = NULL;
	}
	if(policy_association_request_ue->gpsi) {
		ogs_free(policy_association_request_ue->gpsi);
		policy_association_request_ue->gpsi = NULL;
	}
	if(policy_association_request_ue->access_types) {
		OpenAPI_list_free(policy_association_request_ue->access_types);
		policy_association_request_ue->access_types = NULL;
	}
	if(policy_association_request_ue->pei) {
		ogs_free(policy_association_request_ue->pei);
		policy_association_request_ue->pei = NULL;
	}
	if(policy_association_request_ue->user_loc) {
		OpenAPI_user_location_free(
			policy_association_request_ue->user_loc);
		policy_association_request_ue->user_loc = NULL;
	}
	if(policy_association_request_ue->time_zone) {
		ogs_free(policy_association_request_ue->time_zone);
		policy_association_request_ue->time_zone = NULL;
	}
	if(policy_association_request_ue->serving_plmn) {
		OpenAPI_plmn_id_nid_free(
			policy_association_request_ue->serving_plmn);
		policy_association_request_ue->serving_plmn = NULL;
	}
	if(policy_association_request_ue->rat_types) {
		OpenAPI_list_free(policy_association_request_ue->rat_types);
		policy_association_request_ue->rat_types = NULL;
	}
	if(policy_association_request_ue->group_ids) {
		OpenAPI_list_for_each(policy_association_request_ue->group_ids,
		                      node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(policy_association_request_ue->group_ids);
		policy_association_request_ue->group_ids = NULL;
	}
	if(policy_association_request_ue->h_pcf_id) {
		ogs_free(policy_association_request_ue->h_pcf_id);
		policy_association_request_ue->h_pcf_id = NULL;
	}
	if(policy_association_request_ue->h_pcf_uri) {
		ogs_free(policy_association_request_ue->h_pcf_uri);
		policy_association_request_ue->h_pcf_uri = NULL;
	}
	if(policy_association_request_ue->h_pcf_set_id) {
		ogs_free(policy_association_request_ue->h_pcf_set_id);
		policy_association_request_ue->h_pcf_set_id = NULL;
	}
	if(policy_association_request_ue->ue_pol_req) {
		ogs_free(policy_association_request_ue->ue_pol_req);
		policy_association_request_ue->ue_pol_req = NULL;
	}
	if(policy_association_request_ue->guami) {
		OpenAPI_guami_free(policy_association_request_ue->guami);
		policy_association_request_ue->guami = NULL;
	}
	if(policy_association_request_ue->service_name) {
		ogs_free(policy_association_request_ue->service_name);
		policy_association_request_ue->service_name = NULL;
	}
	if(policy_association_request_ue->serving_nf_id) {
		ogs_free(policy_association_request_ue->serving_nf_id);
		policy_association_request_ue->serving_nf_id = NULL;
	}
	if(policy_association_request_ue->a2x_capab) {
		OpenAPI_list_free(policy_association_request_ue->a2x_capab);
		policy_association_request_ue->a2x_capab = NULL;
	}
	if(policy_association_request_ue->pro_se_capab) {
		OpenAPI_list_free(policy_association_request_ue->pro_se_capab);
		policy_association_request_ue->pro_se_capab = NULL;
	}
	if(policy_association_request_ue->conf_snssais) {
		OpenAPI_list_for_each(
			policy_association_request_ue->conf_snssais, node) {
			OpenAPI_configured_snssai_free(node->data);
		}
		OpenAPI_list_free(policy_association_request_ue->conf_snssais);
		policy_association_request_ue->conf_snssais = NULL;
	}
	if(policy_association_request_ue->vps_ue_pol_guidance) {
		OpenAPI_list_for_each(
			policy_association_request_ue->vps_ue_pol_guidance,
			node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ue_policy_parameters_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(
			policy_association_request_ue->vps_ue_pol_guidance);
		policy_association_request_ue->vps_ue_pol_guidance = NULL;
	}
	if(policy_association_request_ue->lbo_roam_info) {
		OpenAPI_list_for_each(
			policy_association_request_ue->lbo_roam_info, node) {
			OpenAPI_lbo_roaming_information_free(node->data);
		}
		OpenAPI_list_free(policy_association_request_ue->lbo_roam_info);
		policy_association_request_ue->lbo_roam_info = NULL;
	}
	if(policy_association_request_ue->supp_feat) {
		ogs_free(policy_association_request_ue->supp_feat);
		policy_association_request_ue->supp_feat = NULL;
	}
	if(policy_association_request_ue->rang_sl_capab) {
		OpenAPI_list_free(policy_association_request_ue->rang_sl_capab);
		policy_association_request_ue->rang_sl_capab = NULL;
	}
	ogs_free(policy_association_request_ue);
}

cJSON *OpenAPI_policy_association_request_ue_convertToJSON(
	OpenAPI_policy_association_request_ue_t *policy_association_request_ue)
{
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(policy_association_request_ue == NULL) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [PolicyAssociationRequestUE]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(!policy_association_request_ue->notification_uri) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [notification_uri]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "notificationUri",
	                           policy_association_request_ue->
	                           notification_uri) == NULL)
	{
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [notification_uri]");
		goto end;
	}

	if(policy_association_request_ue->alt_notif_ipv4_addrs) {
		cJSON *alt_notif_ipv4_addrsList = cJSON_AddArrayToObject(item,
		                                                         "altNotifIpv4Addrs");
		if(alt_notif_ipv4_addrsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_ipv4_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_ipv4_addrs,
			node) {
			if(cJSON_AddStringToObject(alt_notif_ipv4_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_ipv4_addrs]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->alt_notif_ipv6_addrs) {
		cJSON *alt_notif_ipv6_addrsList = cJSON_AddArrayToObject(item,
		                                                         "altNotifIpv6Addrs");
		if(alt_notif_ipv6_addrsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_ipv6_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_ipv6_addrs,
			node) {
			if(cJSON_AddStringToObject(alt_notif_ipv6_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_ipv6_addrs]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->alt_notif_fqdns) {
		cJSON *alt_notif_fqdnsList = cJSON_AddArrayToObject(item,
		                                                    "altNotifFqdns");
		if(alt_notif_fqdnsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_fqdns]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->alt_notif_fqdns, node) {
			if(cJSON_AddStringToObject(alt_notif_fqdnsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [alt_notif_fqdns]");
				goto end;
			}
		}
	}

	if(!policy_association_request_ue->supi) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [supi]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "supi",
	                           policy_association_request_ue->supi) == NULL)
	{
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [supi]");
		goto end;
	}

	if(policy_association_request_ue->gpsi) {
		if(cJSON_AddStringToObject(item, "gpsi",
		                           policy_association_request_ue->gpsi)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [gpsi]");
			goto end;
		}
	}

	if(policy_association_request_ue->access_type !=
	   OpenAPI_access_type_NULL)
	{
		if(cJSON_AddStringToObject(item, "accessType",
		                           OpenAPI_access_type_ToString(
						   policy_association_request_ue
						   ->access_type)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [access_type]");
			goto end;
		}
	}

	if(policy_association_request_ue->access_types !=
	   OpenAPI_access_type_NULL)
	{
		cJSON *access_typesList = cJSON_AddArrayToObject(item,
		                                                 "accessTypes");
		if(access_typesList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [access_types]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->access_types, node) {
			if(cJSON_AddStringToObject(access_typesList, "",
			                           OpenAPI_access_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [access_types]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->pei) {
		if(cJSON_AddStringToObject(item, "pei",
		                           policy_association_request_ue->pei)
		   == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [pei]");
			goto end;
		}
	}

	if(policy_association_request_ue->user_loc) {
		cJSON *user_loc_local_JSON =
			OpenAPI_user_location_convertToJSON(
				policy_association_request_ue->user_loc);
		if(user_loc_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [user_loc]");
			goto end;
		}
		cJSON_AddItemToObject(item, "userLoc", user_loc_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [user_loc]");
			goto end;
		}
	}

	if(policy_association_request_ue->time_zone) {
		if(cJSON_AddStringToObject(item, "timeZone",
		                           policy_association_request_ue->
		                           time_zone) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [time_zone]");
			goto end;
		}
	}

	if(policy_association_request_ue->serving_plmn) {
		cJSON *serving_plmn_local_JSON =
			OpenAPI_plmn_id_nid_convertToJSON(
				policy_association_request_ue->serving_plmn);
		if(serving_plmn_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [serving_plmn]");
			goto end;
		}
		cJSON_AddItemToObject(item, "servingPlmn",
		                      serving_plmn_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [serving_plmn]");
			goto end;
		}
	}

	if(policy_association_request_ue->rat_type != OpenAPI_rat_type_NULL) {
		if(cJSON_AddStringToObject(item, "ratType",
		                           OpenAPI_rat_type_ToString(
						   policy_association_request_ue
						   ->rat_type)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [rat_type]");
			goto end;
		}
	}

	if(policy_association_request_ue->rat_types != OpenAPI_rat_type_NULL) {
		cJSON *rat_typesList = cJSON_AddArrayToObject(item, "ratTypes");
		if(rat_typesList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [rat_types]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_request_ue->rat_types,
		                      node) {
			if(cJSON_AddStringToObject(rat_typesList, "",
			                           OpenAPI_rat_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [rat_types]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->group_ids) {
		cJSON *group_idsList = cJSON_AddArrayToObject(item, "groupIds");
		if(group_idsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [group_ids]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_request_ue->group_ids,
		                      node) {
			if(cJSON_AddStringToObject(group_idsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [group_ids]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->h_pcf_id) {
		if(cJSON_AddStringToObject(item, "hPcfId",
		                           policy_association_request_ue->
		                           h_pcf_id) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [h_pcf_id]");
			goto end;
		}
	}

	if(policy_association_request_ue->h_pcf_uri) {
		if(cJSON_AddStringToObject(item, "hPcfUri",
		                           policy_association_request_ue->
		                           h_pcf_uri) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [h_pcf_uri]");
			goto end;
		}
	}

	if(policy_association_request_ue->h_pcf_set_id) {
		if(cJSON_AddStringToObject(item, "hPcfSetId",
		                           policy_association_request_ue->
		                           h_pcf_set_id) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [h_pcf_set_id]");
			goto end;
		}
	}

	if(policy_association_request_ue->ue_pol_req) {
		if(cJSON_AddStringToObject(item, "uePolReq",
		                           policy_association_request_ue->
		                           ue_pol_req) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [ue_pol_req]");
			goto end;
		}
	}

	if(policy_association_request_ue->guami) {
		cJSON *guami_local_JSON =
			OpenAPI_guami_convertToJSON(
				policy_association_request_ue->guami);
		if(guami_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [guami]");
			goto end;
		}
		cJSON_AddItemToObject(item, "guami", guami_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [guami]");
			goto end;
		}
	}

	if(policy_association_request_ue->service_name) {
		if(cJSON_AddStringToObject(item, "serviceName",
		                           policy_association_request_ue->
		                           service_name) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [service_name]");
			goto end;
		}
	}

	if(policy_association_request_ue->serving_nf_id) {
		if(cJSON_AddStringToObject(item, "servingNfId",
		                           policy_association_request_ue->
		                           serving_nf_id) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [serving_nf_id]");
			goto end;
		}
	}

	if(policy_association_request_ue->pc5_capab !=
	   OpenAPI_pc5_capability_NULL)
	{
		if(cJSON_AddStringToObject(item, "pc5Capab",
		                           OpenAPI_pc5_capability_ToString(
						   policy_association_request_ue
						   ->pc5_capab)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [pc5_capab]");
			goto end;
		}
	}

	if(policy_association_request_ue->a2x_capab !=
	   OpenAPI_a2x_capability_NULL)
	{
		cJSON *a2x_capabList = cJSON_AddArrayToObject(item, "a2xCapab");
		if(a2x_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [a2x_capab]");
			goto end;
		}
		OpenAPI_list_for_each(policy_association_request_ue->a2x_capab,
		                      node) {
			if(cJSON_AddStringToObject(a2x_capabList, "",
			                           OpenAPI_a2x_capability_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [a2x_capab]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->pro_se_capab !=
	   OpenAPI_pro_se_capability_ue_NULL)
	{
		cJSON *pro_se_capabList = cJSON_AddArrayToObject(item,
		                                                 "proSeCapab");
		if(pro_se_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [pro_se_capab]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->pro_se_capab, node) {
			if(cJSON_AddStringToObject(pro_se_capabList, "",
			                           OpenAPI_pro_se_capability_ue_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [pro_se_capab]");
				goto end;
			}
		}
	}

	if(policy_association_request_ue->conf_snssais) {
		cJSON *conf_snssaisList = cJSON_AddArrayToObject(item,
		                                                 "confSnssais");
		if(conf_snssaisList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [conf_snssais]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->conf_snssais, node) {
			cJSON *itemLocal =
				OpenAPI_configured_snssai_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [conf_snssais]");
				goto end;
			}
			cJSON_AddItemToArray(conf_snssaisList, itemLocal);
		}
	}

	if(policy_association_request_ue->n3g_node_re_sel !=
	   OpenAPI_non3gpp_access_NULL)
	{
		if(cJSON_AddStringToObject(item, "n3gNodeReSel",
		                           OpenAPI_non3gpp_access_ToString(
						   policy_association_request_ue
						   ->n3g_node_re_sel)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [n3g_node_re_sel]");
			goto end;
		}
	}

	if(policy_association_request_ue->slice_n3g_node_sel_cap !=
	   OpenAPI_slice_specific_n3g_node_selection_capability_NULL)
	{
		if(cJSON_AddStringToObject(item, "sliceN3gNodeSelCap",
		                           OpenAPI_slice_specific_n3g_node_selection_capability_ToString
					   (
						   policy_association_request_ue
						   ->slice_n3g_node_sel_cap)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [slice_n3g_node_sel_cap]");
			goto end;
		}
	}

	if(policy_association_request_ue->sat_backhaul_category !=
	   OpenAPI_satellite_backhaul_category_NULL)
	{
		if(cJSON_AddStringToObject(item, "satBackhaulCategory",
		                           OpenAPI_satellite_backhaul_category_ToString
					   (
						   policy_association_request_ue
						   ->sat_backhaul_category)) ==
		   NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [sat_backhaul_category]");
			goto end;
		}
	}

	if(policy_association_request_ue->is__5gs_to_eps_mob) {
		if(cJSON_AddBoolToObject(item, "5gsToEpsMob",
		                         policy_association_request_ue->
		                         _5gs_to_eps_mob) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [_5gs_to_eps_mob]");
			goto end;
		}
	}

	if(policy_association_request_ue->vps_ue_pol_guidance) {
		cJSON *vps_ue_pol_guidance = cJSON_AddObjectToObject(item,
		                                                     "vpsUePolGuidance");
		if(vps_ue_pol_guidance == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
			goto end;
		}
		cJSON *localMapObject = vps_ue_pol_guidance;
		if(policy_association_request_ue->vps_ue_pol_guidance) {
			OpenAPI_list_for_each(
				policy_association_request_ue->
				vps_ue_pol_guidance, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_association_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_association_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_ue_policy_parameters_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_association_request_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(policy_association_request_ue->lbo_roam_info) {
		cJSON *lbo_roam_infoList = cJSON_AddArrayToObject(item,
		                                                  "lboRoamInfo");
		if(lbo_roam_infoList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [lbo_roam_info]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->lbo_roam_info, node) {
			cJSON *itemLocal =
				OpenAPI_lbo_roaming_information_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [lbo_roam_info]");
				goto end;
			}
			cJSON_AddItemToArray(lbo_roam_infoList, itemLocal);
		}
	}

	if(!policy_association_request_ue->supp_feat) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [supp_feat]");
		return NULL;
	}
	if(cJSON_AddStringToObject(item, "suppFeat",
	                           policy_association_request_ue->supp_feat) ==
	   NULL)
	{
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed [supp_feat]");
		goto end;
	}

	if(policy_association_request_ue->rang_sl_capab !=
	   OpenAPI_rang_sl_capability_NULL)
	{
		cJSON *rang_sl_capabList = cJSON_AddArrayToObject(item,
		                                                  "rangSlCapab");
		if(rang_sl_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_convertToJSON() failed [rang_sl_capab]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_request_ue->rang_sl_capab, node) {
			if(cJSON_AddStringToObject(rang_sl_capabList, "",
			                           OpenAPI_rang_sl_capability_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_request_ue_convertToJSON() failed [rang_sl_capab]");
				goto end;
			}
		}
	}

end:
	return item;
}

OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_parseFromJSON(
	cJSON *policy_association_request_ueJSON) {
	OpenAPI_policy_association_request_ue_t *
	        policy_association_request_ue_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *notification_uri = NULL;
	cJSON *alt_notif_ipv4_addrs = NULL;
	OpenAPI_list_t *alt_notif_ipv4_addrsList = NULL;
	cJSON *alt_notif_ipv6_addrs = NULL;
	OpenAPI_list_t *alt_notif_ipv6_addrsList = NULL;
	cJSON *alt_notif_fqdns = NULL;
	OpenAPI_list_t *alt_notif_fqdnsList = NULL;
	cJSON *supi = NULL;
	cJSON *gpsi = NULL;
	cJSON *access_type = NULL;
	OpenAPI_access_type_e access_typeVariable = 0;
	cJSON *access_types = NULL;
	OpenAPI_list_t *access_typesList = NULL;
	cJSON *pei = NULL;
	cJSON *user_loc = NULL;
	OpenAPI_user_location_t *user_loc_local_nonprim = NULL;
	cJSON *time_zone = NULL;
	cJSON *serving_plmn = NULL;
	OpenAPI_plmn_id_nid_t *serving_plmn_local_nonprim = NULL;
	cJSON *rat_type = NULL;
	OpenAPI_rat_type_e rat_typeVariable = 0;
	cJSON *rat_types = NULL;
	OpenAPI_list_t *rat_typesList = NULL;
	cJSON *group_ids = NULL;
	OpenAPI_list_t *group_idsList = NULL;
	cJSON *h_pcf_id = NULL;
	cJSON *h_pcf_uri = NULL;
	cJSON *h_pcf_set_id = NULL;
	cJSON *ue_pol_req = NULL;
	cJSON *guami = NULL;
	OpenAPI_guami_t *guami_local_nonprim = NULL;
	cJSON *service_name = NULL;
	cJSON *serving_nf_id = NULL;
	cJSON *pc5_capab = NULL;
	OpenAPI_pc5_capability_e pc5_capabVariable = 0;
	cJSON *a2x_capab = NULL;
	OpenAPI_list_t *a2x_capabList = NULL;
	cJSON *pro_se_capab = NULL;
	OpenAPI_list_t *pro_se_capabList = NULL;
	cJSON *conf_snssais = NULL;
	OpenAPI_list_t *conf_snssaisList = NULL;
	cJSON *n3g_node_re_sel = NULL;
	OpenAPI_non3gpp_access_e n3g_node_re_selVariable = 0;
	cJSON *slice_n3g_node_sel_cap = NULL;
	OpenAPI_slice_specific_n3g_node_selection_capability_e
	        slice_n3g_node_sel_capVariable = 0;
	cJSON *sat_backhaul_category = NULL;
	OpenAPI_satellite_backhaul_category_e sat_backhaul_categoryVariable = 0;
	cJSON *_5gs_to_eps_mob = NULL;
	cJSON *vps_ue_pol_guidance = NULL;
	OpenAPI_list_t *vps_ue_pol_guidanceList = NULL;
	cJSON *lbo_roam_info = NULL;
	OpenAPI_list_t *lbo_roam_infoList = NULL;
	cJSON *supp_feat = NULL;
	cJSON *rang_sl_capab = NULL;
	OpenAPI_list_t *rang_sl_capabList = NULL;
	notification_uri =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "notificationUri");
	if(!notification_uri) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [notification_uri]");
		goto end;
	}
	if(!cJSON_IsString(notification_uri)) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [notification_uri]");
		goto end;
	}

	alt_notif_ipv4_addrs =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "altNotifIpv4Addrs");
	if(alt_notif_ipv4_addrs) {
		cJSON *alt_notif_ipv4_addrs_local = NULL;
		if(!cJSON_IsArray(alt_notif_ipv4_addrs)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_ipv4_addrs]");
			goto end;
		}

		alt_notif_ipv4_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_ipv4_addrs_local,
		                   alt_notif_ipv4_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_ipv4_addrs_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_ipv4_addrs]");
				goto end;
			}
			OpenAPI_list_add(alt_notif_ipv4_addrsList,
			                 ogs_strdup(
						 alt_notif_ipv4_addrs_local->
						 valuestring));
		}
	}

	alt_notif_ipv6_addrs =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "altNotifIpv6Addrs");
	if(alt_notif_ipv6_addrs) {
		cJSON *alt_notif_ipv6_addrs_local = NULL;
		if(!cJSON_IsArray(alt_notif_ipv6_addrs)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_ipv6_addrs]");
			goto end;
		}

		alt_notif_ipv6_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_ipv6_addrs_local,
		                   alt_notif_ipv6_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_ipv6_addrs_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_ipv6_addrs]");
				goto end;
			}
			OpenAPI_list_add(alt_notif_ipv6_addrsList,
			                 ogs_strdup(
						 alt_notif_ipv6_addrs_local->
						 valuestring));
		}
	}

	alt_notif_fqdns =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "altNotifFqdns");
	if(alt_notif_fqdns) {
		cJSON *alt_notif_fqdns_local = NULL;
		if(!cJSON_IsArray(alt_notif_fqdns)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_fqdns]");
			goto end;
		}

		alt_notif_fqdnsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_fqdns_local, alt_notif_fqdns) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_fqdns_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [alt_notif_fqdns]");
				goto end;
			}
			OpenAPI_list_add(alt_notif_fqdnsList,
			                 ogs_strdup(
						 alt_notif_fqdns_local->
						 valuestring));
		}
	}

	supi =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "supi");
	if(!supi) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [supi]");
		goto end;
	}
	if(!cJSON_IsString(supi)) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [supi]");
		goto end;
	}

	gpsi =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "gpsi");
	if(gpsi) {
		if(!cJSON_IsString(gpsi) &&
		   !cJSON_IsNull(gpsi))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [gpsi]");
			goto end;
		}
	}

	access_type =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "accessType");
	if(access_type) {
		if(!cJSON_IsString(access_type)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [access_type]");
			goto end;
		}
		access_typeVariable =
			OpenAPI_access_type_FromString(
				access_type->valuestring);
	}

	access_types =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "accessTypes");
	if(access_types) {
		cJSON *access_types_local = NULL;
		if(!cJSON_IsArray(access_types)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [access_types]");
			goto end;
		}

		access_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(access_types_local, access_types) {
			OpenAPI_access_type_e localEnum =
				OpenAPI_access_type_NULL;
			if(!cJSON_IsString(access_types_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [access_types]");
				goto end;
			}
			localEnum =
				OpenAPI_access_type_FromString(
					access_types_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"access_types\" is not supported. Ignoring it ...",
					access_types_local->valuestring);
			} else {
				OpenAPI_list_add(access_typesList,
				                 (void *) localEnum);
			}
		}
		if(access_typesList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed: Expected access_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	pei =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "pei");
	if(pei) {
		if(!cJSON_IsString(pei) &&
		   !cJSON_IsNull(pei))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [pei]");
			goto end;
		}
	}

	user_loc =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "userLoc");
	if(user_loc) {
		user_loc_local_nonprim =
			OpenAPI_user_location_parseFromJSON(user_loc);
		if(!user_loc_local_nonprim) {
			ogs_error(
				"OpenAPI_user_location_parseFromJSON failed [user_loc]");
			goto end;
		}
	}

	time_zone =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "timeZone");
	if(time_zone) {
		if(!cJSON_IsString(time_zone) &&
		   !cJSON_IsNull(time_zone))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [time_zone]");
			goto end;
		}
	}

	serving_plmn =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "servingPlmn");
	if(serving_plmn) {
		serving_plmn_local_nonprim =
			OpenAPI_plmn_id_nid_parseFromJSON(serving_plmn);
		if(!serving_plmn_local_nonprim) {
			ogs_error(
				"OpenAPI_plmn_id_nid_parseFromJSON failed [serving_plmn]");
			goto end;
		}
	}

	rat_type =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "ratType");
	if(rat_type) {
		if(!cJSON_IsString(rat_type)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [rat_type]");
			goto end;
		}
		rat_typeVariable =
			OpenAPI_rat_type_FromString(rat_type->valuestring);
	}

	rat_types =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "ratTypes");
	if(rat_types) {
		cJSON *rat_types_local = NULL;
		if(!cJSON_IsArray(rat_types)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [rat_types]");
			goto end;
		}

		rat_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(rat_types_local, rat_types) {
			OpenAPI_rat_type_e localEnum = OpenAPI_rat_type_NULL;
			if(!cJSON_IsString(rat_types_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [rat_types]");
				goto end;
			}
			localEnum =
				OpenAPI_rat_type_FromString(
					rat_types_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"rat_types\" is not supported. Ignoring it ...",
					rat_types_local->valuestring);
			} else {
				OpenAPI_list_add(rat_typesList,
				                 (void *) localEnum);
			}
		}
		if(rat_typesList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed: Expected rat_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	group_ids =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "groupIds");
	if(group_ids) {
		cJSON *group_ids_local = NULL;
		if(!cJSON_IsArray(group_ids)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [group_ids]");
			goto end;
		}

		group_idsList = OpenAPI_list_create();

		cJSON_ArrayForEach(group_ids_local, group_ids) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(group_ids_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [group_ids]");
				goto end;
			}
			OpenAPI_list_add(group_idsList,
			                 ogs_strdup(
						 group_ids_local->valuestring));
		}
	}

	h_pcf_id =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "hPcfId");
	if(h_pcf_id) {
		if(!cJSON_IsString(h_pcf_id) &&
		   !cJSON_IsNull(h_pcf_id))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [h_pcf_id]");
			goto end;
		}
	}

	h_pcf_uri =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "hPcfUri");
	if(h_pcf_uri) {
		if(!cJSON_IsString(h_pcf_uri) &&
		   !cJSON_IsNull(h_pcf_uri))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [h_pcf_uri]");
			goto end;
		}
	}

	h_pcf_set_id =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "hPcfSetId");
	if(h_pcf_set_id) {
		if(!cJSON_IsString(h_pcf_set_id) &&
		   !cJSON_IsNull(h_pcf_set_id))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [h_pcf_set_id]");
			goto end;
		}
	}

	ue_pol_req =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "uePolReq");
	if(ue_pol_req) {
		if(!cJSON_IsString(ue_pol_req) &&
		   !cJSON_IsNull(ue_pol_req))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [ue_pol_req]");
			goto end;
		}
	}

	guami =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "guami");
	if(guami) {
		guami_local_nonprim = OpenAPI_guami_parseFromJSON(guami);
		if(!guami_local_nonprim) {
			ogs_error("OpenAPI_guami_parseFromJSON failed [guami]");
			goto end;
		}
	}

	service_name =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "serviceName");
	if(service_name) {
		if(!cJSON_IsString(service_name) &&
		   !cJSON_IsNull(service_name))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [service_name]");
			goto end;
		}
	}

	serving_nf_id =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "servingNfId");
	if(serving_nf_id) {
		if(!cJSON_IsString(serving_nf_id) &&
		   !cJSON_IsNull(serving_nf_id))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [serving_nf_id]");
			goto end;
		}
	}

	pc5_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "pc5Capab");
	if(pc5_capab) {
		if(!cJSON_IsString(pc5_capab)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [pc5_capab]");
			goto end;
		}
		pc5_capabVariable =
			OpenAPI_pc5_capability_FromString(
				pc5_capab->valuestring);
	}

	a2x_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "a2xCapab");
	if(a2x_capab) {
		cJSON *a2x_capab_local = NULL;
		if(!cJSON_IsArray(a2x_capab)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [a2x_capab]");
			goto end;
		}

		a2x_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(a2x_capab_local, a2x_capab) {
			OpenAPI_a2x_capability_e localEnum =
				OpenAPI_a2x_capability_NULL;
			if(!cJSON_IsString(a2x_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [a2x_capab]");
				goto end;
			}
			localEnum =
				OpenAPI_a2x_capability_FromString(
					a2x_capab_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"a2x_capab\" is not supported. Ignoring it ...",
					a2x_capab_local->valuestring);
			} else {
				OpenAPI_list_add(a2x_capabList,
				                 (void *) localEnum);
			}
		}
		if(a2x_capabList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed: Expected a2x_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	pro_se_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "proSeCapab");
	if(pro_se_capab) {
		cJSON *pro_se_capab_local = NULL;
		if(!cJSON_IsArray(pro_se_capab)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [pro_se_capab]");
			goto end;
		}

		pro_se_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(pro_se_capab_local, pro_se_capab) {
			OpenAPI_pro_se_capability_ue_e localEnum =
				OpenAPI_pro_se_capability_ue_NULL;
			if(!cJSON_IsString(pro_se_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [pro_se_capab]");
				goto end;
			}
			localEnum =
				OpenAPI_pro_se_capability_ue_FromString(
					pro_se_capab_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"pro_se_capab\" is not supported. Ignoring it ...",
					pro_se_capab_local->valuestring);
			} else {
				OpenAPI_list_add(pro_se_capabList,
				                 (void *) localEnum);
			}
		}
		if(pro_se_capabList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed: Expected pro_se_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	conf_snssais =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "confSnssais");
	if(conf_snssais) {
		cJSON *conf_snssais_local = NULL;
		if(!cJSON_IsArray(conf_snssais)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [conf_snssais]");
			goto end;
		}

		conf_snssaisList = OpenAPI_list_create();

		cJSON_ArrayForEach(conf_snssais_local, conf_snssais) {
			if(!cJSON_IsObject(conf_snssais_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [conf_snssais]");
				goto end;
			}
			OpenAPI_configured_snssai_t *conf_snssaisItem =
				OpenAPI_configured_snssai_parseFromJSON(
					conf_snssais_local);
			if(!conf_snssaisItem) {
				ogs_error("No conf_snssaisItem");
				goto end;
			}
			OpenAPI_list_add(conf_snssaisList, conf_snssaisItem);
		}
	}

	n3g_node_re_sel =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "n3gNodeReSel");
	if(n3g_node_re_sel) {
		if(!cJSON_IsString(n3g_node_re_sel)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [n3g_node_re_sel]");
			goto end;
		}
		n3g_node_re_selVariable =
			OpenAPI_non3gpp_access_FromString(
				n3g_node_re_sel->valuestring);
	}

	slice_n3g_node_sel_cap =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON,
			"sliceN3gNodeSelCap");
	if(slice_n3g_node_sel_cap) {
		if(!cJSON_IsString(slice_n3g_node_sel_cap)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [slice_n3g_node_sel_cap]");
			goto end;
		}
		slice_n3g_node_sel_capVariable =
			OpenAPI_slice_specific_n3g_node_selection_capability_FromString
			        (slice_n3g_node_sel_cap->valuestring);
	}

	sat_backhaul_category =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON,
			"satBackhaulCategory");
	if(sat_backhaul_category) {
		if(!cJSON_IsString(sat_backhaul_category)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [sat_backhaul_category]");
			goto end;
		}
		sat_backhaul_categoryVariable =
			OpenAPI_satellite_backhaul_category_FromString(
				sat_backhaul_category->valuestring);
	}

	_5gs_to_eps_mob =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "5gsToEpsMob");
	if(_5gs_to_eps_mob) {
		if(!cJSON_IsBool(_5gs_to_eps_mob)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [_5gs_to_eps_mob]");
			goto end;
		}
	}

	vps_ue_pol_guidance =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "vpsUePolGuidance");
	if(vps_ue_pol_guidance) {
		cJSON *vps_ue_pol_guidance_local_map = NULL;
		if(!cJSON_IsObject(vps_ue_pol_guidance) &&
		   !cJSON_IsNull(vps_ue_pol_guidance))
		{
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [vps_ue_pol_guidance]");
			goto end;
		}
		if(cJSON_IsObject(vps_ue_pol_guidance)) {
			vps_ue_pol_guidanceList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(vps_ue_pol_guidance_local_map,
			                   vps_ue_pol_guidance) {
				cJSON *localMapObject =
					vps_ue_pol_guidance_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_ue_policy_parameters_parseFromJSON
						        (localMapObject));
				} else if(cJSON_IsNull(localMapObject)) {
					localMapKeyPair =
						OpenAPI_map_create(ogs_strdup(
									   localMapObject
									   ->
									   string),
						                   NULL);
				} else {
					ogs_error(
						"OpenAPI_policy_association_request_ue_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(vps_ue_pol_guidanceList,
				                 localMapKeyPair);
			}
		}
	}

	lbo_roam_info =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "lboRoamInfo");
	if(lbo_roam_info) {
		cJSON *lbo_roam_info_local = NULL;
		if(!cJSON_IsArray(lbo_roam_info)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [lbo_roam_info]");
			goto end;
		}

		lbo_roam_infoList = OpenAPI_list_create();

		cJSON_ArrayForEach(lbo_roam_info_local, lbo_roam_info) {
			if(!cJSON_IsObject(lbo_roam_info_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [lbo_roam_info]");
				goto end;
			}
			OpenAPI_lbo_roaming_information_t *lbo_roam_infoItem =
				OpenAPI_lbo_roaming_information_parseFromJSON(
					lbo_roam_info_local);
			if(!lbo_roam_infoItem) {
				ogs_error("No lbo_roam_infoItem");
				goto end;
			}
			OpenAPI_list_add(lbo_roam_infoList, lbo_roam_infoItem);
		}
	}

	supp_feat =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "suppFeat");
	if(!supp_feat) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [supp_feat]");
		goto end;
	}
	if(!cJSON_IsString(supp_feat)) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_parseFromJSON() failed [supp_feat]");
		goto end;
	}

	rang_sl_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_request_ueJSON, "rangSlCapab");
	if(rang_sl_capab) {
		cJSON *rang_sl_capab_local = NULL;
		if(!cJSON_IsArray(rang_sl_capab)) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed [rang_sl_capab]");
			goto end;
		}

		rang_sl_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(rang_sl_capab_local, rang_sl_capab) {
			OpenAPI_rang_sl_capability_e localEnum =
				OpenAPI_rang_sl_capability_NULL;
			if(!cJSON_IsString(rang_sl_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_request_ue_parseFromJSON() failed [rang_sl_capab]");
				goto end;
			}
			localEnum =
				OpenAPI_rang_sl_capability_FromString(
					rang_sl_capab_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"rang_sl_capab\" is not supported. Ignoring it ...",
					rang_sl_capab_local->valuestring);
			} else {
				OpenAPI_list_add(rang_sl_capabList,
				                 (void *) localEnum);
			}
		}
		if(rang_sl_capabList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_request_ue_parseFromJSON() failed: Expected rang_sl_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	policy_association_request_ue_local_var =
		OpenAPI_policy_association_request_ue_create(
			ogs_strdup(notification_uri->valuestring),
			alt_notif_ipv4_addrs ? alt_notif_ipv4_addrsList : NULL,
			alt_notif_ipv6_addrs ? alt_notif_ipv6_addrsList : NULL,
			alt_notif_fqdns ? alt_notif_fqdnsList : NULL,
			ogs_strdup(supi->valuestring),
			gpsi &&
			!cJSON_IsNull(gpsi) ? ogs_strdup(gpsi->valuestring) :
			NULL,
			access_type ? access_typeVariable : 0,
			access_types ? access_typesList : NULL,
			pei &&
			!cJSON_IsNull(pei) ? ogs_strdup(pei->valuestring) :
			NULL,
			user_loc ? user_loc_local_nonprim : NULL,
			time_zone &&
			!cJSON_IsNull(time_zone) ?
			ogs_strdup(time_zone->valuestring) :
			NULL,
			serving_plmn ? serving_plmn_local_nonprim : NULL,
			rat_type ? rat_typeVariable : 0,
			rat_types ? rat_typesList : NULL,
			group_ids ? group_idsList : NULL,
			h_pcf_id &&
			!cJSON_IsNull(h_pcf_id) ?
			ogs_strdup(h_pcf_id->valuestring) :
			NULL,
			h_pcf_uri &&
			!cJSON_IsNull(h_pcf_uri) ?
			ogs_strdup(h_pcf_uri->valuestring) :
			NULL,
			h_pcf_set_id &&
			!cJSON_IsNull(h_pcf_set_id) ?
			ogs_strdup(h_pcf_set_id->valuestring) : NULL,
			ue_pol_req &&
			!cJSON_IsNull(ue_pol_req) ?
			ogs_strdup(ue_pol_req->valuestring) : NULL,
			guami ? guami_local_nonprim : NULL,
			service_name &&
			!cJSON_IsNull(service_name) ?
			ogs_strdup(service_name->valuestring) : NULL,
			serving_nf_id &&
			!cJSON_IsNull(serving_nf_id) ?
			ogs_strdup(serving_nf_id->valuestring) : NULL,
			pc5_capab ? pc5_capabVariable : 0,
			a2x_capab ? a2x_capabList : NULL,
			pro_se_capab ? pro_se_capabList : NULL,
			conf_snssais ? conf_snssaisList : NULL,
			n3g_node_re_sel ? n3g_node_re_selVariable : 0,
			slice_n3g_node_sel_cap ?
			slice_n3g_node_sel_capVariable : 0,
			sat_backhaul_category ? sat_backhaul_categoryVariable :
			0,
			_5gs_to_eps_mob ? true : false,
			_5gs_to_eps_mob ? _5gs_to_eps_mob->valueint : 0,
			vps_ue_pol_guidance ? vps_ue_pol_guidanceList : NULL,
			lbo_roam_info ? lbo_roam_infoList : NULL,
			ogs_strdup(supp_feat->valuestring),
			rang_sl_capab ? rang_sl_capabList : NULL
			);

	return policy_association_request_ue_local_var;
end:
	if(alt_notif_ipv4_addrsList) {
		OpenAPI_list_for_each(alt_notif_ipv4_addrsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(alt_notif_ipv4_addrsList);
		alt_notif_ipv4_addrsList = NULL;
	}
	if(alt_notif_ipv6_addrsList) {
		OpenAPI_list_for_each(alt_notif_ipv6_addrsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(alt_notif_ipv6_addrsList);
		alt_notif_ipv6_addrsList = NULL;
	}
	if(alt_notif_fqdnsList) {
		OpenAPI_list_for_each(alt_notif_fqdnsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(alt_notif_fqdnsList);
		alt_notif_fqdnsList = NULL;
	}
	if(access_typesList) {
		OpenAPI_list_free(access_typesList);
		access_typesList = NULL;
	}
	if(user_loc_local_nonprim) {
		OpenAPI_user_location_free(user_loc_local_nonprim);
		user_loc_local_nonprim = NULL;
	}
	if(serving_plmn_local_nonprim) {
		OpenAPI_plmn_id_nid_free(serving_plmn_local_nonprim);
		serving_plmn_local_nonprim = NULL;
	}
	if(rat_typesList) {
		OpenAPI_list_free(rat_typesList);
		rat_typesList = NULL;
	}
	if(group_idsList) {
		OpenAPI_list_for_each(group_idsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(group_idsList);
		group_idsList = NULL;
	}
	if(guami_local_nonprim) {
		OpenAPI_guami_free(guami_local_nonprim);
		guami_local_nonprim = NULL;
	}
	if(a2x_capabList) {
		OpenAPI_list_free(a2x_capabList);
		a2x_capabList = NULL;
	}
	if(pro_se_capabList) {
		OpenAPI_list_free(pro_se_capabList);
		pro_se_capabList = NULL;
	}
	if(conf_snssaisList) {
		OpenAPI_list_for_each(conf_snssaisList, node) {
			OpenAPI_configured_snssai_free(node->data);
		}
		OpenAPI_list_free(conf_snssaisList);
		conf_snssaisList = NULL;
	}
	if(vps_ue_pol_guidanceList) {
		OpenAPI_list_for_each(vps_ue_pol_guidanceList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ue_policy_parameters_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(vps_ue_pol_guidanceList);
		vps_ue_pol_guidanceList = NULL;
	}
	if(lbo_roam_infoList) {
		OpenAPI_list_for_each(lbo_roam_infoList, node) {
			OpenAPI_lbo_roaming_information_free(node->data);
		}
		OpenAPI_list_free(lbo_roam_infoList);
		lbo_roam_infoList = NULL;
	}
	if(rang_sl_capabList) {
		OpenAPI_list_free(rang_sl_capabList);
		rang_sl_capabList = NULL;
	}
	return NULL;
}

OpenAPI_policy_association_request_ue_t *
OpenAPI_policy_association_request_ue_copy(
	OpenAPI_policy_association_request_ue_t *dst,
	OpenAPI_policy_association_request_ue_t *src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_policy_association_request_ue_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_policy_association_request_ue_convertToJSON() failed");
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

	OpenAPI_policy_association_request_ue_free(dst);
	dst = OpenAPI_policy_association_request_ue_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
