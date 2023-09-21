#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Form_GUI.h"

using namespace bellshire::GUI;

Form_GUI_Base::Form_GUI_Base()
{

}

Form_GUI_Base::Form_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Form_GUI_Base::~Form_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Form MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Form_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* FormNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	FormNotebook->Hide();
	FormNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* FormPanel(CreateFormPanel(FormNotebook));

	MatMLInfo_GUI matMLInfo_GUI(FormNotebook,
		wxT("**************** Form *************************\n\nThis element declares the content model for Form, which contains a\ndescription of the form of the bulk material or component.\n\t\t\t\nIt also contains an element to describe the geometry of the the form and\nan element for any notes. For additional information, see the \ndocumentation for the Geometry element\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	FormNotebook->AddPage(FormPanel, wxT("MatML Data."), b_dflt);
	FormNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return FormNotebook;
}

wxWindow* Form_GUI_Base::CreateFormPanel(wxWindow* parent)
{
	wxScrolledWindow* FormPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	FormPanel->SetScrollRate(5, 5);
	FormPanel->SetMinSize(wxSize(400, 500));
	FormPanel->SetMaxSize(wxSize(-1, 100));

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(FormPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	FormPanel->SetSizer(bSizer1);
	FormPanel->Layout();
	bSizer1->Fit(FormPanel);

	return FormPanel;
}

void Form_GUI_Base::Update( const observer_ptr<Form> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Form_GUI_Base::GetTreeLabel(const observer_ptr<Form> element)
{
	wxString str;
	str << wxT("Form");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Form_GUI::Form_GUI() 
	: Form_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Form_GUI::Form_GUI(wxWindow* parent)
	: Form_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Form_GUI::~Form_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Form_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Form_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Form_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Form_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Form_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Form_GUI::OnInsertDescription(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Form, Description) }
void Form_GUI::OnInsertGeometry(wxCommandEvent& event) {
	//ON_PARENT_INSERT_CONT_CHILD(Form,Geometry)
	wxTreeItemId selItemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = NULL;
	if (selItemId.IsOk()) item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(selItemId));
	else return;
	try {

		 auto element= boost::any_cast<observer_ptr<Form> >(item->GetAnyMatMLDataPointer());
		if (element) {
			Form::Geometry_optional& cont(element->Geometry());
			if (element != 0) {

				if (cont.present()) cont = Default<::Geometry>();
				else {

					cont.set(Default<::Geometry>());

					bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(
						bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{ m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(selItemId), selItemId });
					Form_GUI::TraverseMatMLTree(element, func1);

					wxTreeItemId selNextItemId = m_MatMLTreeCtrl->GetNextSibling(selItemId);
					if (selNextItemId.IsOk()) {

						m_MatMLTreeCtrl->SelectItem(selNextItemId);
						m_MatMLTreeCtrl->Expand(selNextItemId);
					}
					if (selItemId.IsOk()) m_MatMLTreeCtrl->Delete(selItemId);
				}
				return;
			}
		}
	}
	catch (const boost::bad_any_cast&) { return; }

}
void Form_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Form, Notes) }

void Form_GUI::OnDeleteGeometry(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Form, Geometry)}
void Form_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Form, Notes)}

/// <summary>
/// Paste Discription on the Form Parent
/// Name Type is used instead of the Description as Description is a typedef of Name
/// </summary>
/// <param name="event"></param>
void Form_GUI::OnPasteDescription(wxCommandEvent& event) { 
	//ON_PARENT_PASTE_CHILD(Form, Description)
	  auto element= GetSelMatML<Form>(m_MatMLTreeCtrl);
	 if (element) {
		 auto copy_element = boost::any_cast<observer_ptr<Form::Description_type> >(m_MatMLItemToCopy);
		 MatML_Base::PasteChild(copy_element, element->Description());
		 SetupSel<Form, Form_GUI>(m_MatMLTreeCtrl);
		
	 }
}//Description

void Form_GUI::OnPasteGeometry(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Form, Geometry) }
void Form_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Form, Notes) }
