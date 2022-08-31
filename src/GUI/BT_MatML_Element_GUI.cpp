#include <wx/config.h>

#include "BT_MatML_Element_GUI.h"

using namespace bellshire;

Element_GUI_Base::Element_GUI_Base()
	:m_GUI(nullptr)
{

}

Element_GUI_Base::Element_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr)
{
	m_GUI = Create(parent);
}

Element_GUI_Base::~Element_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the Element MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="ElementNotebook"></param>
/// <param name="ElementPanel"></param>
/// <returns>bool</returns>
wxNotebook* Element_GUI_Base::Create(wxWindow* parent)
{
	wxNotebook* ElementNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ElementNotebook->Hide();
	ElementNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ElementPanel = new wxScrolledWindow(ElementNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ElementPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer1261 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer1261->AddGrowableCol(0);
	fgSizer1261->AddGrowableRow(0);
	fgSizer1261->SetFlexibleDirection(wxBOTH);
	fgSizer1261->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(ElementPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1261->Add(staticText4, 0, wxALL, 5);

	ElementPanel->SetSizer(fgSizer1261);
	ElementPanel->Layout();
	fgSizer1261->Fit(ElementPanel);

	MatMLInfo_GUI matMLInfo_GUI(ElementNotebook,
		wxT("*************** Element *************************\n\nThis element declares the content model for Element and is composed\nof the following elements.\n\nSymbol contains the symbol for the chemical element, which is one\namong those enumerated by the ChemicalElementSymbol datatype.\nSymbol has one optional attribute, subscript, for indicating the \nsubscript (formula units) of the chemical element. Symbol must occur\nonce and only once within the Element element. For additional\ninformation, see the documentation for the ChemicalElementSymbol\ndatatype.\n\nConcentration contains the concentration of the element and may occur\nonce or not at all within the Element element. For additional information,\nsee the documentation for the Concentration element.\n\nNotes contains any additional information concerning the element and\nmay occur once or not at all within the Element element.\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ElementNotebook->AddPage(ElementPanel, wxT("MatML Data."), b_dflt);
	ElementNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ElementNotebook;
}


void Element_GUI_Base::Update( Element* element)
{
	wxString str;

	//Nothing to update

	Show(true);
}



/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Element_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId &ParentId,  
	Element &element, 
	const wxTreeItemId &PreviousId 
)
{
	  wxString str;
	  str << wxT("Element");

	  wxTreeItemId CurrentId;

	  if(PreviousId.IsOk())
		  CurrentId=MatMLTreeCtrl->InsertItem(ParentId,PreviousId,str,-1,-1,new MatMLTreeItemData(&element));
	  else
		  CurrentId=MatMLTreeCtrl->AppendItem(ParentId, str,-1,-1,new MatMLTreeItemData(&element));

	  //Setup MatML Attribute
	  //--NONE--

	  //Setup Elements Symbol
	  if(element.Symbol()!="")
		  Symbol_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, element.Symbol(), wxTreeItemId());

	  //Setup Element Concentration
	  {
		   Element::Concentration_optional& cont(element.Concentration());
		   if(cont.present())
			   Concentration_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	  }

	  //Setup Element Notes
	  {
		   Element::Notes_optional& cont(element.Notes());
		   if(cont.present())
			   Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	  }
	  return CurrentId;
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Element_GUI::Element_GUI() 
	: Element_GUI_Base(),
	m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Element_GUI::Element_GUI(wxWindow* parent)
	: Element_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Element_GUI::~Element_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Element_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Element_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Element_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Element_GUI::OnInsertSymbol(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Element, Symbol) }
void Element_GUI::OnInsertConcentration(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Element, Concentration) }
void Element_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Element, Notes) }

void Element_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(Element, Symbol)}
void Element_GUI::OnDeleteConcentration(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Element, Concentration)}
void Element_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Element, Notes)}

void Element_GUI::OnPasteSymbol(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(Element, Symbol) }
void Element_GUI::OnPasteConcentration(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Element, Concentration) }
void Element_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Element, Notes) }


void Element_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDown< Element,
		ChemicalComposition,
		ChemicalComposition::Element_sequence,
		Element_GUI,
		&ChemicalComposition::Element
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

	IndividualBumpDown< Element,
		Compound,
		Compound::Element_sequence,
		Element_GUI,
		&Compound::Element
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Element_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUp< Element,
		ChemicalComposition,
		ChemicalComposition::Element_sequence,
		Element_GUI,
		&ChemicalComposition::Element
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

	IndividualBumpUp< Element,
		Compound,
		Compound::Element_sequence,
		Element_GUI,
		&Compound::Element
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);
}
