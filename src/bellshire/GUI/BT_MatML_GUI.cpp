#include "pch.h"
#include "bellshire/GUI/BT_MatML_GUI.h"

using namespace bellshire::GUI;

/// Constructor
/// 
/// <summary>
/// 
/// </summary>
GUI::GUI()
	: m_Intro_GUI(nullptr),
	m_MatML_Doc_GUI(nullptr),
	m_Material_GUI(nullptr),
	m_Associate_GUI(nullptr),
	m_AssociationDetails_GUI(nullptr),
	m_AuthorityDetails_GUI(nullptr),
	m_BulkDetails_GUI(nullptr),
	m_Characterization_GUI(nullptr),
	m_ChemicalComposition_GUI(nullptr),
	m_ChemicalElementSymbol_GUI(nullptr),
	m_Class_GUI(nullptr),
	m_Subclass_GUI(nullptr),
	m_Subclass1_GUI(nullptr),
	m_ParentMaterial_GUI(nullptr),
	m_ParentSubClass_GUI(nullptr),
	m_ComponentDetails_GUI(nullptr),
	m_Compound_GUI(nullptr),
	m_Concentration_GUI(nullptr),
	m_CurrencyCode_GUI(nullptr),
	m_DataSourceDetails_GUI(nullptr),
	m_DimensionalDetails_GUI(nullptr),
	m_Element_GUI(nullptr),
	m_Symbol_GUI(nullptr),
	m_Form_GUI(nullptr),
	m_Formula_GUI(nullptr),
	m_Geometry_GUI(nullptr),
	m_Shape_GUI(nullptr),
	m_Dimensions_GUI(nullptr),
	m_Orientation_GUI(nullptr),
	m_Glossary_GUI(nullptr),
	m_GlossaryTerm_GUI(nullptr),
	m_Definition_GUI(nullptr),
	m_Abbreviation_GUI(nullptr),
	m_Synonym_GUI(nullptr),
	m_Graphs_GUI(nullptr),
	m_Graph_GUI(nullptr),
	m_MeasurementTechniqueDetails_GUI(nullptr),
	m_Metadata_GUI(nullptr),
	m_Name_GUI(nullptr),
	m_Notes_GUI(nullptr),
	m_ParameterDetails_GUI(nullptr),
	m_ParameterValue_GUI(nullptr),
	m_Data_GUI(nullptr),
	m_PhaseComposition_GUI(nullptr),
	m_ProcessingDetails_GUI(nullptr),
	m_Result_GUI(nullptr),
	m_Relationship_GUI(nullptr),
	m_PropertyData_GUI(nullptr),
	m_Data1_GUI(nullptr),
	m_PropertyDetails_GUI(nullptr),
	m_Qualifier_GUI(nullptr),
	m_Source_GUI(nullptr),
	m_SourceDetails_GUI(nullptr),
	m_Specification_GUI(nullptr),
	m_SpecimenDetails_GUI(nullptr),
	m_TestConditionDetails_GUI(nullptr),
	m_Uncertainty_GUI(nullptr),
	m_Scale_GUI(nullptr),
	m_Unit_GUI(nullptr),
	m_Unitless_GUI(nullptr),
	m_Units_GUI(nullptr),
	m_Value_GUI(nullptr)
{}

