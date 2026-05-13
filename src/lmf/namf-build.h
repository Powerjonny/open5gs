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

#ifndef LMF_NAMF_BUILD_H
#define LMF_NAMF_BUILD_H

#include "ogs-sbi.h"
#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lmf_subscribe_params_s
{
	OpenAPI_n1_message_class_e n1;
	OpenAPI_n2_information_class_e n2;
} lmf_subscribe_params_t;

typedef struct lmf_n1n2_message_params_s
{
	struct {
		OpenAPI_n1_message_class_e type;
		ogs_pkbuf_t *pkbuf;
	} n1;

	struct {
		OpenAPI_n2_information_class_e type;
		ogs_pkbuf_t *pkbuf;
	} n2;
} lmf_n1n2_message_params_t;

ogs_sbi_request_t *lmf_namf_build_n1n2_message_subscribe(
        lmf_location_request_t *location_request, void *data);
ogs_sbi_request_t *lmf_namf_build_n1n2_message_unsubscribe(
        lmf_location_request_t *location_request, void *data);
ogs_sbi_request_t *lmf_namf_build_n1_message_transfer(
		lmf_location_request_t *location_request, void *data);

#ifdef __cplusplus
}
#endif

#endif /* LMF_NAMF_BUILD_H */
