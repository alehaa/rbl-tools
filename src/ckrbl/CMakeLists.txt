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

include(GNUInstallDirs)

find_package(codecov)
find_package(Sanitizers)


#
# configure headers
#
configure_file (config.h.in config.h)


#
# build ckrbl
#
add_executable(ckrbl
	ckrbl.c
	lookup.c
	lookup_file.c
	lookup_string.c
	usage.c
	terminfo.c
)

target_include_directories(ckrbl PUBLIC
	../librbl
	${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ckrbl
	rbl_shared
)

add_coverage(ckrbl)
add_sanitizers(ckrbl)


#
# install ckrbl
#
install(TARGETS ckrbl
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)
