#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_DataFormat_GUI.h"


using namespace bellshire::GUI;

DataFormat_GUI_Base::DataFormat_GUI_Base()
{

}

DataFormat_GUI_Base::DataFormat_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

DataFormat_GUI_Base::~DataFormat_GUI_Base() {
	/*parent will destroy Ctrl or window */
}

/// <summary>
/// Create the GUI for the DataFormat MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="DataFormatNotebook"></param>
/// <param name="DataFormatPanel"></param>
/// <returns>bool</returns>
wxNotebook* DataFormat_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* DataFormatNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DataFormatNotebook->Hide();
	DataFormatNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DataFormatPanel(CreateDataFormatPanel(DataFormatNotebook));

	MatMLInfo_GUI matMLInfo_GUI(DataFormatNotebook,
		wxT("*************** DataFormat *************************\n\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataFormatNotebook->AddPage(DataFormatPanel, wxT("MatML Data."), b_dflt);
	DataFormatNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataFormatNotebook;
}


wxWindow* DataFormat_GUI_Base::CreateDataFormatPanel(wxWindow* parent)
{
		wxScrolledWindow* DataFormatPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return DataFormatPanel;

}
void DataFormat_GUI_Base::Update( const observer_ptr<DataFormat> element)
{
	wxString str;

	Show(true);
}

wxString DataFormat_GUI_Base::GetTreeLabel(const observer_ptr<DataFormat> element)
{
	wxString str;
	str << wxT("DataFormat");

	return str;
}

void DataFormat_GUI_Base::SetConnect()
{}


/// <summary>
/// Constructor for the derived class
/// </summary>
DataFormat_GUI::DataFormat_GUI() : DataFormat_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
DataFormat_GUI::DataFormat_GUI(wxWindow* parent)
	: DataFormat_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
DataFormat_GUI::~DataFormat_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* DataFormat_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DataFormat_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DataFormat_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

