#include <wx/config.h>
#include "BT_MatML_Synonym_GUI.h"

using namespace bellshire;

Synonym_GUI_Base::Synonym_GUI_Base()
	:m_GUI(nullptr),
	m_SynonymTextCtrl(nullptr)
{

}

Synonym_GUI_Base::Synonym_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_SynonymTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_SynonymTextCtrl);
}

Synonym_GUI_Base::~Synonym_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Synonym MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Synonym_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& SynonymTextCtrl)
{
	wxNotebook* SynonymNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SynonymNotebook->Hide();
	SynonymNotebook->SetMinSize(wxSize(100, 100));

	wxScrolledWindow* SynonymPanel = new wxScrolledWindow(SynonymNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SynonymPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(SynonymPanel, wxID_ANY, wxT("Synonym"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);

	SynonymTextCtrl = new wxTextCtrl(SynonymPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer1->Add(SynonymTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

	SynonymPanel->SetSizer(bSizer1);
	SynonymPanel->Layout();
	bSizer1->Fit(SynonymPanel);

	MatMLInfo_GUI matMLInfo_GUI(SynonymNotebook,
		wxT("************* Synonym *************************\n\nSynonym contains the term's synonyms and may occur zero or more\ntimes within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SynonymNotebook->AddPage(SynonymPanel, wxT("MatML Data."), b_dflt);
	SynonymNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SynonymNotebook;
}

void Synonym_GUI_Base::Update( Synonym* element)
{
	wxString str;
	str.clear();

	str << _std2wx((*element->t));//double paranthesis required
	m_SynonymTextCtrl->ChangeValue(str);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Synonym_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	GlossaryTerm::Synonym_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Synonym");

	wxTreeItemId CurrentId;

	Synonym* strongtypedefstruct = new Synonym(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));

	//Setup MatML Attribute
	//--NONE--

	return CurrentId;
}

void Synonym_GUI_Base::SetConnect()
{
	m_SynonymTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Synonym_GUI_Base::OnSynonymTextCtrl), NULL, this);
	m_SynonymTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Synonym_GUI_Base::OnSynonymTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Synonym_GUI::Synonym_GUI() : Synonym_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Synonym_GUI::Synonym_GUI(wxWindow* parent)
	: Synonym_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Synonym_GUI::~Synonym_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Synonym_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Synonym_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Synonym_GUI::OnSynonymTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Synonym* element = boost::any_cast<Synonym* >(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			wxString str(m_SynonymTextCtrl->GetValue());
			GlossaryTerm::Synonym_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element->t = NewData;//t required due to strong_typedef
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}