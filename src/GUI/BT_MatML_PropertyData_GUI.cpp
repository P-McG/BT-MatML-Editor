#include <wx/config.h>
#include "BT_MatML_PropertyData_GUI.h"

using namespace bellshire;


PropertyData_GUI_Base::PropertyData_GUI_Base()
	:m_GUI(nullptr),
	m_PropertyDataPropertiesChoice(nullptr),
	m_PropertyDataTechniqueChoice(nullptr),
	m_PropertyDataSourceChoice(nullptr),
	m_PropertyDataSpecimenChoice(nullptr),
	m_PropertyDataTestChoice(nullptr),
	m_PropertyDataDelimiterTextCtrl(nullptr),
	m_PropertyDataQuoteTextCtrl(nullptr),
	m_PropertyDataPropertyDetails_Display_GUI(nullptr),
	m_PropertyDataMeasurementTechniqueDetails_Display_GUI(nullptr),
	m_PropertyDataDataSourceDetails_Display_GUI(nullptr),
	m_PropertyDataSpecimenDetails_Display_GUI(nullptr),
	m_PropertyDataTestConditionDetails_Display_GUI(nullptr)
{

}

PropertyData_GUI_Base::PropertyData_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_PropertyDataPropertiesChoice(nullptr),
	m_PropertyDataTechniqueChoice(nullptr),
	m_PropertyDataSourceChoice(nullptr),
	m_PropertyDataSpecimenChoice(nullptr),
	m_PropertyDataTestChoice(nullptr),
	m_PropertyDataDelimiterTextCtrl(nullptr),
	m_PropertyDataQuoteTextCtrl(nullptr),
	m_PropertyDataPropertyDetails_Display_GUI(nullptr),
	m_PropertyDataMeasurementTechniqueDetails_Display_GUI(nullptr),
	m_PropertyDataDataSourceDetails_Display_GUI(nullptr),
	m_PropertyDataSpecimenDetails_Display_GUI(nullptr),
	m_PropertyDataTestConditionDetails_Display_GUI(nullptr)
{
	m_GUI = Create(parent,
		m_PropertyDataPropertiesChoice,
		m_PropertyDataTechniqueChoice,
		m_PropertyDataSourceChoice,
		m_PropertyDataSpecimenChoice,
		m_PropertyDataTestChoice,
		m_PropertyDataDelimiterTextCtrl,
		m_PropertyDataQuoteTextCtrl,
		m_PropertyDataPropertyDetails_Display_GUI,
		m_PropertyDataMeasurementTechniqueDetails_Display_GUI,
		m_PropertyDataDataSourceDetails_Display_GUI,
		m_PropertyDataSpecimenDetails_Display_GUI,
		m_PropertyDataTestConditionDetails_Display_GUI
	);
}

PropertyData_GUI_Base::~PropertyData_GUI_Base() {
	/*parent will distroy Ctrl or window */

	delete m_PropertyDataPropertyDetails_Display_GUI;//neither a Ctrl or a Window
	delete m_PropertyDataMeasurementTechniqueDetails_Display_GUI;//neither a Ctrl or a Window
	delete m_PropertyDataDataSourceDetails_Display_GUI;//neither a Ctrl or a Window
	delete m_PropertyDataSpecimenDetails_Display_GUI;//neither a Ctrl or a Window
	delete m_PropertyDataTestConditionDetails_Display_GUI;//neither a Ctrl or a Window


}


/// Create the GUI for the PropertyData MatML Data and Info

