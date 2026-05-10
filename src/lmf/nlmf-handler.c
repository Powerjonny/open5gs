/*
 * Copyright (C) 2025 by Juraj Elias <juraj.elias@gmail.com>
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

#include "nlmf-handler.h"
#include "namf-build.h"
#include "context.h"
#include "sbi-path.h"

int lmf_nlmf_handle_determine_location(
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
	lmf_event_t e;
    lmf_location_request_t *location_request = NULL;
    OpenAPI_input_data_t *input_data = NULL;
	OpenAPI_lnode_t *node;

    ogs_assert(stream);
    ogs_assert(recvmsg);

    /* Parse InputData from message */
    input_data = recvmsg->InputData;
    if (!input_data) {
        ogs_error("No InputData in determine location request");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No InputData", NULL, NULL));
        return OGS_ERROR;
    }

    /* Extract SUPI (required) */
    if (!input_data->supi) {
        ogs_error("No SUPI in InputData");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_BAD_REQUEST,
                recvmsg, "No SUPI in InputData", NULL, NULL));
        return OGS_ERROR;
    }

    /* Create location request context */
    location_request = lmf_location_request_add();
    if (!location_request) {
        ogs_error("lmf_location_request_add() failed");
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                recvmsg, "Internal server error", NULL, NULL));
        return OGS_ERROR;
    }

    /* Store stream ID for async response */
    location_request->stream_id = ogs_sbi_id_from_stream(stream);

    /* Extract SUPI */
    location_request->supi = ogs_strdup(input_data->supi);
    ogs_assert(location_request->supi);

    /* Extract AMF ID if present */
    if (input_data->amf_id) {
        location_request->amf_id = ogs_strdup(input_data->amf_id);
        ogs_assert(location_request->amf_id);
    }

    /* Extract NR CGI if present */
    if (input_data->ncgi) {
        if(!ogs_sbi_parse_plmn_id(&location_request->nr_cgi.plmn_id, input_data->ncgi->plmn_id))
        {
			ogs_error("[%s] Included NR Global Cell Identifier of serving gNB could not be extracted", location_request->supi);
			goto err;
		}
		location_request->nr_cgi.cell_id = ogs_uint64_from_string_hexadecimal(input_data->ncgi->nr_cell_id);
    }

    /* Extract LCS Indicator if present */
    if(input_data->ue_location_service_ind != OpenAPI_ue_location_service_ind_NULL)
    {
		location_request->is_molr = true;
		location_request->lcs_service_type = input_data->ue_location_service_ind;
    }

    ogs_info("[%s] Location request: SUPI=%s, AMF_ID=%s",
            location_request->supi,
            location_request->supi,
            location_request->amf_id ? location_request->amf_id : "N/A");

    /* Store the input message in location_request for later cleanup */
    /* We need to keep it because it contains allocated OpenAPI objects (InputData) */
    location_request->input_message = ogs_calloc(1, sizeof(ogs_sbi_message_t));
    if (!location_request->input_message) {
        ogs_error("[%s] Failed to allocate input_message",
                location_request->supi);
        ogs_assert(true ==
            ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                recvmsg, "Internal server error", NULL, NULL));
        /* Don't free recvmsg->h here - it's shared with request->h
         * which will be freed by the server framework */
        ogs_sbi_message_free(recvmsg);
        lmf_location_request_remove(location_request);
        return OGS_ERROR;
    }
    /* Copy the message structure - this transfers ownership of allocated members */
    memcpy(location_request->input_message, recvmsg, sizeof(ogs_sbi_message_t));
    /* Clear the original message to prevent double-free when caller frees it */
    memset(recvmsg, 0, sizeof(ogs_sbi_message_t));

    /*
     * Determine positioning capabilities of UE:
     *
     * (a) if LPP is supported only:
     *	  - subscribe for N1 messages (LPP) to AMF
     *    - check, if LPP messages were already received within MO-LR.
     * 	  - request LPP capabilities if needed.
     *
     * (b) a) applies and LCS over user plane is supported:
     *    - subscribe for N1 messages (UPP-CMI) to AMF
     *	  - negotiate secure user plane connection for LCS (UPP-CM)
     *	  - request LPP capabilities.
     *
     * (c) otherwise: a network-based approach must be used (e.g. ECID, NR ECID)
     *	  - TODO ...
     */
    if(input_data->lpp_message || (input_data->ue_lcs_cap && input_data->ue_lcs_cap->is_lpp_support && input_data->ue_lcs_cap->lpp_support))
    {
		/* Storing LPP support in LR context */
		location_request->ue_lcs_cap.lpp = true;

		/* Initialize state machine for LPP handling */
		memset(&e, 0, sizeof(lmf_event_t));
		e.lr_id = location_request->id;
		ogs_fsm_init(&location_request->lpp.sm, lpp_state_initial, lpp_state_final, &e);
	}

	/*
	 * If LCS-UP is also supported, we also initialize its state machine...
 	 */
	if(location_request->ue_lcs_cap.lpp && input_data->ue_up_pos_caps)
	{
    	OpenAPI_list_for_each(input_data->ue_up_pos_caps, node) {
        	OpenAPI_ue_up_positioning_capabilities_e val = (OpenAPI_ue_up_positioning_capabilities_e) node->data;

			if(val == OpenAPI_ue_up_positioning_capabilities_LCS_UPP)
			{
				/* Storing UPP support in LR context */
		   		location_request->ue_lcs_cap.lcsupp = true;

				/* Initialize state machine for UPP handling */
				memset(&e, 0, sizeof(lmf_event_t));
				e.lr_id = location_request->id;
				ogs_fsm_init(&location_request->upp.sm, upp_state_initial, upp_state_final, &e);
			}
			else if(val == OpenAPI_ue_up_positioning_capabilities_MULTIPLE_LCS_UPP)
			{
				/* Multiple LCS-UP connections are supported */
	   			location_request->ue_lcs_cap.mlcs_up = true;
			}
    	}
	}

		//Subscribe for LPP messages...
		//rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, NULL,(ogs_sbi_request_t *(*)(lmf_location_request_t *, void *))lmf_namf_build_n1n2_message_subscribe,
