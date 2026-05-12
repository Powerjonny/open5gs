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

#ifndef OGS_UPP_H
#define OGS_UPP_H

#include "core/ogs-core.h"

#define OGS_UPP_INSIDE

#include "upp/types.h"
#include "upp/message.h"
#include "upp/encoder.h"
#include "upp/decoder.h"

#undef OGS_UPP_INSIDE

#ifdef __cplusplus
extern "C" {
#endif

extern int __ogs_upp_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __ogs_upp_domain

#ifdef __cplusplus
}
#endif

#endif /* OGS_UPP_H */
