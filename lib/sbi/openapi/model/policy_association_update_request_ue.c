#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "policy_association_update_request_ue.h"

OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_create(char *notification_uri,
                                                    OpenAPI_list_t *
                                                    alt_notif_ipv4_addrs,
                                                    OpenAPI_list_t *
                                                    alt_notif_ipv6_addrs,
                                                    OpenAPI_list_t *
                                                    alt_notif_fqdns,
                                                    OpenAPI_list_t	*
                                                        triggers,
                                                    OpenAPI_list_t	*
                                                        pra_statuses,
                                                    OpenAPI_user_location_t *
                                                    user_loc,
                                                    char		*
                                                                        ue_pol_del_result,
                                                    OpenAPI_ue_policy_transfer_failure_notification_t
                                                    *
                                                                        ue_pol_trans_fail_notif,
                                                    char		*
                                                                        ue_pol_req,
                                                    OpenAPI_guami_t	*guami,
                                                    char		*
                                                    serving_nf_id,
                                                    OpenAPI_plmn_id_nid_t *
                                                    plmn_id,
                                                    OpenAPI_cm_state_t *
                                                    connect_state,
                                                    OpenAPI_list_t *group_ids,
                                                    OpenAPI_pc5_capability_e
                                                    pc5_capab,
                                                    OpenAPI_list_t
                                                        *a2x_capab,
                                                    OpenAPI_list_t
                                                        *pro_se_capab,
                                                    OpenAPI_list_t
                                                        *conf_snssais,
                                                    OpenAPI_non3gpp_access_e
                                                    n3g_node_re_sel,
                                                    OpenAPI_slice_specific_n3g_node_selection_capability_e
                                                    slice_n3g_node_sel_cap,
                                                    OpenAPI_satellite_backhaul_category_e
                                                    sat_backhaul_category,
                                                    OpenAPI_list_t *ursp_enf_rep,
                                                    bool
                                                    is_vps_ue_pol_guidance_null,
                                                    OpenAPI_list_t *
                                                    vps_ue_pol_guidance,
                                                    OpenAPI_list_t *
                                                    lbo_roam_info,
                                                    OpenAPI_list_t	*
                                                        access_types,
                                                    OpenAPI_list_t	*
                                                        rat_types,
                                                    char		*
                                                        supp_feat,
                                                    OpenAPI_list_t	*
                                                        rang_sl_capab) {
	OpenAPI_policy_association_update_request_ue_t *
	        policy_association_update_request_ue_local_var =
		ogs_malloc(
			sizeof(OpenAPI_policy_association_update_request_ue_t));
	ogs_assert(policy_association_update_request_ue_local_var);

	policy_association_update_request_ue_local_var->notification_uri =
		notification_uri;
	policy_association_update_request_ue_local_var->alt_notif_ipv4_addrs =
		alt_notif_ipv4_addrs;
	policy_association_update_request_ue_local_var->alt_notif_ipv6_addrs =
		alt_notif_ipv6_addrs;
	policy_association_update_request_ue_local_var->alt_notif_fqdns =
		alt_notif_fqdns;
	policy_association_update_request_ue_local_var->triggers = triggers;
	policy_association_update_request_ue_local_var->pra_statuses =
		pra_statuses;
	policy_association_update_request_ue_local_var->user_loc = user_loc;
	policy_association_update_request_ue_local_var->ue_pol_del_result =
		ue_pol_del_result;
	policy_association_update_request_ue_local_var->ue_pol_trans_fail_notif
	        = ue_pol_trans_fail_notif;
	policy_association_update_request_ue_local_var->ue_pol_req = ue_pol_req;
	policy_association_update_request_ue_local_var->guami = guami;
	policy_association_update_request_ue_local_var->serving_nf_id =
		serving_nf_id;
	policy_association_update_request_ue_local_var->plmn_id = plmn_id;
	policy_association_update_request_ue_local_var->connect_state =
		connect_state;
	policy_association_update_request_ue_local_var->group_ids = group_ids;
	policy_association_update_request_ue_local_var->pc5_capab = pc5_capab;
	policy_association_update_request_ue_local_var->a2x_capab = a2x_capab;
	policy_association_update_request_ue_local_var->pro_se_capab =
		pro_se_capab;
	policy_association_update_request_ue_local_var->conf_snssais =
		conf_snssais;
	policy_association_update_request_ue_local_var->n3g_node_re_sel =
		n3g_node_re_sel;
	policy_association_update_request_ue_local_var->slice_n3g_node_sel_cap =
		slice_n3g_node_sel_cap;
	policy_association_update_request_ue_local_var->sat_backhaul_category =
		sat_backhaul_category;
	policy_association_update_request_ue_local_var->ursp_enf_rep =
		ursp_enf_rep;
	policy_association_update_request_ue_local_var->
	is_vps_ue_pol_guidance_null = is_vps_ue_pol_guidance_null;
	policy_association_update_request_ue_local_var->vps_ue_pol_guidance =
		vps_ue_pol_guidance;
	policy_association_update_request_ue_local_var->lbo_roam_info =
		lbo_roam_info;
	policy_association_update_request_ue_local_var->access_types =
		access_types;
	policy_association_update_request_ue_local_var->rat_types = rat_types;
	policy_association_update_request_ue_local_var->supp_feat = supp_feat;
	policy_association_update_request_ue_local_var->rang_sl_capab =
		rang_sl_capab;

	return policy_association_update_request_ue_local_var;
}

