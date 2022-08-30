#include "BT_MatML_DimensionalDetails_GUI.h"

using namespace bellshire;

DimensionalDetails_GUI_Base::DimensionalDetails_GUI_Base()
	:m_GUI(nullptr)
{

}

DimensionalDetails_GUI_Base::DimensionalDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

DimensionalDetails_GUI_Base::~DimensionalDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the DimensionalDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="DimensionalDetailsNotebook"></param>
/// <param name="DimensionalDetailsPanel"></param>
/// <returns>bool</returns>
wxNotebook* DimensionalDetails_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* DimensionalDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DimensionalDetailsNotebook->Hide();
	DimensionalDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* DimensionalDetailsPanel = new wxScrolledWindow(DimensionalDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DimensionalDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer251321 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(DimensionalDetailsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer251321->Add(staticText4, 0, wxALL, 5);

	DimensionalDetailsPanel->SetSizer(bSizer251321);
	DimensionalDetailsPanel->Layout();
	bSizer251321->Fit(DimensionalDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(DimensionalDetailsNotebook,
		wxT("************** DimensionalDetails *************************\n\nThis element declares the content model for DimensionalDetails, which\ncontains a description of a dimensional characteristic (e.g. grain size,\nporosity, precipitate size and distribution, etc.) of the bulk material or\ncomponent and is composed of the following elements.\n\nName contains the name of the characteristic and has one optional\nattribute, authority, for identifying an authoritative source of\ndimensional characteristic names. Name must occur once and only once\nwithin the DimensionalDetails element.\n\nValue contains the value of the dimensional characteristic and has one\nrequired attribute, format, for indicating the format of the value. Value \nmust occur once and only once within the DimensionalDetails element.\n\nUnits contains the units for the value of the dimensional characteristic\nand must occur once and only once within the DimensionalDetails\nelement. For additional information, see the documentation for the Units\ntype.\n\nQualifier contains any qualifier pertinent to the value of the dimensional\ncharacteristic (e.g. \"min,\" \"max,\" etc.) and may occur once or not at all\nwithin the DimensionalDetails element.\n\nUncertainty contains the measurement uncertainty(ies) of the data in\nData and may occur zero or more times within the DimensionalDetails \nelement. For additional information, see the documentation for the\nUncertainty type.\n\nNotes contains any additional information concerning the dimensional\ncharacteristic and may occur once or not at all within the\nDimensionalDetails element.\t\t\t")
	);

	DimensionalDetailsNotebook->AddPage(DimensionalDetailsPanel, wxT("MatML Data."), true);
	DimensionalDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), false);

	return DimensionalDetailsNotebook;
}

void DimensionalDetails_GUI_Base::Update( DimensionalDetails* element)
{
	//Nothing to update

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId DimensionalDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	DimensionalDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("DimensionalDetails");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Element Value
	if (Element.Value() != "")
		Value_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Value(), wxTreeItemId());

	//Setup Element Units
	Units_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Units(), wxTreeItemId());

	//Setup Element Qualifier
	{
		DimensionalDetails::Qualifier_optional& cont(Element.Qualifier());
		if (cont.present())
			Qualifier_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	//Setup Element Uncertainty
	{
		DimensionalDetails::Uncertainty_sequence& cont(Element.Uncertainty());
		DimensionalDetails::Uncertainty_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Uncertainty_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Element Notes
	{
		DimensionalDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}
	return CurrentId;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
DimensionalDetails_GUI::DimensionalDetails_GUI() 
	: DimensionalDetails_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
DimensionalDetails_GUI::DimensionalDetails_GUI(wxWindow* parent)
	: DimensionalDetails_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
DimensionalDetails_GUI::~DimensionalDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DimensionalDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DimensionalDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void DimensionalDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void DimensionalDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(DimensionalDetails, Name) }
void DimensionalDetails_GUI::OnInsertValue(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(DimensionalDetails, Value) }
void DimensionalDetails_GUI::OnInsertUnits(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(DimensionalDetails, Units) }
void DimensionalDetails_GUI::OnInsertQualifier(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(DimensionalDetails, Qualifier) }
void DimensionalDetails_GUI::OnInsertUncertainty(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(DimensionalDetails, Uncertainty) }
void DimensionalDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(DimensionalDetails, Notes) }

void DimensionalDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(DimensionalDetails, Notes)}
void DimensionalDetails_GUI::OnDeleteQualifier(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(DimensionalDetails, Qualifier)}
void DimensionalDetails_GUI::OnDeleteUncertainty(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(DimensionalDetails, Uncertainty)}
void DimensionalDetails_GUI::OnDeleteUnits(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(DimensionalDetails, Units)}
void DimensionalDetails_GUI::OnDeleteValue(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(DimensionalDetails, Value)}

void DimensionalDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(DimensionalDetails, Name) }
void DimensionalDetails_GUI::OnPasteValue(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(DimensionalDetails, Value) }
void DimensionalDetails_GUI::OnPasteUnits(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(DimensionalDetails, Units) }
void DimensionalDetails_GUI::OnPasteQualifier(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(DimensionalDetails, Qualifier) }
void DimensionalDetails_GUI::OnPasteUncertainty(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(DimensionalDetails, Uncertainty) }
void DimensionalDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(DimensionalDetails, Notes) }


void DimensionalDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Characterization*)) {
			DimensionalDetails* element = boost::any_cast<DimensionalDetails*>(anyptr);
			Characterization* elementParent = boost::any_cast<Characterization*>(anyptrparent);

			auto& cont = elementParent->DimensionalDetails();
			std::pair<DimensionalDetails*, DimensionalDetails*> data(MatMLFindAndBumpDown(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<DimensionalDetails_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}

void DimensionalDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Characterization*)) {
			DimensionalDetails* element = boost::any_cast<DimensionalDetails*>(anyptr);
			Characterization* elementParent = boost::any_cast<Characterization*>(anyptrparent);

			auto& cont = elementParent->DimensionalDetails();
			std::pair<DimensionalDetails*, DimensionalDetails*> data(MatMLFindAndBumpUp(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<DimensionalDetails_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}
