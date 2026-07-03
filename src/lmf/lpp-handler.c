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

#include "lpp-handler.h"

int
lmf_handle_provide_capabilities_message(ogs_lpp_message_t *message, lmf_location_request_t *location_request)
{
	ogs_assert(message);
	ogs_assert(location_request);

	/*
	 * NOTE: Currently, we only store the requested capabilities.
	 * TODO: In future, we select the target positioning method depending on the UE's capabilities.
	 */
	if(!message->lpp_MessageBody->choice.c1->choice.provideCapabilities ||
	   !message->lpp_MessageBody->choice.c1->choice.provideCapabilities->criticalExtensions.choice.c1 ||
	   message->lpp_MessageBody->choice.c1->choice.provideCapabilities->criticalExtensions.present != LPP_ProvideCapabilities__criticalExtensions_PR_c1 ||
	   message->lpp_MessageBody->choice.c1->choice.provideCapabilities->criticalExtensions.choice.c1->present != LPP_ProvideCapabilities__criticalExtensions__c1_PR_provideCapabilities_r9 ||
	   !message->lpp_MessageBody->choice.c1->choice.provideCapabilities->criticalExtensions.choice.c1->choice.provideCapabilities_r9)
	{
		ogs_error("[%s] Provided Capabilities not included/invalid.", location_request->supi);
		return OGS_ERROR;
	}

	if(location_request->lpp.capabilities)
	{
		ogs_asn_free((void*) &asn_DEF_LPP_ProvideCapabilities_r9_IEs, (void*)location_request->lpp.capabilities);
		ogs_warn("[%s] New capabilities received. Replacing existing capabilities.", location_request->supi);
	}
	location_request->lpp.capabilities = message->lpp_MessageBody->choice.c1->choice.provideCapabilities->criticalExtensions.choice.c1->choice.provideCapabilities_r9;

	return OGS_OK;
}
