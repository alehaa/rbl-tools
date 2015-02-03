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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <rbl.h>


int
main(int argc, char **argv)
{
	/*
	 * general config
	 */
	verbose_level_t verbose_level = ALL;

	const char *blacklist = "pbl.spamhaus.org";

	/*
	 * get comand line options
	 */
	int opt;
	while ((opt = getopt(argc, argv, "b:fq")) != -1) {
		switch (opt) {
			case 'b': blacklist = optarg; break;

			case 'f': verbose_level = LISTED; break;

			case 'q': verbose_level = QUIET; break;

			default: print_usage(); exit(EXIT_FAILURE);
		}
	}

	/*
	 * convert IP into reverse format
	 */
	if (optind >= argc) {
		fprintf(stderr, "Expected IP after options\n\n");
		print_usage();
		exit(EXIT_FAILURE);
	}

	char ip[64];
	if (rbl_atoip(argv[optind], ip) != 0) {
		fprintf(stderr, "IP is invalid\n");
		exit(EXIT_FAILURE);
	}


	/*
	 * lookup IP in rbl
	 */
	printf("%s: ", blacklist);
	switch (rbl_lookup(ip, blacklist, NULL)) {
		case 1:
			if (verbose_level != QUIET)
				printf("blocked\n");

			break;

		case 0:
			if (verbose_level == ALL)
				printf("not blocked\n");

		default:
			if (verbose_level != QUIET)
				printf("an error occued\n");
	}


	// exit normal
	return 0;
}
