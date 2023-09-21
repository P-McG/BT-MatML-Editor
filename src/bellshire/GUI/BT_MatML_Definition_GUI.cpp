#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Definition_GUI.h"

using namespace bellshire::GUI;

Definition_GUI_Base::Definition_GUI_Base()
	:m_DefinitionTextCtrl(nullptr)
{

}

Definition_GUI_Base::Definition_GUI_Base(wxWindow* parent)
	:m_DefinitionTextCtrl(nullptr)
{
	m_GUI = Create(parent,m_DefinitionTextCtrl);
}

Definition_GUI_Base::~Definition_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Definition_GUI_Base::GetDefinitionTextCtrl()
{
	return m_DefinitionTextCtrl;
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

	wxWindow* DefinitionPanel(CreateDefinitionPanel(DefinitionNotebook, DefinitionTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(DefinitionNotebook,
		wxT("************* Definition *************************\n\nDefinition contains the term's definition and must occur once and only\nonce within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DefinitionNotebook->AddPage(DefinitionPanel, wxT("MatML Data."), b_dflt);
	DefinitionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DefinitionNotebook;
}

wxWindow* Definition_GUI_Base::CreateDefinitionPanel(wxWindow* parent, wxTextCtrl*& DefinitionTextCtrl)
{
	wxScrolledWindow* DefinitionPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return DefinitionPanel;
}


void Definition_GUI_Base::Update(const observer_ptr<Definition> element)
{
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element) };
	if (element_observer) {
		wxString str;

		str << _std2wx((*element_observer));//double parenthesis required;
		m_DefinitionTextCtrl->ChangeValue(str);

		ShowGUI(true);
	}
}

wxString Definition_GUI_Base::GetTreeLabel(const observer_ptr<Definition> element)
{
	wxString str;
	str << wxT("Definition");

	return str;
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
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Definition_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
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
		auto element_observer{ remove_strongly_typed_on_observer_ptr_v(
			boost::any_cast<observer_ptr<Definition>>
			(item->GetAnyMatMLDataPointer())
		)};
		if (element_observer) {
			wxString str(GetDefinitionTextCtrl()->GetValue());
			GlossaryTerm::Definition_type NewData((const char*)str.mb_str(wxConvUTF8));
			*(element_observer) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}