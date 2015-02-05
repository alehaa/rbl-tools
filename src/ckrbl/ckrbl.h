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


#ifndef CKRBL_H
#define CKRBL_H


/* include headers
 */
#include <stdio.h>


/* enums
 */
typedef enum { ALL, LISTED, QUIET } verbose_level_t;


/* global variables
 */
verbose_level_t verbose_level;


/* function declarations
 */
void print_usage(FILE *stream);
int lookup(const char *ip, const char *rbl_domain);
int lookup_string(const char *ip, char *blacklists);


#endif // CKRBL_H
