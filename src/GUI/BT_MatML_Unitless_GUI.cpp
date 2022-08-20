#include <wx/config.h>
#include "BT_MatML_Unitless_GUI.h"

using namespace bellshire;

Unitless_GUI_Base::Unitless_GUI_Base()
	:m_GUI(nullptr)
{

}

Unitless_GUI_Base::Unitless_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Unitless_GUI_Base::~Unitless_GUI_Base() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the Unitless MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Unitless_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* UnitlessNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	UnitlessNotebook->Hide();
	UnitlessNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* UnitlessPanel = new wxScrolledWindow(UnitlessNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	UnitlessPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(UnitlessPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	UnitlessPanel->SetSizer(bSizer1);
	UnitlessPanel->Layout();
	bSizer1->Fit(UnitlessPanel);

	MatMLInfo_GUI matMLInfo_GUI(UnitlessNotebook,
		wxT("*********** Unitless *************************\n\nThis element declares the content model for Unitless, which is an empty\nelement used whenever a property, parameter, or uncertainty value has\nno units.\t\t\t")
	);

	bool b, b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	UnitlessNotebook->AddPage(UnitlessPanel, wxT("MatML Data."), b_dflt);
	UnitlessNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return UnitlessNotebook;
}

void Unitless_GUI_Base::Update( Unitless* element)
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
wxTreeItemId Unitless_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	Unitless& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Unitless");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup Element Name
	//treated as an attribute

	return CurrentId;
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Unitless_GUI::Unitless_GUI() : Unitless_GUI_Base()
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Unitless_GUI::Unitless_GUI(wxWindow* parent)
	: Unitless_GUI_Base(parent)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Unitless_GUI::~Unitless_GUI() {
	/*parent will distroy Ctrl or window */
}
