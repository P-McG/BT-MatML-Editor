**Author**
Paul McGrath
**Date**
June, 2022

The MatML Editor is a text Editor for the [MatML 3.1 XML Schema](https://www.matml.org/).

MatML is an extensible markup language (XML) developed especially for 
the interchange of material information. It provides a medium of 
communication for users in materials science and related fields such
as manufacturing and aerospace. It sets the stage for the development
of semantic web standards to enhance knowledge discovery in materials 
science and related areas.

Binary Downloads
================

 Goto [Releases](https://github.com/P-McG/BT-MatML-Editor/releases) and under *Assets* download the win64 for Microsoft Windows releases and Linux for Linux releases.

BT-MatML-Editor Usage
=====================

 To run the program, click on the BT-MatML-Editor application.

 Once running click on 'File->Open', or 'File->New', to start. 

 The general approach to the program is to use the Tree Control user interface to navigate through the MatML data elements. The tree on the left side is the main navigation aid (1). Mouse click on the elements of the tree and then left mouse click to get more options, such as to add more data elements to the Tree Control. The MatML Schema Information will show up on the right panel (2). The tabs for the right panel (3) will display either the MatML Schema Information (default) or the MatML data itself (can be changed in 'Edit->Preferences').

 ![BT-MatML-Editor](../../images/BT-MatML-Editor-Application-1.png)

 While the BT-MatML-Editor is not a database, and not optimized for extremely large files, it can handle multimaterial files. These larger files are more manageable using the following tools.

 Sorting the view of the materials. In 'Edit->Preferences->Sort class', it is possible to add sort classes. This option will changed the view (not the xml file) of the materials. Adding "STEEL" for an example, will display the Materials with the class name of "STEEL" first. Then the remainding materials will be displayed in the order the are in inside the XML file. Once set, 'view->perform material sort' will change the view order of the materials.

 One other option for viewing larger files is the use of 'view->Isolate material branch'. This will isolate materials which are interconnected with ' Material -> ComponentDetails -> Class -> ParentMaterial ' associations. To exit this view, 'View->Exit Isolate material branch' will bring back the original list of materials.

BT-MatML-Editor Builds
======================

 Development source code is hosted on [GitHub](https://github.com/P-McG/BT-MatML-Editor) and source code for stable release versions are found at [releases](https://github.com/P-McG/BT-MatML-Editor/releases) along with the binaries.

 The following prerequisites dependencies are:
 - [Xerces-c](https://xerces.apache.org/xerces-c/) 3.2.3
 - [CodeSynthesis-XSD](https://www.codesynthesis.com/products/xsd/) 4.0.0
 - [wxWidget](https://www.wxwidgets.org/) 3.2.0
 - [Boost](https://www.boost.org/) 1.79.0

 For Building
  [CMake](https://cmake.org) 3.24
 
BT-MatML-Editor Windows Build
------------------------------

 To Build:

 cmake-gui

 Within cmake-gui:
 - Set the "Where is the source code" directory to the BT-MatML-Editor root.
- Set the "Where to build the binaries" directory to the BT-MatML-Editor root/build
- Add the following entries (change paths depending on your installation):
  - CMAKE_BUILD_TYPE "Release"
  - XercesC_ROOT PATH "C:/Program Files/xerces-c" 
  - XSD_ROOT PATH "C:/Program Files/code_synthesis_xsd/xsd-4.0.0-i686-windows/bin" 
  - wxWidgets_ROOT PATH "C:/Program Files/wxWidgets/wxWidgets-3.2.0"
  - BOOST_ROOT PATH "C:/Program Files/boost/boost_1_79_0"

- Press "Configure" button. Specify your generator
- Press "Generate" button.
- Press "Open Project" button.

Within the generator (e.g. Visual Studio):
  - Set the "Solution Configuration" to Release.
  - Set the "Solution Platform" to x64.
  - Build Solution.

In a shell with Administrator privileges (so you can install into "C:/Program Files"):
- cd into the ${BT-MatML-Editor}/build/win64 directory.
- cmake --install . --config release

To run:
- dir "C:/Program Files/BT-MatML-Editor"
- ./BT-MatML-Editor

Package generation:
- cd ${source}/build/win64
- cpack

Package Checksum Values in Windows 10
- certutil -hashfile  BT-MatML-Editor-0.1.1-win64.exe SHA1 

BT-MatML-Editor Linux Build
---------------------------
To build:
- cd /path/to/BT-MatML-Editor/build/linux
- cmake -S ../.. -B .
- make
- sudo cmake --install . --config release

To run:
- BT-MatML-Editor

Package generation:
- cd ${source}/build/linux
- cpack

Package Checksum Values in Linux
- sha1sum  BT-MatML-Editor-0.1.2-Linux.tar.gz 

Programming Guide 
=================
[for doxygen doc see here for active hyperlinks](https://p-mcg.github.io/BT-MatML-Editor)

The program is structure to perform the following tasks:
1. Parsing the MatML XML Schema using Xerces-c and binding the XML data into C++ using CodeSynthesis-XSD.
2. Create GUIs using wxWidgets.
3. Polymorphically bind the MatML XML data to the wxWidgets GUIs.


Parsing the MatML XML Schema using Xerces-c and binding the XML data into C++ using CodeSynthesis-XSD. 
------------------------------------------------------------------------------------------------------

The XML data binding into C++ is done using CodeSynthesis-XSD 
data binding compiler. The compiler produces the matml31.hxx, 
matml31.cxx files. Add these to your project file.

Place the XML Schema Definition file matml31.xsd in the
same directory as the xml data (*.xml).

The xerces-c parsing libraries should be linked in your project. For Windows adding 
xerces-c_3_1.dll and xerces-c_3_1D.dll to the library paths would do it.

With these files above, the user can perform C++ material calculations.

The MatML_Editor is the GUI for the purpose of providing an
input, or output, to these C++ material calculations or used
on its own as a MatML Editor.


Create GUIs using wxWidgets
--------------------------

As per the wxWidgets DECLARE_APP and IMPLEMENT_APP macros, class 
bellshire::BT_MatML_App defines the entry point for the console application.

bellshire::BT_MatML_App::OnInit function calls for the creation of the class 
bellshire::MaterialFrame, which is the main GUI class for the application.

bellshire::MaterialFrame constructor 
bellshire::MaterialFrameBase::MaterialFrameBase then calls for the creation 
of all the different MatML GUI classes via the class bellshire::GUI.

The class bellshire::GUI constructor bellshire::GUI::GUI(wxWindow* parent),
calls for the creation of the individual MatML GUIs, such as class
bellshire::MatML_Doc_GUI.

The individual MatML GUIs, such as class bellshire::MatML_Doc_GUI_Base 
constructor bellshire::MatML_Doc_GUI_Base::MatML_Doc_GUI_Base,
then create the final GUI for the associated MatML data class, such as
MatML_Doc. See the table below for the MatML data and the associated
MatML GUI classes.

The base classes, such as bellshire::MaterialFrameBase and the individual
MatML GUIs, such as bellshire::MatML_Doc_GUI_Base, contain the creation
of the GUIs, virtual Event Handler Functions, and binding the Event Handler
Functions.

The derived classes, such as bellshire::MaterialFrame and the individual 
MatML GUIs, such as bellshire::MatML_Doc_GUI, contain the overwriting of
the Event Handler Functions occuring in the base.

It should also be noted that not all _instances_ of MatML data have MatML GUIs
associated with them, but all _classes_ of MatML data do. This means that 
changing MatML data will require showing, and updating, the MatML GUIs to 
show the new MatML data.

The naming MatML data class and associated MatML GUI classes is as such,

MatML data					| MatML GUI
----------------------------|-------------------------
 Associate					| bellshire::Associate_GUI
 AssociationDetails			| bellshire::AssociationDetails_GUI
 BulkDetails				| bellshire::BulkDetails_GUI
 Characterization			| bellshire::Characterization_GUI
 ChemicalComposition		| bellshire::ChemicalComposition_GUI
 Class						| bellshire::Class_GUI
 ComponentDetails			| bellshire::ComponentDetails_GUI
 Compound					| bellshire::Compound_GUI
 Concentration				| bellshire::Concentration_GUI
 DataFormat					| bellshire::DataFormat_GUI
 DimensionalDetails			| bellshire::DimensionalDetails_GUI
 Element					| bellshire::Element_GUI
 Form						| bellshire::Form_GUI
 Formula					| bellshire::Formula_GUI
 Geometry					| bellshire::Geometry_GUI
 Glossary					| bellshire::Glossary_GUI
 GlossaryTerm				| bellshire::GlossaryTerm_GUI
 Graphs						| bellshire::Graphs_GUI
 Material					| bellshire::Material_GUI
 Metadata					| bellshire::Metadata_GUI
 Name						| bellshire::Name_GUI
 Notes						| bellshire::Notes_GUI
 ParameterValue				| bellshire::ParameterValue_GUI
 PhaseComposition			| bellshire::PhaseComposition_GUI
 ProcessingDetails			| bellshire::ProcessingDetails_GUI
 PropertyData				| bellshire::PropertyData_GUI
 Qualifier					| bellshire::Qualifier_GUI
 Relationship				| bellshire::Relationship_GUI
 Source						| bellshire::Source_GUI
 Specification				| bellshire::Specification_GUI
 Uncertainty				| bellshire::Uncertainty_GUI
 Unit						| bellshire::Unit_GUI
 Unitless					| bellshire::Unitless_GUI
 Units						| bellshire::Units_GUI
 Value						| bellshire::Value_GUI
 AuthorityDetails			| bellshire::AuthorityDetails_GUI
 DataSourceDetails			| bellshire::DataSourceDetails_GUI
 MeasurementTechniqueDetails| bellshire::MeasurementTechniqueDetails_GUI
 ParameterDetails			| bellshire::ParameterDetails_GUI
 PropertyDetails			| bellshire::PropertyDetails_GUI
 SourceDetails				| bellshire::SourceDetails_GUI
 SpecimenDetails			| bellshire::SpecimenDetails_GUI
 TestConditionDetails		| bellshire::TestConditionDetails_GUI
 ChemicalElementSymbol		| bellshire::ChemicalElementSymbol_GUI
 CurrencyCode				| bellshire::CurrencyCode_GUI
 MatML_Doc					| bellshire::MatML_Doc_GUI
 ParentMaterial				| bellshire::ParentMaterial_GUI
 Symbol						| bellshire::Symbol_GUI
 Graph						| bellshire::Graph_GUI
 Data						| bellshire::Data_GUI
 Data1						| bellshire::Data1_GUI
 delimiter					| bellshire::delimiter_GUI[not implemented]
 Scale						| bellshire::Scale_GUI
 Definition                 | bellshire::Definition_GUI *
 Abbreviation               | bellshire::Abbreviation_GUI *
 Synonym                    | bellshire::Synonym_GUI *
 Shape                      | bellshire::Shape_GUI *
 Dimensions                 | bellshire::Dimensions_GUI *
 Orientation                | bellshire::Orientation_GUI * 
 Result                     | bellshire::Result_GUI *
 Description                | bellshire::Description_GUI[not implemented]
 ParentSubClass             | bellshire::ParentSubClass_GUI[not implemented]
 * used BOOST_STRONG_TYPEDEF to implement as a strong type.


Polymorphically bind the MatML XML data to the wxWidgets GUIs
------------------------------------------------------------

Because the not all _instances_ of MatML data have MatML GUIs associated
with them, but all _classes_ of MatML data do, the MatML Editor relies on
polymorphic functions to select the appropriate class type to operate on.

The polymorphic functions uses boost::any pointers. The 
bellshire::TreeCtrlSorted, a derivative of wxTreeCtrl, stores
user data in each of its tree elements. Using this functionality the editor
stores data such as the bellshire::MatMLTreeItemData which contains
the boost::any pointer.

The bellshire::TreeCtrlSorted mimics the tree structure of the MatML_data
and allows the user data to be pulled from the tree elements and used.

After the user data is pulled the a given MatML data`s class typeid 
is compared to the boost::any.type. When the comparison 
matches, a function is either called, or the data is boost::any_cast back
into the MatML data pointer for further processing.

When the MatML data structure is changed the bellshire::TreeCtrlSorted is
recreated once again mimicking the MatML data structure.

An example is a function for updating of the MatML GUIs,

void bellshire::GUI::Update_GUI(::boost::any anyptr, ::boost::shared_ptr<MatML_Doc> doc)

this will Update the appropriate GUI depending on the type of MatML data pointer
the ::boost::any pointer caste into.

Another, function is a function showing the context menu,

void bellshire::MaterialFrame::ShowContextMenu(wxTreeItemId id, const wxPoint& pt)

it will create a context menu showing possible selections depending on the
bellshire::MatMLTreeItemData (has a member of boost::any pointer) selected.
