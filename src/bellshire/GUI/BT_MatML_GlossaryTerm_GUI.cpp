#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_GlossaryTerm_GUI.h"

using namespace bellshire::GUI;

GlossaryTerm_GUI_Base::GlossaryTerm_GUI_Base()
{

}

GlossaryTerm_GUI_Base::GlossaryTerm_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

GlossaryTerm_GUI_Base::~GlossaryTerm_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the GlossaryTerm MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="GlossaryTermNotebook"></param>
/// <param name="GlossaryTermPanel"></param>
/// <returns>bool</returns>
wxNotebook* GlossaryTerm_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* GlossaryTermNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	GlossaryTermNotebook->Hide();
	GlossaryTermNotebook->SetMinSize(wxSize(100, 100));

	wxWindow* GlossaryTermPanel(CreateGlossaryTermPanel(GlossaryTermNotebook));

	MatMLInfo_GUI matMLInfo_GUI(GlossaryTermNotebook,
		wxT("************* GlossaryTerm *************************\n\nThis element declares the content model for GlossaryTerm which is\ncomposed of the following elements.\n\nName contains the term's name and has one optional attribute,\nauthority, for identifying an authoritative source of terms. Name must\noccur once and only once within the Term element.\n\nDefinition contains the term's definition and must occur once and only\nonce within the Term element.\n\nAbbreviation contains the term's abbreviations and may occur zero\nor more times within the Term element.\n\nSynonym contains the term's synonyms and may occur zero or more\ntimes within the Term element.\n\nNotes contains any additional information concerning the term and may\noccur once or not at all within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GlossaryTermNotebook->AddPage(GlossaryTermPanel, wxT("MatML Data."), b_dflt);
	GlossaryTermNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GlossaryTermNotebook;
}

wxWindow* GlossaryTerm_GUI_Base::CreateGlossaryTermPanel(wxWindow* parent)
{
	wxScrolledWindow* GlossaryTermPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GlossaryTermPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText1 = new wxStaticText(GlossaryTermPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText1, 0, wxALL, 5);

	GlossaryTermPanel->SetSizer(bSizer1);
	GlossaryTermPanel->Layout();
	bSizer1->Fit(GlossaryTermPanel);

	return GlossaryTermPanel;
}

void GlossaryTerm_GUI_Base::Update( const observer_ptr<GlossaryTerm> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString GlossaryTerm_GUI_Base::GetTreeLabel(const observer_ptr<GlossaryTerm> element)
{
	wxString str;
	str << wxT("GlossaryTerm");
	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
GlossaryTerm_GUI::GlossaryTerm_GUI() 
	: GlossaryTerm_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
GlossaryTerm_GUI::GlossaryTerm_GUI(wxWindow* parent)
	: GlossaryTerm_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
GlossaryTerm_GUI::~GlossaryTerm_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* GlossaryTerm_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any GlossaryTerm_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void GlossaryTerm_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void GlossaryTerm_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void GlossaryTerm_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void GlossaryTerm_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(GlossaryTerm, Name) }
void GlossaryTerm_GUI::OnInsertDefinition(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(GlossaryTerm, Definition) }
void GlossaryTerm_GUI::OnInsertAbbreviation(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(GlossaryTerm, Abbreviation) }
void GlossaryTerm_GUI::OnInsertSynonym(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(GlossaryTerm, Synonym) }
void GlossaryTerm_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(GlossaryTerm, Notes) }

void GlossaryTerm_GUI::OnDeleteDefinition(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(GlossaryTerm, GlossaryTerm::Definition)}
void GlossaryTerm_GUI::OnDeleteAbbreviation(wxCommandEvent& event)
{
	// The following is hand crafted to allow for the Glossary::Term being the container for GlossaryTerm element type.
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));
	try {
		GlossaryTerm* const elementParent = boost::any_cast<GlossaryTerm* const>(itemParent->GetAnyMatMLDataPointer());
		if (elementParent != 0) {
			GlossaryTerm::Abbreviation_type* const element = boost::any_cast<GlossaryTerm::Abbreviation_type* const>(item->GetAnyMatMLDataPointer());
			if (element != 0) {
				GlossaryTerm::Abbreviation_sequence& cont(elementParent->Abbreviation());
				GlossaryTerm::Abbreviation_iterator iter(cont.begin());
				for (; iter != cont.end(); ++iter) {
					if (&(*iter) == element) {
						cont.erase(iter);
						m_MatMLTreeCtrl->Delete(itemId);
						return;
					}
				}
			}
		}
	}
	catch (const boost::bad_any_cast&) {}
}
void GlossaryTerm_GUI::OnDeleteSynonym(wxCommandEvent& event)
{
	// The following is hand crafted to allow for the Glossary::Term being the container for GlossaryTerm element type.
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));
	try {
		GlossaryTerm* const elementParent = boost::any_cast<GlossaryTerm* const>(itemParent->GetAnyMatMLDataPointer());
		if (elementParent != 0) {
			GlossaryTerm::Synonym_type* const element = boost::any_cast<GlossaryTerm::Synonym_type* const>(item->GetAnyMatMLDataPointer());
			if (element != 0) {
				GlossaryTerm::Synonym_sequence& cont(elementParent->Abbreviation());
				GlossaryTerm::Synonym_iterator iter(cont.begin());
				for (; iter != cont.end(); ++iter) {
					if (&(*iter) == element) {
						cont.erase(iter);
						m_MatMLTreeCtrl->Delete(itemId);
						return;
					}
				}
			}
		}
	}
	catch (const boost::bad_any_cast&) {}
}
void GlossaryTerm_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(GlossaryTerm, Notes)}

