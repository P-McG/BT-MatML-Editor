#include <wx/config.h>

#include "BT_MatML_ComponentDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

ComponentDetails_GUI_Base::ComponentDetails_GUI_Base()
	:m_GUI(nullptr),
	m_ComponentDetails_ID_GUI(nullptr)
{

}

ComponentDetails_GUI_Base::ComponentDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ComponentDetails_ID_GUI(nullptr)
{
	m_GUI = Create(parent, m_ComponentDetails_ID_GUI);
}

ComponentDetails_GUI_Base::~ComponentDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_ComponentDetails_ID_GUI;//this is neither a window nor a ctrl.	
}


/// <summary>
/// Create the GUI for the ComponentDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ComponentDetails_ID_GUI"></param>
/// <returns>bool</returns>
wxNotebook* ComponentDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& ComponentDetails_ID_GUI)
{
	wxNotebook* ComponentDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ComponentDetailsNotebook->Hide();
	ComponentDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ComponentDetailsPanel = new wxScrolledWindow(ComponentDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ComponentDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	ComponentDetails_ID_GUI = new ID_GUI(ComponentDetailsPanel);
	bSizer1->Add(ComponentDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	ComponentDetailsPanel->SetSizer(bSizer1);
	ComponentDetailsPanel->Layout();
	bSizer1->Fit(ComponentDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(ComponentDetailsNotebook,
		wxT("************ ComponentDetails *************************\n\nThis element declares the content model for ComponentDetails, which\ncontains a description of a component within the bulk material and has\none optional attribute, id, which may be used as an identification\nspecifier for the component and is especially useful for complex\nsystems such as composite laminates.\n \nComponentDetails is composed of the following elements.\n\nName contains the component's name and has one optional attribute,\nauthority, for identifying an authoritative source of component names.\nName must occur once and only once within the ComponentDetails\ntype.\n\nClass contains the component's class and may occur zero or more\ntimes within the ComponentDetails element. For additional information, \nsee the documentation for the Class type.\n\nSubclass contains the component's subclass(es) and may occur zero\nor more times within the ComponentDetails element. For additional\ninformation, see the documentation for the SubClass type.\n\nSpecification contains the component's specification(s) and has one\noptional attribute, authority, for identifying an authoritative\nsource of component specifications. Specification may occur zero or\nmore times within the ComponentDetails type.\n\nSource contains the name of the source of the component and may\noccur once or not at all within the ComponentDetails type. For \nadditional information, see the documentation for the SourceDetails \nelement.\n\nForm contains the form of the component and may occur once or not\nat all within the ComponentDetails type. It has an optional element \nGeometry, for describing the dimensions of the Component. For \nadditional information, see the documentation for the Form type.\n\nProcessingDetails contains a description of a processing step for\nthe component and may occur zero or more times within the\nComponentDetails type. For additional information, see the\ndocumentation for the ProcessingDetails element.\n\nCharacterization contains the characterization of the component,\nincluding the formula, chemical composition, phase composition, and\ndimensional details. Characterization may occur once or not at all\nwithin the ComponentDetails type. For additional information, see\nthe documentation for the Characterization element.\n\nPropertyData contains the property data for the component and may\noccur zero or more times within the ComponentDetails type. For\nadditional information, see the documentation for the PropertyData\nelement.\n\nAssociationDetails contains a description of a relationship of the\ncomponent to another component and may occur zero or more times\nwithin the ComponentDetails type. For additional information, see\nthe documentation for the AssociationDetails element.\n\nNotes contains any additional information concerning the component\nand may occur once or not at all within the ComponentDetails type.\n\nComponentDetails contains a description of a component within the\ncomponent and is used to support encoding of information for\ncomplex materials systems such as composites. ComponentDetails\nmay occur zero or more times within a ComponentDetails element.\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ComponentDetailsNotebook->AddPage(ComponentDetailsPanel, wxT("MatML Data."), b_dflt);
	ComponentDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ComponentDetailsNotebook;
}


void ComponentDetails_GUI_Base::Update( ComponentDetails* element)
{

	m_ComponentDetails_ID_GUI->Update(element);

	Show(true);

}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId ComponentDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	ComponentDetails& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("ComponentDetails");
	str << wxT("-") << _std2wx(Element.Name());

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	wxColour clr; clr.Set(176, 196, 222);//light steel blue
	MatMLTreeCtrl->SetItemBackgroundColour(CurrentId, clr);

	//Setup MatML Attribute
	//SetupId();

	//Setup Element Name
	Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Element Class
	{
		
		ComponentDetails::Class_sequence& cont(Element.Class());
		ComponentDetails::Class_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Class_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Subclass
	{
		ComponentDetails::Subclass_sequence& cont(Element.Subclass());
		ComponentDetails::Subclass_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Subclass1_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Specification
	{
		 ComponentDetails::Specification_sequence& cont(Element.Specification());
		ComponentDetails::Specification_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Specification_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Source
	{
		 ComponentDetails::Source_optional& cont(Element.Source());
		if (cont.present())
			Source_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element Form
	{
		 ComponentDetails::Form_optional& cont(Element.Form());
		if (cont.present())
			Form_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element ProcessingDetails
	{
		 ComponentDetails::ProcessingDetails_sequence& cont(Element.ProcessingDetails());
		ComponentDetails::ProcessingDetails_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ProcessingDetails_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Characterization
	{
		 ComponentDetails::Characterization_optional& cont(Element.Characterization());
		if (cont.present())
			Characterization_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element PropertyData
	{
		 ComponentDetails::PropertyData_sequence& cont(Element.PropertyData());
		ComponentDetails::PropertyData_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				PropertyData_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element AssociationDetails
	{
		 ComponentDetails::AssociationDetails_sequence& cont(Element.AssociationDetails());
		ComponentDetails::AssociationDetails_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				AssociationDetails_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element ComponentDetails
	{
		 ComponentDetails::ComponentDetails1_sequence& cont(Element.ComponentDetails1());
		ComponentDetails::ComponentDetails1_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ComponentDetails_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	return CurrentId;
}


void ComponentDetails_GUI_Base::SetConnect()
{}


/// <summary>
/// Constructor for the derived class
/// </summary>
ComponentDetails_GUI::ComponentDetails_GUI() : ComponentDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ComponentDetails_GUI::ComponentDetails_GUI(wxWindow* parent)
	: ComponentDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ComponentDetails_GUI::~ComponentDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ComponentDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLdoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	m_ComponentDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl, MatMLdoc);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ComponentDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ComponentDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ComponentDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(ComponentDetails, Name) }
void ComponentDetails_GUI::OnInsertClass(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, Class) }
void ComponentDetails_GUI::OnInsertSubclass1(wxCommandEvent& event) 
{ 
	//ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, Subclass1 ) //This doesn't work because function name differs from child class name.
	//#define ON_PARENT_INSERT_ITER_CONT_CHILD(parent,child) 
	ComponentDetails* element = MatML_Base_GUI::GetSelMatML<ComponentDetails>(m_MatMLTreeCtrl);
	if (element) {
   		MatML_Base_GUI::InsertSeqContChild<Subclass1>(element->Subclass());//Note: function name differs from child class name
		MatML_Base_GUI::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
	}
}
void ComponentDetails_GUI::OnInsertSpecification(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, Specification) }
void ComponentDetails_GUI::OnInsertSource(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ComponentDetails, Source) }
void ComponentDetails_GUI::OnInsertForm(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ComponentDetails, Form) }
void ComponentDetails_GUI::OnInsertProcessingDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, ProcessingDetails) }
void ComponentDetails_GUI::OnInsertCharacterization(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ComponentDetails, Characterization) }
void ComponentDetails_GUI::OnInsertPropertyData(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, PropertyData) }
void ComponentDetails_GUI::OnInsertAssociationDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ComponentDetails, AssociationDetails) }
void ComponentDetails_GUI::OnInsertComponentDetails(wxCommandEvent& event) {
	//NOTE MACRO WILL NOT WORK DUE TO THE DIFFERENCE IN CLASS NAME

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		ComponentDetails* const Element = boost::any_cast<ComponentDetails* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			ComponentDetails::ComponentDetails1_sequence& cont(Element->ComponentDetails1());//Note: THE DIFFERENCE IN FUNCTION NAME
			cont.push_back(Default<::ComponentDetails>());
			ComponentDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemId, cont.back(), wxTreeItemId());
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void ComponentDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(ComponentDetails, Name)}
void ComponentDetails_GUI::OnDeleteClass(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, Class)}
void ComponentDetails_GUI::OnDeleteSubclass1(wxCommandEvent& event)
{
	//ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(ComponentDetails, Subclass)
	//#define ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(parent,child) Doesn't work because ComponentDetails doesn't have a function Subclass1
	Subclass1* element = MatML_Base_GUI::GetSelMatML<Subclass1>(m_MatMLTreeCtrl);
	ComponentDetails* elementparent = MatML_Base_GUI::GetSelParentMatML<ComponentDetails>(m_MatMLTreeCtrl);
	if (element && elementparent) {
		MatML_Base_GUI::DeleteSeqContChild(element->t, elementparent->Subclass());//Note: ComponentDetails doesn't have a function Subclass1
		MatML_Base_GUI::SetupSelParent<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
	}
}
void ComponentDetails_GUI::OnDeleteAssociationDetails(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, AssociationDetails) }
void ComponentDetails_GUI::OnDeleteCharacterization(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ComponentDetails, Characterization)}
//void ComponentDetails_GUI::OnDeleteComponentDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails,ComponentDetails)}
void ComponentDetails_GUI::OnDeleteForm(wxCommandEvent& event) { ON_PARENT_DELETE_CONT_CHILD(ComponentDetails, Form) }
void ComponentDetails_GUI::OnDeleteProcessingDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, ProcessingDetails)}
void ComponentDetails_GUI::OnDeletePropertyData(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, PropertyData)}
void ComponentDetails_GUI::OnDeleteSpecification(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, Specification)}
void ComponentDetails_GUI::OnDeleteSource(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ComponentDetails, Source)}

void ComponentDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(ComponentDetails, Name) }
void ComponentDetails_GUI::OnPasteClass(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails, Class) }
void ComponentDetails_GUI::OnPasteSubclass(wxCommandEvent& event)
{
	//ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails,Subclass1)//This doesn't work because function name differs from child class name.
	//#define ON_PARENT_PASTE_ITER_CONT_CHILD(parent,child) 
	ComponentDetails* element = MatML_Base_GUI::GetSelMatML<ComponentDetails>(m_MatMLTreeCtrl);
	Subclass1* copy_element = boost::any_cast<Subclass1* >(m_MatMLItemToCopy);
	if (element && copy_element) {
		PasteSeqContChild(copy_element, element->Subclass());//Note: function name differs from child class name.
		MatML_Base_GUI::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
	}

}

void ComponentDetails_GUI::OnPasteSpecification(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails, Specification) }
void ComponentDetails_GUI::OnPasteSource(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ComponentDetails, Source) }
void ComponentDetails_GUI::OnPasteForm(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ComponentDetails, Form) }
void ComponentDetails_GUI::OnPasteProcessingDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails, ProcessingDetails) }
void ComponentDetails_GUI::OnPasteCharacterization(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ComponentDetails, Characterization) }
void ComponentDetails_GUI::OnPastePropertyData(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails, PropertyData) }
void ComponentDetails_GUI::OnPasteAssociationDetails(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ComponentDetails, AssociationDetails) }
void ComponentDetails_GUI::OnPasteComponentDetails(wxCommandEvent& event) {
	//NOTE MACRO WILL NOT WORK DUE TO THE DIFFERENCE IN CLASS NAME
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		ComponentDetails* const element = boost::any_cast<ComponentDetails* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			ComponentDetails* const copy_element = boost::any_cast<ComponentDetails* const>(m_MatMLItemToCopy);
			if (copy_element != 0) {
				ComponentDetails::ComponentDetails1_sequence& cont(element->ComponentDetails1());
				try {
					cont.push_back(*copy_element);
					ComponentDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
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

void ComponentDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< ComponentDetails,
		Material,
		Material::ComponentDetails_sequence,
		ComponentDetails_GUI,
		&Material::ComponentDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}
void ComponentDetails_GUI::OnBumpUp(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< ComponentDetails,
		Material,
		Material::ComponentDetails_sequence,
		ComponentDetails_GUI,
		&Material::ComponentDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}