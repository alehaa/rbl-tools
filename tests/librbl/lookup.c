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

/* Test case for rbl_lookup.
 *
 * This is a simple test case for tbl_lookup of librbl. The first two arguments
 * define the IP and blacklist to lookup. */

#include <stdio.h>
#include <stdlib.h>

#include <rbl.h>


int
main(int argc, char **argv)
{
	/* The first argument is required as IP, the second as blacklist domain. */
	if (argc < 3) {
		fprintf(stderr, "Usage: %s ip blacklist\n", argv[0]);
		return EXIT_FAILURE;
	}


	/* Check the IP and print the result to stdout. */
	int ret = rbl_lookup(argv[1], argv[2]);
	if (ret < 0)
		fprintf(stderr, "An error occured while looking IP up in rbl.\n");
	printf("%s is %slisted in %s.\n", argv[1], (ret == 0) ? "not " : "",
	       argv[2]);
}
