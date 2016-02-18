# This file is part of rbl-tools.
#
# rbl-tools is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see
#
# http://www.gnu.org/licenses/
#
#
# Copyright (C)
#   2015-2016 Alexander Haase <alexander.haase@rwth-aachen.de>
#

include(FindPackageHandleStandardArgs)

find_program(DOT_BIN NAMES dot)
mark_as_advanced(DOT)

find_package_handle_standard_args(GRAPHVIZ DEFAULT_MSG DOT)

if (GRAPHVIZ_FOUND)
	set(DOT_FOUND 1 CACHE INTERNAL "Wheter dot binary was found.")
endif ()
