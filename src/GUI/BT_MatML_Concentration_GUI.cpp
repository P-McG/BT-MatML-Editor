#include <wx/config.h>
#include "BT_MatML_Concentration_GUI.h"

using namespace bellshire;

Concentration_GUI_Base::Concentration_GUI_Base()
	:m_GUI(nullptr)
{

}

Concentration_GUI_Base::Concentration_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Concentration_GUI_Base::~Concentration_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* ConcentrationPanel = new wxScrolledWindow(ConcentrationNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ConcentrationPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer25132 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(ConcentrationPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25132->Add(staticText4, 0, wxALL, 5);

	ConcentrationPanel->SetSizer(bSizer25132);
	ConcentrationPanel->Layout();
	bSizer25132->Fit(ConcentrationPanel);

	MatMLInfo_GUI matMLInfo_GUI(ConcentrationNotebook,
		wxT("*************** Concentration *************************\n\nThis element declares the content model for Concentration and is\ncomposed of the following elements.\n\nValue contains the value of the concentration and has one required\nattribute, format, for indicating the format of the value. Value must \noccur once and only once within the Concentration element.\n\nUnits contains the units for the value of the concentration and must\noccur once and only once within the Concentration element. For \nadditional information, see the documentation for the Units element.\n\nQualifier contains any qualifier pertinent to the value of the \nconcentration (e.g. \"min,\" \"max,\" etc.) and may occur once or not at all within the Concentration element.\n\nUncertainty contains the measurement uncertainty(ies) of the data in\nData and may occur zero or more times within the Concentration \nelement. For additional information, see the documentation for the\nUncertainty type.\n\t\nNotes contains any additional information concerning the concentration\nand may occur once or not at all within the Concentration element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ConcentrationNotebook->AddPage(ConcentrationPanel, wxT("MatML Data."), b_dflt);
	ConcentrationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ConcentrationNotebook;
}

void Concentration_GUI_Base::Update( Concentration* element)
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
wxTreeItemId Concentration_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Concentration& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Concentration");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Value
	if (Element.Value() != "")
		Value_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Value(), wxTreeItemId());

	//Setup Element Units
	Units_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Units(), wxTreeItemId());

	//Setup Element Qualifier
	{
		Concentration::Qualifier_sequence& cont(Element.Qualifier());
		Concentration::Qualifier_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Qualifier_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Uncertainty
	{
		Concentration::Uncertainty_sequence& cont(Element.Uncertainty());
		Concentration::Uncertainty_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Uncertainty_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Notes
	{
		Concentration::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}
	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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

