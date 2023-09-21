#include "pch.h"
#include <wx/config.h>
#include "bellshire/Lib/BT_MatML_MatML_Lib.h"
#include "bellshire/GUI/BT_MatML_Unit_GUI.h"
#include "bellshire/BT_MatML_Default.h"

using namespace bellshire::GUI;

Unit_GUI_Base::Unit_GUI_Base()
	:m_UnitNameTextCtrl(nullptr),
	m_UnitCurrencyCheckBox(nullptr),
	m_UnitCurrencyChoice(nullptr), 
	m_UnitPowerTextCtrl(nullptr),
	m_UnitDescriptionTextCtrl(nullptr)
{

}

Unit_GUI_Base::Unit_GUI_Base(wxWindow* parent)
	:m_UnitNameTextCtrl(nullptr),
	m_UnitCurrencyCheckBox(nullptr),
	m_UnitCurrencyChoice(nullptr),
	m_UnitPowerTextCtrl(nullptr),
	m_UnitDescriptionTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_UnitNameTextCtrl, m_UnitCurrencyCheckBox, m_UnitCurrencyChoice, m_UnitPowerTextCtrl, m_UnitDescriptionTextCtrl);
}

Unit_GUI_Base::~Unit_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Unit_GUI_Base::GetUnitNameTextCtrl()
{
	return m_UnitNameTextCtrl;
}

wxCheckBox* Unit_GUI_Base::GetUnitCurrencyCheckBox()
{
	return m_UnitCurrencyCheckBox;
}

wxChoice* Unit_GUI_Base::GetUnitCurrencyChoice()
{
	return m_UnitCurrencyChoice;
}

wxTextCtrl* Unit_GUI_Base::GetUnitPowerTextCtrl()
{
	return m_UnitPowerTextCtrl;
}

wxTextCtrl* Unit_GUI_Base::GetUnitDescriptionTextCtrl()
{
	return m_UnitDescriptionTextCtrl;
}


