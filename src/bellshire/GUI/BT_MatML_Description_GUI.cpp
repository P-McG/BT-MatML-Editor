#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Description_GUI.h"

using namespace bellshire::GUI;

Description_GUI_Base::Description_GUI_Base()
	:m_DescriptionTextCtrl(nullptr)
{

}

Description_GUI_Base::Description_GUI_Base(wxWindow* parent)
	:m_DescriptionTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_DescriptionTextCtrl);
}

Description_GUI_Base::~Description_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Description_GUI_Base::GetDescriptionTextCtrl()
{
	return m_DescriptionTextCtrl;
}


/// <summary>
/// Create the GUI for the Geometry::Description MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ShapeTextCtrl"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Description_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& DescriptionTextCtrl)
{

	wxNotebook* DescriptionNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DescriptionNotebook->Hide();
	DescriptionNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DescriptionPanel(CreateDescriptionPanel(DescriptionNotebook, DescriptionTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(DescriptionNotebook,
		wxT("***************** Dimension *************************\n\nDescription is a string describing the\nDescription of the bulk material or component and may occur once or not\nat all within the Geometry element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DescriptionNotebook->AddPage(DescriptionPanel, wxT("MatML Data"), b_dflt);
	DescriptionNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DescriptionNotebook;
}

wxWindow* Description_GUI_Base::CreateDescriptionPanel(wxWindow* parent, wxTextCtrl*& DescriptionTextCtrl)
{
	wxPanel* DescriptionPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	DescriptionPanel->SetMinSize(wxSize(400, 500));

	wxFlexGridSizer* fgSizer126 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer126->AddGrowableCol(1);
	fgSizer126->AddGrowableRow(0);
	fgSizer126->SetFlexibleDirection(wxBOTH);
	fgSizer126->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText204 = new wxStaticText(DescriptionPanel, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0);
	staticText204->Wrap(-1);
	fgSizer126->Add(staticText204, 0, wxALL, 5);

	DescriptionTextCtrl = new wxTextCtrl(DescriptionPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	fgSizer126->Add(DescriptionTextCtrl, 1, wxALL | wxEXPAND, 5);

	DescriptionPanel->SetSizer(fgSizer126);
	DescriptionPanel->Layout();
	fgSizer126->Fit(DescriptionPanel);

	return DescriptionPanel;
}
void Description_GUI_Base::Update( const observer_ptr<Description> element)
{
	auto element_observer{remove_strongly_typed_on_observer_ptr_v(element)};
	if (element_observer) {
		m_DescriptionTextCtrl->SetValue(_std2wx((*element_observer)));

		ShowGUI(true);
	}
}


wxString Description_GUI_Base::GetTreeLabel(const observer_ptr<Description> element)
{
	wxString str;
	str << wxT("Description");

	return str;
}


void Description_GUI_Base::SetConnect()
{
	m_DescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Description_GUI_Base::OnDescriptionTextCtrl), NULL, this);
	m_DescriptionTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Description_GUI_Base::OnDescriptionTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Description_GUI::Description_GUI() : Description_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Description_GUI::Description_GUI(wxWindow* parent)
	: Description_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Description_GUI::~Description_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Description_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Description_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Description_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void Description_GUI::OnDescriptionTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		auto element_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Description> >(item->GetAnyMatMLDataPointer()))};
		if (element_observer) {
			wxString str(GetDescriptionTextCtrl()->GetValue());
			Form::Description_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element_observer = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};

