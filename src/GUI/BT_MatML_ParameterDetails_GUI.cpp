#include <wx/config.h>
#include "BT_MatML_ParameterDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

ParameterDetails_GUI_Base::ParameterDetails_GUI_Base()
	:m_GUI(nullptr),
	m_ParameterDetails_ID_GUI(nullptr)
{

}

ParameterDetails_GUI_Base::ParameterDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ParameterDetails_ID_GUI(nullptr)
{
	m_GUI = Create(parent, m_ParameterDetails_ID_GUI);
}

ParameterDetails_GUI_Base::~ParameterDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_ParameterDetails_ID_GUI;//this is neither a window nor a ctrl.
}


/// <summary>
/// Create the GUI for the ParameterDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ParameterDetailsIDTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* ParameterDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& ParameterDetails_ID_GUI)
{

	wxNotebook* ParameterDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ParameterDetailsNotebook->Hide();
	ParameterDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ParameterDetailsPanel = new wxScrolledWindow(ParameterDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ParameterDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	ParameterDetails_ID_GUI = new ID_GUI(ParameterDetailsPanel);
	bSizer1->Add(ParameterDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	ParameterDetailsPanel->SetSizer(bSizer1);
	ParameterDetailsPanel->Layout();
	bSizer1->Fit(ParameterDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(ParameterDetailsNotebook,
		wxT("********** ParameterDetails *************************\n\nThis element declares the content model for ParameterDetails, which\n contains a description of a parameter referenced by the ParameterValue\n element. ParameterDetails has one required attribute, id, which may be\n arbitrarily assigned but must be unique among id attributes assigned\n elsewhere in a MatML document. ParameterDetails is composed of\n the following elements.\n\nName contains the name of the parameter and has one optional attribute,\n authority, for identifying an authoritative source of parameter names. Name must occur once\n and only once within the ParameterDetails\nelement.\n\nUnits and Unitless are mutually exclusive elements for describing the\nparameter's units. Units or Unitless must occur once and only once\nwithin the ParameterDetails element. For additional information, see the\ndocumentation for the Units and Unitless elements.\n\nNotes contains any additional information concerning the parameter and\nmay occur once or not at all within the ParameterDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ParameterDetailsNotebook->AddPage(ParameterDetailsPanel, wxT("MatML Data."), b_dflt);
	ParameterDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ParameterDetailsNotebook;
}

void ParameterDetails_GUI_Base::Update( ParameterDetails* element)
{
	m_ParameterDetails_ID_GUI->Update(element);

	Show(true);
}

::std::string ParameterDetails_GUI_Base::Label(::std::string name, ::std::string id)
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
wxTreeItemId ParameterDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	ParameterDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("ParameterDetails-");
	label.append(Label(Element.Name(), Element.id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Units
	{
		ParameterDetails::Units_optional& cont(Element.Units());
		if (cont.present())
			Units_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Unitless
	{
		ParameterDetails::Unitless_optional& cont(Element.Unitless());
		if (cont.present())
			Unitless_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		ParameterDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}


void ParameterDetails_GUI_Base::SetConnect()
{}


/// <summary>
/// Constructor for the derived class
/// </summary>
ParameterDetails_GUI::ParameterDetails_GUI() : ParameterDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ParameterDetails_GUI::ParameterDetails_GUI(wxWindow* parent)
	: ParameterDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ParameterDetails_GUI::~ParameterDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParameterDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_ParameterDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParameterDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ParameterDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ParameterDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(ParameterDetails, Name) }
void ParameterDetails_GUI::OnInsertUnits(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ParameterDetails, Units) }
void ParameterDetails_GUI::OnInsertUnitless(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ParameterDetails, Unitless) }
void ParameterDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ParameterDetails, Notes) }

void ParameterDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(ParameterDetails, Name)}
void ParameterDetails_GUI::OnDeleteUnitless(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ParameterDetails, Unitless)}
void ParameterDetails_GUI::OnDeleteUnits(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ParameterDetails, Units)}
void ParameterDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ParameterDetails, Notes)}

void ParameterDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(ParameterDetails, Name) }
void ParameterDetails_GUI::OnPasteUnits(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ParameterDetails, Units) }
void ParameterDetails_GUI::OnPasteUnitless(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ParameterDetails, Unitless) }
void ParameterDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ParameterDetails, Notes) }


void ParameterDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Metadata*)) {
			ParameterDetails* element = boost::any_cast<ParameterDetails*>(anyptr);
			Metadata* elementParent = boost::any_cast<Metadata*>(anyptrparent);

			auto& cont = elementParent->ParameterDetails();
			std::pair<ParameterDetails*, ParameterDetails*> data(MatMLFindAndBumpDownHavingId(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<ParameterDetails_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing


}

void ParameterDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Metadata*)) {
			ParameterDetails* element = boost::any_cast<ParameterDetails*>(anyptr);
			Metadata* elementParent = boost::any_cast<Metadata*>(anyptrparent);

			auto& cont = elementParent->ParameterDetails();
			std::pair<ParameterDetails*, ParameterDetails*> data(MatMLFindAndBumpUpHavingId(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<ParameterDetails_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

}

