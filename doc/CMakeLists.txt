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
include(rbl_doc)


set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in")
set(doxy_output_root "${CMAKE_CURRENT_BINARY_DIR}")
set(doxy_html_index_file "${doxy_output_root}/html/index.html")

if (BUILD_DOC OR BUILD_DOC_INTERNAL)
	find_package(Doxygen REQUIRED)

	if (NOT DOXYGEN_DOT_EXECUTABLE)
		set(DOXYGEN_DOT_EXECUTABLE "")
	endif ()

	set(DOXYGEN_DOC_INTERNAL "NO")
	if (BUILD_DOC_INTERNAL)
		set(DOXYGEN_DOC_INTERNAL "YES")
	endif ()

	configure_file(${doxyfile_in} ${RBL_DOXYFILE} @ONLY)

	rbl_doxygen(${doxy_html_index_file} "Generating documentation")
	add_custom_target(doc ALL DEPENDS ${doxy_html_index_file})


	# install documentation
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
	        DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif ()
