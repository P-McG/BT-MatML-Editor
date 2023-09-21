# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "C:/Users/paulm/source/repos/BT-MatML-Editor;C:/Users/paulm/source/repos/BT-MatML-Editor/build")
set(CPACK_CMAKE_GENERATOR "Visual Studio 17 2022")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "BT-MatML-Editor built using CMake")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/paulm/source/repos/BT-MatML-Editor/build;BT-MatML-Editor;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files/BT-MatML-Editor")
set(CPACK_MODULE_PATH "C:/Users/paulm/source/repos/BT-MatML-Editor")
set(CPACK_NSIS_DISPLAY_NAME "BT-MatML-Editor 0.1.4")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "BT-MatML-Editor 0.1.4")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/paulm/source/repos/BT-MatML-Editor/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BT-MatML-Editor built using CMake")
set(CPACK_PACKAGE_FILE_NAME "BT-MatML-Editor-0.1.4-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "BT-MatML-Editor 0.1.4")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "BT-MatML-Editor 0.1.4")
set(CPACK_PACKAGE_NAME "BT-MatML-Editor")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "BT-MatML-Editor development team")
set(CPACK_PACKAGE_VERSION "0.1.4")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "4")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Users/paulm/source/repos/BT-MatML-Editor/LICENSE")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.26/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/paulm/source/repos/BT-MatML-Editor/build/CPackSourceConfig.cmake")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/paulm/source/repos/BT-MatML-Editor/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
