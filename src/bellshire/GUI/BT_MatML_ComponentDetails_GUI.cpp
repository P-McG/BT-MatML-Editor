#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_ComponentDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire::GUI;

ComponentDetails_GUI_Base::ComponentDetails_GUI_Base()
	:m_ComponentDetails_ID_GUI(nullptr)
{

}

ComponentDetails_GUI_Base::ComponentDetails_GUI_Base(wxWindow* parent)
	:m_ComponentDetails_ID_GUI(nullptr)
{
	//Only Get LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt) {
		m_lib_element.release();
		m_lib_element = std::move(GetLib<bellshire::Lib::ComponentDetails_lib>(/*m_lib, */"ComponentDetails_lib.xml"));
	}


	m_GUI = Create(parent, 
		m_ComponentDetails_ID_GUI,
		m_MatMLLibTreeCtrl,
		m_lib_element.get(),
		m_droptarget
	);
}

ComponentDetails_GUI_Base::ComponentDetails_GUI_Base(std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI, MatMLLibDropTarget* droptarget)
	: m_droptarget(droptarget)
{
	 m_ComponentDetails_ID_GUI.reset(ComponentDetails_ID_GUI.release());
}

ComponentDetails_GUI_Base::~ComponentDetails_GUI_Base() {

	wxConfig config(wxT("BTMatML"));
	bool worked = false;

	//Only Save LibPanel if MatMLLibHidePriorSelection is NOT selected in preference
	bool b2_dflt(false);//default value
	config.Read(wxT("/General/MatMLLibHidePriorSelection"), &b2_dflt);
	if (!b2_dflt)
		SetLib<bellshire::Lib::ComponentDetails_lib>(/*
			m_lib,*/
			m_lib_element,
			"ComponentDetails_lib.xml"
		);

	//Copy the Current MatMLLibHideSelection to MatMLLibHidePriorSelection now that we are done with it and set it up
	// for the next run.
	bool b_dflt(false);//temps
	if (config.Read(wxT("/General/MatMLLibHideSelection"), &b_dflt)) {
		worked = config.Write(wxT("/General/MatMLLibHidePriorSelection"), b_dflt);
		assert(worked);
	}

	/*parent will destroy Ctrl or window */
	//delete m_ComponentDetails_ID_GUI;//this is neither a window nor a ctrl.	
}

//ID_GUI* bellshire::ComponentDetails_GUI_Base::GetComponentDetails_ID_GUI()
//{
//	return m_ComponentDetails_ID_GUI;
//}

MatMLLibDropTarget* ComponentDetails_GUI_Base::GetDropTarget()
{
	return m_droptarget;
}


