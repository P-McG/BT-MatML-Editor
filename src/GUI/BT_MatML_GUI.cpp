#include "BT_MatML_GUI.h"

using namespace bellshire;

/// Constuctor
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
/// Initiallizes with new individual MatML GUIs
/// </summary>
/// <param name="parent"></param>
GUI::GUI(wxWindow* parent)
	:m_Intro_GUI(new Intro_GUI(parent)),
	m_MatML_Doc_GUI(new MatML_Doc_GUI(parent)),
	m_Material_GUI(new Material_GUI(parent)),
	m_Associate_GUI(new Associate_GUI(parent)),
	m_AssociationDetails_GUI(new AssociationDetails_GUI(parent)),
	m_AuthorityDetails_GUI(new AuthorityDetails_GUI(parent)),
	m_BulkDetails_GUI(new BulkDetails_GUI(parent)),
	m_Characterization_GUI(new Characterization_GUI(parent)),
	m_ChemicalComposition_GUI(new ChemicalComposition_GUI(parent)),
	m_ChemicalElementSymbol_GUI(new ChemicalElementSymbol_GUI(parent)),
	m_Class_GUI(new Class_GUI(parent)),
	m_ParentMaterial_GUI(new ParentMaterial_GUI(parent)),
	m_ParentSubClass_GUI(new ParentSubClass_GUI(parent)),
	m_ComponentDetails_GUI(new ComponentDetails_GUI(parent)),
	m_Compound_GUI(new Compound_GUI(parent)),
	m_Concentration_GUI( new Concentration_GUI(parent)),
	m_CurrencyCode_GUI( new CurrencyCode_GUI(parent)),
	m_DataSourceDetails_GUI( new DataSourceDetails_GUI(parent)),
	m_DimensionalDetails_GUI( new DimensionalDetails_GUI(parent)),
	m_Element_GUI( new Element_GUI(parent)),
	m_Symbol_GUI( new Symbol_GUI(parent)),
	m_Form_GUI( new Form_GUI(parent)),
	m_Formula_GUI( new Formula_GUI(parent)),
	m_Geometry_GUI( new Geometry_GUI(parent)),
	m_Shape_GUI( new Shape_GUI(parent)),
	m_Dimensions_GUI( new Dimensions_GUI(parent)),
	m_Orientation_GUI( new Orientation_GUI(parent)),
	m_Glossary_GUI( new Glossary_GUI(parent)),
	m_GlossaryTerm_GUI( new GlossaryTerm_GUI(parent)),
	m_Definition_GUI( new Definition_GUI(parent)),
	m_Abbreviation_GUI( new Abbreviation_GUI(parent)),
	m_Synonym_GUI( new Synonym_GUI(parent)),
	m_Graphs_GUI( new Graphs_GUI(parent)),
	m_Graph_GUI( new Graph_GUI(parent)),
	m_MeasurementTechniqueDetails_GUI( new MeasurementTechniqueDetails_GUI(parent)),
	m_Metadata_GUI( new Metadata_GUI(parent)),
	m_Name_GUI( new Name_GUI(parent)),
	m_Notes_GUI( new Notes_GUI(parent)),
	m_ParameterDetails_GUI( new ParameterDetails_GUI(parent)),
	m_ParameterValue_GUI( new ParameterValue_GUI(parent)),
	m_Data_GUI( new Data_GUI(parent)),
	m_PhaseComposition_GUI( new PhaseComposition_GUI(parent)),
	m_ProcessingDetails_GUI( new ProcessingDetails_GUI(parent)),
	m_Result_GUI( new Result_GUI(parent)),
	m_Relationship_GUI( new Relationship_GUI(parent)),
	m_PropertyData_GUI( new PropertyData_GUI(parent)),
	m_Data1_GUI( new Data1_GUI(parent)),
	m_PropertyDetails_GUI( new PropertyDetails_GUI(parent)),
	m_Qualifier_GUI( new Qualifier_GUI(parent)),
	m_Source_GUI( new Source_GUI(parent)),
	m_SourceDetails_GUI( new SourceDetails_GUI(parent)),
	m_Specification_GUI( new Specification_GUI(parent)),
	m_SpecimenDetails_GUI( new SpecimenDetails_GUI(parent)),
	m_TestConditionDetails_GUI( new TestConditionDetails_GUI(parent)),
	m_Uncertainty_GUI( new Uncertainty_GUI(parent)),
	m_Scale_GUI( new Scale_GUI(parent)),
	m_Unit_GUI( new Unit_GUI(parent)),
	m_Unitless_GUI( new Unitless_GUI(parent)),
	m_Units_GUI( new Units_GUI(parent)),
	m_Value_GUI(new Value_GUI(parent))
	{}

