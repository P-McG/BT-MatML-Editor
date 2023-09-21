#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Data_GUI.h"

using namespace bellshire::GUI;

Data_GUI_Base::Data_GUI_Base()
	:m_DataTextCtrl(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{

}

Data_GUI_Base::Data_GUI_Base(wxWindow* parent)
	:m_DataTextCtrl(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{
	m_GUI = Create(parent,
		m_DataTextCtrl,
		m_ValidationButton,
		m_ValidationNewLineRemovalCheckBox
	);
}

Data_GUI_Base::~Data_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Data_GUI_Base::GetDataTextCtrl()
{
	return m_DataTextCtrl;
}

wxButton* Data_GUI_Base::GetValidationButton()
{
	return m_ValidationButton;
}

wxCheckBox* Data_GUI_Base::GetValidationNewLineRemovalCheckBox()
{
	return m_ValidationNewLineRemovalCheckBox;
}

/// <summary>
/// Create the GUI for the ::Data MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="DataTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Data_GUI_Base::Create(wxWindow* parent, 
	wxTextCtrl*& DataTextCtrl,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{
	wxNotebook* DataNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DataNotebook->Hide();
	DataNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DataPanel(CreateDataPanel(DataNotebook, 
		DataTextCtrl,
		ValidationButton,
		ValidationNewLineRemovalCheckBox
	));

	MatMLInfo_GUI matMLInfo_GUI(DataNotebook,
		wxT("*********** Data *************************\n\nData contains the property data and has one required attribute,\nformat [NOT ALLOWED IN MATML 3.1], for indicating the format of the data.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataNotebook->AddPage(DataPanel, wxT("MatML Data."), b_dflt);
	DataNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataNotebook;
}

wxWindow* Data_GUI_Base::CreateDataPanel(wxWindow* parent,
	wxTextCtrl*& DataTextCtrl,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{

	wxScrolledWindow* DataPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DataPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer691 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer171 = new wxFlexGridSizer(4, 2, 0, 0);
	fgSizer171->AddGrowableCol(1);
	fgSizer171->AddGrowableRow(0);
	fgSizer171->SetFlexibleDirection(wxBOTH);
	fgSizer171->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(DataPanel, wxID_ANY, wxT("Parameter Value Data"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer171->Add(staticText1, 0, wxALL, 5);

	DataTextCtrl = new wxTextCtrl(DataPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER);
	fgSizer171->Add(DataTextCtrl, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 5);

	fgSizer171->AddSpacer(10);

	ValidationButton = new wxButton(DataPanel, wxID_ANY, wxT("Validate Data"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer171->Add(ValidationButton, 1, wxEXPAND, 5);

	fgSizer171->AddSpacer(10);

	ValidationNewLineRemovalCheckBox = new wxCheckBox(DataPanel, wxID_ANY, wxT("Remove newline characters from validation"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer171->Add(ValidationNewLineRemovalCheckBox, 1, wxEXPAND, 5);
	;
	fgSizer171->AddSpacer(10);

	wxStaticText* staticText2 = new wxStaticText(DataPanel, wxID_ANY, wxT("Note:\n- Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be delimited (e.g. comma delimited(default)) and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal.\n- Under TestConditionDetails there is no delimiter option, please use comma default delimiter.\n- Under ProcessingDetails there is no delimiter option, please use comma default delimiter."), wxDefaultPosition, wxDefaultSize, 0);
	staticText2->Wrap(-1);
	fgSizer171->Add(staticText2, 0, wxALL, 5);

	bSizer691->Add(fgSizer171, 1, wxEXPAND, 5);

	DataPanel->SetSizer(bSizer691);
	DataPanel->Layout();
	bSizer691->Fit(DataPanel);

	return DataPanel;
}


void Data_GUI_Base::Update( const observer_ptr<Data> element)
{
	m_DataTextCtrl->InitDialog();
	Show(true);
};

wxString Data_GUI_Base::GetTreeLabel(const observer_ptr<Data> element)
{
	wxString str;
	str << wxT("Data");

	return str;
}


void Data_GUI_Base::SetConnect()
{
	m_DataTextCtrl->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Data_GUI_Base::OnDataTextCtrlKillFocus), NULL, this);
	m_ValidationButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(Data_GUI_Base::OnValidationButtonButton), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Data_GUI::Data_GUI() : 
	Data_GUI_Base(),
	m_DataTextCtrlValidator(nullptr)

{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Data_GUI::Data_GUI(wxWindow* parent)
	: Data_GUI_Base(parent),
	m_DataTextCtrlValidator(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Data_GUI::~Data_GUI() {
	/*parent will destroy Ctrl or window */
	delete m_DataTextCtrlValidator;
}

Data_GUI::DataTextCtrlValidator* Data_GUI::GetDataTextCtrlValidator()
{
	return m_DataTextCtrlValidator;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Data_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	//Set the validators for the wxWidgets.
	if(!m_DataTextCtrlValidator)
		m_DataTextCtrlValidator = new DataTextCtrlValidator(MatMLTreeCtrl, GetValidationNewLineRemovalCheckBox());
	GetDataTextCtrl()->SetValidator(*m_DataTextCtrlValidator);

}

void Data_GUI::OnDataTextCtrlKillFocus(wxCommandEvent& event)
{
	//m_DataTextCtrl->Validation() done separately using a Validation button.
	GetDataTextCtrl()->TransferDataFromWindow();

	event.Skip();
}

void Data_GUI::OnValidationButtonButton(wxCommandEvent& event)
{
	GetDataTextCtrl()->Validate();
}


bool Data_GUI::DataTextCtrlValidator::Validate(wxWindow* WXUNUSED(parent))
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

		wxTreeItemId grandparentitemId = m_MatMLTreeCtrl->GetItemParent(parentitemId);
		MatMLTreeItemData* grandparentitem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(grandparentitemId));

		//try {
			Data* const element = boost::any_cast<Data* const>(item->GetAnyMatMLDataPointer());

			if (element) {

				::std::string format("string");
				::std::string delimiter(",");
				bool newlineremoval(m_ValidationNewLineRemovalCheckBox->GetValue());

				ParameterValue* const parentelement = boost::any_cast<ParameterValue* const>(parentitem->GetAnyMatMLDataPointer());
				if (parentelement) format.assign(parentelement->format());

				try {
					//In the case of TestConditionDetails, and ProcessingDetails this will be bad cast. These don't have delimiter attributes anyways.
					PropertyData* const grandparentelement = boost::any_cast<PropertyData* const>(grandparentitem->GetAnyMatMLDataPointer());
					if (grandparentelement) delimiter.assign(grandparentelement->delimiter());
				}
				catch (const boost::bad_any_cast&) {}

				//Validate Data
				std::string input(_wx2std(textctrl->GetValue()));

				rtn = ValidateString(
					input,
					format,
					delimiter,
					newlineremoval,
					&msg
				);
				
			}
			else rtn = false;
		//}
		//catch (const boost::bad_any_cast&) {
		//	msg.assign("Validation Failed");
		//	rtn = false;
		//}
	}
	else { 
		msg.assign("Validation failed");  
		rtn = false; 
	}

	wxMessageDialog Dialog(NULL, msg, _("MatML Message"), wxOK, wxDefaultPosition);
	Dialog.ShowModal();

	return rtn;
}

//bool Data_GUI::DataTextCtrlValidator::ValidateString(
//	::std::string input, 
//	::std::string Format,
//	::std::string Delimiter,
//	bool NewLineRemoval, 
//	::std::string* msg
//)
//{
//	//Validate Data
//	bool rtn = true;//default true;
//	std::list<std::string> result;
//
//	//remove newline characters for validation.
//	if (NewLineRemoval)
//		input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
//
//	//Split up the input string into data items.
//	if (!Delimiter.empty()) {
//		boost::split(result, input, boost::is_any_of(Delimiter));
//	}
//	else {
//		boost::split(result, input, boost::is_any_of(","));//default delimiter.
//	}
//
//	//Iterate over the data items and validate.
//	size_t i = 0;
//	list<std::string>::iterator itor(result.begin());
//	for (; itor != result.end(); ++itor, ++i) {
//		if (Format == "float" && !isValid<float>(*itor)) {
//			msg->append( *itor + " ( data item " + std::to_string(i + 1) +") is NOT a float");
//			rtn = false;
//			break;
//		}
//		else if (Format == "integer" && !isValid<int>(*itor)) {
//			msg->append( *itor + " ( data item " + std::to_string(i + 1) + ") is NOT a integer");
//			rtn = false;
//			break;
//		}
//		else if (Format == "string" && !isValid<string>(*itor)) {
//			msg->append( *itor + " ( data item " + std::to_string(i + 1) + ") is NOT a string");
//			rtn = false;
//			break;
//		}
//	}
//
//	if (rtn) msg->append("Validated");
//
//	return rtn;
//}

//std::string Data_GUI::DataTextCtrlValidator::GetDelimiter()
//{
//	parentelement->delimiter()
//	grandparentelement->delimiter();
//}

bool Data_GUI::DataTextCtrlValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data* const element = boost::any_cast<Data* const>(item->GetAnyMatMLDataPointer());

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

bool Data_GUI::DataTextCtrlValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Data* const element = boost::any_cast<Data* const>(item->GetAnyMatMLDataPointer());

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
//
//template<typename T>
//bool Data_GUI::DataTextCtrlValidator::isValid(const string& num)
//{
//
//	bool res = true;
//
//	try {
//		T tmp = boost::lexical_cast<T>(num);
//	}
//	catch (boost::bad_lexical_cast&) {
//		res = false;
//	}
//
//	return(res);
//}

TreeCtrlSorted* Data_GUI::DataTextCtrlValidator::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

wxCheckBox* Data_GUI::DataTextCtrlValidator::GetValidationNewLineRemovalCheckBox()
{
	return m_ValidationNewLineRemovalCheckBox;
}
