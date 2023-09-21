#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Subclass1_GUI.h"


using namespace bellshire::GUI;

Subclass1_GUI_Base::Subclass1_GUI_Base()
{

}

Subclass1_GUI_Base::Subclass1_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Subclass1_GUI_Base::~Subclass1_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Subclass1 MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="Subclass1Notebook"></param>
/// <param name="Subclass1Panel"></param>
/// <returns>bool</returns>
wxNotebook* Subclass1_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* Subclass1Notebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	Subclass1Notebook->Hide();
	Subclass1Notebook->SetMinSize(wxSize(400, 500));

	wxWindow* Subclass1Panel(CreateSubclass1Panel(Subclass1Notebook));

	MatMLInfo_GUI matMLInfo_GUI(Subclass1Notebook,
		wxT("*************** Subclass1 *************************\n\nThis element declares the content model for Subclass1, which is the material \nSubclass1 to which the Material belongs.\n\t\t\t\nThe Subclass1 can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's Subclass1 \nand may occur only once within the Subclass1 element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Subclass1 element.\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	Subclass1Notebook->AddPage(Subclass1Panel, wxT("MatML Data."), b_dflt);
	Subclass1Notebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return Subclass1Notebook;
}

wxWindow* Subclass1_GUI_Base::CreateSubclass1Panel(wxWindow* parent)
{

	wxScrolledWindow* Subclass1Panel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	Subclass1Panel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1261->AddGrowableCol(0);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(Subclass1Panel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	Subclass1Panel->SetSizer(fgSizer1261);
	Subclass1Panel->Layout();
	fgSizer1261->Fit(Subclass1Panel);

	return Subclass1Panel;
}

void Subclass1_GUI_Base::Update( const observer_ptr<Subclass1> element)
{
	wxString str;

	//Need to add ParentMaterialID

	ShowGUI(true);
}

wxString Subclass1_GUI_Base::GetTreeLabel(const observer_ptr<Subclass1> element)
{
	wxString str;
	str << wxT("Subclass1");
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element)};
	if (element_observer) {
		if (element_observer->Name().present()) str << wxT("-") << _std2wx(element_observer->Name().get());
		else if (!element_observer->ParentMaterial().empty()) {
			if (!element_observer->ParentMaterial().front().id().empty()) {
				const Material* parentmaterial(dynamic_cast<const Material*>(&*element_observer->ParentMaterial().front().id()));
				if (parentmaterial != NULL) str << wxT("-") << _std2wx(parentmaterial->BulkDetails().Name());
			}
		}
		else str << wxT("Need Name or ParentMaterial");
	}

	return str;
}


/// <summary>
/// Constructor for the derived Subclass1
/// </summary>
Subclass1_GUI::Subclass1_GUI() 
	: Subclass1_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{
}

/// <summary>
/// Constructor for the derived Subclass1
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Subclass1_GUI::Subclass1_GUI(wxWindow* parent)
	: Subclass1_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived Subclass1
/// </summary>
Subclass1_GUI::~Subclass1_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Subclass1_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Subclass1_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived Subclass1's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Subclass1_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived Subclass1's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Subclass1_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Subclass1_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Subclass1_GUI::OnInsertName(wxCommandEvent& event) {
	ON_PARENT_INSERT_CONT_CHILD(Subclass1, Name) 
	//#define ON_PARENT_INSERT_CONT_CHILD(parent,child) 
	//const Subclass1* element = MatML_GUI_Base::GetSelMatML<const Subclass1>(m_MatMLTreeCtrl);
	//if (element) {
	//	MatML_GUI_Base::InsertContChild<Name>((element->t)->Name());
	//	MatML_GUI_Base::SetupSel<Subclass1,Subclass1_GUI>(m_MatMLTreeCtrl);
	//}
}
void Subclass1_GUI::OnInsertParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_INSERT_ITER_CONT_CHILD(Subclass1, ParentMaterial) 
}
void Subclass1_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	//MACRO BELOW WILL NOT WORK DUE TO THE Subclass1 NAME CHANGE.
	ON_PARENT_INSERT_ITER_CONT_CHILD(Subclass1,ParentSubClass)

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	 Subclass1* element = boost::any_cast< Subclass1* >(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {

	//		auto& cont((element->t)->ParentSubClass());
	//		cont.push_back(Default<::Subclass1>());

	//		Subclass1_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, m_MatMLTreeCtrl->GetPrevSibling(itemId));
	//		
	//		m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
	//		m_MatMLTreeCtrl->Delete(itemId);
	//		return;
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}

void Subclass1_GUI::OnDeleteName(wxCommandEvent& event) {
	ON_PARENT_DELETE_CONT_CHILD(Subclass1, Name)
}
void Subclass1_GUI::OnDeleteParentMaterial(wxCommandEvent& event) {
	ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass1, ParentMaterial) 
}
void Subclass1_GUI::OnDeleteParentSubClass(wxCommandEvent& event) { 
	ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass1, ParentSubClass) 
	//{
	//	// The following is hand crafted to allow for the Subclass1 being the container for ParentSubSubclass1 element type.
	//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	//	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	//	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	//	try {
	//		Subclass1*  elementParent = boost::any_cast<Subclass1* >(itemParent->GetAnyMatMLDataPointer());
	//		if (elementParent != 0) {
	//			ParentSubClass*  element = boost::any_cast<ParentSubClass* >(item->GetAnyMatMLDataPointer());
	//			if (element != 0) {
	//				auto& cont((elementParent->t)->ParentSubClass());
	//				auto iter(cont.begin());
	//				for (; iter != cont.end(); ++iter) {
	//					if (&(*iter) == element->t) {
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

void Subclass1_GUI::OnPasteName(wxCommandEvent& event) { 
	ON_PARENT_PASTE_CONT_CHILD(Subclass1, Name) 
}
void Subclass1_GUI::OnPasteParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_PASTE_ITER_CONT_CHILD(Subclass1, ParentMaterial) 
}
void Subclass1_GUI::OnPasteParentSubClass(wxCommandEvent& event) {
	ON_PARENT_PASTE_ITER_CONT_CHILD(Subclass1, ParentSubClass)
	//Subclass1* element = MatML_GUI_Base::GetSelMatML<Subclass1>(m_MatMLTreeCtrl);
	//ParentSubClass* copy_element = boost::any_cast<ParentSubClass*>(m_MatMLItemToCopy);
	//	if (element && copy_element) {
	//		
	//			PasteSeqContChild(copy_element, element->t->ParentSubClass());
	//			MatML_GUI_Base::SetupSel<Subclass1, Subclass1_GUI>(m_MatMLTreeCtrl);
	//	}
	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	Subclass1* element = boost::any_cast<Subclass1*>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		Subclass1* copy_element = boost::any_cast<Subclass1*>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			Subclass1::ParentSubSubclass1_sequence& cont(element->ParentSubSubclass1());
	//			try {
	//				cont.push_back(*copy_element);
	//				Subclass1_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
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

void Subclass1_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Subclass1,
		ComponentDetails,
		ComponentDetails::Subclass_sequence,
		Subclass1_GUI,
		&ComponentDetails::Subclass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Subclass1_GUI::OnBumpUp(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);
	MatMLTreeItemData* previtem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(previtemId));

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Subclass1,
		ComponentDetails,
		ComponentDetails::Subclass_sequence,
		Subclass1_GUI,
		&ComponentDetails::Subclass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
