#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_ParentSubClass_GUI.h"


using namespace bellshire::GUI;

ParentSubClass_GUI_Base::ParentSubClass_GUI_Base()
	:m_ParentSubClassTextCtrl(nullptr)
{

}

ParentSubClass_GUI_Base::ParentSubClass_GUI_Base(wxWindow* parent)
	:m_ParentSubClassTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ParentSubClassTextCtrl);
}

ParentSubClass_GUI_Base::~ParentSubClass_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* ParentSubClass_GUI_Base::GetParentSubClassTextCtrl()
{
	return m_ParentSubClassTextCtrl;
}

/// <summary>
/// Create the GUI for the ParentSubClass MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ParentSubClassNotebook"></param>
/// <param name="ParentSubClassPanel"></param>
/// <returns>bool</returns>
wxNotebook* ParentSubClass_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& ParentSubClassTextCtrl
)
{
	wxNotebook* ParentSubClassNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ParentSubClassNotebook->Hide();
	ParentSubClassNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ParentSubClassPanel(CreateParentSubClassPanel(ParentSubClassNotebook,
		ParentSubClassTextCtrl
	));

	MatMLInfo_GUI matMLInfo_GUI(ParentSubClassNotebook,
		wxT("*************** ParentSubClass *************************\n\nThis element declares the content model for ParentSubClass, which is the material \nclass to which the Material belongs.\n\t\t\t\nThe ParentSubClass can either have a Name or ParentMaterial element:\n\t\t\t\nName contains a string representing the name of the material's class \nand may occur only once within the ParentSubClass element.\n\t\t\t\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the ParentSubClass element.\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ParentSubClassNotebook->AddPage(ParentSubClassPanel, wxT("MatML Data."), b_dflt);
	ParentSubClassNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ParentSubClassNotebook;
}

wxWindow* ParentSubClass_GUI_Base::CreateParentSubClassPanel(wxWindow* parent,
	wxTextCtrl*& ParentSubClassTextCtrl
)
{

	wxScrolledWindow* ParentSubClassPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ParentSubClassPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1261->AddGrowableCol(1);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(ParentSubClassPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	ParentSubClassPanel->SetSizer(fgSizer1261);
	ParentSubClassPanel->Layout();
	fgSizer1261->Fit(ParentSubClassPanel);

	return ParentSubClassPanel;
}

void ParentSubClass_GUI_Base::Update(const observer_ptr<ParentSubClass> element)
{
	wxString str;

	//Need to add ParentMaterialID

	ShowGUI(true);
}

wxString ParentSubClass_GUI_Base::GetTreeLabel(const observer_ptr<ParentSubClass> element)
{
	wxString str;

	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element) };
	if (element_observer) {
		str << wxT("ParentSubClass");
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
/// Constructor for the derived class
/// </summary>
ParentSubClass_GUI::ParentSubClass_GUI() : 
	ParentSubClass_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{
}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ParentSubClass_GUI::ParentSubClass_GUI(wxWindow* parent)
	: ParentSubClass_GUI_Base(parent), 
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ParentSubClass_GUI::~ParentSubClass_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* ParentSubClass_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any ParentSubClass_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParentSubClass_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParentSubClass_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ParentSubClass_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}


void ParentSubClass_GUI::OnInsertName(wxCommandEvent& event) { 

	wxString str;//for testing

	auto  element_observer = (remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< ParentSubClass>(m_MatMLTreeCtrl)));
	if (element_observer) {
		MatML_GUI_Base::InsertContChild<Name>(element_observer->Name());
		MatML_GUI_Base::SetupSel<ParentSubClass, ParentSubClass_GUI>(m_MatMLTreeCtrl);

		//str << _std2wx((element->t.Name().get()));//double parenthesis required
	}

	//str << _std2wx((element->t.Name().get()));//double parenthesis required
}

void ParentSubClass_GUI::OnInsertParentMaterial(wxCommandEvent& event) {
	//ON_PARENT_INSERT_ITER_CONT_CHILD(Class::ParentSubClass_type, ParentMaterial)
	//#define ON_PARENT_INSERT_ITER_CONT_CHILD(parent,child) 
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< ParentSubClass>(m_MatMLTreeCtrl)) };
	if (element_observer) {
		MatML_GUI_Base::InsertSeqContChild<ParentMaterial>(element_observer->ParentMaterial());
		MatML_GUI_Base::SetupSel<ParentSubClass, ParentSubClass_GUI>(m_MatMLTreeCtrl);
	}
}

