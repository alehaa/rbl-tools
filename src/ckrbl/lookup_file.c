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

#include <stdio.h>


/** \brief Check \p ip against any blacklist in file \p blacklist_file.
 *
 *
 * \param ip Reverse dotted IP (v4 or v6)
 * \param blacklist_file File containing a list of blacklist domains
 *
 * \return Returns positive value, if \p ip is listed in \p rbl_domain or zero
 *  if it is not listed. On error a negative value will be returned.
 */
int
lookup_file(const char *ip, const char *blacklist_file)
{
	int ret = 0;

	// try to open file
	FILE *fs;
	fs = fopen(blacklist_file, "r");

	if (fs == NULL)
		return -1;


	// read file line by line
	char *buffer = NULL;
	size_t len = 0;

	while ((getline(&buffer, &len, fs)) != -1) {
		char *p = buffer;

		// skip leeding spaces and tabs
		while (*p == ' ' || *p == '\t')
			p++;

		// is line a comment or a blank line?
		if (*p == '#' || *p == '\n')
			continue;

		// replace comments, spaces and newlines after blacklist domain
		for (char *q = p; *p + 1; q++) {
			if (*q == ' ' || *q == '#' || *q == '\n' || *q == '\t') {
				*q = '\0';
				break;
			}
		}

		// check IP in blacklist
		if (lookup(ip, p) != 0)
			ret = 1;
	}

	return ret;
}
