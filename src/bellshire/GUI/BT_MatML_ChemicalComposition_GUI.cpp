#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_ChemicalComposition_GUI.h"

using namespace bellshire::GUI;

ChemicalComposition_GUI_Base::ChemicalComposition_GUI_Base()
{

}

ChemicalComposition_GUI_Base::ChemicalComposition_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

ChemicalComposition_GUI_Base::~ChemicalComposition_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the ChemicalComposition MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ChemicalCompositionNotebook"></param>
/// <param name="ChemicalCompositionPanel"></param>
/// <returns>bool</returns>
wxNotebook* ChemicalComposition_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* ChemicalCompositionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ChemicalCompositionNotebook->Hide();
	ChemicalCompositionNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ChemicalCompositionPanel(CreateChemicalCompositionPanel(ChemicalCompositionNotebook));

	MatMLInfo_GUI matMLInfo_GUI(ChemicalCompositionNotebook,
		wxT("************* ChemicalComposition *************************\n\nThis element declares the content model for ChemicalComposition, which\ncontains a detailed description of the compounds and elements that\ncomprise the bulk material or component. ChemicalComposition must\ncontain at least one Compound element or Element element but may\ncontain as many of each element as needed.\n\nCompound contains a description of a compound. For additional\ninformation, see the documentation for the Compound element.\n\nElement contains a description of an element. For additional information,\nsee the documentation for the Element element.\n\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ChemicalCompositionNotebook->AddPage(ChemicalCompositionPanel, wxT("MatML Data."), b_dflt);
	ChemicalCompositionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ChemicalCompositionNotebook;
}

wxWindow* ChemicalComposition_GUI_Base::CreateChemicalCompositionPanel(wxWindow* parent)
{
	wxScrolledWindow* ChemicalCompositionPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ChemicalCompositionPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer2513 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(ChemicalCompositionPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2513->Add(staticText4, 0, wxALL, 5);

	ChemicalCompositionPanel->SetSizer(bSizer2513);
	ChemicalCompositionPanel->Layout();
	bSizer2513->Fit(ChemicalCompositionPanel);

	return ChemicalCompositionPanel;
}


void ChemicalComposition_GUI_Base::Update( const observer_ptr<ChemicalComposition> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString ChemicalComposition_GUI_Base::GetTreeLabel(const observer_ptr<ChemicalComposition> element)
{
	wxString str;
	str << wxT("ChemicalComposition");
	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
ChemicalComposition_GUI::ChemicalComposition_GUI() 
	: ChemicalComposition_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ChemicalComposition_GUI::ChemicalComposition_GUI(wxWindow* parent)
	: ChemicalComposition_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ChemicalComposition_GUI::~ChemicalComposition_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* ChemicalComposition_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any ChemicalComposition_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalComposition_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalComposition_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ChemicalComposition_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ChemicalComposition_GUI::OnInsertCompound(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnInsertElement(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ChemicalComposition, Element) }

void ChemicalComposition_GUI::OnDeleteCompound(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnDeleteElement(wxCommandEvent& event) {	ON_PARENT_DELETE_ITER_CONT_CHILD(ChemicalComposition, Element) }

void ChemicalComposition_GUI::OnPasteCompound(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnPasteElement(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ChemicalComposition, Element) }