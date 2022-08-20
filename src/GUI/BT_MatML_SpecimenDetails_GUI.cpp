#include <wx/config.h>
#include "BT_MatML_SpecimenDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

SpecimenDetails_GUI_Base::SpecimenDetails_GUI_Base()
	:m_GUI(nullptr), m_SpecimenDetails_ID_GUI(nullptr), m_SpecimenDetailsTypeTextCtrl(nullptr)
{

}

SpecimenDetails_GUI_Base::SpecimenDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_SpecimenDetails_ID_GUI(nullptr), m_SpecimenDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_SpecimenDetails_ID_GUI, m_SpecimenDetailsTypeTextCtrl);
}

SpecimenDetails_GUI_Base::~SpecimenDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_SpecimenDetails_ID_GUI;//this is neither a window nor a ctrl.
}


/// <summary>
/// Create the GUI for the SpecimenDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="SpecimenDetailsTypeTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* SpecimenDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& SpecimenDetails_ID_GUI, wxTextCtrl*& SpecimenDetailsTypeTextCtrl)
{
	wxNotebook* SpecimenDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SpecimenDetailsNotebook->Hide();
	SpecimenDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* SpecimenDetailsPanel = new wxScrolledWindow(SpecimenDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SpecimenDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer97 = new wxBoxSizer(wxVERTICAL);

	SpecimenDetails_ID_GUI = new ID_GUI(SpecimenDetailsPanel);
	bSizer97->Add(SpecimenDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer34 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer34->AddGrowableCol(1);
	fgSizer34->SetFlexibleDirection(wxBOTH);
	fgSizer34->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText52 = new wxStaticText(SpecimenDetailsPanel, wxID_ANY, wxT("Specimen Details Type"), wxDefaultPosition, wxDefaultSize, 0);
	staticText52->Wrap(-1);
	fgSizer34->Add(staticText52, 0, wxALL, 5);

	SpecimenDetailsTypeTextCtrl = new wxTextCtrl(SpecimenDetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer34->Add(SpecimenDetailsTypeTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer97->Add(fgSizer34, 1, wxEXPAND, 5);

	SpecimenDetailsPanel->SetSizer(bSizer97);
	SpecimenDetailsPanel->Layout();
	bSizer97->Fit(SpecimenDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(SpecimenDetailsNotebook,
		wxT("********** SpecimenDetails *************************\n\nThis element declares the content model for SpecimenDetails, which\ncontains a description of a specimen referenced by the PropertyData\nelement. SpecimenDetails has one required attribute, id, which may be\narbitrarily assigned but must be unique among id attributes assigned\nelsewhere in a MatML document. SpecimenDetails also has one optional\nattribute, type, for specifying the type of the specimen (examples include\n \"cylindrical,\" \"rectangular,\" \"full cross-section,\" \"pressed,\" etc.)\nSpecimenDetails is composed of the following elements.\n\nSpecimenDetails also has 3 optional elements, Name, Geometry, and Notes.\n\t\t\t\nName contains the name of the specimen and has one optional\nattribute, authority, for identifying an authoritative source of specimen\nnames. Name may occur once or not at all within the SpecimenDetails\nelement.\n\nGeometry describes the dimensions of the Component. For \nadditional information, see the documentation for the Geometry type. \nGeometry may occur once or not at all within the SpecimenDetails\nelement.\n\nNotes contains any additional information concerning the specimen and\nmay occur once or not at all within the SpecimenDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SpecimenDetailsNotebook->AddPage(SpecimenDetailsPanel, wxT("MatML Data."), b_dflt);
	SpecimenDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SpecimenDetailsNotebook;
}

void SpecimenDetails_GUI_Base::Update( SpecimenDetails* element)
{
	wxString str;

	m_SpecimenDetails_ID_GUI->Update(element);

	const SpecimenDetails::type_optional& cont(element->type());
	if (cont.present()) str << _std2wx((*cont));
	m_SpecimenDetailsTypeTextCtrl->ChangeValue(str);


	Show(true);
}


::std::string SpecimenDetails_GUI_Base::Label(::std::string name, ::std::string id)
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
wxTreeItemId SpecimenDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	SpecimenDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	::std::string name;
	label.assign("SpecimenDetails-");
	if (Element.Name().present()) name.assign(Element.Name().get());
	label.append(Label(name, Element.id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id
	//type

	//Setup Elements Name
	{
		 SpecimenDetails::Name_optional& cont(Element.Name());
		if (cont.present())
			Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		 SpecimenDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Geometry
	{
		 SpecimenDetails::Geometry_optional& cont(Element.Geometry());
		if (cont.present())
			Geometry_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}

void SpecimenDetails_GUI_Base::SetConnect()
{
	m_SpecimenDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SpecimenDetails_GUI_Base::OnSpecimenDetailsTypeTextCtrl), NULL, this);
	m_SpecimenDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SpecimenDetails_GUI_Base::OnSpecimenDetailsTypeTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
SpecimenDetails_GUI::SpecimenDetails_GUI() : SpecimenDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
SpecimenDetails_GUI::SpecimenDetails_GUI(wxWindow* parent)
	: SpecimenDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
SpecimenDetails_GUI::~SpecimenDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void SpecimenDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_SpecimenDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void SpecimenDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void SpecimenDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void SpecimenDetails_GUI::OnSpecimenDetailsTypeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		SpecimenDetails* const Element = boost::any_cast<SpecimenDetails* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			SpecimenDetails::type_optional& cont(Element->type());
			wxString str(m_SpecimenDetailsTypeTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			SpecimenDetails::type_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void SpecimenDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(SpecimenDetails, Name) }
void SpecimenDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(SpecimenDetails, Notes) }
void SpecimenDetails_GUI::OnInsertGeometry(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(SpecimenDetails, Geometry) }

void SpecimenDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(SpecimenDetails, Name)}
void SpecimenDetails_GUI::OnDeleteGeometry(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(SpecimenDetails, Geometry)}
void SpecimenDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(SpecimenDetails, Notes)}

void SpecimenDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(SpecimenDetails, Name) }
void SpecimenDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(SpecimenDetails, Notes) }
void SpecimenDetails_GUI::OnPasteGeometry(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(SpecimenDetails, Geometry) }
