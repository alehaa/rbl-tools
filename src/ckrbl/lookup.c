/* This file is part of rbl-tools.
 *
 * rbl-tools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Copyright (C)
 *  2015 Alexander Haase <alexander.haase@rwth-aachen.de>
 */


/* include headers
 */
#include "ckrbl.h"

#include <rbl.h>

#include "terminfo.h"


/* color definitions
 */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"


/** \brief Lookup \p IP in \p rbl_domain and print out the result.
 *
 *
 * \param ip Reverse dotted IP (v4 or v6)
 * \param rbl_domain The RBL domain to be used
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
lookup(const char *ip, const char *rbl_domain)
{
	// do the rbl lookup
	int ret = rbl_lookup(ip, rbl_domain, NULL);

	// evaluate rbl lookup
	char *color = ANSI_COLOR_RED;
	char *status = "LISTED";

	switch (ret) {
		case 0:
			color = ANSI_COLOR_GREEN;
			status = "  OK  ";
			break;

		case 1: break;

		case -1:
		default:
			color = ANSI_COLOR_YELLOW;
			status = "UNKNOW";
			break;
	}

	// print lookup result
	printf("%-*s [%s%s%s] \n", terminal_width - 10, rbl_domain, color, status,
	       ANSI_COLOR_RESET);

	// return result
	return ret;
}
