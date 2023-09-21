#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Synonym_GUI.h"

using namespace bellshire::GUI;

Synonym_GUI_Base::Synonym_GUI_Base()
	:m_SynonymTextCtrl(nullptr)
{

}

Synonym_GUI_Base::Synonym_GUI_Base(wxWindow* parent)
	:m_SynonymTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_SynonymTextCtrl);
}

Synonym_GUI_Base::~Synonym_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Synonym_GUI_Base::GetSynonymTextCtrl()
{
	return m_SynonymTextCtrl;
}


/// <summary>
/// Create the GUI for the Synonym MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Synonym_GUI_Base::Create(wxWindow* parent,
	wxTextCtrl*& SynonymTextCtrl
)
{
	wxNotebook* SynonymNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SynonymNotebook->Hide();
	SynonymNotebook->SetMinSize(wxSize(100, 100));

	wxWindow* SynonymPanel(CreateSynonymPanel(SynonymNotebook,
		SynonymTextCtrl
	));

	MatMLInfo_GUI matMLInfo_GUI(SynonymNotebook,
		wxT("************* Synonym *************************\n\nSynonym contains the term's synonyms and may occur zero or more\ntimes within the Term element.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SynonymNotebook->AddPage(SynonymPanel, wxT("MatML Data."), b_dflt);
	SynonymNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SynonymNotebook;
}

wxWindow* Synonym_GUI_Base::CreateSynonymPanel(wxWindow* parent,
	wxTextCtrl*& SynonymTextCtrl
)
{

	wxScrolledWindow* SynonymPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return SynonymPanel;
}

void Synonym_GUI_Base::Update( const observer_ptr<Synonym> element)
{
	auto element_observer{remove_strongly_typed_on_observer_ptr_v(element)};
	if (element_observer) {
		wxString str;
		str.clear();

		str << _std2wx((*element_observer));//double parenthesis required
		m_SynonymTextCtrl->ChangeValue(str);

		ShowGUI(true);
	}
}

wxString Synonym_GUI_Base::GetTreeLabel(const observer_ptr<Synonym> element)
{
	wxString str;
	str << wxT("Synonym");

	return str;
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
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Synonym_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
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
		auto element_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Synonym>>(item->GetAnyMatMLDataPointer())) };
		if (element_observer) {
			wxString str(m_SynonymTextCtrl->GetValue());
			GlossaryTerm::Synonym_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element_observer = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}


void Synonym_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Synonym,
		GlossaryTerm,
		GlossaryTerm::Synonym_sequence,
		Synonym_GUI,
		&GlossaryTerm::Synonym
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Synonym_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Synonym,
		GlossaryTerm,
		GlossaryTerm::Synonym_sequence,
		Synonym_GUI,
		&GlossaryTerm::Synonym
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
