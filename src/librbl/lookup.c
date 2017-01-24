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


/* include headers
 */
#include "rbl.h"

#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>


/** \brief Lookup \p ip in \p rbl_domain and return the result.
 *
 * \details This function does a DNSBL-lookup for \p ip in \p rbl_domain. If
 *  \p desc is not NULL, the TXT record will be looked up and stored in the
 *  buffer if it is avivable. This is only usefull for software that is used
 *  interacive.
 *
 * \param ip Reverse dotted IP (v4 or v6)
 * \param rbl_domain The RBL domain to be used
 * \param desc Buffer to store additional information about RBL entry
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
rbl_lookup(const char *ip, const char *rbl_domain, char *desc)
{
	// check, if ip or rbl_domain are NULL (must not be NULL)
	assert(ip);
	assert(rbl_domain);


	// construct rbl lookup domain
	char rbl_lookup_domain[strlen(ip) + strlen(rbl_domain) + 2];
	sprintf(rbl_lookup_domain, "%s.%s", ip, rbl_domain);


	// lookup rbl
	struct hostent *he = gethostbyname(rbl_lookup_domain);

	if (he != NULL)
		// ip is on blacklist
		return 1;

	else if (h_errno == HOST_NOT_FOUND)
		// ip is not on blacklist
		return 0;

	else
		// an error occured
		return -1;
}
