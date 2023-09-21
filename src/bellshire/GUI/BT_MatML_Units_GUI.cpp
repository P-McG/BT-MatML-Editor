#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Units_GUI.h"
#include "bellshire/GUI/BT_MatML_Unit_GUI.h"
#include "bellshire/BT_MatML_Default.h"
#include "bellshire/GUI/BT_MatML_MatMLDropSource.h"
#include "bellshire/Lib/utilities/BT_MatML_Get_Associated_Lib_type.h"

#include <wx/dnd.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/dataobj.h>


using namespace bellshire::GUI;

Units_GUI_Base::Units_GUI_Base()
	:m_UnitsSystemTextCtrl(nullptr),
	m_UnitsFactorTextCtrl(nullptr),
	m_UnitsNameTextCtrl(nullptr),
	m_UnitsDescriptionTextCtrl(nullptr)
{

}

Units_GUI_Base::Units_GUI_Base(wxWindow* parent)
	: m_UnitsSystemTextCtrl(nullptr),
	m_UnitsFactorTextCtrl(nullptr),
	m_UnitsNameTextCtrl(nullptr),
	m_UnitsDescriptionTextCtrl(nullptr)
{
	//Only Get LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt) {
		m_lib_element=std::move(GetLib<bellshire::Lib::Units_lib>("Units_lib.xml"));
	}

	m_GUI = Create(parent,
		m_UnitsSystemTextCtrl,
		m_UnitsFactorTextCtrl,
		m_UnitsNameTextCtrl,
		m_UnitsDescriptionTextCtrl,
		m_MatMLLibTreeCtrl,
		dynamic_cast<Lib::Units_lib*>(m_lib_element.get()),
		m_droptarget
	);
}

Units_GUI_Base::~Units_GUI_Base() {

	wxConfig config(wxT("BTMatML"));
	bool worked = false;
	
	//Only Save LibPanel if MatMLLibHidePriorSelection is NOT selected in preference
	bool b2_dflt(false);//default value
	config.Read(wxT("/General/MatMLLibHidePriorSelection"), &b2_dflt);
	if (!b2_dflt)
		SetLib<bellshire::Lib::Units_lib>(/*m_lib,*/ m_lib_element, "Units_lib.xml");

	//Copy the Current MatMLLibHideSelection to MatMLLibHidePriorSelection now that we are done with it and set it up
	// for the next run.
	bool b_dflt(false);//temps
	if (config.Read(wxT("/General/MatMLLibHideSelection"), &b_dflt)) {
		worked = config.Write(wxT("/General/MatMLLibHidePriorSelection"), b_dflt);
		assert(worked);
	}

	/*parent will destroy Ctrl or window */	
	//delete m_lib_element;
}

wxTextCtrl* Units_GUI_Base::GetUnitsSystemTextCtrl()
{
	return m_UnitsSystemTextCtrl;
}

wxTextCtrl* Units_GUI_Base::GetUnitsFactorTextCtrl()
{
	return m_UnitsFactorTextCtrl;
}

wxTextCtrl* Units_GUI_Base::GetUnitsNameTextCtrl()
{
	return m_UnitsNameTextCtrl;
}

wxTextCtrl* Units_GUI_Base::GetUnitsDescriptionTextCtrl()
{
	return m_UnitsDescriptionTextCtrl;
}

MatMLLibDropTarget* Units_GUI_Base::GetDropTarget()
{
	return m_droptarget;
}


