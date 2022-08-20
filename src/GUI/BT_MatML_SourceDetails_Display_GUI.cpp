#include "BT_MatML_SourceDetails_Display_GUI.h"

using namespace bellshire;

SourceDetails_Display_GUI::SourceDetails_Display_GUI()
	: m_GUI(nullptr),
	m_SourceDetailsNameTextCtrl(nullptr),
	m_SourceDetailsNotesTextCtrl(nullptr)
{

};

SourceDetails_Display_GUI::SourceDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_SourceDetailsNameTextCtrl(nullptr),
	m_SourceDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_SourceDetailsNameTextCtrl,
		m_SourceDetailsNotesTextCtrl
	);
};

SourceDetails_Display_GUI::~SourceDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};


wxPanel* SourceDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& SourceDetailsNameTextCtrl,
	wxTextCtrl*& SourceDetailsNotesTextCtrl
)
{
	//Display the SourceDetails
	wxPanel* SourceDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer116 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer116->AddGrowableCol(1);
	fgSizer116->AddGrowableRow(1);
	fgSizer116->SetFlexibleDirection(wxBOTH);
	fgSizer116->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText184 = new wxStaticText(SourceDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText184->Wrap(-1);
	fgSizer116->Add(staticText184, 0, wxALL, 5);

	SourceDetailsNameTextCtrl = new wxTextCtrl(SourceDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer116->Add(SourceDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText175 = new wxStaticText(SourceDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText175->Wrap(-1);
	fgSizer116->Add(staticText175, 0, wxALL, 5);

	SourceDetailsNotesTextCtrl = new wxTextCtrl(SourceDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer116->Add(SourceDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	SourceDetails_Display->SetSizer(fgSizer116);
	SourceDetails_Display->Layout();
	fgSizer116->Fit(SourceDetails_Display);

	return SourceDetails_Display;
};

void SourceDetails_Display_GUI::Update( Source* element)
{
	//Show details for element->property()
	m_SourceDetailsNameTextCtrl->Clear();
	m_SourceDetailsNotesTextCtrl->Clear();

	const Name::authority_optional& cont = element->source();

	if (cont.present()) {
		const SourceDetails*sourcedetails(dynamic_cast<const SourceDetails*>(&*cont->get()));

		if (sourcedetails != NULL) {
			m_SourceDetailsNameTextCtrl->SetValue(_std2wx(sourcedetails->Name()));

			if (sourcedetails->Notes().present())
				m_SourceDetailsNotesTextCtrl->SetValue(_std2wx(sourcedetails->Notes().get()));
		};
	};
};
