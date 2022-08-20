#include "GUI/BT_MatML_DataSourceDetails_Display_GUI.h"

using namespace bellshire;

DataSourceDetails_Display_GUI::DataSourceDetails_Display_GUI()
	: m_GUI(nullptr),
	m_DataSourceDetailsUnitsTextCtrl(nullptr),
	m_DataSourceDetailsNameTextCtrl(nullptr),
	m_DataSourceDetailsNotesTextCtrl(nullptr)
{

};

DataSourceDetails_Display_GUI::DataSourceDetails_Display_GUI(wxNotebook* parent)
	: m_GUI(nullptr),
	m_DataSourceDetailsUnitsTextCtrl(nullptr),
	m_DataSourceDetailsNameTextCtrl(nullptr),
	m_DataSourceDetailsNotesTextCtrl(nullptr)
{
	m_GUI = Create(parent,
		m_DataSourceDetailsNameTextCtrl,
		m_DataSourceDetailsNotesTextCtrl
	);
};

DataSourceDetails_Display_GUI::~DataSourceDetails_Display_GUI()
{
	/*parent will distroy Ctrl or window */
};


wxPanel* DataSourceDetails_Display_GUI::Create(
	wxNotebook* parent,
	wxTextCtrl*& DataSourceDetailsNameTextCtrl,
	wxTextCtrl*& DataSourceDetailsNotesTextCtrl
)
{
	//Display the DataSourceDetails
	wxPanel* DataSourceDetails_Display = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxFlexGridSizer* fgSizer11611 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer11611->AddGrowableCol(1);
	fgSizer11611->AddGrowableRow(1);
	fgSizer11611->SetFlexibleDirection(wxBOTH);
	fgSizer11611->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText1851 = new wxStaticText(DataSourceDetails_Display, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1851->Wrap(-1);
	fgSizer11611->Add(staticText1851, 0, wxALL, 5);

	DataSourceDetailsNameTextCtrl = new wxTextCtrl(DataSourceDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	fgSizer11611->Add(DataSourceDetailsNameTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText17511 = new wxStaticText(DataSourceDetails_Display, wxID_ANY, wxT("Notes"), wxDefaultPosition, wxDefaultSize, 0);
	staticText17511->Wrap(-1);
	fgSizer11611->Add(staticText17511, 0, wxALL, 5);

	DataSourceDetailsNotesTextCtrl = new wxTextCtrl(DataSourceDetails_Display, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY);
	fgSizer11611->Add(DataSourceDetailsNotesTextCtrl, 1, wxALL | wxEXPAND, 5);

	DataSourceDetails_Display->SetSizer(fgSizer11611);
	DataSourceDetails_Display->Layout();
	fgSizer11611->Fit(DataSourceDetails_Display);

	return DataSourceDetails_Display;
}


void DataSourceDetails_Display_GUI::Update( PropertyData* element)
{
	//Update the DataSourceDetails Data on the panel
	
	m_DataSourceDetailsNameTextCtrl->Clear();
	m_DataSourceDetailsNotesTextCtrl->Clear();

	if (element->source().present()) {

		const DataSourceDetails* datasourcedetails(dynamic_cast<const DataSourceDetails*>(&*element->source().get()));
		if (datasourcedetails != NULL) {
			m_DataSourceDetailsNameTextCtrl->SetValue(_std2wx(datasourcedetails->Name()));
			if (datasourcedetails->Notes().present())
				m_DataSourceDetailsNotesTextCtrl->SetValue(_std2wx(datasourcedetails->Notes().get()));
		}
	}
};
