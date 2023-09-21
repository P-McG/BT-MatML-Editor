#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Symbol_GUI.h"


using namespace bellshire::GUI;

Symbol_GUI_Base::Symbol_GUI_Base()
	:m_SymbolChoice(nullptr),
	m_SymbolSubScriptTextCtrl(nullptr)
{

}

Symbol_GUI_Base::Symbol_GUI_Base(wxWindow* parent)
	:m_SymbolChoice(nullptr)
{
	m_GUI = Create(parent, m_SymbolSubScriptTextCtrl, m_SymbolChoice);
}

Symbol_GUI_Base::~Symbol_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Symbol_GUI_Base::GetSymbolSubScriptTextCtrl()
{
	return m_SymbolSubScriptTextCtrl;
}

wxChoice* Symbol_GUI_Base::GetSymbolChoice()
{
	return m_SymbolChoice;
}


/// <summary>
/// Create the GUI for the Symbol MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="SymbolNotebook"></param>
/// <param name="SymbolPanel"></param>
/// <param name="SymbolSubScriptTextCtrl"></param>
/// <param name="SymbolChoice"></param>
/// <returns>bool</returns>
wxNotebook* Symbol_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& SymbolSubScriptTextCtrl, wxChoice*& SymbolChoice)
{

	wxNotebook* SymbolNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SymbolNotebook->Hide();
	SymbolNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* SymbolPanel(CreateSymbolPanel(SymbolNotebook,
		SymbolSubScriptTextCtrl,
		SymbolChoice
	));

	MatMLInfo_GUI matMLInfo_GUI(SymbolNotebook,
		wxT("*************** Symbol *************************\n\nSymbol contains the symbol for the chemical element, which is one\namong those enumerated by the ChemicalSymbol datatype.\nSymbol has one optional attribute, subscript, for indicating the \nsubscript (formula units) of the chemical element.\t"));

	bool b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SymbolNotebook->AddPage(SymbolPanel, wxT("MatML Data."), b_dflt);
	SymbolNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."),!b_dflt);

	return SymbolNotebook;
}

