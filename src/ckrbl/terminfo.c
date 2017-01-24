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


/* include header files
 */
#include "terminfo.h"

#include <sys/ioctl.h>


/** \brief Determine the width of the terminal
 *
 * \details Determines the width of the terminal via ioctl. The result will be
 *  saved in the global variable \ref terminal_width. This function should be
 *  called once at the beginning of \ref main.
 *
 *
 * \return On success zero is returned. On error, -1 is returned, and errno is
 *  set appropriately.
 */
void
get_term_width()
{
	struct winsize w;

	// get terminal width
	if (ioctl(0, TIOCGWINSZ, &w) != 0)
		terminal_width = 80;

	// save terminal size in global variable
	terminal_width = w.ws_col;
}
