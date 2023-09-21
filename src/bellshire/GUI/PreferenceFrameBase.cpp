
#include "pch.h"
#include "bellshire/GUI/PreferenceFrameBase.h"

using namespace bellshire::GUI;

PreferenceFrameBase::PreferenceFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxFlexGridSizer* fgSizer117 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer117->AddGrowableCol(0);
	fgSizer117->AddGrowableRow(0);
	fgSizer117->SetFlexibleDirection(wxBOTH);
	fgSizer117->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);


	m_listbook1 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxLB_LEFT);

	CreateGeneralPanel();
	CreateSortClassPanel();

	m_listbook1->AddPage(m_GeneralPanel, wxT("General"), true);
	m_listbook1->AddPage(m_SortClassPanel, wxT("Sort Class"), false);


	fgSizer117->Add(m_listbook1, 1, wxALL | wxEXPAND, 0);

	m_SavePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer(wxHORIZONTAL);

	m_SavePreferencesButton = new wxButton(m_SavePanel, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
	m_SavePreferencesButton->SetDefault();
	bSizer65->Add(m_SavePreferencesButton, 1, wxALL, 5);

	m_CancelPreferencesButton = new wxButton(m_SavePanel, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer65->Add(m_CancelPreferencesButton, 1, wxALIGN_CENTER | wxALL, 5);

	m_SavePanel->SetSizer(bSizer65);
	m_SavePanel->Layout();
	bSizer65->Fit(m_SavePanel);
	fgSizer117->Add(m_SavePanel, 1, wxALL | wxEXPAND, 0);


	this->SetSizer(fgSizer117);
	this->Layout();

	// Connect Events
	m_MatMLDataSelection->Connect(wxEVT_CHECKBOX, wxCommandEventHandler(PreferenceFrameBase::OnMatMLInfoSelection), NULL, this);
	m_WorkingDirPicker->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(PreferenceFrameBase::OnWorkingDirPicker), NULL, this);
	m_TemplateDirPicker->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(PreferenceFrameBase::OnTemplateDirPicker), NULL, this);
	m_UUIDPrefixTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PreferenceFrameBase::OnUUIDPrefixTextCtrl), NULL, this);
	m_LibDirPicker->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(PreferenceFrameBase::OnLibDirPicker), NULL, this);

	m_SavePreferencesButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PreferenceFrameBase::OnSavePreferencesButton), NULL, this);
	m_CancelPreferencesButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PreferenceFrameBase::OnCancelPreferencesButton), NULL, this);
}

