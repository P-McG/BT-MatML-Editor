#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Unitless_GUI.h"

using namespace bellshire::GUI;

Unitless_GUI_Base::Unitless_GUI_Base()
{

}

Unitless_GUI_Base::Unitless_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Unitless_GUI_Base::~Unitless_GUI_Base() {
	/*parent will destroy Ctrl or window */
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

	wxWindow* UnitlessPanel(CreateUnitlessPanel(UnitlessNotebook));

	MatMLInfo_GUI matMLInfo_GUI(UnitlessNotebook,
		wxT("*********** Unitless *************************\n\nThis element declares the content model for Unitless, which is an empty\nelement used whenever a property, parameter, or uncertainty value has\nno units.\t\t\t")
	);

	// Notebook assembly
	// =================

	bool b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	UnitlessNotebook->AddPage(UnitlessPanel, wxT("MatML Data."), b_dflt);
	UnitlessNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return UnitlessNotebook;
}

wxWindow* Unitless_GUI_Base::CreateUnitlessPanel(wxWindow* parent)
{
	wxScrolledWindow* UnitlessPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	UnitlessPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(UnitlessPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	UnitlessPanel->SetSizer(bSizer1);
	UnitlessPanel->Layout();
	bSizer1->Fit(UnitlessPanel);

	return UnitlessPanel;
}

void Unitless_GUI_Base::Update( const observer_ptr<Unitless> element)
{
	//Nothing to update

	ShowGUI(true);
}


wxString Unitless_GUI_Base::GetTreeLabel(const observer_ptr<Unitless> element)
{
	wxString str;
	str << wxT("Unitless");

	return str;
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
	/*parent will destroy Ctrl or window */
}