wxNotebook* PropertyData_GUI_Base::Create(wxWindow* parent,
	wxChoice*& PropertyDataPropertiesChoice,
	wxChoice*& PropertyDataTechniqueChoice,
	wxChoice*& PropertyDataSourceChoice,
	wxChoice*& PropertyDataSpecimenChoice,
	wxChoice*& PropertyDataTestChoice,
	wxTextCtrl*& PropertyDataDelimiterTextCtrl,
	wxTextCtrl*& PropertyDataQuoteTextCtrl,
	PropertyDetails_Display_GUI*& PropertyDataPropertyDetails_Display_GUI,
	MeasurementTechniqueDetails_Display_GUI*& PropertyDataMeasurementTechniqueDetails_Display_GUI,
	DataSourceDetails_Display_GUI*& PropertyDataDataSourceDetails_Display_GUI,
	SpecimenDetails_Display_GUI*& PropertyDataSpecimenDetails_Display_GUI,
	TestConditionDetails_Display_GUI*& PropertyDataTestConditionDetails_Display_GUI
)
{
	wxNotebook* PropertyDataNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	PropertyDataNotebook->Hide();
	PropertyDataNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* PropertyDataPanel = new wxScrolledWindow(PropertyDataNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	PropertyDataPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer75 = new wxBoxSizer(wxHORIZONTAL);

	wxFlexGridSizer* fgSizer138 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer138->AddGrowableCol(0);
	fgSizer138->AddGrowableRow(1);
	fgSizer138->SetFlexibleDirection(wxBOTH);
	fgSizer138->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxFlexGridSizer* fgSizer19 = new wxFlexGridSizer(7, 2, 0, 0);
	fgSizer19->AddGrowableCol(1);
	fgSizer19->SetFlexibleDirection(wxBOTH);
	fgSizer19->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText15 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Property"), wxDefaultPosition, wxDefaultSize, 0);
	staticText15->Wrap(-1);
	fgSizer19->Add(staticText15, 0, wxALL, 5);

	wxArrayString PropertyDataPropertiesChoiceChoices;
	PropertyDataPropertiesChoice = new wxChoice(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, PropertyDataPropertiesChoiceChoices, 0);
	PropertyDataPropertiesChoice->SetSelection(0);
	fgSizer19->Add(PropertyDataPropertiesChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText16 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Technique"), wxDefaultPosition, wxDefaultSize, 0);
	staticText16->Wrap(-1);
	fgSizer19->Add(staticText16, 0, wxALL, 5);

	wxArrayString PropertyDataTechniqueChoiceChoices;
	PropertyDataTechniqueChoice = new wxChoice(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, PropertyDataTechniqueChoiceChoices, 0);
	PropertyDataTechniqueChoice->SetSelection(0);
	fgSizer19->Add(PropertyDataTechniqueChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText17 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Source"), wxDefaultPosition, wxDefaultSize, 0);
	staticText17->Wrap(-1);
	fgSizer19->Add(staticText17, 0, wxALL, 5);

	wxArrayString PropertyDataSourceChoiceChoices;
	PropertyDataSourceChoice = new wxChoice(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, PropertyDataSourceChoiceChoices, 0);
	PropertyDataSourceChoice->SetSelection(0);
	fgSizer19->Add(PropertyDataSourceChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText18 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Specimen"), wxDefaultPosition, wxDefaultSize, 0);
	staticText18->Wrap(-1);
	fgSizer19->Add(staticText18, 0, wxALL, 5);

	wxArrayString PropertyDataSpecimenChoiceChoices;
	PropertyDataSpecimenChoice = new wxChoice(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, PropertyDataSpecimenChoiceChoices, 0);
	PropertyDataSpecimenChoice->SetSelection(0);
	fgSizer19->Add(PropertyDataSpecimenChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText19 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0);
	staticText19->Wrap(-1);
	fgSizer19->Add(staticText19, 0, wxALL, 5);

	wxArrayString PropertyDataTestChoiceChoices;
	PropertyDataTestChoice = new wxChoice(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, PropertyDataTestChoiceChoices, 0);
	PropertyDataTestChoice->SetSelection(0);
	fgSizer19->Add(PropertyDataTestChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText20 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Delimiter"), wxDefaultPosition, wxDefaultSize, 0);
	staticText20->Wrap(-1);
	fgSizer19->Add(staticText20, 0, wxALL, 5);

	PropertyDataDelimiterTextCtrl = new wxTextCtrl(PropertyDataPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer19->Add(PropertyDataDelimiterTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText21 = new wxStaticText(PropertyDataPanel, wxID_ANY, wxT("Quote"), wxDefaultPosition, wxDefaultSize, 0);
	staticText21->Wrap(-1);
	fgSizer19->Add(staticText21, 0, wxALL, 5);

	PropertyDataQuoteTextCtrl = new wxTextCtrl(PropertyDataPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer19->Add(PropertyDataQuoteTextCtrl, 1, wxALL | wxEXPAND, 5);

	fgSizer138->Add(fgSizer19, 1, wxEXPAND, 5);

	//Display Notebook
	wxNotebook* notebook6 = new wxNotebook(PropertyDataPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	//Display the Details
	PropertyDataPropertyDetails_Display_GUI=new PropertyDetails_Display_GUI(notebook6);
	notebook6->AddPage(PropertyDataPropertyDetails_Display_GUI->get(), wxT("Property"), false);

	PropertyDataMeasurementTechniqueDetails_Display_GUI = new MeasurementTechniqueDetails_Display_GUI(notebook6);
	notebook6->AddPage(PropertyDataMeasurementTechniqueDetails_Display_GUI->get(), wxT("Technique"), false);

	PropertyDataDataSourceDetails_Display_GUI = new DataSourceDetails_Display_GUI(notebook6);
	notebook6->AddPage(PropertyDataDataSourceDetails_Display_GUI->get(), wxT("Source"), false);

	PropertyDataSpecimenDetails_Display_GUI = new SpecimenDetails_Display_GUI(notebook6);
	notebook6->AddPage(PropertyDataSpecimenDetails_Display_GUI->get(), wxT("Specimen"), false);

	PropertyDataTestConditionDetails_Display_GUI = new TestConditionDetails_Display_GUI(notebook6);
	notebook6->AddPage(PropertyDataTestConditionDetails_Display_GUI->get(), wxT("Test Condition"), false);

	fgSizer138->Add(notebook6, 1, wxEXPAND | wxALL, 5);

	bSizer75->Add(fgSizer138, 1, wxEXPAND, 5);

	PropertyDataPanel->SetSizer(bSizer75);
	PropertyDataPanel->Layout();
	bSizer75->Fit(PropertyDataPanel);

	MatMLInfo_GUI matMLInfo_GUI(PropertyDataNotebook,
		wxT("*********** PropertyData *************************\n\nThis element declares the content model for PropertyData, which\ncontains property data. PropertyData has seven attributes.\n\nThe first attribute, property, is required and references an id attribute\nspecified in a PropertyDetails element so that the descriptive details for\nthe property are tied to the data found in the Data element.\n\nThe second attribute, technique, is optional and references an id \nattribute Specified in a MeasurementTechniqueDetails element so \nthat the Descriptive details for the measurement technique are\n tied to the data found In the Data element.\n\nThe third attribute, source, is optional and references an id attribute\nspecified in a DataSourceDetails element so that the descriptive details \nfor the data source are tied to the data found in the Data element.\n\nThe fourth attribute, specimen, is optional and references an id attribute\nspecified in a SpecimenDetails element so that the descriptive details for\nthe specimen are tied to the data found in the Data element.\n\t\t\t\nThe fifth attribute, test, is optional and references an id attribute\nspecified in a TestCondtionDetails element so that the descriptive \ndetails for the test condition(s) are tied to the data found in the \nData element.\n\t\t\t\nThe sixth attribute, delimiter, specifies the delimiter that \nseparates multiple values in the Data, Qualifier, Uncertainty, and \nParameterValue elements. The default value is a comma (',')\n\t\t\t\nThe seventh attribute, quote, specifies the string that is used \nto quote values in the Data, Qualifier, Uncertainty and \nParameterValue elements. The default value is a null string, \nwhich is equivalent to saying that the values are not quoted.\n\nPropertyData is composed of the following elements.\n\nData contains the property data and has one required attribute,\nformat, for indicating the format of the data. Data must occur \nonce and only once within the PropertyData element.\n\nQualifier contains any qualifier(s) pertinent to the data in Data \n(e.g. \"min,\" \"max,\" etc.) and may occur once or not at all within the\nPropertyData element.\n\nUncertainty contains the measurement uncertainty(ies) of the data in\nData and may occur once [MatML 3.1 schema set as many] or not at all within the PropertyData\nelement. For additional information, see the documentation for the\nUncertainty element.\n\nParameterValue contains the value(s) of a parameter under which\nthe data were determined and may occur zero or more times within\nthe PropertyData element. For additional information, see the\ndocumentation for the ParameterValue element.\n\nNotes contains any additional information concerning the property\ndata and may occur once or not at all within the PropertyData element.\n\nNote - Multiple entries in the Data, Qualifier, Uncertainty Value, and\nParameterValue elements must be comma delimited and\nsynchronized across elements, i.e., the number of entries\nin each of these four elements must be equal.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	PropertyDataNotebook->AddPage(PropertyDataPanel, wxT("MatML Data"), b_dflt);
	PropertyDataNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return PropertyDataNotebook;
}


void PropertyData_GUI_Base::Update( PropertyData* element, const ::boost::shared_ptr<MatML_Doc> doc)
{
	wxString str;

	if (IsShown() == false) {
		m_PropertyDataPropertiesChoice->Clear();
		m_PropertyDataTechniqueChoice->Clear();
		m_PropertyDataSourceChoice->Clear();
		m_PropertyDataSpecimenChoice->Clear();
		m_PropertyDataTestChoice->Clear();


		//Setup the id String for PropertyData.property choices boxes
		{
			const Metadata::PropertyDetails_sequence& cont(doc->Metadata()->PropertyDetails());
			Metadata::PropertyDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				wxArrayString strPropertyDataPropertiesChoice;
				for (; iter != cont.end(); ++iter) strPropertyDataPropertiesChoice.Add(_std2wx(Label(iter->Name(), iter->id())));
				m_PropertyDataPropertiesChoice->Append(strPropertyDataPropertiesChoice);
			}

		}

		//Setup the Technique String for PropertyData.technique choices boxes
		{
			const Metadata::MeasurementTechniqueDetails_sequence& cont(doc->Metadata()->MeasurementTechniqueDetails());
			Metadata::MeasurementTechniqueDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				wxArrayString strPropertyDataTechniqueChoice;
				strPropertyDataTechniqueChoice.Add(wxString(wxT("")));
				for (; iter != cont.end(); ++iter) strPropertyDataTechniqueChoice.Add(_std2wx(Label(iter->Name(), iter->id())));
				m_PropertyDataTechniqueChoice->Append(strPropertyDataTechniqueChoice);
			}

		}

		//Setup the Source String for PropertyData.source choices boxes
		{
			const Metadata::DataSourceDetails_sequence& cont(doc->Metadata()->DataSourceDetails());
			Metadata::DataSourceDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				wxArrayString strPropertyDataSourceChoice;
				strPropertyDataSourceChoice.Add(wxString(wxT("")));
				for (; iter != cont.end(); ++iter) strPropertyDataSourceChoice.Add(_std2wx(Label(iter->Name(), iter->id())));
				m_PropertyDataSourceChoice->Append(strPropertyDataSourceChoice);
			}

		}

		//Setup the Specimen String for PropertyData.Specimen choices boxes
		{
			const Metadata::SpecimenDetails_sequence& cont(doc->Metadata()->SpecimenDetails());
			Metadata::SpecimenDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				wxArrayString strPropertyDataSpecimenChoice;
				strPropertyDataSpecimenChoice.Add(wxString(wxT("")));
				for (; iter != cont.end(); ++iter) {
					::std::string name;
					if (iter->Name().present()) name = iter->Name().get();
					strPropertyDataSpecimenChoice.Add(_std2wx(Label(name, iter->id())));
				}
				m_PropertyDataSpecimenChoice->Append(strPropertyDataSpecimenChoice);
			}

		}

		//Setup the Test String for PropertyData.Test choices boxes
		{
			const Metadata::TestConditionDetails_sequence& cont(doc->Metadata()->TestConditionDetails());
			Metadata::TestConditionDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				wxArrayString strPropertyDataTestChoice;
				strPropertyDataTestChoice.Add(wxString(wxT("")));
				for (; iter != cont.end(); ++iter) strPropertyDataTestChoice.Add(_std2wx(Label("", iter->id())));
				m_PropertyDataTestChoice->Append(strPropertyDataTestChoice);
			}

		}
	}

	{
		::std::string label;
		const xml_schema::idref& idref(element->property());
		const PropertyDetails* prop = dynamic_cast<const PropertyDetails*>(&*idref);
		if (prop) m_PropertyDataPropertiesChoice->SetStringSelection(_std2wx(Label(prop->Name(), prop->id())));
		m_PropertyDataPropertyDetails_Display_GUI->Update(element);
	}

	{
		if (element->technique().present()) {
			::std::string label;
			const xml_schema::idref& idref(element->technique().get());
			const MeasurementTechniqueDetails* tech = dynamic_cast<const MeasurementTechniqueDetails*>(&*idref);
			if(tech) m_PropertyDataTechniqueChoice->SetStringSelection(_std2wx(Label(tech->Name(), tech->id())));

			m_PropertyDataMeasurementTechniqueDetails_Display_GUI->Update(element);
		}
	}
		
	{
		if (element->source().present()) {
			::std::string label;
			const xml_schema::idref& idref(element->source().get());
			const DataSourceDetails* src = dynamic_cast<const DataSourceDetails*>(&*idref);
			if(src) m_PropertyDataSourceChoice->SetStringSelection(_std2wx(Label(src->Name(), src->id())));

			m_PropertyDataDataSourceDetails_Display_GUI->Update(element);
		}
		
	}

	{
		if (element->specimen().present()) {
			const xml_schema::idref& idref(element->specimen().get());
			const SpecimenDetails* spec = dynamic_cast<const SpecimenDetails*>(&*idref);
			::std::string name;
			if (spec) {
				if (spec->Name().present()) name = spec->Name().get();
				m_PropertyDataSpecimenChoice->SetStringSelection(_std2wx(Label(name, spec->id())));
			}

			m_PropertyDataSpecimenDetails_Display_GUI->Update(element);

		}
	}

	{
		if (element->test().present()) {
			const xml_schema::idref& idref(element->test().get());
			const TestConditionDetails* test = dynamic_cast<const TestConditionDetails*>(&*idref);
			if(test) m_PropertyDataTestChoice->SetStringSelection(_std2wx(Label("", test->id())));

			m_PropertyDataTestConditionDetails_Display_GUI->Update(element);
		}
	}

	str.clear();
	str << _std2wx(element->delimiter());
	m_PropertyDataDelimiterTextCtrl->ChangeValue(str);

	str.clear();
	{
		const PropertyData::quote_optional& cont(element->quote());
		if (cont.present()) str << _std2wx((*cont));
		m_PropertyDataQuoteTextCtrl->ChangeValue(str);
	}

	Show(true);
}

::std::string PropertyData_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}
::std::string PropertyData_GUI_Base::LabelToId(::std::string label)
{
	::std::list<::std::string> result;
	return boost::split(result, label, boost::is_any_of(":")).back();
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId PropertyData_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	PropertyData& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	wxColour clr; clr.Set(0, 0, 0);
	if (Element.source().present()) {
		wxString strSource;
		strSource << _std2wx(Element.source().get());
		// if(!(strSource.Find(wxT("UNSOLVED"))==wxNOT_FOUND)) clr.Set(255,0,0);//red
		   //else if(!(strSource.Find(wxT("SOLVED"))==wxNOT_FOUND)) clr.Set(0,100,0);//green
		   //else if(!(strSource.Find(wxT("LINKED"))==wxNOT_FOUND)) clr.Set(0,0,255);//blue
		   //else if(!(strSource.Find(wxT("ASSUMPTION"))==wxNOT_FOUND)) clr.Set(0,255,255);//Lt. blue
		   //else if(!(strSource.Find(wxT("SEE-NOTES"))==wxNOT_FOUND)) clr.Set(255,0,255);//pink

		if (!(strSource.Find(wxT("METAMODEL-INTERPOLATION-UNSOLVED")) == wxNOT_FOUND)) clr.Set(wxT("#8B0000"));//dark red
		else if (!(strSource.Find(wxT("METAMODEL-INTERPOLATION-SOLVED")) == wxNOT_FOUND)) clr.Set(wxT("#006400"));//Dark Green
		else if (!(strSource.Find(wxT("UNSOLVED")) == wxNOT_FOUND))  clr.Set(wxT("#FF0000"));//red
		else if (!(strSource.Find(wxT("SOLVED")) == wxNOT_FOUND)) clr.Set(wxT("#008000"));//green
		else if (!(strSource.Find(wxT("LINKED")) == wxNOT_FOUND)) clr.Set(wxT("#0000FF"));//blue
		else if (!(strSource.Find(wxT("BROKEN-LINK")) == wxNOT_FOUND)) clr.Set(wxT("#FF00FF"));//pink
		else if (!(strSource.Find(wxT("SEE-NOTES")) == wxNOT_FOUND)) clr.Set(wxT("#A9A9A9"));//dark gray
		else if (!(strSource.Find(wxT("ASSUMPTION")) == wxNOT_FOUND)) clr.Set(wxT("#556B2F"));//dark olive green
	}

	::std::string label("PropertyData-");
	const xml_schema::idref& idref(Element.property());//get property for label
	const PropertyDetails* prop = dynamic_cast<const PropertyDetails*>(&*idref);
	if(prop) label.append(Label(prop->Name(), prop->id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	MatMLTreeCtrl->SetItemTextColour(CurrentId, clr);



	//MatML Attributes
	//Format
	//Property
	//Technique
	//Source
	//Specimen
	//test
	//delimiter
	//quote

	//Setup Elements Data
	if (Element.Data() != "")
		Data1_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Data(), wxTreeItemId());

	//Setup Element Uncertainty
	{
		 PropertyData::Uncertainty_sequence& cont(Element.Uncertainty());
		PropertyData::Uncertainty_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Uncertainty_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Qualifier
	{
		 PropertyData::Qualifier_sequence& cont = Element.Qualifier();
		PropertyData::Qualifier_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Qualifier_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}
	//Setup Element ParameterValue
	{
		 PropertyData::ParameterValue_sequence& cont(Element.ParameterValue());
		PropertyData::ParameterValue_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParameterValue_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		 PropertyData::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}


void PropertyData_GUI_Base::SetConnect()
{
	m_PropertyDataPropertiesChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataPropertiesChoice), NULL, this);
	m_PropertyDataTechniqueChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataTechniqueChoice), NULL, this);
	m_PropertyDataSourceChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataSourceChoice), NULL, this);
	m_PropertyDataSpecimenChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataSpecimenChoice), NULL, this);
	m_PropertyDataTestChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataTestChoice), NULL, this);
	m_PropertyDataDelimiterTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataDelimiterTextCtrl), NULL, this);
	m_PropertyDataDelimiterTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataDelimiterTextCtrl), NULL, this);
	m_PropertyDataQuoteTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataQuoteTextCtrl), NULL, this);
	m_PropertyDataQuoteTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PropertyData_GUI_Base::OnPropertyDataQuoteTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
