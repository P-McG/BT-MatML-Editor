#include <wx/config.h>
#include "BT_MatML_Graph_GUI.h"

using namespace bellshire;

Graph_GUI_Base::Graph_GUI_Base():m_graphtextctrl(nullptr), m_graphdisplay(nullptr), m_GUI(nullptr)
{

}

Graph_GUI_Base::Graph_GUI_Base(wxWindow* parent) : m_graphtextctrl(nullptr), m_graphdisplay(nullptr), m_GUI(nullptr)
{
	m_GUI=Create(parent, m_graphtextctrl, m_graphdisplay);
}

Graph_GUI_Base::~Graph_GUI_Base() {
	/*parent will distroy Ctrl or window */ 
}

/// <summary>
/// Create the GUI for the Graph MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="GraphTextCtrl"></param>
/// <param name="GraphDisplayPanel"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Graph_GUI_Base::Create(wxWindow* parent, wxTextCtrl*& graphtextctrl, GraphDisplay*& graphdisplay)
{
	wxNotebook* GraphNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	GraphNotebook->Hide();
	GraphNotebook->SetMinSize(wxSize(400, 500));

	//GraphPanel

	wxScrolledWindow* GraphPanel = new wxScrolledWindow(GraphNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GraphPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->AddGrowableRow(0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText1 = new wxStaticText(GraphPanel, wxID_ANY, wxT("SVG Data"), wxDefaultPosition, wxDefaultSize, 0);
	staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);

	graphtextctrl = new wxTextCtrl(GraphPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxSIMPLE_BORDER | wxVSCROLL | wxHSCROLL | wxTE_RICH);
	fgSizer1->Add(graphtextctrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

	GraphPanel->SetSizer(bSizer1);
	GraphPanel->Layout();
	bSizer1->Fit(GraphPanel);

	//GraphDisplayPanel

	graphdisplay = new GraphDisplay(GraphNotebook, graphtextctrl);
	graphdisplay->SetScrollRate(5, 5);
	graphdisplay->Hide();

	wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);

	graphdisplay->SetSizer(bSizer2);
	graphdisplay->Layout();
	bSizer2->Fit(graphdisplay);

	//MatMLInfoPanel
	MatMLInfo_GUI matml_GUI(GraphNotebook,
		wxT("**************** Graphs:Graph *************************\n\nGraph uses the W3C's Scalable Vector Graphics markup language (SVG)\n for describing two dimensional graphics and allows for three types of \ngraphical objects: vector graphics shapes, images, and text[unsupported].\n\n Graph must occur one or more times within the Graphs element. For more\n information concerning SVG, see the documentation \nat http://www.w3.org/TR/SVG/.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GraphNotebook->AddPage(GraphPanel, wxT("MatML Data."), b_dflt);
	GraphNotebook->AddPage(graphdisplay, wxT("SVG Image."), false);
	GraphNotebook->AddPage(matml_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GraphNotebook;
}

void Graph_GUI_Base::Update( Graph* element)
{
	//UNSUPPORTED

	Show(true);
}

GraphDisplay::GraphDisplay(wxNotebook* parent, wxTextCtrl* GraphTextCtrl)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL)
{
    SetBackgroundColour(*wxWHITE);
    SetScrollbars(20, 20, 50, 50);
    m_GraphTextCtrl = GraphTextCtrl;
}

// Define the repainting behaviour
void GraphDisplay::OnDraw(wxDC& dc)
{
    //dc.DrawBitmap(wxBitmap(".\\svg.svg"), 50, 15);

    // vars to use ...
    wxPen wP;
    wxBrush wB;
    wxPoint points[6];
    wxColour wC;

    dc.SetFont(*wxSWISS_FONT);
    dc.SetPen(*wxGREEN_PEN);

    // draw lines to make a cross
    dc.DrawLine(0, 0, 200, 200);
    dc.DrawLine(200, 0, 0, 200);
    // draw point colored line and spline
    wP = *wxCYAN_PEN;
    wP.SetWidth(3);
    dc.SetPen(wP);

    dc.DrawPoint(25, 15);
    dc.DrawLine(50, 30, 200, 30);
    dc.DrawSpline(50, 200, 50, 100, 200, 10);
}


/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Graph_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Graph& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Graph");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//--NONE--

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Graph_GUI::Graph_GUI() : Graph_GUI_Base()
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Graph_GUI::Graph_GUI(wxWindow* parent)
	: Graph_GUI_Base(parent)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Graph_GUI::~Graph_GUI() {
	/*parent will distroy Ctrl or window */
}
