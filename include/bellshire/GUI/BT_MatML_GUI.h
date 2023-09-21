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

#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.H"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_PropertyDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_MeasurementTechniqueDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_DataSourceDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_SpecimenDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_TestConditionDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_ParameterDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_AuthorityDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_SourceDetails_Display_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_Intro_GUI.h"
#include "bellshire/GUI/BT_MatML_Graph_GUI.h"
#include "bellshire/GUI/BT_MatML_MatML_Doc_GUI.h"
#include "bellshire/GUI/BT_MatML_Material_GUI.h"
#include "bellshire/GUI/BT_MatML_Associate_GUI.h"
#include "bellshire/GUI/BT_MatML_AssociationDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_AuthorityDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_BulkDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Characterization_GUI.h"
#include "bellshire/GUI/BT_MatML_ChemicalComposition_GUI.h"
#include "bellshire/GUI/BT_MatML_ChemicalElementSymbol_GUI.h"
#include "bellshire/GUI/BT_MatML_Class_GUI.h"
#include "bellshire/GUI/BT_MatML_Subclass_GUI.h"
#include "bellshire/GUI/BT_MatML_Subclass1_GUI.h"
#include "bellshire/GUI/BT_MatML_ParentMaterial_GUI.h"
#include "bellshire/GUI/BT_MatML_ParentSubClass_GUI.h"
#include "bellshire/GUI/BT_MatML_ComponentDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Compound_GUI.h"
#include "bellshire/GUI/BT_MatML_Concentration_GUI.h"
#include "bellshire/GUI/BT_MatML_CurrencyCode_GUI.h"
#include "bellshire/GUI/BT_MatML_DataSourceDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_DimensionalDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Element_GUI.h"
#include "bellshire/GUI/BT_MatML_Form_GUI.h"
#include "bellshire/GUI/BT_MatML_Formula_GUI.h"
#include "bellshire/GUI/BT_MatML_Geometry_GUI.h"
#include "bellshire/GUI/BT_MatML_Shape_GUI.h"
#include "bellshire/GUI/BT_MatML_Dimensions_GUI.h"
#include "bellshire/GUI/BT_MatML_Orientation_GUI.h"
#include "bellshire/GUI/BT_MatML_Glossary_GUI.h"
#include "bellshire/GUI/BT_MatML_GlossaryTerm_GUI.h"
#include "bellshire/GUI/BT_MatML_Definition_GUI.h"
#include "bellshire/GUI/BT_MatML_Abbreviation_GUI.h"
#include "bellshire/GUI/BT_MatML_Symbol_GUI.h"
#include "bellshire/GUI/BT_MatML_Synonym_GUI.h"
#include "bellshire/GUI/BT_MatML_Graphs_GUI.h"
#include "bellshire/GUI/BT_MatML_MeasurementTechniqueDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Metadata_GUI.h"
#include "bellshire/GUI/BT_MatML_Name_GUI.h"
#include "bellshire/GUI/BT_MatML_Notes_GUI.h"
#include "bellshire/GUI/BT_MatML_ParameterDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_ParameterValue_GUI.h"
#include "bellshire/GUI/BT_MatML_Data_GUI.h"
#include "bellshire/GUI/BT_MatML_PhaseComposition_GUI.h"
#include "bellshire/GUI/BT_MatML_ProcessingDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Result_GUI.h"
#include "bellshire/GUI/BT_MatML_Relationship_GUI.h"
#include "bellshire/GUI/BT_MatML_PropertyData_GUI.h"
#include "bellshire/GUI/BT_MatML_Data1_GUI.h"
#include "bellshire/GUI/BT_MatML_PropertyDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Qualifier_GUI.h"
#include "bellshire/GUI/BT_MatML_Source_GUI.h"
#include "bellshire/GUI/BT_MatML_SourceDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Specification_GUI.h"
#include "bellshire/GUI/BT_MatML_SpecimenDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_TestConditionDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_Uncertainty_GUI.h"
#include "bellshire/GUI/BT_MatML_Scale_GUI.h"
#include "bellshire/GUI/BT_MatML_Unit_GUI.h"
#include "bellshire/GUI/BT_MatML_Unitless_GUI.h"
#include "bellshire/GUI/BT_MatML_Units_GUI.h"
#include "bellshire/GUI/BT_MatML_Value_GUI.h"
#include "bellshire/GUI/BT_MatML_DataFormat_GUI.h"
#include "bellshire/GUI/BT_MatML_Description_GUI.h"

namespace bellshire::GUI {

