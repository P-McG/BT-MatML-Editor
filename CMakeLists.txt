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
project(BT-MatML-Editor VERSION 0.1.4)

set(CMAKE_BUILD_TYPE)
set(CMAKE_DEBUG_POSTFIX d)

# Packaging support
set(CPACK_PACKAGE_VENDOR "BT-MatML-Editor development team")

add_library(BT-MatML-Editor_compiler_flags INTERFACE)
target_compile_features(BT-MatML-Editor_compiler_flags INTERFACE cxx_std_17)


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
  set(BOOST_ROOT "C:/Program Files/boost")
  set(wxWidgets_ROOT "C:/Program Files/wxWidgets")
  set(XercesC_ROOT "C:/xsd/debug")
  set(XSD_ROOT "C:/xsd/debug")
  set(ICU_ROOT "C:/xsd/debug")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
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

  add_definitions(-DLIBXERCES_C_STATIC)

# the following doesnt work in multi config generators (like visual studio), 
# unless it is assigned explicitly
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(XercesC_LIBRARY_DIR "${XercesC_ROOT}/debug/lib")
    set(XercesC_LIBRARY "xerces-c.lib")
  else ()
    set(XercesC_LIBRARY_DIR "${XercesC_ROOT}/release/lib")
    set(XercesC_LIBRARY "xerces-c.lib")
  endif ()

  set(BUILD_SHARED_LIBS OFF)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(XercesC_LIBRARY_DIR "${XercesC_ROOT}/lib/x86_64-linux-gnu")
  set(XercesC_LIBRARY "xerces-c-3.2")
endif ()

set(XercesC_INCLUDE_DIR  "${XercesC_ROOT}/include")
set(XercesC_VERSION "3.2")

find_package(XercesC REQUIRED)
link_directories(${XercesC_LIBRARY_DIR})

#icuuc.lib
#--------
#if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

# the following doesnt work in multi config generators (like visual studio), 
# unless it is assigned explicitly
#  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set(Icu_LIBRARY_DIR "${XercesC_ROOT}/debug/lib")
#    set(Icu_LIBRARY "icuuc.lib")
#  else ()
#    set(Icu_LIBRARY_DIR "${XercesC_ROOT}/release/lib")
#    set(Icu_LIBRARY "icuuc.lib")
#  endif ()
#elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
#  set(Icu_LIBRARY_DIR "${XercesC_ROOT}/lib/x86_64-linux-gnu")
#  set(Icu_LIBRARY "xerces-c-3.2")
#endif ()

set(ICU_INCLUDE_DIR  "${ICU_ROOT}/include")
set(ICU_I18N_LIBRARY "icui18n")
set(ICU_UC_LIBRARY "icuuc")
set(ICU_DATA_LIBRARY "icudata")
set(ICU_LIBRARY "${ICU_I18N_LIBRARY};${ICU_UC_LIBRARY};${ICU_DATA_LIBRARY}")
find_package(ICU REQUIRED)
link_directories(${ICU_LIBRARY_DIR})


#XSD
#---
add_definitions(-DXSD_CXX11)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(XSD_INCLUDE_DIRS "${XSD_ROOT}/debug/include;${XSD_ROOT}/debug/include/xsd/cxx/tree")
  else()
    set(XSD_INCLUDE_DIRS "${XSD_ROOT}/release/include")
  endif()
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

