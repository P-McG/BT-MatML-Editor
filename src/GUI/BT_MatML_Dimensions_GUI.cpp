#include <wx/config.h>

#include "BT_MatML_Dimensions_GUI.h"

using namespace bellshire;

Dimensions_GUI_Base::Dimensions_GUI_Base()
	:m_GUI(nullptr),
	m_DimensionsTextCtrl(nullptr)
{

}

Dimensions_GUI_Base::Dimensions_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_DimensionsTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_DimensionsTextCtrl);
}

Dimensions_GUI_Base::~Dimensions_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxPanel* DimensionsPanel = new wxPanel(DimensionsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
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

	MatMLInfo_GUI matMLInfo_GUI(DimensionsNotebook,
		wxT("***************** Dimension *************************\n\nDimensions is a string describing the\ndimensions of the bulk material or component and may occur once or not\nat all within the Geometry element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DimensionsNotebook->AddPage(DimensionsPanel, wxT("MatML Data"), b_dflt);
	DimensionsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DimensionsNotebook;
}


void Dimensions_GUI_Base::Update( Dimensions* element)
{
	const Geometry::Dimensions_type& tmp1();// required due to use of BOOST_STRONG_TYPEDEF for Dimensions
	m_DimensionsTextCtrl->SetValue(_std2wx((*element->t)));

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Dimensions_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Geometry::Dimensions_type& Element,
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Dimensions");

	wxTreeItemId CurrentId;

	Dimensions* strongtypedefstruct = new Dimensions(&Element);

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(strongtypedefstruct));

	//Setup MatML Attribute
	//--NONE--

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
		Dimensions* element = boost::any_cast<Dimensions* const>(item->GetAnyMatMLDataPointer());	 
		if (element != nullptr) {
			wxString str(m_DimensionsTextCtrl->GetValue());
			Geometry::Dimensions_type NewData((const char*)str.mb_str(wxConvUTF8));
			*element->t = NewData;//t required due to strong_typedef
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
};

