#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Qualifier_GUI.h"

using namespace bellshire::GUI;

Qualifier_GUI_Base::Qualifier_GUI_Base()
	:m_QualifierTextCtrl(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{

}

Qualifier_GUI_Base::Qualifier_GUI_Base(wxWindow* parent)
	:m_QualifierTextCtrl(nullptr),
	m_ValidationButton(nullptr),
	m_ValidationNewLineRemovalCheckBox(nullptr)
{
	m_GUI = Create(parent,
		m_QualifierTextCtrl,
		m_ValidationButton,
		m_ValidationNewLineRemovalCheckBox);
}

Qualifier_GUI_Base::~Qualifier_GUI_Base() {
	/*parent will destroy Ctrl or window */

}

wxTextCtrl* Qualifier_GUI_Base::GetQualifierTextCtrl()
{
	return m_QualifierTextCtrl;
}

wxButton* Qualifier_GUI_Base::GetValidationButton()
{
	return m_ValidationButton;
}

wxCheckBox* Qualifier_GUI_Base::GetValidationNewLineRemovalCheckBox()
{
	return m_ValidationNewLineRemovalCheckBox;
}

/// <summary>
/// Create the GUI for the Qualifier MatML Data and Info
/// </summary>CreateQualifierPanel
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="QualifierNotebook"></param>
/// <param name="QualifierPanel"></param>
/// <param name="QualifierTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* Qualifier_GUI_Base::Create(wxWindow* parent,
	wxTextCtrl*& QualifierTextCtrl,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{

	wxNotebook* QualifierNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	QualifierNotebook->Hide();
	QualifierNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* QualifierPanel(CreateQualifierPanel(QualifierNotebook,
		QualifierTextCtrl,
		ValidationButton,
		ValidationNewLineRemovalCheckBox
	));

	MatMLInfo_GUI matMLInfo_GUI(QualifierNotebook,
		wxT("*********** Qualifier *************************\n\nThis element declares the content model for Qualifier, which contains\na string representing a qualifier.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	QualifierNotebook->AddPage(QualifierPanel, wxT("MatML Data."), b_dflt);
	QualifierNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return QualifierNotebook;
}

wxWindow* Qualifier_GUI_Base::CreateQualifierPanel(wxWindow* parent,
	wxTextCtrl*& QualifierTextCtrl,
	wxButton*& ValidationButton,
	wxCheckBox*& ValidationNewLineRemovalCheckBox
)
{

	wxScrolledWindow* QualifierPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	QualifierPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer77 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer20 = new wxFlexGridSizer(4, 2, 0, 0);
	fgSizer20->AddGrowableCol(1);
	fgSizer20->AddGrowableRow(0);
	fgSizer20->SetFlexibleDirection(wxBOTH);
	fgSizer20->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(QualifierPanel, wxID_ANY, wxT("Qualifier"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer20->Add(staticText1, 0, wxALL, 5);

	QualifierTextCtrl = new wxTextCtrl(QualifierPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_DONTWRAP | wxALWAYS_SHOW_SB | wxTE_PROCESS_ENTER, wxDefaultValidator);
	fgSizer20->Add(QualifierTextCtrl, 0, wxALL | wxEXPAND, 5);

	fgSizer20->AddSpacer(10);

	ValidationButton = new wxButton(QualifierPanel, wxID_ANY, wxT("Validate Data"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer20->Add(ValidationButton, 1, wxEXPAND, 5);

	fgSizer20->AddSpacer(10);

	ValidationNewLineRemovalCheckBox = new wxCheckBox(QualifierPanel, wxID_ANY, wxT("Remove newline characters from validation"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer20->Add(ValidationNewLineRemovalCheckBox, 1, wxEXPAND, 5);

	fgSizer20->AddSpacer(10);

	wxStaticText* staticText2 = new wxStaticText(QualifierPanel, wxID_ANY, wxT("Note - Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be delimited (e.g. comma delimited) and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal."), wxDefaultPosition, wxDefaultSize, 0);
	staticText2->Wrap(-1);
	fgSizer20->Add(staticText2, 0, wxALL, 5);

	bSizer77->Add(fgSizer20, 1, wxEXPAND, 5);

	QualifierPanel->SetSizer(bSizer77);
	QualifierPanel->Layout();
	bSizer77->Fit(QualifierPanel);

	return QualifierPanel;
}

void Qualifier_GUI_Base::Update( const observer_ptr<Qualifier> element)
{
	m_QualifierTextCtrl->InitDialog();

	ShowGUI(true);
}


wxString Qualifier_GUI_Base::GetTreeLabel(const observer_ptr<Qualifier> element)
{
	wxString str;
	str << wxT("Qualifier");

	return str;
}


void Qualifier_GUI_Base::SetConnect()
{
	m_QualifierTextCtrl->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Qualifier_GUI_Base::OnQualifierTextCtrlKillFocus), NULL, this);
	m_ValidationButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(Qualifier_GUI_Base::OnValidationButtonButton), NULL, this);
}



/// <summary>
/// Constructor for the derived class
/// </summary>
Qualifier_GUI::Qualifier_GUI()
	: Qualifier_GUI_Base(),
	m_MatMLTreeCtrl(nullptr),
	m_TextCtrlValidator(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Qualifier_GUI::Qualifier_GUI(wxWindow* parent)
	: Qualifier_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr),
	m_TextCtrlValidator(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Qualifier_GUI::~Qualifier_GUI() {
	/*parent will destroy Ctrl or window */

	delete m_TextCtrlValidator;
}

TreeCtrlSorted* Qualifier_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Qualifier_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	//Set the validators for the wxWidgets.
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	if(!m_TextCtrlValidator)
		m_TextCtrlValidator = new TextCtrlValidator(MatMLTreeCtrl, m_ValidationNewLineRemovalCheckBox);
	m_QualifierTextCtrl->SetValidator(*m_TextCtrlValidator);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Qualifier_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Qualifier_GUI::OnQualifierTextCtrlKillFocus(wxCommandEvent& event)
{
	//m_Data1TextCtrl->Validation() done separately using a Validation button.
	m_QualifierTextCtrl->TransferDataFromWindow();

	event.Skip();
}

void Qualifier_GUI::OnValidationButtonButton(wxCommandEvent& event)
{
	m_QualifierTextCtrl->Validate();
}

bool Qualifier_GUI::TextCtrlValidator::Validate(wxWindow* WXUNUSED(parent))
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
			Qualifier* const element = boost::any_cast<Qualifier* const>(item->GetAnyMatMLDataPointer());

			if (element) {

				PropertyData* const parentelement = boost::any_cast<PropertyData* const>(parentitem->GetAnyMatMLDataPointer());

				if (parentelement) {

					//Validate Data
					std::string input(_wx2std(textctrl->GetValue()));

					rtn = ValidateString(
						input,
						::std::string("string"),//hardcoded string format for Qualifier.
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

bool Qualifier_GUI::TextCtrlValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Qualifier* const element = boost::any_cast<Qualifier* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			wxString str;
			str << _std2wx((*element));//double parenthesis required
			textctrl->ChangeValue(str);
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Qualifier_GUI::TextCtrlValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxTextCtrl));

	wxTextCtrl* textctrl = (wxTextCtrl*)GetWindow();
	if (!textctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Qualifier* const element = boost::any_cast<Qualifier* const>(item->GetAnyMatMLDataPointer());

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


void Qualifier_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Qualifier,
		ParameterValue,
		ParameterValue::Qualifier_sequence,
		Qualifier_GUI,
		&ParameterValue::Qualifier
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Qualifier_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Qualifier,
		ParameterValue,
		ParameterValue::Qualifier_sequence,
		Qualifier_GUI,
		&ParameterValue::Qualifier
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

TreeCtrlSorted* Qualifier_GUI::TextCtrlValidator::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

wxCheckBox* Qualifier_GUI::TextCtrlValidator::GetValidationNewLineRemovalCheckBox()
{
	return m_ValidationNewLineRemovalCheckBox;
}
