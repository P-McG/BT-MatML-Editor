/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_GUI.h
// Purpose:     Headers of GUI interfaces.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_PropertyDetails_Display_GUI.h"
#include "BT_MatML_MeasurementTechniqueDetails_Display_GUI.h"
#include "BT_MatML_DataSourceDetails_Display_GUI.h"
#include "BT_MatML_SpecimenDetails_Display_GUI.h"
#include "BT_MatML_TestConditionDetails_Display_GUI.h"
#include "BT_MatML_ParameterDetails_Display_GUI.h"
#include "BT_MatML_AuthorityDetails_Display_GUI.h"
#include "BT_MatML_SourceDetails_Display_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_Intro_GUI.h"
#include "BT_MatML_Graph_GUI.h"
#include "BT_MatML_MatML_Doc_GUI.h"
#include "BT_MatML_Material_GUI.h"
#include "BT_MatML_Associate_GUI.h"
#include "BT_MatML_AssociationDetails_GUI.h"
#include "BT_MatML_AuthorityDetails_GUI.h"
#include "BT_MatML_BulkDetails_GUI.h"
#include "BT_MatML_Characterization_GUI.h"
#include "BT_MatML_ChemicalComposition_GUI.h"
#include "BT_MatML_ChemicalElementSymbol_GUI.h"
#include "BT_MatML_Class_GUI.h"
#include "BT_MatML_ParentMaterial_GUI.h"
#include "BT_MatML_ParentSubClass_GUI.h"
#include "BT_MatML_ComponentDetails_GUI.h"
#include "BT_MatML_Compound_GUI.h"
#include "BT_MatML_Concentration_GUI.h"
#include "BT_MatML_CurrencyCode_GUI.h"
#include "BT_MatML_DataSourceDetails_GUI.h"
#include "BT_MatML_DimensionalDetails_GUI.h"
#include "BT_MatML_Element_GUI.h"
#include "BT_MatML_Form_GUI.h"
#include "BT_MatML_Formula_GUI.h"
#include "BT_MatML_Geometry_GUI.h"
#include "BT_MatML_Shape_GUI.h"
#include "BT_MatML_Dimensions_GUI.h"
#include "BT_MatML_Orientation_GUI.h"
#include "BT_MatML_Glossary_GUI.h"
#include "BT_MatML_GlossaryTerm_GUI.h"
#include "BT_MatML_Definition_GUI.h"
#include "BT_MatML_Abbreviation_GUI.h"
#include "BT_MatML_Symbol_GUI.h"
#include "BT_MatML_Synonym_GUI.h"
#include "BT_MatML_Graphs_GUI.h"
#include "BT_MatML_MeasurementTechniqueDetails_GUI.h"
#include "BT_MatML_Metadata_GUI.h"
#include "BT_MatML_Name_GUI.h"
#include "BT_MatML_Notes_GUI.h"
#include "BT_MatML_ParameterDetails_GUI.h"
#include "BT_MatML_ParameterValue_GUI.h"
#include "BT_MatML_Data_GUI.h"
#include "BT_MatML_PhaseComposition_GUI.h"
#include "BT_MatML_ProcessingDetails_GUI.h"
#include "BT_MatML_Result_GUI.h"
#include "BT_MatML_Relationship_GUI.h"
#include "BT_MatML_PropertyData_GUI.h"
#include "BT_MatML_Data1_GUI.h"
#include "BT_MatML_PropertyDetails_GUI.h"
#include "BT_MatML_Qualifier_GUI.h"
#include "BT_MatML_Source_GUI.h"
#include "BT_MatML_SourceDetails_GUI.h"
#include "BT_MatML_Specification_GUI.h"
#include "BT_MatML_SpecimenDetails_GUI.h"
#include "BT_MatML_TestConditionDetails_GUI.h"
#include "BT_MatML_Uncertainty_GUI.h"
#include "BT_MatML_Scale_GUI.h"
#include "BT_MatML_Unit_GUI.h"
#include "BT_MatML_Unitless_GUI.h"
#include "BT_MatML_Units_GUI.h"
#include "BT_MatML_Value_GUI.h"

namespace bellshire {

	class Intro_GUI;
	class MatML_Doc_GUI;
	class Material_GUI;
	class Associate_GUI;
	class AssociationDetails_GUI;
	class AuthorityDetails_GUI;
	class BulkDetails_GUI;
	class Characterization_GUI;
	class ChemicalComposition_GUI;
	class ChemicalElementSymbol_GUI;
	class Class_GUI;
	class ParentMaterial_GUI;
	class ParentSubClass_GUI;
	class ComponentDetails_GUI;
	class Compound_GUI;
	class Concentration_GUI;
	class CurrencyCode_GUI;
	class DataSourceDetails_GUI;
	class DimensionalDetails_GUI;
	class Element_GUI;
	class Symbol_GUI;
	class Form_GUI;
	class Formula_GUI;
	class Geometry_GUI;
	class Shape_GUI;
	class Dimensions_GUI;
	class Orientation_GUI;
	class Glossary_GUI;
	class GlossaryTerm_GUI;
	class Definition_GUI;
	class Abbreviation_GUI;
	class Synonym_GUI;
	class Graphs_GUI;
	class Graph_GUI;
	class MeasurementTechniqueDetails_GUI;
	class Metadata_GUI;
	class Name_GUI;
	class Notes_GUI;
	class ParameterDetails_GUI;
	class ParameterValue_GUI;
	class Data_GUI;
	class PhaseComposition_GUI;
	class ProcessingDetails_GUI;
	class Result_GUI;
	class Relationship_GUI;
	class PropertyData_GUI;
	class Data1_GUI;
	class PropertyDetails_GUI;
	class Qualifier_GUI;
	class Source_GUI;
	class SourceDetails_GUI;
	class Specification_GUI;
	class SpecimenDetails_GUI;
	class TestConditionDetails_GUI;
	class Uncertainty_GUI;
	class Scale_GUI;
	class Unit_GUI;
	class Unitless_GUI;
	class Units_GUI;
	class Value_GUI;

