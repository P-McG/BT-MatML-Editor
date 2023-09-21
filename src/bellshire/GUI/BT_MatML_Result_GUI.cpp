#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Result_GUI.h"

using namespace bellshire::GUI;

Result_GUI_Base::Result_GUI_Base()
	:m_ResultTextCtrl(nullptr)
{

}

Result_GUI_Base::Result_GUI_Base(wxWindow* parent)
	:m_ResultTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ResultTextCtrl);
}

Result_GUI_Base::~Result_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Result_GUI_Base::GetResultTextCtrl()
{
	return m_ResultTextCtrl;
}



/// <summary>
/// Create the GUI for the Result MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Result_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& ResultTextCtrl
)
{
	wxNotebook* ResultNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ResultNotebook->Hide();
	ResultNotebook->SetMinSize(wxSize(100, 100));

	wxWindow* ResultPanel(CreateResultPanel(ResultNotebook, ResultTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(ResultNotebook,
		wxT("************ Results *************************\n\nResult is a string that contains a description of the outcome or result\n of the processing step and may occur once or not at all within the\nProcessingDetails element.")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ResultNotebook->AddPage(ResultPanel, wxT("MatML Data."), b_dflt);
	ResultNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ResultNotebook;
}

wxWindow* Result_GUI_Base::CreateResultPanel(wxWindow* parent,
	wxTextCtrl*& ResultTextCtrl
)
{

	wxScrolledWindow* ResultPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ResultPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->AddGrowableRow(0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(ResultPanel, wxID_ANY, wxT("Result/Outcome"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);

	ResultTextCtrl = new wxTextCtrl(ResultPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	fgSizer1->Add(ResultTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer1, 1, wxEXPAND | wxALL, 5);

	ResultPanel->SetSizer(bSizer1);
	ResultPanel->Layout();
	bSizer1->Fit(ResultPanel);

	return ResultPanel;
}

void Result_GUI_Base::Update( const observer_ptr<Result > element)
{
	auto element_observer{(remove_strongly_typed_on_observer_ptr_v(element))};
	if(element_observer) {
		wxString str;
		str.clear();

		str << _std2wx((*element_observer));//double parenthesis required
		m_ResultTextCtrl->ChangeValue(str);

		ShowGUI(true);
	}
}

wxString Result_GUI_Base::GetTreeLabel(const observer_ptr<Result> element)
{
	wxString str;
	str << wxT("Result");

	return str;
}


void Result_GUI_Base::SetConnect()
{
	m_ResultTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Result_GUI_Base::OnResultTextCtrl), NULL, this);
	m_ResultTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Result_GUI_Base::OnResultTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Result_GUI::Result_GUI() : Result_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Result_GUI::Result_GUI(wxWindow* parent)
	: Result_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Result_GUI::~Result_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Result_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Result_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Result_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Result_GUI::OnResultTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		 auto element_observer = remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Result>>(item->GetAnyMatMLDataPointer()));
		if (element_observer) {
			wxString str(m_ResultTextCtrl->GetValue());
			ProcessingDetails::Result_type NewData(::xml_schema::string(str.mb_str()));
			*element_observer = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; };

}