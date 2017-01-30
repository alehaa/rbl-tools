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

/* Test case for rbl_lookup_txt.
 *
 * This is a simple test case for tbl_lookup_a of librbl. The first two
 * arguments define the IP and blacklist to lookup. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rbl.h>


int
main(int argc, char **argv)
{
	/* The first argument is required as IP, the second as blacklist domain.
	 * Additional arguments are IPs to match in the A record. */
	if (argc < 3) {
		fprintf(stderr, "Usage: %s ip blacklist [match ...]\n", argv[0]);
		return EXIT_FAILURE;
	}


	/* Pass the first argument to rbl_atoip. If an error occured, print an error
	 * message to stderr and exit. */
	rbl_revip ip;
	if (rbl_atoip(argv[1], &ip) != 0) {
		fprintf(stderr, "IP not valid\n");
		return EXIT_FAILURE;
	}


	/* Lookup the IP in the DNSBL and print the result and TXT record. */
	char buffer[255];
	int ret = rbl_lookup_txt(&ip, argv[2], buffer, 255);

	/* Print the result. */
	if (ret < 0)
		fprintf(stderr, "An error occured while looking IP up in rbl.\n");
	else if (ret == 0)
		printf("%s is not listed in %s.\n", argv[1], argv[2]);
	else {
		printf("%s is listed in %s.\n", argv[1], argv[2]);

		char *p = strtok(buffer, "\n");
		while (p != NULL) {
			printf("TXT: %s\n", p);
			p = strtok(NULL, "\n");
		}
	}
}
