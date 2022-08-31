#include <wx/config.h>
#include "BT_MatML_Uncertainty_GUI.h"

using namespace bellshire;

Uncertainty_GUI_Base::Uncertainty_GUI_Base()
	:m_GUI(nullptr), 
	m_UncertaintyDistributionTypeTextCtrl(nullptr),
	m_UncertaintyNum_Std_DevTextCtrl(nullptr),
	m_UncertaintyPercentileTextCtrl(nullptr), 
	m_UncertaintyConfidenceLevelTextCtrl(nullptr),
	m_UncertaintyScaleChoice(nullptr)
{

}

Uncertainty_GUI_Base::Uncertainty_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_UncertaintyDistributionTypeTextCtrl(nullptr),
	m_UncertaintyNum_Std_DevTextCtrl(nullptr),
	m_UncertaintyPercentileTextCtrl(nullptr),
	m_UncertaintyConfidenceLevelTextCtrl(nullptr),
	m_UncertaintyScaleChoice(nullptr)
{
	m_GUI = Create(parent, 
	m_UncertaintyDistributionTypeTextCtrl,
	m_UncertaintyNum_Std_DevTextCtrl,
	m_UncertaintyPercentileTextCtrl,
	m_UncertaintyConfidenceLevelTextCtrl,
	m_UncertaintyScaleChoice);
}