/// Main Constructor
/// 
/// <summary>
/// Initializes with new individual MatML GUIs
/// </summary>
/// <param name="parent"></param>
GUI::GUI(wxWindow* parent)
	:m_Intro_GUI(std::make_shared<Intro_GUI>(parent)),
	m_MatML_Doc_GUI(std::make_shared < MatML_Doc_GUI>(parent)),
	m_Material_GUI(std::make_shared < Material_GUI>(parent)),
	m_Associate_GUI(std::make_shared < Associate_GUI>(parent)),/*somethings odd with this*/
	m_AssociationDetails_GUI(std::make_shared < AssociationDetails_GUI>(parent)),
	m_AuthorityDetails_GUI(std::make_shared < AuthorityDetails_GUI>(parent)),
	m_BulkDetails_GUI(std::make_shared < BulkDetails_GUI>(parent)),
	m_Characterization_GUI(std::make_shared < Characterization_GUI>(parent)),
	m_ChemicalComposition_GUI(std::make_shared < ChemicalComposition_GUI>(parent)),
	m_ChemicalElementSymbol_GUI(std::make_shared < ChemicalElementSymbol_GUI>(parent)),
	m_Class_GUI(std::make_shared < Class_GUI>(parent)),
	m_Subclass_GUI(std::make_shared < Subclass_GUI>(parent)),
	m_Subclass1_GUI(std::make_shared < Subclass1_GUI>(parent)),
	m_ParentMaterial_GUI(std::make_shared < ParentMaterial_GUI>(parent)),
	m_ParentSubClass_GUI(std::make_shared < ParentSubClass_GUI>(parent)),
	m_ComponentDetails_GUI(std::make_shared < ComponentDetails_GUI>(parent)),
	m_Compound_GUI(std::make_shared < Compound_GUI>(parent)),
	m_Concentration_GUI(std::make_shared < Concentration_GUI>(parent)),
	m_CurrencyCode_GUI(std::make_shared < CurrencyCode_GUI>(parent)),
	m_DataSourceDetails_GUI(std::make_shared < DataSourceDetails_GUI>(parent)),
	m_DimensionalDetails_GUI(std::make_shared < DimensionalDetails_GUI>(parent)),
	m_Element_GUI(std::make_shared < Element_GUI>(parent)),
	m_Symbol_GUI(std::make_shared < Symbol_GUI>(parent)),
	m_Form_GUI(std::make_shared < Form_GUI>(parent)),
	m_Formula_GUI(std::make_shared < Formula_GUI>(parent)),
	m_Geometry_GUI(std::make_shared < Geometry_GUI>(parent)),
	m_Shape_GUI(std::make_shared < Shape_GUI>(parent)),
	m_Dimensions_GUI(std::make_shared < Dimensions_GUI>(parent)),
	m_Orientation_GUI(std::make_shared < Orientation_GUI>(parent)),
	m_Glossary_GUI(std::make_shared < Glossary_GUI>(parent)),
	m_GlossaryTerm_GUI(std::make_shared < GlossaryTerm_GUI>(parent)),
	m_Definition_GUI(std::make_shared < Definition_GUI>(parent)),
	m_Abbreviation_GUI(std::make_shared < Abbreviation_GUI>(parent)),
	m_Synonym_GUI(std::make_shared < Synonym_GUI>(parent)),
	m_Graphs_GUI(std::make_shared < Graphs_GUI>(parent)),
	m_Graph_GUI(std::make_shared < Graph_GUI>(parent)),
	m_MeasurementTechniqueDetails_GUI(std::make_shared < MeasurementTechniqueDetails_GUI>(parent)),
	m_Metadata_GUI(std::make_shared < Metadata_GUI>(parent)),
	m_Name_GUI(std::make_shared < Name_GUI>(parent)),
	m_Notes_GUI(std::make_shared < Notes_GUI>(parent)),
	m_ParameterDetails_GUI(std::make_shared < ParameterDetails_GUI>(parent)),
	m_ParameterValue_GUI(std::make_shared < ParameterValue_GUI>(parent)),
	m_Data_GUI(std::make_shared < Data_GUI>(parent)),
	m_PhaseComposition_GUI(std::make_shared < PhaseComposition_GUI>(parent)),
	m_ProcessingDetails_GUI(std::make_shared < ProcessingDetails_GUI>(parent)),
	m_Result_GUI(std::make_shared < Result_GUI>(parent)),
	m_Relationship_GUI(std::make_shared < Relationship_GUI>(parent)),
	m_PropertyData_GUI(std::make_shared < PropertyData_GUI>(parent)),
	m_Data1_GUI(std::make_shared < Data1_GUI>(parent)),
	m_PropertyDetails_GUI(std::make_shared < PropertyDetails_GUI>(parent)),
	m_Qualifier_GUI(std::make_shared < Qualifier_GUI>(parent)),
	m_Source_GUI(std::make_shared < Source_GUI>(parent)),
	m_SourceDetails_GUI(std::make_shared < SourceDetails_GUI>(parent)),
	m_Specification_GUI(std::make_shared < Specification_GUI>(parent)),
	m_SpecimenDetails_GUI(std::make_shared < SpecimenDetails_GUI>(parent)),
	m_TestConditionDetails_GUI(std::make_shared < TestConditionDetails_GUI>(parent)),
	m_Uncertainty_GUI(std::make_shared < Uncertainty_GUI>(parent)),
	m_Scale_GUI(std::make_shared < Scale_GUI>(parent)),
	m_Unit_GUI(std::make_shared < Unit_GUI>(parent)),
	m_Unitless_GUI(std::make_shared < Unitless_GUI>(parent)),
	m_Units_GUI(std::make_shared < Units_GUI>(parent)),
	m_Value_GUI(std::make_shared < Value_GUI>(parent))
	{}

