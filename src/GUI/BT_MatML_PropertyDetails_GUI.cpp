#include <wx/config.h>
#include "BT_MatML_PropertyDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

PropertyDetails_GUI_Base::PropertyDetails_GUI_Base()
	:m_GUI(nullptr),
	m_PropertyDetails_ID_GUI(nullptr),
	m_PropertyDetailsTypeTextCtrl(nullptr)
{

}

PropertyDetails_GUI_Base::PropertyDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_PropertyDetails_ID_GUI(nullptr),
	m_PropertyDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_PropertyDetails_ID_GUI, m_PropertyDetailsTypeTextCtrl);
}

PropertyDetails_GUI_Base::~PropertyDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_PropertyDetails_ID_GUI;//this is neither a window nor a ctrl.
}

/// <summary>
/// Create the GUI for the PropertyDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="PropertyDetailsNotebook"></param>
/// <param name="PropertyDetailsPanel"></param>
/// <param name="PropertyDetailsGenerateUuidButton"></param>
/// <param name="PropertyDetailsIDTextCtrl"></param>
/// <param name="PropertyDetailsTypeTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* PropertyDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& PropertyDetails_ID_GUI, wxTextCtrl*& PropertyDetailsTypeTextCtrl)
{
	wxNotebook* PropertyDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	PropertyDetailsNotebook->Hide();
	PropertyDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* PropertyDetailsPanel = new wxScrolledWindow(PropertyDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	PropertyDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer76 = new wxBoxSizer(wxVERTICAL);

	PropertyDetails_ID_GUI = new ID_GUI(PropertyDetailsPanel);
	bSizer76->Add(PropertyDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer32 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer32->AddGrowableCol(1);
	fgSizer32->SetFlexibleDirection(wxBOTH);
	fgSizer32->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText48 = new wxStaticText(PropertyDetailsPanel, wxID_ANY, wxT("Property Details Type"), wxDefaultPosition, wxDefaultSize, 0);
	staticText48->Wrap(-1);
	fgSizer32->Add(staticText48, 0, wxALL, 5);

	PropertyDetailsTypeTextCtrl = new wxTextCtrl(PropertyDetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer32->Add(PropertyDetailsTypeTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer76->Add(fgSizer32, 0, wxEXPAND, 5);

	PropertyDetailsPanel->SetSizer(bSizer76);
	PropertyDetailsPanel->Layout();
	bSizer76->Fit(PropertyDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(PropertyDetailsNotebook,
		wxT("********** PropertyDetails *************************\n\nThis element declares the content model for PropertyDetails, which\ncontains a description of a property referenced by the PropertyData\nelement. PropertyDetails has one required attribute, id, which may be\narbitrarily assigned but must be unique among id attributes assigned \nelsewhere in a MatML document. PropertyDetails also has one optional\nattribute, type, for specifying the type of the property (examples include\n\"thermal,\" \"mechanical,\" \"electrical,\" etc.) PropertyDetails is composed of\nthe following elements.\n\nName contains the name of the property and has one optional attribute,\nauthority, for identifying an authoritative source of property names.\nName must occur once and only once within the PropertyDetails\nelement.\n\nUnits and Unitless are mutually exclusive elements for describing the\nproperty's units. Units or Unitless must occur once and only once within\nthe PropertyDetails element. For additional information, see the\ndocumentation for the Units and Unitless elements.\n\nNotes contains any additional information concerning the property and\nmay occur once or not at all within the PropertyDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	PropertyDetailsNotebook->AddPage(PropertyDetailsPanel, wxT("MatML Data."), b_dflt);
	PropertyDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return PropertyDetailsNotebook;
}

void PropertyDetails_GUI_Base::Update( PropertyDetails* element)
{
	wxString str;

	m_PropertyDetails_ID_GUI->Update(element);

	str.clear();
	{
		const PropertyDetails::type_optional& cont(element->type());
		if (cont.present()) str << _std2wx((*cont));
		m_PropertyDetailsTypeTextCtrl->ChangeValue(str);
	}

	Show(true);
}

::std::string PropertyDetails_GUI_Base::Label(::std::string name, ::std::string id)
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
wxTreeItemId PropertyDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	PropertyDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("PropertyDetails-");
	label.append(Label(Element.Name(), Element.id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, label, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, label, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id
	//type

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Units
	{
		PropertyDetails::Units_optional& cont(Element.Units());
		if (cont.present())
			Units_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Unitless
	{
		PropertyDetails::Unitless_optional& cont(Element.Unitless());
		if (cont.present())
			Unitless_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		PropertyDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}

void PropertyDetails_GUI_Base::SetConnect()
{
	m_PropertyDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PropertyDetails_GUI_Base::OnPropertyDetailsTypeTextCtrl), NULL, this);
	m_PropertyDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PropertyDetails_GUI_Base::OnPropertyDetailsTypeTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
PropertyDetails_GUI::PropertyDetails_GUI() : PropertyDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
PropertyDetails_GUI::PropertyDetails_GUI(wxWindow* parent)
	: PropertyDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
PropertyDetails_GUI::~PropertyDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PropertyDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	m_PropertyDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl, MatMLDoc);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PropertyDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void PropertyDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void PropertyDetails_GUI::OnPropertyDetailsTypeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyDetails*  Element = boost::any_cast<PropertyDetails* >(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			PropertyDetails::type_optional& cont(Element->type());
			wxString str(m_PropertyDetailsTypeTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			PropertyDetails::type_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(PropertyDetails, Name) }
void PropertyDetails_GUI::OnInsertUnits(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PropertyDetails, Units) }
void PropertyDetails_GUI::OnInsertUnitless(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PropertyDetails, Unitless) }
void PropertyDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PropertyDetails, Notes) }

void PropertyDetails_GUI::OnDeleteName(wxCommandEvent& event) { ON_PARENT_DELETE_CHILD(PropertyDetails, Name) }
void PropertyDetails_GUI::OnDeleteUnitless(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PropertyDetails, Unitless)}
void PropertyDetails_GUI::OnDeleteUnits(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PropertyDetails, Units)}
void PropertyDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PropertyDetails, Notes)}

void PropertyDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(PropertyDetails, Name) }
void PropertyDetails_GUI::OnPasteUnits(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PropertyDetails, Units) }
void PropertyDetails_GUI::OnPasteUnitless(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PropertyDetails, Unitless) }
void PropertyDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PropertyDetails, Notes) }


void PropertyDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< PropertyDetails,
		Metadata,
		Metadata::PropertyDetails_sequence,
		PropertyDetails_GUI,
		&Metadata::PropertyDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void PropertyDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingId< PropertyDetails,
		Metadata,
		Metadata::PropertyDetails_sequence,
		PropertyDetails_GUI,
		&Metadata::PropertyDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

