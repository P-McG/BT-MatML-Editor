#include <wx/config.h>
#include "BT_MatML_Relationship_GUI.h"

using namespace bellshire;

Relationship_GUI_Base::Relationship_GUI_Base()
	:m_GUI(nullptr),
	m_RelationshipTextCtrl(nullptr)
{

}

Relationship_GUI_Base::Relationship_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_RelationshipTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_RelationshipTextCtrl);
}

Relationship_GUI_Base::~Relationship_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Relationship MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="RelationshipTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Relationship_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& RelationshipTextCtrl)
{

	wxNotebook* RelationshipNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	RelationshipNotebook->Hide();
	RelationshipNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* RelationshipPanel = new wxScrolledWindow(RelationshipNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize,  wxHSCROLL | wxVSCROLL);
	RelationshipPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer78 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer21 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer21->AddGrowableCol(1);
	fgSizer21->AddGrowableRow(0);
	fgSizer21->SetFlexibleDirection(wxBOTH);
	fgSizer21->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText24 = new wxStaticText(RelationshipPanel, wxID_ANY, wxT("Relationship"), wxDefaultPosition, wxDefaultSize, 0);
	staticText24->Wrap(-1);
	fgSizer21->Add(staticText24, 0, wxALL | wxEXPAND, 5);

	RelationshipTextCtrl = new wxTextCtrl(RelationshipPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	fgSizer21->Add(RelationshipTextCtrl, 0, wxALL | wxEXPAND, 5);

	bSizer78->Add(fgSizer21, 1, wxALL|wxEXPAND, 5);

	RelationshipPanel->SetSizer(bSizer78);
	RelationshipPanel->Layout();
	bSizer78->Fit(RelationshipPanel);

	MatMLInfo_GUI matMLInfo_GUI(RelationshipNotebook,
		wxT("************ Relationship *************************\n\nThis element declares the content model for Relationship, which\ncontains a string representing the relationship between a component\nand the associate.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	RelationshipNotebook->AddPage(RelationshipPanel, wxT("MatML Data."), b_dflt);
	RelationshipNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return RelationshipNotebook;
}

void Relationship_GUI_Base::Update( Relationship* element)
{
	wxString str;

	str << _std2wx((*element));//double paranthesis required
	m_RelationshipTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Relationship_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Relationship& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Relationship");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}

void Relationship_GUI_Base::SetConnect()
{
	m_RelationshipTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Relationship_GUI_Base::OnRelationshipTextCtrl), NULL, this);
	m_RelationshipTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Relationship_GUI_Base::OnRelationshipTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Relationship_GUI::Relationship_GUI() : Relationship_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Relationship_GUI::Relationship_GUI(wxWindow* parent)
	: Relationship_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Relationship_GUI::~Relationship_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Relationship_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Relationship_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void Relationship_GUI::OnRelationshipTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Relationship* const Element = boost::any_cast<Relationship* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_RelationshipTextCtrl->GetValue());
			Relationship NewData((const char*)str.mb_str(wxConvUTF8));
			(*Element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

