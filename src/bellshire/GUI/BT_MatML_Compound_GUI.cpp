#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Compound_GUI.h"

using namespace bellshire::GUI;

Compound_GUI_Base::Compound_GUI_Base()
{

}

Compound_GUI_Base::Compound_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Compound_GUI_Base::~Compound_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Compound MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Compound_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* CompoundNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	CompoundNotebook->Hide();
	CompoundNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* CompoundPanel(CreateCompoundPanel(CompoundNotebook));

	MatMLInfo_GUI matMLInfo_GUI(CompoundNotebook,
		wxT("*************** Compound *************************\n\t\t\t\nThis element declares the content model for Compound, which contains\nthe elemental description of a chemical compound and is composed the\nfollowing elements.\n\nElement contains the description of a chemical element and must occur\none or more times within the Compound element. For additional\ninformation, see the documentation for the Element element.\n\nConcentration contains the concentration of the compound and may\noccur once or not at all within the Compound element. For additional\ninformation, see the documentation for the Concentration element.\n\t\t\t\nNotes contains any additional information concerning the compound\nand may occur once or not at all within the Compound element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	CompoundNotebook->AddPage(CompoundPanel, wxT("MatML Data."), b_dflt);
	CompoundNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return CompoundNotebook;
}

wxWindow* Compound_GUI_Base::CreateCompoundPanel(wxWindow* parent)
{
	wxScrolledWindow* CompoundPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	CompoundPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer25131 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(CompoundPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25131->Add(staticText4, 0, wxALL, 5);

	CompoundPanel->SetSizer(bSizer25131);
	CompoundPanel->Layout();
	bSizer25131->Fit(CompoundPanel);
	
	return CompoundPanel;
}

void Compound_GUI_Base::Update( const observer_ptr<Compound> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Compound_GUI_Base::GetTreeLabel(const observer_ptr<Compound> element)
{
	wxString str;
	str << wxT("Compound");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Compound_GUI::Compound_GUI() 
	: Compound_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Compound_GUI::Compound_GUI(wxWindow* parent)
	: Compound_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Compound_GUI::~Compound_GUI() {
	/*parent will destroy Ctrl or window */
}
TreeCtrlSorted* Compound_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}
::boost::any Compound_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}
/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Compound_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Compound_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Compound_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Compound_GUI::OnInsertElement(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Compound, Element) }
void Compound_GUI::OnInsertConcentration(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Compound, Concentration) }
void Compound_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Compound, Notes) }

void Compound_GUI::OnDeleteConcentration(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Compound, Concentration)}
void Compound_GUI::OnDeleteElement(wxCommandEvent& event) {	ON_PARENT_DELETE_ITER_CONT_CHILD(Compound, Element)}
void Compound_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Compound, Notes)}

void Compound_GUI::OnPasteElement(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Compound, Element) }
void Compound_GUI::OnPasteConcentration(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Compound, Concentration) }
void Compound_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Compound, Notes) }


void Compound_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Compound,
		ChemicalComposition,
		ChemicalComposition::Compound_sequence,
		Compound_GUI,
		&ChemicalComposition::Compound
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Compound_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Compound,
		ChemicalComposition,
		ChemicalComposition::Compound_sequence,
		Compound_GUI,
		&ChemicalComposition::Compound
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}