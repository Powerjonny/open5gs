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

#ifndef LMF_LPP_BUILD_H
#define LMF_LPP_BUILD_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

ogs_pkbuf_t* lpp_build_request_capabilities_full(ogs_lpp_session_t *session, bool is_cp);
ogs_pkbuf_t* lpp_build_acknowledgement_message(ogs_lpp_session_t *session);
ogs_pkbuf_t* lpp_build_error_message(ogs_lpp_session_t *session, long cause, bool is_cp);

#ifdef __cplusplus
}
#endif

#endif /* LMF_LPP_BUILD_H */