PropertyData_GUI::PropertyData_GUI() : PropertyData_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
PropertyData_GUI::PropertyData_GUI(wxWindow* parent)
	: PropertyData_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
PropertyData_GUI::~PropertyData_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PropertyData_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void PropertyData_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void PropertyData_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void PropertyData_GUI::OnPropertyDataPropertiesChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {

			//Get wxWidget info and Store MatML Data
			PropertyData::property_type NewData(LabelToId(_wx2std(m_PropertyDataPropertiesChoice->GetStringSelection())).c_str());
			Element->property() = NewData;

			//Set up label string

			::std::string label("PropertyData-");

			xml_schema::idref& idref(Element->property());//get parameter for label
			const PropertyDetails* prop = dynamic_cast<const PropertyDetails*>(&*idref);
			label.append(Label(prop->Name(), prop->id()));

			m_MatMLTreeCtrl->SetItemText(itemId, _std2wx(label));//Set Label

			//Update the PropertyDetails Data on the panel
			m_PropertyDataPropertyDetails_Display_GUI->Update(Element);

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}


void PropertyData_GUI::OnPropertyDataTechniqueChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			//Get wxWidget info and Store MatML Data
			::std::string id(LabelToId(_wx2std(m_PropertyDataTechniqueChoice->GetStringSelection())));
			if (id.empty()) Element->technique().reset();//Empty data is still data so reset.
			else {
				PropertyData::technique_type NewData(id.c_str());
				Element->technique() = NewData;
			}

			//Set up label string

			//Update the MeasurementTechniqueDetails Data on the panel
			m_PropertyDataMeasurementTechniqueDetails_Display_GUI->Update(Element);
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnPropertyDataSourceChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			//Get wxWidget info and Store MatML Data
			::std::string id(LabelToId(_wx2std(m_PropertyDataSourceChoice->GetStringSelection())));
			if (id.empty()) Element->source().reset();//Empty data is still data so reset.
			else {
				PropertyData::source_type NewData(id.c_str());
				Element->source() = NewData;
			}

			m_PropertyDataDataSourceDetails_Display_GUI->Update(Element);
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnPropertyDataSpecimenChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			//Get wxWidget info and Store MatML Data
			::std::string id(LabelToId(_wx2std(m_PropertyDataSpecimenChoice->GetStringSelection())));
			if (id.empty()) Element->specimen().reset();//Empty data is still data so reset.
			else {
				PropertyData::specimen_type NewData(id.c_str());
				Element->specimen() = NewData;
			}

			//Update the SpecimenDetails Data on the panel
			m_PropertyDataSpecimenDetails_Display_GUI->Update(Element);
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnPropertyDataTestChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			//Get wxWidget info and Store MatML Data
			::std::string id(LabelToId(_wx2std(m_PropertyDataTestChoice->GetStringSelection())));
			if (id.empty()) Element->test().reset();//Empty data is still data so reset.
			else {
				PropertyData::test_type NewData(id.c_str());
				Element->test() = NewData;
			}

			//Update the TestConditionDetails Data on the panel
			m_PropertyDataTestConditionDetails_Display_GUI->Update(Element);
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnPropertyDataDelimiterTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_PropertyDataDelimiterTextCtrl->GetValue());
			PropertyData::delimiter_type NewData((const char*)str.mb_str(wxConvUTF8));
			(Element->delimiter()) = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnPropertyDataQuoteTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		PropertyData* const Element = boost::any_cast<PropertyData* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			PropertyData::quote_optional& cont(Element->quote());
			wxString str(m_PropertyDataQuoteTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			PropertyData::quote_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void PropertyData_GUI::OnInsertData(wxCommandEvent& event) {/*ON_PARENT_INSERT_CHILD(PropertyData,Data) //	This element wont exist on its own.*/ }
void PropertyData_GUI::OnInsertUncertainty(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(PropertyData, Uncertainty) }
void PropertyData_GUI::OnInsertQualifier(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(PropertyData, Qualifier) }
void PropertyData_GUI::OnInsertParameterValue(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(PropertyData, ParameterValue) }
void PropertyData_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(PropertyData, Notes) }