set(BT_MatML_Editor_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include;include/bellshire/Lib")
set(INCLUDE_DIRS "${Boost_INCLUDE_DIRS};${ICU_INCLUDE_DIRS};${XercesC_INCLUDE_DIR};${XSD_INCLUDE_DIRS};${wxWidgets_INCLUDE_DIRS};${BT-MatML-Editor_INCLUDE_DIRS}")
include_directories(${INCLUDE_DIRS} ${PROJECT_BINARY_DIR})


file(GLOB SOURCES1 "src/*.cpp")
file(GLOB SOURCES2 "src/*.cxx")
file(GLOB SOURCES3 "src/bellshire/*.cpp")
file(GLOB SOURCES4 "src/bellshire/*.cxx")
file(GLOB SOURCES5 "src/bellshire/utilities/*.cpp")
file(GLOB SOURCES6 "src/bellshire/utilities/*.cxx")
file(GLOB SOURCES7 "src/bellshire/Lib/*.cpp")
file(GLOB SOURCES8 "src/bellshire/Lib/*.cxx")
file(GLOB SOURCES9 "src/bellshire/Lib/utilities/*.cpp")
file(GLOB SOURCES10 "src/bellshire/Lib/utilities/*.cxx")
file(GLOB SOURCES11 "src/bellshire/GUI/*.cpp")
file(GLOB SOURCES12 "src/bellshire/GUI/*.cxx")
file(GLOB SOURCES13 "src/bellshire/GUI/utilities/*.cpp")
file(GLOB SOURCES14 "src/bellshire/GUI/utilities/*.cxx")

file(GLOB SOURCES15 "include/*.h")
file(GLOB SOURCES16 "include/*.hxx")
file(GLOB SOURCES17 "include/*.txx")
file(GLOB SOURCES18 "include/*.inl")
file(GLOB SOURCES19 "include/bellshire/*.h")
file(GLOB SOURCES20 "include/bellshire/*.hxx")
file(GLOB SOURCES21 "include/bellshire/*.inl")
file(GLOB SOURCES22 "include/bellshire/utilities/*.h")
file(GLOB SOURCES23 "include/bellshire/utilities/*.hxx")
file(GLOB SOURCES24 "include/bellshire/utilities/*.inl")
file(GLOB SOURCES25 "include/bellshire/Lib/*.h")
file(GLOB SOURCES26 "include/bellshire/Lib/*.hxx")
file(GLOB SOURCES27 "include/bellshire/Lib/*.inl")
file(GLOB SOURCES28 "include/bellshire/Lib/utilities/*.h")
file(GLOB SOURCES29 "include/bellshire/Lib/utilities/*.hxx")
file(GLOB SOURCES30 "include/bellshire/Lib/utilities/*.inl")
file(GLOB SOURCES31 "include/bellshire/GUI/*.h")
file(GLOB SOURCES32 "include/bellshire/GUI/*.hxx")
file(GLOB SOURCES33 "include/bellshire/GUI/*.inl")
file(GLOB SOURCES34 "include/bellshire/GUI/utilities/*.h")
file(GLOB SOURCES35 "include/bellshire/GUI/utilities/*.hxx")
file(GLOB SOURCES36 "include/bellshire/GUI/utilities/*.inl")

add_executable(BT-MatML-Editor WIN32
    ${SOURCES1} 
    ${SOURCES2}
    ${SOURCES3}
    ${SOURCES4}
    ${SOURCES5}
    ${SOURCES6}
    ${SOURCES7}
    ${SOURCES8}
    ${SOURCES9}
    ${SOURCES10}
    ${SOURCES11}
    ${SOURCES12}
    ${SOURCES13}
    ${SOURCES14}
    ${SOURCES15}
    ${SOURCES16}
    ${SOURCES17}
    ${SOURCES18}
    ${SOURCES19} 
    ${SOURCES20}
    ${SOURCES21}
    ${SOURCES22}
    ${SOURCES23}
    ${SOURCES24}
    ${SOURCES25}
    ${SOURCES26}
    ${SOURCES27}
    ${SOURCES28}
    ${SOURCES29}
    ${SOURCES30}
    ${SOURCES31}
    ${SOURCES32}
    ${SOURCES33}
    ${SOURCES34}
    ${SOURCES35}
    ${SOURCES36}
)

#the following is not possible with wxWidgets using shared dlls
#set_property(TARGET BT-MatML-Editor PROPERTY
#  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(BT-MatML-Editor PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET BT-MatML-Editor PROPERTY CXX_STANDARD 17)
set_property(TARGET BT-MatML-Editor PROPERTY CXX_STANDARD_REQUIRED ON)

# Works correctly for both single and multi-config generators
target_compile_definitions(BT-MatML-Editor PRIVATE
  $<$<CONFIG:Release>:RELEASE_BUILD>
)

target_include_directories(BT-MatML-Editor PUBLIC ${BT_MatML_Editor_INCLUDE_DIRS} )

target_link_libraries(BT-MatML-Editor 
                      ${wxWidgets_LIBRARIES}
                      ${ICU_LIBRARIES}
                      ${XercesC_LIBRARIES} 
                      ${Boost_LIBRARIES})

target_precompile_headers(BT-MatML-Editor 
  PUBLIC    "include/bellshire/BT_MatML_MatML_Base.h"
            "include/bellshire/BT_MatML_Abbreviation.h"
            "include/bellshire/BT_MatML_Associate.h"
            "include/bellshire/BT_MatML_AssociationDetails.h"
            "include/bellshire/BT_MatML_AuthorityDetails.h"
            "include/bellshire/BT_MatML_BulkDetails.h"
            "include/bellshire/BT_MatML_Characterization.h"
            "include/bellshire/BT_MatML_ChemicalComposition.h"
            "include/bellshire/BT_MatML_ChemicalElementSymbol.h"
            "include/bellshire/BT_MatML_Class.h"
            "include/bellshire/BT_MatML_ComponentDetails.h"
            "include/bellshire/BT_MatML_Compound.h"
            "include/bellshire/BT_MatML_Concentration.h"
            "include/bellshire/BT_MatML_CurrencyCode.h"
            "include/bellshire/BT_MatML_Data1.h"
            "include/bellshire/BT_MatML_DataFormat.h"
            "include/bellshire/BT_MatML_DataSourceDetails.h"
            "include/bellshire/BT_MatML_Data.h"
            "include/bellshire/BT_MatML_Definition.h"
            "include/bellshire/BT_MatML_DimensionalDetails.h"
            "include/bellshire/BT_MatML_Dimensions.h"
            "include/bellshire/BT_MatML_Element.h"
            "include/bellshire/BT_MatML_Form.h"
            "include/bellshire/BT_MatML_Formula.h"
            "include/bellshire/BT_MatML_Geometry.h"
            "include/bellshire/BT_MatML_GlossaryTerm.h"
            "include/bellshire/BT_MatML_Glossary.h"
            "include/bellshire/BT_MatML_Graph.h"
            "include/bellshire/BT_MatML_Graphs.h"
            "include/bellshire/BT_MatML_MatML_Doc.h"
            "include/bellshire/BT_MatML_Material.h"
            "include/bellshire/BT_MatML_MeasurementTechniqueDetails.h"
            "include/bellshire/BT_MatML_Metadata.h"
            "include/bellshire/BT_MatML_Name.h"
            "include/bellshire/BT_MatML_Notes.h"
            "include/bellshire/BT_MatML_Orientation.h"
            "include/bellshire/BT_MatML_ParameterDetails.h"
            "include/bellshire/BT_MatML_ParameterValue.h"
            "include/bellshire/BT_MatML_ParentMaterial.h"
            "include/bellshire/BT_MatML_ParentSubClass.h"
            "include/bellshire/BT_MatML_PhaseComposition.h"
            "include/bellshire/BT_MatML_ProcessingDetails.h"
            "include/bellshire/BT_MatML_PropertyData.h"
            "include/bellshire/BT_MatML_PropertyDetails.h"
            "include/bellshire/BT_MatML_Qualifier.h"
            "include/bellshire/BT_MatML_Relationship.h"
            "include/bellshire/BT_MatML_Result.h"
            "include/bellshire/BT_MatML_Scale.h"
            "include/bellshire/BT_MatML_Shape.h"
            "include/bellshire/BT_MatML_SourceDetails.h"
            "include/bellshire/BT_MatML_Source.h"
            "include/bellshire/BT_MatML_Specification.h"
            "include/bellshire/BT_MatML_SpecimenDetails.h"
            "include/bellshire/BT_MatML_Subclass1.h"
            "include/bellshire/BT_MatML_Subclass.h"
            "include/bellshire/BT_MatML_Symbol.h"
            "include/bellshire/BT_MatML_Synonym.h"
            "include/bellshire/BT_MatML_TestConditionDetails.h"
            "include/bellshire/BT_MatML_Uncertainty.h"
            "include/bellshire/BT_MatML_Unit.h"
            "include/bellshire/BT_MatML_Unitless.h"
            "include/bellshire/BT_MatML_Units.h"
            "include/bellshire/BT_MatML_Value.h"
            "include/bellshire/BT_MatML.h"
            "include/bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
            "include/bellshire/GUI/BT_MatML_Abbreviation_GUI.h"
            "include/bellshire/GUI/BT_MatML_Associate_GUI.h"
            "include/bellshire/GUI/BT_MatML_AssociationDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_AuthorityDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_BulkDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Characterization_GUI.h"
            "include/bellshire/GUI/BT_MatML_ChemicalComposition_GUI.h"
            "include/bellshire/GUI/BT_MatML_ChemicalElementSymbol_GUI.h"
            "include/bellshire/GUI/BT_MatML_Class_GUI.h"
            "include/bellshire/GUI/BT_MatML_ComponentDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Compound_GUI.h"
            "include/bellshire/GUI/BT_MatML_Concentration_GUI.h"
            "include/bellshire/GUI/BT_MatML_CurrencyCode_GUI.h"
            "include/bellshire/GUI/BT_MatML_Data1_GUI.h"
            "include/bellshire/GUI/BT_MatML_DataFormat_GUI.h"
            "include/bellshire/GUI/BT_MatML_DataSourceDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Data_GUI.h"
            "include/bellshire/GUI/BT_MatML_Definition_GUI.h"
            "include/bellshire/GUI/BT_MatML_DimensionalDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Dimensions_GUI.h"
            "include/bellshire/GUI/BT_MatML_Element_GUI.h"
            "include/bellshire/GUI/BT_MatML_Form_GUI.h"
            "include/bellshire/GUI/BT_MatML_Formula_GUI.h"
            "include/bellshire/GUI/BT_MatML_Geometry_GUI.h"
            "include/bellshire/GUI/BT_MatML_GlossaryTerm_GUI.h"
            "include/bellshire/GUI/BT_MatML_Glossary_GUI.h"
            "include/bellshire/GUI/BT_MatML_Graph_GUI.h"
            "include/bellshire/GUI/BT_MatML_Graphs_GUI.h"
            "include/bellshire/GUI/BT_MatML_MatML_Doc_GUI.h"
            "include/bellshire/GUI/BT_MatML_Material_GUI.h"
            "include/bellshire/GUI/BT_MatML_MeasurementTechniqueDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Metadata_GUI.h"
            "include/bellshire/GUI/BT_MatML_Name_GUI.h"
            "include/bellshire/GUI/BT_MatML_Notes_GUI.h"
            "include/bellshire/GUI/BT_MatML_Orientation_GUI.h"
            "include/bellshire/GUI/BT_MatML_ParameterDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_ParameterValue_GUI.h"
            "include/bellshire/GUI/BT_MatML_ParentMaterial_GUI.h"
            "include/bellshire/GUI/BT_MatML_ParentSubClass_GUI.h"
            "include/bellshire/GUI/BT_MatML_PhaseComposition_GUI.h"
            "include/bellshire/GUI/BT_MatML_ProcessingDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_PropertyData_GUI.h"
            "include/bellshire/GUI/BT_MatML_PropertyDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Qualifier_GUI.h"
            "include/bellshire/GUI/BT_MatML_Relationship_GUI.h"
            "include/bellshire/GUI/BT_MatML_Result_GUI.h"
            "include/bellshire/GUI/BT_MatML_Scale_GUI.h"
            "include/bellshire/GUI/BT_MatML_Shape_GUI.h"
            "include/bellshire/GUI/BT_MatML_SourceDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Source_GUI.h"
            "include/bellshire/GUI/BT_MatML_Specification_GUI.h"
            "include/bellshire/GUI/BT_MatML_SpecimenDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Subclass1_GUI.h"
            "include/bellshire/GUI/BT_MatML_Subclass_GUI.h"
            "include/bellshire/GUI/BT_MatML_Symbol_GUI.h"
            "include/bellshire/GUI/BT_MatML_Synonym_GUI.h"
            "include/bellshire/GUI/BT_MatML_TestConditionDetails_GUI.h"
            "include/bellshire/GUI/BT_MatML_Uncertainty_GUI.h"
            "include/bellshire/GUI/BT_MatML_Unit_GUI.h"
            "include/bellshire/GUI/BT_MatML_Unitless_GUI.h"
            "include/bellshire/GUI/BT_MatML_Units_GUI.h"
            "include/bellshire/GUI/BT_MatML_Value_GUI.h"
            "include/bellshire/GUI/BT_MatML_GUI.h"
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
#        "include/matml31_strongly_typed_def.h"
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
#        "include/GUI/BT_MatML_GUI_Base.h"
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
