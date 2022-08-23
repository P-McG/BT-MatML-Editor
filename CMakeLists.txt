#############################################################################
# Name:        CMakeLists.txt
# Purpose:     Primary CMake for BT-MatML-Editor
# Author:      Paul McGrath
# Created:     2022-08-01
# Copyright:   (c) 2022 BT-MatML-Editor development team
# Licence:     GPL-3.0-only licence
#############################################################################
cmake_minimum_required(VERSION 3.24)

# set the project name
project(BT-MatML-Editor VERSION 0.1.3)

set(CMAKE_BUILD_TYPE)
set(CMAKE_DEBUG_POSTFIX d)

# Packaging support
set(CPACK_PACKAGE_VENDOR "BT-MatML-Editor development team")

add_library(BT-MatML-Editor_compiler_flags INTERFACE)
target_compile_features(BT-MatML-Editor_compiler_flags INTERFACE cxx_std_11)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(BT-MatML-Editor_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

configure_file(BT_MatML_Editor-Config.h.in BT_MatML_Editor-Config.h)

# Allows for the use of findXSD.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(BOOST_ROOT "/usr")
  set(wxWidgets_ROOT "/usr")
  set(XSD_ROOT "/usr")
  set(XercesC_ROOT "/usr")
endif ()

#BOOST
#-----
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(BOOST_INCLUDEDIR "/usr/include")
  set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
endif ()
#statically link to Boost libs
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.79 COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

#XERCES-C
#--------
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(XercesC_LIBRARY_DIR "${XercesC_ROOT}/lib")

# the following doesnt work in multi config generators (like visual studio), 
# unless it is assigned explicitly
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(XercesC_LIBRARY "xerces-c_3D")
  else ()
    set(XercesC_LIBRARY "xerces-c_3")
  endif ()

  set(BUILD_SHARED_LIBS OFF)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(XercesC_LIBRARY_DIR "${XercesC_ROOT}/lib/x86_64-linux-gnu")
  set(XercesC_LIBRARY "xerces-c-3.2")
endif ()

set(XercesC_INCLUDE_DIR  "${XercesC_ROOT}/include")
set(XercesC_VERSION "3.1.1")

find_package(XercesC REQUIRED)
link_directories(${XercesC_LIBRARY_DIR})

#XSD
#---
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(XSD_INCLUDE_DIRS "${XSD_ROOT}/libxsd")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(XSD_INCLUDE_DIRS "${XSD_ROOT}/include")
endif ()

find_package(XSD REQUIRED)

#WXWIDGETS
#---------
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(wxWidgets_CONFIG_EXECUTABLE "/usr/local/bin/wx-config")
  set(WX_ROOT_DIR "/usr/local/lib")
  set(wxWidgets_USE_DEBUG OFF)
  set(wxWidgets_USE_UNICODE ON)
  set(wxWidgets_USE_UNIVERSAL OFF)
  set(wxWidgets_CONFIG_OPTIONS )
  ## CAUSES ERROR --toolkit=base needs removed ## set(wxWidgets_CONFIG_OPTIONS --toolkit=base --prefix=/usr/local)
endif ()

find_package(wxWidgets 3.2 REQUIRED COMPONENTS net core base html)

include(${wxWidgets_USE_FILE})


#BT-MatML-Editor
#---------------

set(BT-MatML-Editor_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include;include/GUI")
set(INCLUDE_DIRS "${Boost_INCLUDE_DIRS};${XercesC_INCLUDE_DIR};${XSD_INCLUDE_DIRS};${wxWidgets_INCLUDE_DIRS};${BT-MatML-Editor_INCLUDE_DIRS}")
include_directories(${INCLUDE_DIRS} ${PROJECT_BINARY_DIR})

file(GLOB SOURCES1 "src/*.cpp")
file(GLOB SOURCES2 "src/GUI/*.cpp")
file(GLOB SOURCES3 "src/*.cxx")
file(GLOB SOURCES4 "src/GUI/*.cxx")


add_executable(BT-MatML-Editor WIN32 ${SOURCES1} ${SOURCES2} ${SOURCES3} ${SOURCES4})

#the following is not possible with wxWidgets using shared dlls
#set_property(TARGET BT-MatML-Editor PROPERTY
#  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(BT-MatML-Editor PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# Works correctly for both single and multi-config generators
target_compile_definitions(BT-MatML-Editor PRIVATE
  $<$<CONFIG:Release>:RELEASE_BUILD>
)

target_link_libraries(BT-MatML-Editor 
                      ${wxWidgets_LIBRARIES} 
                      ${XercesC_LIBRARIES} 
                      ${Boost_LIBRARIES})

target_include_directories(BT-MatML-Editor PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS BT-MatML-Editor DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/BT_MatML_Editor-Config.h"
  DESTINATION include
  )

# Copy required directories
install(DIRECTORY "${PROJECT_SOURCE_DIR}/data/" DESTINATION "data")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/images/" DESTINATION "images")

#include not required until  libGUI.so or GUI.dll is created
#include(GNUInstallDirs)
#install(FILES 
#        "include/config.h"
#        "include/fcopy.h"
#        "include/matml31.hxx"
#        "include/matml31_strongtypedef.h"
#        "include/StringStream.h"
#        "include/Uuid-Utility.h"
#        "include/version.h"
#        "include/BT_MatML_App.h"
#        "include/bt_matml_config.h"
#        "include/BT_MatML_MatMLTreeItemData.h"
#        "include/GUI/BT_MatML_Uncertainty_GUI.h"
#        "include/GUI/BT_MatML_Unit_GUI.h"
#        "include/GUI/BT_MatML_Unitless_GUI.h"
#        "include/GUI/BT_MatML_Units_GUI.h"
#        "include/GUI/BT_MatML_Utilities_GUI.h"
#        "include/GUI/BT_MatML_Value_GUI.h"
#        "include/GUI/HTMLFrame.h"
#        "include/GUI/HTMLFrameBase.h"
#        "include/GUI/PreferenceFrame.h"
#        "include/GUI/PreferenceFrameBase.h"
#        "include/GUI/printing.h"
#        "include/GUI/BT_MatML_Abbreviation_GUI.h"
#        "include/GUI/BT_MatML_Associate_GUI.h"
#        "include/GUI/BT_MatML_AssociationDetails_GUI.h"
#        "include/GUI/BT_MatML_AuthorityDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_AuthorityDetails_GUI.h"
#        "include/GUI/BT_MatML_Base_GUI.h"
#        "include/GUI/BT_MatML_BulkDetails_GUI.h"
#        "include/GUI/BT_MatML_Characterization_GUI.h"
#        "include/GUI/BT_MatML_ChemicalComposition_GUI.h"
#        "include/GUI/BT_MatML_ChemicalElementSymbol_GUI.h"
#        "include/GUI/BT_MatML_Class_GUI.h"
#        "include/GUI/BT_MatML_ComponentDetails_GUI.h"
#        "include/GUI/BT_MatML_Compound_GUI.h"
#        "include/GUI/BT_MatML_Concentration_GUI.h"
#        "include/GUI/BT_MatML_CurrencyCode_GUI.h"
#        "include/GUI/BT_MatML_Data_GUI.h"
#        "include/GUI/BT_MatML_Data1_GUI.h"
#        "include/GUI/BT_MatML_DataFormat_GUI.h"
#        "include/GUI/BT_MatML_DataSourceDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_DataSourceDetails_GUI.h"
#        "include/GUI/BT_MatML_Default.h"
#        "include/GUI/BT_MatML_Definition_GUI.h"
#        "include/GUI/BT_MatML_DimensionalDetails_GUI.h"
#        "include/GUI/BT_MatML_Dimensions_GUI.h"
#        "include/GUI/BT_MatML_Element_GUI.h"
#        "include/GUI/BT_MatML_Form_GUI.h"
#        "include/GUI/BT_MatML_Formula_GUI.h"
#        "include/GUI/BT_MatML_Geometry_GUI.h"
#        "include/GUI/BT_MatML_Glossary_GUI.h"
#        "include/GUI/BT_MatML_GlossaryTerm_GUI.h"
#        "include/GUI/BT_MatML_Graph_GUI.h"
#        "include/GUI/BT_MatML_Graphs_GUI.h"
#        "include/GUI/BT_MatML_GUI.h"
#        "include/GUI/BT_MatML_ID_GUI.h"
#        "include/GUI/BT_MatML_Material_GUI.h"
#        "include/GUI/BT_MatML_MaterialFrame.h"
#        "include/GUI/BT_MatML_MaterialFrameBase.h"
#        "include/GUI/BT_MatML_MatML_Doc_GUI.h"
#        "include/GUI/BT_MatML_MatMLInfo_GUI.h"
#        "include/GUI/BT_MatML_MeasurementTechniqueDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_MeasurementTechniqueDetails_GUI.h"
#        "include/GUI/BT_MatML_Metadata_GUI.h"
#        "include/GUI/BT_MatML_Name_GUI.h"
#        "include/GUI/BT_MatML_Notes_GUI.h"
#        "include/GUI/BT_MatML_Orientation_GUI.h"
#        "include/GUI/BT_MatML_ParameterDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_ParameterDetails_GUI.h"
#        "include/GUI/BT_MatML_ParameterValue_GUI.h"
#        "include/GUI/BT_MatML_ParentMaterial_GUI.h"
#        "include/GUI/BT_MatML_ParentSubClass_GUI.h"
#        "include/GUI/BT_MatML_PhaseComposition_GUI.h"
#        "include/GUI/BT_MatML_ProcessingDetails_GUI.h"
#        "include/GUI/BT_MatML_PropertyData_GUI.h"
#        "include/GUI/BT_MatML_PropertyDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_PropertyDetails_GUI.h"
#        "include/GUI/BT_MatML_Qualifier_GUI.h"
#        "include/GUI/BT_MatML_Relationship_GUI.h"
#        "include/GUI/BT_MatML_Result_GUI.h"
#        "include/GUI/BT_MatML_Scale_GUI.h"
#        "include/GUI/BT_MatML_Shape_GUI.h"
#        "include/GUI/BT_MatML_Source_GUI.h"
#        "include/GUI/BT_MatML_SourceDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_SourceDetails_GUI.h"
#        "include/GUI/BT_MatML_Specification_GUI.h"
#        "include/GUI/BT_MatML_SpecimenDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_SpecimenDetails_GUI.h"
#        "include/GUI/BT_MatML_StringValidator.h"
#        "include/GUI/BT_MatML_Symbol_GUI.h"
#        "include/GUI/BT_MatML_Synonym_GUI.h"
#        "include/GUI/BT_MatML_TestConditionDetails_Display_GUI.h"
#        "include/GUI/BT_MatML_TestConditionDetails_GUI.h"
#        "include/GUI/BT_MatML_TreeCtrlSorted.h"
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${BT-MatML-Editor_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BT-MatML-Editor_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
