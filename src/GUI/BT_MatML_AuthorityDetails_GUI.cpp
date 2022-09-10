#include "BT_MatML_AuthorityDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

AuthorityDetails_GUI_Base::AuthorityDetails_GUI_Base()
	:m_GUI(nullptr), m_AuthorityDetails_ID_GUI(nullptr)
{

}

AuthorityDetails_GUI_Base::AuthorityDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_AuthorityDetails_ID_GUI(nullptr)
{
	m_GUI = Create(parent, m_AuthorityDetails_ID_GUI);
}

AuthorityDetails_GUI_Base::~AuthorityDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_AuthorityDetails_ID_GUI;//this is neither a window nor a ctrl.
}


/// <summary>
/// Create the GUI for the AuthorityDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="AuthorityDetailsNotebook"></param>
/// <param name="AuthorityDetailsPanel"></param>
/// <param name="AuthorityDetailsGenerateUuidButton"></param>
/// <param name="AuthorityDetailsIDTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* AuthorityDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& AuthorityDetails_ID_GUI)
{
	wxNotebook* AuthorityDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	AuthorityDetailsNotebook->Hide();
	AuthorityDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* AuthorityDetailsPanel = new wxScrolledWindow(AuthorityDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	AuthorityDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer29 = new wxBoxSizer(wxVERTICAL);

	AuthorityDetails_ID_GUI = new ID_GUI(AuthorityDetailsPanel);
	//wxPanel* IDCtrlPanel = CreateIDCtrl(AuthorityDetailsPanel, AuthorityDetailsGenerateUuidButton, AuthorityDetailsIDTextCtrl);
	bSizer29->Add(AuthorityDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	AuthorityDetailsPanel->SetSizer(bSizer29);
	AuthorityDetailsPanel->Layout();
	bSizer29->Fit(AuthorityDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(AuthorityDetailsNotebook,
		wxT("********* AuthorityDetails *************************\n\nThis element declares the content model for AuthorityDetails, which\ncontains a description of an authority referenced by other elements,\n such as the Specification and Name elements. An authority is typically an\norganisation that is the authoritative source of information about the \nelement that is referencing it.\n\t\t\t\nAuthorityDetails has one required attribute, id, which may be\narbitrarily assigned but must be unique among id attributes assigned\nelsewhere in a MatML document. \n\t\t\t\nAuthorityDetails additionally has two elements, Name and Notes.\n\nName contains the name of the Authority. Name must occur once and \nonly once within the AuthorityDetails element.\n\nNotes contains any additional information concerning the parameter and\nmay occur once or not at all within the AuthorityDetails element.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	AuthorityDetailsNotebook->AddPage(AuthorityDetailsPanel, wxT("MatML Data."), b_dflt);
	AuthorityDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return AuthorityDetailsNotebook;
}

void AuthorityDetails_GUI_Base::Update( AuthorityDetails* element)
{
	m_AuthorityDetails_ID_GUI->Update(element);

	Show(true);
}


::std::string AuthorityDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}


/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId AuthorityDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId &ParentId, 
	AuthorityDetails &Element,
	const wxTreeItemId &PreviousId
)
{
	::std::string label;
	label.assign("AuthorityDetails-");
	label.append(Label(Element.Name(), Element.id()));

	  wxTreeItemId CurrentId;

	  if(PreviousId.IsOk())
		  CurrentId=MatMLTreeCtrl->InsertItem(ParentId,PreviousId,_std2wx(label),-1,-1,new MatMLTreeItemData(&Element));
	  else
		  CurrentId=MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label),-1,-1,new MatMLTreeItemData(&Element));


	  //MatML Attributes
	  //Id

	  //Setup Elements Name
	  if(Element.Name()!="")
		  Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	  //Setup Elements Notes
	  {
		   AuthorityDetails::Notes_optional& cont(Element.Notes());
		   if(cont.present())
			   Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	  }

	  return CurrentId;
}
/// <summary>
/// Set up the connect between the MatML_GUI and the functions
/// </summary>
void AuthorityDetails_GUI_Base::SetConnect(){}


AuthorityDetails_GUI::AuthorityDetails_GUI()
	:AuthorityDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{}

AuthorityDetails_GUI::AuthorityDetails_GUI(wxWindow* parent)
	: AuthorityDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

AuthorityDetails_GUI::~AuthorityDetails_GUI() 
{
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void AuthorityDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	m_AuthorityDetails_ID_GUI->SetEvtHandlerVar(m_MatMLTreeCtrl, MatMLDoc);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void AuthorityDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void AuthorityDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void AuthorityDetails_GUI::OnInsertName(wxCommandEvent& event) { 
	ON_PARENT_INSERT_CHILD(AuthorityDetails, Name) 
}

void AuthorityDetails_GUI::OnInsertNotes(wxCommandEvent& event) {
	ON_PARENT_INSERT_CONT_CHILD(AuthorityDetails, Notes) 
}

void AuthorityDetails_GUI::OnDeleteName(wxCommandEvent& event) {
	ON_PARENT_DELETE_CHILD(AuthorityDetails, Name)
}

void AuthorityDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {
	ON_PARENT_DELETE_CONT_CHILD(AuthorityDetails, Notes)
}

void AuthorityDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(AuthorityDetails, Name) }
void AuthorityDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(AuthorityDetails, Notes) }


void AuthorityDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< AuthorityDetails, 
		Metadata, 
		Metadata::AuthorityDetails_sequence, 
		AuthorityDetails_GUI, 
		&Metadata::AuthorityDetails 
	>
	(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void AuthorityDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingId< AuthorityDetails,
		Metadata,
		Metadata::AuthorityDetails_sequence,
		AuthorityDetails_GUI,
		&Metadata::AuthorityDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}


//void AuthorityDetails_GUI::OnBumpUp(wxCommandEvent& event)
//{
//
//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
//
//	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);
//
//	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
//	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));
//
//	boost::any anyptr(item->GetAnyMatMLDataPointer());
//	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());
//
//	try {
//		if (anyptrparent.type() == typeid(Metadata*)) {
//			AuthorityDetails* element = boost::any_cast<AuthorityDetails*>(anyptr);
//			Metadata* elementParent = boost::any_cast<Metadata*>(anyptrparent);
//
//			typedef Metadata::AuthorityDetails_sequence& (Metadata::* Cont_Func)();
//
//			Cont_Func cont_func = &Metadata::AuthorityDetails;
//
//			std::pair<AuthorityDetails*, AuthorityDetails*> data(MatMLFindAndBumpUpHavingId(element, (elementParent->*cont_func)()));
//			if (data.second)
//				MatMLTreeCtrlBumpUp<AuthorityDetails_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);
//
//			return;
//		}
//	}
//	catch (const boost::bad_any_cast&) {};//do nothing
//
//}
