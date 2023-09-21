#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Subclass_GUI.h"


using namespace bellshire::GUI;

Subclass_GUI_Base::Subclass_GUI_Base()
{

}

Subclass_GUI_Base::Subclass_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Subclass_GUI_Base::~Subclass_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Subclass MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="SubclassNotebook"></param>
/// <param name="SubclassPanel"></param>
/// <returns>bool</returns>
wxNotebook* Subclass_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* SubclassNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SubclassNotebook->Hide();
	SubclassNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* SubclassPanel(CreateSubclassPanel(SubclassNotebook));

	MatMLInfo_GUI matMLInfo_GUI(SubclassNotebook,
		wxT("*************** Subclass *************************\n\nThis element declares the content model for Subclass, which is the material \nSubclass to which the Material belongs.\n\t\t\t\nThe Subclass can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's Subclass \nand may occur only once within the Subclass element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Subclass element.\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SubclassNotebook->AddPage(SubclassPanel, wxT("MatML Data."), b_dflt);
	SubclassNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SubclassNotebook;
}

wxWindow* Subclass_GUI_Base::CreateSubclassPanel(wxWindow* parent)
{

	wxScrolledWindow* SubclassPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SubclassPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1261->AddGrowableCol(0);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(SubclassPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	SubclassPanel->SetSizer(fgSizer1261);
	SubclassPanel->Layout();
	fgSizer1261->Fit(SubclassPanel);

	return SubclassPanel;
}

void Subclass_GUI_Base::Update( const observer_ptr<Subclass> element)
{
	wxString str;

	//Need to add ParentMaterialID

	ShowGUI(true);
}

wxString Subclass_GUI_Base::GetTreeLabel(const observer_ptr<Subclass> element)
{
	wxString str;
	str << wxT("Subclass");

	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element) };
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
/// Constructor for the derived Subclass
/// </summary>
Subclass_GUI::Subclass_GUI() 
	: Subclass_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{
}

/// <summary>
/// Constructor for the derived Subclass
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Subclass_GUI::Subclass_GUI(wxWindow* parent)
	: Subclass_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived Subclass
/// </summary>
Subclass_GUI::~Subclass_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Subclass_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Subclass_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived Subclass's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Subclass_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived Subclass's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Subclass_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Subclass_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Subclass_GUI::OnInsertName(wxCommandEvent& event) {
	ON_PARENT_INSERT_CONT_CHILD(Subclass, Name) 
}
void Subclass_GUI::OnInsertParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_INSERT_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	//MACRO BELOW WILL NOT WORK DUE TO THE Subclass NAME CHANGE.
	ON_PARENT_INSERT_ITER_CONT_CHILD(Subclass,ParentSubClass)

	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	 Subclass* element = boost::any_cast< Subclass* >(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {

	//		auto& cont((element->t)->ParentSubClass());
	//		cont.push_back(Default<::Subclass>());

	//		Subclass_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, m_MatMLTreeCtrl->GetPrevSibling(itemId));
	//		
	//		m_MatMLTreeCtrl->Expand(m_MatMLTreeCtrl->GetSelection());
	//		m_MatMLTreeCtrl->Delete(itemId);
	//		return;
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}

void Subclass_GUI::OnDeleteName(wxCommandEvent& event) {
	ON_PARENT_DELETE_CONT_CHILD(Subclass, Name)
}
void Subclass_GUI::OnDeleteParentMaterial(wxCommandEvent& event) {
	ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnDeleteParentSubClass(wxCommandEvent& event) { 
	ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass, ParentSubClass) 

	////ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass, Subclass::ParentSubSubclass) 
	//{
	//	// The following is hand crafted to allow for the Subclass being the container for ParentSubSubclass element type.
	//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	//	wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
	//	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	//	try {
	//		Subclass*  elementParent = boost::any_cast<Subclass* >(itemParent->GetAnyMatMLDataPointer());
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

void Subclass_GUI::OnPasteName(wxCommandEvent& event) { 
	ON_PARENT_PASTE_CONT_CHILD(Subclass, Name) 
}
void Subclass_GUI::OnPasteParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_PASTE_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnPasteParentSubClass(wxCommandEvent& event) {
	ON_PARENT_PASTE_ITER_CONT_CHILD(Subclass, ParentSubClass)
	//Subclass* element = MatML_GUI_Base::GetSelMatML<Subclass>(m_MatMLTreeCtrl);
	//ParentSubClass* copy_element = boost::any_cast<ParentSubClass*>(m_MatMLItemToCopy);
	//	if (element && copy_element) {
	//		
	//			PasteSeqContChild(copy_element, element->t->ParentSubClass());
	//			MatML_GUI_Base::SetupSel<Subclass, Subclass_GUI>(m_MatMLTreeCtrl);
	//	}
	//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	//try {
	//	Subclass* element = boost::any_cast<Subclass*>(item->GetAnyMatMLDataPointer());
	//	if (element != 0) {
	//		Subclass* copy_element = boost::any_cast<Subclass*>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {
	//			Subclass::ParentSubSubclass_sequence& cont(element->ParentSubSubclass());
	//			try {
	//				cont.push_back(*copy_element);
	//				Subclass_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, itemId);
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

void Subclass_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Subclass,
		BulkDetails,
		BulkDetails::Subclass_sequence,
		Subclass_GUI,
		&BulkDetails::Subclass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}
void Subclass_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Subclass,
		BulkDetails,
		BulkDetails::Subclass_sequence,
		Subclass_GUI,
		&BulkDetails::Subclass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
