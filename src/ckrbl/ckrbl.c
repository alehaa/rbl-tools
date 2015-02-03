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
#include <stdio.h>
#include <rbl.h>


int
main(int argc, char **argv)
{
	char ip[64];
	rbl_atoip(argv[1], ip);


	int i = rbl_lookup(ip, argv[2], NULL);

	if (i == 1)
		printf("blocked\n");
	else if (i == 0)
		printf("not blocked\n");
	else
		printf("an error occured\n");

	return 0;
}
