#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Data1_GUI.h"


using namespace bellshire::GUI;

Data1_GUI_Base::Data1_GUI_Base()
	:m_Data1TextCtrl(nullptr),
	m_FormatChoice(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{

}

Data1_GUI_Base::Data1_GUI_Base(wxWindow* parent)
	:m_Data1TextCtrl(nullptr),
	m_FormatChoice(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{
	m_GUI = Create(parent,
		m_Data1TextCtrl,
		m_FormatChoice,
		m_ValidationButton,
		m_ValidationNewLineRemovalCheckBox
	);
}

Data1_GUI_Base::~Data1_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Data1_GUI_Base::GetData1TextCtrl()
{
	return m_Data1TextCtrl;
}

wxChoice* Data1_GUI_Base::GetFormatChoice()
{
	return m_FormatChoice;
}

wxButton* Data1_GUI_Base::GetValidationButton()
{
	return m_ValidationButton;
}

wxCheckBox* Data1_GUI_Base::GetValidationNewLineRemovalCheckBox()
{
	return m_ValidationNewLineRemovalCheckBox;
}


/// <summary>
/// Create the GUI for the ::Data MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="DataNotebook"></param>
/// <param name="DataPanel"></param>
/// <param name="bpButton1"></param>
/// <param name="bpButton2"></param>
/// <param name="DataTextCtrl"></param>
/// <param name="FormatChoice"></param>
/// <param name="DataUnitsMultiButton"></param>
/// <param name="DataYouHaveTextCtrl"></param>
/// <param name="DataYouWantMultTextCtrl"></param>
/// <param name="DataYouWantTextCtrl"></param>
/// <param name="DataUnitsMultiTextCtrl"></param>
/// <param name="DataUnitsTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Data1_GUI_Base::Create(wxWindow* parent,
	wxTextCtrl*& DataTextCtrl, 
	wxChoice*& FormatChoice,
	wxButton*& ValidationButton, 
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{

	wxNotebook* DataNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	DataNotebook->Hide();
	DataNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DataPanel(CreateDataPanel(DataNotebook,
		DataTextCtrl,
		FormatChoice,
		ValidationButton,
		ValidationNewLineRemovalCheckBox
	));

	MatMLInfo_GUI matMLInfo_GUI(DataNotebook,
		wxT("*********** Data1 *************************\n\nData contains the property data and has one required attribute,\nformat, for indicating the format of the data. Data must occur once \nand only once within the  element.\n\nNote - Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be comma delimited and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataNotebook->AddPage(DataPanel, wxT("MatML Data"), b_dflt);
	DataNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataNotebook;
}

wxWindow* Data1_GUI_Base::CreateDataPanel(wxWindow* parent,
	wxTextCtrl*& DataTextCtrl,
	wxChoice*& FormatChoice,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{
		wxScrolledWindow* DataPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DataPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer6911 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1711 = new wxFlexGridSizer(5, 2, 0, 0);
	fgSizer1711->AddGrowableCol(1);
	fgSizer1711->AddGrowableRow(0);
	fgSizer1711->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer1711->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* StaticText = new wxStaticText(DataPanel, wxID_ANY, wxT(" Data"), wxDefaultPosition, wxDefaultSize, 0);
	StaticText->Wrap(-1);
	fgSizer1711->Add(StaticText, 1, wxEXPAND, 5);

	DataTextCtrl = new wxTextCtrl(DataPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER, wxDefaultValidator);
	fgSizer1711->Add(DataTextCtrl, 1, wxALIGN_LEFT | wxALIGN_TOP | wxALL | wxEXPAND, 0);

	wxStaticText* staticText1411 = new wxStaticText(DataPanel, wxID_ANY, wxT("Format"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1411->Wrap(-1);
	fgSizer1711->Add(staticText1411, 0, wxALL, 5);

	wxArrayString FormatChoiceChoices;
	FormatChoice = new wxChoice(DataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, FormatChoiceChoices, 0);
	FormatChoice->SetSelection(0);
	fgSizer1711->Add(FormatChoice, 1, wxALL, 5);

	fgSizer1711->AddSpacer(10);

	ValidationButton = new wxButton(DataPanel, wxID_ANY, wxT("Validate Data"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1711->Add(ValidationButton, 1, wxEXPAND, 5);

	fgSizer1711->AddSpacer(10);

	ValidationNewLineRemovalCheckBox = new wxCheckBox(DataPanel, wxID_ANY, wxT("Remove newline characters from validation"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1711->Add(ValidationNewLineRemovalCheckBox, 1, wxEXPAND, 5);

	fgSizer1711->AddSpacer(10);

	wxStaticText* StaticText1 = new wxStaticText(DataPanel, wxID_ANY, wxT("Note - Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be delimited (e.g. comma delimited(default)) and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal."), wxDefaultPosition, wxDefaultSize, 0);
	StaticText1->Wrap(-1);
	fgSizer1711->Add(StaticText1, 1, wxEXPAND, 5);

	bSizer6911->Add(fgSizer1711, 1, wxALL | wxEXPAND, 5);

	DataPanel->SetSizer(bSizer6911);
	DataPanel->Layout();
	bSizer6911->Fit(DataPanel);

	return DataPanel;
}

void Data1_GUI_Base::Update( const observer_ptr<Data1> element)
{
	m_Data1TextCtrl->InitDialog();
	m_FormatChoice->InitDialog();
	ShowGUI(true);
};

wxString Data1_GUI_Base::GetTreeLabel(const observer_ptr<Data1> element)
{
	wxString str;
	str << wxT("Data");

	return str;
}


void Data1_GUI_Base::SetConnect()
{
	m_Data1TextCtrl->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Data1_GUI_Base::OnData1TextCtrlKillFocus), NULL, this);
	m_FormatChoice->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Data1_GUI_Base::OnFormatChoiceKillFocus), NULL, this);
	m_ValidationButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(Data1_GUI_Base::OnValidationButtonButton), NULL, this);
}



/// <summary>
/// Constructor for the derived class
/// </summary>
Data1_GUI::Data1_GUI() 
	: Data1_GUI_Base(),
	m_Data1TextCtrlValidator(nullptr),
	m_FormatChoiceValidator(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Data1_GUI::Data1_GUI(wxWindow* parent)
	: Data1_GUI_Base(parent),
	m_Data1TextCtrlValidator(nullptr),
	m_FormatChoiceValidator(nullptr)
{
	SetConnect();

}

/// <summary>
/// Destructor for the derived class
/// </summary>
Data1_GUI::~Data1_GUI() {
	/*parent will destroy Ctrl or window */

	delete m_Data1TextCtrlValidator;
	delete m_FormatChoiceValidator;
}

Data1_GUI::Data1TextCtrlValidator* Data1_GUI::GetData1TextCtrlValidator()
{
	return m_Data1TextCtrlValidator;
}

Data1_GUI::FormatChoiceValidator* Data1_GUI::GetFormatChoiceValidator()
{
	return m_FormatChoiceValidator;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Data1_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{

	//Set the validators for the wxWidgets.
	if(!m_Data1TextCtrlValidator)
		m_Data1TextCtrlValidator = new Data1TextCtrlValidator(MatMLTreeCtrl, m_ValidationNewLineRemovalCheckBox);
	m_Data1TextCtrl->SetValidator(*m_Data1TextCtrlValidator);

	if(!m_FormatChoiceValidator)
		m_FormatChoiceValidator = new FormatChoiceValidator(MatMLTreeCtrl);
	m_FormatChoice->SetValidator(*m_FormatChoiceValidator);

}

void Data1_GUI::OnData1TextCtrlKillFocus(wxCommandEvent& event)
{
	//m_Data1TextCtrl->Validation() done separately using a Validation button.
	m_Data1TextCtrl->TransferDataFromWindow();

	event.Skip();
 }

void Data1_GUI::OnFormatChoiceKillFocus(wxCommandEvent& event)
{
	if(m_FormatChoice->Validate())
		m_FormatChoice->TransferDataFromWindow();

	event.Skip();
 }

void Data1_GUI::OnValidationButtonButton(wxCommandEvent& event)
{
	m_Data1TextCtrl->Validate();
}

bool Data1_GUI::Data1TextCtrlValidator::Validate(wxWindow* WXUNUSED(parent))
{
	bool rtn = false;
	::std::string msg("");

	//Get wxWidget GUI Data
	wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (textctrl) {

		//Get MatML Data
		wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
		MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

		wxTreeItemId parentitemId = m_MatMLTreeCtrl->GetItemParent(itemId);
		MatMLTreeItemData* parentitem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(parentitemId));

		try {
			Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

			if (element) {

				PropertyData* const parentelement = boost::any_cast<PropertyData* const>(parentitem->GetAnyMatMLDataPointer());

				if (parentelement) {

					//Validate Data
					std::string input(_wx2std(textctrl->GetValue()));

					rtn = ValidateString(
						input,
						element->format(),
						parentelement->delimiter(),
						m_ValidationNewLineRemovalCheckBox->GetValue(),
						&msg
					);
				}
			}
			else {
				msg.assign("Validation Failed");
				rtn = false;
			}
		}
		catch (const boost::bad_any_cast&) { 
			msg.assign("Validation Failed"); 
			rtn = false; 
		}
	}
	else {
		msg.assign("Validation Failed");
		rtn = false;
	}

	wxMessageDialog Dialog(NULL, msg, _("MatML Message"), wxOK, wxDefaultPosition);
	Dialog.ShowModal();

	return rtn;
}

bool Data1_GUI::Data1TextCtrlValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			wxString str;
			str << _std2wx((*element));//double paranthesis required
			textctrl->ChangeValue(str);
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Data1_GUI::Data1TextCtrlValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{

			//Exchange Data
			wxString strData(textctrl->GetValue());
			element->assign(std::string(strData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Data1_GUI::FormatChoiceValidator::Validate(wxWindow* WXUNUSED(parent))
{
	//Get wxWidget GUI Data
	wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxChoice)));

	wxChoice* textctrl = (wxChoice*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

		if (element) {

			//No Validation required for DataFormat, but
			// Data1 should be validated based on new Dataformat.

		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Data1_GUI::FormatChoiceValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* formatchoice = (wxChoice*)GetWindow();
	if (!formatchoice)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			formatchoice->Clear();
			wxString str;

			for (size_t i = 0; i < 5; i++) {
				str.clear();
				str << _std2wx(std::string(DataFormat::_xsd_DataFormat_literals_[i]));
				formatchoice->Append(str);
			}

			str.clear();
			str << _std2wx(std::string(DataFormat::_xsd_DataFormat_literals_[element->format()]));
			formatchoice->SetStringSelection(str);

		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Data1_GUI::FormatChoiceValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* formatchoice = (wxChoice*)GetWindow();
	if (!formatchoice)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data1* const element = boost::any_cast<Data1* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{

			//Exchange Data
			element->format()= std::string(DataFormat::_xsd_DataFormat_literals_[formatchoice->GetSelection()]); //->assign(::string(iData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}
