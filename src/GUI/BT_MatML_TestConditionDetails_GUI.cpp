#include <wx/config.h>
#include "BT_MatML_TestConditionDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

TestConditionDetails_GUI_Base::TestConditionDetails_GUI_Base()
	:m_GUI(nullptr),
	m_TestConditionDetails_ID_GUI(nullptr),
	m_TestConditionDetailsTypeTextCtrl(nullptr)

{

}

TestConditionDetails_GUI_Base::TestConditionDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_TestConditionDetails_ID_GUI(nullptr),
	m_TestConditionDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_TestConditionDetails_ID_GUI);
}

TestConditionDetails_GUI_Base::~TestConditionDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_TestConditionDetails_ID_GUI;//this is neither a window nor a ctrl.
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

	wxScrolledWindow* TestConditionDetailsPanel = new wxScrolledWindow(TestConditionDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	TestConditionDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	TestConditionDetails_ID_GUI = new ID_GUI(TestConditionDetailsPanel);
	bSizer1->Add(TestConditionDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	TestConditionDetailsPanel->SetSizer(bSizer1);
	TestConditionDetailsPanel->Layout();
	bSizer1->Fit(TestConditionDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(TestConditionDetailsNotebook,
		wxT("********* TestConditionDetails *************************\n\t\t\t\nThis element declares the content model for TestConditionDetails, which\ncontains a description of the test conditions referenced by the\nPropertyData element. TestConditionDetails has one required attribute, id, \nwhich may be arbitrarily assigned but must be unique among id attributes\n assigned elsewhere in a MatML document.\n\nTestConditionDetails has two optional elements, ParameterValue and\nNotes.\n\t\t\t\nParameterValue contains the value(s) of a parameter, i.e., a test\ncondition, and may occur zero or more times within\nthe TestConditionDetails element. For additional information, see the\ndocumentation for the ParameterValue element.\n\nNotes contains any additional information concerning the test\nconditions and may occur once or not at all within the \nTestConditionDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	TestConditionDetailsNotebook->AddPage(TestConditionDetailsPanel, wxT("MatML Data."), b_dflt);
	TestConditionDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return TestConditionDetailsNotebook;
}


void TestConditionDetails_GUI_Base::Update( TestConditionDetails* element)
{

	m_TestConditionDetails_ID_GUI->Update(element);

	Show(true);
}

::std::string TestConditionDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId TestConditionDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	TestConditionDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("TestConditionDetails-");
	label.append(Label("", Element.id()));

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id

	//Setup Element ParameterValue
	{
		TestConditionDetails::ParameterValue_sequence& cont(Element.ParameterValue());
		TestConditionDetails::ParameterValue_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				ParameterValue_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}

	//Setup Elements Notes
	{
		TestConditionDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void TestConditionDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_TestConditionDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
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
