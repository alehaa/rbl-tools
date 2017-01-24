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
#include "ckrbl.h"

#include <string.h>


/** \brief Check \p ip against any blacklist in \p blacklists.
 *
 *
 * \param ip Reverse dotted IP (v4 or v6)
 * \param blacklists List of blacklist domains. May be separated by comma,
 *  semicolon or space.
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
lookup_string(const char *ip, char *blacklists)
{
	int ret = 0;

	/* split blacklists if containing more than one blacklist and lookup IP in
	 * every blacklist.
	 */
	char delimiter[] = ",; ";
	char *blacklist = strtok(blacklists, delimiter);

	for (; blacklist; blacklist = strtok(NULL, delimiter)) {
		// set ret to -1, if IP is listed on any blacklist
		if (lookup(ip, blacklist) != 0)
			ret = 1;
	}

	return ret;
}