/// <summary>
/// Create the GUI for the Unit MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="UnitNotebook"></param>
/// <param name="UnitPanel"></param>
/// <param name="UnitNameTextCtrl"></param>
/// <param name="UnitCurrencyCheckBox"></param>
/// <param name="UnitCurrencyChoice"></param>
/// <param name="UnitPowerTextCtrl"></param>
/// <param name="UnitDescriptionTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Unit_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& UnitNameTextCtrl, 
	wxCheckBox*& UnitCurrencyCheckBox, 
	wxChoice*& UnitCurrencyChoice, 
	wxTextCtrl*& UnitPowerTextCtrl, 
	wxTextCtrl*& UnitDescriptionTextCtrl
)
{
	wxNotebook* UnitNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	UnitNotebook->Hide();

	wxWindow* UnitPanel(CreateUnitPanel(UnitNotebook, UnitNameTextCtrl, UnitCurrencyCheckBox, UnitCurrencyChoice, UnitPowerTextCtrl, UnitDescriptionTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(UnitNotebook,
		wxT("*********** Unit *************************\n\nThis element declares the content model for Unit, which contains a\nunit and has two optional attributes.\n\nThe first attribute, power, is used to indicate the exponent for Unit.\n\nThe second attribute, description, is used to describe Unit.\n\nNote -\tMultiple Unit elements are multiplied together to form units.\n\tDivision is specified by setting the power attribute of Unit\n\tequal to \"-1.\" For additional information, see the\n\tdocumentation for the Units element.\n\nUnit has a choice between two elements [MUST]:\n\t\t\t\nName is the Name of the unit, and can occur only once in the Unit \nelement.\n\t\t\t\nCurrency is the CurrencyCode for the unit, if it is a unit expressing \ncost in an ISO 4217 recognised currency.")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	UnitNotebook->AddPage(UnitPanel, wxT("MatML Data"), b_dflt);
	UnitNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return UnitNotebook;
}

wxWindow* Unit_GUI_Base::CreateUnitPanel(wxWindow* parent,
	wxTextCtrl*& UnitNameTextCtrl,
	wxCheckBox*& UnitCurrencyCheckBox,
	wxChoice*& UnitCurrencyChoice,
	wxTextCtrl*& UnitPowerTextCtrl,
	wxTextCtrl*& UnitDescriptionTextCtrl
)
{

	wxScrolledWindow* UnitPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	UnitPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer25 = new wxFlexGridSizer(3, 1, 0, 0);
	fgSizer25->AddGrowableCol(0);
	fgSizer25->SetFlexibleDirection(wxBOTH);
	fgSizer25->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxFlexGridSizer* fgSizer144 = new wxFlexGridSizer(3, 2, 0, 0);
	fgSizer144->AddGrowableCol(1);
	fgSizer144->AddGrowableRow(0);
	fgSizer144->AddGrowableRow(2);
	fgSizer144->SetFlexibleDirection(wxBOTH);
	fgSizer144->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText119 = new wxStaticText(UnitPanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText119->Wrap(-1);
	fgSizer144->Add(staticText119, 0, wxALL, 5);

	UnitNameTextCtrl = new wxTextCtrl(UnitPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	UnitNameTextCtrl->SetToolTip(wxT("eg. kilogram, metre, second"));

	fgSizer144->Add(UnitNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText205 = new wxStaticText(UnitPanel, wxID_ANY, wxT("- OR -"), wxDefaultPosition, wxDefaultSize, 0);
	staticText205->Wrap(-1);
	fgSizer144->Add(staticText205, 0, wxALL, 0);

	fgSizer144->Add(0, 0, 1, wxEXPAND, 5);

	UnitCurrencyCheckBox = new wxCheckBox(UnitPanel, wxID_ANY, wxT("Currency"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer144->Add(UnitCurrencyCheckBox, 0, wxALL, 5);

	wxString UnitCurrencyChoiceChoices[] = { wxT("CAD"), wxT("USD") };
	int UnitCurrencyChoiceNChoices = sizeof(UnitCurrencyChoiceChoices) / sizeof(wxString);
	UnitCurrencyChoice = new wxChoice(UnitPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, UnitCurrencyChoiceNChoices, UnitCurrencyChoiceChoices, 0);
	UnitCurrencyChoice->SetSelection(0);
	UnitCurrencyChoice->Enable(false);

	fgSizer144->Add(UnitCurrencyChoice, 0, wxALL, 5);

	fgSizer25->Add(fgSizer144, 1, wxEXPAND, 5);

	wxStaticLine* staticline20 = new wxStaticLine(UnitPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	staticline20->SetMaxSize(wxSize(-1, 5));

	fgSizer25->Add(staticline20, 1, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer145 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer145->AddGrowableCol(1);
	fgSizer145->AddGrowableRow(0);
	fgSizer145->AddGrowableRow(1);
	fgSizer145->SetFlexibleDirection(wxBOTH);
	fgSizer145->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText33 = new wxStaticText(UnitPanel, wxID_ANY, wxT("Power"), wxDefaultPosition, wxDefaultSize, 0);
	staticText33->Wrap(-1);
	fgSizer145->Add(staticText33, 0, wxALL, 5);

	UnitPowerTextCtrl = new wxTextCtrl(UnitPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	UnitPowerTextCtrl->SetToolTip(wxT("eg. +1,+1,-2"));

	fgSizer145->Add(UnitPowerTextCtrl, 0, wxALL, 5);

	wxStaticText* staticText34 = new wxStaticText(UnitPanel, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0);
	staticText34->Wrap(-1);
	fgSizer145->Add(staticText34, 0, wxALL, 5);

	UnitDescriptionTextCtrl = new wxTextCtrl(UnitPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP | wxTE_PROCESS_ENTER | wxTE_RICH);
	UnitDescriptionTextCtrl->SetToolTip(wxT("eg. mass, length, time"));

	fgSizer145->Add(UnitDescriptionTextCtrl, 1, wxALIGN_TOP | wxALL | wxEXPAND, 5);

	fgSizer25->Add(fgSizer145, 1, wxEXPAND, 5);

	UnitPanel->SetSizer(fgSizer25);
	UnitPanel->Layout();
	fgSizer25->Fit(UnitPanel);

	return UnitPanel;
}

void Unit_GUI_Base::Update(const observer_ptr<Unit> element)
{
	if (element) {

		wxString str;

		if (element->Currency().present()) {
			m_UnitNameTextCtrl->Enable(false);
			m_UnitCurrencyChoice->Enable(true);
			m_UnitCurrencyCheckBox->SetValue(true);

			str.clear();
			const Unit::Currency_optional& cont(element->Currency());
			if (cont.present()) str << _std2wx((*cont));
			m_UnitCurrencyChoice->SetStringSelection(str);
		}
		else {
			m_UnitNameTextCtrl->Enable(true);
			m_UnitCurrencyChoice->Enable(false);
			m_UnitCurrencyCheckBox->SetValue(false);

			str.clear();
			const Unit::Name_optional& cont(element->Name());
			if (cont.present()) str << _std2wx((cont.get()));
			m_UnitNameTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Unit::power_optional& cont(element->power());
			if (cont.present()) str << (double)cont.get();
			m_UnitPowerTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Unit::description_optional& cont(element->description());
			if (cont.present()) str << _std2wx(cont.get());
			m_UnitDescriptionTextCtrl->ChangeValue(str);
		}

		ShowGUI(true);
	}
}

wxString Unit_GUI_Base::GetTreeLabel(const observer_ptr<Unit> element)
{
	wxString str;
	str << wxT("Unit");

	if (element) {

		if (element->Name().present())
			str << "-" << _std2wx(element->Name().get());

		if (element->Currency().present())
			str << "-" << _std2wx(element->Currency().get());
	}

	return str;
}


void Unit_GUI_Base::SetConnect()
{
	//m_UnitNotebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( Unit_GUI_Base::OnUnitNotebook ), NULL, this );
	m_UnitNameTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Unit_GUI_Base::OnUnitNameTextCtrl), NULL, this);
	m_UnitNameTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Unit_GUI_Base::OnUnitNameTextCtrl), NULL, this);
	m_UnitCurrencyCheckBox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Unit_GUI_Base::OnUnitCurrencyCheckBox), NULL, this);
	m_UnitCurrencyChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Unit_GUI_Base::OnUnitCurrencyChoice), NULL, this);
	m_UnitPowerTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Unit_GUI_Base::OnUnitPowerTextCtrl), NULL, this);
	m_UnitPowerTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Unit_GUI_Base::OnUnitPowerTextCtrl), NULL, this);
	m_UnitDescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Unit_GUI_Base::OnUnitDescriptionTextCtrl), NULL, this);
	m_UnitDescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Unit_GUI_Base::OnUnitDescriptionTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Unit_GUI::Unit_GUI() : Unit_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Unit_GUI::Unit_GUI(wxWindow* parent)
	: Unit_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Unit_GUI::~Unit_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Unit_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Unit_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Unit_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Unit_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Unit_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Unit_GUI::OnUnitNameTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Unit* const Element = boost::any_cast<Unit* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Unit::Name_optional& cont(Element->Name());
			wxString str(m_UnitNameTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			Unit::Name_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Unit_GUI::OnUnitCurrencyCheckBox(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Unit* const Element = boost::any_cast<Unit* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			if (m_UnitCurrencyCheckBox->GetValue() == true) {
				m_UnitNameTextCtrl->Enable(false);
				Element->Name().reset();
				Element->Currency().set(Default<::CurrencyCode>());
				m_UnitCurrencyChoice->Enable(true);
			}
			else {
				m_UnitNameTextCtrl->Enable(true);
				Element->Currency().reset();
				Element->Name().set(Default<::Name>());
				m_UnitCurrencyChoice->Enable(false);

			}
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

}


void Unit_GUI::OnUnitCurrencyChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Unit* const Element = boost::any_cast<Unit* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_UnitCurrencyChoice->GetStringSelection());
			Unit::Currency_type NewData((const char*)str.mb_str(wxConvUTF8));
			Element->Currency().set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Unit_GUI::OnUnitPowerTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Unit* const Element = boost::any_cast<Unit* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Unit::power_optional& cont(Element->power());
			wxString str(m_UnitPowerTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			double NumData; str.ToDouble(&NumData);
			Unit::power_type NewData(NumData);
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Unit_GUI::OnUnitDescriptionTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Unit* const Element = boost::any_cast<Unit* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Unit::description_optional& cont(Element->description());
			wxString str(m_UnitDescriptionTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			Unit::description_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}




void Unit_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Unit, Name) }
void Unit_GUI::OnInsertCurrency(wxCommandEvent& event) { 
	// Note: Macro below does not work because Currency default is CurrencyCode with a different name.
	//ON_PARENT_INSERT_CONT_CHILD(Unit, Currency) 

	wxTreeItemId selItemId = m_MatMLTreeCtrl->GetSelection(); 
	MatMLTreeItemData *item=NULL; 
	if(selItemId.IsOk()) item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(selItemId));	
	else return; 
	try{																				 
		auto element_observer = boost::any_cast<observer_ptr<Unit>>(item->GetAnyMatMLDataPointer());
		Unit::Currency_optional& cont(element_observer->Currency());
		if (element_observer){   
			if(cont.present()) cont=Default<::CurrencyCode>();
			else {   
				cont.set(Default<::CurrencyCode>());

				bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data{ 
					m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetItemParent(selItemId),selItemId 
				};
				Unit_GUI::TraverseMatMLTree(element_observer,
					bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI(data)
				);

                wxTreeItemId selNextItemId = m_MatMLTreeCtrl->GetNextSibling(selItemId); 
				if(selNextItemId.IsOk()) { 
				    m_MatMLTreeCtrl->SelectItem(selNextItemId); 
				    m_MatMLTreeCtrl->Expand(selNextItemId); 
				} 
				if(selItemId.IsOk()) m_MatMLTreeCtrl->Delete(selItemId);   
			}  
			return;							 
		}									  
	}											
	catch(const boost::bad_any_cast &){return;}

}

