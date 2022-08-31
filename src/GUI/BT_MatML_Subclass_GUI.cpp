#include <wx/config.h>

#include "BT_MatML_Subclass_GUI.h"


using namespace bellshire;

Subclass_GUI_Base::Subclass_GUI_Base()
	:m_GUI(nullptr)
{

}

Subclass_GUI_Base::Subclass_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Subclass_GUI_Base::~Subclass_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* SubclassPanel = new wxScrolledWindow(SubclassNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	MatMLInfo_GUI matMLInfo_GUI(SubclassNotebook,
		wxT("*************** Subclass *************************\n\nThis element declares the content model for Subclass, which is the material \nSubclass to which the Material belongs.\n\t\t\t\nThe Subclass can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's Subclass \nand may occur only once within the Subclass element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Subclass element.\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SubclassNotebook->AddPage(SubclassPanel, wxT("MatML Data."), b_dflt);
	SubclassNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SubclassNotebook;
}

void Subclass_GUI_Base::Update( Subclass* element)
{
	wxString str;

	//Need to add ParentMaterialID

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Subclass_GUI_Base::SetupMatMLTreeCtrl( TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	BulkDetails::Subclass_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Subclass");
	if (Element.Name().present()) str << wxT("-") << _std2wx(Element.Name().get());
	else if (!Element.ParentMaterial().empty()) {
		if (!Element.ParentMaterial().front().id().empty()) {
			const Material* parentmaterial(dynamic_cast<const Material*>(&*Element.ParentMaterial().front().id()));
			if (parentmaterial != NULL) str << wxT("-") << _std2wx(parentmaterial->BulkDetails().Name());
		}
	}
	else str << wxT("Need Name or ParentMaterial");

	wxTreeItemId CurrentId;

	MatMLTreeItemData* data = new MatMLTreeItemData(new Subclass(&Element));

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, data);
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, data);

	//Setup MatML Attribute
	//SetupId();

	//Setup Element Name
	{
		auto& cont(Element.Name());
		if (cont.present())
			Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element ParentMaterial
	{
		auto& cont(Element.ParentMaterial());
		auto iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParentMaterial_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element ParentSubClass
	{
		auto& cont(Element.ParentSubClass());
		auto iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParentSubClass_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	MatMLTreeCtrl->SortChildren(ParentId);

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
	ON_PARENT_STRONGTYPE_INSERT_CONT_CHILD(Subclass, Name) 
	//#define ON_PARENT_INSERT_CONT_CHILD(parent,child) 
	//const Subclass* element = MatML_Base_GUI::GetSelMatML<const Subclass>(m_MatMLTreeCtrl);
	//if (element) {
	//	MatML_Base_GUI::InsertContChild<Name>((element->t)->Name());
	//	MatML_Base_GUI::SetupSel<Subclass,Subclass_GUI>(m_MatMLTreeCtrl);
	//}
}
void Subclass_GUI::OnInsertParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_STRONGTYPE_INSERT_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	//MACRO BELOW WILL NOT WORK DUE TO THE Subclass NAME CHANGE.
	ON_PARENT_STRONGTYPE_INSERT_ITER_CONT_CHILD(Subclass,ParentSubClass)

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
	ON_PARENT_STRONGTYPE_DELETE_CONT_CHILD(Subclass, Name)
}
void Subclass_GUI::OnDeleteParentMaterial(wxCommandEvent& event) {
	ON_PARENT_STRONGTYPE_DELETE_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnDeleteParentSubClass(wxCommandEvent& event) { 
	//ON_PARENT_DELETE_ITER_CONT_CHILD(Subclass, Subclass::ParentSubSubclass) 
	{
		// The following is hand crafted to allow for the Subclass being the container for ParentSubSubclass element type.
		wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
		MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

		wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
		MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

		try {
			Subclass*  elementParent = boost::any_cast<Subclass* >(itemParent->GetAnyMatMLDataPointer());
			if (elementParent != 0) {
				ParentSubClass*  element = boost::any_cast<ParentSubClass* >(item->GetAnyMatMLDataPointer());
				if (element != 0) {
					auto& cont((elementParent->t)->ParentSubClass());
					auto iter(cont.begin());
					for (; iter != cont.end(); ++iter) {
						if (&(*iter) == element->t) {
							cont.erase(iter);
							m_MatMLTreeCtrl->Delete(itemId);
							return;
						}
					}
				}
			}
		}
		catch (const boost::bad_any_cast&) {}
	}
}

void Subclass_GUI::OnPasteName(wxCommandEvent& event) { 
	ON_PARENT_STRONGTYPE_PASTE_CONT_CHILD(Subclass, Name) 
}
void Subclass_GUI::OnPasteParentMaterial(wxCommandEvent& event) { 
	ON_PARENT_STRONGTYPE_PASTE_ITER_CONT_CHILD(Subclass, ParentMaterial) 
}
void Subclass_GUI::OnPasteParentSubClass(wxCommandEvent& event) {
	ON_PARENT_STRONGTYPE_PASTE_ITER_CONT_CHILD(Subclass, ParentSubClass)
	//Subclass* element = MatML_Base_GUI::GetSelMatML<Subclass>(m_MatMLTreeCtrl);
	//ParentSubClass* copy_element = boost::any_cast<ParentSubClass*>(m_MatMLItemToCopy);
	//	if (element && copy_element) {
	//		
	//			PasteSeqContChild(copy_element, element->t->ParentSubClass());
	//			MatML_Base_GUI::SetupSel<Subclass, Subclass_GUI>(m_MatMLTreeCtrl);
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

	IndividualBumpDownStrongtype< Subclass,
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

	IndividualBumpUpStrongtype< Subclass,
		BulkDetails,
		BulkDetails::Subclass_sequence,
		Subclass_GUI,
		&BulkDetails::Subclass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
