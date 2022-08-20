#include <wx/config.h>

#include "GUI/BT_MatML_Abbreviation_GUI.h"

using namespace bellshire;

Abbreviation_GUI_Base::Abbreviation_GUI_Base()
	:m_GUI(nullptr),
	m_AbbreviationTextCtrl(nullptr)
{

}

Abbreviation_GUI_Base::Abbreviation_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_AbbreviationTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_AbbreviationTextCtrl);
}

Abbreviation_GUI_Base::~Abbreviation_GUI_Base() {
	/*parent will distroy Ctrl or window */
}



/// <summary>
/// Create the GUI for the Abbreviation MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Abbreviation_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& AbbreviationTextCtrl)
{
	wxNotebook* AbbreviationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	AbbreviationNotebook->Hide();
	AbbreviationNotebook->SetMinSize(wxSize(100, 100));

	wxScrolledWindow* AbbreviationPanel = new wxScrolledWindow(AbbreviationNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	AbbreviationPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(AbbreviationPanel, wxID_ANY, wxT("Abbreviation"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);

	AbbreviationTextCtrl = new wxTextCtrl(AbbreviationPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer1->Add(AbbreviationTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

	AbbreviationPanel->SetSizer(bSizer1);
	AbbreviationPanel->Layout();
	bSizer1->Fit(AbbreviationPanel);

	MatMLInfo_GUI matMLInfo_GUI(AbbreviationNotebook,
		wxT("************* Abbreviation *************************\n\nAbbreviation contains the term's abbreviations and may occur zero\nor more times within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);;

	AbbreviationNotebook->AddPage(AbbreviationPanel, wxT("MatML Data."), b_dflt);
	AbbreviationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return AbbreviationNotebook;
}


void Abbreviation_GUI_Base::Update( Abbreviation* element)
{
	wxString str;
	str.clear();

	str << _std2wx((*(element->t)));//double paranthesis required
	m_AbbreviationTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Abbreviation_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	GlossaryTerm::Abbreviation_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Abbreviation");

	wxTreeItemId CurrentId;

	Abbreviation* strongtypedefstruct = new Abbreviation(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));

	//Setup MatML Attribute
	//--NONE--

	return CurrentId;
}

void Abbreviation_GUI_Base::SetConnect()
{
	m_AbbreviationTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Abbreviation_GUI_Base::OnAbbreviationTextCtrl), NULL, this);
	m_AbbreviationTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Abbreviation_GUI_Base::OnAbbreviationTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Abbreviation_GUI::Abbreviation_GUI() : Abbreviation_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Abbreviation_GUI::Abbreviation_GUI(wxWindow* parent)
	: Abbreviation_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Abbreviation_GUI::~Abbreviation_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Abbreviation_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Abbreviation_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Abbreviation_GUI::OnAbbreviationTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Abbreviation* Element = boost::any_cast<Abbreviation*>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_AbbreviationTextCtrl->GetValue());
			GlossaryTerm::Abbreviation_type NewData(::xml_schema::string(str.mb_str()));
			*Element->t = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; };

}