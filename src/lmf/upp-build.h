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

#ifndef LMF_UPP_BUILD_H
#define LMF_UPP_BUILD_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

ogs_pkbuf_t *upp_build_connection_establishment_command(ogs_pool_id_t binding_id, ogs_upp_cm_lcs_up_address_t *address, ogs_upp_cm_lmf_routing_id_t *routing_id);

#ifdef __cplusplus
}
#endif

#endif /* LMF_UPP_BUILD_H */
