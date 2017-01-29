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

include(easylib)
include(rbl_doc)


# Install the public man pages for this object.
rbl_add_man(rbl_lookup rbl_atoip)
rbl_add_man(rbl_lookup rbl_lookup_a)
rbl_add_man(rbl_lookup rbl_lookup_txt)


# Build library
#
easy_add_library(rbl
	atoip.c
	lookup.c
	lookup_a.c
	lookup_txt.c)

target_link_libraries(rbl_shared resolv)

set_target_properties(rbl_shared PROPERTIES
	VERSION "${RBL_MAJOR_VERSION}.${RBL_MINOR_VERSION}.${RBL_PATCH_VERSION}"
	SOVERSION ${RBL_MAJOR_VERSION})


# Install libraries and header.
#
install(TARGETS rbl_shared rbl_static
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(FILES rbl.h DESTINATION include)