/// <summary>
/// Create the GUI for the Units MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="UnitsNotebook"></param>
/// <param name="UnitsPanel"></param>
/// <param name="SIradioBtn"></param>
/// <param name="CGSradioBtn"></param>
/// <param name="OnImpradioBtn"></param>
/// <param name="OnUSradioBtn"></param>
/// <param name="OnOtherradioBtn"></param>
/// <param name="UnitsSystemTextCtrl"></param>
/// <param name="UnitsFactorTextCtrl"></param>
/// <param name="UnitsNameTextCtrl"></param>
/// <param name="AutoInsertBaseUnitsButton"></param>
/// <param name="UnitsDescriptionTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Units_GUI_Base::Create(wxWindow* parent,
	wxTextCtrl*& UnitsSystemTextCtrl, 
	wxTextCtrl*& UnitsFactorTextCtrl, 
	wxTextCtrl*& UnitsNameTextCtrl, 
	wxTextCtrl*& UnitsDescriptionTextCtrl,
	TreeCtrlSorted*& MatMLLibTreeCtrl,
	observer_ptr<Lib::Units_lib> lib_element,
	MatMLLibDropTarget* droptarget
)
{
	wxNotebook* UnitsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	UnitsNotebook->Hide();

	wxWindow* UnitsPanel(CreateUnitsPanel(UnitsNotebook, UnitsSystemTextCtrl, UnitsFactorTextCtrl, UnitsNameTextCtrl, UnitsDescriptionTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(UnitsNotebook,
		wxT("*********** Units *************************\n\nThis element declares the content model for Units, which contains units\nand has four optional attributes.\n\nThe first attribute, system, is used to indicate the units system, such as\n\"SI.\"\n\nThe second attribute, factor, is used to indicate a constant multiplier in\nfloating point format.\n\nThe third attribute, name, is used to indicate the name of the units\n\nThe fourth attribute, description, is used to describe the units.\n\nUnits is composed of the following elements.\n\nUnit contains a unit and *MUST* occur one or more times within the Units\nelement. For additional information, see the documentation for the Unit\nelement.\n\nBase Unit\n\nUnit conversins are done using \nGnu Units [ http://www.gnu.org/software/units/ ]\nso it is recomended the unit entered here\nbe in the form supported by that system.\n\nIf \"Auto Insert Base Units\" function was uses \nthe units inserted in \"Unit\" will be one of the\nthe primitive base units defined in Gnu Units \ndefinition files. The default setting will likely\nprovide a SI base unit.\n\nFactor\n\n\n\n\n")
	);

	wxWindow* LibPanel = nullptr ;

	//Only Create LibPanel if HideLibPanel is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt)
		LibPanel=CreateLibPanel< 
		Units,
		Units_Base,
		bellshire::Lib::utilities::Get_Associated_Lib_type<Units>::MatML_lib_type
		>(UnitsNotebook, MatMLLibTreeCtrl, lib_element, droptarget);

	// Notebook assembly
	// =================

	bool b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	UnitsNotebook->AddPage(UnitsPanel, wxT("MatML Data."), b_dflt);
	UnitsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);
	if(!b2_dflt) UnitsNotebook->AddPage(LibPanel, wxT("MatML Lib."), false);

	return UnitsNotebook;
}

wxWindow* Units_GUI_Base::CreateUnitsPanel(wxWindow* parent,
	wxTextCtrl*& UnitsSystemTextCtrl,
	wxTextCtrl*& UnitsFactorTextCtrl,
	wxTextCtrl*& UnitsNameTextCtrl,
	wxTextCtrl*& UnitsDescriptionTextCtrl
)
{
	wxScrolledWindow* UnitsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	UnitsPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer26 = new wxFlexGridSizer(4, 2, 0, 0);
	fgSizer26->AddGrowableCol(1);
	fgSizer26->AddGrowableRow(3);
	fgSizer26->SetFlexibleDirection(wxBOTH);
	fgSizer26->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText206 = new wxStaticText(UnitsPanel, wxID_ANY, wxT("System"), wxDefaultPosition, wxDefaultSize, 0);
	staticText206->Wrap(-1);
	fgSizer26->Add(staticText206, 0, wxALL, 5);

	UnitsSystemTextCtrl = new wxTextCtrl(UnitsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer26->Add(UnitsSystemTextCtrl, 1, wxALL | wxEXPAND, 5);
	UnitsSystemTextCtrl->SetToolTip(wxT("SI, CGS, IMP,..."));

	wxStaticText* staticText36 = new wxStaticText(UnitsPanel, wxID_ANY, wxT("Factor"), wxDefaultPosition, wxDefaultSize, 0);
	staticText36->Wrap(-1);
	fgSizer26->Add(staticText36, 0, wxALL, 5);

	UnitsFactorTextCtrl = new wxTextCtrl(UnitsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	UnitsFactorTextCtrl->SetToolTip(wxT("eg. 1.0e-3"));

	fgSizer26->Add(UnitsFactorTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText37 = new wxStaticText(UnitsPanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText37->Wrap(-1);
	fgSizer26->Add(staticText37, 0, wxALL, 5);

	wxFlexGridSizer* fgSizer1412 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1412->AddGrowableCol(0);
	fgSizer1412->SetFlexibleDirection(wxBOTH);
	fgSizer1412->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	UnitsNameTextCtrl = new wxTextCtrl(UnitsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	UnitsNameTextCtrl->SetToolTip(wxT("eg. kilonewton"));

	fgSizer1412->Add(UnitsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	fgSizer26->Add(fgSizer1412, 1, wxEXPAND, 5);

	wxStaticText* staticText38 = new wxStaticText(UnitsPanel, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0);
	staticText38->Wrap(-1);
	fgSizer26->Add(staticText38, 0, wxALL, 5);

	UnitsDescriptionTextCtrl = new wxTextCtrl(UnitsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	UnitsDescriptionTextCtrl->SetToolTip(wxT("eg. Force"));

	fgSizer26->Add(UnitsDescriptionTextCtrl, 0, wxALL | wxEXPAND, 5);

	UnitsPanel->SetSizer(fgSizer26);
	UnitsPanel->Layout();
	fgSizer26->Fit(UnitsPanel);

	return UnitsPanel;
}

void Units_GUI_Base::Update(const observer_ptr< Units> element)
{
	wxString str;

	if (element) {

		str.clear();
		{
			const Units::system_optional& cont(element->system());
			if (cont.present()) str << _std2wx((cont.get()));
			m_UnitsSystemTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Units::factor_optional& cont(element->factor());
			if (cont.present()) str << (float)(*cont);
			m_UnitsFactorTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Units::name_optional& cont(element->name());
			if (cont.present()) str << _std2wx((*cont));
			m_UnitsNameTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Units::description_optional& cont(element->description());
			if (cont.present()) str << _std2wx((*cont));
			m_UnitsDescriptionTextCtrl->ChangeValue(str);
		}

		//Only Update LibPanel if HideLibPanel is NOT selected in preference
		bool b2_dflt(false);//default value
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
		if (!b2_dflt)
			UpdateLib<Units, Units_GUI, bellshire::Lib::Units_lib>(m_MatMLLibTreeCtrl, m_lib_element.get());

		ShowGUI(true);
	}
}

wxString Units_GUI_Base::GetTreeLabel(const observer_ptr<Units> element)
{
	wxString str;
	str << wxT("Units");

	if (element) {
		if (element->name().present()) {
			str << "-" << _std2wx(element->name().get());
		}
	}

	return str;
}


void Units_GUI_Base::SetConnect()
{
	m_GUI->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(Units_GUI_Base::OnUnitsNotebook), NULL, this);
	m_UnitsSystemTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Units_GUI_Base::OnUnitsSystemTextCtrl), NULL, this);
	m_UnitsSystemTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Units_GUI_Base::OnUnitsSystemTextCtrl), NULL, this);
	m_UnitsFactorTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Units_GUI_Base::OnUnitsFactorTextCtrl), NULL, this);
	m_UnitsFactorTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Units_GUI_Base::OnUnitsFactorTextCtrl), NULL, this);
	m_UnitsNameTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Units_GUI_Base::OnUnitsNameTextCtrl), NULL, this);
	m_UnitsNameTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Units_GUI_Base::OnUnitsNameTextCtrl), NULL, this);
	m_UnitsDescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Units_GUI_Base::OnUnitsDescriptionTextCtrl), NULL, this);
	m_UnitsDescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Units_GUI_Base::OnUnitsDescriptionTextCtrl), NULL, this);

	//Only Connect to LibPanel if HideLibPanelSelection is NOT selected in preference
	bool b2_dflt(false);//default value
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLLibHideSelection"), &b2_dflt);
	if (!b2_dflt)
		MatML_GUI_Base::SetLibConnect();
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Units_GUI::Units_GUI() 
	: Units_GUI_Base(), 
