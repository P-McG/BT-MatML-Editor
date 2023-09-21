#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Geometry_GUI.h"

using namespace bellshire::GUI;

Geometry_GUI_Base::Geometry_GUI_Base()
{

}

Geometry_GUI_Base::Geometry_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Geometry_GUI_Base::~Geometry_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Geometry MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Geometry_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* GeometryNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	GeometryNotebook->Hide();
	GeometryNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* GeometryPanel(CreateGeometryPanel(GeometryNotebook));

	MatMLInfo_GUI matMLInfo_GUI(GeometryNotebook,
		wxT("***************** Geometry *************************\n\nThis element declares the content model for Geometry, which contains a\ndescription of the geometry of the bulk material, component or specimen\nand is composed of the following elements. \n\nShape is a string describing the\nshape of the bulk material or component and must occur once and only\nonce within the Geometry element. \n\nDimensions is a string describing the\ndimensions of the bulk material or component and may occur once or not\nat all within the Geometry element. \n\nOrientation is a string describing the\norientation of the bulk material or component and may occur once or not\nat all within the Geometry element. \n\nNotes contains any additional \ninformation concerning the geometry and may occur once or not at all \nwithin the Geometry element. \n")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GeometryNotebook->AddPage(GeometryPanel, wxT("MatML Data"), b_dflt);
	GeometryNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GeometryNotebook;
}

wxWindow* Geometry_GUI_Base::CreateGeometryPanel(wxWindow* parent)
{

	wxPanel* GeometryPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	GeometryPanel->SetMinSize(wxSize(400, 500));

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(GeometryPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	GeometryPanel->SetSizer(bSizer1);
	GeometryPanel->Layout();
	bSizer1->Fit(GeometryPanel);

	return GeometryPanel;
}

void Geometry_GUI_Base::Update( const observer_ptr<Geometry> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Geometry_GUI_Base::GetTreeLabel(const observer_ptr<Geometry> element)
{
	wxString str;
	str << wxT("Geometry");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Geometry_GUI::Geometry_GUI() 
	: Geometry_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Geometry_GUI::Geometry_GUI(wxWindow* parent)
	: Geometry_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Geometry_GUI::~Geometry_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Geometry_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Geometry_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Geometry_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Geometry_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Geometry_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Geometry_GUI::OnInsertShape(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Geometry, Shape) }
void Geometry_GUI::OnInsertDimensions(wxCommandEvent& event) {
	ON_PARENT_INSERT_CONT_CHILD(Geometry,Dimensions)

	//	ON_PARENT_INSERT_CONT_CHILD(Geometry,Dimensions)
	//wxTreeItemId selItemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = NULL;
	//if (selItemId.IsOk()) item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(selItemId));
	//else return;
	//try {

	//	Geometry* const element = boost::any_cast<Geometry* const>(item->GetAnyMatMLDataPointer());
	//	Geometry::Dimensions_optional& cont(element->Dimensions());
	//	if (element != 0) {

	//		if (cont.present()) cont = Default<::Dimensions>();
	//		else {

	//			cont.set(Default<::Dimensions>());

	//			Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(selItemId), selItemId });
	//			Geometry_GUI::TraverseMatMLTree(element, func1);

	//			wxTreeItemId selNextItemId = m_MatMLTreeCtrl->GetNextSibling(selItemId);
	//			if (selNextItemId.IsOk()) {

	//				m_MatMLTreeCtrl->SelectItem(selNextItemId);
	//				m_MatMLTreeCtrl->Expand(selNextItemId);
	//			}
	//			if (selItemId.IsOk()) m_MatMLTreeCtrl->Delete(selItemId);
	//		}
	//		return;
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }

}
void Geometry_GUI::OnInsertOrientation(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Geometry, Orientation) }
void Geometry_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Geometry, Notes) }

void Geometry_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Geometry, Notes)}

void Geometry_GUI::OnPasteShape(wxCommandEvent& event) {
	ON_PARENT_PASTE_CHILD(Geometry, Shape)
}
void Geometry_GUI::OnPasteDimensions(wxCommandEvent& event) {
	ON_PARENT_PASTE_CONT_CHILD(Geometry,Dimensions)
	
	//ON_PARENT_PASTE_CONT_CHILD(Geometry,Dimensions)}
	//wxTreeItemId selItemId = m_MatMLTreeCtrl->GetSelection();
	//MatMLTreeItemData* item = NULL;
	//if (selItemId.IsOk()) item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(selItemId));
	//else return;
	//try {

	//	Geometry* const element = boost::any_cast<Geometry* const>(item->GetAnyMatMLDataPointer());
	//	Geometry::Dimensions_optional& cont(element->Dimensions());
	//	if (element != 0) {

	//		Dimensions* const copy_element = boost::any_cast<Dimensions* const>(m_MatMLItemToCopy);
	//		if (copy_element != 0) {

	//			if (cont.present()) cont = *copy_element;
	//			else {

	//				cont.set(*copy_element);

	//				Geometry_GUI::TraverseMatMLTree(element,
	//					Functor_SetupCtrl_MatMLTree_GUI(Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(selItemId), selItemId })
	//				);

	//				wxTreeItemId selNextItemId = m_MatMLTreeCtrl->GetNextSibling(selItemId);
	//				if (selNextItemId.IsOk()) {

	//					m_MatMLTreeCtrl->SelectItem(selNextItemId);
	//					m_MatMLTreeCtrl->Expand(selNextItemId);
	//				}
	//				if (selItemId.IsOk()) m_MatMLTreeCtrl->Delete(selItemId);
	//			}
	//		}
	//		return;
	//	}
	//}
	//catch (const boost::bad_any_cast&) { return; }
}
void Geometry_GUI::OnPasteOrientation(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Geometry, Orientation) }
void Geometry_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Geometry, Notes) }