	class MatML_GUI_Base;
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
	class Subclass_GUI;
	class Subclass1_GUI;
	class ParentMaterial_GUI;
	class ParentSubClass_GUI;
	class ComponentDetails_GUI;
	class Compound_GUI;
	class Concentration_GUI;
	class CurrencyCode_GUI;
	class DataSourceDetails_GUI;
	class Description_GUI;
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
	/// 
	/// Note: These pointers non-owning because the GUI are owned and destroyed by the parent window in wxWidget.
	class GUI
	{
	public:
		static const unsigned m_nclasses=63;
		std::shared_ptr<Intro_GUI> m_Intro_GUI;
		std::shared_ptr<MatML_Doc_GUI> m_MatML_Doc_GUI;
		std::shared_ptr<Material_GUI> m_Material_GUI;
		std::shared_ptr<Associate_GUI> m_Associate_GUI;
		std::shared_ptr<AssociationDetails_GUI> m_AssociationDetails_GUI;
		std::shared_ptr<AuthorityDetails_GUI> m_AuthorityDetails_GUI;
		std::shared_ptr<BulkDetails_GUI> m_BulkDetails_GUI;
		std::shared_ptr<Characterization_GUI> m_Characterization_GUI;
		std::shared_ptr<ChemicalComposition_GUI> m_ChemicalComposition_GUI;
		std::shared_ptr<ChemicalElementSymbol_GUI> m_ChemicalElementSymbol_GUI;
		std::shared_ptr<Class_GUI> m_Class_GUI;
		std::shared_ptr<Subclass_GUI> m_Subclass_GUI;
		std::shared_ptr<Subclass1_GUI> m_Subclass1_GUI;
		std::shared_ptr<ParentMaterial_GUI> m_ParentMaterial_GUI;
		std::shared_ptr<ParentSubClass_GUI> m_ParentSubClass_GUI;
		std::shared_ptr<ComponentDetails_GUI> m_ComponentDetails_GUI;
		std::shared_ptr<Compound_GUI> m_Compound_GUI;
		std::shared_ptr<Concentration_GUI> m_Concentration_GUI;
		std::shared_ptr<CurrencyCode_GUI> m_CurrencyCode_GUI;
		std::shared_ptr<DataSourceDetails_GUI> m_DataSourceDetails_GUI;
		std::shared_ptr<Description_GUI> m_Description_GUI;
		std::shared_ptr<DimensionalDetails_GUI> m_DimensionalDetails_GUI;
		std::shared_ptr<Element_GUI> m_Element_GUI;
		std::shared_ptr<Symbol_GUI> m_Symbol_GUI;
		std::shared_ptr<Form_GUI> m_Form_GUI;
		std::shared_ptr<Formula_GUI> m_Formula_GUI;
		std::shared_ptr<Geometry_GUI> m_Geometry_GUI;
		std::shared_ptr<Shape_GUI> m_Shape_GUI;
		std::shared_ptr<Dimensions_GUI> m_Dimensions_GUI;
		std::shared_ptr<Orientation_GUI> m_Orientation_GUI;
		std::shared_ptr<Glossary_GUI> m_Glossary_GUI;
		std::shared_ptr<GlossaryTerm_GUI> m_GlossaryTerm_GUI;
		std::shared_ptr<Definition_GUI> m_Definition_GUI;
		std::shared_ptr<Abbreviation_GUI> m_Abbreviation_GUI;
		std::shared_ptr<Synonym_GUI> m_Synonym_GUI;
		std::shared_ptr<Graphs_GUI> m_Graphs_GUI;
		std::shared_ptr<Graph_GUI> m_Graph_GUI;
		std::shared_ptr<MeasurementTechniqueDetails_GUI> m_MeasurementTechniqueDetails_GUI;
		std::shared_ptr<Metadata_GUI> m_Metadata_GUI;
		std::shared_ptr<Name_GUI> m_Name_GUI;
		std::shared_ptr<Notes_GUI> m_Notes_GUI;
		std::shared_ptr<ParameterDetails_GUI> m_ParameterDetails_GUI;
		std::shared_ptr<ParameterValue_GUI> m_ParameterValue_GUI;
		std::shared_ptr<Data_GUI> m_Data_GUI;
		std::shared_ptr<PhaseComposition_GUI> m_PhaseComposition_GUI;
		std::shared_ptr<ProcessingDetails_GUI> m_ProcessingDetails_GUI;
		std::shared_ptr<Result_GUI> m_Result_GUI;
		std::shared_ptr<Relationship_GUI> m_Relationship_GUI;
		std::shared_ptr<PropertyData_GUI> m_PropertyData_GUI;
		std::shared_ptr<Data1_GUI> m_Data1_GUI;
		std::shared_ptr<PropertyDetails_GUI> m_PropertyDetails_GUI;
		std::shared_ptr<Qualifier_GUI> m_Qualifier_GUI;
		std::shared_ptr<Source_GUI> m_Source_GUI;
		std::shared_ptr<SourceDetails_GUI> m_SourceDetails_GUI;
		std::shared_ptr<Specification_GUI> m_Specification_GUI;
		std::shared_ptr<SpecimenDetails_GUI> m_SpecimenDetails_GUI;
		std::shared_ptr<TestConditionDetails_GUI> m_TestConditionDetails_GUI;
		std::shared_ptr<Uncertainty_GUI> m_Uncertainty_GUI;
		std::shared_ptr<Scale_GUI> m_Scale_GUI;
		std::shared_ptr<Unit_GUI> m_Unit_GUI;
		std::shared_ptr<Unitless_GUI> m_Unitless_GUI;
		std::shared_ptr<Units_GUI> m_Units_GUI;
		std::shared_ptr<Value_GUI> m_Value_GUI;

		GUI(); /*!< Constructor */
		GUI(wxWindow* parent); /*!< Main Constructor */
		virtual ~GUI();/*!< Destructor */

		void SetSizer(wxFlexGridSizer*& fgSizer);/*!< Sets the window to have the given layout sizer. */

		template<class MatML_Class, class GUI_Class>
		bool Update_individual_GUI(::boost::any anyptr, observer_ptr<GUI_Class> GUI);/*!< Updates the individual MatML GUI */

		template<class MatML_Class, class GUI_Class>
		bool Update_individual_GUI(::boost::any anyptr, observer_ptr<GUI_Class> GUI, observer_ptr<MatML_Doc> doc);/*!< Updates the individual MatML GUI with information from the doc */

		void Update_GUI(::boost::any anyptr, observer_ptr<MatML_Doc> doc);/*!< Update **all** the individual MatML GUI */

		void HideAllPanels();/*!< Hide all the MatML GUI panels */

		void SetEvtHandlerVar(TreeCtrlSorted* MatMLTreeCtrl, observer_ptr<MatML_Doc> doc);/*!<Set the Event Handler functions variable */
	};

}//bellshire