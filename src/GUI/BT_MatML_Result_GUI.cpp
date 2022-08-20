#include <wx/config.h>
#include "GUI/BT_MatML_Result_GUI.h"

using namespace bellshire;

Result_GUI_Base::Result_GUI_Base()
	:m_GUI(nullptr),
	m_ResultTextCtrl(nullptr)
{

}

Result_GUI_Base::Result_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ResultTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ResultTextCtrl);
}

Result_GUI_Base::~Result_GUI_Base() {
	/*parent will distroy Ctrl or window */
}



/// <summary>
/// Create the GUI for the Result MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Result_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& ResultTextCtrl)
{
	wxNotebook* ResultNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ResultNotebook->Hide();
	ResultNotebook->SetMinSize(wxSize(100, 100));

	wxScrolledWindow* ResultPanel = new wxScrolledWindow(ResultNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	bSizer1->Add(fgSizer1, 1, wxEXPAND|wxALL, 5);

	ResultPanel->SetSizer(bSizer1);
	ResultPanel->Layout();
	bSizer1->Fit(ResultPanel);

	MatMLInfo_GUI matMLInfo_GUI(ResultNotebook,
		wxT("************ Results *************************\n\nResult is a string that contains a description of the outcome or result\n of the processing step and may occur once or not at all within the\nProcessingDetails element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ResultNotebook->AddPage(ResultPanel, wxT("MatML Data."), b_dflt);
	ResultNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ResultNotebook;
}


void Result_GUI_Base::Update( Result* element)
{
	wxString str;
	str.clear();

	str << _std2wx((*element->t));//double paranthesis required
	m_ResultTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Result_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	ProcessingDetails::Result_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Result");

	wxTreeItemId CurrentId;

	Result* strongtypedefstruct = new Result(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));

	//Setup MatML Attribute
	//--NONE--

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
		Result* Element = boost::any_cast<Result*>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_ResultTextCtrl->GetValue());
			ProcessingDetails::Result_type NewData(::xml_schema::string(str.mb_str()));
			*Element->t = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; };

}