/// Destructor
/// 
/// <summary>
/// Destroys individual MatML GUIs
/// </summary>
GUI::~GUI()
{
	delete m_Intro_GUI;
	delete m_MatML_Doc_GUI;
	delete m_Material_GUI;
	delete m_Associate_GUI;
	delete m_AssociationDetails_GUI;
	delete m_AuthorityDetails_GUI;
	delete m_BulkDetails_GUI;
	delete m_Characterization_GUI;
	delete m_ChemicalComposition_GUI;
	delete m_ChemicalElementSymbol_GUI;
	delete m_Class_GUI;
	delete m_ParentMaterial_GUI;
	delete m_ParentSubClass_GUI;
	delete m_ComponentDetails_GUI;
	delete m_Compound_GUI;
	delete m_Concentration_GUI;
	delete m_CurrencyCode_GUI;
	delete m_DataSourceDetails_GUI;
	delete m_DimensionalDetails_GUI;
	delete m_Element_GUI;
	delete m_Symbol_GUI;
	delete m_Form_GUI;
	delete m_Formula_GUI;
	delete m_Geometry_GUI;
	delete m_Shape_GUI;
	delete m_Dimensions_GUI;
	delete m_Orientation_GUI;
	delete m_Glossary_GUI;
	delete m_GlossaryTerm_GUI;
	delete m_Definition_GUI;
	delete m_Abbreviation_GUI;
	delete m_Synonym_GUI;
	delete m_Graphs_GUI;
	delete m_Graph_GUI;
	delete m_MeasurementTechniqueDetails_GUI;
	delete m_Metadata_GUI;
	delete m_Name_GUI;
	delete m_Notes_GUI;
	delete m_ParameterDetails_GUI;
	delete m_ParameterValue_GUI;
	delete m_Data_GUI;
	delete m_PhaseComposition_GUI;
	delete m_ProcessingDetails_GUI;
	delete m_Result_GUI;
	delete m_Relationship_GUI;
	delete m_PropertyData_GUI;
	delete m_Data1_GUI;
	delete m_PropertyDetails_GUI;
	delete m_Qualifier_GUI;
	delete m_Source_GUI;
	delete m_SourceDetails_GUI;
	delete m_Specification_GUI;
	delete m_SpecimenDetails_GUI;
	delete m_TestConditionDetails_GUI;
	delete m_Uncertainty_GUI;
	delete m_Scale_GUI;
	delete m_Unit_GUI;
	delete m_Unitless_GUI;
	delete m_Units_GUI;
	delete m_Value_GUI;
}


