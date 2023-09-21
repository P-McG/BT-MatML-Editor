#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Concentration_GUI.h"

using namespace bellshire::GUI;

Concentration_GUI_Base::Concentration_GUI_Base()
{

}

Concentration_GUI_Base::Concentration_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Concentration_GUI_Base::~Concentration_GUI_Base() {
	/*parent will destroy Ctrl or window */
}



/// <summary>
/// Create the GUI for the Concentration MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Concentration_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* ConcentrationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ConcentrationNotebook->Hide();
	ConcentrationNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ConcentrationPanel(CreateConcentrationPanel(ConcentrationNotebook));

	MatMLInfo_GUI matMLInfo_GUI(ConcentrationNotebook,
		wxT("*************** Concentration *************************\n\nThis element declares the content model for Concentration and is\ncomposed of the following elements.\n\nValue contains the value of the concentration and has one required\nattribute, format, for indicating the format of the value. Value must \noccur once and only once within the Concentration element.\n\nUnits contains the units for the value of the concentration and must\noccur once and only once within the Concentration element. For \nadditional information, see the documentation for the Units element.\n\nQualifier contains any qualifier pertinent to the value of the \nconcentration (e.g. \"min,\" \"max,\" etc.) and may occur once or not at all within the Concentration element.\n\nUncertainty contains the measurement uncertainty(ies) of the data in\nData and may occur zero or more times within the Concentration \nelement. For additional information, see the documentation for the\nUncertainty type.\n\t\nNotes contains any additional information concerning the concentration\nand may occur once or not at all within the Concentration element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ConcentrationNotebook->AddPage(ConcentrationPanel, wxT("MatML Data."), b_dflt);
	ConcentrationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ConcentrationNotebook;
}

wxWindow* Concentration_GUI_Base::CreateConcentrationPanel(wxWindow* parent)
{
	wxScrolledWindow* ConcentrationPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ConcentrationPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer25132 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(ConcentrationPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25132->Add(staticText4, 0, wxALL, 5);

	ConcentrationPanel->SetSizer(bSizer25132);
	ConcentrationPanel->Layout();
	bSizer25132->Fit(ConcentrationPanel);

	return ConcentrationPanel;
}

void Concentration_GUI_Base::Update( const observer_ptr<Concentration> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Concentration_GUI_Base::GetTreeLabel(const observer_ptr<Concentration> element)
{
	wxString str;
	str << wxT("Concentration");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Concentration_GUI::Concentration_GUI() 
	: Concentration_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Concentration_GUI::Concentration_GUI(wxWindow* parent)
	: Concentration_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Concentration_GUI::~Concentration_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Concentration_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Concentration_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Concentration_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Concentration_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Concentration_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Concentration_GUI::OnInsertValue(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Concentration, Value) }
void Concentration_GUI::OnInsertUnits(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Concentration, Units) }
void Concentration_GUI::OnInsertQualifier(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Concentration, Qualifier) }
void Concentration_GUI::OnInsertUncertainty(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Concentration, Uncertainty) }
void Concentration_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Concentration, Notes) }

void Concentration_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Concentration, Notes)}
void Concentration_GUI::OnDeleteQualifier(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Concentration, Qualifier)}
void Concentration_GUI::OnDeleteUncertainty(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Concentration, Uncertainty)}
void Concentration_GUI::OnDeleteUnits(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(Concentration, Units)}
void Concentration_GUI::OnDeleteValue(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(Concentration, Value)}

void Concentration_GUI::OnPasteValue(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(Concentration, Value) }
void Concentration_GUI::OnPasteUnits(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(Concentration, Units) }
void Concentration_GUI::OnPasteQualifier(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Concentration, Qualifier) }
void Concentration_GUI::OnPasteUncertainty(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Concentration, Uncertainty) }
void Concentration_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Concentration, Notes) }

