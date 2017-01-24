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
#include <stdio.h>

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/** \brief Converts \p src to an reverse noted ip string stored in \p dest.
 *
 * \details \p src will be examined, if it is a valid IPv4 or IPv6 address. If
 *  it is valid, it will be reformated and stored in \p dest and can be used by
 *  \ref rbl_lookup.
 *
 * \param src String containing IP to be examined
 * \param dest Destination buffer for reformated IP
 *
 * \return On success zero will be returned. On any error a non-zero value will
 *  be returned and errno set appropriately.
 *
 * \note \p dest should be 64 bytes long.
 */
int
rbl_atoip(const char *src, char *dest)
{
	// check, src or dest are NULL (must not be NULL)
	assert(src);
	assert(dest);


	// prepare hint
	struct addrinfo hint = {0};
	hint.ai_family = PF_UNSPEC;
	hint.ai_flags = AI_NUMERICHOST;


	// check if IP is valid
	struct addrinfo *res = NULL;

	if (getaddrinfo(src, NULL, &hint, &res))
		// address was invalid
		return -1;


	// is src an IPv4 or IPv6 address?
	int ret = 0;

	switch (res->ai_family) {
		case AF_INET: {
			// cast address
			struct sockaddr_in *in = (struct sockaddr_in *)res->ai_addr;

			// copy IP reverse into dest
			sprintf(dest, "%u.%u.%u.%u",
			        (unsigned int)((in->sin_addr.s_addr >> 24) & 0xff),
			        (unsigned int)((in->sin_addr.s_addr >> 16) & 0xff),
			        (unsigned int)((in->sin_addr.s_addr >> 8) & 0xff),
			        (unsigned int)((in->sin_addr.s_addr) & 0xff));

			break;
		}

		case AF_INET6: {
			// cast address
			struct sockaddr_in6 *in = (struct sockaddr_in6 *)res->ai_addr;

			// copy IP reverse into dest
			char *p = dest;

			ssize_t i;
			for (i = 15; i >= 0; i--) {
				// set writing schema
				char *schema = "%x.%x.";

				if (i == 0)
					schema = "%x.%x";

				// copy octet reverse into dest
				sprintf(p, schema,
				        (unsigned int)((in->sin6_addr.s6_addr[i]) & 0xf),
				        (unsigned int)((in->sin6_addr.s6_addr[i] >> 4)));

				// shift writing pointer
				if (i > 0)
					p += 4;
			}

			break;
		}

		default:
			// unknown address format
			ret = -1;
	}

	// free address info
	freeaddrinfo(res);

	return ret;
}
