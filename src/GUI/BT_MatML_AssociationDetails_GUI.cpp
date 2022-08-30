#include <wx/config.h>

#include "BT_MatML_AssociationDetails_GUI.h"
#include "BT_MatML_GUI.h"
#include "BT_MatML_Base_GUI.h"


using namespace bellshire;

AssociationDetails_GUI_Base::AssociationDetails_GUI_Base() :m_GUI(nullptr)
{

}

AssociationDetails_GUI_Base::AssociationDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

AssociationDetails_GUI_Base::~AssociationDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the AssociationDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="AssociationDetailsNotebook"></param>
/// <param name="AssociationDetailsPanel"></param>
/// <returns>bool</returns>
wxNotebook* AssociationDetails_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* AssociationDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	AssociationDetailsNotebook->Hide();
	AssociationDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* AssociationDetailsPanel = new wxScrolledWindow(AssociationDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	AssociationDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer251 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(AssociationDetailsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer251->Add(staticText4, 0, wxALL, 5);

	AssociationDetailsPanel->SetSizer(bSizer251);
	AssociationDetailsPanel->Layout();
	bSizer251->Fit(AssociationDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(AssociationDetailsNotebook,
		wxT("********** AssociationDetails *************************\n\nThis element declares the content model for AssociationDetails, which\ncontains a description of a relationship of the component to another\ncomponent in a complex material system such as a composite, weld, or\nmultilayer material. AssociationDetails is composed of the following\nelements. \n\nAssociate contains the name of a component's associate. For example,\na TiC coating has been placed on AISI 1018 steel coupons. The\nAssociate of the steel, then, is the \"titanium carbide coating.\" Associate\nmust occur once and only once within the AssociationDetails element.\nRelationship contains a description of the relationship between a\ncomponent and the associate. For example, the associate of the \"steel\"\ncomponent is the \"titanium carbide coating.\" The relationship of the \"steel\" to the \"titanium carbide coating\" is that the steel is the \"substrate\" for the coating. Relationship must occur once and only once within the\nAssociationDetails element.\n\nNotes contains any additional information concerning the association and\nmay occur once or not at all within the AssociationDetails element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	AssociationDetailsNotebook->AddPage(AssociationDetailsPanel, wxT("MatML Data."), b_dflt);
	AssociationDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return AssociationDetailsNotebook;
}

void AssociationDetails_GUI_Base::Update( AssociationDetails* element)
{
	//Nothing to update

	Show(true);
}


void AssociationDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	AssociationDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("AssociationDetails");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup Elements Associate
	{
		AssociationDetails::Associate_optional& cont = Element.Associate();
		if (cont.present())
			Associate_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Relationship
	{
		AssociationDetails::Relationship_optional& cont = Element.Relationship();
		if (cont.present())
			Relationship_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		AssociationDetails::Notes_optional& cont = Element.Notes();
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}
}

void AssociationDetails_GUI_Base::SetConnect() {}

/// <summary>
/// Constructor for the derived class
/// </summary>
AssociationDetails_GUI::AssociationDetails_GUI() 
	: AssociationDetails_GUI_Base(), 
	m_MatMLTreeCtrl(nullptr),
	m_MatMLItemToCopy(0)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
AssociationDetails_GUI::AssociationDetails_GUI(wxWindow* parent)
	: AssociationDetails_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr),
	m_MatMLItemToCopy(0)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
AssociationDetails_GUI::~AssociationDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void AssociationDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void AssociationDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void AssociationDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}


/// <summary>
/// Matml_TreeCtrl EvtHandler functions for inserting children.
/// Bound my MaterialFrame using the bind function.
/// </summary>
/// <param name="event"></param>
void AssociationDetails_GUI::OnInsertAssociate(wxCommandEvent& event) 
{ 	
	ON_PARENT_INSERT_CONT_CHILD(AssociationDetails, Associate)
}

/// <summary>
/// Matml_TreeCtrl EvtHandler functions for inserting children.
/// Bound my MaterialFrame using the bind function.
/// </summary>
/// <param name="event"></param>
void AssociationDetails_GUI::OnInsertRelationship(wxCommandEvent& event) 
{ 
	ON_PARENT_INSERT_CONT_CHILD(AssociationDetails, Relationship)
}

/// <summary>
/// Matml_TreeCtrl EvtHandler functions for inserting children.
/// Bound my MaterialFrame using the bind function.
/// </summary>
/// <param name="event"></param>
void AssociationDetails_GUI::OnInsertNotes(wxCommandEvent& event) 
{ 
	ON_PARENT_INSERT_CONT_CHILD(AssociationDetails, Notes)
}

void AssociationDetails_GUI::OnDeleteAssociate(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_CONT_CHILD(AssociationDetails, Associate)
}

void AssociationDetails_GUI::OnDeleteRelationship(wxCommandEvent& event) 
{ 
	ON_PARENT_DELETE_CONT_CHILD(AssociationDetails, Relationship)
}

void AssociationDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {
	ON_PARENT_DELETE_CONT_CHILD(AssociationDetails, Notes)
}

void AssociationDetails_GUI::OnPasteAssociate(wxCommandEvent& event) 
{ 
	ON_PARENT_PASTE_CONT_CHILD(AssociationDetails, Associate)
}

void AssociationDetails_GUI::OnPasteRelationship(wxCommandEvent& event) 
{ 
	ON_PARENT_PASTE_CONT_CHILD(AssociationDetails, Relationship)
}

void AssociationDetails_GUI::OnPasteNotes(wxCommandEvent& event) 
{ 
	ON_PARENT_PASTE_CONT_CHILD(AssociationDetails, Notes)
}



void AssociationDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(ComponentDetails*)) {
			AssociationDetails* element = boost::any_cast<AssociationDetails*>(anyptr);
			ComponentDetails* elementParent = boost::any_cast<ComponentDetails*>(anyptrparent);

			auto& cont = elementParent->AssociationDetails();
			std::pair<AssociationDetails*, AssociationDetails*> data(MatMLFindAndBumpDown(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<AssociationDetails_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

}

void AssociationDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(ComponentDetails*)) {
			AssociationDetails* element = boost::any_cast<AssociationDetails*>(anyptr);
			ComponentDetails* elementParent = boost::any_cast<ComponentDetails*>(anyptrparent);

			auto& cont = elementParent->AssociationDetails();
			std::pair<AssociationDetails*, AssociationDetails*> data(MatMLFindAndBumpUp(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<AssociationDetails_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}

