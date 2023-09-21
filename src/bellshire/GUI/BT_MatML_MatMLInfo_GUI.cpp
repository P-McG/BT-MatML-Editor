#include "pch.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

using namespace bellshire::GUI;

MatMLInfo_GUI::MatMLInfo_GUI():m_label(""), m_GUI(nullptr) {}
MatMLInfo_GUI::MatMLInfo_GUI(wxWindow* parent, const wxString& label):m_label(label), m_GUI(nullptr)
{
	m_GUI = Create(parent, m_label);
}

MatMLInfo_GUI::~MatMLInfo_GUI() {
	/* parent destroys the window or control */
}

const wxString MatMLInfo_GUI::GetLabel()
{
	return m_label;
}

wxScrolledWindow* MatMLInfo_GUI::GetGUI()
{
	return m_GUI;
}


/// <summary>
/// Create GUI for MatML Info.
/// </summary>
/// <param name="parent"></param>
/// <param name="label"></param>
/// <returns>wxScrolledWindow*</returns>
wxScrolledWindow* MatMLInfo_GUI::Create(wxWindow* parent, const wxString& label)
{
	wxScrolledWindow* MatMLInfoPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	MatMLInfoPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1->AddGrowableCol(0);
	fgSizer1->AddGrowableRow(0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText = new wxStaticText(MatMLInfoPanel, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, 0);
	staticText->Wrap(-1);
	fgSizer1->Add(staticText, 1, wxALL | wxEXPAND, 5);

	MatMLInfoPanel->SetSizer(fgSizer1);
	MatMLInfoPanel->Layout();
	fgSizer1->Fit(MatMLInfoPanel);

	return MatMLInfoPanel;
}