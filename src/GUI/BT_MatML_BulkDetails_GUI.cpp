#include <wx/config.h>

#include "BT_MatML_BulkDetails_GUI.h"

using namespace bellshire;

BulkDetails_GUI_Base::BulkDetails_GUI_Base()
	:m_GUI(nullptr)
{

}

BulkDetails_GUI_Base::BulkDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

BulkDetails_GUI_Base::~BulkDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the BulkDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="BulkDetailsNotebook"></param>
/// <param name="BulkDetailsPanel"></param>
/// <returns>bool</returns>
wxNotebook* BulkDetails_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* BulkDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	BulkDetailsNotebook->Hide();
	BulkDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* BulkDetailsPanel = new wxScrolledWindow(BulkDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	BulkDetailsPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer2->AddGrowableCol(0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(BulkDetailsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer2->Add(staticText4, 0, wxALL, 5);

	BulkDetailsPanel->SetSizer(fgSizer2);
	BulkDetailsPanel->Layout();
	fgSizer2->Fit(BulkDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(BulkDetailsNotebook,
		wxT("************** BulkDetails *************************\nThis element declares the content model for BulkDetails, which\ncontains a description of the bulk material and is composed of the\nfollowing elements.\n\nName contains the material's name and has one optional attribute,\nauthority, for identifying an authoritative source of material\nnames. Name must occur once and only once within the BulkDetails\nelement.\n\nClass contains the material's class and may occur zero or more times\nwithin the BulkDetails element.\n\nSubclass contains the material's subclass(es) and may occur zero \nor more times within the BulkDetails element.\n\nSpecification contains the material's specification(s) and has one\noptional attribute, authority, for identifying an authoritative\nsource of material specifications. Specification may occur zero or\nmore times within the BulkDetails element.\n\nSource contains the name of the source of the material and may\noccur once or not at all within the BulkDetails element.\nForm contains the form of the material and may occur once or not at\nall within the BulkDetails element. It has an optional element \nGeometry, for describing the dimensions of the Component. For \nadditional information, see the documentation for the Form type.\n\nProcessingDetails contains a description of a processing step for\nthe material and may occur zero or more times within the BulkDetails\nelement. For additional information, see the documentation for the\nProcessingDetails element.\n\nCharacterization contains the characterization of the material,\nincluding the formula, chemical composition, phase composition, and\ndimensional details. Characterization may occur once or not at all\nwithin the BulkDetails element. For additional information, see the \ndocumentation for the Characterization element.\n\nPropertyData contains the property data for the material and may occur\nzero or more times within the BulkDetails element. For additional\ninformation, see the documentation for the PropertyData element.\n\nNotes contains any additional information concerning the bulk material\nand may occur once or not at all within the BulkDetails element.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	BulkDetailsNotebook->AddPage(BulkDetailsPanel, wxT("MatML Data."), b_dflt);
	BulkDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return BulkDetailsNotebook;
}


void BulkDetails_GUI_Base::Update( BulkDetails* element)
{
	//Nothing to update

	Show(true);
}

void BulkDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	BulkDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("BulkDetails");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attributes
	//--NONE--

	//Setup Element Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Element Class
	{
		BulkDetails::Class_sequence& cont(Element.Class());
		BulkDetails::Class_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Class_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Subclass
	{
		 BulkDetails::Subclass_sequence& cont(Element.Subclass());
		BulkDetails::Subclass_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Subclass_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element SetupSpecification
	{
		 BulkDetails::Specification_sequence& cont(Element.Specification());
		BulkDetails::Specification_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Specification_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Source
	{
		 BulkDetails::Source_optional& cont(Element.Source());
		if (cont.present())
			Source_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}


	//Setup Element Form
	{
		 BulkDetails::Form_optional& cont(Element.Form());
		if (cont.present())
			Form_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element ProcessDetails
	{
		 BulkDetails::ProcessingDetails_sequence& cont(Element.ProcessingDetails());
		BulkDetails::ProcessingDetails_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ProcessingDetails_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Characterization
	{
		 BulkDetails::Characterization_optional& cont(Element.Characterization());
		if (cont.present())
			Characterization_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element PropertyData
	{
		 BulkDetails::PropertyData_sequence& cont(Element.PropertyData());
		BulkDetails::PropertyData_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				PropertyData_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Notes
	{
		 BulkDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}
}


/// <summary>
/// Constructor for the derived class
/// </summary>
BulkDetails_GUI::BulkDetails_GUI() 
	: BulkDetails_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
BulkDetails_GUI::BulkDetails_GUI(wxWindow* parent)
	: BulkDetails_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
BulkDetails_GUI::~BulkDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void BulkDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void BulkDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void BulkDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void  BulkDetails_GUI::OnInsertName(wxCommandEvent& event) 
{ 
	ON_PARENT_INSERT_CHILD(BulkDetails, Name)
}

void  BulkDetails_GUI::OnInsertClass(wxCommandEvent& event)
{ 
	ON_PARENT_INSERT_ITER_CONT_CHILD(BulkDetails, Class)
}

void  BulkDetails_GUI::OnInsertSubclass(wxCommandEvent& event)
  {
	ON_PARENT_INSERT_ITER_CONT_CHILD(BulkDetails, Subclass)
}

void  BulkDetails_GUI::OnInsertSpecification(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_ITER_CONT_CHILD(BulkDetails, Specification)
}

void  BulkDetails_GUI::OnInsertSource(wxCommandEvent& event)
{ 
	ON_PARENT_INSERT_CONT_CHILD(BulkDetails, Source)
}

void  BulkDetails_GUI::OnInsertForm(wxCommandEvent& event) 
{ 
	ON_PARENT_INSERT_CONT_CHILD(BulkDetails, Form)
}

void  BulkDetails_GUI::OnInsertProcessingDetails(wxCommandEvent& event) 
{
	ON_PARENT_INSERT_ITER_CONT_CHILD(BulkDetails, ProcessingDetails)
}

void  BulkDetails_GUI::OnInsertCharacterization(wxCommandEvent& event) 
{ 
	ON_PARENT_INSERT_CONT_CHILD(BulkDetails, Characterization)
}

void  BulkDetails_GUI::OnInsertPropertyData(wxCommandEvent& event)
{ 
	ON_PARENT_INSERT_ITER_CONT_CHILD(BulkDetails, PropertyData)
}

void  BulkDetails_GUI::OnInsertNotes(wxCommandEvent& event)
{ 
	ON_PARENT_INSERT_CONT_CHILD(BulkDetails, Notes)
}

void BulkDetails_GUI::OnDeleteName(wxCommandEvent& event)
{
	ON_PARENT_DELETE_CHILD(BulkDetails, Name)
}

void BulkDetails_GUI::OnDeleteClass(wxCommandEvent& event)
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(BulkDetails, Class)
}

void BulkDetails_GUI::OnDeleteSubclass(wxCommandEvent& event)
{
	ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(BulkDetails, Subclass)
}

void BulkDetails_GUI::OnDeleteCharacterization(wxCommandEvent& event)
{ 
	ON_PARENT_DELETE_CONT_CHILD(BulkDetails, Characterization)
}

void BulkDetails_GUI::OnDeleteForm(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_CONT_CHILD(BulkDetails, Form)
}

void BulkDetails_GUI::OnDeleteNotes(wxCommandEvent& event)
{
	ON_PARENT_DELETE_CONT_CHILD(BulkDetails, Notes)
}

void BulkDetails_GUI::OnDeleteProcessingDetails(wxCommandEvent& event)
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(BulkDetails, ProcessingDetails)
}

void BulkDetails_GUI::OnDeletePropertyData(wxCommandEvent& event)
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(BulkDetails, PropertyData)
}

void BulkDetails_GUI::OnDeleteSpecification(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_ITER_CONT_CHILD(BulkDetails, Specification)
}

void BulkDetails_GUI::OnDeleteSource(wxCommandEvent& event) 
{
	ON_PARENT_DELETE_CONT_CHILD(BulkDetails, Source)
}

void BulkDetails_GUI::OnPasteName(wxCommandEvent& event) 
{
    ON_PARENT_PASTE_CHILD(BulkDetails, Name)
}

void BulkDetails_GUI::OnPasteClass(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails, Class)
}

void BulkDetails_GUI::OnPasteSubclass(wxCommandEvent& event)
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails,Subclass)
}

void BulkDetails_GUI::OnPasteSpecification(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails, Specification)
}

void BulkDetails_GUI::OnPasteSource(wxCommandEvent& event)
{
	ON_PARENT_PASTE_CONT_CHILD(BulkDetails, Source)

}

void BulkDetails_GUI::OnPasteForm(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_CONT_CHILD(BulkDetails, Form)
}

void BulkDetails_GUI::OnPasteProcessingDetails(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails, ProcessingDetails)
}
void BulkDetails_GUI::OnPasteCharacterization(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_CONT_CHILD(BulkDetails, Characterization)
}

void BulkDetails_GUI::OnPastePropertyData(wxCommandEvent& event) 
{
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails, PropertyData)
}

void BulkDetails_GUI::OnPasteNotes(wxCommandEvent& event)
{
	ON_PARENT_PASTE_CONT_CHILD(BulkDetails, Notes)
}
