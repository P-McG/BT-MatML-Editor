#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_ParameterValue_GUI.h"

using namespace bellshire;

ParameterValue_GUI_Base::ParameterValue_GUI_Base()
	:m_ParameterValueParameterChoice(nullptr),
	m_ParameterValueFormatChoice(nullptr),
	m_ParameterValueParameterDetails_Display_GUI(nullptr)
{

}

ParameterValue_GUI_Base::ParameterValue_GUI_Base(wxWindow* parent)
	:m_ParameterValueParameterChoice(nullptr),
	m_ParameterValueFormatChoice(nullptr),
	m_ParameterValueParameterDetails_Display_GUI(nullptr)
{
	m_GUI = Create(parent, m_ParameterValueParameterChoice, m_ParameterValueFormatChoice, m_ParameterValueParameterDetails_Display_GUI);
}

ParameterValue_GUI_Base::~ParameterValue_GUI_Base() {
	/*parent will destroy Ctrl or window */
	delete m_ParameterValueParameterDetails_Display_GUI;// neither a Ctrl or window
}

wxChoice* ParameterValue_GUI_Base::GetParameterValueParameterChoice()
{
	return m_ParameterValueParameterChoice;
}

wxChoice* ParameterValue_GUI_Base::GetParameterValueFormatChoice()
{
	return m_ParameterValueFormatChoice;
}

ParameterDetails_Display_GUI* ParameterValue_GUI_Base::GetParameterValueParameterDetails_Display_GUI()
{
	return m_ParameterValueParameterDetails_Display_GUI;
}

