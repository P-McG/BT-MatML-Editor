#include <wx/config.h>
#include "BT_MatML_Value_GUI.h"

using namespace bellshire;

Value_GUI_Base::Value_GUI_Base()
	:m_GUI(nullptr),
	m_TextCtrl(nullptr),
	m_FormatChoice(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{

}

Value_GUI_Base::Value_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_TextCtrl(nullptr),
	m_FormatChoice(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{
	m_GUI = Create(parent,
		m_TextCtrl,
		m_FormatChoice,
		m_ValidationButton,
		m_ValidationNewLineRemovalCheckBox
	);
}

Value_GUI_Base::~Value_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Value MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ValueTextCtrl"></param>
/// <param name="ValueDataFormatChoice"></param>
/// <returns>bool</returns>
/// <todo>Value does not get inserted</todo>
wxNotebook* Value_GUI_Base::Create(wxWindow* parent,
	wxTextCtrl*& ValueTextCtrl,
	wxChoice*& FormatChoice,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{

	wxNotebook* ValueNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	ValueNotebook->Hide();

	wxScrolledWindow* ValuePanel = new wxScrolledWindow(ValueNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ValuePanel->SetScrollRate(5, 5);
	wxBoxSizer* bSizer92 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer17111 = new wxFlexGridSizer(5, 2, 0, 0);
	fgSizer17111->AddGrowableCol(1);
	fgSizer17111->AddGrowableRow(0);
	fgSizer17111->SetFlexibleDirection(wxBOTH);
	fgSizer17111->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* PropertyDataStaticText1 = new wxStaticText(ValuePanel, wxID_ANY, wxT("Value"), wxDefaultPosition, wxDefaultSize, 0);
	PropertyDataStaticText1->Wrap(-1);
	fgSizer17111->Add(PropertyDataStaticText1, 0, wxALL, 5);

	ValueTextCtrl = new wxTextCtrl(ValuePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER, wxDefaultValidator);
	fgSizer17111->Add(ValueTextCtrl, 0, wxALL | wxEXPAND, 0);

	wxStaticText* staticText2 = new wxStaticText(ValuePanel, wxID_ANY, wxT("Format"), wxDefaultPosition, wxDefaultSize, 0);
	staticText2->Wrap(-1);
	fgSizer17111->Add(staticText2, 0, wxALL, 5);

	wxArrayString ValueDataFormatChoiceChoices;
	FormatChoice = new wxChoice(ValuePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ValueDataFormatChoiceChoices, 0);
	FormatChoice->SetSelection(0);
	fgSizer17111->Add(FormatChoice, 1, wxALL | wxEXPAND, 5);

	fgSizer17111->AddSpacer(10);

	ValidationButton = new wxButton(ValuePanel, wxID_ANY, wxT("Validate Data"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer17111->Add(ValidationButton, 1, wxEXPAND, 5);

	fgSizer17111->AddSpacer(10);

	ValidationNewLineRemovalCheckBox = new wxCheckBox(ValuePanel, wxID_ANY, wxT("Remove newline characters from validation"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer17111->Add(ValidationNewLineRemovalCheckBox, 1, wxEXPAND, 5);

	fgSizer17111->AddSpacer(10);

	wxStaticText* PropertyDataStaticText3 = new wxStaticText(ValuePanel, wxID_ANY, wxT("Note - Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be delimited (e.g. comma delimited(default)) and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal."), wxDefaultPosition, wxDefaultSize, 0);
	PropertyDataStaticText3->Wrap(-1);
	fgSizer17111->Add(PropertyDataStaticText3, 0, wxALL, 5);

	bSizer92->Add(fgSizer17111, 1, wxEXPAND, 5);

	ValuePanel->SetSizer(bSizer92);
	ValuePanel->Layout();
	bSizer92->Fit(ValuePanel);

	MatMLInfo_GUI matMLInfo_GUI(ValueNotebook,
		wxT("*********** Value *************************\n\nThis element declares the content model for value, which\ncontains a string representing a value. Value has one\nrequired attribute, format, for indicating the format of the\nvalue.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ValueNotebook->AddPage(ValuePanel, wxT("MatML Data"), b_dflt);
	ValueNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ValueNotebook;
}

void Value_GUI_Base::Update( Value* element)
{
	m_TextCtrl->InitDialog();
	m_FormatChoice->InitDialog();

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Value_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	Value& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Value");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//format

	return CurrentId;
}

void Value_GUI_Base::SetConnect()
{
	m_TextCtrl->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Value_GUI_Base::OnTextCtrlKillFocus), NULL, this);
	m_FormatChoice->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Value_GUI_Base::OnFormatChoiceKillFocus), NULL, this);
	m_ValidationButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(Data1_GUI_Base::OnValidationButtonButton), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Value_GUI::Value_GUI() 
	: Value_GUI_Base(),
	m_MatMLTreeCtrl(nullptr),
	m_TextCtrlValidator(nullptr),
	m_FormatChoiceValidator(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Value_GUI::Value_GUI(wxWindow* parent)
	: Value_GUI_Base(parent), 
	m_MatMLTreeCtrl(nullptr),
	m_TextCtrlValidator(nullptr),
	m_FormatChoiceValidator(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Value_GUI::~Value_GUI() {
	/*parent will distroy Ctrl or window */
	delete m_TextCtrlValidator;
	delete m_FormatChoiceValidator;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Value_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	//Set the validators for the wxWidgets.
	if(!m_TextCtrlValidator)
		m_TextCtrlValidator = new TextCtrlValidator(MatMLTreeCtrl, m_ValidationNewLineRemovalCheckBox);
	m_TextCtrl->SetValidator(*m_TextCtrlValidator);

	if(!m_FormatChoiceValidator)
		m_FormatChoiceValidator = new FormatChoiceValidator(MatMLTreeCtrl);
	m_FormatChoice->SetValidator(*m_FormatChoiceValidator);

}

void Value_GUI::OnTextCtrlKillFocus(wxCommandEvent& event)
{
	//m_Data1TextCtrl->Validation() done separately using a Validation button.
	m_TextCtrl->TransferDataFromWindow();

	event.Skip();
}

void Value_GUI::OnFormatChoiceKillFocus(wxCommandEvent& event)
{
	if (m_FormatChoice->Validate())
		m_FormatChoice->TransferDataFromWindow();

	event.Skip();
}

void Value_GUI::OnValidationButtonButton(wxCommandEvent& event)
{
	m_TextCtrl->Validate();
}


bool Value_GUI::TextCtrlValidator::Validate(wxWindow* WXUNUSED(parent))
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

		try {
			Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());
			PropertyData* const grandparentelement = boost::any_cast<PropertyData* const>(grandparentitem->GetAnyMatMLDataPointer());

			if (element && grandparentelement) {

				//Validate Data
				std::string input(_wx2std(textctrl->GetValue()));

				rtn = ValidateString(
					input,
					element->format(),
					grandparentelement->delimiter(),
					m_ValidationNewLineRemovalCheckBox->GetValue(),
					&msg
				);
				
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

bool Value_GUI::TextCtrlValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());

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

bool Value_GUI::TextCtrlValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{

			//Exchange Data
			wxString strData(textctrl->GetValue());
			element->assign(::string(strData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}


bool Value_GUI::FormatChoiceValidator::Validate(wxWindow* WXUNUSED(parent))
{
	//Get wxWidget GUI Data
	wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxChoice)));

	wxChoice* textctrl = (wxChoice*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());

		if (element) {

			//No Validation required for DataFormat, but
			// TextCtrl should be validated based on new Dataformat.

		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Value_GUI::FormatChoiceValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* formatchoice = (wxChoice*)GetWindow();
	if (!formatchoice)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			formatchoice->Clear();
			wxString str;

			for (size_t i = 0; i < 5; i++) {
				str.clear();
				str << _std2wx(::string(DataFormat::_xsd_DataFormat_literals_[i]));
				formatchoice->Append(str);
			}

			str.clear();
			str << _std2wx(::string(DataFormat::_xsd_DataFormat_literals_[element->format()]));
			formatchoice->SetStringSelection(str);

		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Value_GUI::FormatChoiceValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* formatchoice = (wxChoice*)GetWindow();
	if (!formatchoice)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Value* const element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			element->format() = ::string(DataFormat::_xsd_DataFormat_literals_[formatchoice->GetSelection()]); //->assign(::string(iData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}


//
//void Value_GUI::OnValueTextCtrl(wxCommandEvent& event)
//{
//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
//
//	try {
//		Value* const Element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());
//		if (Element != 0) {
//			wxString str(m_ValueTextCtrl->GetValue());
//			Value NewData((const char*)str.mb_str(wxConvUTF8), Element->format());
//			(*Element) = NewData;
//			return;
//		}
//	}
//	catch (const boost::bad_any_cast&) { return; }
//}
//
//void Value_GUI::OnValueDataFormatChoice(wxCommandEvent& event)
//{
//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
//
//	try {
//		Value* const Element = boost::any_cast<Value* const>(item->GetAnyMatMLDataPointer());  
//		if (Element != 0) {
//			wxString str(m_ValueDataFormatChoice->GetStringSelection());
//			Value::format_type NewData((const char*)str.mb_str(wxConvUTF8));
//			Element->format() = NewData;
//			return;
//		}
//	}
//	catch (const boost::bad_any_cast&) { return; }
//}

