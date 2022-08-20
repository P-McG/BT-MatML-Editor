#include "BT_MatML_PropertyDetails_Display_GUI.h"

using namespace bellshire;

PropertyDetails_Display_GUI::PropertyDetails_Display_GUI()
	: m_GUI(nullptr),
	m_PropertyDetailsNameTextCtrl(nullptr),
	m_PropertyDetailsUnitsTextCtrl(nullptr),
	m_PropertyDetailsNotesTextCtrl(nullptr)
{

};

PropertyDetails_Display_GUI::PropertyDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_PropertyDetailsNameTextCtrl(nullptr),
	m_PropertyDetailsUnitsTextCtrl(nullptr),
	m_PropertyDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
	m_PropertyDetailsNameTextCtrl,
	m_PropertyDetailsUnitsTextCtrl,
	m_PropertyDetailsNotesTextCtrl
	);
};

PropertyDetails_Display_GUI::~PropertyDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};


wxPanel* PropertyDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& PropertyDetailsNameTextCtrl,
	wxTextCtrl*& PropertyDetailsUnitsTextCtrl,
	wxTextCtrl*& PropertyDetailsNotesTextCtrl
)
{
	//Display the PropertyDetails
	wxPanel* PropertyDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer116 = new wxFlexGridSizer(3, 2, 0, 0);
	fgSizer116->AddGrowableCol(1);
	fgSizer116->AddGrowableRow(2);
	fgSizer116->SetFlexibleDirection(wxBOTH);
	fgSizer116->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText184 = new wxStaticText(PropertyDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText184->Wrap(-1);
	fgSizer116->Add(staticText184, 0, wxALL, 5);

	PropertyDetailsNameTextCtrl = new wxTextCtrl(PropertyDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer116->Add(PropertyDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText174 = new wxStaticText(PropertyDetails_Display, wxID_ANY, wxT("Units"), wxDefaultPosition, wxDefaultSize, 0);
	staticText174->Wrap(-1);
	fgSizer116->Add(staticText174, 0, wxALL, 5);

	PropertyDetailsUnitsTextCtrl = new wxTextCtrl(PropertyDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer116->Add(PropertyDetailsUnitsTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText175 = new wxStaticText(PropertyDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText175->Wrap(-1);
	fgSizer116->Add(staticText175, 0, wxALL, 5);

	PropertyDetailsNotesTextCtrl = new wxTextCtrl(PropertyDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer116->Add(PropertyDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	PropertyDetails_Display->SetSizer(fgSizer116);
	PropertyDetails_Display->Layout();
	fgSizer116->Fit(PropertyDetails_Display);

	return PropertyDetails_Display;
};

void PropertyDetails_Display_GUI::Update( PropertyData* element)
{
	//Show details for element->property()
	m_PropertyDetailsNameTextCtrl->Clear();
	m_PropertyDetailsUnitsTextCtrl->Clear();
	m_PropertyDetailsNotesTextCtrl->Clear();
	const PropertyDetails* propertydetails(dynamic_cast<const PropertyDetails*>(&*element->property()));
	if (propertydetails != NULL) {
		m_PropertyDetailsNameTextCtrl->SetValue(_std2wx(propertydetails->Name()));
		if (propertydetails->Units().present())
			if (propertydetails->Units()->name().present())
				m_PropertyDetailsUnitsTextCtrl->SetValue(_std2wx(propertydetails->Units()->name().get()));
		if (propertydetails->Notes().present())
			m_PropertyDetailsNotesTextCtrl->SetValue(_std2wx(propertydetails->Notes().get()));
	};
};
