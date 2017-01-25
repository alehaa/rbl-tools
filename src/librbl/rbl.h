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

#ifndef LIBRBL_H
#define LIBRBL_H


#include <stddef.h>


/** \brief Datatyype for storing the reverse formatted IP.
 */
typedef struct rbl_revip
{
	char r_ip[64]; ///< The IP in reverse notation.
} rbl_revip;


int rbl_lookup(rbl_revip *ip, const char *rbl_domain, char *desc);
int rbl_atoip(const char *src, rbl_revip *dest);

int rbl_lookup_txt(const rbl_revip *ip, const char *rbl_domain, char *dest,
                   const size_t num);


#endif
