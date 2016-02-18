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
# Idea was found on:
#   https://www.tty1.net/blog/2014/cmake-doxygen_en.html
#

# configuration
set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in")
set(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf")
set(doxy_output_root "${CMAKE_CURRENT_BINARY_DIR}")
set(doxy_html_index_file "${doxy_output_root}/html/index.html")


# add a target to generate documentation with Doxygen
option(ENABLE_DOCS "Create HTML based documentation" OFF)

if (NOT ENABLE_DOCS)
	return ()
endif ()


find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	return()
endif (NOT DOXYGEN_FOUND)

find_package(Graphviz)
set(DOXYGEN_HAVE_DOT "NO")
if (DOT_FOUND)
	set(DOXYGEN_HAVE_DOT "YES")
endif()


# configure doxyfile
configure_file(${doxyfile_in} ${doxyfile} @ONLY)

add_custom_command(OUTPUT ${doxy_html_index_file}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                   # The following should be ${doxyfile} only but it will break
                   # the dependency. The optimal solution would be creating a
                   # custom_command for ${doxyfile} generation.
                   MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
                   DEPENDS ckrbl concierge rbl_shared rbl_static
                   COMMENT "Generating documentation")

add_custom_target(doc ALL DEPENDS ${doxy_html_index_file})

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
	DESTINATION share/doc/rbl-tools)