void GlossaryTerm_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(GlossaryTerm, Name) }
void GlossaryTerm_GUI::OnPasteDefinition(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(GlossaryTerm, Definition) }
void GlossaryTerm_GUI::OnPasteAbbreviation(wxCommandEvent& event) {
	//ON_PARENT_PASTE_ITER_CONT_CHILD(GlossaryTerm, Abbreviation)
	ON_PARENT_PASTE_ITER_CONT_CHILD(GlossaryTerm, Abbreviation)

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	GlossaryTerm* const element = boost::any_cast<GlossaryTerm* const>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		GlossaryTerm::Abbreviation_type* const copy_element = boost::any_cast<GlossaryTerm::Abbreviation_type* const>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			GlossaryTerm::Abbreviation_sequence& cont(element->Synonym());
	//			try {
	//				cont.push_back(*copy_element);

	//				Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), itemId });
	//				GlossaryTerm_GUI::TraverseMatMLTree(element, func1);

	//				m_MatMLTreeCtrl->Delete(itemId);
	//				m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
	//				return;
	//			}
	//			catch (const xml_schema::duplicate_id&) { return; }
	//		}
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}
void GlossaryTerm_GUI::OnPasteSynonym(wxCommandEvent& event) {
	ON_PARENT_PASTE_ITER_CONT_CHILD(GlossaryTerm, Synonym)

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	GlossaryTerm* const element = boost::any_cast<GlossaryTerm* const>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		GlossaryTerm::Synonym_type* const copy_element = boost::any_cast<GlossaryTerm::Synonym_type* const>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			GlossaryTerm::Synonym_sequence& cont(element->Synonym());
	//			try {
	//				cont.push_back(*copy_element);

	//				Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), itemId});
	//				GlossaryTerm_GUI::TraverseMatMLTree(element, func1);
	//				m_MatMLTreeCtrl->Delete(itemId);
	//				m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
	//				return;
	//			}
	//			catch (const xml_schema::duplicate_id&) { return; }
	//		}
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}
void GlossaryTerm_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(GlossaryTerm, Notes) }


void GlossaryTerm_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< GlossaryTerm,
		Glossary,
		Glossary::Term_sequence,
		GlossaryTerm_GUI,
		&Glossary::Term
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void GlossaryTerm_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< GlossaryTerm,
		Glossary,
		Glossary::Term_sequence,
		GlossaryTerm_GUI,
		&Glossary::Term
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

