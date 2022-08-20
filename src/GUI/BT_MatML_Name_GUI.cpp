#include <wx/config.h>
#include "BT_MatML_Name_GUI.h"

using namespace bellshire;

Name_GUI_Base::Name_GUI_Base() 
	:m_GUI(nullptr),
	m_NameTextCtrl(nullptr),
	m_AuthorityChoice(nullptr),
	m_NameAuthorityDetails_Display_GUI(nullptr)
{

}

Name_GUI_Base::Name_GUI_Base(wxWindow* parent) 
	: m_GUI(nullptr),
	m_NameTextCtrl(nullptr),
	m_AuthorityChoice(nullptr),
	m_NameAuthorityDetails_Display_GUI(nullptr)
{
	m_GUI = Create(parent, m_NameTextCtrl, m_AuthorityChoice, m_NameAuthorityDetails_Display_GUI);
}

Name_GUI_Base::~Name_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_NameAuthorityDetails_Display_GUI; // neither a Ctrl or window
}

/// <summary>
/// Create the GUI for the Name MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="NameNotebook"></param>
/// <param name="NamePanel"></param>
/// <param name="NameTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Name_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& NameTextCtrl, wxChoice*& AuthorityChoice, AuthorityDetails_Display_GUI*& NameAuthorityDetails_Display_GUI)
{

	wxNotebook* NameNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	NameNotebook->Hide();
	NameNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* NamePanel = new wxScrolledWindow(NameNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	NamePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer67 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer15 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer15->AddGrowableCol(1);
	fgSizer15->AddGrowableRow(0);
	fgSizer15->SetFlexibleDirection(wxBOTH);
	fgSizer15->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText11 = new wxStaticText(NamePanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText11->Wrap(-1);
	fgSizer15->Add(staticText11, 0, wxALL, 5);

	NameTextCtrl = new wxTextCtrl(NamePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP | wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	fgSizer15->Add(NameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText28 = new wxStaticText(NamePanel, wxID_ANY, wxT("Authority"), wxDefaultPosition, wxDefaultSize, 0);
	staticText28->Wrap(-1);
	fgSizer15->Add(staticText28, 0, wxALL, 5);

	wxArrayString AuthorityChoiceChoices;
	AuthorityChoice = new wxChoice(NamePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, AuthorityChoiceChoices, 0);
	AuthorityChoice->SetSelection(0);
	fgSizer15->Add(AuthorityChoice, 1, wxALL | wxEXPAND, 5);

	bSizer67->Add(fgSizer15, 1, wxEXPAND, 5);

	//Display Notebook
	wxNotebook* notebook6 = new wxNotebook(NamePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	//Display the Details
	NameAuthorityDetails_Display_GUI = new AuthorityDetails_Display_GUI(notebook6);
	notebook6->AddPage(NameAuthorityDetails_Display_GUI->get(), wxT("Authority"), false);

	bSizer67->Add(notebook6, 1, wxEXPAND | wxALL, 5);

	NamePanel->SetSizer(bSizer67);
	NamePanel->Layout();
	bSizer67->Fit(NamePanel);

	MatMLInfo_GUI matMLInfo_GUI(NameNotebook,
		wxT("*********** Name *************************\n\nThis element declares the content model for Name, which contains a\nstring representing a name and has one optional attribute, authority,\nfor identifying an authoritative source of names in the context in which\nthe Name element is used.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	NameNotebook->AddPage(NamePanel, wxT("MatML Data."), b_dflt);
	NameNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return NameNotebook;
}

void Name_GUI_Base::Update(Name* element, ::boost::shared_ptr<MatML_Doc> doc)
{
	wxString str;

	str << _std2wx((*element));//double paranthesis required
	m_NameTextCtrl->ChangeValue(str);

	Metadata::AuthorityDetails_sequence& cont(doc->Metadata()->AuthorityDetails());
	Metadata::AuthorityDetails_iterator iter(cont.begin());
	if (!cont.empty()) {
		m_AuthorityChoice->Clear();
		m_AuthorityChoice->Append(wxT(""));
		for (; iter != cont.end(); ++iter) {
			m_AuthorityChoice->Append(_std2wx(Label(iter->Name(), iter->id())));
		}
	}

	if (element->authority().present()) {
		const xml_schema::idref& idref(element->authority().get());
		const AuthorityDetails* auth = dynamic_cast<const AuthorityDetails*>(&*idref);
		if (auth) m_AuthorityChoice->SetStringSelection(_std2wx(Label(auth->Name(), auth->id())));
	}
	
	m_NameAuthorityDetails_Display_GUI->Update(element);
	
	Show(true);
}

::std::string Name_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}
::std::string Name_GUI_Base::LabelToId(::std::string label)
{
	::std::list<::std::string> result;
	return boost::split(result, label, boost::is_any_of(":")).back();
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Name_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Name& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Name");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//SetupAuthority()

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}

void Name_GUI_Base::SetConnect()
{
	m_NameTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Name_GUI_Base::OnNameTextCtrl), NULL, this);
	m_NameTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Name_GUI_Base::OnNameTextCtrl), NULL, this);
	m_AuthorityChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Name_GUI_Base::OnNameAuthorityChoice), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Name_GUI::Name_GUI() : Name_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Name_GUI::Name_GUI(wxWindow* parent)
	: Name_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Name_GUI::~Name_GUI() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Name_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Name_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}



void Name_GUI::OnNameTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	const boost::any& anyptr(item->GetAnyMatMLDataPointer());

	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));
	const boost::any& anyparentptr(itemParent->GetAnyMatMLDataPointer());


	try {
		if (anyptr.type() == typeid(Name*)) {
			Name*  Element = boost::any_cast<Name* >(anyptr);
			if (Element != 0) {
				wxString str(m_NameTextCtrl->GetValue());
				Name NewData((const char*)str.mb_str(wxConvUTF8));
				(*Element) = NewData;

				if(anyparentptr.type() == typeid(BulkDetails*)) {
					wxString label;
					label << str;
					m_MatMLTreeCtrl->SetItemText(m_MatMLTreeCtrl->GetItemParent(itemParentId), label);
				}
		
				if (anyparentptr.type() == typeid(ParentSubClass*)) {
					wxString label;
					label << wxT("ParentSubClass-");
					label << str;
					m_MatMLTreeCtrl->SetItemText(itemParentId, label);
				}

				if (anyparentptr.type() == typeid(Class*)) {
					wxString label;
					label << wxT("Class-");
					label << str;
					m_MatMLTreeCtrl->SetItemText(itemParentId, label);
				}
			
				if (anyparentptr.type() == typeid(ComponentDetails*)) {
					wxString label;
					label << wxT("ComponentDetails-");
					label << str;
					m_MatMLTreeCtrl->SetItemText(itemParentId, label);
				}

				if (anyparentptr.type() == typeid(ProcessingDetails*)) {
					wxString label;
					label << wxT("ProcessingDetails-");
					label << str;
					m_MatMLTreeCtrl->SetItemText(itemParentId, label);
				}

				return;
			}
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Name_GUI::OnNameAuthorityChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Name* const Element = boost::any_cast<Name* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Name::authority_optional& cont(Element->authority());

			wxString str(m_AuthorityChoice->GetStringSelection());

			if (str.IsEmpty()) { 
				cont.reset(); 
				m_NameAuthorityDetails_Display_GUI->Update(Element);
				return; 
			}

			Name::authority_type NewData(LabelToId(_wx2std(str)));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
		
			m_NameAuthorityDetails_Display_GUI->Update(Element);

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}