	/// MatML_GUI class
	/// <summary>
	/// GUI for each of the MatML classes
	/// </summary>
	/// **EACH** of the MatML **CLASSES** have a GUIs associated with it.\n 
	/// However, **INDIVIDUAL INSTANCES** of MatML classes do **NOT** have a GUI associated with them, because
	/// MatML Instances **SHARE** the MatML GUIs among the different instances.\n
	class GUI
	{
	public:
		Intro_GUI* m_Intro_GUI;
		MatML_Doc_GUI* m_MatML_Doc_GUI;
		Material_GUI* m_Material_GUI;
		Associate_GUI* m_Associate_GUI;
		AssociationDetails_GUI* m_AssociationDetails_GUI;
		AuthorityDetails_GUI* m_AuthorityDetails_GUI;
		BulkDetails_GUI* m_BulkDetails_GUI;
		Characterization_GUI* m_Characterization_GUI;
		ChemicalComposition_GUI* m_ChemicalComposition_GUI;
		ChemicalElementSymbol_GUI* m_ChemicalElementSymbol_GUI;
		Class_GUI* m_Class_GUI;
		ParentMaterial_GUI* m_ParentMaterial_GUI;
		ParentSubClass_GUI* m_ParentSubClass_GUI;
		ComponentDetails_GUI* m_ComponentDetails_GUI;
		Compound_GUI* m_Compound_GUI;
		Concentration_GUI* m_Concentration_GUI;
		CurrencyCode_GUI* m_CurrencyCode_GUI;
		DataSourceDetails_GUI* m_DataSourceDetails_GUI;
		DimensionalDetails_GUI* m_DimensionalDetails_GUI;
		Element_GUI* m_Element_GUI;
		Symbol_GUI* m_Symbol_GUI;
		Form_GUI* m_Form_GUI;
		Formula_GUI* m_Formula_GUI;
		Geometry_GUI* m_Geometry_GUI;
		Shape_GUI* m_Shape_GUI;
		Dimensions_GUI* m_Dimensions_GUI;
		Orientation_GUI* m_Orientation_GUI;
		Glossary_GUI* m_Glossary_GUI;
		GlossaryTerm_GUI* m_GlossaryTerm_GUI;
		Definition_GUI* m_Definition_GUI;
		Abbreviation_GUI* m_Abbreviation_GUI;
		Synonym_GUI* m_Synonym_GUI;
		Graphs_GUI* m_Graphs_GUI;
		Graph_GUI* m_Graph_GUI;
		MeasurementTechniqueDetails_GUI* m_MeasurementTechniqueDetails_GUI;
		Metadata_GUI* m_Metadata_GUI;
		Name_GUI* m_Name_GUI;
		Notes_GUI* m_Notes_GUI;
		ParameterDetails_GUI* m_ParameterDetails_GUI;
		ParameterValue_GUI* m_ParameterValue_GUI;
		Data_GUI* m_Data_GUI;
		PhaseComposition_GUI* m_PhaseComposition_GUI;
		ProcessingDetails_GUI* m_ProcessingDetails_GUI;
		Result_GUI* m_Result_GUI;
		Relationship_GUI* m_Relationship_GUI;
		PropertyData_GUI* m_PropertyData_GUI;
		Data1_GUI* m_Data1_GUI;
		PropertyDetails_GUI* m_PropertyDetails_GUI;
		Qualifier_GUI* m_Qualifier_GUI;
		Source_GUI* m_Source_GUI;
		SourceDetails_GUI* m_SourceDetails_GUI;
		Specification_GUI* m_Specification_GUI;
		SpecimenDetails_GUI* m_SpecimenDetails_GUI;
		TestConditionDetails_GUI* m_TestConditionDetails_GUI;
		Uncertainty_GUI* m_Uncertainty_GUI;
		Scale_GUI* m_Scale_GUI;
		Unit_GUI* m_Unit_GUI;
		Unitless_GUI* m_Unitless_GUI;
		Units_GUI* m_Units_GUI;
		Value_GUI* m_Value_GUI;

		GUI(); /*!< Constructor */
		GUI(wxWindow* parent); /*!< Main Constructor */
		virtual ~GUI();/*!< Destructor */

		void SetSizer(wxFlexGridSizer*& fgSizer);/*!< Sets the window to have the given layout sizer. */

		template<class MatML_Class, class GUI_Class>
		bool Update_individual_GUI(::boost::any anyptr, GUI_Class GUI);/*!< Updates the individual MatML GUI */

		template<class MatML_Class, class GUI_Class>
		bool Update_individual_GUI(::boost::any anyptr, GUI_Class GUI, ::boost::shared_ptr<MatML_Doc> doc);/*!< Updates the individual MatML GUI with information from the doc */

		void Update_GUI(::boost::any anyptr, ::boost::shared_ptr<MatML_Doc> doc);/*!< Update **all** the individual MatML GUI */

		void HideAllPanels();/*!< Hide all the MatML GUI panels */

		void SetEvtHandlerVar(TreeCtrlSorted* MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc> doc);/*!<Set the Event Handler functions variable */
	};

}//bellshire