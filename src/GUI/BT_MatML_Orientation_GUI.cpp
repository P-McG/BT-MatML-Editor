#include <wx/config.h>
#include "BT_MatML_Orientation_GUI.h"

using namespace bellshire;

Orientation_GUI_Base::Orientation_GUI_Base()
	:m_GUI(nullptr),
	m_OrientationTextCtrl(nullptr)
{

}

Orientation_GUI_Base::Orientation_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_OrientationTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_OrientationTextCtrl);
}

Orientation_GUI_Base::~Orientation_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Geometry::Orientation MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="OrientationTextCtrl"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Orientation_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& OrientationTextCtrl)
{

	wxNotebook* OrientationNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	OrientationNotebook->Hide();
	OrientationNotebook->SetMinSize(wxSize(400, 500));

	wxPanel* OrientationPanel = new wxPanel(OrientationNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	OrientationPanel->SetMinSize(wxSize(400, 500));

	wxFlexGridSizer* fgSizer126 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer126->AddGrowableCol(1);
	fgSizer126->AddGrowableRow(0);
	fgSizer126->SetFlexibleDirection(wxBOTH);
	fgSizer126->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText204 = new wxStaticText(OrientationPanel, wxID_ANY, wxT("Orientation"), wxDefaultPosition, wxDefaultSize, 0);
	staticText204->Wrap(-1);
	fgSizer126->Add(staticText204, 0, wxALL, 5);

	OrientationTextCtrl = new wxTextCtrl(OrientationPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	fgSizer126->Add(OrientationTextCtrl, 1, wxALL | wxEXPAND, 5);

	OrientationPanel->SetSizer(fgSizer126);
	OrientationPanel->Layout();
	fgSizer126->Fit(OrientationPanel);

	MatMLInfo_GUI matMLInfo_GUI(OrientationNotebook,
		wxT("***************** Orientation *************************\n\nOrientation is a string describing the\norientation of the bulk material or component and may occur once or not\nat all within the Geometry element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	OrientationNotebook->AddPage(OrientationPanel, wxT("MatML Data"), b_dflt);
	OrientationNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return OrientationNotebook;
}

void Orientation_GUI_Base::Update( Orientation* element)
{
	m_OrientationTextCtrl->SetValue(_std2wx((*element->t)));

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Orientation_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	Geometry::Orientation_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Orientation");

	wxTreeItemId CurrentId;

	Orientation* strongtypedefstruct = new Orientation(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));

	//Setup MatML Attribute
	//--NONE--
	return CurrentId;
}

void Orientation_GUI_Base::SetConnect()
{
	m_OrientationTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Orientation_GUI_Base::OnOrientationTextCtrl), NULL, this);
	m_OrientationTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Orientation_GUI_Base::OnOrientationTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Orientation_GUI::Orientation_GUI() : Orientation_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Orientation_GUI::Orientation_GUI(wxWindow* parent)
	: Orientation_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Orientation_GUI::~Orientation_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Orientation_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Orientation_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Orientation_GUI::OnOrientationTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Orientation* const element = boost::any_cast<Orientation* const>(item->GetAnyMatMLDataPointer());	 
		if (element != 0) {
			wxString str(m_OrientationTextCtrl->GetValue());
			Geometry::Orientation_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element->t = NewData;//t required due to strong_typedef
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};