m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Units_GUI::Units_GUI(wxWindow* parent)
	: Units_GUI_Base(parent), 
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Units_GUI::~Units_GUI() {
	/*parent will destroy Ctrl or window */

}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Units_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Units_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Units_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Units_GUI::OnUnitsSystemTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Units* const Element = boost::any_cast<Units* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Units::system_optional& cont(Element->system());
			wxString str(m_UnitsSystemTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			Units::system_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}


void Units_GUI::OnUnitsFactorTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Units* const Element = boost::any_cast<Units* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Units::factor_optional& cont(Element->factor());
			wxString str(m_UnitsFactorTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			double NumData; str.ToDouble(&NumData);
			Units::factor_type NewData(NumData);
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Units_GUI::OnUnitsNameTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Units* const Element = boost::any_cast<Units* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Units::name_optional& cont(Element->name());
			wxString str(m_UnitsNameTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			Units::name_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);

			//gnu_units gu;
			//std::string youhave(*cont);
			//m_AutoInsertBaseUnitsButton->Enable(gu.check(youhave.c_str()));

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Units_GUI::OnUnitsDescriptionTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Units* const Element = boost::any_cast<Units* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Units::description_optional& cont(Element->description());
			wxString str(m_UnitsDescriptionTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			Units::description_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Units_GUI::OnInsertUnit(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Units, Unit) }

void Units_GUI::OnDeleteUnit(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Units, Unit)}

void Units_GUI::OnPasteUnit(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Units, Unit) }

//void Units_GUI::OnLeftDown(wxTreeEvent& event)
//{
//	DnDSource(event, m_MatMLLibTreeCtrl, m_GUI);
//}


bool Units_GUI_Base::operator==(const Units_GUI_Base& other) const
{
	return m_UnitsSystemTextCtrl == other.m_UnitsSystemTextCtrl && m_UnitsFactorTextCtrl == other.m_UnitsFactorTextCtrl && m_UnitsNameTextCtrl == other.m_UnitsNameTextCtrl && m_UnitsDescriptionTextCtrl == other.m_UnitsDescriptionTextCtrl && m_droptarget == other.m_droptarget;
}
