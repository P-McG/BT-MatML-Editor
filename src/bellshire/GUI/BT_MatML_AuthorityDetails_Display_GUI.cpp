#include "pch.h"
#include "bellshire/GUI/BT_MatML_AuthorityDetails_Display_GUI.h"

using namespace bellshire::GUI;

AuthorityDetails_Display_GUI::AuthorityDetails_Display_GUI()
	: m_GUI(nullptr),
	m_AuthorityDetailsNameTextCtrl(nullptr),
	m_AuthorityDetailsNotesTextCtrl(nullptr)
{

};

AuthorityDetails_Display_GUI::AuthorityDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_AuthorityDetailsNameTextCtrl(nullptr),
	m_AuthorityDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_AuthorityDetailsNameTextCtrl,
		m_AuthorityDetailsNotesTextCtrl
	);
};

AuthorityDetails_Display_GUI::~AuthorityDetails_Display_GUI()
{
	/*parent will destroy Ctrl or window */
}
wxPanel* AuthorityDetails_Display_GUI::GetGUI()
{
	return m_GUI;
}
wxTextCtrl* AuthorityDetails_Display_GUI::GetAuthorityDetailsNameTextCtrl()
{
	return m_AuthorityDetailsNameTextCtrl;
}
wxTextCtrl* AuthorityDetails_Display_GUI::GetAuthorityDetailsNotesTextCtrl()
{
	return m_AuthorityDetailsNotesTextCtrl;
}

wxPanel* AuthorityDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& AuthorityDetailsNameTextCtrl,
	wxTextCtrl*& AuthorityDetailsNotesTextCtrl
)
{
	//Display the AuthorityDetails
	wxPanel* AuthorityDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer116 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer116->AddGrowableCol(1);
	fgSizer116->AddGrowableRow(1);
	fgSizer116->SetFlexibleDirection(wxBOTH);
	fgSizer116->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText184 = new wxStaticText(AuthorityDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText184->Wrap(-1);
	fgSizer116->Add(staticText184, 0, wxALL, 5);

	AuthorityDetailsNameTextCtrl = new wxTextCtrl(AuthorityDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer116->Add(AuthorityDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText175 = new wxStaticText(AuthorityDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText175->Wrap(-1);
	fgSizer116->Add(staticText175, 0, wxALL, 5);

	AuthorityDetailsNotesTextCtrl = new wxTextCtrl(AuthorityDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer116->Add(AuthorityDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	AuthorityDetails_Display->SetSizer(fgSizer116);
	AuthorityDetails_Display->Layout();
	fgSizer116->Fit(AuthorityDetails_Display);

	return AuthorityDetails_Display;
};

void AuthorityDetails_Display_GUI::Update(const observer_ptr< Name> element)
{
	if (element) {
		//Show details for element->property()
		m_AuthorityDetailsNameTextCtrl->Clear();
		m_AuthorityDetailsNotesTextCtrl->Clear();

		const Name::authority_optional& cont = element->authority();

		if (cont.present()) {
			const AuthorityDetails* authoritydetails(dynamic_cast<const AuthorityDetails*>(&*cont->get()));

			if (authoritydetails != NULL) {
				m_AuthorityDetailsNameTextCtrl->SetValue(_std2wx(authoritydetails->Name()));

				if (authoritydetails->Notes().present())
					m_AuthorityDetailsNotesTextCtrl->SetValue(_std2wx(authoritydetails->Notes().get()));
			};
		}
	}
};

void AuthorityDetails_Display_GUI::Update( const observer_ptr<Specification> element)
{
	if (element) {

		//Show details for element->property()
		m_AuthorityDetailsNameTextCtrl->Clear();
		m_AuthorityDetailsNotesTextCtrl->Clear();

		const Name::authority_optional& cont = element->authority();

		if (cont.present()) {
			const AuthorityDetails* authoritydetails(dynamic_cast<const AuthorityDetails*>(&*cont->get()));

			if (authoritydetails != NULL) {
				m_AuthorityDetailsNameTextCtrl->SetValue(_std2wx(authoritydetails->Name()));

				if (authoritydetails->Notes().present())
					m_AuthorityDetailsNotesTextCtrl->SetValue(_std2wx(authoritydetails->Notes().get()));
			};
		}
	}
};