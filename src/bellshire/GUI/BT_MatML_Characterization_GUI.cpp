#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Characterization_GUI.h"
#include "bellshire/GUI/BT_MatML_GUI.h"

using namespace bellshire::GUI;

Characterization_GUI_Base::Characterization_GUI_Base()
{

}

Characterization_GUI_Base::Characterization_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Characterization_GUI_Base::~Characterization_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Characterization MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="CharacterizationNotebook"></param>
/// <param name="CharacterizationPanel"></param>
/// <returns>bool</returns>
wxNotebook* Characterization_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* CharacterizationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	CharacterizationNotebook->Hide();
	CharacterizationNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* CharacterizationPanel(CreateCharacterizationPanel(CharacterizationNotebook));

	MatMLInfo_GUI matMLInfo_GUI(CharacterizationNotebook,
		wxT("************* Characterization *************************\n\nThis element declares the content model for Characterization, which\ncontains a description of the chemical composition of the bulk material\nor component and is composed of the following elements.\n\nFormula contains a string representation of the chemical formula for\nthe bulk material or component and must occur once and only once\nwithin the Characterization element. For further details see\n documentation of the Formula element.\n\nChemicalComposition contains a description of the compounds and\nelements that comprise the bulk material or component and may\noccur once or not at all within the Characterization element. For\nadditional information, see the documentation for the ChemicalComposition element.\n\nPhaseComposition contains a description of the phases that comprise\nthe bulk material or component and may occur zero or more times\nwithin the Characterization element. For additional information, see the\ndocumentation for the PhaseComposition element.\n\t\t\t\nDimensionalDetails contains information relating to component or bulk\nmaterial dimensional characteristics such as grain size, porosity,\nprecipitate size and distribution, etc., and may occur zero or more times\nwithin the Characterization element. For additional information, see the\ndocumentation for the DimensionalDetails element.\n\nNotes contains any additional information concerning the Characterization\n and may occur once or not at all within the Characterization element.\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	CharacterizationNotebook->AddPage(CharacterizationPanel, wxT("MatML Data."), b_dflt);
	CharacterizationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return CharacterizationNotebook;
}

wxWindow* Characterization_GUI_Base::CreateCharacterizationPanel(wxWindow* parent
)
{
	wxScrolledWindow* CharacterizationPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	CharacterizationPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer2512 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(CharacterizationPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2512->Add(staticText4, 0, wxALL, 5);

	CharacterizationPanel->SetSizer(bSizer2512);
	CharacterizationPanel->Layout();
	bSizer2512->Fit(CharacterizationPanel);

	return CharacterizationPanel;
}

void Characterization_GUI_Base::Update( const observer_ptr<Characterization> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Characterization_GUI_Base::GetTreeLabel(const observer_ptr<Characterization> element)
{
	wxString str;
	str << wxT("Characterization");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Characterization_GUI::Characterization_GUI() 
	: Characterization_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Characterization_GUI::Characterization_GUI(wxWindow* parent)
	: Characterization_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Characterization_GUI::~Characterization_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Characterization_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Characterization_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Characterization_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Characterization_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Characterization_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Characterization_GUI::OnInsertFormula(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_CHILD(Characterization, Formula)
}

void Characterization_GUI::OnInsertChemicalComposition(wxCommandEvent& event)
{
	ON_PARENT_INSERT_CONT_CHILD(Characterization, ChemicalComposition)
}

void Characterization_GUI::OnInsertPhaseComposition(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_ITER_CONT_CHILD(Characterization, PhaseComposition)
}

void Characterization_GUI::OnInsertDimensionalDetails(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_ITER_CONT_CHILD(Characterization, DimensionalDetails)
}

void Characterization_GUI::OnInsertNotes(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_CONT_CHILD(Characterization, Notes)
}

void Characterization_GUI::OnDeleteChemicalComposition(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_CONT_CHILD(Characterization, ChemicalComposition)
}

void Characterization_GUI::OnDeleteDimensionalDetails(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(Characterization, DimensionalDetails)
}

void Characterization_GUI::OnDeleteFormula(wxCommandEvent& event) 
{	
	ON_PARENT_DELETE_CHILD(Characterization, Formula)
}

void Characterization_GUI::OnDeleteNotes(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_CONT_CHILD(Characterization, Notes)
}

void Characterization_GUI::OnDeletePhaseComposition(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(Characterization, PhaseComposition)
}


void Characterization_GUI::OnPasteFormula(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_CHILD(Characterization, Formula)
}

void Characterization_GUI::OnPasteChemicalComposition(wxCommandEvent& event) 
{ 
	ON_PARENT_PASTE_CONT_CHILD(Characterization, ChemicalComposition)
}

void Characterization_GUI::OnPastePhaseComposition(wxCommandEvent& event)
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(Characterization, PhaseComposition)
}

void Characterization_GUI::OnPasteDimensionalDetails(wxCommandEvent& event) 
{ 
	ON_PARENT_PASTE_ITER_CONT_CHILD(Characterization, DimensionalDetails)
}

void Characterization_GUI::OnPasteNotes(wxCommandEvent& event)
{
	ON_PARENT_PASTE_CONT_CHILD(Characterization, Notes)
}
