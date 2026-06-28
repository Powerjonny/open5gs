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

#include "lpp-build.h"

ogs_pkbuf_t*
lpp_build_request_capabilities_full(ogs_lpp_session_t *session, bool is_cp)
{
	LPP_LPP_Message_t pdu;
	LPP_LPP_TransactionID_t *transaction = NULL;
	LPP_LPP_MessageBody_t *body = NULL;
	LPP_RequestCapabilities_t *cap = NULL;
	LPP_RequestCapabilities_r9_IEs_t *ie = NULL;

	LPP_CommonIEsRequestCapabilities_t *common = NULL;
	LPP_A_GNSS_RequestCapabilities_t *gnss = NULL;

	ogs_assert(session);

	ogs_debug("RequestCapabilities");

	/* Initialize message header */
	memset(&pdu, 0, sizeof(LPP_LPP_Message_t));
	pdu.transactionID = CALLOC(1, sizeof(LPP_LPP_TransactionID_t));
	transaction = pdu.transactionID;

	/* Request Capabilities is a new transaction (procedure) */
	transaction->initiator = session->transaction.initiator = LPP_Initiator_locationServer;
	transaction->transactionNumber = ++session->transaction.transactionNumber;

	/* For control plane only: Assign sequence number and acknowledgment indicator */
	if(is_cp)
	{
		pdu.sequenceNumber = CALLOC(1, sizeof(LPP_SequenceNumber_t));
		*pdu.sequenceNumber = ++session->sqn_tx;
		pdu.acknowledgement = CALLOC(1, sizeof(LPP_Acknowledgement_t));
		pdu.acknowledgement->ackRequested = 1;
	}

	/* Initialize message body */
	pdu.lpp_MessageBody = CALLOC(1, sizeof(LPP_LPP_MessageBody_t));
	body = pdu.lpp_MessageBody;
	body->present = LPP_LPP_MessageBody_PR_c1;
	body->choice.c1 = CALLOC(1, sizeof(struct LPP_LPP_MessageBody__c1));
	body->choice.c1->present = LPP_LPP_MessageBody__c1_PR_requestCapabilities;
	body->choice.c1->choice.requestCapabilities = CALLOC(1, sizeof(LPP_RequestCapabilities_t));

	/* Initialize RequestCapabilities IE */
	cap = body->choice.c1->choice.requestCapabilities;
	cap->criticalExtensions.present = LPP_RequestCapabilities__criticalExtensions_PR_c1;
	cap->criticalExtensions.choice.c1 = CALLOC(1, sizeof(struct LPP_RequestCapabilities__criticalExtensions__c1));
	cap->criticalExtensions.choice.c1->present = LPP_RequestCapabilities__criticalExtensions__c1_PR_requestCapabilities_r9;
	cap->criticalExtensions.choice.c1->choice.requestCapabilities_r9 = CALLOC(1, sizeof(LPP_RequestCapabilities_r9_IEs_t));

	/* Initialize RequestCapabilities-r9 IE */
	ie = cap->criticalExtensions.choice.c1->choice.requestCapabilities_r9;
	ie->commonIEsRequestCapabilities = CALLOC(1, sizeof(LPP_CommonIEsRequestCapabilities_t));
	ie->a_gnss_RequestCapabilities = CALLOC(1, sizeof(LPP_A_GNSS_RequestCapabilities_t));
	ie->otdoa_RequestCapabilities = CALLOC(1, sizeof(LPP_OTDOA_RequestCapabilities_t));
	ie->ecid_RequestCapabilities = CALLOC(1, sizeof(LPP_ECID_RequestCapabilities_t));
	/* ie->epdu_RequestCapabilities = CALLOC(1, sizeof(LPP_EPDU_Sequence_t));  this is for external use */

	ie->ext1 = CALLOC(1, sizeof(struct LPP_RequestCapabilities_r9_IEs__ext1));
	ie->ext1->sensor_RequestCapabilities_r13 = CALLOC(1, sizeof(LPP_Sensor_RequestCapabilities_r13_t));
	ie->ext1->tbs_RequestCapabilities_r13 = CALLOC(1, sizeof(LPP_TBS_RequestCapabilities_r13_t));
	ie->ext1->wlan_RequestCapabilities_r13 = CALLOC(1, sizeof(LPP_WLAN_RequestCapabilities_r13_t));
	ie->ext1->bt_RequestCapabilities_r13 = CALLOC(1, sizeof(LPP_BT_RequestCapabilities_r13_t));

	ie->ext2 = CALLOC(1, sizeof(struct LPP_RequestCapabilities_r9_IEs__ext2));
	ie->ext2->nr_ECID_RequestCapabilities_r16 = CALLOC(1, sizeof(LPP_NR_ECID_RequestCapabilities_r16_t));
	ie->ext2->nr_Multi_RTT_RequestCapabilities_r16 = CALLOC(1, sizeof(LPP_NR_Multi_RTT_RequestCapabilities_r16_t));
	ie->ext2->nr_DL_AoD_RequestCapabilities_r16 = CALLOC(1, sizeof(LPP_NR_DL_AoD_RequestCapabilities_r16_t));
	ie->ext2->nr_DL_TDOA_RequestCapabilities_r16 = CALLOC(1, sizeof(LPP_NR_DL_TDOA_RequestCapabilities_r16_t));
	ie->ext2->nr_UL_RequestCapabilities_r16 = CALLOC(1, sizeof(LPP_NR_UL_RequestCapabilities_r16_t));

	/* CommonRequestCapabilities IE */
	common = ie->commonIEsRequestCapabilities;
	common->ext1 = CALLOC(1, sizeof(struct LPP_CommonIEsRequestCapabilities__ext1));
	common->ext1->lpp_message_segmentation_req_r14 = CALLOC(1, sizeof(BIT_STRING_t));
	common->ext1->lpp_message_segmentation_req_r14->buf = CALLOC(1, sizeof(uint8_t));
	common->ext1->lpp_message_segmentation_req_r14->size = sizeof(uint8_t);
	common->ext1->lpp_message_segmentation_req_r14->bits_unused = 6; /* no support for LPP message segmentation */

	common->ext2 = CALLOC(1, sizeof(struct LPP_CommonIEsRequestCapabilities__ext2));
	common->ext2->remoteUE_IndicationReq_r18 = CALLOC(1, sizeof(long));

	/* A-GNSS-RequestCapabilities IE */
	gnss = ie->a_gnss_RequestCapabilities;
	gnss->gnss_SupportListReq = 1;
	gnss->assistanceDataSupportListReq = 1;
	gnss->locationVelocityTypesReq = 1;

	return ogs_lpp_encode(&pdu);
}
