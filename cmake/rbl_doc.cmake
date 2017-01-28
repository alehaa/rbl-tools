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


# Options
#
option("BUILD_DOC" "Build HTML documentation" Off)
option("BUILD_DOC_INTERNAL"
  "Build HTML documentation including private functions" Off)


#
# Configuration.
#
set(RBL_DOXYFILE "${PROJECT_BINARY_DIR}/doc/doxygen.conf")


## \brief Call Doxygen to generate \p OUTPUT file.
#
# \details This function calls Doxygen to generate the \p OUTPUT file. All other
#  files will be generated, too, but this is used to define dependencies if a
#  required output file is missing (e.g. a required man page).
#
#
# \param OUTPUT The file to be generated.
# \param MESSAGE The message to be printed.
#
function (rbl_doxygen OUTPUT MESSAGE)
  find_package(Doxygen REQUIRED)

  add_custom_command(OUTPUT ${OUTPUT}
                     COMMAND ${DOXYGEN_EXECUTABLE} ${RBL_DOXYFILE}
                     WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/doc"
                     MAIN_DEPENDENCY ${RBL_DOXYFILE}
                     DEPENDS rbl_shared ckrbl
                     COMMENT ${MESSAGE})
endfunction ()


## \brief Add a man page for Doxygen \p MODULE with \p SYMBOL as symlink.
#
# \note This function has no effect if BUILD_DOC and BUILD_DOC_INTERNAL are
#  disabled.
#
#
# \param MODULE The Doxygen module name.
# \param SYMBOL The name of a symbol in the module.
#
function (rbl_add_man MODULE SYMBOL)
  if (NOT BUILD_DOC AND NOT BUILD_DOC_INTERNAL)
    return()
  endif ()


  set(manfile "${PROJECT_BINARY_DIR}/doc/man/man3/${MODULE}.3")

  if (NOT TARGET "${MODULE}.3")
    rbl_doxygen(${manfile} "Generating man page ${MODULE}.3")
    add_custom_target("${MODULE}.3" ALL DEPENDS ${manfile})

    # Install the manpage and a link for SYMBOL.
    install(FILES ${manfile} DESTINATION ${CMAKE_INSTALL_MANDIR}/man3)
  endif ()

  if(CMAKE_HOST_UNIX)
    install(CODE "
      execute_process(COMMAND ln -fs ${MODULE}.3
                      ${CMAKE_INSTALL_FULL_MANDIR}/man3/${SYMBOL}.3)
      message(STATUS \"Installing: \"
                     \"${CMAKE_INSTALL_FULL_MANDIR}/man3/${SYMBOL}.3\")
    ")
  else()
    message(WARNING "Can't install symlinks for man pages.")
  endif()
endfunction ()
