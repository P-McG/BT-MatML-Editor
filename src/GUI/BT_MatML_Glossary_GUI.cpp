#include <wx/config.h>
#include "BT_MatML_Glossary_GUI.h"

using namespace bellshire;

Glossary_GUI_Base::Glossary_GUI_Base()
	:m_GUI(nullptr)
{

}

Glossary_GUI_Base::Glossary_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Glossary_GUI_Base::~Glossary_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Glossary MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Glossary_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* GlossaryNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	GlossaryNotebook->Hide();
	GlossaryNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* GlossaryPanel = new wxScrolledWindow(GlossaryNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GlossaryPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(GlossaryPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	GlossaryPanel->SetSizer(bSizer1);
	GlossaryPanel->Layout();
	bSizer1->Fit(GlossaryPanel);

	MatMLInfo_GUI matMLInfo_GUI(GlossaryNotebook,
		wxT("******************* Glossary *************************\n\nThis element declares the content model for Glossary, which contains\ndescriptions of material and property terms used in the document.\nGlossary must contain one or more Term elements.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GlossaryNotebook->AddPage(GlossaryPanel, wxT("MatML Data."), b_dflt);
	GlossaryNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GlossaryNotebook;
}

void Glossary_GUI_Base::Update( Glossary* element)
{
	//Nothing to update

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Glossary_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId,
	Glossary& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Glossary");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element GlossaryTerm
	{
		Glossary::Term_sequence& cont(Element.Term());
		Glossary::Term_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				GlossaryTerm_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}
	return CurrentId;
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Glossary_GUI::Glossary_GUI() 
	: Glossary_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Glossary_GUI::Glossary_GUI(wxWindow* parent)
	: Glossary_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Glossary_GUI::~Glossary_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Glossary_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Glossary_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Glossary_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Glossary_GUI::OnInsertTerm(wxCommandEvent& event) {
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		Glossary* const element = boost::any_cast<Glossary* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			Glossary::Term_sequence& cont(element->Term());
			cont.push_back(Default<::GlossaryTerm>());
			Glossary_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, m_MatMLTreeCtrl->GetPrevSibling(itemId));
			
			m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
			m_MatMLTreeCtrl->Delete(itemId);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Glossary_GUI::OnDeleteGlossaryTerm(wxCommandEvent& event)
{
	// The following is hand crafted to allow for the Glossary::Term being the container for GlossaryTerm element type.
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));
	try {
		Glossary* const elementParent = boost::any_cast<Glossary* const>(itemParent->GetAnyMatMLDataPointer());
		if (elementParent != 0) {
			GlossaryTerm* const element = boost::any_cast<GlossaryTerm* const>(item->GetAnyMatMLDataPointer());
			if (element != 0) {
				Glossary::Term_sequence& cont(elementParent->Term());
				Glossary::Term_iterator iter(cont.begin());
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

void Glossary_GUI::OnPasteTerm(wxCommandEvent& event) {
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		Glossary* const element = boost::any_cast<Glossary* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			GlossaryTerm* const copy_element = boost::any_cast<GlossaryTerm* const>(m_MatMLItemToCopy);
			if (copy_element != 0) {
				Glossary::Term_sequence& cont(element->Term());
				try {
					cont.push_back(*copy_element);
					Glossary_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
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