/// <summary>
/// Create the GUI for the ComponentDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ComponentDetails_ID_GUI"></param>
/// <returns>bool</returns>
wxNotebook* ComponentDetails_GUI_Base::Create(wxWindow* parent, 
	std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI,
	TreeCtrlSorted*& MatMLLibTreeCtrl,
	observer_ptr<xml_schema::element_type> lib_element,
	MatMLLibDropTarget* droptarget
)
{
	wxNotebook* ComponentDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ComponentDetailsNotebook->Hide();
	ComponentDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ComponentDetailsPanel{ CreateComponentDetailsPanel(ComponentDetailsNotebook, ComponentDetails_ID_GUI) };

	//MatML Info Panel
	//================

	MatMLInfo_GUI matMLInfo_GUI(ComponentDetailsNotebook,
		wxT("************ ComponentDetails *************************\n\nThis element declares the content model for ComponentDetails, which\ncontains a description of a component within the bulk material and has\none optional attribute, id, which may be used as an identification\nspecifier for the component and is especially useful for complex\nsystems such as composite laminates.\n \nComponentDetails is composed of the following elements.\n\nName contains the component's name and has one optional attribute,\nauthority, for identifying an authoritative source of component names.\nName must occur once and only once within the ComponentDetails\ntype.\n\nClass contains the component's class and may occur zero or more\ntimes within the ComponentDetails element. For additional information, \nsee the documentation for the Class type.\n\nSubclass contains the component's subclass(es) and may occur zero\nor more times within the ComponentDetails element. For additional\ninformation, see the documentation for the SubClass type.\n\nSpecification contains the component's specification(s) and has one\noptional attribute, authority, for identifying an authoritative\nsource of component specifications. Specification may occur zero or\nmore times within the ComponentDetails type.\n\nSource contains the name of the source of the component and may\noccur once or not at all within the ComponentDetails type. For \nadditional information, see the documentation for the SourceDetails \nelement.\n\nForm contains the form of the component and may occur once or not\nat all within the ComponentDetails type. It has an optional element \nGeometry, for describing the dimensions of the Component. For \nadditional information, see the documentation for the Form type.\n\nProcessingDetails contains a description of a processing step for\nthe component and may occur zero or more times within the\nComponentDetails type. For additional information, see the\ndocumentation for the ProcessingDetails element.\n\nCharacterization contains the characterization of the component,\nincluding the formula, chemical composition, phase composition, and\ndimensional details. Characterization may occur once or not at all\nwithin the ComponentDetails type. For additional information, see\nthe documentation for the Characterization element.\n\nPropertyData contains the property data for the component and may\noccur zero or more times within the ComponentDetails type. For\nadditional information, see the documentation for the PropertyData\nelement.\n\nAssociationDetails contains a description of a relationship of the\ncomponent to another component and may occur zero or more times\nwithin the ComponentDetails type. For additional information, see\nthe documentation for the AssociationDetails element.\n\nNotes contains any additional information concerning the component\nand may occur once or not at all within the ComponentDetails type.\n\nComponentDetails contains a description of a component within the\ncomponent and is used to support encoding of information for\ncomplex materials systems such as composites. ComponentDetails\nmay occur zero or more times within a ComponentDetails element.\t\t")
	);

	wxWindow* LibPanel = nullptr;

	//Only Create LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt)
		LibPanel = CreateLibPanel<
		ComponentDetails, 
		ComponentDetails_Base,
		::bellshire::Lib::ComponentDetails_lib
		>(ComponentDetailsNotebook, MatMLLibTreeCtrl, lib_element, droptarget);


	// Notebook assembly
	// =================

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ComponentDetailsNotebook->AddPage(ComponentDetailsPanel, wxT("MatML Data."), b_dflt);
	ComponentDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);
	if (!b2_dflt) ComponentDetailsNotebook->AddPage(LibPanel, wxT("MatML Lib."), false);

	return ComponentDetailsNotebook;
}

wxWindow* ComponentDetails_GUI_Base::CreateComponentDetailsPanel(
	wxWindow* parent,
	std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI
	)
{
	wxScrolledWindow* ComponentDetailsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ComponentDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	ComponentDetails_ID_GUI = std::move(std::make_unique<ID_GUI>(ComponentDetailsPanel));
	bSizer1->Add(ComponentDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	ComponentDetailsPanel->SetSizer(bSizer1);
	ComponentDetailsPanel->Layout();
	bSizer1->Fit(ComponentDetailsPanel);

	return ComponentDetailsPanel;
}

void ComponentDetails_GUI_Base::Update( const observer_ptr<ComponentDetails> element)
{

	m_ComponentDetails_ID_GUI->Update(element);

	//Only Update LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt)
		UpdateLib<ComponentDetails, ComponentDetails_GUI, bellshire::Lib::ComponentDetails_lib>(m_MatMLLibTreeCtrl, m_lib_element.get());

	ShowGUI(true);

}

wxString ComponentDetails_GUI_Base::GetTreeLabel(const observer_ptr<ComponentDetails> element)
{
	wxString str;
	str << wxT("ComponentDetails");

	return str;
}


void ComponentDetails_GUI_Base::SetConnect()
{
	//Only Connect to LibPanel if HideLibPanelSelection is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt)
		MatML_GUI_Base::SetLibConnect();

}


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
	: ComponentDetails_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ComponentDetails_GUI::~ComponentDetails_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* ComponentDetails_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any ComponentDetails_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ComponentDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLdoc)
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
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML<ComponentDetails>(m_MatMLTreeCtrl))};
	if (element_observer) {
		MatML_GUI_Base::InsertSeqContChild<Subclass1>(element_observer->Subclass());
		MatML_GUI_Base::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
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

	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML<ComponentDetails>(m_MatMLTreeCtrl)) }; 
	if (element_observer) {
		MatML_GUI_Base::InsertSeqContChild<AssociationDetails>(element_observer->AssociationDetails());
		MatML_GUI_Base::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
	}

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	//try {
	//	ComponentDetails* const Element = boost::any_cast<ComponentDetails* const>(item->GetAnyMatMLDataPointer());
	//	if (Element != 0) {
	//		ComponentDetails::ComponentDetails1_sequence& cont(Element->ComponentDetails1());//Note: THE DIFFERENCE IN FUNCTION NAME
	//		cont.push_back(Default<::ComponentDetails>());

	//		Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, itemId, wxTreeItemId() });
	//		ComponentDetails_GUI::TraverseMatMLTree(&cont.back(), func1);
	//		return;
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}

void ComponentDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(ComponentDetails, Name)}
void ComponentDetails_GUI::OnDeleteClass(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, Class)}
void ComponentDetails_GUI::OnDeleteSubclass1(wxCommandEvent& event)
{
	//ON_PARENT_DELETE_ITER_CONT_CHILD(ComponentDetails, Subclass)
	//#define ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(parent,child) Doesn't work because ComponentDetails doesn't have a function Subclass1
	auto element{ MatML_GUI_Base::GetSelMatML<Subclass>(m_MatMLTreeCtrl) }; 
	 auto element_parent_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelParentMatML<ComponentDetails>(m_MatMLTreeCtrl)) }; 
	if (element_parent_observer) {
		MatML_Base::DeleteSeqContChild(element, element_parent_observer->Subclass());
		MatML_GUI_Base::SetupSelParent<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
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
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< ComponentDetails >(m_MatMLTreeCtrl)) }; 
	auto copy_element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<Subclass1> >(m_MatMLItemToCopy)) }; 
	if (element_observer) {
		MatML_Base::PasteSeqContChild(copy_element, element_observer->Subclass()); MatML_GUI_Base::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
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
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< ComponentDetails >(m_MatMLTreeCtrl)) };
	auto copy_element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<ComponentDetails> >(m_MatMLItemToCopy)) }; 
	if (element_observer) {
		MatML_Base::PasteSeqContChild(copy_element, element_observer->ComponentDetails1());
		MatML_GUI_Base::SetupSel<ComponentDetails, ComponentDetails_GUI>(m_MatMLTreeCtrl);
	}

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	ComponentDetails* const element = boost::any_cast<ComponentDetails* const>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		ComponentDetails* const copy_element = boost::any_cast<ComponentDetails* const>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			ComponentDetails::ComponentDetails1_sequence& cont(element->ComponentDetails1());
	//			try {
	//				cont.push_back(*copy_element);

	//				Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), itemId });
	//				ComponentDetails_GUI::TraverseMatMLTree(element, func1);

	//				m_MatMLTreeCtrl->Delete(itemId);
	//				m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
	//				return;
	//			}
	//			catch (const xml_schema::duplicate_id&) { return; }
	//		}
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}

/// <summary>
/// the OnBumpDown function for ComponentDetails is required
/// to handle the required ComponentDetails->id();
/// </summary>
/// <param name="event"></param>
void ComponentDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< ComponentDetails,
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

	IndividualBumpUpHavingId< ComponentDetails,
		Material,
		Material::ComponentDetails_sequence,
		ComponentDetails_GUI,
		&Material::ComponentDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

void ComponentDetails_GUI::OnLeftDown(wxTreeEvent& event)
{
	DnDSource(event, m_MatMLLibTreeCtrl, m_GUI);
}




bool ComponentDetails_GUI_Base::operator==(const ComponentDetails_GUI_Base& other) const
{
	return m_ComponentDetails_ID_GUI == other.m_ComponentDetails_ID_GUI && m_droptarget == other.m_droptarget;
}
