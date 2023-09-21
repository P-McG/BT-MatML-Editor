#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Notes_GUI.h"

using namespace bellshire::GUI;

Notes_GUI_Base::Notes_GUI_Base()
	:m_NotesTextCtrl(nullptr)
{

}

Notes_GUI_Base::Notes_GUI_Base(wxWindow* parent)
	:m_NotesTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_NotesTextCtrl);
}

Notes_GUI_Base::~Notes_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Notes MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="NotesTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Notes_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& NotesTextCtrl
)
{

	wxNotebook* NotesNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	NotesNotebook->Hide();
	NotesNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* NotesPanel(CreateNotesPanel(NotesNotebook, NotesTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(NotesNotebook,
		wxT("*********** Notes *************************\n\nThis element declares the content model for Notes, which contains a\nstring representing descriptive notes.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	NotesNotebook->AddPage(NotesPanel, wxT("MatML Data."), b_dflt);
	NotesNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return NotesNotebook;
}

wxWindow* Notes_GUI_Base::CreateNotesPanel(wxWindow* parent,
	wxTextCtrl*& NotesTextCtrl
)
{
	wxScrolledWindow* NotesPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	NotesPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer68 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer16 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer16->AddGrowableCol(1);
	fgSizer16->AddGrowableRow(0);
	fgSizer16->SetFlexibleDirection(wxBOTH);
	fgSizer16->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText12 = new wxStaticText(NotesPanel, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText12->Wrap(-1);
	fgSizer16->Add(staticText12, 1, wxALL | wxEXPAND, 5);

	NotesTextCtrl = new wxTextCtrl(NotesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	fgSizer16->Add(NotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer68->Add(fgSizer16, 1, wxEXPAND, 5);

	NotesPanel->SetSizer(bSizer68);
	NotesPanel->Layout();
	bSizer68->Fit(NotesPanel);

	return NotesPanel;
}

void Notes_GUI_Base::Update( const observer_ptr<Notes> element)
{
	if (element) {
		wxString str;

		str << _std2wx((*element));//double parenthesis required
		m_NotesTextCtrl->ChangeValue(str);

		ShowGUI(true);
	}
}

wxString Notes_GUI_Base::GetTreeLabel(const observer_ptr<Notes> element)
{
	wxString str;
	str << wxT("Notes");

	return str;
}


void Notes_GUI_Base::SetConnect()
{
	m_NotesTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Notes_GUI_Base::OnNotesTextCtrl), NULL, this);
	m_NotesTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Notes_GUI_Base::OnNotesTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Notes_GUI::Notes_GUI() : Notes_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Notes_GUI::Notes_GUI(wxWindow* parent)
	: Notes_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Notes_GUI::~Notes_GUI() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Notes_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Notes_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Notes_GUI::OnNotesTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Notes* Element = boost::any_cast<Notes*>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_NotesTextCtrl->GetValue());
//			Notes NewData((const char*) str.mb_str(wxConvUTF8));
			Notes NewData(::xml_schema::string(str.mb_str()));
			(*Element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; };

}
