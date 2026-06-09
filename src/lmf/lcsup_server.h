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

#ifndef LMF_LCS_UP_SERVER_H
#define LMF_LCS_UP_SERVER_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lmf_poll_handle_s
{
	ogs_lnode_t lnode;

	ogs_poll_t *handle;
	ogs_sock_t *sock;
} lmf_poll_handle_t;

/* Helper structure to pass multiple parameters to a callback function */
typedef struct lmf_binding_params_s
{
    ogs_sock_t *sock;
    WOLFSSL *ssl;
	lmf_lcs_up_base_e base;
} lmf_binding_params_t;

void lmf_lcs_up_server_loop(void *data);

#ifdef __cplusplus
}
#endif

#endif /* LMF_LCS_UP_SERVER_H */
