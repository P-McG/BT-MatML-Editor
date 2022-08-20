#include <wx/config.h>
#include "BT_MatML_Shape_GUI.h"

using namespace bellshire;

Shape_GUI_Base::Shape_GUI_Base()
	:m_GUI(nullptr),
	m_ShapeTextCtrl(nullptr)
{

}

Shape_GUI_Base::Shape_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ShapeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_ShapeTextCtrl);
}

Shape_GUI_Base::~Shape_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxPanel* ShapePanel = new wxPanel(ShapeNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
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

	MatMLInfo_GUI matMLInfo_GUI(ShapeNotebook,
		wxT("***************** Shape *************************\n\nShape is a string describing the\nshape of the bulk material or component and must occur once and only\nonce within the Geometry element. ")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ShapeNotebook->AddPage(ShapePanel, wxT("MatML Data"), b_dflt);
	ShapeNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ShapeNotebook;
}


void Shape_GUI_Base::Update( Shape* element)
{
	m_ShapeTextCtrl->SetValue(_std2wx((*element->t)));

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Shape_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	Geometry::Shape_type& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Shape");

	wxTreeItemId CurrentId;

	MatMLTreeItemData* data=new MatMLTreeItemData(new Shape(&Element));

	if (PreviousId.IsOk()) {
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, data);
	}
	else {
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, data);
	}

	//Shape* strongtypedefstruct = new Shape(Element);

	//if (PreviousId.IsOk()) {
	//	CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	//}
	//else {

	//	wxTreeItemData* p_MatMLTreeItemData = new MatMLTreeItemData(strongtypedefstruct);
	//	CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, p_MatMLTreeItemData);
	//}


	//Setup MatML Attribute
	//--NONE--
	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
		Shape* element = boost::any_cast<Shape* const>(item->GetAnyMatMLDataPointer());	 
		if (element != 0) {
			wxString str(m_ShapeTextCtrl->GetValue());
			Geometry::Shape_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element->t = NewData;//t required due to strong_typedef
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};
