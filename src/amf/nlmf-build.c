/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "nlmf-build.h"

ogs_sbi_request_t*
amf_nlmf_build_determine_location_request(amf_ue_t *amf_ue, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    OpenAPI_ue_up_positioning_capabilities_e cap1 = OpenAPI_ue_up_positioning_capabilities_LCS_UPP,
					     cap2 = OpenAPI_ue_up_positioning_capabilities_MULTIPLE_LCS_UPP;

    OpenAPI_input_data_t input;

    ogs_assert(amf_ue);

    /*
     * Initialize message header with path: /nlmf-loc/v1/determine-location
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_DETERMINE_LOCATION;

    /*
     * Initialize JSON body via InputData IE
     */
    memset(&input, 0, sizeof(OpenAPI_input_data_t));
    message.InputData = &input;
    input.amf_id = NF_INSTANCE_ID(ogs_sbi_self()->nf_instance);
    input.supi = amf_ue->supi;
    input.ncgi = ogs_calloc(1, sizeof(struct OpenAPI_ncgi_s));
    ogs_assert(input.ncgi);
    input.ncgi->plmn_id = ogs_sbi_build_plmn_id(&amf_ue->nr_cgi.plmn_id);
    ogs_assert(input.ncgi->plmn_id);
    input.ncgi->nr_cell_id = ogs_uint64_to_string(amf_ue->nr_cgi.cell_id);
    ogs_assert(input.ncgi->nr_cell_id);
    input.ue_location_service_ind = OpenAPI_ue_location_service_ind_LOCATION_ESTIMATE; //later, we will set it to Assistance data, when we have implemented MO-LR reception!

    if(amf_ue->gmm_capability.lte_positioning_protocol_capability)
    {
	input.ue_lcs_cap = CALLOC(1, sizeof(struct OpenAPI_ue_lcs_capability_s));
	ogs_assert(input.ue_lcs_cap);
	input.ue_lcs_cap->is_lpp_support = true;
	input.ue_lcs_cap->lpp_support = 1;
    }

    if(amf_ue->gmm_capability.lcs_upp)
    {
	input.ue_up_pos_caps = OpenAPI_list_create();
	ogs_assert(input.ue_up_pos_caps);
	OpenAPI_list_add(input.ue_up_pos_caps, (void*)cap1);
    }

    if(amf_ue->gmm_capability.mlcs_up)
    {
	if(!input.ue_up_pos_caps)
	{
	    input.ue_up_pos_caps = OpenAPI_list_create();
	    ogs_assert(input.ue_up_pos_caps);
	}
	OpenAPI_list_add(input.ue_up_pos_caps, (void*)cap2);
    }

    request = ogs_sbi_build_request(&message);
    ogs_expect(request);

	/*
	 * Free allocated memory
	 */
	if(input.ue_lcs_cap)
	{
		ogs_free(input.ue_lcs_cap);
		input.ue_lcs_cap = NULL;
	}

	if(input.ue_up_pos_caps)
	{
	    OpenAPI_list_free(input.ue_up_pos_caps);
		input.ue_up_pos_caps = NULL;
	}

	if(input.ncgi)
	{
		if(input.ncgi->plmn_id)
		{
			ogs_sbi_free_plmn_id(input.ncgi->plmn_id);
		}
		if(input.ncgi->nr_cell_id)
		{
			ogs_free(input.ncgi->nr_cell_id);
		}
		ogs_free(input.ncgi);
	}

	return request;
}

//TODO: we need in @data: a) indicator of LCS-UP connection setup or termination,
// b) a notify correlation iD (probably an initial LCS-UP context iD that is implemented as in LMF independently of an AMF-UE context)
// c) 
ogs_sbi_request_t *amf_nlmf_build_up_config_request(amf_ue_t *amf_ue, void *data)
{
	ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

	OpenAPI_up_config_t up_cfg;

	ogs_assert(amf_ue);
	ogs_assert(amf_ue->supi);

	/*
     * Initialize message header with path: /nlmf-loc/v1/configure-up
     */
    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name = (char *)OGS_SBI_SERVICE_NAME_NLMF_LOC;
    message.h.api.version = (char *)OGS_SBI_API_V1;

    message.h.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_CONFIGURE_UP;

	/* Initialize JSON body with UPConfig IE */
	memset(&up_cfg, 0, sizeof(OpenAPI_up_config_t));
	message.UpConfig = &up_cfg;

	//TODO: continue here

	return request;
}