/// SetSizer
/// Adds the GUIs to the controlling Sizer.
/// <summary>
/// Assumes the same sizer for all the MatML GUIs and that the panels are placed
/// adjacent. Panels of the MatML GUIs are hiden and shown on updating
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
bool GUI::Update_individual_GUI(::boost::any anyptr, GUI_Class GUI)
{
	bool rtn = false;
	try {
		if (anyptr.type() == typeid(MatML_Class)) {
			MatML_Class const derived = boost::any_cast<MatML_Class const>(anyptr);
			if (derived != 0) {
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
bool GUI::Update_individual_GUI(::boost::any anyptr, GUI_Class GUI, ::boost::shared_ptr<MatML_Doc> doc)
{
	bool rtn = false;
	try {
		if (anyptr.type() == typeid(MatML_Class)) {
			MatML_Class const derived = boost::any_cast<MatML_Class const>(anyptr);
			if (derived != 0) {
				GUI->Update(derived, doc);
				rtn = true;
			}
			else rtn = false;
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
void GUI::Update_GUI(::boost::any anyptr, ::boost::shared_ptr<MatML_Doc> doc)
{
	if (Update_individual_GUI< Associate*, Associate_GUI*>(anyptr, m_Associate_GUI)) goto done;
	if (Update_individual_GUI< AssociationDetails*, AssociationDetails_GUI*>(anyptr, m_AssociationDetails_GUI)) goto done;
	if (Update_individual_GUI< AuthorityDetails*, AuthorityDetails_GUI*>(anyptr, m_AuthorityDetails_GUI)) goto done;
	if (Update_individual_GUI< BulkDetails*, BulkDetails_GUI*>(anyptr, m_BulkDetails_GUI)) goto done;
	if (Update_individual_GUI< Characterization*, Characterization_GUI*>(anyptr, m_Characterization_GUI)) goto done;
	if (Update_individual_GUI< ChemicalComposition*, ChemicalComposition_GUI*>(anyptr, m_ChemicalComposition_GUI)) goto done;
	if (Update_individual_GUI< ChemicalElementSymbol*, ChemicalElementSymbol_GUI*>(anyptr, m_ChemicalElementSymbol_GUI)) goto done;
	if (Update_individual_GUI< Class*, Class_GUI*>(anyptr, m_Class_GUI)) goto done;
	if (Update_individual_GUI< ParentMaterial*, ParentMaterial_GUI*>(anyptr, m_ParentMaterial_GUI, doc)) goto done;
	if (Update_individual_GUI< ParentSubClass*, ParentSubClass_GUI*>(anyptr, m_ParentSubClass_GUI)) goto done;
	if (Update_individual_GUI< ComponentDetails*, ComponentDetails_GUI*>(anyptr, m_ComponentDetails_GUI)) goto done;
	if (Update_individual_GUI< Compound*, Compound_GUI*>(anyptr, m_Compound_GUI)) goto done;
	if (Update_individual_GUI< Concentration*, Concentration_GUI*>(anyptr, m_Concentration_GUI)) goto done;
	if (Update_individual_GUI< CurrencyCode*, CurrencyCode_GUI*>(anyptr, m_CurrencyCode_GUI)) goto done;
	if (Update_individual_GUI< DataSourceDetails*, DataSourceDetails_GUI*>(anyptr, m_DataSourceDetails_GUI)) goto done;
	if (Update_individual_GUI< DimensionalDetails*, DimensionalDetails_GUI*>(anyptr, m_DimensionalDetails_GUI)) goto done;
	if (Update_individual_GUI< Element*, Element_GUI*>(anyptr, m_Element_GUI)) goto done;
	if (Update_individual_GUI< Symbol*, Symbol_GUI*>(anyptr, m_Symbol_GUI)) goto done;
	if (Update_individual_GUI< Form*, Form_GUI*>(anyptr, m_Form_GUI)) goto done;
	//if (Update_individual_GUI< Description*, Description_GUI*>(anyptr, m_Description_GUI)) goto done;
	if (Update_individual_GUI< Formula*, Formula_GUI*>(anyptr, m_Formula_GUI)) goto done;
	if (Update_individual_GUI< Geometry*, Geometry_GUI*>(anyptr, m_Geometry_GUI)) goto done;
	if (Update_individual_GUI< Shape*, Shape_GUI*>(anyptr, m_Shape_GUI)) goto done;
	if (Update_individual_GUI< Dimensions*, Dimensions_GUI*>(anyptr, m_Dimensions_GUI)) goto done;
	if (Update_individual_GUI< Orientation*, Orientation_GUI*>(anyptr, m_Orientation_GUI)) goto done;
	if (Update_individual_GUI< Glossary*, Glossary_GUI*>(anyptr, m_Glossary_GUI)) goto done;
	if (Update_individual_GUI< GlossaryTerm*, GlossaryTerm_GUI*>(anyptr, m_GlossaryTerm_GUI)) goto done;
	if (Update_individual_GUI< Definition*, Definition_GUI*>(anyptr, m_Definition_GUI)) goto done;
	if (Update_individual_GUI< Abbreviation*, Abbreviation_GUI*>(anyptr, m_Abbreviation_GUI)) goto done;
	if (Update_individual_GUI< Synonym*, Synonym_GUI*>(anyptr, m_Synonym_GUI)) goto done;
	if (Update_individual_GUI< Graphs*, Graphs_GUI*>(anyptr, m_Graphs_GUI)) goto done;
	if (Update_individual_GUI< Graph*, Graph_GUI*>(anyptr, m_Graph_GUI)) goto done;
	if (Update_individual_GUI< Material*, Material_GUI*>(anyptr, m_Material_GUI)) goto done;
	//if (Update_individual_GUI< MatML_Doc*, MatML_Doc_GUI*>(anyptr, m_MatML_Doc_GUI)) goto done;
	if (Update_individual_GUI< MeasurementTechniqueDetails*, MeasurementTechniqueDetails_GUI*>(anyptr, m_MeasurementTechniqueDetails_GUI)) goto done;
	if (Update_individual_GUI< Metadata*, Metadata_GUI*>(anyptr, m_Metadata_GUI)) goto done;
	if (Update_individual_GUI< Name*, Name_GUI*>(anyptr, m_Name_GUI, doc)) goto done;
	if (Update_individual_GUI< Notes*, Notes_GUI*>(anyptr, m_Notes_GUI)) goto done;
	if (Update_individual_GUI< ParameterDetails*, ParameterDetails_GUI*>(anyptr, m_ParameterDetails_GUI)) goto done;
	if (Update_individual_GUI< ParameterValue*, ParameterValue_GUI*>(anyptr, m_ParameterValue_GUI, doc)) goto done;
	if (Update_individual_GUI< Data*, Data_GUI*>(anyptr, m_Data_GUI)) goto done;
	if (Update_individual_GUI< PhaseComposition*, PhaseComposition_GUI*>(anyptr, m_PhaseComposition_GUI)) goto done;
	if (Update_individual_GUI< ProcessingDetails*, ProcessingDetails_GUI*>(anyptr, m_ProcessingDetails_GUI)) goto done;
	if (Update_individual_GUI< Result*, Result_GUI*>(anyptr, m_Result_GUI)) goto done;
	if (Update_individual_GUI< PropertyData*, PropertyData_GUI*>(anyptr, m_PropertyData_GUI, doc)) goto done;
	if (Update_individual_GUI< Data1*, Data1_GUI*>(anyptr, m_Data1_GUI)) goto done;
	if (Update_individual_GUI< PropertyDetails*, PropertyDetails_GUI*>(anyptr, m_PropertyDetails_GUI)) goto done;
	if (Update_individual_GUI< Qualifier*, Qualifier_GUI*>(anyptr, m_Qualifier_GUI)) goto done;
	if (Update_individual_GUI< Relationship*, Relationship_GUI*>(anyptr, m_Relationship_GUI)) goto done;
	if (Update_individual_GUI< Source*, Source_GUI*>(anyptr, m_Source_GUI, doc)) goto done;
	if (Update_individual_GUI< SourceDetails*, SourceDetails_GUI*>(anyptr, m_SourceDetails_GUI)) goto done;
	if (Update_individual_GUI< Specification*, Specification_GUI*>(anyptr, m_Specification_GUI, doc)) goto done;
	if (Update_individual_GUI< SpecimenDetails*, SpecimenDetails_GUI*>(anyptr, m_SpecimenDetails_GUI)) goto done;
	if (Update_individual_GUI< TestConditionDetails*, TestConditionDetails_GUI*>(anyptr, m_TestConditionDetails_GUI)) goto done;
	if (Update_individual_GUI< Uncertainty*, Uncertainty_GUI*>(anyptr, m_Uncertainty_GUI)) goto done;
	if (Update_individual_GUI< Scale*, Scale_GUI*>(anyptr, m_Scale_GUI)) goto done;
	if (Update_individual_GUI< Unit*, Unit_GUI*>(anyptr, m_Unit_GUI)) goto done;
	if (Update_individual_GUI< Unitless*, Unitless_GUI*>(anyptr, m_Unitless_GUI)) goto done;
	if (Update_individual_GUI< Units*, Units_GUI*>(anyptr, m_Units_GUI)) goto done;
	if (Update_individual_GUI< Value*, Value_GUI*>(anyptr, m_Value_GUI)) goto done;

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
	m_Intro_GUI->Show(false);
	m_MatML_Doc_GUI->Show(false);
	m_Associate_GUI->Show(false);
	m_AssociationDetails_GUI->Show(false);
	m_AuthorityDetails_GUI->Show(false);
	m_BulkDetails_GUI->Show(false);
	m_Characterization_GUI->Show(false);
	m_ChemicalComposition_GUI->Show(false);
	m_ChemicalElementSymbol_GUI->Show(false);
	m_Class_GUI->Show(false);
	m_ParentMaterial_GUI->Show(false);
	m_ParentSubClass_GUI->Show(false);
	m_Compound_GUI->Show(false);
	m_ComponentDetails_GUI->Show(false);
	m_Concentration_GUI->Show(false);
	m_CurrencyCode_GUI->Show(false);
	m_DataSourceDetails_GUI->Show(false);
	m_DimensionalDetails_GUI->Show(false);
	m_Element_GUI->Show(false);
	m_Symbol_GUI->Show(false);
	m_Form_GUI->Show(false);
	m_Formula_GUI->Show(false);
	m_Geometry_GUI->Show(false);
	m_Shape_GUI->Show(false);
	m_Dimensions_GUI->Show(false);
	m_Orientation_GUI->Show(false);
	m_Glossary_GUI->Show(false);
	m_GlossaryTerm_GUI->Show(false);
	m_Definition_GUI->Show(false);
	m_Abbreviation_GUI->Show(false);
	m_Synonym_GUI->Show(false);
	m_Graphs_GUI->Show(false);
	m_Graph_GUI->Show(false);
	m_Material_GUI->Show(false);
	m_MeasurementTechniqueDetails_GUI->Show(false);
	m_Metadata_GUI->Show(false);
	m_Name_GUI->Show(false);
	m_Notes_GUI->Show(false);
	m_ParameterDetails_GUI->Show(false);
	m_ParameterValue_GUI->Show(false);
	m_Data_GUI->Show(false);
	m_PhaseComposition_GUI->Show(false);
	m_ProcessingDetails_GUI->Show(false);
	m_Result_GUI->Show(false);
	m_Relationship_GUI->Show(false);
	m_PropertyData_GUI->Show(false);
	m_Data1_GUI->Show(false);
	m_PropertyDetails_GUI->Show(false);
	m_Qualifier_GUI->Show(false);
	m_Source_GUI->Show(false);
	m_SourceDetails_GUI->Show(false);
	m_Specification_GUI->Show(false);
	m_SpecimenDetails_GUI->Show(false);
	m_TestConditionDetails_GUI->Show(false);
	m_Uncertainty_GUI->Show(false);
	m_Scale_GUI->Show(false);
	m_Unit_GUI->Show(false);
	m_Unitless_GUI->Show(false);
	m_Units_GUI->Show(false);
	m_Value_GUI->Show(false);
}

/// Set Event Handler Variable
/// <summary>
/// Sets the variables for the Event Handlers related to the MatML_GUIs.
/// These variables are members of the MaterialFrame class.
/// Need to be run before using MatML_GUIs events.
/// </summary>
void GUI::SetEvtHandlerVar(TreeCtrlSorted* MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc> doc)
{
	m_MatML_Doc_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Material_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_Associate_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_AssociationDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_AuthorityDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_BulkDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Characterization_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ChemicalComposition_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ChemicalElementSymbol_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Class_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ParentMaterial_GUI->SetEvtHandlerVar(MatMLTreeCtrl, doc);
	m_ParentSubClass_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ComponentDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Compound_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Concentration_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_CurrencyCode_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_DataSourceDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
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
	m_Graph_GUI->SetEvtHandlerVar();
	m_MeasurementTechniqueDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Metadata_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Name_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Notes_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ParameterDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ParameterValue_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Data_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PhaseComposition_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_ProcessingDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Result_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Relationship_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PropertyData_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Data1_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_PropertyDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Qualifier_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Source_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_SourceDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Specification_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_SpecimenDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_TestConditionDetails_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Uncertainty_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Scale_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Unit_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Unitless_GUI->SetEvtHandlerVar();
	m_Units_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	m_Value_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
}