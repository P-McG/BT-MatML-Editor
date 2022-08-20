#include <wx/config.h>
#include "BT_MatML_CurrencyCode_GUI.h"

using namespace bellshire;

CurrencyCode_GUI_Base::CurrencyCode_GUI_Base()
	:m_GUI(nullptr), m_CurrencyCodeChoice(nullptr)
{

}

CurrencyCode_GUI_Base::CurrencyCode_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_CurrencyCodeChoice(nullptr)
{
	m_GUI = Create(parent, m_CurrencyCodeChoice);
}

CurrencyCode_GUI_Base::~CurrencyCode_GUI_Base() {
	/*parent will distroy Ctrl or window */
}



/// <summary>
/// Create the GUI for the CurrencyCode MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="CurrencyCodeNotebook"></param>
/// <param name="CurrencyCodePanel"></param>
/// <param name="CurrencyCodeChoice"></param>
/// <returns>bool</returns>
wxNotebook* CurrencyCode_GUI_Base::Create(wxWindow* parent, wxChoice*& CurrencyCodeChoice)
{
	wxNotebook* CurrencyCodeNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	CurrencyCodeNotebook->Hide();
	CurrencyCodeNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* CurrencyCodePanel = new wxScrolledWindow(CurrencyCodeNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	CurrencyCodePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer100 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer37 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer37->SetFlexibleDirection(wxBOTH);
	fgSizer37->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText55 = new wxStaticText(CurrencyCodePanel, wxID_ANY, wxT("Currency Code"), wxDefaultPosition, wxDefaultSize, 0);
	staticText55->Wrap(-1);
	fgSizer37->Add(staticText55, 0, wxALL, 5);

	wxString CurrencyCodeChoiceChoices[] = { wxT("CAD"), wxT("USD") };
	int CurrencyCodeChoiceNChoices = sizeof(CurrencyCodeChoiceChoices) / sizeof(wxString);
	CurrencyCodeChoice = new wxChoice(CurrencyCodePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, CurrencyCodeChoiceNChoices, CurrencyCodeChoiceChoices, 0);
	CurrencyCodeChoice->SetSelection(0);
	fgSizer37->Add(CurrencyCodeChoice, 0, wxALL, 5);

	bSizer100->Add(fgSizer37, 1, wxEXPAND, 5);

	CurrencyCodePanel->SetSizer(bSizer100);
	CurrencyCodePanel->Layout();
	bSizer100->Fit(CurrencyCodePanel);

	MatMLInfo_GUI matMLInfo_GUI(CurrencyCodeNotebook,
		wxT("***** ISO4217_CurrencyCode *************************\n\nBased on ISO-4217, and taken from paper N699 on http://www.jtc1sc32.org/\nAs of 2003-12-11 permission to use this element has been sought from, but not yet been granted by, the authors of the paper.\n\nThis element declares the content model for value, which contains a string representing a currency.\n\t\t\t\nFor the most current updates, refer to\t\thttp://www.din.de/gremien/nas/nabd/iso4217ma/codlistp1/en_listp1.html\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	CurrencyCodeNotebook->AddPage(CurrencyCodePanel, wxT("MatML Data."), b_dflt);
	CurrencyCodeNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return CurrencyCodeNotebook;
}


void CurrencyCode_GUI_Base::Update( CurrencyCode* element)
{
	/*	wxString str;

		str<< _std2wx((*element));//double paranthesis required
		m_CurrencyCodeChoice->SetStringSelection(str);
	*/
	// this->Freeze();
	Show(true);
}


/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId  CurrencyCode_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	CurrencyCode& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("CurrencyCode");

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

void CurrencyCode_GUI_Base::SetConnect()
{
	m_CurrencyCodeChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CurrencyCode_GUI_Base::OnCurrencyCodeChoice), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
CurrencyCode_GUI::CurrencyCode_GUI() : CurrencyCode_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
CurrencyCode_GUI::CurrencyCode_GUI(wxWindow* parent)
	: CurrencyCode_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
CurrencyCode_GUI::~CurrencyCode_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void CurrencyCode_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void CurrencyCode_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void CurrencyCode_GUI::OnCurrencyCodeChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		CurrencyCode* const Element = boost::any_cast<CurrencyCode* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_CurrencyCodeChoice->GetStringSelection());
			CurrencyCode NewData((const char*)str.mb_str(wxConvUTF8));
			(*Element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}
