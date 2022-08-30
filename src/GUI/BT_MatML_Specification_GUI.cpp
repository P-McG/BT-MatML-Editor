#include <wx/config.h>
#include "BT_MatML_Specification_GUI.h"

using namespace bellshire;

Specification_GUI_Base::Specification_GUI_Base()
	:m_GUI(nullptr),
	m_SpecificationTextCtrl(nullptr),
	m_AuthorityChoice(nullptr),
	m_SpecificationAuthorityDetails_Display_GUI(nullptr)
{

}

Specification_GUI_Base::Specification_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), 
	m_SpecificationTextCtrl(nullptr),
	m_AuthorityChoice(nullptr),
	m_SpecificationAuthorityDetails_Display_GUI(nullptr)
{
	m_GUI = Create(parent, m_SpecificationTextCtrl, m_AuthorityChoice, m_SpecificationAuthorityDetails_Display_GUI);
}

Specification_GUI_Base::~Specification_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete	m_SpecificationAuthorityDetails_Display_GUI; // neither a Ctrl or a window
}

/// <summary>
/// Create the GUI for the Specification MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="SpecificationNotebook"></param>
/// <param name="SpecificationPanel"></param>
/// <param name="SpecificationTextCtrl"></param>
/// <param name="AuthorityChoice"></param>
/// <returns>bool</returns>
wxNotebook* Specification_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& SpecificationTextCtrl, 
	wxChoice*& AuthorityChoice, 
	AuthorityDetails_Display_GUI*& SpecificationAuthorityDetails_Display_GUI
)
{
	wxNotebook* SpecificationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SpecificationNotebook->Hide();
	SpecificationNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* SpecificationPanel = new wxScrolledWindow(SpecificationNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SpecificationPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer82 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer23 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer23->AddGrowableCol(1);
	fgSizer23->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer23->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText27 = new wxStaticText(SpecificationPanel, wxID_ANY, wxT("Specification"), wxDefaultPosition, wxDefaultSize, 0);
	staticText27->Wrap(-1);
	fgSizer23->Add(staticText27, 0, wxALL, 5);

	SpecificationTextCtrl = new wxTextCtrl(SpecificationPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer23->Add(SpecificationTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText28 = new wxStaticText(SpecificationPanel, wxID_ANY, wxT("Authority"), wxDefaultPosition, wxDefaultSize, 0);
	staticText28->Wrap(-1);
	fgSizer23->Add(staticText28, 0, wxALL, 5);

	wxArrayString AuthorityChoiceChoices;
	AuthorityChoice = new wxChoice(SpecificationPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, AuthorityChoiceChoices, 0);
	AuthorityChoice->SetSelection(0);
	fgSizer23->Add(AuthorityChoice, 1, wxALL | wxEXPAND, 5);

	bSizer82->Add(fgSizer23, 1, wxEXPAND, 5);

	//Display Notebook
	wxNotebook* notebook6 = new wxNotebook(SpecificationPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	//Display the Details
	SpecificationAuthorityDetails_Display_GUI = new AuthorityDetails_Display_GUI(notebook6);
	notebook6->AddPage(SpecificationAuthorityDetails_Display_GUI->get(), wxT("Authority"), false);

	bSizer82->Add(notebook6, 1, wxEXPAND | wxALL, 5);

	SpecificationPanel->SetSizer(bSizer82);
	SpecificationPanel->Layout();
	bSizer82->Fit(SpecificationPanel);

	MatMLInfo_GUI matMLInfo_GUI(SpecificationNotebook,
		wxT("********** Specification *************************\n\nThis element declares the content model for Specification, which\ncontains a string representing the specification for the bulk material or\ncomponent and has one optional attribute, authority, for identifying an\nauthoritative source of specifications.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SpecificationNotebook->AddPage(SpecificationPanel, wxT("MatML Data."), b_dflt);
	SpecificationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SpecificationNotebook;
}

void Specification_GUI_Base::Update( Specification* element, const ::boost::shared_ptr<MatML_Doc> doc)
{
	wxString str;

	str << _std2wx((*element));//double paranthesis required
	m_SpecificationTextCtrl->ChangeValue(str);

	str.clear();
	//{
	//	Specification::authority_optional& cont(element->authority());
	//	if(cont.present()) str<< _std2wx((*cont));
	//	m_AuthorityTextCtrl->ChangeValue(str);
 // 	}

	{
		const Metadata::AuthorityDetails_sequence& cont(doc->Metadata()->AuthorityDetails());
		Metadata::AuthorityDetails_const_iterator iter(cont.begin());
		if (!cont.empty()) {
			m_AuthorityChoice->Clear();
			m_AuthorityChoice->Append(wxT(""));
			for (; iter != cont.end(); ++iter) {
				wxString str;
				str << _std2wx((iter)->id());
				m_AuthorityChoice->Append(str);
			}
		}
	}

	str.clear();
	{
		const Specification::authority_optional& cont(element->authority());
		if (cont.present()) str << _std2wx((*cont));
		m_AuthorityChoice->SetStringSelection(str);
	}

	m_SpecificationAuthorityDetails_Display_GUI->Update(element);

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Specification_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Specification& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Specification");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//authority

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}

void Specification_GUI_Base::SetConnect()
{
	m_SpecificationTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Specification_GUI_Base::OnSpecificationTextCtrl), NULL, this);
	m_SpecificationTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Specification_GUI_Base::OnSpecificationTextCtrl), NULL, this);
	m_AuthorityChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Specification_GUI_Base::OnSpecificationAuthorityChoice), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Specification_GUI::Specification_GUI() : Specification_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Specification_GUI::Specification_GUI(wxWindow* parent)
	: Specification_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Specification_GUI::~Specification_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Specification_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Specification_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void Specification_GUI::OnSpecificationTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Specification* const Element = boost::any_cast<Specification* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_SpecificationTextCtrl->GetValue());
			Specification NewData((const char*)str.mb_str(wxConvUTF8));
			(*Element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Specification_GUI::OnSpecificationAuthorityChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Specification* const Element = boost::any_cast<Specification* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Specification::authority_optional& cont(Element->authority());
			wxString str(m_AuthorityChoice->GetStringSelection());;
			if (str.IsEmpty()) { 
				cont.reset(); 
				m_SpecificationAuthorityDetails_Display_GUI->Update(Element);
				return; 
			}

			Specification::authority_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);

			m_SpecificationAuthorityDetails_Display_GUI->Update(Element);

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Specification_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type()==typeid(BulkDetails*)) {
			Specification* element = boost::any_cast<Specification*>(anyptr);
			BulkDetails* elementParent = boost::any_cast<BulkDetails*>(anyptrparent);

			auto& cont = elementParent->Specification();
			std::pair<Specification*, Specification*> data(MatMLFindAndBumpDown(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<Specification_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

	try {
		if (anyptrparent.type() == typeid(ComponentDetails*)) {
			Specification* element = boost::any_cast<Specification*>(anyptr);
			ComponentDetails* elementParent = boost::any_cast<ComponentDetails*>(anyptrparent);

			auto& cont(elementParent->Specification());
			std::pair<Specification*, Specification*> data(MatMLFindAndBumpDown(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<Specification_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}

void Specification_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(BulkDetails*)) {
			Specification* element = boost::any_cast<Specification*>(anyptr);
			BulkDetails* elementParent = boost::any_cast<BulkDetails*>(anyptrparent);

			auto& cont = elementParent->Specification();
			std::pair<Specification*, Specification*> data(MatMLFindAndBumpUp(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<Specification_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

	try {
		if (anyptrparent.type() == typeid(ComponentDetails*)) {
			Specification* element = boost::any_cast<Specification*>(anyptr);
			ComponentDetails* elementParent = boost::any_cast<ComponentDetails*>(anyptrparent);

			auto& cont(elementParent->Specification());
			std::pair<Specification*, Specification*> data(MatMLFindAndBumpUp(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<Specification_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}
