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

# Minimum required cmake version.
cmake_minimum_required(VERSION 2.8.11)


# Set policies.
foreach (POL CMP0042 CMP0048)
	if (POLICY ${POL})
		cmake_policy(SET ${POL} NEW)
	endif ()
endforeach ()


# Project information.
if (${CMAKE_MAJOR_VERSION} EQUAL 3)
	project("RBL" LANGUAGES C)
else ()
	project("RBL" C)
endif ()


# Set the module search path to include local modules.
set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/cmake"
	"${PROJECT_SOURCE_DIR}/externals/CMake-CChelper/cmake"
	"${PROJECT_SOURCE_DIR}/externals/CMake-codecov/cmake"
	"${PROJECT_SOURCE_DIR}/externals/CMake-easylib/cmake"
	"${PROJECT_SOURCE_DIR}/externals/CMake-gitinfo/cmake"
	"${PROJECT_SOURCE_DIR}/externals/sanitizers-cmake/cmake"
	${CMAKE_MODULE_PATH})


# Project version.
find_package(GitInfo REQUIRED)
git_version_info(REQUIRED)
message(STATUS "Configuring version ${RBL_VERSION}")


# Enable CCHelpers.
include(CChelper)


# Recurse into subdirectories.
add_subdirectory(conf)
add_subdirectory(doc)
add_subdirectory(src)

# Tests.
option(ENABLE_TESTS "Selects whether tests are built." false)
if (ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif ()
