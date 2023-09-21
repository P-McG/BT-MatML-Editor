#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_TestConditionDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire::GUI;

TestConditionDetails_GUI_Base::TestConditionDetails_GUI_Base()
	:m_TestConditionDetails_ID_GUI(nullptr),
	m_TestConditionDetailsTypeTextCtrl(nullptr)

{

}

TestConditionDetails_GUI_Base::TestConditionDetails_GUI_Base(wxWindow* parent)
	:m_TestConditionDetails_ID_GUI(nullptr),
	m_TestConditionDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_TestConditionDetails_ID_GUI);
}

TestConditionDetails_GUI_Base::~TestConditionDetails_GUI_Base() {
	/*parent will destroy Ctrl or window */
	delete m_TestConditionDetails_ID_GUI;//this is neither a window nor a ctrl.
}

ID_GUI* TestConditionDetails_GUI_Base::GetTestConditionDetails_ID_GUI()
{
	return m_TestConditionDetails_ID_GUI;
}

wxTextCtrl* TestConditionDetails_GUI_Base::GetTestConditionDetailsTypeTextCtrl()
{
	return m_TestConditionDetailsTypeTextCtrl;
}

/// <summary>
/// Create the GUI for the TestConditionDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="TestConditionDetailsNotebook"></param>
/// <param name="TestConditionDetailsPanel"></param>
/// <param name="TestConditionDetailsGenerateUuidButton"></param>
/// <param name="TestConditionDetailsIDTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* TestConditionDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& TestConditionDetails_ID_GUI)
{
	wxNotebook* TestConditionDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	TestConditionDetailsNotebook->Hide();
	TestConditionDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* TestConditionDetailsPanel(CreateTextConditionDetailsPanel(TestConditionDetailsNotebook,
		TestConditionDetails_ID_GUI
	));

	MatMLInfo_GUI matMLInfo_GUI(TestConditionDetailsNotebook,
		wxT("********* TestConditionDetails *************************\n\t\t\t\nThis element declares the content model for TestConditionDetails, which\ncontains a description of the test conditions referenced by the\nPropertyData element. TestConditionDetails has one required attribute, id, \nwhich may be arbitrarily assigned but must be unique among id attributes\n assigned elsewhere in a MatML document.\n\nTestConditionDetails has two optional elements, ParameterValue and\nNotes.\n\t\t\t\nParameterValue contains the value(s) of a parameter, i.e., a test\ncondition, and may occur zero or more times within\nthe TestConditionDetails element. For additional information, see the\ndocumentation for the ParameterValue element.\n\nNotes contains any additional information concerning the test\nconditions and may occur once or not at all within the \nTestConditionDetails element.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	TestConditionDetailsNotebook->AddPage(TestConditionDetailsPanel, wxT("MatML Data."), b_dflt);
	TestConditionDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return TestConditionDetailsNotebook;
}

wxWindow* TestConditionDetails_GUI_Base::CreateTextConditionDetailsPanel(wxWindow* parent, 
	ID_GUI*& TestConditionDetails_ID_GUI
)
{

	wxScrolledWindow* TestConditionDetailsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	TestConditionDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	TestConditionDetails_ID_GUI = new ID_GUI(TestConditionDetailsPanel);
	bSizer1->Add(TestConditionDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	TestConditionDetailsPanel->SetSizer(bSizer1);
	TestConditionDetailsPanel->Layout();
	bSizer1->Fit(TestConditionDetailsPanel);

	return TestConditionDetailsPanel;
}

void TestConditionDetails_GUI_Base::Update(const observer_ptr< TestConditionDetails> element)
{

	m_TestConditionDetails_ID_GUI->Update(element);

	ShowGUI(true);
}

::std::string TestConditionDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

wxString TestConditionDetails_GUI_Base::GetTreeLabel(const observer_ptr<TestConditionDetails> element)
{
	::std::string label;
	label.assign("TestConditionDetails-");

	if (element) {
		label.append(Label("", element->id()));
	}

	return label;
}


void TestConditionDetails_GUI_Base::SetConnect()
{}


/// <summary>
/// Constructor for the derived class
/// </summary>
TestConditionDetails_GUI::TestConditionDetails_GUI() : TestConditionDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
TestConditionDetails_GUI::TestConditionDetails_GUI(wxWindow* parent)
	: TestConditionDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
TestConditionDetails_GUI::~TestConditionDetails_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* TestConditionDetails_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any TestConditionDetails_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void TestConditionDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc)
{
	m_TestConditionDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl, MatMLDoc);
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void TestConditionDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void TestConditionDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void TestConditionDetails_GUI::OnInsertParameterValue(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(TestConditionDetails, ParameterValue) }

void TestConditionDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(TestConditionDetails, Notes) }

void TestConditionDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(TestConditionDetails, Notes)}
void TestConditionDetails_GUI::OnDeleteParameterValue(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(TestConditionDetails, ParameterValue)}

void TestConditionDetails_GUI::OnPasteParameterValue(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(TestConditionDetails, ParameterValue) }
void TestConditionDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(TestConditionDetails, Notes) }

void TestConditionDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< TestConditionDetails,
		Metadata,
		Metadata::TestConditionDetails_sequence,
		TestConditionDetails_GUI,
		&Metadata::TestConditionDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);
}

void TestConditionDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingId< TestConditionDetails,
		Metadata,
		Metadata::TestConditionDetails_sequence,
		TestConditionDetails_GUI,
		&Metadata::TestConditionDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
