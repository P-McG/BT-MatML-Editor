#include <wx/config.h>

#include "BT_MatML_ChemicalElementSymbol_GUI.h"

using namespace bellshire;

ChemicalElementSymbol_GUI_Base::ChemicalElementSymbol_GUI_Base()
	:m_GUI(nullptr), m_ChemicalElementSymbolChoice(nullptr)
{

}

ChemicalElementSymbol_GUI_Base::ChemicalElementSymbol_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_ChemicalElementSymbolChoice(nullptr)
{
	m_GUI = Create(parent, m_ChemicalElementSymbolChoice);
}

ChemicalElementSymbol_GUI_Base::~ChemicalElementSymbol_GUI_Base() {
	/*parent will distroy Ctrl or window */
}



/// <summary>
/// Create the GUI for the ChemicalElementSymbol MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ChemicalElementSymbolNotebook"></param>
/// <param name="ChemicalElementSymbolPanel"></param>
/// <param name="ChemicalElementSymbolChoice"></param>
/// <returns>bool</returns>
wxNotebook* ChemicalElementSymbol_GUI_Base::Create(wxWindow* parent, wxChoice*& ChemicalElementSymbolChoice)
{
	wxNotebook* ChemicalElementSymbolNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ChemicalElementSymbolNotebook->Hide();
	ChemicalElementSymbolNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ChemicalElementSymbolPanel = new wxScrolledWindow(ChemicalElementSymbolNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ChemicalElementSymbolPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer17 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer36 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer36->SetFlexibleDirection(wxBOTH);
	fgSizer36->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText54 = new wxStaticText(ChemicalElementSymbolPanel, wxID_ANY, wxT("Chemical Element Symbol"), wxDefaultPosition, wxDefaultSize, 0);
	staticText54->Wrap(-1);
	fgSizer36->Add(staticText54, 0, wxALL, 5);

	wxString ChemicalElementSymbolChoiceChoices[] = { wxT("H"), wxT("He"), wxT("Li"), wxT("Be"), wxT("B"), wxT("C"), wxT("N"), wxT("O"), wxT("F"), wxT("Ne"), wxT("Na"), wxT("Mg"), wxT("Al"), wxT("Si"), wxT("P"), wxT("S"), wxT("Cl"), wxT("Ar"), wxT("K"), wxT("Ca"), wxT("Sc"), wxT("Ti"), wxT("V"), wxT("Cr"), wxT("Mn"), wxT("Fe"), wxT("Co"), wxT("Ni"), wxT("Cu"), wxT("Zn"), wxT("Ga"), wxT("Ge"), wxT("As"), wxT("Se"), wxT("Br"), wxT("Kr"), wxT("Rb"), wxT("Sr"), wxT("Y"), wxT("Zr"), wxT("Nb"), wxT("Mo"), wxT("Tc"), wxT("Ru"), wxT("Rh"), wxT("Pd"), wxT("Ag"), wxT("Cd"), wxT("In"), wxT("Sn"), wxT("Sb"), wxT("Te"), wxT("I"), wxT("Xe"), wxT("Cs"), wxT("Ba"), wxT("La"), wxT("Ce"), wxT("Pr"), wxT("Nd"), wxT("Pm"), wxT("Sm"), wxT("Eu"), wxT("Gd"), wxT("Tb"), wxT("Dy"), wxT("Ho"), wxT("Er"), wxT("Tm"), wxT("Yb"), wxT("Lu"), wxT("Hf"), wxT("Ta"), wxT("W"), wxT("Re"), wxT("Os"), wxT("Ir"), wxT("Pt"), wxT("Au"), wxT("Hg"), wxT("Tl"), wxT("Pb"), wxT("Bi"), wxT("Po"), wxT("At"), wxT("Rn"), wxT("Fr"), wxT("Ra"), wxT("Ac"), wxT("Th`"), wxT("Pa"), wxT("U"), wxT("Np"), wxT("Pu"), wxT("Am"), wxT("Cm"), wxT("Bk"), wxT("Cf"), wxT("Es"), wxT("Fm"), wxT("Md"), wxT("No"), wxT("Lr"), wxT("Rf"), wxT("Db"), wxT("Sg"), wxT("Bh"), wxT("Hs"), wxT("Mt"), wxT("Uun"), wxT("Uuu"), wxT("Uub"), wxT("Unq"), wxT("Uuh"), wxT("Uuo") };
	int ChemicalElementSymbolChoiceNChoices = sizeof(ChemicalElementSymbolChoiceChoices) / sizeof(wxString);
	ChemicalElementSymbolChoice = new wxChoice(ChemicalElementSymbolPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ChemicalElementSymbolChoiceNChoices, ChemicalElementSymbolChoiceChoices, 0);
	ChemicalElementSymbolChoice->SetSelection(0);
	fgSizer36->Add(ChemicalElementSymbolChoice, 0, wxALL, 5);

	bSizer17->Add(fgSizer36, 1, wxEXPAND, 5);

	ChemicalElementSymbolPanel->SetSizer(bSizer17);
	ChemicalElementSymbolPanel->Layout();
	bSizer17->Fit(ChemicalElementSymbolPanel);

	MatMLInfo_GUI matMLInfo_GUI(ChemicalElementSymbolNotebook,
		wxT("********** ChemicalElementSymbol *************************\n\nThis datatype enumerates the valid strings representing chemical\nelements, which may be used in the Symbol element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ChemicalElementSymbolNotebook->AddPage(ChemicalElementSymbolPanel, wxT("MatML Data."), b_dflt);
	ChemicalElementSymbolNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ChemicalElementSymbolNotebook;
}

void ChemicalElementSymbol_GUI_Base::Update( ChemicalElementSymbol* element)
{
		wxString str;
		int i = *element;
		str<< wxString(ChemicalElementSymbol::_xsd_ChemicalElementSymbol_literals_[i]);
		m_ChemicalElementSymbolChoice->SetStringSelection(str);
	
	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId ChemicalElementSymbol_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	ChemicalElementSymbol& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("ChemicalElementSymbol");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}

void ChemicalElementSymbol_GUI_Base::SetConnect()
{
	m_ChemicalElementSymbolChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(ChemicalElementSymbol_GUI_Base::OnChemicalElementSymbol), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
ChemicalElementSymbol_GUI::ChemicalElementSymbol_GUI() 
	: ChemicalElementSymbol_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ChemicalElementSymbol_GUI::ChemicalElementSymbol_GUI(wxWindow* parent)
	: ChemicalElementSymbol_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ChemicalElementSymbol_GUI::~ChemicalElementSymbol_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalElementSymbol_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ChemicalElementSymbol_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void ChemicalElementSymbol_GUI::OnChemicalElementSymbol(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		ChemicalElementSymbol* Element = boost::any_cast<ChemicalElementSymbol* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_ChemicalElementSymbolChoice->GetStringSelection());
			ChemicalElementSymbol NewData((const char*)str.mb_str(wxConvUTF8));
			*Element = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }


	// TODO: Implement OnChemicalElementSymbol
}