#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Scale_GUI.h"


using namespace bellshire::GUI;

Scale_GUI_Base::Scale_GUI_Base()
	:m_ScaleChoice(nullptr)
{

}

Scale_GUI_Base::Scale_GUI_Base(wxWindow* parent)
	:m_ScaleChoice(nullptr)
{
	m_GUI = Create(parent,
		m_ScaleChoice
	);
}

Scale_GUI_Base::~Scale_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxChoice* Scale_GUI_Base::GetScaleChoice()
{
	return m_ScaleChoice;
}


/// <summary>
/// Create the GUI for the ::Data MatML Data and Info
/// </summary>
wxNotebook* Scale_GUI_Base::Create(wxWindow* parent,
	wxChoice*& ScaleChoice
)
{

	wxNotebook* ScaleNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	ScaleNotebook->Hide();
	ScaleNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ScalePanel(CreateScalePanel(ScaleNotebook, ScaleChoice));

	MatMLInfo_GUI matMLInfo_GUI(ScaleNotebook,
		wxT("*********** :Scale *************************\n\nScale contains the value for either linear or exponential scale. Default is linear.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ScaleNotebook->AddPage(ScalePanel, wxT("MatML Data"), b_dflt);
	ScaleNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ScaleNotebook;
}

wxWindow* Scale_GUI_Base::CreateScalePanel(wxWindow* parent,
	wxChoice*& ScaleChoice
)
{

	wxScrolledWindow* ScalePanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ScalePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer6911 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer1711 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1711->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer1711->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(ScalePanel, wxID_ANY, wxT("Scale"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1711->Add(staticText1, 0, wxALL, 5);

	wxString ScaleChoiceChoices[] = { wxT("Linear"), wxT("Logarithmic") };
	int ScaleChoiceNChoices = sizeof(ScaleChoiceChoices) / sizeof(wxString);
	ScaleChoice = new wxChoice(ScalePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ScaleChoiceNChoices, ScaleChoiceChoices, 0);
	ScaleChoice->SetSelection(0);
	fgSizer1711->Add(ScaleChoice, 1, wxALL | wxEXPAND, 5);

	bSizer6911->Add(fgSizer1711, 1, wxALL | wxEXPAND, 5);

	ScalePanel->SetSizer(bSizer6911);
	ScalePanel->Layout();
	bSizer6911->Fit(ScalePanel);

	return ScalePanel;
}

void Scale_GUI_Base::Update( const observer_ptr<Scale> element)
{
	m_ScaleChoice->InitDialog();
	ShowGUI(true);
};


wxString Scale_GUI_Base::GetTreeLabel(const observer_ptr<Scale> element)
{
	wxString str;
	str << wxT("Scale");

	return str;
}


void Scale_GUI_Base::SetConnect()
{
	m_ScaleChoice->Connect(wxEVT_KILL_FOCUS, wxCommandEventHandler(Scale_GUI_Base::OnScaleChoiceKillFocus), NULL, this);
}



/// <summary>
/// Constructor for the derived class
/// </summary>
Scale_GUI::Scale_GUI()
	: Scale_GUI_Base(),
	m_ScaleChoiceValidator(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Scale_GUI::Scale_GUI(wxWindow* parent)
	: Scale_GUI_Base(parent),
	m_ScaleChoiceValidator(nullptr)
{
	SetConnect();

}

/// <summary>
/// Destructor for the derived class
/// </summary>
Scale_GUI::~Scale_GUI() {
	/*parent will destroy Ctrl or window */

	delete m_ScaleChoiceValidator;
}

Scale_GUI::ScaleChoiceValidator* Scale_GUI::GetScaleChoiceValidator()
{
	return m_ScaleChoiceValidator;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Scale_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{

	//Set the validators for the wxWidgets.
	if(!m_ScaleChoiceValidator)
		m_ScaleChoiceValidator = new ScaleChoiceValidator(MatMLTreeCtrl);
	GetScaleChoice()->SetValidator(*m_ScaleChoiceValidator);

}

void Scale_GUI::OnScaleChoiceKillFocus(wxCommandEvent& event)
{
	GetScaleChoice()->Validate(); //done separately using a Validation button.
	GetScaleChoice()->TransferDataFromWindow();

	event.Skip();
}

bool Scale_GUI::ScaleChoiceValidator::Validate(wxWindow* WXUNUSED(parent))
{
	//Validate Data
    //NO VALIDATION REQUIRED
	return true;
}

bool Scale_GUI::ScaleChoiceValidator::TransferToWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* ctrl = (wxChoice*)GetWindow();
	if (!ctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Scale* const element = boost::any_cast<Scale* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{
			//Exchange Data
			wxString str;
			str << _std2wx((*element));//double parenthesis required
			ctrl->SetStringSelection(str);
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

bool Scale_GUI::ScaleChoiceValidator::TransferFromWindow()
{
	//Get wxWidget GUI Data
	wxASSERT(wxDynamicCast(m_validatorWindow, wxChoice));

	wxChoice* ctrl = (wxChoice*)GetWindow();
	if (!ctrl)	return false;

	//Get MatML Data
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Scale* const element = boost::any_cast<Scale* const>(item->GetAnyMatMLDataPointer());

		if (element)
		{

			//Exchange Data
			wxString strData(ctrl->GetStringSelection());
			element->assign(std::string(strData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}

TreeCtrlSorted* Scale_GUI::ScaleChoiceValidator::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}
