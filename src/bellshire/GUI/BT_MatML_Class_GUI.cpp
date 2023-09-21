#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Class_GUI.h"


using namespace bellshire::GUI;

Class_GUI_Base::Class_GUI_Base()
	//:m_GUI(nullptr)
{

}

Class_GUI_Base::Class_GUI_Base(wxWindow* parent)
	//: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Class_GUI_Base::~Class_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Class MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ClassNotebook"></param>
/// <param name="ClassPanel"></param>
/// <returns>bool</returns>
wxNotebook* Class_GUI_Base::Create(wxWindow* parent	)
{
	wxNotebook* ClassNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ClassNotebook->Hide();
	ClassNotebook->SetMinSize(wxSize(400, 500));
	
	wxWindow* ClassPanel(CreateClassPanel(ClassNotebook));

	//MatML Info Panel
	//================

	MatMLInfo_GUI matMLInfo_GUI(ClassNotebook,
		wxT("*************** Class *************************\n\nThis element declares the content model for Class, which is the material \nclass to which the Material belongs.\n\t\t\t\nThe Class can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's class \nand may occur only once within the Class element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Class element.\t")
	);

	// Notebook assembly
	// =================

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ClassNotebook->AddPage(ClassPanel, wxT("MatML Data."), b_dflt);
	ClassNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ClassNotebook;
}

wxWindow* Class_GUI_Base::CreateClassPanel(wxWindow* parent)
{
	wxScrolledWindow* ClassPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ClassPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1261->AddGrowableCol(0);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(ClassPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	ClassPanel->SetSizer(fgSizer1261);
	ClassPanel->Layout();
	fgSizer1261->Fit(ClassPanel);

	return ClassPanel;
}

void Class_GUI_Base::Update( const observer_ptr<Class> element)
{
	wxString str;

	//Need to add ParentMaterialID

	ShowGUI(true);
}

wxString Class_GUI_Base::GetTreeLabel(const observer_ptr<Class> element)
{
	wxString str;

	if (element) {
		str << wxT("Class");
		if (element->Name().present()) str << wxT("-") << _std2wx(element->Name().get());
		else if (!element->ParentMaterial().empty()) {
			if (!element->ParentMaterial().front().id().empty()) {
				const Material* parentmaterial(dynamic_cast<const Material*>(&*element->ParentMaterial().front().id()));
				if (parentmaterial != NULL) str << wxT("-") << _std2wx(parentmaterial->BulkDetails().Name());
			}
		}
		else str << wxT("Need Name or ParentMaterial");
	}

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Class_GUI::Class_GUI() 
	: Class_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{
}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Class_GUI::Class_GUI(wxWindow* parent)
	: Class_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Class_GUI::~Class_GUI() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Class_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Class_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Class_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Class_GUI::OnInsertName(wxCommandEvent& event) {
	ON_PARENT_INSERT_CONT_CHILD(Class, Name) 
//#define ON_PARENT_INSERT_CONT_CHILD(parent,child) 
	//const Class* element = MatML_GUI_Base::GetSelMatML<const Class>(m_MatMLTreeCtrl);
	//if (element) {
	//	MatML_GUI_Base::InsertContChild<Name>(const_cast<Class*>(element)->Name());
	//	MatML_GUI_Base::SetupSel<Class,Class_GUI>(m_MatMLTreeCtrl);
	//}
}
void Class_GUI::OnInsertParentMaterial(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Class, ParentMaterial) }
void Class_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	//MACRO BELOW WILL NOT WORK DUE TO THE CLASS NAME CHANGE.
//	ON_PARENT_INSERT_ITER_CONT_CHILD(Class,ParentSubClass)

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		  auto element = boost::any_cast< observer_ptr<Class> >(item->GetAnyMatMLDataPointer());
		if (element) {

			auto& cont(element->ParentSubClass());
			cont.push_back(Default<::Class>());

			bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(
				bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{
					m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), m_MatMLTreeCtrl->GetPrevSibling(itemId) 
				});
			Class_GUI::TraverseMatMLTree(element, func1);
			
			m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
			m_MatMLTreeCtrl->Delete(itemId);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Class_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Class, Name)}
void Class_GUI::OnDeleteParentMaterial(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Class, ParentMaterial) }
void Class_GUI::OnDeleteParentSubClass(wxCommandEvent& event) { 
	//ON_PARENT_DELETE_ITER_CONT_CHILD(Class, Class::ParentSubClass_type) 
		
	auto element{ MatML_GUI_Base::GetSelMatML<Class::ParentSubClass_type>(m_MatMLTreeCtrl) };
	 auto element_parent{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelParentMatML<Class>(m_MatMLTreeCtrl)) }; 
	if (element_parent) {
		MatML_Base::DeleteSeqContChild(element, element_parent->Class::ParentSubClass());
		MatML_GUI_Base::SetupSelParent<Class, Class_GUI>(m_MatMLTreeCtrl);
	}


	//{
	//	// The following is hand crafted to allow for the Class being the container for ParentSubClass element type.
	//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	//	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	//	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	//	try {
	//		 auto& element_parent_observer = boost::any_cast<observer_ptr<Class> >(itemParent->GetAnyMatMLDataPointer()).lock();
	//		if (element_parent_observer) {
	//			ParentSubClass*  element = boost::any_cast<ParentSubClass* >(item->GetAnyMatMLDataPointer());
	//			if (element != 0) {
	//				Class::ParentSubClass_sequence& cont(elementParent->ParentSubClass());
	//				Class::ParentSubClass_iterator iter(cont.begin());
	//				for (; iter != cont.end(); ++iter) {
	//					auto lhs{&(*iter)};	
	//					auto rhs{element->t};
	//					if ( lhs == rhs) {
	//						cont.erase(iter);
	//						m_MatMLTreeCtrl->Delete(itemId);
	//						return;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	catch (const boost::bad_any_cast&) {}
	//}
}

void Class_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Class, Name) }
void Class_GUI::OnPasteParentMaterial(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentMaterial) }
void Class_GUI::OnPasteParentSubClass(wxCommandEvent& event) {
	/* ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentSubClass)*/
	auto element{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< Class >(m_MatMLTreeCtrl)) };
	auto copy_element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<ParentSubClass> >(m_MatMLItemToCopy)) };
	if (element) {
		MatML_Base::PasteSeqContChild(copy_element, element->ParentSubClass()); 
		MatML_GUI_Base::SetupSel<Class, Class_GUI>(m_MatMLTreeCtrl);
	}

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	Class* element = boost::any_cast<Class*>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		Class* copy_element = boost::any_cast<Class*>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			Class::ParentSubClass_sequence& cont(element->ParentSubClass());
	//			try {
	//				cont.push_back(*copy_element);
	//				Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
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

void Class_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Class,
		BulkDetails,
		BulkDetails::Class_sequence,
		Class_GUI,
		&BulkDetails::Class
	>
	(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< Class,
		ComponentDetails,
		ComponentDetails::Class_sequence,
		Class_GUI,
		&ComponentDetails::Class
	>
	(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);
}
void Class_GUI::OnBumpUp(wxCommandEvent& event)
{
	// this->Freeze();
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);
	//MatMLTreeItemData* previtem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(previtemId));

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Class,
		BulkDetails,
		BulkDetails::Class_sequence,
		Class_GUI,
		&BulkDetails::Class
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);


	IndividualBumpUp< Class,
		ComponentDetails,
		ComponentDetails::Class_sequence,
		Class_GUI,
		&ComponentDetails::Class
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