Uncertainty_GUI_Base::~Uncertainty_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Uncertainty MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="UncertaintyNotebook"></param>
/// <param name="UncertaintyPanel"></param>
/// <param name="UncertaintyDistributionTypeTextCtrl"></param>
/// <param name="UncertaintyNum_Std_DevTextCtrl"></param>
/// <param name="UncertaintyPercentileTextCtrl"></param>
/// <param name="UncertaintyConfidenceLevelTextCtrl"></param>
/// <param name="UncertaintyScaleChoice"></param>
/// <returns>bool</returns>
wxNotebook* Uncertainty_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& UncertaintyDistributionTypeTextCtrl, wxTextCtrl*& UncertaintyNum_Std_DevTextCtrl, wxTextCtrl*& UncertaintyPercentileTextCtrl, wxTextCtrl*& UncertaintyConfidenceLevelTextCtrl, wxChoice*& UncertaintyScaleChoice)
{

	wxNotebook* UncertaintyNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	UncertaintyNotebook->Hide();

	wxScrolledWindow* UncertaintyPanel = new wxScrolledWindow(UncertaintyNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	UncertaintyPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer84 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer24 = new wxFlexGridSizer(5, 2, 0, 0);
	fgSizer24->AddGrowableCol(1);
	fgSizer24->SetFlexibleDirection(wxBOTH);
	fgSizer24->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText29 = new wxStaticText(UncertaintyPanel, wxID_ANY, wxT("Distribution Type"), wxDefaultPosition, wxDefaultSize, 0);
	staticText29->Wrap(-1);
	fgSizer24->Add(staticText29, 0, wxALL, 5);

	UncertaintyDistributionTypeTextCtrl = new wxTextCtrl(UncertaintyPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer24->Add(UncertaintyDistributionTypeTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText30 = new wxStaticText(UncertaintyPanel, wxID_ANY, wxT("Num_Std_Dev"), wxDefaultPosition, wxDefaultSize, 0);
	staticText30->Wrap(-1);
	fgSizer24->Add(staticText30, 0, wxALL, 5);

	UncertaintyNum_Std_DevTextCtrl = new wxTextCtrl(UncertaintyPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer24->Add(UncertaintyNum_Std_DevTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText31 = new wxStaticText(UncertaintyPanel, wxID_ANY, wxT("Percentile"), wxDefaultPosition, wxDefaultSize, 0);
	staticText31->Wrap(-1);
	fgSizer24->Add(staticText31, 0, wxALL, 5);

	UncertaintyPercentileTextCtrl = new wxTextCtrl(UncertaintyPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer24->Add(UncertaintyPercentileTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText32 = new wxStaticText(UncertaintyPanel, wxID_ANY, wxT("ConfidenceLevel"), wxDefaultPosition, wxDefaultSize, 0);
	staticText32->Wrap(-1);
	fgSizer24->Add(staticText32, 0, wxALL, 5);

	UncertaintyConfidenceLevelTextCtrl = new wxTextCtrl(UncertaintyPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer24->Add(UncertaintyConfidenceLevelTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer84->Add(fgSizer24, 1, wxEXPAND, 5);

	UncertaintyPanel->SetSizer(bSizer84);
	UncertaintyPanel->Layout();
	bSizer84->Fit(UncertaintyPanel);

	MatMLInfo_GUI matMLInfo_GUI(UncertaintyNotebook,
		wxT("*********** Uncertainty *************************\n\nTHE DOCUMENTATION IN THE SCHEMA IS OUT DATED TO\nTO THE SCHEMA CODE. BELOW IS THE CORRECTED DISCRIPTION\nAND BELOW THAT THE ORIGINAL \"OFFICIAL\" SCHEMA \nDOCUMENTATION.\n------------------------------------------------------------------------\n\nThis element declares the content model for Uncertainty, which\ncontains a description of the measurement uncertainty of the data.\n\t\t\t\nUncertainty has four optional attributes:\n\t\t\t\nDistributionType attribute is the name of the distribution. Default Normal/Gaussian\n\nNum_Std_Dev attribute is a value (default 2.0) of how much variation or \"dispersion\"\nexists in the data from the average (mean, or expected value). An uncertainty \n2 standard deviations below the mean for a normally distributed dataset \nwould have a uncertainty percentile of 5% and 2 standard deviations above\n the mean would be 95%.\n\nPercentile attribute is a value indicating the percentage of the data population\nthat have values less than or equal to that expressed by the Uncertainty\nvalue. If Percentile is not given then Value is interpreted as being an\nequal and unspecified deviation above and below the data/value(s).\n\nConfidenceLevel attribute is a value refers to the percentage of all possible\nsamples that can be expected to include the true population parameter. For\nexample, suppose all possible samples were selected from the same\npopulation, and a confidence interval were computed for each sample. A\n0.95(95%) confidence level implies that 0.95(95%) of the confidence intervals would\ninclude the true population parameter.\n\nUncertainty is composed of the following required elements.\n\nValue contains the value of the uncertainty and has one required\nattribute, format, for indicating the format of the value. Value must occur \nonce and only once within the Uncertainty element. \n\nUnits (or optionally Unitless) contains the units for the value of the \nuncertainty and must occur once and only once within the Uncertainty\nelement. For additional information, see the documentation for the Units element.\n\nUncertainty is composed of the following optional elements.\n\nNotes contains any additional information concerning the uncertainty,\nsuch as a description of the evaluation of the uncertainty, and may\noccur once or not at all within the Uncertainty element.\t\n\nScale contains the value for either linear or exponential scale. Default is linear,\t\t\n\n\n\n------------------------------------------------------------------------\nORIGINAL \"OFFICIAL\" SCHEMA DOCUMENTATION.\n\nThis element declares the content model for Uncertainty, which\ncontains a description of the measurement uncertainty of the data.\n\t\t\t\nUncertainty has 1 optional attributes:\n\t\t\t\nName is a description of the nature of the uncertainty value, for example \n'6 sigma', 'Gaussian' or '2 std dev.'\n\t\t\nUncertainty is composed of the following elements.\n\nValue contains the value of the uncertainty and has one required\nattribute, format, for indicating the format of the value. Value must occur \nonce and only once within the Uncertainty element. \n\nUnits contains the units for the value of the uncertainty and must occur\nonce and only once within the Uncertainty element. For additional\ninformation, see the documentation for the Units element.\n\nPercentile is a value indicating the percentage of the data population\nthat have values less than or equal to that expressed by the Uncertainty\nvalue. Percentile can occur zero or more times. If Percentile is not given\nthen Value is interpreted as being an equal and unspecified deviation \nabove and below the Property value(s).\n\t\t\t\nAn uncertainty of 2 standard deviations below the mean for a \nnormally distributed dataset would have a uncertainty percentile of 5%,\nand 2 standard deviations above the mean would be 95%.\n\t\t\nNotes contains any additional information concerning the uncertainty,\nsuch as a description of the evaluation of the uncertainty, and may\noccur once or not at all within the Uncertainty element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	UncertaintyNotebook->AddPage(UncertaintyPanel, wxT("MatML Data"), b_dflt);
	UncertaintyNotebook->AddPage(matMLInfo_GUI.get(), wxT("Editor Info."), !b_dflt);

	return UncertaintyNotebook;
}

void Uncertainty_GUI_Base::Update( Uncertainty* element)
{
	wxString str;

	str << _std2wx(element->DistributionType());
	m_UncertaintyDistributionTypeTextCtrl->ChangeValue(str);

	str.clear();
	str << (float)element->Num_Std_Dev();
	m_UncertaintyNum_Std_DevTextCtrl->ChangeValue(str);

	str.clear();
	{
		const Uncertainty::Percentile_optional& cont(element->Percentile());
		if (cont.present()) str << (float)(*cont);
		m_UncertaintyPercentileTextCtrl->ChangeValue(str);
	}

	str.clear();
	{
		const Uncertainty::ConfidenceLevel_optional& cont(element->ConfidenceLevel());
		if (cont.present()) str << (float)(*cont);
		m_UncertaintyConfidenceLevelTextCtrl->ChangeValue(str);
	}

	//str.clear();
	//{
	//	if (element->Scale().present()) str << _std2wx(::string(Scale::_xsd_Scale_literals_[element->Scale().get()]));
	//	m_UncertaintyScaleChoice->SetStringSelection(str);
	//}

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Uncertainty_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	Uncertainty& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Uncertainty");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//DistributionType
	//Num_Std_Dev
	//Percentile
	//ConfidenceLevel

	//Setup Elements Value
	if (Element.Value() != "")
		Value_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Value(), wxTreeItemId());

	//Setup Elements Units
	{
		 Uncertainty::Units_optional& cont(Element.Units());
		if (cont.present())
			Units_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Unitless
	{
		 Uncertainty::Unitless_optional& cont(Element.Unitless());
		if (cont.present())
			Unitless_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Scale
	{
		 Uncertainty::Scale_optional& cont(Element.Scale());
		if (cont.present())
			Scale_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		 Uncertainty::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}

void Uncertainty_GUI_Base::SetConnect()
{
	m_UncertaintyDistributionTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyDistributionTypeTextCtrl), NULL, this);
	m_UncertaintyDistributionTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyDistributionTypeTextCtrl), NULL, this);
	m_UncertaintyNum_Std_DevTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyNum_Std_DevTextCtrl), NULL, this);
	m_UncertaintyNum_Std_DevTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyNum_Std_DevTextCtrl), NULL, this);
	m_UncertaintyPercentileTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyPercentileTextCtrl), NULL, this);
	m_UncertaintyPercentileTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyPercentileTextCtrl), NULL, this);
	m_UncertaintyConfidenceLevelTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyConfidenceLevelTextCtrl), NULL, this);
	m_UncertaintyConfidenceLevelTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Uncertainty_GUI_Base::OnUncertaintyConfidenceLevelTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Uncertainty_GUI::Uncertainty_GUI() : Uncertainty_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Uncertainty_GUI::Uncertainty_GUI(wxWindow* parent)
	: Uncertainty_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Uncertainty_GUI::~Uncertainty_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Uncertainty_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Uncertainty_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Uncertainty_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Uncertainty_GUI::OnUncertaintyDistributionTypeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Uncertainty* const Element = boost::any_cast<Uncertainty* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_UncertaintyDistributionTypeTextCtrl->GetValue());
			Uncertainty::DistributionType_type NewData((const char*)str.mb_str(wxConvUTF8));
			Element->DistributionType() = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Uncertainty_GUI::OnUncertaintyNum_Std_DevTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Uncertainty* const Element = boost::any_cast<Uncertainty* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_UncertaintyNum_Std_DevTextCtrl->GetValue());
			double NumData; str.ToDouble(&NumData);
			Uncertainty::Num_Std_Dev_type NewData(NumData);
			Element->Num_Std_Dev() = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Uncertainty_GUI::OnUncertaintyPercentileTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Uncertainty* const Element = boost::any_cast<Uncertainty* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Uncertainty::Percentile_optional& cont(Element->Percentile());
			wxString str(m_UncertaintyPercentileTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			double NumData; str.ToDouble(&NumData);
			Uncertainty::Percentile_type NewData(NumData);
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Uncertainty_GUI::OnUncertaintyConfidenceLevelTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Uncertainty* const Element = boost::any_cast<Uncertainty* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Uncertainty::ConfidenceLevel_optional& cont(Element->ConfidenceLevel());
			wxString str(m_UncertaintyConfidenceLevelTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			double NumData; str.ToDouble(&NumData);
			Uncertainty::ConfidenceLevel_type NewData(NumData);
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void Uncertainty_GUI::OnInsertValue(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Uncertainty, Value) }
void Uncertainty_GUI::OnInsertUnits(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Uncertainty, Units) }
void Uncertainty_GUI::OnInsertUnitless(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Uncertainty, Unitless) }
void Uncertainty_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Uncertainty, Notes) }
void Uncertainty_GUI::OnInsertScale(wxCommandEvent& event) {ON_PARENT_INSERT_CONT_CHILD(Uncertainty,Scale) }

