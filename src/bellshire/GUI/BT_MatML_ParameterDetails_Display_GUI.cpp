#include "pch.h"
#include "bellshire/GUI/BT_MatML_ParameterDetails_Display_GUI.h"

using namespace bellshire::GUI;

ParameterDetails_Display_GUI::ParameterDetails_Display_GUI()
	: m_GUI(nullptr),
	m_ParameterDetailsNameTextCtrl(nullptr),
	m_ParameterDetailsNotesTextCtrl(nullptr)
{

};

ParameterDetails_Display_GUI::ParameterDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_ParameterDetailsNameTextCtrl(nullptr),
	m_ParameterDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_ParameterDetailsNameTextCtrl,
		m_ParameterDetailsNotesTextCtrl
	);
}

ParameterDetails_Display_GUI::~ParameterDetails_Display_GUI()
{
	/*parent will destroy Ctrl or window */
}
wxPanel* ParameterDetails_Display_GUI::GetGUI()
{
	return m_GUI;
}

wxTextCtrl* ParameterDetails_Display_GUI::GetParameterDetailsNameTextCtrl()
{
	return m_ParameterDetailsNameTextCtrl;
}

wxTextCtrl* ParameterDetails_Display_GUI::GetParameterDetailsNotesTextCtrl()
{
	return m_ParameterDetailsNotesTextCtrl;
}


wxPanel* ParameterDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& ParameterDetailsNameTextCtrl,
	wxTextCtrl*& ParameterDetailsNotesTextCtrl
)
{
	//Display the ParameterDetails
	wxPanel* ParameterDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer116 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer116->AddGrowableCol(1);
	fgSizer116->AddGrowableRow(1);
	fgSizer116->SetFlexibleDirection(wxBOTH);
	fgSizer116->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText184 = new wxStaticText(ParameterDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText184->Wrap(-1);
	fgSizer116->Add(staticText184, 0, wxALL, 5);

	ParameterDetailsNameTextCtrl = new wxTextCtrl(ParameterDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer116->Add(ParameterDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText175 = new wxStaticText(ParameterDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText175->Wrap(-1);
	fgSizer116->Add(staticText175, 0, wxALL, 5);

	ParameterDetailsNotesTextCtrl = new wxTextCtrl(ParameterDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer116->Add(ParameterDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	ParameterDetails_Display->SetSizer(fgSizer116);
	ParameterDetails_Display->Layout();
	fgSizer116->Fit(ParameterDetails_Display);

	return ParameterDetails_Display;
};

void ParameterDetails_Display_GUI::Update(const observer_ptr< ParameterValue> element)
{
	if (element) {

		//Show details for element->property()
		m_ParameterDetailsNameTextCtrl->Clear();
		m_ParameterDetailsNotesTextCtrl->Clear();

		const ParameterDetails* parameterdetails(dynamic_cast<const ParameterDetails*>(&*element->parameter()));

		if (parameterdetails != NULL) {
			m_ParameterDetailsNameTextCtrl->SetValue(_std2wx(parameterdetails->Name()));

			if (parameterdetails->Notes().present())
				m_ParameterDetailsNotesTextCtrl->SetValue(_std2wx(parameterdetails->Notes().get()));
		}
	}
};
