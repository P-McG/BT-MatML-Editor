#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Shape_GUI.h"

using namespace bellshire::GUI;

Shape_GUI_Base::Shape_GUI_Base()
	:m_ShapeTextCtrl(nullptr)
{

}

Shape_GUI_Base::Shape_GUI_Base(wxWindow* parent)
	:m_ShapeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ShapeTextCtrl);
}

Shape_GUI_Base::~Shape_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

wxTextCtrl* Shape_GUI_Base::GetShapeTextCtrl()
{
	return m_ShapeTextCtrl;
}

/// <summary>
/// Create the GUI for the Shape MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ShapeTextCtrl"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Shape_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& ShapeTextCtrl)
{

	wxNotebook* ShapeNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ShapeNotebook->Hide();
	ShapeNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* ShapePanel(CreateShapePanel(ShapeNotebook, ShapeTextCtrl));

	MatMLInfo_GUI matMLInfo_GUI(ShapeNotebook,
		wxT("***************** Shape *************************\n\nShape is a string describing the\nshape of the bulk material or component and must occur once and only\nonce within the Geometry element. ")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ShapeNotebook->AddPage(ShapePanel, wxT("MatML Data"), b_dflt);
	ShapeNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ShapeNotebook;
}

wxWindow* Shape_GUI_Base::CreateShapePanel(wxWindow* parent, 
	wxTextCtrl*& ShapeTextCtrl
)
{

	wxPanel* ShapePanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	ShapePanel->SetMinSize(wxSize(400, 500));

	wxFlexGridSizer* fgSizer126 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer126->AddGrowableCol(1);
	fgSizer126->AddGrowableRow(0);
	fgSizer126->SetFlexibleDirection(wxBOTH);
	fgSizer126->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText204 = new wxStaticText(ShapePanel, wxID_ANY, wxT("Shape"), wxDefaultPosition, wxDefaultSize, 0);
	staticText204->Wrap(-1);
	fgSizer126->Add(staticText204, 0, wxALL, 5);

	ShapeTextCtrl = new wxTextCtrl(ShapePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	fgSizer126->Add(ShapeTextCtrl, 1, wxALL | wxEXPAND, 5);

	ShapePanel->SetSizer(fgSizer126);
	ShapePanel->Layout();
	fgSizer126->Fit(ShapePanel);

	return ShapePanel;
}

void Shape_GUI_Base::Update( const observer_ptr<Shape> element)
{
	auto element_observer{remove_strongly_typed_on_observer_ptr_v(element)};
	if(element_observer)
		m_ShapeTextCtrl->SetValue(_std2wx((*element_observer)));

	ShowGUI(true);
}

wxString Shape_GUI_Base::GetTreeLabel(const observer_ptr<Shape> element)
{
	wxString str;
	str << wxT("Shape");

	return str;
}


void Shape_GUI_Base::SetConnect()
{
	m_ShapeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Shape_GUI_Base::OnShapeTextCtrl), NULL, this);
	m_ShapeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Shape_GUI_Base::OnShapeTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Shape_GUI::Shape_GUI() : Shape_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Shape_GUI::Shape_GUI(wxWindow* parent)
	: Shape_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Shape_GUI::~Shape_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Shape_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Shape_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Shape_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Shape_GUI::OnShapeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		 auto element_observer = remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<Shape>>(item->GetAnyMatMLDataPointer()));	 
		if (element_observer) {
			wxString str(m_ShapeTextCtrl->GetValue());
			Geometry::Shape_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element_observer = NewData;
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};