wxWindow* Symbol_GUI_Base::CreateSymbolPanel(wxWindow* parent,
	wxTextCtrl*& SymbolSubScriptTextCtrl,
	wxChoice*& SymbolChoice
)
{

	wxScrolledWindow* SymbolPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SymbolPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer251322 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer141 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer141->SetFlexibleDirection(wxBOTH);
	fgSizer141->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText91 = new wxStaticText(SymbolPanel, wxID_ANY, wxT("SubScript"), wxDefaultPosition, wxDefaultSize, 0);
	staticText91->Wrap(-1);
	fgSizer141->Add(staticText91, 0, wxALL, 5);

	SymbolSubScriptTextCtrl = new wxTextCtrl(SymbolPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer141->Add(SymbolSubScriptTextCtrl, 0, wxALL, 5);

	wxStaticText* staticText541 = new wxStaticText(SymbolPanel, wxID_ANY, wxT("Chemical Symbol Symbol"), wxDefaultPosition, wxDefaultSize, 0);
	staticText541->Wrap(-1);
	fgSizer141->Add(staticText541, 0, wxALL, 5);

	wxString SymbolChoiceChoices[] = { wxT("H"), wxT("He"), wxT("Li"), wxT("Be"), wxT("B"), wxT("C"), wxT("N"), wxT("O"), wxT("F"), wxT("Ne"), wxT("Na"), wxT("Mg"), wxT("Al"), wxT("Si"), wxT("P"), wxT("S"), wxT("Cl"), wxT("Ar"), wxT("K"), wxT("Ca"), wxT("Sc"), wxT("Ti"), wxT("V"), wxT("Cr"), wxT("Mn"), wxT("Fe"), wxT("Co"), wxT("Ni"), wxT("Cu"), wxT("Zn"), wxT("Ga"), wxT("Ge"), wxT("As"), wxT("Se"), wxT("Br"), wxT("Kr"), wxT("Rb"), wxT("Sr"), wxT("Y"), wxT("Zr"), wxT("Nb"), wxT("Mo"), wxT("Tc"), wxT("Ru"), wxT("Rh"), wxT("Pd"), wxT("Ag"), wxT("Cd"), wxT("In"), wxT("Sn"), wxT("Sb"), wxT("Te"), wxT("I"), wxT("Xe"), wxT("Cs"), wxT("Ba"), wxT("La"), wxT("Ce"), wxT("Pr"), wxT("Nd"), wxT("Pm"), wxT("Sm"), wxT("Eu"), wxT("Gd"), wxT("Tb"), wxT("Dy"), wxT("Ho"), wxT("Er"), wxT("Tm"), wxT("Yb"), wxT("Lu"), wxT("Hf"), wxT("Ta"), wxT("W"), wxT("Re"), wxT("Os"), wxT("Ir"), wxT("Pt"), wxT("Au"), wxT("Hg"), wxT("Tl"), wxT("Pb"), wxT("Bi"), wxT("Po"), wxT("At"), wxT("Rn"), wxT("Fr"), wxT("Ra"), wxT("Ac"), wxT("Th`"), wxT("Pa"), wxT("U"), wxT("Np"), wxT("Pu"), wxT("Am"), wxT("Cm"), wxT("Bk"), wxT("Cf"), wxT("Es"), wxT("Fm"), wxT("Md"), wxT("No"), wxT("Lr"), wxT("Rf"), wxT("Db"), wxT("Sg"), wxT("Bh"), wxT("Hs"), wxT("Mt"), wxT("Uun"), wxT("Uuu"), wxT("Uub"), wxT("Unq"), wxT("Uuh"), wxT("Uuo") };
	int SymbolChoiceNChoices = sizeof(SymbolChoiceChoices) / sizeof(wxString);
	SymbolChoice = new wxChoice(SymbolPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, SymbolChoiceNChoices, SymbolChoiceChoices, 0);
	SymbolChoice->SetSelection(0);
	fgSizer141->Add(SymbolChoice, 0, wxALL, 5);

	bSizer251322->Add(fgSizer141, 1, wxEXPAND, 5);

	SymbolPanel->SetSizer(bSizer251322);
	SymbolPanel->Layout();
	bSizer251322->Fit(SymbolPanel);

	return SymbolPanel;
}

void Symbol_GUI_Base::Update(const observer_ptr< Symbol> element)
{
	wxString str;

	if (element) {

		str << _std2wx(element->subscript());
		m_SymbolSubScriptTextCtrl->ChangeValue(str);

		str.clear();
		str << _std2wx(std::string(ChemicalElementSymbol::_xsd_ChemicalElementSymbol_literals_[int(*element)]));
		m_SymbolChoice->SetStringSelection(str);

		ShowGUI(true);
	}
}


wxString Symbol_GUI_Base::GetTreeLabel(const observer_ptr<Symbol> element)
{
	  wxString str;
	  str << wxT("Symbol");

	  return str;
}


void Symbol_GUI_Base::SetConnect()
{
	m_SymbolSubScriptTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Symbol_GUI_Base::OnSymbolSubScriptTextCtrl), NULL, this);
	m_SymbolSubScriptTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Symbol_GUI_Base::OnSymbolSubScriptTextCtrl), NULL, this);
	m_SymbolChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Symbol_GUI_Base::OnSymbolChoice), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Symbol_GUI::Symbol_GUI() : Symbol_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Symbol_GUI::Symbol_GUI(wxWindow* parent)
	: Symbol_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Symbol_GUI::~Symbol_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Symbol_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Symbol_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Symbol_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Symbol_GUI::OnSymbolSubScriptTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Symbol* const element = boost::any_cast<Symbol* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			wxString str(m_SymbolSubScriptTextCtrl->GetValue());
			Symbol::subscript_type NewData((const char*)str.mb_str(wxConvUTF8));
			element->subscript() = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

};

void Symbol_GUI::OnSymbolChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Symbol* element = boost::any_cast<Symbol* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			wxString str(m_SymbolChoice->GetStringSelection());
			Symbol NewData(ChemicalElementSymbol((const char*)(str.mb_str(wxConvUTF8))));

			//The following is required because the NewData has a default value for the subscript that overwrites the users value.
			wxString str1(m_SymbolSubScriptTextCtrl->GetValue());
			NewData.subscript((const char*)str1.mb_str(wxConvUTF8));

			(*element) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

};