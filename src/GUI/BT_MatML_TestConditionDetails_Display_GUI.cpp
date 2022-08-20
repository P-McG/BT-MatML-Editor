#include "BT_MatML_TestConditionDetails_Display_GUI.h"

using namespace bellshire;

TestConditionDetails_Display_GUI::TestConditionDetails_Display_GUI()
	: m_GUI(nullptr),
	m_TestConditionDetailsNotesTextCtrl(nullptr)
{

};

TestConditionDetails_Display_GUI::TestConditionDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_TestConditionDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_TestConditionDetailsNotesTextCtrl
	);
};

TestConditionDetails_Display_GUI::~TestConditionDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};


wxPanel* TestConditionDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& TestConditionDetailsNotesTextCtrl
)
{
	//Display the TestConditionDetails
	wxPanel* TestConditionDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* bSizer61 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer11613 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer11613->AddGrowableCol(1);
	fgSizer11613->AddGrowableRow(0);
	fgSizer11613->SetFlexibleDirection(wxBOTH);
	fgSizer11613->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	//Set up note display
	wxStaticText* staticText17513 = new wxStaticText(TestConditionDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText17513->Wrap(-1);
	fgSizer11613->Add(staticText17513, 0, wxALL, 5);

	TestConditionDetailsNotesTextCtrl = new wxTextCtrl(TestConditionDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	TestConditionDetailsNotesTextCtrl->Enable(false);

	fgSizer11613->Add(TestConditionDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);


	bSizer61->Add(fgSizer11613, 1, wxEXPAND, 5);

	TestConditionDetails_Display->SetSizer(bSizer61);
	TestConditionDetails_Display->Layout();
	bSizer61->Fit(TestConditionDetails_Display);

	return TestConditionDetails_Display;
}


void TestConditionDetails_Display_GUI::Update( PropertyData* element)
{
	m_TestConditionDetailsNotesTextCtrl->Clear();
	
	if (element->test().present()) {

		const TestConditionDetails* testconditiondetails(dynamic_cast<const TestConditionDetails*>(&*element->test().get()));
		if (testconditiondetails != NULL) {
			if (testconditiondetails->Notes().present())
				m_TestConditionDetailsNotesTextCtrl->SetValue(_std2wx(testconditiondetails->Notes().get()));
		}
	}
};
