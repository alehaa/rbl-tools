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


/** \brief Shortcut function for \ref rbl_atoip and \ref rbl_lookup_a.
 *
 * \details This function may be used as shortcut for simply looking up \p ip in
 *  the DNSBL \p rbl_domain.
 *
 * \note It is recommended to not use this function, if \p ip is checked in
 *  multiple DNSBL, as the reverse notation of the IP will not be cached. In
 *  this case use \ref rbl_atoip and \ref rbl_lookup_a.
 *
 *
 * \param ip The IP to be looked up.
 * \param rbl_domain The domain of the RBL to be checked.
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
rbl_lookup(const char *ip, const char *rbl_domain)
{
	/* Convert the given IP to a reverse formatted one, as required for
	 * rbl_lookup_a. If this fails, an error will be returned. */
	rbl_revip buffer;
	if (rbl_atoip(ip, &buffer) != 0)
		return -1;

	/* Lookup the IP in the DNSBL domain. The A resource record will not be
	 * matched against a list of IPs and the result pass through. */
	return rbl_lookup_a(&buffer, rbl_domain, NULL);
}
