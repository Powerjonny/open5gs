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

#include <sys/types.h>
#include <ifaddrs.h>

int ogs_get_address_by_interface_name(const char *name, ogs_sockaddr_t *addr, int family)
{
	struct ifaddrs *ifaddr, *ifa;
	bool is_unspec = false;

	ogs_assert(addr);
	ogs_assert(name);

	if(family != AF_INET && family != AF_INET6)
	{
		if(family == AF_UNSPEC)
		{
			is_unspec = true;
		}

		else
		{
			ogs_error("Unknown family identifier during interface address lockup.");
			return OGS_ERROR;
		}
	}

	/* Determine address structures depending on interface name */
	if(getifaddrs(&ifaddr) < 0)
	{
		ogs_error("getifaddrs failed");
		return OGS_ERROR;
	}

	/* Loop over result(s) */
	for(ifa = ifaddr; ifa; ifa = ifa->ifa_next)
	{
		/* Case I: Address family is not important (IPv4 or IPv6) */
		if(is_unspec)
		{
			if(strcmp(name, ifa->ifa_name) == 0)
			{
				memcpy(&addr->sa, ifa->ifa_addr, sizeof(struct sockaddr));
				freeifaddrs(ifaddr);
				return OGS_OK;
			}
		}

		/* Case II: Address family is important */
		else
		{
			if(strcmp(name, ifa->ifa_name) == 0 && ifa->ifa_addr->sa_family == family)
			{
				memcpy(&addr->sa, ifa->ifa_addr, sizeof(struct sockaddr));
                freeifaddrs(ifaddr);
                return OGS_OK;
			}
		}
	}

	freeifaddrs(ifaddr);

	return OGS_ERROR;
}

int ogs_upp_lookup_lcs_up_address(ogs_upp_cm_lcs_up_address_t *address, int port)
{
	int rv, family;
	ogs_sockaddr_t addr;

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
	rv = ogs_get_address_by_interface_name("eth0", &addr, family); //TODO: set iface name via config file in future!

	if(rv != OGS_OK)
	{
		return OGS_ERROR;
	}

	/* Copy request address to target IE */
	switch(addr.sa.sa_family)
	{
		case AF_INET:
			memcpy(address->address, &addr.sin.sin_addr.s_addr, 4);
			ogs_info("LMF LCS-UP IPv4 address: %s", inet_ntoa(addr.sin.sin_addr));
			address->length = 5;
			break;

		case AF_INET6:
			memcpy(address->address, addr.sin6.sin6_addr.s6_addr, 16);
			address->length = 17;
			break;

		case AF_UNSPEC:
			ogs_warn("Found network interface can not be of family type AF_UNSPEC!");
			return OGS_ERROR;

		default:
			break;
	}

	return OGS_OK;
}
