#include <wx/config.h>
#include "BT_MatML_PhaseComposition_GUI.h"

using namespace bellshire;

PhaseComposition_GUI_Base::PhaseComposition_GUI_Base()
	:m_GUI(nullptr)
{

}

PhaseComposition_GUI_Base::PhaseComposition_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

PhaseComposition_GUI_Base::~PhaseComposition_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the PhaseComposition MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="PhaseCompositionNotebook"></param>
/// <param name="PhaseCompositionPanel"></param>
/// <returns>bool</returns>
wxNotebook* PhaseComposition_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* PhaseCompositionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	PhaseCompositionNotebook->Hide();
	PhaseCompositionNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* PhaseCompositionPanel = new wxScrolledWindow(PhaseCompositionNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	PhaseCompositionPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(PhaseCompositionPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	PhaseCompositionPanel->SetSizer(bSizer1);
	PhaseCompositionPanel->Layout();
	bSizer1->Fit(PhaseCompositionPanel);

	MatMLInfo_GUI matMLInfo_GUI(PhaseCompositionNotebook,
		wxT("********** PhaseComposition *************************\n\t\t\t\nThis element declares the content model for PhaseComposition, which\ncontains a description of a phase that comprises the bulk material or\ncomponent and is composed of the following elements.\n\nName contains the name of the phase and has one optional attribute,\nauthority, for identifying an authoritative source of phase names. Name\nmust occur once and only once within the PhaseComposition element.\n\nConcentration contains the concentration of the phase and may occur\nonce or not at all within the PhaseComposition element. For additional\ninformation, see the documentation for the Concentration element.\n\nPropertyData contains property data for the phase and may occur zero\nor more times within the PhaseComposition element. For additional\ninformation, see the documentation for the PropertyData element.\n\nNotes contains any additional information concerning the phase and may\noccur once or not at all within the PhaseComposition element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	PhaseCompositionNotebook->AddPage(PhaseCompositionPanel, wxT("MatML Data."), b_dflt);
	PhaseCompositionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return PhaseCompositionNotebook;
}

void PhaseComposition_GUI_Base::Update( PhaseComposition* element)
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
wxTreeItemId PhaseComposition_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId,
	PhaseComposition& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("PhaseComposition");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Concentration
	{
		PhaseComposition::Concentration_optional& cont(Element.Concentration());
		if (cont.present())
			Concentration_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element PropertyData
	{
		PhaseComposition::PropertyData_sequence& cont(Element.PropertyData());
		PhaseComposition::PropertyData_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				PropertyData_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		PhaseComposition::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
PhaseComposition_GUI::PhaseComposition_GUI() 
	: PhaseComposition_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
PhaseComposition_GUI::PhaseComposition_GUI(wxWindow* parent)
	: PhaseComposition_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
PhaseComposition_GUI::~PhaseComposition_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PhaseComposition_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PhaseComposition_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void PhaseComposition_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void PhaseComposition_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(PhaseComposition, Name) }
void PhaseComposition_GUI::OnInsertConcentration(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PhaseComposition, Concentration) }
void PhaseComposition_GUI::OnInsertPropertyData(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(PhaseComposition, PropertyData) }
void PhaseComposition_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PhaseComposition, Notes) }

void PhaseComposition_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(PhaseComposition, Name)}
void PhaseComposition_GUI::OnDeleteConcentration(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PhaseComposition, Concentration)}
void PhaseComposition_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PhaseComposition, Notes)}
void PhaseComposition_GUI::OnDeletePropertyData(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(PhaseComposition, PropertyData)}

void PhaseComposition_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(PhaseComposition, Name) }
void PhaseComposition_GUI::OnPasteConcentration(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PhaseComposition, Concentration) }
void PhaseComposition_GUI::OnPastePropertyData(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(PhaseComposition, PropertyData) }
void PhaseComposition_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PhaseComposition, Notes) }