//            location_request, (void*)OpenAPI_n1_message_class_LPP);

/*	    if (rv != OGS_OK) {
    	    ogs_error("[%s] lmf_amf_sbi_discover_and_send() failed: %d",
        	        location_request->supi ? location_request->supi : "Unknown", rv);
 	    }*/

    if(!location_request->ue_lcs_cap.lpp && !location_request->ue_lcs_cap.lcsupp)
    {
		//Here, we have to subscribe for N2 (NRPPa) messages first, when we implement it in future.
		ogs_error("[%s] No LPP/UPP support. Network-based positioning is currently not implemented.", location_request->supi);
		goto err;
    }

    /* Response will be sent asynchronously when location is determined */
    /* input_message will be freed in lmf_location_request_remove() */
    return OGS_OK;

err:
    /* Only send error if location_request still exists (error wasn't already sent) */
    if (location_request->input_message) {
        ogs_assert(true ==
              ogs_sbi_server_send_error(stream, OGS_SBI_HTTP_STATUS_INTERNAL_SERVER_ERROR,
                    location_request->input_message, "Location determination failed", NULL, NULL));
        /* Free InputData explicitly before freeing message */
        if (location_request->input_message->InputData) {
            OpenAPI_input_data_free(location_request->input_message->InputData);
               location_request->input_message->InputData = NULL;
        }
        ogs_sbi_message_free(location_request->input_message);
        ogs_free(location_request->input_message);
        location_request->input_message = NULL;
    }

    /* Only remove if it wasn't already removed */
    if (location_request->supi) {
        lmf_location_request_remove(location_request);
    }

    return OGS_ERROR;
}
