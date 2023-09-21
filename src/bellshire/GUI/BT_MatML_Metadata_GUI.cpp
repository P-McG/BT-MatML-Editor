#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Metadata_GUI.h"

using namespace bellshire::GUI;

Metadata_GUI_Base::Metadata_GUI_Base()
{

}

Metadata_GUI_Base::Metadata_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Metadata_GUI_Base::~Metadata_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Metadata MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Metadata_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* MetadataNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	MetadataNotebook->Hide();
	MetadataNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* MetadataPanel(CreateMetadataPanel(MetadataNotebook));

	MatMLInfo_GUI matMLInfo_GUI(MetadataNotebook,
		wxT("********* Metadata *************************\n\nThis element declares the content model for Metadata, which contains\ndescriptions of authorities, data sources, measurement techniques,\nparameters, properties, material and component sources, specimens, \nand test conditions. Metadata is composed of the following elements.\n\nAuthorityDetails contains a description of authorities referenced from \nthe Specification and Name elements and may occur zero or more times \nwithin the Metadata element. For additional information, see the \ndocumentation for the AuthorityDetails element.\n\nDataSourceDetails contains a description of a data source referenced\nusing the PropertyData element and may occur zero or more times within\nthe Metadata element. For additional information, see the documentation\nfor the DataSourceDetails element.\n\nMeasurementTechniqueDetails contains a description of a measurement\ntechnique referenced using the PropertyData element and may occur zero\n or more times within the Metadata element. For additional information,\n see the documentation for the MeasurementTechniqueDetails element.\n\nParameterDetails contains a description of a parameter referenced using\nthe PropertyData element and may occur zero or more times within the\nMetadata element. For additional information, see the documentation for\nthe ParameterDetails element.\n\nPropertyDetails contains a description of a property for which materials\ndata are encoded using the PropertyData element and may occur zero or\nmore times within the Metadata element. For additional information, \nsee the documentation for the PropertyDetails element.\n\t\t\t\nSourceDetails contains a description of the source of a material or\ncomponent referenced using the Source element and may occur zero or \nmore times within the Metadata element. For additional information, \nsee the documentation for the SourceDetails element.\n\nSpecimenDetails contains a description of a specimen referenced using\nthe PropertyData element and may occur zero or more times within the\nMetadata element. For additional information, see the documentation for\nthe SpecimenDetails element.\n\t\t\t\nTestCondtionDetails contains a description of the test condtion(s) \nreferenced using the PropertyData element and may occur zero or more \ntimes within the Metadata element. For additional information, see the \ndocumentation for the TestCondtionDetails element.")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	MetadataNotebook->AddPage(MetadataPanel, wxT("MatML Data."), b_dflt);
	MetadataNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return MetadataNotebook;
}

wxWindow* Metadata_GUI_Base::CreateMetadataPanel(wxWindow* parent)
{
	wxScrolledWindow* MetadataPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	MetadataPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(MetadataPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	MetadataPanel->SetSizer(bSizer1);
	MetadataPanel->Layout();
	bSizer1->Fit(MetadataPanel);

	return MetadataPanel;
}

void Metadata_GUI_Base::Update( const observer_ptr<Metadata> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Metadata_GUI_Base::GetTreeLabel(const observer_ptr<Metadata> element)
{
	wxString str;
	str << wxT("*** METADATA ***");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Metadata_GUI::Metadata_GUI() 
	: Metadata_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Metadata_GUI::Metadata_GUI(wxWindow* parent)
	: Metadata_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Metadata_GUI::~Metadata_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Metadata_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Metadata_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Metadata_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Metadata_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Metadata_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Metadata_GUI::OnInsertAuthorityDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, AuthorityDetails) }
void Metadata_GUI::OnInsertDataSourceDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, DataSourceDetails) }
void Metadata_GUI::OnInsertMeasurementTechniqueDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, MeasurementTechniqueDetails) }
void Metadata_GUI::OnInsertParameterDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, ParameterDetails) }
void Metadata_GUI::OnInsertPropertyDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, PropertyDetails) }
void Metadata_GUI::OnInsertSourceDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, SourceDetails) }
void Metadata_GUI::OnInsertSpecimenDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, SpecimenDetails) }
void Metadata_GUI::OnInsertTestConditionDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Metadata, TestConditionDetails) }

void Metadata_GUI::OnDeleteAuthorityDetails(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, AuthorityDetails) }
void Metadata_GUI::OnDeleteDataSourceDetails(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, DataSourceDetails) }
void Metadata_GUI::OnDeleteMeasurementTechniqueDetails(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, MeasurementTechniqueDetails) }
void Metadata_GUI::OnDeleteParameterDetails(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, ParameterDetails) }
void Metadata_GUI::OnDeletePropertyDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, PropertyDetails)}
void Metadata_GUI::OnDeleteSpecimenDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, SpecimenDetails)}
void Metadata_GUI::OnDeleteSourceDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, SourceDetails)}
void Metadata_GUI::OnDeleteTestConditionDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Metadata, TestConditionDetails)}

void Metadata_GUI::OnPasteAuthorityDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, AuthorityDetails) }
void Metadata_GUI::OnPasteDataSourceDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, DataSourceDetails) }
void Metadata_GUI::OnPasteMeasurementTechniqueDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, MeasurementTechniqueDetails) }
void Metadata_GUI::OnPasteParameterDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, ParameterDetails) }
void Metadata_GUI::OnPastePropertyDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, PropertyDetails) }
void Metadata_GUI::OnPasteSourceDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, SourceDetails) }
void Metadata_GUI::OnPasteSpecimenDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, SpecimenDetails) }
void Metadata_GUI::OnPasteTestConditionDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Metadata, TestConditionDetails) }
