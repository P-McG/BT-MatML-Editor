#include <wx/config.h>
#include "BT_MatML_ProcessingDetails_GUI.h"

using namespace bellshire;

ProcessingDetails_GUI_Base::ProcessingDetails_GUI_Base()
	:m_GUI(nullptr),
	m_ProcessingDetailsResultTextCtrl(nullptr)
{

}

ProcessingDetails_GUI_Base::ProcessingDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ProcessingDetailsResultTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ProcessingDetailsResultTextCtrl);
}

ProcessingDetails_GUI_Base::~ProcessingDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the ProcessingDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ProcessingDetailsResultTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* ProcessingDetails_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& ProcessingDetailsResultTextCtrl)
{

	wxNotebook* ProcessingDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ProcessingDetailsNotebook->Hide();
	ProcessingDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ProcessingDetailsPanel = new wxScrolledWindow(ProcessingDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	ProcessingDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(ProcessingDetailsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	ProcessingDetailsPanel->SetSizer(bSizer1);
	ProcessingDetailsPanel->Layout();
	bSizer1->Fit(ProcessingDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(ProcessingDetailsNotebook,
		wxT("************ ProcessingDetails *************************\n\nThis element declares the content model for ProcessingDetails, which\ncontains a description of a processing step for the bulk material or\ncomponent. ProcessingDetails is composed of the following elements.\n\nName contains the name of the processing step and has one optional\nattribute, authority, for identifying an authoritative source of processing\nstep names. Name must occur once and only once within the\nProcessingDetails element.\n\nParameterValue contains the value of a parameter under which the\nprocessing step occurred and may occur zero or more times within the\nProcessingDetails element. For additional information, see the\ndocumentation for the ParameterValue element.\n\nResult is a string that contains a description of the outcome or result\n of the processing step and may occur once or not at all within the\nProcessingDetails element.\n\nNotes contains any additional information concerning the processing\nstep and may occur once or not at all within the ProcessingDetails\nelement.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ProcessingDetailsNotebook->AddPage(ProcessingDetailsPanel, wxT("MatML Data."), b_dflt);
	ProcessingDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ProcessingDetailsNotebook;
}

void ProcessingDetails_GUI_Base::Update( ProcessingDetails* element)
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
wxTreeItemId ProcessingDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId,
	ProcessingDetails& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("ProcessingDetails-");
	str << _std2wx(Element.Name());

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Element ParameterValue
	{
		ProcessingDetails::ParameterValue_sequence& cont(Element.ParameterValue());
		ProcessingDetails::ParameterValue_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParameterValue_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Elements Results
	{
		ProcessingDetails::Result_optional& cont(Element.Result());
		if (cont.present())
			Result_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}


	//Setup Elements Notes
	{
		ProcessingDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}

void ProcessingDetails_GUI_Base::SetConnect()
{
}

/// <summary>
/// Constructor for the derived class
/// </summary>
ProcessingDetails_GUI::ProcessingDetails_GUI() : ProcessingDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ProcessingDetails_GUI::ProcessingDetails_GUI(wxWindow* parent)
	: ProcessingDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ProcessingDetails_GUI::~ProcessingDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ProcessingDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ProcessingDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void ProcessingDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void ProcessingDetails_GUI::OnProcessingDetailsResultTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		ProcessingDetails*  Element = boost::any_cast<ProcessingDetails* >(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			ProcessingDetails::Result_optional& cont(Element->Result());
			wxString str(m_ProcessingDetailsResultTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			ProcessingDetails::Result_type NewData(::xml_schema::string(str.mb_str()));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void ProcessingDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(ProcessingDetails, Name) }
void ProcessingDetails_GUI::OnInsertParameterValue(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(ProcessingDetails, ParameterValue) }
void ProcessingDetails_GUI::OnInsertResult(wxCommandEvent& event) {ON_PARENT_INSERT_CONT_CHILD(ProcessingDetails,Result) }
void ProcessingDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(ProcessingDetails, Notes) }

void ProcessingDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(ProcessingDetails, Name)}
void ProcessingDetails_GUI::OnDeleteParameterValue(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(ProcessingDetails, ParameterValue)}
void ProcessingDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ProcessingDetails, Notes)}
void ProcessingDetails_GUI::OnDeleteResult(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(ProcessingDetails, Result)}

void ProcessingDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(ProcessingDetails, Name) }
void ProcessingDetails_GUI::OnPasteParameterValue(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(ProcessingDetails, ParameterValue) }
void ProcessingDetails_GUI::OnPasteResult(wxCommandEvent& event) {/*ON_PARENT_PASTE_CONT_CHILD(ProcessingDetails,Result)*/ }
void ProcessingDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(ProcessingDetails, Notes) }

void ProcessingDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< ProcessingDetails,
		BulkDetails,
		BulkDetails::ProcessingDetails_sequence,
		ProcessingDetails_GUI,
		&BulkDetails::ProcessingDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< ProcessingDetails,
		ComponentDetails,
		ComponentDetails::ProcessingDetails_sequence,
		ProcessingDetails_GUI,
		&ComponentDetails::ProcessingDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void ProcessingDetails_GUI::OnBumpUp(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< ProcessingDetails,
		BulkDetails,
		BulkDetails::ProcessingDetails_sequence,
		ProcessingDetails_GUI,
		&BulkDetails::ProcessingDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< ProcessingDetails,
		ComponentDetails,
		ComponentDetails::ProcessingDetails_sequence,
		ProcessingDetails_GUI,
		&ComponentDetails::ProcessingDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

