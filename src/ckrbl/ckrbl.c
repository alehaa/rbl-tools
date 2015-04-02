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

#include "config.h"
#include "terminfo.h"


int
main(int argc, char **argv)
{
	/* get terminal information
	 */
	get_term_width();


	/* get comand line options
	 */
	verbose_level = ALL;
	char *blacklists = NULL;
	const char *blacklist_file = NULL;
	int opt;

	while ((opt = getopt(argc, argv, "b:B:hlq")) != -1) {
		switch (opt) {
			case 'b': blacklists = optarg; break;

			case 'B': blacklist_file = optarg; break;

			case 'l': verbose_level = LISTED; break;

			case 'q': verbose_level = QUIET; break;

			case 'h': print_usage(stdout); exit(EXIT_SUCCESS);

			default: print_usage(stderr); exit(EXIT_FAILURE);
		}
	}


	/* convert IP into reverse format
	 */
	if (optind >= argc) {
		fprintf(stderr, "Expected IP after options\n\n");
		print_usage(stderr);
		exit(EXIT_FAILURE);
	}

	char ip[64];

	if (rbl_atoip(argv[optind], ip) != 0) {
		fprintf(stderr, "IP is invalid\n");
		exit(EXIT_FAILURE);
	}


	/* check IP against blacklists
	 */
	int ret = 0;

	// check manual set blacklists
	if (blacklists != NULL)
		ret = lookup_string(ip, blacklists);

	else {
		if (blacklist_file == NULL)
			blacklist_file = DEFAULT_BLACKLIST_FILE;

		ret = lookup_file(ip, blacklist_file);
		if (ret < 0)
			fprintf(stderr, "Unable to read file: '%s'\n", blacklist_file);
	}


	/* set exit code
	 */
	switch (ret) {
		case 0: return 0;

		case 1: return 255;

		case -1:
		default: return 1;
	}
}
