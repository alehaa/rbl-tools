# This file is part of rbl-tools.
#
# rbl-tools is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# rbl-tools is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see
#
#  http://www.gnu.org/licenses/
#
#
# Copyright (C)
#  2015-2017 Alexander Haase <ahaase@mksec.de>
#


#
# build shared library
#
add_library(rbl_shared SHARED
	atoip.c
	lookup.c
	lookup_txt.c
)

target_link_libraries(rbl_shared resolv)

set_target_properties(rbl_shared PROPERTIES
	VERSION 0.1
	SOVERSION 0
	OUTPUT_NAME rbl
)


#
# build static library
#
add_library(rbl_static STATIC
	atoip.c
	lookup.c
	lookup_txt.c
)

set_target_properties(rbl_static PROPERTIES
	OUTPUT_NAME rbl
)



#
# install libraries
#
install(TARGETS rbl_shared rbl_static
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)


#
# install header
#
install(FILES rbl.h DESTINATION include
)
