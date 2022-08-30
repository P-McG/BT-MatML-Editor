#include <wx/config.h>
#include "BT_MatML_Graphs_GUI.h"

using namespace bellshire;

Graphs_GUI_Base::Graphs_GUI_Base()
	:m_GUI(nullptr)
{

}

Graphs_GUI_Base::Graphs_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Graphs_GUI_Base::~Graphs_GUI_Base() {
	/*parent will distroy Ctrl or window */
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

	wxScrolledWindow* GraphsPanel = new wxScrolledWindow(GraphsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GraphsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticText4 = new wxStaticText(GraphsPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(staticText4, 0, wxALL, 5);

	GraphsPanel->SetSizer(bSizer1);
	GraphsPanel->Layout();
	bSizer1->Fit(GraphsPanel);

	MatMLInfo_GUI matMLInfo_GUI(GraphsNotebook,
		wxT("**************** Graphs *************************\n\nThis element declares the content model for Graphs, which must contain\none or more Graph elements.\n\nGraph uses the W3C's Scalable Vector Graphics markup language (SVG)\nfor describing two dimensional graphics and allows for three types of\ngraphical objects: vector graphics shapes, images, and text. Graph must\noccur one or more times within the Graphs element. For more information\nconcerning SVG, see the documentation at http://www.w3.org/TR/SVG/.\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	GraphsNotebook->AddPage(GraphsPanel, wxT("MatML Data."), b_dflt);
	GraphsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return GraphsNotebook;
}

void Graphs_GUI_Base::Update( Graphs* element)
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
wxTreeItemId Graphs_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Graphs& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Graphs");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//Setup MatML Attribute
	//--NONE--

	//Setup Element Graph
	{
		Graphs::Graph_sequence& cont(Element.Graph());
		Graphs::Graph_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Graph_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, wxTreeItemId());
	}
	return CurrentId;
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
	/*parent will distroy Ctrl or window */
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
