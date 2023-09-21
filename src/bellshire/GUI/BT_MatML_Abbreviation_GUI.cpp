#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Abbreviation_GUI.h"

using namespace bellshire::GUI;

bellshire::GUI::Abbreviation_GUI_Base::Abbreviation_GUI_Base()
{
}

Abbreviation_GUI_Base::Abbreviation_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent, m_AbbreviationTextCtrl);
}



/// <summary>
/// Create the GUI for the Abbreviation MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Abbreviation_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& AbbreviationTextCtrl
)
{
	wxNotebook* AbbreviationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	AbbreviationNotebook->Hide();
	AbbreviationNotebook->SetMinSize(wxSize(100, 100));

	wxWindow* AbbreviationPanel(CreateAbbreviationPanel(AbbreviationNotebook, AbbreviationTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(AbbreviationNotebook,
		wxT("************* Abbreviation *************************\n\nAbbreviation contains the term's abbreviations and may occur zero\nor more times within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);;

	AbbreviationNotebook->AddPage(AbbreviationPanel, wxT("MatML Data."), b_dflt);
	AbbreviationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return AbbreviationNotebook;
}

wxWindow* Abbreviation_GUI_Base::CreateAbbreviationPanel(wxWindow* parent,
	wxTextCtrl*& AbbreviationTextCtrl
)
{
	wxScrolledWindow* AbbreviationPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return AbbreviationPanel;
}

void Abbreviation_GUI_Base::Update( const observer_ptr<Abbreviation> element)
{
	wxString str;
	str.clear();

	//str << _std2wx((*(element->t)));//double parenthesis required


	if (auto tmp = remove_strongly_typed_on_observer_ptr_v(element)) {
		str << _std2wx((*tmp));//double parenthesis required
		m_AbbreviationTextCtrl->ChangeValue(str);
	}
	
	ShowGUI(true);
}

wxTextCtrl* bellshire::GUI::Abbreviation_GUI_Base::GetAbbreviationTextCtrl()
{
	return m_AbbreviationTextCtrl;
}

wxString Abbreviation_GUI_Base::GetTreeLabel(const observer_ptr<Abbreviation> Element)
{
	wxString str;
	str << wxT("Abbreviation");

	return str;
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
	: Abbreviation_GUI_Base(parent)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Abbreviation_GUI::~Abbreviation_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Abbreviation_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
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
		auto element_observer{ 
			remove_strongly_typed_on_observer_ptr_v(
				boost::any_cast<observer_ptr<Abbreviation>>
				(item->GetAnyMatMLDataPointer()))
		};

		wxString str(GetAbbreviationTextCtrl()->GetValue());
		GlossaryTerm::Abbreviation_type NewData(::xml_schema::string(str.mb_str()));
		if (element_observer) {
			*element_observer = NewData;
		}
		return;
	}

	catch (const boost::bad_any_cast&) { return; };
}

void Abbreviation_GUI::OnBumpDown(wxCommandEvent & event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Abbreviation,
		GlossaryTerm,
		GlossaryTerm::Abbreviation_sequence,
		Abbreviation_GUI,
		&GlossaryTerm::Abbreviation
	>
	(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Abbreviation_GUI::OnBumpUp(wxCommandEvent & event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Abbreviation,
		GlossaryTerm,
		GlossaryTerm::Abbreviation_sequence,
		Abbreviation_GUI,
		&GlossaryTerm::Abbreviation
	>
	(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}