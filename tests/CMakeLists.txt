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

include(CMakeParseArguments)


# Helper function to add test cases for librbl.
function (rbl_add_test NAME)
	set(oneValueArgs PASS_EXPRESSION FAIL_EXPRESSION)
	set(multiValueArgs COMMAND)
	cmake_parse_arguments("OPT" "" "${oneValueArgs}" "${multiValueArgs}"
	                      ${ARGN})

	# Add test case with optional pass or fail regular expression.
	add_test(NAME ${NAME} COMMAND ${OPT_COMMAND})
	if (OPT_PASS_EXPRESSION)
		set_tests_properties(${NAME} PROPERTIES PASS_REGULAR_EXPRESSION
		                     "${OPT_PASS_EXPRESSION}")
	else ()
		if (NOT OPT_FAIL_EXPRESSION)
			set(OPT_FAIL_EXPRESSION "Error;ERROR;Failed")
		endif ()

		set_tests_properties(${NAME} PROPERTIES FAIL_REGULAR_EXPRESSION
		                     "${OPT_FAIL_EXPRESSION}")
	endif ()
endfunction ()


# Recurse into subdirectories.
add_subdirectory(librbl)