/// <summary>
/// Create the GUI for the ParameterValue MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ParameterValueParameterChoice"></param>
/// <param name="ParameterValueFormatChoice"></param>
/// <returns>bool</returns>
wxNotebook* ParameterValue_GUI_Base::Create(wxWindow* parent, 
	wxChoice*& ParameterValueParameterChoice, 
	wxChoice*& ParameterValueFormatChoice, 
	ParameterDetails_Display_GUI*& ParameterValueParameterDetails_Display_GUI
)
{

	wxNotebook* ParameterValueNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ParameterValueNotebook->Hide();
	ParameterValueNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ParameterValuePanel(CreateParameterValuePanel(ParameterValueNotebook,
		ParameterValueParameterChoice,
		ParameterValueFormatChoice,
		ParameterValueParameterDetails_Display_GUI
	));

	MatMLInfo_GUI matMLInfo_GUI(ParameterValueNotebook,
		wxT("*********** ParameterValue *************************\n\nThis element declares the content model for ParameterValue, which\ncontains the value of a parameter. ParameterValue has two required\nattributes.\n\nThe first attribute, parameter, references an id attribute specified in a\nParameterDetails element so that the descriptive details of the parameter\nare tied to the value.\n\nThe second attribute, format, indicates the format of the value. If used, \n\"mixed\" indicates that the not all of the parameter values are of the same\ntype (e.g. a \"No Break\" value for an otherwise numeric set of Charpy \nIzod test results). If used, then the \"format\" attribute on each \"Data\" \nitem should be individually set.\n\nParameterValue is composed of the following elements.\n\nData contains the property data and has one required attribute,\nformat [NOT ALLOWED IN MATML 3.1], for indicating the format of the data.\nData must occur once and only once within the ParameterValue element.\n\nQualifier contains any qualifier(s) pertinent to the data in \nParameterValue(e.g. \"min,\" \"max,\" etc.) and may occur zero or more times \nwithin the PropertyData element.\n\nUncertainty contains the measurement uncertainty(ies) of the data in\nParameterValue and may occur once [MatML 3.1 schema set as many] or not at all within the ParameterValue\nelement. For additional information, see the documentation for the Uncertainty\n element.\n\nNotes contains any additional information concerning the property\ndata and may occur once or not at all within the PropertyData element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ParameterValueNotebook->AddPage(ParameterValuePanel, wxT("MatML Data."), b_dflt);
	ParameterValueNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ParameterValueNotebook;
}

wxWindow* ParameterValue_GUI_Base::CreateParameterValuePanel(wxWindow* parent,
	wxChoice*& ParameterValueParameterChoice,
	wxChoice*& ParameterValueFormatChoice,
	ParameterDetails_Display_GUI*& ParameterValueParameterDetails_Display_GUI
)
{
	wxScrolledWindow* ParameterValuePanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ParameterValuePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer69 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer138 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer138->AddGrowableCol(0);
	fgSizer138->AddGrowableRow(1);
	fgSizer138->SetFlexibleDirection(wxBOTH);
	fgSizer138->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxFlexGridSizer* fgSizer17 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer17->AddGrowableCol(1);
	fgSizer17->AddGrowableRow(1);
	fgSizer17->SetFlexibleDirection(wxBOTH);
	fgSizer17->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText13 = new wxStaticText(ParameterValuePanel, wxID_ANY, wxT("Parameter"), wxDefaultPosition, wxDefaultSize, 0);
	staticText13->Wrap(-1);
	fgSizer17->Add(staticText13, 0, wxALL, 5);

	wxArrayString ParameterValueParameterChoiceChoices;
	ParameterValueParameterChoice = new wxChoice(ParameterValuePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ParameterValueParameterChoiceChoices, 0);
	ParameterValueParameterChoice->SetSelection(0);
	fgSizer17->Add(ParameterValueParameterChoice, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText1412 = new wxStaticText(ParameterValuePanel, wxID_ANY, wxT("Parameter Value Format"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1412->Wrap(-1);
	fgSizer17->Add(staticText1412, 0, wxALL, 5);

	wxString ParameterValueFormatChoiceChoices[] = { wxT("float"), wxT("integer"), wxT("string"), wxT("exponential"), wxT("mixed") };
	int ParameterValueFormatChoiceNChoices = sizeof(ParameterValueFormatChoiceChoices) / sizeof(wxString);
	ParameterValueFormatChoice = new wxChoice(ParameterValuePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ParameterValueFormatChoiceNChoices, ParameterValueFormatChoiceChoices, 0);
	ParameterValueFormatChoice->SetSelection(0);
	fgSizer17->Add(ParameterValueFormatChoice, 0, wxALL | wxEXPAND, 5);

	fgSizer138->Add(fgSizer17, 1, wxEXPAND, 5);

	//Display Notebook
	wxNotebook* notebook6 = new wxNotebook(ParameterValuePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	//Display the Details
	ParameterValueParameterDetails_Display_GUI = new ParameterDetails_Display_GUI(notebook6);
	notebook6->AddPage(ParameterValueParameterDetails_Display_GUI->get(), wxT("Parameter"), false);

	fgSizer138->Add(notebook6, 1, wxEXPAND | wxALL, 5);

	bSizer69->Add(fgSizer138, 1, wxEXPAND | wxALL, 5);

	ParameterValuePanel->SetSizer(bSizer69);
	ParameterValuePanel->Layout();
	bSizer69->Fit(ParameterValuePanel);

	return ParameterValuePanel;
}

void ParameterValue_GUI_Base::Update( const observer_ptr<ParameterValue> element, const observer_ptr<MatML_Doc> doc)
{
	if (element && doc) {

		wxString str;

		//Setup the id String for PropertyData.property choices boxes
		{
			const Metadata::ParameterDetails_sequence& cont(doc->Metadata()->ParameterDetails());
			Metadata::ParameterDetails_const_iterator iter(cont.begin());
			if (!cont.empty()) {
				m_ParameterValueParameterChoice->Clear();

				wxArrayString strParameterValueParameterChoice;
				for (; iter != cont.end(); ++iter)
					strParameterValueParameterChoice.Add(_std2wx(Label(iter->Name(), iter->id())));

				m_ParameterValueParameterChoice->Append(strParameterValueParameterChoice);
			}
		}

		//Set ParameterValue choice box
		::std::string label;
		const xml_schema::idref& idref(element->parameter());
		const ParameterDetails* para = dynamic_cast<const ParameterDetails*>(&*idref);
		if (para)
			m_ParameterValueParameterChoice->SetStringSelection(_std2wx(Label(para->Name(), para->id())));

		str.clear();
		str << _std2wx(std::string(DataFormat::_xsd_DataFormat_literals_[int(element->format())]));
		m_ParameterValueFormatChoice->SetStringSelection(str);

		m_ParameterValueParameterDetails_Display_GUI->Update(element);

		ShowGUI(true);
	}
}

::std::string ParameterValue_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
    if (!name.empty() && !id.empty()) label.append( " :");
	if (!id.empty()) label.append(id);
	return label;
}
::std::string ParameterValue_GUI_Base::LabelToId(::std::string label)
{
	::std::list<::std::string> result;
	return boost::split(result, label, boost::is_any_of(":")).back();
}

wxString ParameterValue_GUI_Base::GetTreeLabel(const observer_ptr<ParameterValue> element)
{
	::std::string label("ParameterValue-");

	if (element) {
		const xml_schema::idref& idref(element->parameter());//get parameter for label
		const ParameterDetails* pram = dynamic_cast<const ParameterDetails*>(&*idref);
		if (pram) label.append(Label(pram->Name(), pram->id()));
	}

	return label;
}


void ParameterValue_GUI_Base::SetConnect()
{
	m_ParameterValueParameterChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(ParameterValue_GUI_Base::OnParameterValueParameterChoice), NULL, this);
	m_ParameterValueFormatChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(ParameterValue_GUI_Base::OnParameterValueFormatChoice), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
ParameterValue_GUI::ParameterValue_GUI() : ParameterValue_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ParameterValue_GUI::ParameterValue_GUI(wxWindow* parent)
	: ParameterValue_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ParameterValue_GUI::~ParameterValue_GUI() 
{
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* ParameterValue_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any ParameterValue_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParameterValue_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParameterValue_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ParameterValue_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ParameterValue_GUI::OnParameterValueParameterChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		auto element_observer{ boost::any_cast<observer_ptr<ParameterValue>>(item->GetAnyMatMLDataPointer())};
		if (element_observer) {

			//Get wxWidget info and Store MatML Data
			ParameterValue::parameter_type NewData(LabelToId(_wx2std(m_ParameterValueParameterChoice->GetStringSelection())).c_str());
			element_observer->parameter() = NewData;

			//Set up label string

			::std::string label("ParameterValue-");

			xml_schema::idref& idref(element_observer->parameter());//get parameter for label
			const ParameterDetails* pram = dynamic_cast<const ParameterDetails*>(&*idref);
			label.append(Label(pram->Name(), pram->id()));
			
			m_MatMLTreeCtrl->SetItemText(itemId, _std2wx(label));//Set Label

			m_ParameterValueParameterDetails_Display_GUI->Update(element_observer);

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void ParameterValue_GUI::OnParameterValueFormatChoice(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		ParameterValue* const Element = boost::any_cast<ParameterValue* const>(item->GetAnyMatMLDataPointer());  
		if (Element != 0) {
			wxString str(m_ParameterValueFormatChoice->GetStringSelection());
			ParameterValue::format_type NewData((const char*)str.mb_str(wxConvUTF8));
			Element->format() = NewData;

			//update label


			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void ParameterValue_GUI::OnInsertData(wxCommandEvent& event) {/*ON_PARENT_INSERT_CHILD(ParameterValue,Data) //This element wont exist on its own*/ }
void ParameterValue_GUI::OnInsertUncertainty(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ParameterValue, Uncertainty) }
void ParameterValue_GUI::OnInsertQualifier(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ParameterValue, Qualifier) }
void ParameterValue_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ParameterValue, Notes) }

void ParameterValue_GUI::OnDeleteQualifier(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ParameterValue, Qualifier)}
void ParameterValue_GUI::OnDeleteUncertainty(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ParameterValue, Uncertainty)}
void ParameterValue_GUI::OnDeleteNotes(wxCommandEvent& event) { ON_PARENT_DELETE_CONT_CHILD(ParameterValue, Notes) }

void ParameterValue_GUI::OnPasteData(wxCommandEvent& event) {/*ON_PARENT_PASTE_CHILD(ParameterValue,Data) //This element wont exist on its own*/ }
void ParameterValue_GUI::OnPasteUncertainty(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ParameterValue, Uncertainty) }
void ParameterValue_GUI::OnPasteQualifier(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ParameterValue, Qualifier) }
void ParameterValue_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ParameterValue, Notes) }


void ParameterValue_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< ParameterValue,
		ProcessingDetails,
		ProcessingDetails::ParameterValue_sequence,
		ParameterValue_GUI,
		&ProcessingDetails::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< ParameterValue,
		PropertyData,
		PropertyData::ParameterValue_sequence,
		ParameterValue_GUI,
		&PropertyData::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< ParameterValue,
		TestConditionDetails,
		TestConditionDetails::ParameterValue_sequence,
		ParameterValue_GUI,
		&TestConditionDetails::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void ParameterValue_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< ParameterValue,
		ProcessingDetails,
		ProcessingDetails::ParameterValue_sequence,
		ParameterValue_GUI,
		&ProcessingDetails::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< ParameterValue,
		PropertyData,
		PropertyData::ParameterValue_sequence,
		ParameterValue_GUI,
		&PropertyData::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< ParameterValue,
		TestConditionDetails,
		TestConditionDetails::ParameterValue_sequence,
		ParameterValue_GUI,
		&TestConditionDetails::ParameterValue
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

