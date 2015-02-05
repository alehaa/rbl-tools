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


/** \brief Print usage for this application.
 *
 *
 * \return This function returns no value.
 */
void
print_usage(FILE *stream)
{
	fprintf(stream, "Usage: ckrbl [options] IP\n\n");
	fprintf(stream, "Avivable options:\n");
	fprintf(stream, "  -b\tBlacklists that IP should be checked against.\n\n");
	fprintf(stream, "  -f\tPrint only blacklists, where IP is matched.\n\n");
	fprintf(stream, "  -h\tPrint this help\n\n");
	fprintf(stream, "  -q\tPrint nothing.\n\n");
}
