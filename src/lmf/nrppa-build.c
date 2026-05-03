/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
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

#include "nrppa-build.h"

ogs_pkbuf_t*
ogs_nrppa_build_trp_information_request(void)
{
	NRPPA_NRPPA_PDU_t pdu;
	NRPPA_InitiatingMessage_t *initiatingMessage = NULL;
	NRPPA_TRPInformationRequest_t *trp = NULL;
	NRPPA_TRPInformationRequest_IEs_t *ie = NULL;
	NRPPA_TRPInformationTypeItemTRPReq_t *item = NULL;

	ogs_debug("TRPInformationRequest");

	memset(&pdu, 0, sizeof (NRPPA_NRPPA_PDU_t));
	pdu.present = NRPPA_NRPPA_PDU_PR_initiatingMessage;
	pdu.choice.initiatingMessage = CALLOC(1, sizeof(NRPPA_InitiatingMessage_t));

	initiatingMessage = pdu.choice.initiatingMessage;
	initiatingMessage->procedureCode = NRPPA_ProcedureCode_id_tRPInformationExchange;
	initiatingMessage->criticality = NRPPA_Criticality_reject;
	initiatingMessage->value.present = NRPPA_InitiatingMessage__value_PR_TRPInformationRequest;

	trp = &initiatingMessage->value.choice.TRPInformationRequest;

	/*
	 * TRPInformationTypeList IE
	 */
	ie = CALLOC(1, sizeof(NRPPA_TRPInformationRequest_IEs_t));
	ASN_SEQUENCE_ADD(&trp->protocolIEs, ie);

	ie->id = NRPPA_ProtocolIE_ID_id_TRPInformationTypeListTRPReq;
	ie->criticality = NRPPA_Criticality_reject;
	ie->value.present = NRPPA_TRPInformationRequest_IEs__value_PR_TRPInformationTypeListTRPReq;

	/*
	 * Currently, only one item: On-Demand PRS Information
	 */
	item = CALLOC(1, sizeof(NRPPA_TRPInformationTypeItemTRPReq_t));
	ASN_SEQUENCE_ADD(&ie->value.choice.TRPInformationTypeListTRPReq, item);

	item->id = NRPPA_ProtocolIE_ID_id_TRPInformationTypeItem;
        item->criticality = NRPPA_Criticality_reject;
        item->value.present = NRPPA_TRPInformationTypeItemTRPReq__value_PR_TRPInformationTypeItem;
	item->value.choice.TRPInformationTypeItem = NRPPA_TRPInformationTypeItem_ondemandPRSInfo;

	return ogs_nrppa_encode(&pdu);
}

ogs_pkbuf_t*
ogs_nrppa_build_prs_configuration_request(bool configure)
{
	NRPPA_NRPPA_PDU_t pdu;
        NRPPA_InitiatingMessage_t *initiatingMessage = NULL;
	NRPPA_PRSConfigurationRequest_t *prs = NULL;
	NRPPA_PRSConfigurationRequest_IEs_t *ie = NULL, *ie2 = NULL;

	ogs_debug("PRSConfigurationRequest");

        memset(&pdu, 0, sizeof (NRPPA_NRPPA_PDU_t));
        pdu.present = NRPPA_NRPPA_PDU_PR_initiatingMessage;
        pdu.choice.initiatingMessage = CALLOC(1, sizeof(NRPPA_InitiatingMessage_t));

        initiatingMessage = pdu.choice.initiatingMessage;
        initiatingMessage->procedureCode = NRPPA_ProcedureCode_id_pRSConfigurationExchange;
        initiatingMessage->criticality = NRPPA_Criticality_reject;
        initiatingMessage->value.present = NRPPA_InitiatingMessage__value_PR_PRSConfigurationRequest;

	prs = &initiatingMessage->value.choice.PRSConfigurationRequest;

	/*
	 * PRSConfigurationRequest IE with 2 items
	 */
	ie = CALLOC(1, sizeof(NRPPA_PRSConfigurationRequest_IEs_t));
        ASN_SEQUENCE_ADD(&prs->protocolIEs, ie);
	ie2 = CALLOC(1, sizeof(NRPPA_PRSConfigurationRequest_IEs_t));
	ASN_SEQUENCE_ADD(&prs->protocolIEs, ie2);

	ie->id = NRPPA_ProtocolIE_ID_id_PRSConfigRequestType;
        ie->criticality = NRPPA_Criticality_reject;
        ie->value.present = NRPPA_PRSConfigurationRequest_IEs__value_PR_PRSConfigRequestType;

	ie2->id = NRPPA_ProtocolIE_ID_id_PRSTRPList;
	ie2->criticality = NRPPA_Criticality_ignore;
	ie2->value.present = NRPPA_PRSConfigurationRequest_IEs__value_PR_PRSTRPList;

	/*
	 * PRS transmission change: configure or turning off
	 */
	if(configure)
	{
		ie->value.choice.PRSConfigRequestType = NRPPA_PRSConfigRequestType_configure;
		//TODO: continue here ~> TS 38.455, 9.2.61 + change function signature if needed
	}
	else
	{
		ie->value.choice.PRSConfigRequestType = NRPPA_PRSConfigRequestType_off;
		//TODO: continue here ~> TS 38.455, 9.2.64 + ...
	}

	return ogs_nrppa_encode(&pdu);
}
