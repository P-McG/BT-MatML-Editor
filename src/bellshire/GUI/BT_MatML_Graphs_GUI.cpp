#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Graphs_GUI.h"

using namespace bellshire::GUI;

Graphs_GUI_Base::Graphs_GUI_Base()
{

}

Graphs_GUI_Base::Graphs_GUI_Base(wxWindow* parent)
{
	m_GUI = Create(parent);
}

Graphs_GUI_Base::~Graphs_GUI_Base() {
	/*parent will destroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Graphs MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <returns>bool</returns>
wxNotebook* Graphs_GUI_Base::Create(wxWindow* parent)
{

	wxNotebook* GraphsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	GraphsNotebook->Hide();
	GraphsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* GraphsPanel(CreateGraphsPanel(GraphsNotebook));

	MatMLInfo_GUI matMLInfo_GUI(GraphsNotebook,
		wxT("**************** Graphs *************************\n\nThis element declares the content model for Graphs, which must contain\none or more Graph elements.\n\nGraph uses the W3C's Scalable Vector Graphics markup language (SVG)\nfor describing two dimensional graphics and allows for three types of\ngraphical objects: vector graphics shapes, images, and text. Graph must\noccur one or more times within the Graphs element. For more information\nconcerning SVG, see the documentation at http://www.w3.org/TR/SVG/.\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GraphsNotebook->AddPage(GraphsPanel, wxT("MatML Data."), b_dflt);
	GraphsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GraphsNotebook;
}

wxWindow* Graphs_GUI_Base::CreateGraphsPanel(wxWindow* parent)
{
	wxScrolledWindow* GraphsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GraphsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(GraphsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	GraphsPanel->SetSizer(bSizer1);
	GraphsPanel->Layout();
	bSizer1->Fit(GraphsPanel);

	return GraphsPanel;
}

void Graphs_GUI_Base::Update( const observer_ptr<Graphs> element)
{
	//Nothing to update

	ShowGUI(true);
}

wxString Graphs_GUI_Base::GetTreeLabel(const observer_ptr<Graphs> element)
{
	wxString str;
	str << wxT("Graphs");

	return str;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Graphs_GUI::Graphs_GUI() 
	: Graphs_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{
}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Graphs_GUI::Graphs_GUI(wxWindow* parent)
	: Graphs_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Graphs_GUI::~Graphs_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Graphs_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any Graphs_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Graphs_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Graphs_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Graphs_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Graphs_GUI::OnInsertGraph(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Graphs, Graph) }
void Graphs_GUI::OnDeleteGraph(wxCommandEvent& event) { ON_PARENT_DELETE_ITER_CONT_CHILD(Graphs, Graph) }
void Graphs_GUI::OnPasteGraph(wxCommandEvent& event) { ON_PARENT_PASTE_ITER_CONT_CHILD(Graphs, Graph) }