void PreferenceFrameBase::CreateGeneralPanel()
{
	m_GeneralPanel = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* bSizer64 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* m_staticText0 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("General"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText0->Wrap(-1);
	m_staticText0->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	bSizer64->Add(m_staticText0, 0, wxALL, 5);

	wxFlexGridSizer* fgSizer115 = new wxFlexGridSizer(10, 2, 0, 0);
	fgSizer115->AddGrowableCol(1);
	fgSizer115->AddGrowableRow(7);
	fgSizer115->SetFlexibleDirection(wxBOTH);
	fgSizer115->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	//fgSizer115->AddSpacer(0);
	wxStaticText* m_staticText01 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("Click to show MatML Data tab first \n(application restart required)"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText01->Wrap(-1);
	fgSizer115->Add(m_staticText01, 0, wxALL, 5);

	m_MatMLDataSelection = new wxCheckBox(m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fgSizer115->Add(m_MatMLDataSelection, 1, wxALL | wxEXPAND, 5);

	wxStaticText* m_staticText1 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("Working Directory"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	fgSizer115->Add(m_staticText1, 0, wxALL, 5);

	m_WorkingDirPicker = new wxDirPickerCtrl(m_GeneralPanel, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer115->Add(m_WorkingDirPicker, 1, wxALL | wxEXPAND, 5);

	wxStaticText* m_staticText2 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("Template Directory"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	fgSizer115->Add(m_staticText2, 0, wxALL, 5);

	m_TemplateDirPicker = new wxDirPickerCtrl(m_GeneralPanel, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer115->Add(m_TemplateDirPicker, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText3 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("UUID Prefix (Alphabetic only)"), wxDefaultPosition, wxDefaultSize, 0);
	staticText3->Wrap(-1);
	fgSizer115->Add(staticText3, 0, wxALL, 5);

	m_UUIDPrefixTextCtrl = new wxTextCtrl(m_GeneralPanel, wxID_ANY, wxT("BT"), wxDefaultPosition, wxDefaultSize, 0);
	m_UUIDPrefixTextCtrl->SetHint(wxT("First character must be alphabetic, NOT NUMERIC!"));
	fgSizer115->Add(m_UUIDPrefixTextCtrl, 0, wxALL | wxEXPAND, 5);

	wxStaticText* m_staticText31 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("Click to hide MatML Lib tab\n(application restart required)"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText31->Wrap(-1);
	fgSizer115->Add(m_staticText31, 0, wxALL, 5);

	m_MatMLLibHideSelection = new wxCheckBox(m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_MatMLLibHideSelection->SetValue(false);
	fgSizer115->Add(m_MatMLLibHideSelection, 1, wxALL | wxEXPAND, 5);

	wxStaticText* m_staticText4 = new wxStaticText(m_GeneralPanel, wxID_ANY, wxT("Library Directory"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	fgSizer115->Add(m_staticText4, 0, wxALL, 5);
 
	wxString LibDfltPath = "";
	m_LibDirPicker = new wxDirPickerCtrl(m_GeneralPanel, wxID_ANY, LibDfltPath, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer115->Add(m_LibDirPicker, 1, wxALL | wxEXPAND, 5);

	bSizer64->Add(fgSizer115, 0, wxEXPAND, 5);

	m_GeneralPanel->SetSizer(bSizer64);
	m_GeneralPanel->Layout();
	bSizer64->Fit(m_GeneralPanel);
}

void PreferenceFrameBase::CreateSortClassPanel()
{

	m_SortClassPanel = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* bSizer20 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText20 = new wxStaticText(m_SortClassPanel, wxID_ANY, wxT("Sort Class"), wxDefaultPosition, wxDefaultSize, 0);
	staticText20->Wrap(-1);
	staticText20->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	bSizer20->Add(staticText20, 0, wxALL, 5);

	wxFlexGridSizer* fgSizer20 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer20->AddGrowableCol(1);
	fgSizer20->AddGrowableRow(1);
	fgSizer20->SetFlexibleDirection(wxBOTH);
	fgSizer20->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText21 = new wxStaticText(m_SortClassPanel, wxID_ANY, wxT("Material's Class Sort Order"), wxDefaultPosition, wxDefaultSize, 0);
	staticText21->Wrap(-1);
	fgSizer20->Add(staticText21, 0, wxALL, 5);

	wxStaticText* staticText22 = new wxStaticText(m_SortClassPanel, wxID_ANY, wxT("Sorts view (not the xml file) as per the following: \n1) Material as per its Class->Name,\n2) Material as per its position in the xml file."), wxDefaultPosition, wxDefaultSize, 0);
	staticText22->Wrap(-1);
	fgSizer20->Add(staticText22, 0, wxALL, 5);

	fgSizer20->AddSpacer(0);

	m_ClassSortOrderListBox = new wxEditableListBox(m_SortClassPanel, wxID_ANY,wxT("Edit Sort Classes"), wxDefaultPosition, wxSize(50, 200));
	fgSizer20->Add(m_ClassSortOrderListBox, 0, wxALL | wxEXPAND, 5);
	

	bSizer20->Add(fgSizer20, 0,wxALL| wxEXPAND, 5);

	m_SortClassPanel->SetSizer(bSizer20);
	m_SortClassPanel->Layout();
	bSizer20->Fit(m_SortClassPanel);

}


PreferenceFrameBase::~PreferenceFrameBase()
{
}
