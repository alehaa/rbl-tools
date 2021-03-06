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
#include <resolv.h>


/** \brief Lookup \p ip in \p rbl_domain and return the result.
 *
 * \details This function does a DNSBL-lookup for \p ip in \p rbl_domain. If
 *  \p desc is not NULL, the TXT record will be looked up and stored in the
 *  buffer if it is avivable. This is only usefull for software that is used
 *  interacive.
 *
 *
 * \param ip The IP to lookup, reverse formatted by \ref rbl_atoip.
 * \param rbl_domain The domain of the RBL to be checked.
 * \param match An optional array of IPs, the A resource record of the DNSBL is
 *  required to match for returning a positive result as 'listed'. The array has
 *  to be terminated by zero.
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
rbl_lookup_a(rbl_revip *ip, const char *rbl_domain, const in_addr_t *match)
{
	/* Check the required parameters for valid values. All parameters are
	 * mandatory and MUST NOT be null. */
	assert(ip);
	assert(rbl_domain);


	/* Fire a new DNS query for the IP in the DNSBL. The domain to be queried is
	 * the reverse formatted IP concatenated with the DNSBL domain. If the
	 * domain has no TXT record or an error occured, an failure / error code
	 * will be returned. */
	unsigned char response[NS_PACKETSZ];
	int response_len = res_querydomain(ip->r_ip, rbl_domain, ns_c_in, ns_t_a,
	                                   response, NS_PACKETSZ);

	if (match == NULL || (response_len < 0 || response_len == NS_PACKETSZ))
		/* First check for an error, then check if an A resource record was
		 * found or not. */
		return (response_len == NS_PACKETSZ) ? -1 : (response_len < 0) ? 0 : 1;


	/* If the match parameter is not empty and an A resource record was found,
	 * check the IP of the A resource record with the IPs to be matched. Only if
	 * these match return a positive match. */
	ns_msg handle;
	if (ns_initparse(response, response_len, &handle) == 0) {
		uint16_t n = ns_msg_count(handle, ns_s_an);
		do {
			ns_rr rr;
			if (ns_parserr(&handle, ns_s_an, n - 1, &rr) == 0) {
				/* Convert the DNS response data to an IPv4 (as 32 bit integer
				 * aka in_addr_t). */
				in_addr_t rr_a = ns_get32(ns_rr_rdata(rr));

				/* Iterate over the match array and check for matches. If the
				 * IPs match, a found result will be returned. */
				in_addr_t *iter;
				for (iter = (in_addr_t *)match; *iter; iter++)
					if (*iter == rr_a)
						return 1;
			}
		} while (--n);
	}

	/* The IP was listet in the DNSBL, but the returned A record did not match
	 * the IPs required to be matched. */
	return 0;
}
