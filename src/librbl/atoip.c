/* This file is part of rbl-tools.
 *
 * rbl-tools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * rbl-tools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see
 *
 *  http://www.gnu.org/licenses/
 *
 *
 * Copyright (C)
 *  2015-2017 Alexander Haase <ahaase@mksec.de>
 */

#include "rbl.h"

#include <assert.h>
#include <stdio.h>

#include <arpa/inet.h>


/** \brief Convert IPv4 \p addr into reverse notation.
 *
 * \details This function convertes the IP (v4) in \p addr from the A.B.C.D
 *  format to the reverse notation format D.C.B.A.
 *
 *
 * \param addr The IP to be converted.
 * \param [out] dest Pointer where to store the reverse noted IP.
 *
 * \return On success zero will be returned, otherwise -1.
 */
static int
rbl_convert_ipv4(const in_addr_t *addr, rbl_revip *dest)
{
	/* This solution was found at stack overflow and is licensed under the MIT
	 * license. The solution can be found at:
	 *
	 *   http://stackoverflow.com/a/16373300
	 */
	in_addr_t reverse =
	    ((*addr & 0xff000000) >> 24) | ((*addr & 0x00ff0000) >> 8) |
	    ((*addr & 0x0000ff00) << 8) | ((*addr & 0x000000ff) << 24);

	return (inet_ntop(AF_INET, &reverse, dest->r_ip, sizeof(dest->r_ip)) !=
	        NULL)
	           ? 0
	           : -1;
}


/** \brief Convert IPv6 in \p sa into reverse notation.
 *
 * \details This functions converts the IPv6 in \p sa from the ABCD:EFGH::
 *  format to the reverse notation .H.G.F.E.D.C.B.A. Shortened IPv6 address
 *  parts will be filled with zeros.
 *
 *
 * \param sa AF_INET6 socket address struct containing the IPv6 to convert.
 * \param [out] dest Pointer where to store the reverse noted IP.
 *
 * \return On success zero will be returned. An error code of -1 indicates that
 *  the memory of \p dest is not sufficient.
 */
static int
rbl_convert_ipv6(struct sockaddr_in6 *sa, rbl_revip *dest)
{
	/* This loop will concatenate all IPv6 octets in hexadecimal notation in
	 * reverse order. */
	int i, num;
	char *p = dest->r_ip;
	for (i = 15, num = sizeof(dest->r_ip); i >= 0; i--, p += 4, num -= 4)
		if (snprintf(p, num, "%x.%x%s",
		             (unsigned char)((sa->sin6_addr.s6_addr[i]) & 0xf),
		             (unsigned char)((sa->sin6_addr.s6_addr[i] >> 4)),
		             (i != 0) ? "." : "") > num)
			return -1;

	return 0;
}


/** \brief Converts \p src to an reverse noted ip string stored in \p dest.
 *
 * \details \p src will be examined, if it is a valid IPv4 or IPv6 address. If
 *  it is valid, it will be reformated and stored in \p dest and can be used by
 *  \ref rbl_lookup.
 *
 * \note \p dest should be 64 bytes long.
 *
 *
 * \param src String containing IP to be examined
 * \param [out] dest Pointer where to store the reverse noted IP.
 *
 * \return On success zero will be returned. On any error a non-zero value will
 *  be returned and errno set appropriately.
 */
int
rbl_atoip(const char *src, rbl_revip *dest)
{
	/* Check the required parameters for valid values. src and dest are both
	 * mandatory and MUST NOT be null. */
	assert(src);
	assert(dest);


	/* Try to convert src into a network address structure of either AF_INET or
	 * AF_INET6 address family. The static functions rbl_convert_ipv4 and _ipv6
	 * will then convert the IPs to the reverse notation. */
	in_addr_t addr;
	if (inet_pton(AF_INET, src, &addr) == 1)
		return rbl_convert_ipv4(&addr, dest);

	struct sockaddr_in6 sa6;
	if (inet_pton(AF_INET6, src, &(sa6.sin6_addr)) == 1)
		return rbl_convert_ipv6(&sa6, dest);


	/* The IP has no known IP format and can't be converted. */
	return -1;
}