void Uncertainty_GUI::OnDeleteUnitless(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Uncertainty, Unitless)}
void Uncertainty_GUI::OnDeleteUnits(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Uncertainty, Units)}
void Uncertainty_GUI::OnDeleteValue(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(Uncertainty, Value)}
void Uncertainty_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Uncertainty, Notes)}
void Uncertainty_GUI::OnDeleteScale(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Uncertainty, Scale)}

void Uncertainty_GUI::OnPasteValue(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(Uncertainty, Value) }
void Uncertainty_GUI::OnPasteUnits(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Uncertainty, Units) }
void Uncertainty_GUI::OnPasteUnitless(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Uncertainty, Unitless) }
void Uncertainty_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Uncertainty, Notes) }
void Uncertainty_GUI::OnPasteScale(wxCommandEvent& event) {ON_PARENT_PASTE_CONT_CHILD(Uncertainty,Scale) }

void Uncertainty_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Uncertainty,
		Concentration,
		Concentration::Uncertainty_sequence,
		Uncertainty_GUI,
		&Concentration::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< Uncertainty,
		DimensionalDetails,
		DimensionalDetails::Uncertainty_sequence,
		Uncertainty_GUI,
		&DimensionalDetails::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< Uncertainty,
		ParameterValue,
		ParameterValue::Uncertainty_sequence,
		Uncertainty_GUI,
		&ParameterValue::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< Uncertainty,
		PropertyData,
		PropertyData::Uncertainty_sequence,
		Uncertainty_GUI,
		&PropertyData::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Uncertainty_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Uncertainty,
		Concentration,
		Concentration::Uncertainty_sequence,
		Uncertainty_GUI,
		&Concentration::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< Uncertainty,
		DimensionalDetails,
		DimensionalDetails::Uncertainty_sequence,
		Uncertainty_GUI,
		&DimensionalDetails::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< Uncertainty,
		ParameterValue,
		ParameterValue::Uncertainty_sequence,
		Uncertainty_GUI,
		&ParameterValue::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< Uncertainty,
		PropertyData,
		PropertyData::Uncertainty_sequence,
		Uncertainty_GUI,
		&PropertyData::Uncertainty
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

