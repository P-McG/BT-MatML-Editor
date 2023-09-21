#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Graph_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire::GUI;

Graph_GUI_Base::Graph_GUI_Base()
	:m_graphtextctrl(nullptr),
	m_graphdisplay(nullptr)
{

}

Graph_GUI_Base::Graph_GUI_Base(wxWindow* parent) 
	: m_graphtextctrl(nullptr), 
	m_graphdisplay(nullptr)
{
	m_GUI=Create(parent, m_graphtextctrl, m_graphdisplay);
}

Graph_GUI_Base::~Graph_GUI_Base() {
	/*parent will destroy Ctrl or window */ 
}

wxTextCtrl* Graph_GUI_Base::GetGraphTextCtrl()
{
	return m_graphtextctrl;
}

GraphDisplay* Graph_GUI_Base::GetGraphDisplay()
{
	return m_graphdisplay;
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

	wxWindow* GraphPanel(CreateGraphPanel(GraphNotebook, graphtextctrl));

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

wxWindow* Graph_GUI_Base::CreateGraphPanel(wxWindow* parent,
	 wxTextCtrl*& graphtextctrl
)
{
	//GraphPanel

	wxScrolledWindow* GraphPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return GraphPanel;
}

void Graph_GUI_Base::Update( const observer_ptr<Graph> element)
{
	wxString str;

	//str << _std2wx((*element));//double paranthesis required
	//m_graphtextctrl->ChangeValue(str);

	ShowGUI(true);
}

GraphDisplay::GraphDisplay(wxNotebook* parent, wxTextCtrl* GraphTextCtrl)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL)
{
    SetBackgroundColour(*wxWHITE);
    SetScrollbars(20, 20, 50, 50);
    m_GraphTextCtrl = GraphTextCtrl;
}

wxTextCtrl* GraphDisplay::GetGraphTextCtrl()
{
	return m_GraphTextCtrl;
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

wxString Graph_GUI_Base::GetTreeLabel(const observer_ptr<Graph> element)
{
	wxString str;
	str << wxT("Graph");

	return str;
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
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Graph_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Graph_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Graph_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Graph_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(Graphs*)) {
			auto element{ boost::any_cast<observer_ptr<Graph>>(anyptr) };
			auto element_parent_observer{ boost::any_cast<observer_ptr<Graphs> >(anyptrparent)};

			auto& cont = element_parent_observer->Graph();
			auto data(MatML_Base::FindAndBumpDown(element, cont));
			if (data.second)
				MatMLTreeCtrlBumpDown<Graph_GUI>(m_MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing


}

void Graph_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	try {
		if (anyptrparent.type() == typeid(observer_ptr<Graphs>)) {
			auto element{ boost::any_cast<observer_ptr<Graph> >(anyptr) };
			auto element_parent_observer{ boost::any_cast<observer_ptr<Graphs> >(anyptrparent)};

			if (element_parent_observer) {
				auto& cont = element_parent_observer->Graph();
				auto data(MatML_Base::FindAndBumpUp(element, cont));
				if (data.second)
					MatMLTreeCtrlBumpUp<Graph_GUI>(m_MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

				return;
			}
		}
	}
	catch (const boost::bad_any_cast&) {};//do nothing
}
