#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_PhaseComposition_GUI.h"

using namespace bellshire;

PhaseComposition_GUI_Base::PhaseComposition_GUI_Base()
{

}

PhaseComposition_GUI_Base::PhaseComposition_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

PhaseComposition_GUI_Base::~PhaseComposition_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the PhaseComposition MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="PhaseCompositionNotebook"></param>
/// <param name="PhaseCompositionPanel"></param>
/// <returns>bool</returns>
wxNotebook* PhaseComposition_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* PhaseCompositionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	PhaseCompositionNotebook->Hide();
	PhaseCompositionNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* PhaseCompositionPanel(CreatePhaseCompositionPanel(PhaseCompositionNotebook));

	MatMLInfo_GUI matMLInfo_GUI(PhaseCompositionNotebook,
		wxT("********** PhaseComposition *************************\n\t\t\t\nThis element declares the content model for PhaseComposition, which\ncontains a description of a phase that comprises the bulk material or\ncomponent and is composed of the following elements.\n\nName contains the name of the phase and has one optional attribute,\nauthority, for identifying an authoritative source of phase names. Name\nmust occur once and only once within the PhaseComposition element.\n\nConcentration contains the concentration of the phase and may occur\nonce or not at all within the PhaseComposition element. For additional\ninformation, see the documentation for the Concentration element.\n\nPropertyData contains property data for the phase and may occur zero\nor more times within the PhaseComposition element. For additional\ninformation, see the documentation for the PropertyData element.\n\nNotes contains any additional information concerning the phase and may\noccur once or not at all within the PhaseComposition element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	PhaseCompositionNotebook->AddPage(PhaseCompositionPanel, wxT("MatML Data."), b_dflt);
	PhaseCompositionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return PhaseCompositionNotebook;
}

wxWindow* PhaseComposition_GUI_Base::CreatePhaseCompositionPanel(wxWindow* parent)
{

	wxScrolledWindow* PhaseCompositionPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	PhaseCompositionPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(PhaseCompositionPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	PhaseCompositionPanel->SetSizer(bSizer1);
	PhaseCompositionPanel->Layout();
	bSizer1->Fit(PhaseCompositionPanel);

	return PhaseCompositionPanel;
}

void PhaseComposition_GUI_Base::Update( const observer_ptr<PhaseComposition> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString PhaseComposition_GUI_Base::GetTreeLabel(const observer_ptr<PhaseComposition> element)
{
	wxString str;
	str << wxT("PhaseComposition");

	return str;
}


TreeCtrlSorted* PhaseComposition_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any PhaseComposition_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Constructor for the derived class
/// </summary>
PhaseComposition_GUI::PhaseComposition_GUI() 
	: PhaseComposition_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
PhaseComposition_GUI::PhaseComposition_GUI(wxWindow* parent)
	: PhaseComposition_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
PhaseComposition_GUI::~PhaseComposition_GUI() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PhaseComposition_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PhaseComposition_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void PhaseComposition_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void PhaseComposition_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(PhaseComposition, Name) }
void PhaseComposition_GUI::OnInsertConcentration(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PhaseComposition, Concentration) }
void PhaseComposition_GUI::OnInsertPropertyData(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(PhaseComposition, PropertyData) }
void PhaseComposition_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PhaseComposition, Notes) }

void PhaseComposition_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(PhaseComposition, Name)}
void PhaseComposition_GUI::OnDeleteConcentration(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PhaseComposition, Concentration)}
void PhaseComposition_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PhaseComposition, Notes)}
void PhaseComposition_GUI::OnDeletePropertyData(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(PhaseComposition, PropertyData)}

void PhaseComposition_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(PhaseComposition, Name) }
void PhaseComposition_GUI::OnPasteConcentration(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PhaseComposition, Concentration) }
void PhaseComposition_GUI::OnPastePropertyData(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(PhaseComposition, PropertyData) }
void PhaseComposition_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PhaseComposition, Notes) }


void PhaseComposition_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< PhaseComposition,
		Characterization,
		Characterization::PhaseComposition_sequence,
		PhaseComposition_GUI,
		&Characterization::PhaseComposition
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);
}

void PhaseComposition_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< PhaseComposition,
		Characterization,
		Characterization::PhaseComposition_sequence,
		PhaseComposition_GUI,
		&Characterization::PhaseComposition
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);
}
