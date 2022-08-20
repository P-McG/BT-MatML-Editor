#include <wx/config.h>

#include "BT_MatML_Form_GUI.h"

using namespace bellshire;

Form_GUI_Base::Form_GUI_Base()
	:m_GUI(nullptr)
{

}

Form_GUI_Base::Form_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Form_GUI_Base::~Form_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* FormPanel = new wxScrolledWindow(FormNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	FormPanel->SetScrollRate(5, 5);
	FormPanel->SetMinSize(wxSize(400, 500));
	FormPanel->SetMaxSize(wxSize(-1, 100));

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(FormPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	FormPanel->SetSizer(bSizer1);
	FormPanel->Layout();
	bSizer1->Fit(FormPanel);

	MatMLInfo_GUI matMLInfo_GUI(FormNotebook,
		wxT("**************** Form *************************\n\nThis element declares the content model for Form, which contains a\ndescription of the form of the bulk material or component.\n\t\t\t\nIt also contains an element to describe the geometry of the the form and\nan element for any notes. For additional information, see the \ndocumentation for the Geometry element\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	FormNotebook->AddPage(FormPanel, wxT("MatML Data."), b_dflt);
	FormNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return FormNotebook;
}

void Form_GUI_Base::Update( Form* element)
{
	//Nothing to update

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Form_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	Form& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Form");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Description
	if (Element.Description() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Description(), wxTreeItemId());

	//Setup Element Geometry
	{
		Form::Geometry_optional& cont(Element.Geometry());
		if (cont.present())
			Geometry_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element Notes
	{
		Form::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}
	return  CurrentId;
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
	/*parent will distroy Ctrl or window */
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

		Form* element = boost::any_cast<Form*>(item->GetAnyMatMLDataPointer());
		Form::Geometry_optional& cont(element->Geometry());
		if (element != 0) {

			if (cont.present()) cont = Default<::Geometry>();
			else {

				cont.set(Default<::Geometry>());
				Form_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(selItemId), *element, selItemId);
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
	catch (const boost::bad_any_cast&) { return; }

}
void Form_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Form, Notes) }

void Form_GUI::OnDeleteGeometry(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Form, Geometry)}
void Form_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Form, Notes)}

/// <summary>
/// Paste Discription on the Form Parent
/// Name Type is used instead of the Discription as Discription is a typedef of Name
/// </summary>
/// <param name="event"></param>
void Form_GUI::OnPasteDescription(wxCommandEvent& event) { 
	//ON_PARENT_PASTE_CHILD(Form, Description)
	 Form* element = GetSelMatML<Form>(m_MatMLTreeCtrl);
	 Name*  copy_element = boost::any_cast< Name* >(m_MatMLItemToCopy);
		if (element && copy_element) {
				PasteChild(copy_element, element->Description());
				SetupSel<Form, Form_GUI>(m_MatMLTreeCtrl);
		}
}//Description

void Form_GUI::OnPasteGeometry(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Form, Geometry) }
void Form_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Form, Notes) }
