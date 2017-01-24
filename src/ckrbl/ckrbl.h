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


#ifndef CKRBL_H
#define CKRBL_H


/* include headers
 */
#include <stdio.h>

#include <rbl.h>


/* enums
 */
typedef enum { ALL, LISTED, QUIET } verbose_level_t;


/* global variables
 */
verbose_level_t verbose_level;


/* function declarations
 */
void print_usage(FILE *stream);
int lookup(rbl_revip *ip, const char *rbl_domain);
int lookup_string(rbl_revip *ip, char *blacklists);
int lookup_file(rbl_revip *ip, const char *blacklist_file);


#endif // CKRBL_H
