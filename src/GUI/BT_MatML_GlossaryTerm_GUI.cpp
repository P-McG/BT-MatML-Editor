#include <wx/config.h>
#include "BT_MatML_GlossaryTerm_GUI.h"

using namespace bellshire;

GlossaryTerm_GUI_Base::GlossaryTerm_GUI_Base()
	:m_GUI(nullptr)
{

}

GlossaryTerm_GUI_Base::GlossaryTerm_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

GlossaryTerm_GUI_Base::~GlossaryTerm_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* GlossaryTermPanel = new wxScrolledWindow(GlossaryTermNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GlossaryTermPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText1 = new wxStaticText(GlossaryTermPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText1, 0, wxALL, 5);

	GlossaryTermPanel->SetSizer(bSizer1);
	GlossaryTermPanel->Layout();
	bSizer1->Fit(GlossaryTermPanel);

	MatMLInfo_GUI matMLInfo_GUI(GlossaryTermNotebook,
		wxT("************* GlossaryTerm *************************\n\nThis element declares the content model for GlossaryTerm which is\ncomposed of the following elements.\n\nName contains the term's name and has one optional attribute,\nauthority, for identifying an authoritative source of terms. Name must\noccur once and only once within the Term element.\n\nDefinition contains the term's definition and must occur once and only\nonce within the Term element.\n\nAbbreviation contains the term's abbreviations and may occur zero\nor more times within the Term element.\n\nSynonym contains the term's synonyms and may occur zero or more\ntimes within the Term element.\n\nNotes contains any additional information concerning the term and may\noccur once or not at all within the Term element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GlossaryTermNotebook->AddPage(GlossaryTermPanel, wxT("MatML Data."), b_dflt);
	GlossaryTermNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GlossaryTermNotebook;
}


void GlossaryTerm_GUI_Base::Update( GlossaryTerm* element)
{
	//Nothing to update

	Show(true);
}

/// <summary>
/// 
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// 
/// In this function the children GlossaryTerm::Definition, GlossaryTerm::Abbreviation, GlossaryTerm::Synonym are NOT called
/// due to the boost::any_cast not being able to differentiate each from a typedef of ::xml_schema::string
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId GlossaryTerm_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	GlossaryTerm& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("GlossaryTerm");

	wxTreeItemId CurrentId;
		MatMLTreeItemData* data = new MatMLTreeItemData(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, data);
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, data);

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup MatML Element
	// 
	//Setup Element Definition
	if (Element.Definition() != "") 
		Definition_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Definition(), wxTreeItemId());
	

	//Setup Element GlossaryTerm::Abbreviation
	{
		GlossaryTerm::Abbreviation_sequence& cont(Element.Abbreviation());
		GlossaryTerm::Abbreviation_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter) {
				Abbreviation_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
			}
	}
	//Synonym
	{
		GlossaryTerm::Synonym_sequence& cont(Element.Synonym());
		GlossaryTerm::Synonym_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter) {
				Synonym_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
			}
	}

	//Setup Element Notes
	{
		GlossaryTerm::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		GlossaryTerm* const element = boost::any_cast<GlossaryTerm* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			GlossaryTerm::Abbreviation_type* const copy_element = boost::any_cast<GlossaryTerm::Abbreviation_type* const>(m_MatMLItemToCopy);
			if (copy_element != 0) {
				GlossaryTerm::Abbreviation_sequence& cont(element->Synonym());
				try {
					cont.push_back(*copy_element);
					GlossaryTerm_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
					return;
				}
				catch (const xml_schema::duplicate_id&) { return; }
			}
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}
void GlossaryTerm_GUI::OnPasteSynonym(wxCommandEvent& event) {
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		GlossaryTerm* const element = boost::any_cast<GlossaryTerm* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			GlossaryTerm::Synonym_type* const copy_element = boost::any_cast<GlossaryTerm::Synonym_type* const>(m_MatMLItemToCopy);
			if (copy_element != 0) {
				GlossaryTerm::Synonym_sequence& cont(element->Synonym());
				try {
					cont.push_back(*copy_element);
					GlossaryTerm_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
					return;
				}
				catch (const xml_schema::duplicate_id&) { return; }
			}
		}
	}
	catch (const boost::bad_any_cast&) { return; }
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

	try {
		if (anyptrparent.type() == typeid(Glossary*)) {
			GlossaryTerm* element = boost::any_cast<GlossaryTerm*>(anyptr);
			Glossary* elementParent = boost::any_cast<Glossary*>(anyptrparent);

			auto& cont = elementParent->Term();
			std::pair<GlossaryTerm*, GlossaryTerm*> data(MatMLFindAndBumpDown(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<GlossaryTerm_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

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

	try {
		if (anyptrparent.type() == typeid(Glossary*)) {
			GlossaryTerm* element = boost::any_cast<GlossaryTerm*>(anyptr);
			Glossary* elementParent = boost::any_cast<Glossary*>(anyptrparent);

			auto& cont = elementParent->Term();
			std::pair<GlossaryTerm*, GlossaryTerm*> data(MatMLFindAndBumpUp(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<GlossaryTerm_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

}

