#include <wx/config.h>

#include "BT_MatML_ChemicalComposition_GUI.h"

using namespace bellshire;

ChemicalComposition_GUI_Base::ChemicalComposition_GUI_Base()
	:m_GUI(nullptr)
{

}

ChemicalComposition_GUI_Base::ChemicalComposition_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

ChemicalComposition_GUI_Base::~ChemicalComposition_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the ChemicalComposition MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ChemicalCompositionNotebook"></param>
/// <param name="ChemicalCompositionPanel"></param>
/// <returns>bool</returns>
wxNotebook* ChemicalComposition_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* ChemicalCompositionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ChemicalCompositionNotebook->Hide();
	ChemicalCompositionNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ChemicalCompositionPanel = new wxScrolledWindow(ChemicalCompositionNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ChemicalCompositionPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer2513 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(ChemicalCompositionPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2513->Add(staticText4, 0, wxALL, 5);

	ChemicalCompositionPanel->SetSizer(bSizer2513);
	ChemicalCompositionPanel->Layout();
	bSizer2513->Fit(ChemicalCompositionPanel);

	MatMLInfo_GUI matMLInfo_GUI(ChemicalCompositionNotebook,
		wxT("************* ChemicalComposition *************************\n\nThis element declares the content model for ChemicalComposition, which\ncontains a detailed description of the compounds and elements that\ncomprise the bulk material or component. ChemicalComposition must\ncontain at least one Compound element or Element element but may\ncontain as many of each element as needed.\n\nCompound contains a description of a compound. For additional\ninformation, see the documentation for the Compound element.\n\nElement contains a description of an element. For additional information,\nsee the documentation for the Element element.\n\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ChemicalCompositionNotebook->AddPage(ChemicalCompositionPanel, wxT("MatML Data."), b_dflt);
	ChemicalCompositionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ChemicalCompositionNotebook;
}

void ChemicalComposition_GUI_Base::Update( ChemicalComposition* element)
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
wxTreeItemId ChemicalComposition_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	ChemicalComposition& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("ChemicalComposition");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attributes
	//--NONE--

	//Setup Element Compound
	{
		 ChemicalComposition::Compound_sequence& cont(Element.Compound());
		ChemicalComposition::Compound_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Compound_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Element
	{
		ChemicalComposition::Element_sequence& cont(Element.Element());
		ChemicalComposition::Element_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Element_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	return CurrentId;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
ChemicalComposition_GUI::ChemicalComposition_GUI() 
	: ChemicalComposition_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ChemicalComposition_GUI::ChemicalComposition_GUI(wxWindow* parent)
	: ChemicalComposition_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ChemicalComposition_GUI::~ChemicalComposition_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalComposition_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalComposition_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ChemicalComposition_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ChemicalComposition_GUI::OnInsertCompound(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnInsertElement(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ChemicalComposition, Element) }

void ChemicalComposition_GUI::OnDeleteCompound(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnDeleteElement(wxCommandEvent& event) {	ON_PARENT_DELETE_ITER_CONT_CHILD(ChemicalComposition, Element) }

void ChemicalComposition_GUI::OnPasteCompound(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ChemicalComposition, Compound) }
void ChemicalComposition_GUI::OnPasteElement(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ChemicalComposition, Element) }