/// Destructor
/// 
/// <summary>
/// Destroys individual MatML GUIs
/// </summary>
GUI::~GUI()
{}


/// SetSizer
/// Adds the GUIs to the controlling Sizer.
/// <summary>
/// Assumes the same sizer for all the MatML GUIs and that the panels are placed
/// adjacent. Panels of the MatML GUIs are hidden and shown on updating
/// with data.
/// </summary>
/// <param name="fgSizer"></param>
void GUI::SetSizer(wxFlexGridSizer*& fgSizer)
{
	fgSizer->Add(m_Intro_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_MatML_Doc_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Material_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Associate_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_AssociationDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_AuthorityDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_BulkDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Characterization_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ChemicalComposition_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ChemicalElementSymbol_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Class_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Subclass_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Subclass1_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ParentMaterial_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ParentSubClass_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ComponentDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Compound_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Concentration_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_CurrencyCode_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_DataSourceDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_DimensionalDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Element_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Symbol_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Form_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Formula_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Geometry_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Shape_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Dimensions_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Orientation_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Glossary_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_GlossaryTerm_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Definition_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Abbreviation_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Synonym_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Graphs_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Graph_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_MeasurementTechniqueDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Metadata_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Name_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Notes_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ParameterDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ParameterValue_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Data_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_PhaseComposition_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_ProcessingDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Result_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Relationship_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_PropertyData_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Data1_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_PropertyDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Qualifier_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Source_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_SourceDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Specification_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_SpecimenDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_TestConditionDetails_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Uncertainty_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Scale_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Unit_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Unitless_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Units_GUI->get(), 1, wxEXPAND | wxALL, 5);
	fgSizer->Add(m_Value_GUI->get(), 1, wxEXPAND | wxALL, 5);
}


/// <summary>
/// Template for updating the individual GUI
/// based on the boost::any pointer caste type.
/// </summary>
/// <typeparam name="GUI_Class"></typeparam>
/// <typeparam name="MatML_Class"></typeparam>
/// <param name="anyptr"></param>
/// <param name="GUI"></param>
/// <returns></returns>
template<class MatML_Class, class GUI_Class>
bool GUI::Update_individual_GUI(::boost::any anyptr, observer_ptr<GUI_Class> GUI)
{
	bool rtn = false;
	try {
		if (anyptr.type() == typeid(observer_ptr<MatML_Class>)) {
			auto derived = boost::any_cast<observer_ptr<MatML_Class>>(anyptr);
			if (derived) {
				GUI->Update(derived);
				rtn = true;
			}
			else rtn = false;
		}
	}
	catch (const boost::bad_any_cast&) { rtn = false; }

	return rtn;
}

/// <summary>
/// Template for updating the individual GUI
/// based on the boost::any pointer caste type. 
/// For MatML GUIs that require access to MatML_Doc pointer
/// for additional data.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="GUI_Class"></typeparam>
/// <param name="anyptr"></param>
/// <param name="GUI"></param>
/// <param name="doc"></param>
/// <returns></returns>
template<class MatML_Class, class GUI_Class>
bool GUI::Update_individual_GUI(::boost::any anyptr, observer_ptr<GUI_Class> GUI, observer_ptr<MatML_Doc> doc)
{
	bool rtn = false;
	try {
		if (anyptr.type() == typeid(observer_ptr<MatML_Class>)) {
			auto const derived = boost::any_cast<observer_ptr<MatML_Class> >(anyptr);
			
			GUI->Update(derived, doc);
			rtn = true;
		}
	}
	catch (const boost::bad_any_cast&) { rtn = false; }

	return rtn;
}

