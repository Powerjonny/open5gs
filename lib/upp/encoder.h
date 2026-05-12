/*
 * Copyright (C) 2026 by Nico Kalis <nico.kalis@uni-rostock.de>
 *
 * This file is part of Open5GS.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#if !defined(OGS_UPP_INSIDE) && !defined(OGS_UPP_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_UPP_ENCODER_H
#define OGS_UPP_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

int ogs_upp_encode_downlink_lcs_transport(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);
int ogs_upp_encode_connection_establishment_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);
int ogs_upp_encode_connection_establishment_reject(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);
int ogs_upp_encode_connection_release_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);
int ogs_upp_encode_connection_modification_command(ogs_pkbuf_t *pkbuf, ogs_upp_message_t *message);

#ifdef __cplusplus
}
#endif

#endif /* OGS_UPP_ENCODER_H */