void OpenAPI_policy_association_update_request_ue_free(
	OpenAPI_policy_association_update_request_ue_t *
	policy_association_update_request_ue) {
	OpenAPI_lnode_t *node = NULL;

	if(NULL == policy_association_update_request_ue) {
		return;
	}
	if(policy_association_update_request_ue->notification_uri) {
		ogs_free(
			policy_association_update_request_ue->notification_uri);
		policy_association_update_request_ue->notification_uri = NULL;
	}
	if(policy_association_update_request_ue->alt_notif_ipv4_addrs) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->
			alt_notif_ipv4_addrs, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->
			alt_notif_ipv4_addrs);
		policy_association_update_request_ue->alt_notif_ipv4_addrs =
			NULL;
	}
	if(policy_association_update_request_ue->alt_notif_ipv6_addrs) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->
			alt_notif_ipv6_addrs, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->
			alt_notif_ipv6_addrs);
		policy_association_update_request_ue->alt_notif_ipv6_addrs =
			NULL;
	}
	if(policy_association_update_request_ue->alt_notif_fqdns) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->alt_notif_fqdns,
			node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->alt_notif_fqdns);
		policy_association_update_request_ue->alt_notif_fqdns = NULL;
	}
	if(policy_association_update_request_ue->triggers) {
		OpenAPI_list_free(
			policy_association_update_request_ue->triggers);
		policy_association_update_request_ue->triggers = NULL;
	}
	if(policy_association_update_request_ue->pra_statuses) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->pra_statuses,
			node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->pra_statuses);
		policy_association_update_request_ue->pra_statuses = NULL;
	}
	if(policy_association_update_request_ue->user_loc) {
		OpenAPI_user_location_free(
			policy_association_update_request_ue->user_loc);
		policy_association_update_request_ue->user_loc = NULL;
	}
	if(policy_association_update_request_ue->ue_pol_del_result) {
		ogs_free(
			policy_association_update_request_ue->ue_pol_del_result);
		policy_association_update_request_ue->ue_pol_del_result = NULL;
	}
	if(policy_association_update_request_ue->ue_pol_trans_fail_notif) {
		OpenAPI_ue_policy_transfer_failure_notification_free(
			policy_association_update_request_ue->
			ue_pol_trans_fail_notif);
		policy_association_update_request_ue->ue_pol_trans_fail_notif =
			NULL;
	}
	if(policy_association_update_request_ue->ue_pol_req) {
		ogs_free(policy_association_update_request_ue->ue_pol_req);
		policy_association_update_request_ue->ue_pol_req = NULL;
	}
	if(policy_association_update_request_ue->guami) {
		OpenAPI_guami_free(policy_association_update_request_ue->guami);
		policy_association_update_request_ue->guami = NULL;
	}
	if(policy_association_update_request_ue->serving_nf_id) {
		ogs_free(policy_association_update_request_ue->serving_nf_id);
		policy_association_update_request_ue->serving_nf_id = NULL;
	}
	if(policy_association_update_request_ue->plmn_id) {
		OpenAPI_plmn_id_nid_free(
			policy_association_update_request_ue->plmn_id);
		policy_association_update_request_ue->plmn_id = NULL;
	}
	if(policy_association_update_request_ue->connect_state) {
		OpenAPI_cm_state_free(
			policy_association_update_request_ue->connect_state);
		policy_association_update_request_ue->connect_state = NULL;
	}
	if(policy_association_update_request_ue->group_ids) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->group_ids, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->group_ids);
		policy_association_update_request_ue->group_ids = NULL;
	}
	if(policy_association_update_request_ue->a2x_capab) {
		OpenAPI_list_free(
			policy_association_update_request_ue->a2x_capab);
		policy_association_update_request_ue->a2x_capab = NULL;
	}
	if(policy_association_update_request_ue->pro_se_capab) {
		OpenAPI_list_free(
			policy_association_update_request_ue->pro_se_capab);
		policy_association_update_request_ue->pro_se_capab = NULL;
	}
	if(policy_association_update_request_ue->conf_snssais) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->conf_snssais,
			node) {
			OpenAPI_configured_snssai_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->conf_snssais);
		policy_association_update_request_ue->conf_snssais = NULL;
	}
	if(policy_association_update_request_ue->ursp_enf_rep) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->ursp_enf_rep,
			node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ursp_enforcement_pdu_session_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->ursp_enf_rep);
		policy_association_update_request_ue->ursp_enf_rep = NULL;
	}
	if(policy_association_update_request_ue->vps_ue_pol_guidance) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->
			vps_ue_pol_guidance, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ue_policy_parameters_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->
			vps_ue_pol_guidance);
		policy_association_update_request_ue->vps_ue_pol_guidance =
			NULL;
	}
	if(policy_association_update_request_ue->lbo_roam_info) {
		OpenAPI_list_for_each(
			policy_association_update_request_ue->lbo_roam_info,
			node) {
			OpenAPI_lbo_roaming_information_free(node->data);
		}
		OpenAPI_list_free(
			policy_association_update_request_ue->lbo_roam_info);
		policy_association_update_request_ue->lbo_roam_info = NULL;
	}
	if(policy_association_update_request_ue->access_types) {
		OpenAPI_list_free(
			policy_association_update_request_ue->access_types);
		policy_association_update_request_ue->access_types = NULL;
	}
	if(policy_association_update_request_ue->rat_types) {
		OpenAPI_list_free(
			policy_association_update_request_ue->rat_types);
		policy_association_update_request_ue->rat_types = NULL;
	}
	if(policy_association_update_request_ue->supp_feat) {
		ogs_free(policy_association_update_request_ue->supp_feat);
		policy_association_update_request_ue->supp_feat = NULL;
	}
	if(policy_association_update_request_ue->rang_sl_capab) {
		OpenAPI_list_free(
			policy_association_update_request_ue->rang_sl_capab);
		policy_association_update_request_ue->rang_sl_capab = NULL;
	}
	ogs_free(policy_association_update_request_ue);
}