void Unit_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(Unit, Name)}

void Unit_GUI::OnPasteName(wxCommandEvent& event) {ON_PARENT_PASTE_CONT_CHILD(Unit, Name) }

void Unit_GUI::OnPasteCurrencyCode(wxCommandEvent& event) { 
	//ON_PARENT_PASTE_CONT_CHILD(Unit, CurrencyCode) 
	//#define ON_PARENT_PASTE_CONT_CHILD(parent,child) 
	auto element_observer = MatML_GUI_Base::GetSelMatML< Unit>(m_MatMLTreeCtrl);
	auto copy_element = boost::any_cast<observer_ptr<CurrencyCode>>(m_MatMLItemToCopy);
	if (element_observer && copy_element) {
		MatML_Base::PasteContChild(copy_element, element_observer->Currency());
		MatML_GUI_Base::SetupSel<Unit, Unit_GUI>(m_MatMLTreeCtrl);
	}

}

void Unit_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Unit,
		Units,
		Units::Unit_sequence,
		Unit_GUI,
		&Units::Unit
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Unit_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Unit,
		Units,
		Units::Unit_sequence,
		Unit_GUI,
		&Units::Unit
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}



bool Unit_GUI_Base::operator==(const Unit_GUI_Base& other) const
{
	return m_lib_element == other.m_lib_element && m_UnitNameTextCtrl == other.m_UnitNameTextCtrl && m_UnitCurrencyCheckBox == other.m_UnitCurrencyCheckBox && m_UnitCurrencyChoice == other.m_UnitCurrencyChoice && m_UnitPowerTextCtrl == other.m_UnitPowerTextCtrl && m_UnitDescriptionTextCtrl == other.m_UnitDescriptionTextCtrl;
}


//Unit_GUI_Base::Unit_GUI_Base(const std::shared_ptr<Lib::Unit_lib>& lib_element, wxTextCtrl* UnitNameTextCtrl, wxCheckBox* UnitCurrencyCheckBox, wxChoice* UnitCurrencyChoice, wxTextCtrl* UnitPowerTextCtrl, wxTextCtrl* UnitDescriptionTextCtrl)
//	: m_lib_element(lib_element), m_UnitNameTextCtrl(UnitNameTextCtrl), m_UnitCurrencyCheckBox(UnitCurrencyCheckBox), m_UnitCurrencyChoice(UnitCurrencyChoice), m_UnitPowerTextCtrl(UnitPowerTextCtrl), m_UnitDescriptionTextCtrl(UnitDescriptionTextCtrl)
//{
//}
