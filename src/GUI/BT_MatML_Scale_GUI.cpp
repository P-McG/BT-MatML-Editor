#include <wx/config.h>
#include "BT_MatML_Scale_GUI.h"


using namespace bellshire;

Scale_GUI_Base::Scale_GUI_Base()
	:m_GUI(nullptr),
	m_ScaleChoice(nullptr)
{

}

Scale_GUI_Base::Scale_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ScaleChoice(nullptr)
{
	m_GUI = Create(parent,
		m_ScaleChoice
	);
}

Scale_GUI_Base::~Scale_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* ScalePanel = new wxScrolledWindow(ScaleNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	MatMLInfo_GUI matMLInfo_GUI(ScaleNotebook,
		wxT("*********** :Scale *************************\n\nScale contains the value for either linear or exponential scale. Default is linear.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ScaleNotebook->AddPage(ScalePanel, wxT("MatML Data"), b_dflt);
	ScaleNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ScaleNotebook;
}

void Scale_GUI_Base::Update( Scale* element)
{
	m_ScaleChoice->InitDialog();
	Show(true);
};


/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Scale_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	Scale& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Scale");

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
	/*parent will distroy Ctrl or window */

	delete m_ScaleChoiceValidator;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Scale_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{

	//Set the validators for the wxWidgets.
	m_ScaleChoiceValidator = new ScaleChoiceValidator(MatMLTreeCtrl);
	m_ScaleChoice->SetValidator(*m_ScaleChoiceValidator);

}

void Scale_GUI::OnScaleChoiceKillFocus(wxCommandEvent& event)
{
	m_ScaleChoice->Validate(); //done separately using a Validation button.
	m_ScaleChoice->TransferDataFromWindow();

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
			str << _std2wx((*element));//double paranthesis required
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
			element->assign(::string(strData.mb_str()));
		}
		else return false;
	}
	catch (const boost::bad_any_cast&) { return false; }

	return true;
}