cJSON *OpenAPI_policy_association_update_request_ue_convertToJSON(
	OpenAPI_policy_association_update_request_ue_t *
	policy_association_update_request_ue) {
	cJSON *item = NULL;
	OpenAPI_lnode_t *node = NULL;

	if(policy_association_update_request_ue == NULL) {
		ogs_error(
			"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [PolicyAssociationUpdateRequestUE]");
		return NULL;
	}

	item = cJSON_CreateObject();
	if(policy_association_update_request_ue->notification_uri) {
		if(cJSON_AddStringToObject(item, "notificationUri",
		                           policy_association_update_request_ue
		                           ->notification_uri) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [notification_uri]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->alt_notif_ipv4_addrs) {
		cJSON *alt_notif_ipv4_addrsList = cJSON_AddArrayToObject(item,
		                                                         "altNotifIpv4Addrs");
		if(alt_notif_ipv4_addrsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_ipv4_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->
			alt_notif_ipv4_addrs, node) {
			if(cJSON_AddStringToObject(alt_notif_ipv4_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_ipv4_addrs]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->alt_notif_ipv6_addrs) {
		cJSON *alt_notif_ipv6_addrsList = cJSON_AddArrayToObject(item,
		                                                         "altNotifIpv6Addrs");
		if(alt_notif_ipv6_addrsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_ipv6_addrs]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->
			alt_notif_ipv6_addrs, node) {
			if(cJSON_AddStringToObject(alt_notif_ipv6_addrsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_ipv6_addrs]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->alt_notif_fqdns) {
		cJSON *alt_notif_fqdnsList = cJSON_AddArrayToObject(item,
		                                                    "altNotifFqdns");
		if(alt_notif_fqdnsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_fqdns]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->alt_notif_fqdns,
			node) {
			if(cJSON_AddStringToObject(alt_notif_fqdnsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [alt_notif_fqdns]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->triggers !=
	   OpenAPI_request_trigger_ue_NULL)
	{
		cJSON *triggersList = cJSON_AddArrayToObject(item, "triggers");
		if(triggersList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [triggers]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->triggers, node) {
			if(cJSON_AddStringToObject(triggersList, "",
			                           OpenAPI_request_trigger_ue_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [triggers]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->pra_statuses) {
		cJSON *pra_statuses = cJSON_AddObjectToObject(item,
		                                              "praStatuses");
		if(pra_statuses == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pra_statuses]");
			goto end;
		}
		cJSON *localMapObject = pra_statuses;
		if(policy_association_update_request_ue->pra_statuses) {
			OpenAPI_list_for_each(
				policy_association_update_request_ue->
				pra_statuses, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pra_statuses]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pra_statuses]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_presence_info_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(policy_association_update_request_ue->user_loc) {
		cJSON *user_loc_local_JSON =
			OpenAPI_user_location_convertToJSON(
				policy_association_update_request_ue->user_loc);
		if(user_loc_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [user_loc]");
			goto end;
		}
		cJSON_AddItemToObject(item, "userLoc", user_loc_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [user_loc]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->ue_pol_del_result) {
		if(cJSON_AddStringToObject(item, "uePolDelResult",
		                           policy_association_update_request_ue
		                           ->ue_pol_del_result) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ue_pol_del_result]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->ue_pol_trans_fail_notif) {
		cJSON *ue_pol_trans_fail_notif_local_JSON =
			OpenAPI_ue_policy_transfer_failure_notification_convertToJSON
			        (policy_association_update_request_ue->
			        ue_pol_trans_fail_notif);
		if(ue_pol_trans_fail_notif_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ue_pol_trans_fail_notif]");
			goto end;
		}
		cJSON_AddItemToObject(item, "uePolTransFailNotif",
		                      ue_pol_trans_fail_notif_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ue_pol_trans_fail_notif]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->ue_pol_req) {
		if(cJSON_AddStringToObject(item, "uePolReq",
		                           policy_association_update_request_ue
		                           ->ue_pol_req) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ue_pol_req]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->guami) {
		cJSON *guami_local_JSON =
			OpenAPI_guami_convertToJSON(
				policy_association_update_request_ue->guami);
		if(guami_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [guami]");
			goto end;
		}
		cJSON_AddItemToObject(item, "guami", guami_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [guami]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->serving_nf_id) {
		if(cJSON_AddStringToObject(item, "servingNfId",
		                           policy_association_update_request_ue
		                           ->serving_nf_id) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [serving_nf_id]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->plmn_id) {
		cJSON *plmn_id_local_JSON =
			OpenAPI_plmn_id_nid_convertToJSON(
				policy_association_update_request_ue->plmn_id);
		if(plmn_id_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [plmn_id]");
			goto end;
		}
		cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [plmn_id]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->connect_state) {
		cJSON *connect_state_local_JSON =
			OpenAPI_cm_state_convertToJSON(
				policy_association_update_request_ue->
				connect_state);
		if(connect_state_local_JSON == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [connect_state]");
			goto end;
		}
		cJSON_AddItemToObject(item, "connectState",
		                      connect_state_local_JSON);
		if(item->child == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [connect_state]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->group_ids) {
		cJSON *group_idsList = cJSON_AddArrayToObject(item, "groupIds");
		if(group_idsList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [group_ids]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->group_ids, node) {
			if(cJSON_AddStringToObject(group_idsList, "",
			                           (char *) node->data) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [group_ids]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->pc5_capab !=
	   OpenAPI_pc5_capability_NULL)
	{
		if(cJSON_AddStringToObject(item, "pc5Capab",
		                           OpenAPI_pc5_capability_ToString(
						   policy_association_update_request_ue
						   ->pc5_capab)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pc5_capab]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->a2x_capab !=
	   OpenAPI_a2x_capability_NULL)
	{
		cJSON *a2x_capabList = cJSON_AddArrayToObject(item, "a2xCapab");
		if(a2x_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [a2x_capab]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->a2x_capab, node) {
			if(cJSON_AddStringToObject(a2x_capabList, "",
			                           OpenAPI_a2x_capability_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [a2x_capab]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->pro_se_capab !=
	   OpenAPI_pro_se_capability_ue_NULL)
	{
		cJSON *pro_se_capabList = cJSON_AddArrayToObject(item,
		                                                 "proSeCapab");
		if(pro_se_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pro_se_capab]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->pro_se_capab,
			node) {
			if(cJSON_AddStringToObject(pro_se_capabList, "",
			                           OpenAPI_pro_se_capability_ue_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [pro_se_capab]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->conf_snssais) {
		cJSON *conf_snssaisList = cJSON_AddArrayToObject(item,
		                                                 "confSnssais");
		if(conf_snssaisList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [conf_snssais]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->conf_snssais,
			node) {
			cJSON *itemLocal =
				OpenAPI_configured_snssai_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [conf_snssais]");
				goto end;
			}
			cJSON_AddItemToArray(conf_snssaisList, itemLocal);
		}
	}

	if(policy_association_update_request_ue->n3g_node_re_sel !=
	   OpenAPI_non3gpp_access_NULL)
	{
		if(cJSON_AddStringToObject(item, "n3gNodeReSel",
		                           OpenAPI_non3gpp_access_ToString(
						   policy_association_update_request_ue
						   ->n3g_node_re_sel)) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [n3g_node_re_sel]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->slice_n3g_node_sel_cap !=
	   OpenAPI_slice_specific_n3g_node_selection_capability_NULL)
	{
		if(cJSON_AddStringToObject(item, "sliceN3gNodeSelCap",
		                           OpenAPI_slice_specific_n3g_node_selection_capability_ToString
					   (
						   policy_association_update_request_ue
						   ->slice_n3g_node_sel_cap))
		   == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [slice_n3g_node_sel_cap]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->sat_backhaul_category !=
	   OpenAPI_satellite_backhaul_category_NULL)
	{
		if(cJSON_AddStringToObject(item, "satBackhaulCategory",
		                           OpenAPI_satellite_backhaul_category_ToString
					   (
						   policy_association_update_request_ue
						   ->sat_backhaul_category))
		   == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [sat_backhaul_category]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->ursp_enf_rep) {
		cJSON *ursp_enf_rep = cJSON_AddObjectToObject(item,
		                                              "urspEnfRep");
		if(ursp_enf_rep == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ursp_enf_rep]");
			goto end;
		}
		cJSON *localMapObject = ursp_enf_rep;
		if(policy_association_update_request_ue->ursp_enf_rep) {
			OpenAPI_list_for_each(
				policy_association_update_request_ue->
				ursp_enf_rep, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ursp_enf_rep]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [ursp_enf_rep]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_ursp_enforcement_pdu_session_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	}

	if(policy_association_update_request_ue->vps_ue_pol_guidance) {
		cJSON *vps_ue_pol_guidance = cJSON_AddObjectToObject(item,
		                                                     "vpsUePolGuidance");
		if(vps_ue_pol_guidance == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
			goto end;
		}
		cJSON *localMapObject = vps_ue_pol_guidance;
		if(policy_association_update_request_ue->vps_ue_pol_guidance) {
			OpenAPI_list_for_each(
				policy_association_update_request_ue->
				vps_ue_pol_guidance, node) {
				OpenAPI_map_t *localKeyValue =
					(OpenAPI_map_t *) node->data;
				if(localKeyValue == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
					goto end;
				}
				if(localKeyValue->key == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
					goto end;
				}
				cJSON *itemLocal = localKeyValue->value ?
				                   OpenAPI_ue_policy_parameters_convertToJSON
				                           (localKeyValue->value)
				:
				                   cJSON_CreateNull();
				if(itemLocal == NULL) {
					ogs_error(
						"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [inner]");
					goto end;
				}
				cJSON_AddItemToObject(localMapObject,
				                      localKeyValue->key,
				                      itemLocal);
			}
		}
	} else if(policy_association_update_request_ue->
	          is_vps_ue_pol_guidance_null)
	{
		if(cJSON_AddNullToObject(item, "vpsUePolGuidance") == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [vps_ue_pol_guidance]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->lbo_roam_info) {
		cJSON *lbo_roam_infoList = cJSON_AddArrayToObject(item,
		                                                  "lboRoamInfo");
		if(lbo_roam_infoList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [lbo_roam_info]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->lbo_roam_info,
			node) {
			cJSON *itemLocal =
				OpenAPI_lbo_roaming_information_convertToJSON(
					node->data);
			if(itemLocal == NULL) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [lbo_roam_info]");
				goto end;
			}
			cJSON_AddItemToArray(lbo_roam_infoList, itemLocal);
		}
	}

	if(policy_association_update_request_ue->access_types !=
	   OpenAPI_access_type_NULL)
	{
		cJSON *access_typesList = cJSON_AddArrayToObject(item,
		                                                 "accessTypes");
		if(access_typesList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [access_types]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->access_types,
			node) {
			if(cJSON_AddStringToObject(access_typesList, "",
			                           OpenAPI_access_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [access_types]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->rat_types !=
	   OpenAPI_rat_type_NULL)
	{
		cJSON *rat_typesList = cJSON_AddArrayToObject(item, "ratTypes");
		if(rat_typesList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [rat_types]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->rat_types, node) {
			if(cJSON_AddStringToObject(rat_typesList, "",
			                           OpenAPI_rat_type_ToString(
							   (intptr_t) node->data))
			   == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [rat_types]");
				goto end;
			}
		}
	}

	if(policy_association_update_request_ue->supp_feat) {
		if(cJSON_AddStringToObject(item, "suppFeat",
		                           policy_association_update_request_ue
		                           ->supp_feat) == NULL)
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [supp_feat]");
			goto end;
		}
	}

	if(policy_association_update_request_ue->rang_sl_capab !=
	   OpenAPI_rang_sl_capability_NULL)
	{
		cJSON *rang_sl_capabList = cJSON_AddArrayToObject(item,
		                                                  "rangSlCapab");
		if(rang_sl_capabList == NULL) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [rang_sl_capab]");
			goto end;
		}
		OpenAPI_list_for_each(
			policy_association_update_request_ue->rang_sl_capab,
			node) {
			if(cJSON_AddStringToObject(rang_sl_capabList, "",
			                           OpenAPI_rang_sl_capability_ToString
			                                   ((intptr_t) node->
			                                   data)) == NULL)
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_convertToJSON() failed [rang_sl_capab]");
				goto end;
			}
		}
	}

end:
	return item;
}

OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_parseFromJSON(
	cJSON *policy_association_update_request_ueJSON) {
	OpenAPI_policy_association_update_request_ue_t *
	        policy_association_update_request_ue_local_var = NULL;
	OpenAPI_lnode_t *node = NULL;
	cJSON *notification_uri = NULL;
	cJSON *alt_notif_ipv4_addrs = NULL;
	OpenAPI_list_t *alt_notif_ipv4_addrsList = NULL;
	cJSON *alt_notif_ipv6_addrs = NULL;
	OpenAPI_list_t *alt_notif_ipv6_addrsList = NULL;
	cJSON *alt_notif_fqdns = NULL;
	OpenAPI_list_t *alt_notif_fqdnsList = NULL;
	cJSON *triggers = NULL;
	OpenAPI_list_t *triggersList = NULL;
	cJSON *pra_statuses = NULL;
	OpenAPI_list_t *pra_statusesList = NULL;
	cJSON *user_loc = NULL;
	OpenAPI_user_location_t *user_loc_local_nonprim = NULL;
	cJSON *ue_pol_del_result = NULL;
	cJSON *ue_pol_trans_fail_notif = NULL;
	OpenAPI_ue_policy_transfer_failure_notification_t *
	        ue_pol_trans_fail_notif_local_nonprim = NULL;
	cJSON *ue_pol_req = NULL;
	cJSON *guami = NULL;
	OpenAPI_guami_t *guami_local_nonprim = NULL;
	cJSON *serving_nf_id = NULL;
	cJSON *plmn_id = NULL;
	OpenAPI_plmn_id_nid_t *plmn_id_local_nonprim = NULL;
	cJSON *connect_state = NULL;
	OpenAPI_cm_state_t *connect_state_local_nonprim = NULL;
	cJSON *group_ids = NULL;
	OpenAPI_list_t *group_idsList = NULL;
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
	cJSON *ursp_enf_rep = NULL;
	OpenAPI_list_t *ursp_enf_repList = NULL;
	cJSON *vps_ue_pol_guidance = NULL;
	OpenAPI_list_t *vps_ue_pol_guidanceList = NULL;
	cJSON *lbo_roam_info = NULL;
	OpenAPI_list_t *lbo_roam_infoList = NULL;
	cJSON *access_types = NULL;
	OpenAPI_list_t *access_typesList = NULL;
	cJSON *rat_types = NULL;
	OpenAPI_list_t *rat_typesList = NULL;
	cJSON *supp_feat = NULL;
	cJSON *rang_sl_capab = NULL;
	OpenAPI_list_t *rang_sl_capabList = NULL;
	notification_uri =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"notificationUri");
	if(notification_uri) {
		if(!cJSON_IsString(notification_uri) &&
		   !cJSON_IsNull(notification_uri))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [notification_uri]");
			goto end;
		}
	}

	alt_notif_ipv4_addrs =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"altNotifIpv4Addrs");
	if(alt_notif_ipv4_addrs) {
		cJSON *alt_notif_ipv4_addrs_local = NULL;
		if(!cJSON_IsArray(alt_notif_ipv4_addrs)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_ipv4_addrs]");
			goto end;
		}

		alt_notif_ipv4_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_ipv4_addrs_local,
		                   alt_notif_ipv4_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_ipv4_addrs_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_ipv4_addrs]");
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
			policy_association_update_request_ueJSON,
			"altNotifIpv6Addrs");
	if(alt_notif_ipv6_addrs) {
		cJSON *alt_notif_ipv6_addrs_local = NULL;
		if(!cJSON_IsArray(alt_notif_ipv6_addrs)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_ipv6_addrs]");
			goto end;
		}

		alt_notif_ipv6_addrsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_ipv6_addrs_local,
		                   alt_notif_ipv6_addrs) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_ipv6_addrs_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_ipv6_addrs]");
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
			policy_association_update_request_ueJSON,
			"altNotifFqdns");
	if(alt_notif_fqdns) {
		cJSON *alt_notif_fqdns_local = NULL;
		if(!cJSON_IsArray(alt_notif_fqdns)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_fqdns]");
			goto end;
		}

		alt_notif_fqdnsList = OpenAPI_list_create();

		cJSON_ArrayForEach(alt_notif_fqdns_local, alt_notif_fqdns) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(alt_notif_fqdns_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [alt_notif_fqdns]");
				goto end;
			}
			OpenAPI_list_add(alt_notif_fqdnsList,
			                 ogs_strdup(
						 alt_notif_fqdns_local->
						 valuestring));
		}
	}

	triggers =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "triggers");
	if(triggers) {
		cJSON *triggers_local = NULL;
		if(!cJSON_IsArray(triggers)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [triggers]");
			goto end;
		}

		triggersList = OpenAPI_list_create();

		cJSON_ArrayForEach(triggers_local, triggers) {
			OpenAPI_request_trigger_ue_e localEnum =
				OpenAPI_request_trigger_ue_NULL;
			if(!cJSON_IsString(triggers_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [triggers]");
				goto end;
			}
			localEnum =
				OpenAPI_request_trigger_ue_FromString(
					triggers_local->valuestring);
			if(!localEnum) {
				ogs_info(
					"Enum value \"%s\" for field \"triggers\" is not supported. Ignoring it ...",
					triggers_local->valuestring);
			} else {
				OpenAPI_list_add(triggersList,
				                 (void *) localEnum);
			}
		}
		if(triggersList->count == 0) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected triggersList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	pra_statuses =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"praStatuses");
	if(pra_statuses) {
		cJSON *pra_statuses_local_map = NULL;
		if(!cJSON_IsObject(pra_statuses) &&
		   !cJSON_IsNull(pra_statuses))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [pra_statuses]");
			goto end;
		}
		if(cJSON_IsObject(pra_statuses)) {
			pra_statusesList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(pra_statuses_local_map,
			                   pra_statuses) {
				cJSON *localMapObject = pra_statuses_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_presence_info_parseFromJSON
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
						"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(pra_statusesList,
				                 localMapKeyPair);
			}
		}
	}

	user_loc =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "userLoc");
	if(user_loc) {
		user_loc_local_nonprim =
			OpenAPI_user_location_parseFromJSON(user_loc);
		if(!user_loc_local_nonprim) {
			ogs_error(
				"OpenAPI_user_location_parseFromJSON failed [user_loc]");
			goto end;
		}
	}

	ue_pol_del_result =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"uePolDelResult");
	if(ue_pol_del_result) {
		if(!cJSON_IsString(ue_pol_del_result) &&
		   !cJSON_IsNull(ue_pol_del_result))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [ue_pol_del_result]");
			goto end;
		}
	}

	ue_pol_trans_fail_notif =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"uePolTransFailNotif");
	if(ue_pol_trans_fail_notif) {
		ue_pol_trans_fail_notif_local_nonprim =
			OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON
			        (ue_pol_trans_fail_notif);
		if(!ue_pol_trans_fail_notif_local_nonprim) {
			ogs_error(
				"OpenAPI_ue_policy_transfer_failure_notification_parseFromJSON failed [ue_pol_trans_fail_notif]");
			goto end;
		}
	}

	ue_pol_req =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "uePolReq");
	if(ue_pol_req) {
		if(!cJSON_IsString(ue_pol_req) &&
		   !cJSON_IsNull(ue_pol_req))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [ue_pol_req]");
			goto end;
		}
	}

	guami =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "guami");
	if(guami) {
		guami_local_nonprim = OpenAPI_guami_parseFromJSON(guami);
		if(!guami_local_nonprim) {
			ogs_error("OpenAPI_guami_parseFromJSON failed [guami]");
			goto end;
		}
	}

	serving_nf_id =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"servingNfId");
	if(serving_nf_id) {
		if(!cJSON_IsString(serving_nf_id) &&
		   !cJSON_IsNull(serving_nf_id))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [serving_nf_id]");
			goto end;
		}
	}

	plmn_id =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "plmnId");
	if(plmn_id) {
		plmn_id_local_nonprim =
			OpenAPI_plmn_id_nid_parseFromJSON(plmn_id);
		if(!plmn_id_local_nonprim) {
			ogs_error(
				"OpenAPI_plmn_id_nid_parseFromJSON failed [plmn_id]");
			goto end;
		}
	}

	connect_state =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"connectState");
	if(connect_state) {
		connect_state_local_nonprim =
			OpenAPI_cm_state_parseFromJSON(connect_state);
		if(!connect_state_local_nonprim) {
			ogs_error(
				"OpenAPI_cm_state_parseFromJSON failed [connect_state]");
			goto end;
		}
	}

	group_ids =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "groupIds");
	if(group_ids) {
		cJSON *group_ids_local = NULL;
		if(!cJSON_IsArray(group_ids)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [group_ids]");
			goto end;
		}

		group_idsList = OpenAPI_list_create();

		cJSON_ArrayForEach(group_ids_local, group_ids) {
			double *localDouble = NULL;
			int *localInt = NULL;
			if(!cJSON_IsString(group_ids_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [group_ids]");
				goto end;
			}
			OpenAPI_list_add(group_idsList,
			                 ogs_strdup(
						 group_ids_local->valuestring));
		}
	}

	pc5_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "pc5Capab");
	if(pc5_capab) {
		if(!cJSON_IsString(pc5_capab)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [pc5_capab]");
			goto end;
		}
		pc5_capabVariable =
			OpenAPI_pc5_capability_FromString(
				pc5_capab->valuestring);
	}

	a2x_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "a2xCapab");
	if(a2x_capab) {
		cJSON *a2x_capab_local = NULL;
		if(!cJSON_IsArray(a2x_capab)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [a2x_capab]");
			goto end;
		}

		a2x_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(a2x_capab_local, a2x_capab) {
			OpenAPI_a2x_capability_e localEnum =
				OpenAPI_a2x_capability_NULL;
			if(!cJSON_IsString(a2x_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [a2x_capab]");
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
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected a2x_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	pro_se_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "proSeCapab");
	if(pro_se_capab) {
		cJSON *pro_se_capab_local = NULL;
		if(!cJSON_IsArray(pro_se_capab)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [pro_se_capab]");
			goto end;
		}

		pro_se_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(pro_se_capab_local, pro_se_capab) {
			OpenAPI_pro_se_capability_ue_e localEnum =
				OpenAPI_pro_se_capability_ue_NULL;
			if(!cJSON_IsString(pro_se_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [pro_se_capab]");
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
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected pro_se_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	conf_snssais =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"confSnssais");
	if(conf_snssais) {
		cJSON *conf_snssais_local = NULL;
		if(!cJSON_IsArray(conf_snssais)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [conf_snssais]");
			goto end;
		}

		conf_snssaisList = OpenAPI_list_create();

		cJSON_ArrayForEach(conf_snssais_local, conf_snssais) {
			if(!cJSON_IsObject(conf_snssais_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [conf_snssais]");
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
			policy_association_update_request_ueJSON,
			"n3gNodeReSel");
	if(n3g_node_re_sel) {
		if(!cJSON_IsString(n3g_node_re_sel)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [n3g_node_re_sel]");
			goto end;
		}
		n3g_node_re_selVariable =
			OpenAPI_non3gpp_access_FromString(
				n3g_node_re_sel->valuestring);
	}

	slice_n3g_node_sel_cap =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"sliceN3gNodeSelCap");
	if(slice_n3g_node_sel_cap) {
		if(!cJSON_IsString(slice_n3g_node_sel_cap)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [slice_n3g_node_sel_cap]");
			goto end;
		}
		slice_n3g_node_sel_capVariable =
			OpenAPI_slice_specific_n3g_node_selection_capability_FromString
			        (slice_n3g_node_sel_cap->valuestring);
	}

	sat_backhaul_category =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"satBackhaulCategory");
	if(sat_backhaul_category) {
		if(!cJSON_IsString(sat_backhaul_category)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [sat_backhaul_category]");
			goto end;
		}
		sat_backhaul_categoryVariable =
			OpenAPI_satellite_backhaul_category_FromString(
				sat_backhaul_category->valuestring);
	}

	ursp_enf_rep =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "urspEnfRep");
	if(ursp_enf_rep) {
		cJSON *ursp_enf_rep_local_map = NULL;
		if(!cJSON_IsObject(ursp_enf_rep) &&
		   !cJSON_IsNull(ursp_enf_rep))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [ursp_enf_rep]");
			goto end;
		}
		if(cJSON_IsObject(ursp_enf_rep)) {
			ursp_enf_repList = OpenAPI_list_create();
			OpenAPI_map_t *localMapKeyPair = NULL;
			cJSON_ArrayForEach(ursp_enf_rep_local_map,
			                   ursp_enf_rep) {
				cJSON *localMapObject = ursp_enf_rep_local_map;
				if(cJSON_IsObject(localMapObject)) {
					localMapKeyPair = OpenAPI_map_create(
						ogs_strdup(
							localMapObject->string),
						OpenAPI_ursp_enforcement_pdu_session_parseFromJSON
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
						"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [inner]");
					goto end;
				}
				OpenAPI_list_add(ursp_enf_repList,
				                 localMapKeyPair);
			}
		}
	}

	vps_ue_pol_guidance =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"vpsUePolGuidance");
	if(vps_ue_pol_guidance) {
		if(!cJSON_IsNull(vps_ue_pol_guidance)) {
			cJSON *vps_ue_pol_guidance_local_map = NULL;
			if(!cJSON_IsObject(vps_ue_pol_guidance) &&
			   !cJSON_IsNull(vps_ue_pol_guidance))
			{
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [vps_ue_pol_guidance]");
				goto end;
			}
			if(cJSON_IsObject(vps_ue_pol_guidance)) {
				vps_ue_pol_guidanceList = OpenAPI_list_create();
				OpenAPI_map_t *localMapKeyPair = NULL;
				cJSON_ArrayForEach(
					vps_ue_pol_guidance_local_map,
					vps_ue_pol_guidance) {
					cJSON *localMapObject =
						vps_ue_pol_guidance_local_map;
					if(cJSON_IsObject(localMapObject)) {
						localMapKeyPair =
							OpenAPI_map_create(
								ogs_strdup(
									localMapObject
									->string),
								OpenAPI_ue_policy_parameters_parseFromJSON
								(
									localMapObject));
					} else if(cJSON_IsNull(
							  localMapObject))
					{
						localMapKeyPair =
							OpenAPI_map_create(
								ogs_strdup(
									localMapObject
									->string),
								NULL);
					} else {
						ogs_error(
							"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [inner]");
						goto end;
					}
					OpenAPI_list_add(
						vps_ue_pol_guidanceList,
						localMapKeyPair);
				}
			}
		}
	}

	lbo_roam_info =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"lboRoamInfo");
	if(lbo_roam_info) {
		cJSON *lbo_roam_info_local = NULL;
		if(!cJSON_IsArray(lbo_roam_info)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [lbo_roam_info]");
			goto end;
		}

		lbo_roam_infoList = OpenAPI_list_create();

		cJSON_ArrayForEach(lbo_roam_info_local, lbo_roam_info) {
			if(!cJSON_IsObject(lbo_roam_info_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [lbo_roam_info]");
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

	access_types =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"accessTypes");
	if(access_types) {
		cJSON *access_types_local = NULL;
		if(!cJSON_IsArray(access_types)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [access_types]");
			goto end;
		}

		access_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(access_types_local, access_types) {
			OpenAPI_access_type_e localEnum =
				OpenAPI_access_type_NULL;
			if(!cJSON_IsString(access_types_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [access_types]");
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
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected access_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	rat_types =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "ratTypes");
	if(rat_types) {
		cJSON *rat_types_local = NULL;
		if(!cJSON_IsArray(rat_types)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [rat_types]");
			goto end;
		}

		rat_typesList = OpenAPI_list_create();

		cJSON_ArrayForEach(rat_types_local, rat_types) {
			OpenAPI_rat_type_e localEnum = OpenAPI_rat_type_NULL;
			if(!cJSON_IsString(rat_types_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [rat_types]");
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
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected rat_typesList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	supp_feat =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON, "suppFeat");
	if(supp_feat) {
		if(!cJSON_IsString(supp_feat) &&
		   !cJSON_IsNull(supp_feat))
		{
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [supp_feat]");
			goto end;
		}
	}

	rang_sl_capab =
		cJSON_GetObjectItemCaseSensitive(
			policy_association_update_request_ueJSON,
			"rangSlCapab");
	if(rang_sl_capab) {
		cJSON *rang_sl_capab_local = NULL;
		if(!cJSON_IsArray(rang_sl_capab)) {
			ogs_error(
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [rang_sl_capab]");
			goto end;
		}

		rang_sl_capabList = OpenAPI_list_create();

		cJSON_ArrayForEach(rang_sl_capab_local, rang_sl_capab) {
			OpenAPI_rang_sl_capability_e localEnum =
				OpenAPI_rang_sl_capability_NULL;
			if(!cJSON_IsString(rang_sl_capab_local)) {
				ogs_error(
					"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed [rang_sl_capab]");
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
				"OpenAPI_policy_association_update_request_ue_parseFromJSON() failed: Expected rang_sl_capabList to not be empty (after ignoring unsupported enum values).");
			goto end;
		}
	}

	policy_association_update_request_ue_local_var =
		OpenAPI_policy_association_update_request_ue_create(
			notification_uri &&
			!cJSON_IsNull(notification_uri) ?
			ogs_strdup(notification_uri->valuestring) : NULL,
			alt_notif_ipv4_addrs ? alt_notif_ipv4_addrsList : NULL,
			alt_notif_ipv6_addrs ? alt_notif_ipv6_addrsList : NULL,
			alt_notif_fqdns ? alt_notif_fqdnsList : NULL,
			triggers ? triggersList : NULL,
			pra_statuses ? pra_statusesList : NULL,
			user_loc ? user_loc_local_nonprim : NULL,
			ue_pol_del_result &&
			!cJSON_IsNull(ue_pol_del_result) ?
			ogs_strdup(ue_pol_del_result->valuestring) : NULL,
			ue_pol_trans_fail_notif ?
			ue_pol_trans_fail_notif_local_nonprim : NULL,
			ue_pol_req &&
			!cJSON_IsNull(ue_pol_req) ?
			ogs_strdup(ue_pol_req->valuestring) : NULL,
			guami ? guami_local_nonprim : NULL,
			serving_nf_id &&
			!cJSON_IsNull(serving_nf_id) ?
			ogs_strdup(serving_nf_id->valuestring) : NULL,
			plmn_id ? plmn_id_local_nonprim : NULL,
			connect_state ? connect_state_local_nonprim : NULL,
			group_ids ? group_idsList : NULL,
			pc5_capab ? pc5_capabVariable : 0,
			a2x_capab ? a2x_capabList : NULL,
			pro_se_capab ? pro_se_capabList : NULL,
			conf_snssais ? conf_snssaisList : NULL,
			n3g_node_re_sel ? n3g_node_re_selVariable : 0,
			slice_n3g_node_sel_cap ?
			slice_n3g_node_sel_capVariable : 0,
			sat_backhaul_category ? sat_backhaul_categoryVariable :
			0,
			ursp_enf_rep ? ursp_enf_repList : NULL,
			vps_ue_pol_guidance &&
			cJSON_IsNull(vps_ue_pol_guidance) ? true : false,
			vps_ue_pol_guidance ? vps_ue_pol_guidanceList : NULL,
			lbo_roam_info ? lbo_roam_infoList : NULL,
			access_types ? access_typesList : NULL,
			rat_types ? rat_typesList : NULL,
			supp_feat &&
			!cJSON_IsNull(supp_feat) ?
			ogs_strdup(supp_feat->valuestring) :
			NULL,
			rang_sl_capab ? rang_sl_capabList : NULL
			);

	return policy_association_update_request_ue_local_var;
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
	if(triggersList) {
		OpenAPI_list_free(triggersList);
		triggersList = NULL;
	}
	if(pra_statusesList) {
		OpenAPI_list_for_each(pra_statusesList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_presence_info_free(localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(pra_statusesList);
		pra_statusesList = NULL;
	}
	if(user_loc_local_nonprim) {
		OpenAPI_user_location_free(user_loc_local_nonprim);
		user_loc_local_nonprim = NULL;
	}
	if(ue_pol_trans_fail_notif_local_nonprim) {
		OpenAPI_ue_policy_transfer_failure_notification_free(
			ue_pol_trans_fail_notif_local_nonprim);
		ue_pol_trans_fail_notif_local_nonprim = NULL;
	}
	if(guami_local_nonprim) {
		OpenAPI_guami_free(guami_local_nonprim);
		guami_local_nonprim = NULL;
	}
	if(plmn_id_local_nonprim) {
		OpenAPI_plmn_id_nid_free(plmn_id_local_nonprim);
		plmn_id_local_nonprim = NULL;
	}
	if(connect_state_local_nonprim) {
		OpenAPI_cm_state_free(connect_state_local_nonprim);
		connect_state_local_nonprim = NULL;
	}
	if(group_idsList) {
		OpenAPI_list_for_each(group_idsList, node) {
			ogs_free(node->data);
		}
		OpenAPI_list_free(group_idsList);
		group_idsList = NULL;
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
	if(ursp_enf_repList) {
		OpenAPI_list_for_each(ursp_enf_repList, node) {
			OpenAPI_map_t *localKeyValue =
				(OpenAPI_map_t *) node->data;
			ogs_free(localKeyValue->key);
			OpenAPI_ursp_enforcement_pdu_session_free(
				localKeyValue->value);
			OpenAPI_map_free(localKeyValue);
		}
		OpenAPI_list_free(ursp_enf_repList);
		ursp_enf_repList = NULL;
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
	if(access_typesList) {
		OpenAPI_list_free(access_typesList);
		access_typesList = NULL;
	}
	if(rat_typesList) {
		OpenAPI_list_free(rat_typesList);
		rat_typesList = NULL;
	}
	if(rang_sl_capabList) {
		OpenAPI_list_free(rang_sl_capabList);
		rang_sl_capabList = NULL;
	}
	return NULL;
}

OpenAPI_policy_association_update_request_ue_t *
OpenAPI_policy_association_update_request_ue_copy(
	OpenAPI_policy_association_update_request_ue_t	*dst,
	OpenAPI_policy_association_update_request_ue_t	*src) {
	cJSON *item = NULL;
	char *content = NULL;

	ogs_assert(src);
	item = OpenAPI_policy_association_update_request_ue_convertToJSON(src);
	if(!item) {
		ogs_error(
			"OpenAPI_policy_association_update_request_ue_convertToJSON() failed");
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

	OpenAPI_policy_association_update_request_ue_free(dst);
	dst = OpenAPI_policy_association_update_request_ue_parseFromJSON(item);
	cJSON_Delete(item);

	return dst;
}
