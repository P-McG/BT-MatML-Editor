#include <wx/config.h>

#include "BT_MatML_Class_GUI.h"


using namespace bellshire;

Class_GUI_Base::Class_GUI_Base()
	:m_GUI(nullptr)
{

}

Class_GUI_Base::Class_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Class_GUI_Base::~Class_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Class MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ClassNotebook"></param>
/// <param name="ClassPanel"></param>
/// <returns>bool</returns>
wxNotebook* Class_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* ClassNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ClassNotebook->Hide();
	ClassNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ClassPanel = new wxScrolledWindow(ClassNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	MatMLInfo_GUI matMLInfo_GUI(ClassNotebook,
		wxT("*************** Class *************************\n\nThis element declares the content model for Class, which is the material \nclass to which the Material belongs.\n\t\t\t\nThe Class can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's class \nand may occur only once within the Class element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Class element.\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ClassNotebook->AddPage(ClassPanel, wxT("MatML Data."), b_dflt);
	ClassNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ClassNotebook;
}

void Class_GUI_Base::Update( Class* element)
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
wxTreeItemId Class_GUI_Base::SetupMatMLTreeCtrl( TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	Class& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Class");
	if (Element.Name().present()) str << wxT("-") << _std2wx(Element.Name().get());
	else if (!Element.ParentMaterial().empty()) {
		if (!Element.ParentMaterial().front().id().empty()) {
			const Material* parentmaterial(dynamic_cast<const Material*>(&*Element.ParentMaterial().front().id()));
			if (parentmaterial != NULL) str << wxT("-") << _std2wx(parentmaterial->BulkDetails().Name());
		}
	}
	else str << wxT("Need Name or ParentMaterial");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//SetupId();

	//Setup Element Name
	{
		 Class::Name_optional& cont(Element.Name());
		if (cont.present())
			Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element ParentMaterial
	{
		 Class::ParentMaterial_sequence& cont(Element.ParentMaterial());
		Class::ParentMaterial_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParentMaterial_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element ParentSubClass
	{
		 Class::ParentSubClass_sequence& cont(Element.ParentSubClass());
		Class::ParentSubClass_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParentSubClass_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	MatMLTreeCtrl->SortChildren(ParentId);

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
	//const Class* element = MatML_Base_GUI::GetSelMatML<const Class>(m_MatMLTreeCtrl);
	//if (element) {
	//	MatML_Base_GUI::InsertContChild<Name>(const_cast<Class*>(element)->Name());
	//	MatML_Base_GUI::SetupSel<Class,Class_GUI>(m_MatMLTreeCtrl);
	//}
}
void Class_GUI::OnInsertParentMaterial(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Class, ParentMaterial) }
void Class_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	//MACRO BELOW WILL NOT WORK DUE TO THE CLASS NAME CHANGE.
//	ON_PARENT_INSERT_ITER_CONT_CHILD(Class,ParentSubClass)

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		 Class* element = boost::any_cast< Class* >(item->GetAnyMatMLDataPointer());
		if (element != 0) {

			Class::ParentSubClass_sequence& cont(element->ParentSubClass());
			cont.push_back(Default<::Class>());

			Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(itemId), *element, m_MatMLTreeCtrl->GetPrevSibling(itemId));
			
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
	//ON_PARENT_DELETE_ITER_CONT_CHILD(Class, Class::ParentSubClass) 
	{
		// The following is hand crafted to allow for the Class being the container for ParentSubClass element type.
		wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
		MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

		wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
		MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

		try {
			Class*  elementParent = boost::any_cast<Class* >(itemParent->GetAnyMatMLDataPointer());
			if (elementParent != 0) {
				ParentSubClass*  element = boost::any_cast<ParentSubClass* >(item->GetAnyMatMLDataPointer());
				if (element != 0) {
					Class::ParentSubClass_sequence& cont(elementParent->ParentSubClass());
					Class::ParentSubClass_iterator iter(cont.begin());
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

void Class_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Class, Name) }
void Class_GUI::OnPasteParentMaterial(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentMaterial) }
void Class_GUI::OnPasteParentSubClass(wxCommandEvent& event) {/* ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentSubClass)*/
	Class* element = MatML_Base_GUI::GetSelMatML<Class>(m_MatMLTreeCtrl);
	ParentSubClass* copy_element = boost::any_cast<ParentSubClass*>(m_MatMLItemToCopy);
		if (element && copy_element) {
			
				PasteSeqContChild(copy_element, element->ParentSubClass());
				MatML_Base_GUI::SetupSel<Class, Class_GUI>(m_MatMLTreeCtrl);
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
	// this->Freeze();

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	try {
		Class* element = boost::any_cast<Class*>(item->GetAnyMatMLDataPointer());

		try {
			BulkDetails* const elementParent = boost::any_cast<BulkDetails* const>(itemParent->GetAnyMatMLDataPointer());

			BulkDetails::Class_sequence& cont(elementParent->Class());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (BulkDetails::Class_iterator iter = cont.begin(); iter != cont.end() - 1; ++iter) {
				if (element == static_cast<Class*>(&*iter)) {//if the pointer are the same (aka same memory location
					Class temp = *(iter);
					*(iter) = *(iter + 1);
					*(iter + 1) = temp;

					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter + 1), nextitemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(nextitemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Delete(nextitemId);

					// this->Thaw();

					return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {};//do nothing

		try {
			ComponentDetails*  elementParent = boost::any_cast<ComponentDetails* >(itemParent->GetAnyMatMLDataPointer());

			ComponentDetails::Class_sequence& cont(elementParent->Class());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (ComponentDetails::Class_iterator iter = cont.begin(); iter != cont.end() - 1; ++iter) {
				if (element == static_cast<Class*>(&*iter)) {//if the pointer are the same (aka same memory location
					Class temp = *(iter);
					*(iter) = *(iter + 1);
					*(iter + 1) = temp;

					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter + 1), nextitemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(nextitemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Delete(nextitemId);

					// this->Thaw();

					return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {};//do nothing

	}
	catch (const boost::bad_any_cast&) {// this->Thaw();
		return;
	}
}
void Class_GUI::OnBumpUp(wxCommandEvent& event)
{
	// this->Freeze();
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);
	MatMLTreeItemData* previtem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(previtemId));

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	try {
		try {
			BulkDetails*  elementParent = boost::any_cast<BulkDetails* >(itemParent->GetAnyMatMLDataPointer());
			Class* element = boost::any_cast<Class*>(item->GetAnyMatMLDataPointer());

			BulkDetails::Class_sequence& cont(elementParent->Class());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (BulkDetails::Class_iterator iter = cont.begin() + 1; iter != cont.end(); ++iter) {
				if (element == static_cast<Class*>(&*iter)) {//if the pointer are the same (aka same memory location
					Class temp = *(iter);
					*(iter) = *(iter - 1);
					*(iter - 1) = temp;

					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter - 1), previtemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(previtemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(previtemId);
					m_MatMLTreeCtrl->Delete(itemId);//perform last so selection bumps down

					/* this->Thaw();*/ return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}

		try {
			ComponentDetails*  elementParent = boost::any_cast<ComponentDetails* >(itemParent->GetAnyMatMLDataPointer());
			Class* element = boost::any_cast<Class*>(item->GetAnyMatMLDataPointer());

			ComponentDetails::Class_sequence& cont(elementParent->Class());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (ComponentDetails::Class_iterator iter = cont.begin() + 1; iter != cont.end(); ++iter) {
				if (element == static_cast<Class*>(&*iter)) {//if the pointer are the same (aka same memory location
					Class temp = *(iter);
					*(iter) = *(iter - 1);
					*(iter - 1) = temp;

					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					Class_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter - 1), previtemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(previtemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(previtemId);
					m_MatMLTreeCtrl->Delete(itemId);//perform last so selection bumps down

					/* this->Thaw();*/ return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}//

	}
	catch (const boost::bad_any_cast&) {/* this->Thaw();*/ return; }
}
