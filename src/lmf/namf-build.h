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
#include "sbi-path.h"

#ifdef __cplusplus
extern "C" {
#endif

ogs_sbi_request_t *lmf_namf_build_n1n2_message_subscribe(
        lmf_sbi_params_t *params, void *data);
ogs_sbi_request_t *lmf_namf_build_n1n2_message_unsubscribe(
        lmf_sbi_params_t *params, void *data);
ogs_sbi_request_t *lmf_namf_build_n1_message_transfer(
		lmf_sbi_params_t *params, void *data);
ogs_sbi_request_t *lmf_namf_build_lcsup_notification(
		lmf_lcs_up_context_t *context, const char *target_lmf);
#ifdef __cplusplus
}
#endif

#endif /* LMF_NAMF_BUILD_H */
