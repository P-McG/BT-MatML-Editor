#include "BT_MatML_SpecimenDetails_Display_GUI.h"

using namespace bellshire;

SpecimenDetails_Display_GUI::SpecimenDetails_Display_GUI()
	: m_GUI(nullptr),
	m_SpecimenDetailsNameTextCtrl(nullptr),
	m_SpecimenDetailsNotesTextCtrl(nullptr)
{

};

SpecimenDetails_Display_GUI::SpecimenDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_SpecimenDetailsNameTextCtrl(nullptr),
	m_SpecimenDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_SpecimenDetailsNameTextCtrl,
		m_SpecimenDetailsNotesTextCtrl
	);
};

SpecimenDetails_Display_GUI::~SpecimenDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};


wxPanel* SpecimenDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& SpecimenDetailsNameTextCtrl,
	wxTextCtrl*& SpecimenDetailsNotesTextCtrl
)
{
	//Display the SpecimenDetails
	wxPanel* SpecimenDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer11612 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer11612->AddGrowableCol(1);
	fgSizer11612->AddGrowableRow(1);
	fgSizer11612->SetFlexibleDirection(wxBOTH);
	fgSizer11612->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText18511 = new wxStaticText(SpecimenDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText18511->Wrap(-1);
	fgSizer11612->Add(staticText18511, 0, wxALL, 5);

	SpecimenDetailsNameTextCtrl = new wxTextCtrl(SpecimenDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer11612->Add(SpecimenDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText17512 = new wxStaticText(SpecimenDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText17512->Wrap(-1);
	fgSizer11612->Add(staticText17512, 0, wxALL, 5);

	SpecimenDetailsNotesTextCtrl = new wxTextCtrl(SpecimenDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer11612->Add(SpecimenDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	SpecimenDetails_Display->SetSizer(fgSizer11612);
	SpecimenDetails_Display->Layout();
	fgSizer11612->Fit(SpecimenDetails_Display);

	return SpecimenDetails_Display;
};

void SpecimenDetails_Display_GUI::Update( PropertyData* element)
{
	m_SpecimenDetailsNameTextCtrl->Clear();
	m_SpecimenDetailsNotesTextCtrl->Clear();

	if (element->specimen().present()) {

		const SpecimenDetails* specimendetails(dynamic_cast<const SpecimenDetails*>(&*element->specimen().get()));
		if (specimendetails != NULL) {
			if (specimendetails->Name().present())
				m_SpecimenDetailsNameTextCtrl->SetValue(_std2wx(specimendetails->Name().get()));
			if (specimendetails->Notes().present())
				m_SpecimenDetailsNotesTextCtrl->SetValue(_std2wx(specimendetails->Notes().get()));
		}
	}
};
