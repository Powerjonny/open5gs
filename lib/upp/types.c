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

#include "ogs-upp.h"

int ogs_upp_lookup_lcs_up_address(ogs_upp_cm_lcs_up_address_t *address, int port)
{
	int rv, family;
	ogs_sockaddr_t *addr = NULL;

	ogs_assert(address);

	/* Determine IP family */
	switch(address->type)
	{
		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4:
			family = AF_INET;
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV6:
			family = AF_INET6;
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_IPV4V6:
			family = AF_UNSPEC;
			break;

		case UPP_CM_LMF_LCS_UP_ADDRESS_TYPE_FQDN:
			ogs_warn("Lookup of network interface for FQDN is not neccessary.");
			return OGS_OK;

		default:
			ogs_warn("Unknown address type (0x%.2x)", address->type);
			return OGS_ERROR;
	}

	/* Lookup suitable network interface address */
	rv = ogs_getaddrinfo(&addr, family, NULL, port, 0);
	if(rv != OGS_OK || !addr)
	{
		return OGS_ERROR;
	}

	/* Copy request address to target IE */
	switch(family)
	{
		case AF_INET:
			memcpy(address->address, &addr->sin.sin_addr.s_addr, 4);
			ogs_info("LMF LCS-UP IPv4 address: %s", inet_ntoa(addr->sin.sin_addr));
			address->length = 5;
			break;

		case AF_INET6:
			memcpy(address->address, addr->sin6.sin6_addr.s6_addr, 16);
			address->length = 17;
			break;

		case AF_UNSPEC:
			ogs_warn("Lookup of IPv4 and IPv6 is currently not implemented.");
			ogs_freeaddrinfo(addr);
			return OGS_ERROR;

		default:
			break;
	}

	/* Free allocated address */
	ogs_freeaddrinfo(addr);

	return OGS_OK;
}
