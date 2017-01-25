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

/* Test case for rbl_atoip.
 *
 * This is a simple test case for rbl_atoip of librbl. The first argument of
 * this executable will be passed to rbl_atoip and - if no error occured - the
 * reversed IP printed on stdout, so CTest may check the output. */

#include <stdio.h>
#include <stdlib.h>

#include <rbl.h>


int
main(int argc, char **argv)
{
	/* The first argument is required as IP. */
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [ip]\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Pass the first argument to rbl_atoip. If no error occured print the
	 * result to stdout, otherwise an error message. */
	rbl_revip ip;

	if (rbl_atoip(argv[1], &ip) != 0) {
		printf("IP not valid\n");
		return EXIT_FAILURE;
	} else
		printf("%s\n", ip.r_ip);
}
