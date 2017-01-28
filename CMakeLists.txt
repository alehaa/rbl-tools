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


# minimum required cmake version
cmake_minimum_required(VERSION 2.8.11)


#
# project information
#
if (${CMAKE_MAJOR_VERSION} EQUAL 3)
	project("rbl-tools" LANGUAGES C)
else ()
	project("rbl-tools" C)
endif ()


# choose new behaviour for CMP0042
# see http://www.cmake.org/cmake/help/v3.0/policy/CMP0042.html for more details
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 NEW)
endif (POLICY CMP0042)


# Set the module search path to include local modules.
set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/cmake"
	"${PROJECT_SOURCE_DIR}/externals/CMake-easylib/cmake"
	${CMAKE_MODULE_PATH})


#
# recurse into subdirectories
#
add_subdirectory(conf)
add_subdirectory(doc)
add_subdirectory(src)


option(ENABLE_TESTS "Selects whether tests are built." false)
if (ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif ()