/// <summary>
/// Updating one of the MatML GUIs based on the boost::any pointer.
/// Polymorphic calls using the anyptr.
/// </summary>
/// <param name="anyptr"></param>
void GUI::Update_GUI(::boost::any anyptr, observer_ptr<MatML_Doc> doc)
{
	if (Update_individual_GUI< Associate, Associate_GUI>(anyptr, m_Associate_GUI.get())) goto done;
	if (Update_individual_GUI< AssociationDetails, AssociationDetails_GUI>(anyptr, m_AssociationDetails_GUI.get())) goto done;
	if (Update_individual_GUI< AuthorityDetails, AuthorityDetails_GUI>(anyptr, m_AuthorityDetails_GUI.get())) goto done;
	if (Update_individual_GUI< BulkDetails, BulkDetails_GUI>(anyptr, m_BulkDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Characterization, Characterization_GUI>(anyptr, m_Characterization_GUI.get())) goto done;
	if (Update_individual_GUI< ChemicalComposition, ChemicalComposition_GUI>(anyptr, m_ChemicalComposition_GUI.get())) goto done;
	if (Update_individual_GUI< ChemicalElementSymbol, ChemicalElementSymbol_GUI>(anyptr, m_ChemicalElementSymbol_GUI.get())) goto done;
	if (Update_individual_GUI< Class, Class_GUI>(anyptr, m_Class_GUI.get())) goto done;
	if (Update_individual_GUI< Subclass, Subclass_GUI>(anyptr, m_Subclass_GUI.get())) goto done;
	if (Update_individual_GUI< Subclass1, Subclass1_GUI>(anyptr, m_Subclass1_GUI.get())) goto done;
	if (Update_individual_GUI< ParentMaterial, ParentMaterial_GUI>(anyptr, m_ParentMaterial_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< ParentSubClass, ParentSubClass_GUI>(anyptr, m_ParentSubClass_GUI.get())) goto done;
	if (Update_individual_GUI< ComponentDetails, ComponentDetails_GUI>(anyptr, m_ComponentDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Compound, Compound_GUI>(anyptr, m_Compound_GUI.get())) goto done;
	if (Update_individual_GUI< Concentration, Concentration_GUI>(anyptr, m_Concentration_GUI.get())) goto done;
	if (Update_individual_GUI< CurrencyCode, CurrencyCode_GUI>(anyptr, m_CurrencyCode_GUI.get())) goto done;
	if (Update_individual_GUI< DataSourceDetails, DataSourceDetails_GUI>(anyptr, m_DataSourceDetails_GUI.get())) goto done;
	if (Update_individual_GUI< DimensionalDetails, DimensionalDetails_GUI>(anyptr, m_DimensionalDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Element, Element_GUI>(anyptr, m_Element_GUI.get())) goto done;
	if (Update_individual_GUI< Symbol, Symbol_GUI>(anyptr, m_Symbol_GUI.get())) goto done;
	if (Update_individual_GUI< Form, Form_GUI>(anyptr, m_Form_GUI.get())) goto done;
	//if (Update_individual_GUI< Description, Description_GUI>(anyptr, m_Description_GUI.get())) goto done;
	if (Update_individual_GUI< Formula, Formula_GUI>(anyptr, m_Formula_GUI.get())) goto done;
	if (Update_individual_GUI< Geometry, Geometry_GUI>(anyptr, m_Geometry_GUI.get())) goto done;
	if (Update_individual_GUI< Shape, Shape_GUI>(anyptr, m_Shape_GUI.get())) goto done;
	if (Update_individual_GUI< Dimensions, Dimensions_GUI>(anyptr, m_Dimensions_GUI.get())) goto done;
	if (Update_individual_GUI< Orientation, Orientation_GUI>(anyptr, m_Orientation_GUI.get())) goto done;
	if (Update_individual_GUI< Glossary, Glossary_GUI>(anyptr, m_Glossary_GUI.get())) goto done;
	if (Update_individual_GUI< GlossaryTerm, GlossaryTerm_GUI>(anyptr, m_GlossaryTerm_GUI.get())) goto done;
	if (Update_individual_GUI< Definition, Definition_GUI>(anyptr, m_Definition_GUI.get())) goto done;
	if (Update_individual_GUI< Abbreviation, Abbreviation_GUI>(anyptr, m_Abbreviation_GUI.get())) goto done;
	if (Update_individual_GUI< Synonym, Synonym_GUI>(anyptr, m_Synonym_GUI.get())) goto done;
	if (Update_individual_GUI< Graphs, Graphs_GUI>(anyptr, m_Graphs_GUI.get())) goto done;
	if (Update_individual_GUI< Graph, Graph_GUI>(anyptr, m_Graph_GUI.get())) goto done;
	if (Update_individual_GUI< Material, Material_GUI>(anyptr, m_Material_GUI.get())) goto done;
	//if (Update_individual_GUI< MatML_Doc, MatML_Doc_GUI>(anyptr, m_MatML_Doc_GUI.get())) goto done;
	if (Update_individual_GUI< MeasurementTechniqueDetails, MeasurementTechniqueDetails_GUI>(anyptr, m_MeasurementTechniqueDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Metadata, Metadata_GUI>(anyptr, m_Metadata_GUI.get())) goto done;
	if (Update_individual_GUI< Name, Name_GUI>(anyptr, m_Name_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< Notes, Notes_GUI>(anyptr, m_Notes_GUI.get())) goto done;
	if (Update_individual_GUI< ParameterDetails, ParameterDetails_GUI>(anyptr, m_ParameterDetails_GUI.get())) goto done;
	if (Update_individual_GUI< ParameterValue, ParameterValue_GUI>(anyptr, m_ParameterValue_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< Data, Data_GUI>(anyptr, m_Data_GUI.get())) goto done;
	if (Update_individual_GUI< PhaseComposition, PhaseComposition_GUI>(anyptr, m_PhaseComposition_GUI.get())) goto done;
	if (Update_individual_GUI< ProcessingDetails, ProcessingDetails_GUI>(anyptr, m_ProcessingDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Result, Result_GUI>(anyptr, m_Result_GUI.get())) goto done;
	if (Update_individual_GUI< PropertyData, PropertyData_GUI>(anyptr, m_PropertyData_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< Data1, Data1_GUI>(anyptr, m_Data1_GUI.get())) goto done;
	if (Update_individual_GUI< PropertyDetails, PropertyDetails_GUI>(anyptr, m_PropertyDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Qualifier, Qualifier_GUI>(anyptr, m_Qualifier_GUI.get())) goto done;
	if (Update_individual_GUI< Relationship, Relationship_GUI>(anyptr, m_Relationship_GUI.get())) goto done;
	if (Update_individual_GUI< Source, Source_GUI>(anyptr, m_Source_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< SourceDetails, SourceDetails_GUI>(anyptr, m_SourceDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Specification, Specification_GUI>(anyptr, m_Specification_GUI.get(), doc)) goto done;
	if (Update_individual_GUI< SpecimenDetails, SpecimenDetails_GUI>(anyptr, m_SpecimenDetails_GUI.get())) goto done;
	if (Update_individual_GUI< TestConditionDetails, TestConditionDetails_GUI>(anyptr, m_TestConditionDetails_GUI.get())) goto done;
	if (Update_individual_GUI< Uncertainty, Uncertainty_GUI>(anyptr, m_Uncertainty_GUI.get())) goto done;
	if (Update_individual_GUI< Scale, Scale_GUI>(anyptr, m_Scale_GUI.get())) goto done;
	if (Update_individual_GUI< Unit, Unit_GUI>(anyptr, m_Unit_GUI.get())) goto done;
	if (Update_individual_GUI< Unitless, Unitless_GUI>(anyptr, m_Unitless_GUI.get())) goto done;
	if (Update_individual_GUI< Units, Units_GUI>(anyptr, m_Units_GUI.get())) goto done;
	if (Update_individual_GUI< Value, Value_GUI>(anyptr, m_Value_GUI.get())) goto done;

	
	m_MatML_Doc_GUI->Update();//default update

done:;
}

/// Hide all GUI Panels
///
/// <summary>
/// 
/// </summary>
void GUI::HideAllPanels()
{
	m_Intro_GUI->ShowGUI(false);
	m_MatML_Doc_GUI->ShowGUI(false);
	m_Associate_GUI->ShowGUI(false);
	m_AssociationDetails_GUI->ShowGUI(false);
	m_AuthorityDetails_GUI->ShowGUI(false);
	m_BulkDetails_GUI->ShowGUI(false);
	m_Characterization_GUI->ShowGUI(false);
	m_ChemicalComposition_GUI->ShowGUI(false);
	m_ChemicalElementSymbol_GUI->ShowGUI(false);
	m_Class_GUI->ShowGUI(false);
	m_Subclass_GUI->ShowGUI(false);
	m_Subclass1_GUI->ShowGUI(false);
	m_ParentMaterial_GUI->ShowGUI(false);
	m_ParentSubClass_GUI->ShowGUI(false);
	m_Compound_GUI->ShowGUI(false);
	m_ComponentDetails_GUI->ShowGUI(false);
	m_Concentration_GUI->ShowGUI(false);
	m_CurrencyCode_GUI->ShowGUI(false);
	m_DataSourceDetails_GUI->ShowGUI(false);
	m_DimensionalDetails_GUI->ShowGUI(false);
	m_Element_GUI->ShowGUI(false);
	m_Symbol_GUI->ShowGUI(false);
	m_Form_GUI->ShowGUI(false);
	m_Formula_GUI->ShowGUI(false);
	m_Geometry_GUI->ShowGUI(false);
	m_Shape_GUI->ShowGUI(false);
	m_Dimensions_GUI->ShowGUI(false);
	m_Orientation_GUI->ShowGUI(false);
	m_Glossary_GUI->ShowGUI(false);
	m_GlossaryTerm_GUI->ShowGUI(false);
	m_Definition_GUI->ShowGUI(false);
	m_Abbreviation_GUI->ShowGUI(false);
	m_Synonym_GUI->ShowGUI(false);
	m_Graphs_GUI->ShowGUI(false);
	m_Graph_GUI->ShowGUI(false);
	m_Material_GUI->ShowGUI(false);
	m_MeasurementTechniqueDetails_GUI->ShowGUI(false);
	m_Metadata_GUI->ShowGUI(false);
	m_Name_GUI->ShowGUI(false);
	m_Notes_GUI->ShowGUI(false);
	m_ParameterDetails_GUI->ShowGUI(false);
	m_ParameterValue_GUI->ShowGUI(false);
	m_Data_GUI->ShowGUI(false);
	m_PhaseComposition_GUI->ShowGUI(false);
	m_ProcessingDetails_GUI->ShowGUI(false);
	m_Result_GUI->ShowGUI(false);
	m_Relationship_GUI->ShowGUI(false);
	m_PropertyData_GUI->ShowGUI(false);
	m_Data1_GUI->ShowGUI(false);
	m_PropertyDetails_GUI->ShowGUI(false);
	m_Qualifier_GUI->ShowGUI(false);
	m_Source_GUI->ShowGUI(false);
	m_SourceDetails_GUI->ShowGUI(false);
	m_Specification_GUI->ShowGUI(false);
	m_SpecimenDetails_GUI->ShowGUI(false);
	m_TestConditionDetails_GUI->ShowGUI(false);
	m_Uncertainty_GUI->ShowGUI(false);
	m_Scale_GUI->ShowGUI(false);
	m_Unit_GUI->ShowGUI(false);
	m_Unitless_GUI->ShowGUI(false);
	m_Units_GUI->ShowGUI(false);
	m_Value_GUI->ShowGUI(false);
}

/// Set Event Handler Variable
/// <summary>
/// Sets the variables for the Event Handlers related to the MatML_GUIs.
/// These variables are members of the MaterialFrame class.
/// Need to be run before using MatML_GUIs events.
/// </summary>
void GUI::SetEvtHandlerVar(TreeCtrlSorted* MatMLTreeCtrl, observer_ptr<MatML_Doc> doc)
{
	m_MatML_Doc_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Material_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Associate_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_AssociationDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_AuthorityDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_BulkDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Characterization_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ChemicalComposition_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ChemicalElementSymbol_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Class_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Subclass_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Subclass1_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ParentMaterial_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_ParentSubClass_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ComponentDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Compound_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Concentration_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_CurrencyCode_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_DataSourceDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_DimensionalDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Element_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Symbol_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Form_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Formula_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Geometry_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Shape_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Dimensions_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Orientation_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Glossary_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_GlossaryTerm_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Definition_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Abbreviation_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Synonym_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Graphs_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Graph_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_MeasurementTechniqueDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Metadata_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Name_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Notes_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ParameterDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_ParameterValue_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Data_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PhaseComposition_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ProcessingDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Result_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Relationship_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PropertyData_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Data1_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PropertyDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Qualifier_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Source_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_SourceDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Specification_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_SpecimenDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_TestConditionDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Uncertainty_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Scale_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Unit_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Unitless_GUI->SetEvtHandlerVar();
	m_Units_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Value_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
}