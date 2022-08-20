#include <wx/config.h>

#include "BT_MatML_Definition_GUI.h"

using namespace bellshire;

Definition_GUI_Base::Definition_GUI_Base()
	:m_GUI(nullptr),
	m_DefinitionTextCtrl(nullptr)
{

}

Definition_GUI_Base::Definition_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_DefinitionTextCtrl(nullptr)
{
	m_GUI = Create(parent,m_DefinitionTextCtrl);
}

Definition_GUI_Base::~Definition_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Definition MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Definition_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& DefinitionTextCtrl)
{
	wxNotebook* DefinitionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DefinitionNotebook->Hide();
	DefinitionNotebook->SetMinSize(wxSize(100, 100));

	wxScrolledWindow* DefinitionPanel = new wxScrolledWindow(DefinitionNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DefinitionPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->AddGrowableRow(0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(DefinitionPanel, wxID_ANY, wxT("Definition"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);

	DefinitionTextCtrl = new wxTextCtrl(DefinitionPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	fgSizer1->Add(DefinitionTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer1, 1, wxALL | wxEXPAND, 5);

	DefinitionPanel->SetSizer(bSizer1);
	DefinitionPanel->Layout();
	bSizer1->Fit(DefinitionPanel);

	MatMLInfo_GUI matMLInfo_GUI(DefinitionNotebook,
		wxT("************* Definition *************************\n\nDefinition contains the term's definition and must occur once and only\nonce within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DefinitionNotebook->AddPage(DefinitionPanel, wxT("MatML Data."), b_dflt);
	DefinitionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DefinitionNotebook;
}


void Definition_GUI_Base::Update( Definition* element)
{
	wxString str;

	str << _std2wx(( * (element->t)));//double paranthesis required; t due to strongtypedef
	m_DefinitionTextCtrl->ChangeValue(str);

	Show(true);
}


/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Definition_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	GlossaryTerm::Definition_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Definition");

	wxTreeItemId CurrentId;

	MatMLTreeItemData* data = new MatMLTreeItemData(new Definition(&Element));

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, data);
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, data);

	//Setup MatML Attribute
	//--NONE--

	return CurrentId;
}

void Definition_GUI_Base::SetConnect()
{
	m_DefinitionTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Definition_GUI_Base::OnDefinitionTextCtrl), NULL, this);
	m_DefinitionTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Definition_GUI_Base::OnDefinitionTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Definition_GUI::Definition_GUI() : Definition_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Definition_GUI::Definition_GUI(wxWindow* parent)
	: Definition_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}



/// <summary>
/// Destructor for the derived class
/// </summary>
Definition_GUI::~Definition_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Definition_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Definition_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Definition_GUI::OnDefinitionTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Definition* element = boost::any_cast<Definition* >(item->GetAnyMatMLDataPointer());	 
		if (element != 0) {
			wxString str(m_DefinitionTextCtrl->GetValue());
			GlossaryTerm::Definition_type NewData((const char*)str.mb_str(wxConvUTF8));
			*(element->t) = NewData;//t required due to strong_typedef
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}