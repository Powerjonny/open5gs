/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock.de>
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
#include "lpp-path.h"
#include "namf-build.h"
#include "sbi-path.h"

int lpp_send_to_amf(lmf_location_request_t *request, ogs_pkbuf_t *pkbuf, lmf_timer_e timer_id)
{
	int rv = OGS_OK;
	lmf_n1n2_message_params_t params;
	ogs_sbi_discovery_option_t *discovery_option = NULL;
	ogs_sbi_nf_instance_t *nf_instance = NULL;
	lmf_sbi_params_t sbi_params;

	ogs_assert(request);
	ogs_assert(pkbuf);

	/* Create parameter structure to build SBI message */
	memset(&params, 0, sizeof(lmf_n1n2_message_params_t));
	params.n1.type = OpenAPI_n1_message_class_LPP;
	params.n1.pkbuf = pkbuf;

	memset(&sbi_params, 0, sizeof(lmf_sbi_params_t));
	sbi_params.type = LMF_SBI_PARAMS_TYPE_LOCATION_REQUEST;
	sbi_params.location_request = request;

	/* Build and send SBI message to AMF via NRF */
	if(!request->amf_id)
	{
		goto send;
	}

	discovery_option = ogs_sbi_discovery_option_new();
	if(!discovery_option)
	{
		ogs_warn("[%s] LPP message transfer to AMF is done without discovery option.", request->supi);
		goto send;
	}

	nf_instance = ogs_sbi_nf_instance_find(request->amf_id);
    if (nf_instance && nf_instance->nf_type == OpenAPI_nf_type_AMF) {
        ogs_sbi_discovery_option_set_target_nf_instance_id(discovery_option, request->amf_id);
    }

send:
	rv = lmf_amf_sbi_discover_and_send(OGS_SBI_SERVICE_TYPE_NAMF_COMM, discovery_option, (ogs_sbi_request_t *(*)(lmf_sbi_params_t *, void *))lmf_namf_build_n1_message_transfer, &sbi_params, &params);

	/* Start corresponding timer if provided */
    if(rv == OGS_OK)
    {
        switch(timer_id)
        {
            /* Retransmission of last LPP message */
            case LMF_TIMER_LPP:
                ogs_timer_start(request->lpp_cp.timer, lmf_timer_cfg(timer_id)->duration);
                break;

            default:
                ogs_warn("[%s] Timer %s does not exist.", request->supi, lmf_timer_get_name(timer_id));
                break;
        }
    }

	return rv;
}
