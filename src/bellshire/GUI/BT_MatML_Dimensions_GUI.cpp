#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_Dimensions_GUI.h"

using namespace bellshire::GUI;

Dimensions_GUI_Base::Dimensions_GUI_Base()
	:m_DimensionsTextCtrl(nullptr)
{

}

Dimensions_GUI_Base::Dimensions_GUI_Base(wxWindow* parent)
	:m_DimensionsTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_DimensionsTextCtrl);
}

Dimensions_GUI_Base::~Dimensions_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Dimensions_GUI_Base::GetDimensionsTextCtrl()
{
	return m_DimensionsTextCtrl;
}


/// <summary>
/// Create the GUI for the Geometry::Dimensions MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ShapeTextCtrl"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Dimensions_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& DimensionsTextCtrl)
{

	wxNotebook* DimensionsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DimensionsNotebook->Hide();
	DimensionsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DimensionsPanel(CreateDimensionsPanel(DimensionsNotebook, DimensionsTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(DimensionsNotebook,
		wxT("***************** Dimension *************************\n\nDimensions is a string describing the\ndimensions of the bulk material or component and may occur once or not\nat all within the Geometry element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DimensionsNotebook->AddPage(DimensionsPanel, wxT("MatML Data"), b_dflt);
	DimensionsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DimensionsNotebook;
}

wxWindow* Dimensions_GUI_Base::CreateDimensionsPanel(wxWindow* parent, wxTextCtrl*& DimensionsTextCtrl)
{
	wxPanel* DimensionsPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	DimensionsPanel->SetMinSize(wxSize(400, 500));

	wxFlexGridSizer* fgSizer126 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer126->AddGrowableCol(1);
	fgSizer126->AddGrowableRow(0);
	fgSizer126->SetFlexibleDirection(wxBOTH);
	fgSizer126->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText204 = new wxStaticText(DimensionsPanel, wxID_ANY, wxT("Dimensions"), wxDefaultPosition, wxDefaultSize, 0);
	staticText204->Wrap(-1);
	fgSizer126->Add(staticText204, 0, wxALL, 5);

	DimensionsTextCtrl = new wxTextCtrl(DimensionsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	fgSizer126->Add(DimensionsTextCtrl, 1, wxALL | wxEXPAND, 5);

	DimensionsPanel->SetSizer(fgSizer126);
	DimensionsPanel->Layout();
	fgSizer126->Fit(DimensionsPanel);

	return DimensionsPanel;
}
void Dimensions_GUI_Base::Update( const observer_ptr<Dimensions> element)
{
	auto element_observer{remove_strongly_typed_on_observer_ptr_v(element)};
	if (element_observer) {
		m_DimensionsTextCtrl->SetValue(_std2wx((*element_observer)));

		ShowGUI(true);
	}
}


wxString Dimensions_GUI_Base::GetTreeLabel(const observer_ptr<Dimensions> element)
{
	wxString str;
	str << wxT("Dimensions");

	return str;
}


void Dimensions_GUI_Base::SetConnect()
{
	m_DimensionsTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Dimensions_GUI_Base::OnDimensionsTextCtrl), NULL, this);
	m_DimensionsTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Dimensions_GUI_Base::OnDimensionsTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Dimensions_GUI::Dimensions_GUI() : Dimensions_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Dimensions_GUI::Dimensions_GUI(wxWindow* parent)
	: Dimensions_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Dimensions_GUI::~Dimensions_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Dimensions_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Dimensions_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Dimensions_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void Dimensions_GUI::OnDimensionsTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		const auto element_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Dimensions> >(item->GetAnyMatMLDataPointer())) };
		if (element_observer ) {
			wxString str(GetDimensionsTextCtrl()->GetValue());
			Geometry::Dimensions_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element_observer = NewData;//t required due to STRONGLY_TYPED_DEF
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};