void PropertyData_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(PropertyData, Notes)}
void PropertyData_GUI::OnDeleteParameterValue(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(PropertyData, ParameterValue)}
void PropertyData_GUI::OnDeleteQualifier(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(PropertyData, Qualifier)}
void PropertyData_GUI::OnDeleteUncertainty(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(PropertyData, Uncertainty)}

void PropertyData_GUI::OnPasteData(wxCommandEvent& event) {/*ON_PARENT_PASTE_CHILD(PropertyData,Data) //	This element wont exist on its own.*/ }
void PropertyData_GUI::OnPasteUncertainty(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(PropertyData, Uncertainty) }
void PropertyData_GUI::OnPasteQualifier(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(PropertyData, Qualifier) }
void PropertyData_GUI::OnPasteParameterValue(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(PropertyData, ParameterValue) }
void PropertyData_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(PropertyData, Notes) }

void PropertyData_GUI::OnBumpDown(wxCommandEvent& event)
{
	// this->Freeze();

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	try {
		PropertyData* element = boost::any_cast<PropertyData*>(item->GetAnyMatMLDataPointer());
		try {
			BulkDetails* const elementParent = boost::any_cast<BulkDetails* const>(itemParent->GetAnyMatMLDataPointer());

			BulkDetails::PropertyData_sequence& cont(elementParent->PropertyData());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (BulkDetails::PropertyData_iterator iter = cont.begin(); iter != cont.end() - 1; ++iter) {
				if (element == static_cast<PropertyData*>(&*iter)) {//if the pointer are the same (aka same memory location
					PropertyData temp = *(iter);
					*(iter) = *(iter + 1);
					*(iter + 1) = temp;

					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter + 1), nextitemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(nextitemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Delete(nextitemId);

					// this->Thaw();

					return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}
		try {
			ComponentDetails* const elementParent = boost::any_cast<ComponentDetails* const>(itemParent->GetAnyMatMLDataPointer());

			ComponentDetails::PropertyData_sequence& cont(elementParent->PropertyData());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (ComponentDetails::PropertyData_iterator iter = cont.begin(); iter != cont.end() - 1; ++iter) {
				if (element == static_cast<PropertyData*>(&*iter)) {//if the pointer are the same (aka same memory location
					PropertyData temp = *(iter);
					*(iter) = *(iter + 1);
					*(iter + 1) = temp;

					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter + 1), nextitemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(nextitemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(itemId);
					m_MatMLTreeCtrl->Delete(nextitemId);

					// this->Thaw();

					return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}

	}
	catch (const boost::bad_any_cast&) { return; }
}
void PropertyData_GUI::OnBumpUp(wxCommandEvent& event)
{
	// this->Freeze();
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);
	MatMLTreeItemData* previtem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(previtemId));

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	try {
		PropertyData* element = boost::any_cast<PropertyData*>(item->GetAnyMatMLDataPointer());
		try {
			BulkDetails* const elementParent = boost::any_cast<BulkDetails* const>(itemParent->GetAnyMatMLDataPointer());

			BulkDetails::PropertyData_sequence& cont(elementParent->PropertyData());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (BulkDetails::PropertyData_iterator iter = cont.begin() + 1; iter != cont.end(); ++iter) {
				if (element == static_cast<PropertyData*>(&*iter)) {//if the pointer are the same (aka same memory location
					PropertyData temp = *(iter);
					*(iter) = *(iter - 1);
					*(iter - 1) = temp;

					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter - 1), previtemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(previtemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(previtemId);
					m_MatMLTreeCtrl->Delete(itemId);//perform last so selection bumps down

					/* this->Thaw();*/ return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}
		try {
			ComponentDetails* const elementParent = boost::any_cast<ComponentDetails* const>(itemParent->GetAnyMatMLDataPointer());

			ComponentDetails::PropertyData_sequence& cont(elementParent->PropertyData());
			if (cont.empty() || cont.size() < 2) {/* this->Thaw();*/ return; }

			for (ComponentDetails::PropertyData_iterator iter = cont.begin() + 1; iter != cont.end(); ++iter) {
				if (element == static_cast<PropertyData*>(&*iter)) {//if the pointer are the same (aka same memory location
					PropertyData temp = *(iter);
					*(iter) = *(iter - 1);
					*(iter - 1) = temp;

					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *iter, itemId);
					PropertyData_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, itemParentId, *(iter - 1), previtemId);

					m_MatMLTreeCtrl->SelectItem(m_MatMLTreeCtrl->GetNextSibling(previtemId));//setup so selection bumps down

					m_MatMLTreeCtrl->Delete(previtemId);
					m_MatMLTreeCtrl->Delete(itemId);//perform last so selection bumps down

					/* this->Thaw();*/ return;
				}
			}
		}
		catch (const boost::bad_any_cast&) {}
	}
	catch (const boost::bad_any_cast&) {/* this->Thaw();*/ return; }
}
