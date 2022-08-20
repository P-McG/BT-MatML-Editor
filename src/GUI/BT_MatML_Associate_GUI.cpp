#include <wx/config.h>

#include "BT_MatML_Associate_GUI.h"

using namespace bellshire;

Associate_GUI_Base::Associate_GUI_Base() :m_GUI(nullptr),m_AssociateTextCtrl(nullptr)
{

}

Associate_GUI_Base::Associate_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_AssociateTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_AssociateTextCtrl);
}

Associate_GUI_Base::~Associate_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Associate MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="AssociateNotebook"></param>
/// <param name="AssociatePanel"></param>
/// <param name="AssociateTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Associate_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& AssociateTextCtrl)
{
	wxNotebook* AssociateNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	AssociateNotebook->Hide();
	AssociateNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* AssociatePanel = new wxScrolledWindow(AssociateNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	AssociatePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer25 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer9 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer9->AddGrowableCol(1);
	fgSizer9->AddGrowableRow(0);
	fgSizer9->SetFlexibleDirection(wxBOTH);
	fgSizer9->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText6 = new wxStaticText(AssociatePanel, wxID_ANY, wxT("Associate"), wxDefaultPosition, wxDefaultSize, 0);
	staticText6->Wrap(-1);
	fgSizer9->Add(staticText6, 0, wxALL, 5);

	AssociateTextCtrl = new wxTextCtrl(AssociatePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB);
	fgSizer9->Add(AssociateTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer25->Add(fgSizer9, 1, wxALL | wxEXPAND, 5);

	AssociatePanel->SetSizer(bSizer25);
	AssociatePanel->Layout();
	bSizer25->Fit(AssociatePanel);

	MatMLInfo_GUI matMLInfo_GUI(AssociateNotebook,
		wxT("********** Associate *************************\n\nThis element declares the content model for Associate, which contains\na string representing a component's associate.\n")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	AssociateNotebook->AddPage(AssociatePanel, wxT("MatML Data."), b_dflt);
	AssociateNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return AssociateNotebook;
}


void Associate_GUI_Base::Update(Associate* element)
{
	wxString str;

	str << _std2wx(( * element));
	m_AssociateTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// 
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
void Associate_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId,
	Associate& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Associate");

	wxTreeItemId CurrentId; if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//MatML Elements
	//--NONE--
}


/// <summary>
/// Set up the connect between the MatML_GUI and the functions
/// </summary>
void Associate_GUI_Base::SetConnect()
{
	m_AssociateTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Associate_GUI_Base::OnAssociateTextCtrl), NULL, this);
	m_AssociateTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Associate_GUI_Base::OnAssociateTextCtrl), NULL, this);
}

////////////////////derived class//////////////////////////////////


Associate_GUI::Associate_GUI() 
	: Associate_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

Associate_GUI::Associate_GUI(wxWindow* parent)
	: Associate_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

Associate_GUI::~Associate_GUI() 
{
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Associate_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Associate_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void Associate_GUI::OnAssociateTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Associate* Element = boost::any_cast<Associate* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_AssociateTextCtrl->GetValue());
			Associate NewData((const char*)str.mb_str(wxConvUTF8));
			*Element = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

	// TODO: Implement OnAssociate

}
