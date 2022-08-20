#include <wx/config.h>

#include "BT_MatML_DataFormat_GUI.h"


using namespace bellshire;

DataFormat_GUI::DataFormat_GUI()
	:m_GUI(nullptr)
{

}

DataFormat_GUI::DataFormat_GUI(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

DataFormat_GUI::~DataFormat_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the DataFormat MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="DataFormatNotebook"></param>
/// <param name="DataFormatPanel"></param>
/// <returns>bool</returns>
wxNotebook* DataFormat_GUI::Create(wxWindow* parent)
{
	wxNotebook* DataFormatNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DataFormatNotebook->Hide();
	DataFormatNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* DataFormatPanel = new wxScrolledWindow(DataFormatNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DataFormatPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1261->AddGrowableCol(0);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(DataFormatPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	DataFormatPanel->SetSizer(fgSizer1261);
	DataFormatPanel->Layout();
	fgSizer1261->Fit(DataFormatPanel);

	MatMLInfo_GUI matMLInfo_GUI(DataFormatNotebook,
		wxT("*************** DataFormat *************************\n\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataFormatNotebook->AddPage(DataFormatPanel, wxT("MatML Data."), b_dflt);
	DataFormatNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataFormatNotebook;
}

void DataFormat_GUI::Update( DataFormat* element)
{
	wxString str;

	//Need to add ParentMaterialID

	Show(true);
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId DataFormat_GUI::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	DataFormat& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("DataFormat");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element
	//--NONE--

	return CurrentId;
}