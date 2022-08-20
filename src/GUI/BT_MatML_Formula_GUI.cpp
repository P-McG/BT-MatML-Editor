#include <wx/config.h>
#include "BT_MatML_Formula_GUI.h"

using namespace bellshire;

Formula_GUI_Base::Formula_GUI_Base()
	:m_GUI(nullptr),
	m_FormulaTextCtrl(nullptr)
{

}

Formula_GUI_Base::Formula_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_FormulaTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_FormulaTextCtrl);
}

Formula_GUI_Base::~Formula_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Formula MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="FormulaTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Formula_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& FormulaTextCtrl)
{

	wxNotebook* FormulaNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	FormulaNotebook->Hide();
	FormulaNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* FormulaPanel = new wxScrolledWindow(FormulaNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	FormulaPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer55 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer14 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer14->AddGrowableCol(1);
	fgSizer14->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer14->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText9 = new wxStaticText(FormulaPanel, wxID_ANY, wxT("Formula"), wxDefaultPosition, wxDefaultSize, 0);
	staticText9->Wrap(-1);
	fgSizer14->Add(staticText9, 0, wxALL, 5);

	FormulaTextCtrl = new wxTextCtrl(FormulaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer14->Add(FormulaTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer55->Add(fgSizer14, 1, wxEXPAND, 5);

	FormulaPanel->SetSizer(bSizer55);
	FormulaPanel->Layout();
	bSizer55->Fit(FormulaPanel);

	MatMLInfo_GUI matMLInfo_GUI(FormulaNotebook,
		wxT("***************** Formula *************************\n\nFormula contains a string representation of the chemical formula for\nthe bulk material or component and must occur once and only once\nwithin the Characterization element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	FormulaNotebook->AddPage(FormulaPanel, wxT("MatML Data."), b_dflt);
	FormulaNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return FormulaNotebook;
}

void Formula_GUI_Base::Update( Formula* element)
{
	wxString str;

	str << _std2wx((*element));
	m_FormulaTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Formula_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Formula& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Formula");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Description
	//--NONE--
	return CurrentId;
}

void Formula_GUI_Base::SetConnect()
{
	m_FormulaTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Formula_GUI_Base::OnFormulaTextCtrl), NULL, this);
	m_FormulaTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Formula_GUI_Base::OnFormulaTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Formula_GUI::Formula_GUI() : Formula_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Formula_GUI::Formula_GUI(wxWindow* parent)
	: Formula_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Formula_GUI::~Formula_GUI() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Formula_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Formula_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Formula_GUI::OnFormulaTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Formula* const Element = boost::any_cast<Formula* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_FormulaTextCtrl->GetValue());
			Formula NewData((const char*)str.mb_str(wxConvUTF8));
			(*Element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};
