#include "BT_MatML_MeasurementTechniqueDetails_Display_GUI.h"

using namespace bellshire;

MeasurementTechniqueDetails_Display_GUI::MeasurementTechniqueDetails_Display_GUI()
	: m_GUI(nullptr),
	m_MeasurementTechniqueDetailsNameTextCtrl(nullptr),
	m_MeasurementTechniqueDetailsNotesTextCtrl(nullptr)
{

};

MeasurementTechniqueDetails_Display_GUI::MeasurementTechniqueDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_MeasurementTechniqueDetailsNameTextCtrl(nullptr),
	m_MeasurementTechniqueDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_MeasurementTechniqueDetailsNameTextCtrl,
		m_MeasurementTechniqueDetailsNotesTextCtrl
	);
};

MeasurementTechniqueDetails_Display_GUI::~MeasurementTechniqueDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};



wxPanel* MeasurementTechniqueDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& MeasurementTechniqueDetailsNameTextCtrl,
	wxTextCtrl*& MeasurementTechniqueDetailsNotesTextCtrl
)
{
	//Display the MeasurementTechniqueDetails
	wxPanel* MeasurementTechniqueDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer1161 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer1161->AddGrowableCol(1);
	fgSizer1161->AddGrowableRow(1);
	fgSizer1161->SetFlexibleDirection(wxBOTH);
	fgSizer1161->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText185 = new wxStaticText(MeasurementTechniqueDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText185->Wrap(-1);
	fgSizer1161->Add(staticText185, 0, wxALL, 5);

	MeasurementTechniqueDetailsNameTextCtrl = new wxTextCtrl(MeasurementTechniqueDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer1161->Add(MeasurementTechniqueDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText1751 = new wxStaticText(MeasurementTechniqueDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1751->Wrap(-1);
	fgSizer1161->Add(staticText1751, 0, wxALL, 5);

	MeasurementTechniqueDetailsNotesTextCtrl = new wxTextCtrl(MeasurementTechniqueDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer1161->Add(MeasurementTechniqueDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	MeasurementTechniqueDetails_Display->SetSizer(fgSizer1161);
	MeasurementTechniqueDetails_Display->Layout();
	fgSizer1161->Fit(MeasurementTechniqueDetails_Display);

	return MeasurementTechniqueDetails_Display;
}

void MeasurementTechniqueDetails_Display_GUI::Update( PropertyData* element)
{
	m_MeasurementTechniqueDetailsNameTextCtrl->Clear();
	m_MeasurementTechniqueDetailsNotesTextCtrl->Clear();

	if (element->technique().present()) {
		const MeasurementTechniqueDetails* measurementtechniquedetails(dynamic_cast<const MeasurementTechniqueDetails*>(&*element->technique().get()));
		if (measurementtechniquedetails != NULL) {
			m_MeasurementTechniqueDetailsNameTextCtrl->SetValue(_std2wx(measurementtechniquedetails->Name()));
			if (measurementtechniquedetails->Notes().present())
				m_MeasurementTechniqueDetailsNotesTextCtrl->SetValue(_std2wx(measurementtechniquedetails->Notes().get()));
		}
	}
}