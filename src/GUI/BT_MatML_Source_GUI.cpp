#include <wx/config.h>
#include "BT_MatML_Source_GUI.h"

using namespace bellshire;

Source_GUI_Base::Source_GUI_Base()
	:m_GUI(nullptr),
	m_SourceChoice(nullptr),
	m_SourceSourceDetails_Display_GUI(nullptr)
{

}

Source_GUI_Base::Source_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), 
	m_SourceChoice(nullptr),
	m_SourceSourceDetails_Display_GUI(nullptr)
{
	m_GUI = Create(parent, m_SourceChoice, m_SourceSourceDetails_Display_GUI);
}

Source_GUI_Base::~Source_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_SourceSourceDetails_Display_GUI; //neither a Ctrl or a window
}



/// <summary>
/// Create the GUI for the Source MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="SourceNotebook"></param>
/// <param name="SourcePanel"></param>
/// <param name="SourceChoice"></param>
/// <returns>bool</returns>
wxNotebook* Source_GUI_Base::Create(wxWindow* parent, wxChoice*& SourceChoice, SourceDetails_Display_GUI*& SourceSourceDetails_Display_GUI)
{
	wxNotebook* SourceNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SourceNotebook->Hide();
	SourceNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* SourcePanel = new wxScrolledWindow(SourceNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SourcePanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer95 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer22 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer22->AddGrowableCol(1);
	fgSizer22->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer22->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText26 = new wxStaticText(SourcePanel, wxID_ANY, wxT("Source"), wxDefaultPosition, wxDefaultSize, 0);
	staticText26->Wrap(-1);
	fgSizer22->Add(staticText26, 0, wxALL, 5);

	wxArrayString SourceChoiceChoices;
	SourceChoice = new wxChoice(SourcePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, SourceChoiceChoices, 0);
	SourceChoice->SetSelection(0);
	fgSizer22->Add(SourceChoice, 1, wxALL | wxEXPAND, 5);

	bSizer95->Add(fgSizer22, 1, wxEXPAND, 5);

	//Display Notebook
	wxNotebook* notebook6 = new wxNotebook(SourcePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	//Display the Details
	SourceSourceDetails_Display_GUI = new SourceDetails_Display_GUI(notebook6);
	notebook6->AddPage(SourceSourceDetails_Display_GUI->get(), wxT("Source"), false);

	bSizer95->Add(notebook6, 1, wxEXPAND | wxALL, 5);

	SourcePanel->SetSizer(bSizer95);
	SourcePanel->Layout();
	bSizer95->Fit(SourcePanel);

	MatMLInfo_GUI matMLInfo_GUI(SourceNotebook,
		wxT("*********** Source *************************\n\t\t\t\nThis element declares the content model for Source, which contains\nan id attribute specified in a SourceDetails element representing \nthe source of the bulk material or component\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SourceNotebook->AddPage(SourcePanel, wxT("MatML Data."), b_dflt);
	SourceNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SourceNotebook;
}


void Source_GUI_Base::Update( Source* element, const ::boost::shared_ptr<MatML_Doc> doc)
{
	wxString str;

	//str.clear();
	//{
	//	Source::source_optional& cont(element->source());
	//	if(cont.present()) str<< _std2wx((*cont));
	//	m_SourceSourceTextCtrl->ChangeValue(str);
	//}

	//Setup the Test String for PropertyData.Test choices boxes
	{
		const Metadata::SourceDetails_sequence& cont(doc->Metadata()->SourceDetails());
		Metadata::SourceDetails_const_iterator iter(cont.begin());
		if (!cont.empty()) {
			m_SourceChoice->Clear();
			m_SourceChoice->Append(wxT(""));
			for (; iter != cont.end(); ++iter) 
				m_SourceChoice->Append(_std2wx(Label(iter->Name(), iter->id())));
		}

	}

	str.clear();
	{
		const Source::source_optional& cont(element->source());
		if (cont.present()) str << _std2wx((*cont));
		m_SourceChoice->SetStringSelection(str);
	}

	//Set ParameterValue choice box
	::std::string label;
	if (element->source().present()) {
		const xml_schema::idref& idref(element->source().get());
		const SourceDetails* src = dynamic_cast<const SourceDetails*>(&*idref);
		if (src)
			m_SourceChoice->SetStringSelection(_std2wx(Label(src->Name(), src->id())));
	}

	m_SourceSourceDetails_Display_GUI->Update(element);

	Show(true);
}


::std::string Source_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}
::std::string Source_GUI_Base::LabelToId(::std::string label)
{
	::std::list<::std::string> result;
	return boost::split(result, label, boost::is_any_of(":")).back();
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId Source_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId, 
	Source& Element, 
	const wxTreeItemId& PreviousId
)
{
	wxString str;
	str << wxT("Source");

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, str, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//source

	//Setup MatML Elements
	//--NONE--

	return CurrentId;
}


void Source_GUI_Base::SetConnect()
{
	m_SourceChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Source_GUI_Base::OnSourceChoice), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Source_GUI::Source_GUI() : Source_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Source_GUI::Source_GUI(wxWindow* parent)
	: Source_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Source_GUI::~Source_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Source_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Source_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void Source_GUI::OnSourceChoice(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Source* const Element = boost::any_cast<Source* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			//Source::source_optional& cont(Element->source());
			//wxString str(m_SourceChoice->GetStringSelection());
			//if (str.IsEmpty()) { 
			//	cont.reset();
			//	m_SourceSourceDetails_Display_GUI->Update(Element);
			//	return; 
			//}

			//Source::source_type NewData((const char*)str.mb_str(wxConvUTF8));
			//if (cont.present()) cont = NewData;
			//else cont.set(NewData);

			//Get wxWidget info and Store MatML Data
			::std::string id(LabelToId(_wx2std(m_SourceChoice->GetStringSelection())));
			if (id.empty()) Element->source().reset();//Empty data is still data so reset.
			else {
				PropertyData::source_type NewData(id.c_str());
				Element->source() = NewData;
			}

			//Set up label string

			::std::string label("Source-");

			if (Element->source().present()) {
				const xml_schema::idref& idref(Element->source().get());//get parameter for label
				const SourceDetails* src = dynamic_cast<const SourceDetails*>(&*idref);
				label.append(Label(src->Name(), src->id()));
			}
			
			m_MatMLTreeCtrl->SetItemText(itemId, _std2wx(label));//Set Label
			

			m_SourceSourceDetails_Display_GUI->Update(Element);

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}
