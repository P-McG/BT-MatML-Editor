#include "pch.h"
#include <wx/config.h>

#include "bellshire/Lib/utilities/BT_MATML_GET_ASSOCIATED_LIB_TYPE.H"
#include "bellshire/GUI/BT_MatML_BulkDetails_GUI.h"

using namespace bellshire::GUI;

BulkDetails_GUI_Base::BulkDetails_GUI_Base()
	:m_droptarget(nullptr)
{}

BulkDetails_GUI_Base::BulkDetails_GUI_Base(wxWindow* parent)
{

	//Only Get LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt) {
		//converts from a derived to a base class pointer for handling.
		m_lib_element = std::move(GetLib<bellshire::Lib::BulkDetails_lib>("BulkDetails_lib.xml"));
	}
	
	//Create GUI
	m_GUI = Create(parent,
		m_MatMLLibTreeCtrl,
		m_lib_element.get(),
		m_droptarget
	);
}
BulkDetails_GUI_Base::BulkDetails_GUI_Base(MatMLLibDropTarget* m_droptarget)
	: m_droptarget(m_droptarget)
{
}

BulkDetails_GUI_Base::~BulkDetails_GUI_Base() {

	// Save Lib data

	wxConfig config(wxT("BTMatML"));
	bool worked = false;

	//Only Save LibPanel if MatMLLibHidePriorSelection is NOT selected in preference
	bool b2_dflt(false);//default value
	config.Read(wxT("/General/MatMLLibHidePriorSelection"), &b2_dflt);
	if (!b2_dflt && m_lib_element)
		SetLib<bellshire::Lib::BulkDetails_lib>(/*m_lib,*/ m_lib_element, "BulkDetails_lib.xml");
	
	//Copy the Current MatMLLibHideSelection to MatMLLibHidePriorSelection now that we are done with it and set it up
	// for the next run.
	bool b_dflt(false);//temps
	if (config.Read(wxT("/General/MatMLLibHideSelection"), &b_dflt)) {
		worked = config.Write(wxT("/General/MatMLLibHidePriorSelection"), b_dflt);
		assert(worked);
	}

}


/// <summary>
/// Create the GUI for the BulkDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="BulkDetailsNotebook"></param>
/// <param name="BulkDetailsPanel"></param>
/// <returns>bool</returns>
wxNotebook* BulkDetails_GUI_Base::Create(wxWindow* parent,
	TreeCtrlSorted*& MatMLLibTreeCtrl,
	observer_ptr<xml_schema::element_type> lib_element,
	MatMLLibDropTarget* droptarget
)
{

	wxNotebook* BulkDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	BulkDetailsNotebook->Hide();
	BulkDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* BulkDetailsPanel{ CreateBulkDetailsPanel(BulkDetailsNotebook) };

	//MatML Info Panel
	//================

	MatMLInfo_GUI matMLInfo_GUI(BulkDetailsNotebook,
		wxT("************** BulkDetails *************************\nThis element declares the content model for BulkDetails, which\ncontains a description of the bulk material and is composed of the\nfollowing elements.\n\nName contains the material's name and has one optional attribute,\nauthority, for identifying an authoritative source of material\nnames. Name must occur once and only once within the BulkDetails\nelement.\n\nClass contains the material's class and may occur zero or more times\nwithin the BulkDetails element.\n\nSubclass contains the material's subclass(es) and may occur zero \nor more times within the BulkDetails element.\n\nSpecification contains the material's specification(s) and has one\noptional attribute, authority, for identifying an authoritative\nsource of material specifications. Specification may occur zero or\nmore times within the BulkDetails element.\n\nSource contains the name of the source of the material and may\noccur once or not at all within the BulkDetails element.\nForm contains the form of the material and may occur once or not at\nall within the BulkDetails element. It has an optional element \nGeometry, for describing the dimensions of the Component. For \nadditional information, see the documentation for the Form type.\n\nProcessingDetails contains a description of a processing step for\nthe material and may occur zero or more times within the BulkDetails\nelement. For additional information, see the documentation for the\nProcessingDetails element.\n\nCharacterization contains the characterization of the material,\nincluding the formula, chemical composition, phase composition, and\ndimensional details. Characterization may occur once or not at all\nwithin the BulkDetails element. For additional information, see the \ndocumentation for the Characterization element.\n\nPropertyData contains the property data for the material and may occur\nzero or more times within the BulkDetails element. For additional\ninformation, see the documentation for the PropertyData element.\n\nNotes contains any additional information concerning the bulk material\nand may occur once or not at all within the BulkDetails element.\t\t\t")
	);


	wxWindow* LibPanel = nullptr;
	bool b2_dflt(false);//default value

	if (lib_element) {
		//Only Create LibPanel if HideLibPanel is NOT selected in preference
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);

		if (!b2_dflt && lib_element)
			LibPanel = CreateLibPanel<
			BulkDetails, 
			BulkDetails_Base,
			bellshire::Lib::utilities::Get_Associated_Lib_type<BulkDetails>::MatML_lib_type
			>(BulkDetailsNotebook, MatMLLibTreeCtrl, lib_element, droptarget);

	}

	// Notebook assembly
	// =================

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	BulkDetailsNotebook->AddPage(BulkDetailsPanel, wxT("MatML Data."), b_dflt);
	BulkDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt && LibPanel)
		BulkDetailsNotebook->AddPage(LibPanel, wxT("MatML Lib."), false);

	return BulkDetailsNotebook;
}

wxWindow* BulkDetails_GUI_Base::CreateBulkDetailsPanel( wxWindow* parent)
{
	wxScrolledWindow* BulkDetailsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return BulkDetailsPanel;
}


void BulkDetails_GUI_Base::Update( const observer_ptr<BulkDetails> element)
{
	UpdateLib<BulkDetails, BulkDetails_Base, bellshire::Lib::BulkDetails_lib>(m_MatMLLibTreeCtrl, m_lib_element.get());

	ShowGUI(true);
}

wxString BulkDetails_GUI_Base::GetTreeLabel(const observer_ptr<BulkDetails> Element)
{
	wxString str;
	str << wxT("BulkDetails");

	return str;
}

MatMLLibDropTarget* BulkDetails_GUI_Base::GetDropTarget()
{
	return m_droptarget;
}
	
void BulkDetails_GUI_Base::SetConnect()
{
	//m_MatMLLibTreeCtrl->Connect(wxEVT_TREE_BEGIN_DRAG, wxTreeEventHandler(BulkDetails_GUI_Base::OnLeftDown), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActivated*/
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
	/*parent will destroy Ctrl or window */
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

TreeCtrlSorted* BulkDetails_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any BulkDetails_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
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
	ON_PARENT_DELETE_ITER_CONT_CHILD(BulkDetails, Subclass)
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
	ON_PARENT_PASTE_ITER_CONT_CHILD(BulkDetails, Subclass)
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

void BulkDetails_GUI::OnLeftDown(wxTreeEvent& event)
{
	DnDSource(event, m_MatMLLibTreeCtrl, m_GUI);
}




bool BulkDetails_GUI_Base::operator==(const BulkDetails_GUI_Base& other) const
{
	return m_droptarget == other.m_droptarget;
}