void ParentSubClass_GUI::OnInsertParentSubClass(wxCommandEvent& event) {
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< ParentSubClass>(m_MatMLTreeCtrl))};
	if (element_observer) {
		MatML_GUI_Base::InsertSeqContChild<ParentSubClass>(element_observer->ParentSubClass());
		MatML_GUI_Base::SetupSel<ParentSubClass, ParentSubClass_GUI>(m_MatMLTreeCtrl);
	}
}

void ParentSubClass_GUI::OnDeleteName(wxCommandEvent& event) { 
	//ON_PARENT_DELETE_CONT_CHILD(ParentSubClass, Name) 
//#define ON_PARENT_DELETE_CONT_CHILD(parent,child) 
	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelParentMatML<ParentSubClass>(m_MatMLTreeCtrl))};
	if (element_observer) {
		MatML_GUI_Base::DeleteContChild(element_observer->Name());
		MatML_GUI_Base::SetupSelParent<ParentSubClass, ParentSubClass_GUI>(m_MatMLTreeCtrl);
	}
}
void ParentSubClass_GUI::OnDeleteParentMaterial(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Class, ParentMaterial) }
void ParentSubClass_GUI::OnDeleteParentSubClass(wxCommandEvent& event) {
	//ON_PARENT_DELETE_ITER_CONT_CHILD(Class, Class::ParentSubClass) 
	{
		// The following is hand crafted to allow for the Class being the container for ParentSubClass element type.
		wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
		MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

		wxTreeItemId itemParentId = m_MatMLTreeCtrl->GetItemParent(itemId);
		MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

		try {
			 auto element_parent_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Class>>(itemParent->GetAnyMatMLDataPointer()))};
			if (element_parent_observer) {
				auto  element_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<ParentSubClass>>(item->GetAnyMatMLDataPointer()))};
				if (element_observer) {
					Class::ParentSubClass_sequence& cont(element_parent_observer->ParentSubClass());
					Class::ParentSubClass_iterator iter(cont.begin());
					for (; iter != cont.end(); ++iter) {
						if (&(*iter) == element_observer) {
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

void ParentSubClass_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Class, Name) }
void ParentSubClass_GUI::OnPasteParentMaterial(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentMaterial) }
void ParentSubClass_GUI::OnPasteParentSubClass(wxCommandEvent& event) {
	//ON_PARENT_PASTE_ITER_CONT_CHILD(Class, ParentSubClass)

	auto element_observer{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< Class>(m_MatMLTreeCtrl)) };
		 auto copy_element = remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<ParentSubClass>>(m_MatMLItemToCopy)); 
		if (element_observer && copy_element) {
			
				MatML_Base::PasteSeqContChild(copy_element,element_observer->ParentSubClass());
				MatML_GUI_Base::SetupSel< Class, Class_GUI>(m_MatMLTreeCtrl); 
		}

		//wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
		//MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
		//try {
		//	Class* const element = boost::any_cast<Class* const>(item->GetAnyMatMLDataPointer());
		//	if (element != 0) {
		//		Class* const copy_element = boost::any_cast<Class* const>(m_MatMLItemToCopy);
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

void ParentSubClass_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< ParentSubClass,
		Class,
		Class::ParentSubClass_sequence,
		ParentSubClass_GUI,
		&Class::ParentSubClass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void ParentSubClass_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< ParentSubClass,
		Class,
		Class::ParentSubClass_sequence,
		ParentSubClass_GUI,
		&Class::ParentSubClass
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
