#include <wx/config.h>
#include "BT_MatML_MeasurementTechniqueDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

MeasurementTechniqueDetails_GUI_Base::MeasurementTechniqueDetails_GUI_Base()
	:m_GUI(nullptr),
	m_MeasurementTechniqueDetails_ID_GUI(nullptr)
{

}

MeasurementTechniqueDetails_GUI_Base::MeasurementTechniqueDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_MeasurementTechniqueDetails_ID_GUI(nullptr)
{
	m_GUI = Create(parent, m_MeasurementTechniqueDetails_ID_GUI);
}

MeasurementTechniqueDetails_GUI_Base::~MeasurementTechniqueDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_MeasurementTechniqueDetails_ID_GUI;//this is neither a window nor a ctrl.
}


/// <summary>
/// Create the GUI for the MeasurementTechniqueDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="MeasurementTechniqueDetails_ID_GUI"></param>
/// <returns>bool</returns>
wxNotebook* MeasurementTechniqueDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& MeasurementTechniqueDetails_ID_GUI)
{
	wxNotebook* MeasurementTechniqueDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	MeasurementTechniqueDetailsNotebook->Hide();
	MeasurementTechniqueDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* MeasurementTechniqueDetailsPanel = new wxScrolledWindow(MeasurementTechniqueDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	MeasurementTechniqueDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	MeasurementTechniqueDetails_ID_GUI = new ID_GUI(MeasurementTechniqueDetailsPanel);
	bSizer1->Add(MeasurementTechniqueDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	MeasurementTechniqueDetailsPanel->SetSizer(bSizer1);
	MeasurementTechniqueDetailsPanel->Layout();
	bSizer1->Fit(MeasurementTechniqueDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(MeasurementTechniqueDetailsNotebook,
		wxT("******** MeasurementTechniqueDetails *************************\n\nThis element declares the content model for MeasurementTechniqueDetails,\n which contains a description of a measurement technique referenced by the PropertyData\n element. MeasurementTechniqueDetails has one required\nattribute, id, which may be arbitrarily assigned but must be unique among\nid attributes assigned elsewhere in a MatML document.\nMeasurementTechniqueDetails is composed of the following elements.\n\nName contains the name of the measurement technique and has one\noptional attribute, authority, for identifying an authoritative source of\nmeasurement techniques. Name must occur once and only once within the MeasurementTechniqueDetails element.\n\nNotes contains any additional information concerning the measurement\ntechnique, such as a description of the technique, and may occur once or\nnot at all within the MeasurementTechniqueDetails element.\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	MeasurementTechniqueDetailsNotebook->AddPage(MeasurementTechniqueDetailsPanel, wxT("MatML Data."), b_dflt);
	MeasurementTechniqueDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return MeasurementTechniqueDetailsNotebook;
}

void MeasurementTechniqueDetails_GUI_Base::Update( MeasurementTechniqueDetails* element)
{
	m_MeasurementTechniqueDetails_ID_GUI->Update(element);

	Show(true);
}

::std::string MeasurementTechniqueDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId MeasurementTechniqueDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId,
	MeasurementTechniqueDetails& Element,
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("MeasurementTechniqueDetails-");
	label.append(Label(Element.Name(), Element.id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Notes
	{
		MeasurementTechniqueDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}


void MeasurementTechniqueDetails_GUI_Base::SetConnect()
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
MeasurementTechniqueDetails_GUI::MeasurementTechniqueDetails_GUI() : MeasurementTechniqueDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
MeasurementTechniqueDetails_GUI::MeasurementTechniqueDetails_GUI(wxWindow* parent)
	: MeasurementTechniqueDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
MeasurementTechniqueDetails_GUI::~MeasurementTechniqueDetails_GUI() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void MeasurementTechniqueDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	m_MeasurementTechniqueDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void MeasurementTechniqueDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void MeasurementTechniqueDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void MeasurementTechniqueDetails_GUI::OnInsertName(wxCommandEvent& event) {}
void MeasurementTechniqueDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(MeasurementTechniqueDetails, Notes) }

void MeasurementTechniqueDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(MeasurementTechniqueDetails, Name)}
void MeasurementTechniqueDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(MeasurementTechniqueDetails, Notes)}

void MeasurementTechniqueDetails_GUI::OnPasteName(wxCommandEvent& event) {}
void MeasurementTechniqueDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(MeasurementTechniqueDetails, Notes) }

void MeasurementTechniqueDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Metadata*)) {
			MeasurementTechniqueDetails* element = boost::any_cast<MeasurementTechniqueDetails*>(anyptr);
			Metadata* elementParent = boost::any_cast<Metadata*>(anyptrparent);

			auto& cont = elementParent->MeasurementTechniqueDetails();
			std::pair<MeasurementTechniqueDetails*, MeasurementTechniqueDetails*> data(MatMLFindAndBumpDownHavingId(element, cont));
			if (data.second) MatMLTreeCtrlBumpDown<MeasurementTechniqueDetails_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing


}

void MeasurementTechniqueDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Metadata*)) {
			MeasurementTechniqueDetails* element = boost::any_cast<MeasurementTechniqueDetails*>(anyptr);
			Metadata* elementParent = boost::any_cast<Metadata*>(anyptrparent);

			auto& cont = elementParent->MeasurementTechniqueDetails();
			std::pair<MeasurementTechniqueDetails*, MeasurementTechniqueDetails*> data(MatMLFindAndBumpUpHavingId(element, cont));
			if (data.second) MatMLTreeCtrlBumpUp<MeasurementTechniqueDetails_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing

}
