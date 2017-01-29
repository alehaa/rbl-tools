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
#include <string.h>

#include <resolv.h>


/** \brief Lookup TXT record for \p ip in DNSBL \p rbl_domain.
 *
 * \details Many DNSBL provide additional information about the blocking like a
 *  link in the TXT record. This function will lookup the TXT record and write
 *  its content to \p dest.
 *
 * \note If the used DNSBL provides a TXT record for all matching IPs, there is
 *  no need to call \ref rbl_lookup before. A call to this function is
 *  sufficient and will return the same result.
 *
 *
 * \param ip The IP to lookup, reverse formatted by \ref rbl_atoip.
 * \param rbl_domain The domain of the RBL to be checked.
 * \param [out] dest Where to store the data of the TXT record.
 * \param num Size of \p dest.
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
rbl_lookup_txt(const rbl_revip *ip, const char *rbl_domain, char *dest,
               const size_t num)
{
	/* Check the required parameters for valid values. All parameters are
	 * mandatory and MUST NOT be null. */
	assert(ip);
	assert(rbl_domain);
	assert(dest);
	assert(num);


	/* Fire a new DNS query for the IP in the DNSBL. The domain to be queried is
	 * the reverse formatted IP concatenated with the DNSBL domain. If the
	 * domain has no TXT record or an error occured, an failure / error code
	 * will be returned. */
	unsigned char response[NS_PACKETSZ];
	int response_len = res_querydomain(ip->r_ip, rbl_domain, ns_c_in, ns_t_txt,
	                                   response, NS_PACKETSZ);

	if (response_len < 0)
		/* The IP was not found in the DNSBL. */
		return 0;
	else if (response_len == NS_PACKETSZ)
		/* An error occured. */
		return -1;


	/* Parse the data in the TXT resource record. Only the first string in the
	 * first found TXT record will be examined. As described in RFC1035 and in
	 * http://stackoverflow.com/a/11658242 the first byte has to be ignored. */
	ns_msg handle;
	if (ns_initparse(response, response_len, &handle) == 0) {
		ns_rr rr;
		if (ns_parserr(&handle, ns_s_an, 0, &rr) == 0) {
			strncpy(dest, (char *)ns_rr_rdata(rr) + 1, num);
			dest[num - 1] = '\0';
			return 1;
		}
	}

	/* An error occured while parsing the resource record. */
	return -1;
}
