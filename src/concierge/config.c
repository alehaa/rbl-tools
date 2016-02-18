/* This file is part of rbl-tools.
 *
 * rbl-tools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Copyright (C)
 *  2015-2016 Alexander Haase <alexander.haase@rwth-aachen.de>
 */

#include "config.h"

#include <stdlib.h> // atoi

#include <argp.h>


// Informative data for ARGP.
const char *argp_program_bug_address =
    "https://github.com/alehaa/rbl-tools/issues";

static char doc[] = "concierge -- realtime blacklist nfqueues handler";


static struct argp_option options[] = {
    {"verbose", 'v', 0, 0,
     "Produce verbose output. Use multiple times to increase verbosity."},
    {"blacklist", 'b', "domain", 0,
     "DNS blacklist domain to check IPs against."},
    {"queue-num", 'q', "num", 0, "NFQUEUE to use."},
    {0}};


static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we know is a pointer to our
	 * arguments structure. */
	struct concierge_config *config = state->input;

	switch (key) {
		case 'v':
			config->verbose_level = (config->verbose_level << 1) + 1;
			break;

		case 'b': config->blacklist_domain = arg; break;
		case 'q': config->nfqueue_num = atoi(arg); break;

		default: return ARGP_ERR_UNKNOWN;
	}

	return 0;
}


static struct argp argp = {options, parse_opt, NULL, doc};

void
concierge_parse_config(int argc, char **argv, struct concierge_config *config)
{
	// Default values.
	config->verbose_level = 0;
	config->blacklist_domain = NULL;
	config->nfqueue_num = 0;

	argp_parse(&argp, argc, argv, 0, 0, config);
}
