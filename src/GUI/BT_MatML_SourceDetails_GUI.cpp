#include <wx/config.h>
#include "BT_MatML_SourceDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

SourceDetails_GUI_Base::SourceDetails_GUI_Base()
	:m_GUI(nullptr), m_SourceDetails_ID_GUI(nullptr), m_SourceDetailsTypeTextCtrl(nullptr)
{

}

SourceDetails_GUI_Base::SourceDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr), m_SourceDetails_ID_GUI(nullptr), m_SourceDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_SourceDetails_ID_GUI, m_SourceDetailsTypeTextCtrl);
}

SourceDetails_GUI_Base::~SourceDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_SourceDetails_ID_GUI;//this is neither a window nor a ctrl.
}

/// <summary>
/// Create the GUI for the SourceDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="SourceDetailsNotebook"></param>
/// <param name="SourceDetailsPanel"></param>
/// <param name="SourceDetailsGenerateUuidButton"></param>
/// <param name="SourceDetailsIDTextCtrl"></param>
/// <param name="SourceDetailsTypeTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* SourceDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& SourceDetails_ID_GUI, wxTextCtrl*& SourceDetailsTypeTextCtrl)
{
	wxNotebook* SourceDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SourceDetailsNotebook->Hide();
	SourceDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* SourceDetailsPanel = new wxScrolledWindow(SourceDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	SourceDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	SourceDetails_ID_GUI = new ID_GUI(SourceDetailsPanel);
	bSizer1->Add(SourceDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer33 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer33->AddGrowableCol(1);
	fgSizer33->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer33->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* m_staticText50 = new wxStaticText(SourceDetailsPanel, wxID_ANY, wxT("Source Details Type"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText50->Wrap(-1);
	fgSizer33->Add(m_staticText50, 0, wxALL, 5);

	SourceDetailsTypeTextCtrl = new wxTextCtrl(SourceDetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer33->Add(SourceDetailsTypeTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer33, 1, wxEXPAND, 5);

	SourceDetailsPanel->SetSizer(bSizer1);
	SourceDetailsPanel->Layout();
	bSizer1->Fit(SourceDetailsPanel);

	MatMLInfo_GUI matMLInfo_GUI(SourceDetailsNotebook,
		wxT("************** SourceDetails *************************\n\nThis element declares the content model for SourceDetails, which\ncontains the name of the source of the component.\n\nName contains the name of the source and has one optional\nattribute, Notes.\n\t\t\t\nNotes contains any additional information concerning the data source\nand may occur once or not at all within the DataSourceDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SourceDetailsNotebook->AddPage(SourceDetailsPanel, wxT("MatML Data."), b_dflt);
	SourceDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SourceDetailsNotebook;
}

void SourceDetails_GUI_Base::Update( SourceDetails* element)
{
	wxString str;

	m_SourceDetails_ID_GUI->Update(element);

	str.clear();
	{
		const SourceDetails::type_optional& cont(element->type());
		if (cont.present()) str << _std2wx((*cont));
		m_SourceDetailsTypeTextCtrl->ChangeValue(str);
	}

	Show(true);
}

::std::string SourceDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// </summary>
/// <param name="ParentId"></param>
/// <param name="Element"></param>
/// <param name="PreviousId"></param>
wxTreeItemId SourceDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
	const wxTreeItemId& ParentId,
	SourceDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("SourceDetails-");
	label.append(Label(Element.Name(), Element.id()));


	//strSourceDetailsId.Add(str);

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, label, -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, label, -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id
	//type

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Notes
	{
		SourceDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
}

void SourceDetails_GUI_Base::SetConnect()
{
	//m_SourceDetails_ID_GUI->m_GenerateUuidButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SourceDetails_GUI_Base::OnSourceDetailsGenerateUuidButton), NULL, this);
	//m_SourceDetails_ID_GUI->m_IDTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SourceDetails_GUI_Base::OnSourceDetailsIDTextCtrl), NULL, this);
	//m_SourceDetails_ID_GUI->m_IDTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SourceDetails_GUI_Base::OnSourceDetailsIDTextCtrl), NULL, this);
	m_SourceDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SourceDetails_GUI_Base::OnSourceDetailsTypeTextCtrl), NULL, this);
	m_SourceDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SourceDetails_GUI_Base::OnSourceDetailsTypeTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
SourceDetails_GUI::SourceDetails_GUI() : SourceDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
SourceDetails_GUI::SourceDetails_GUI(wxWindow* parent)
	: SourceDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
SourceDetails_GUI::~SourceDetails_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void SourceDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_SourceDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl);
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void SourceDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

void SourceDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

//
//void SourceDetails_GUI::OnSourceDetailsGenerateUuidButton(wxCommandEvent& event)
//{
//
//	wxTreeItemId ItemId = m_MatMLTreeCtrl->GetSelection();
//	MatMLTreeItemData* Item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(ItemId));
//
//	try {
//		SourceDetails* const matml_item = boost::any_cast<SourceDetails* const>(Item->GetAnyMatMLDataPointer());
//		SourceDetailsGenerateUuid(matml_item);
//		Update(matml_item);
//	}
//	catch (const boost::bad_any_cast&) { return; }
//
//}
//
//void SourceDetails_GUI::SourceDetailsGenerateUuid(SourceDetails* sourcedetails)
//{
//
//	SourceDetails::id_type NewId(bellshire::MaterialFrame::GetUUIDLabel());
//	sourcedetails->id() = NewId;
//
//}
//
//void SourceDetails_GUI::OnSourceDetailsIDTextCtrl(wxCommandEvent& event)
//{
//	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
//	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
//
//	try {
//		SourceDetails* const Element = boost::any_cast<SourceDetails* const>(item->GetAnyMatMLDataPointer());	 
//		if (Element != 0) {
//			wxString str(m_SourceDetails_ID_GUI->m_IDTextCtrl->GetValue());
//			try {
//				SourceDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
//				Element->id(NewData);
//				wxColour clr; clr.Set(0, 0, 0);
//				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);/*
//				wxString msg(wxT(""));
//				m_statusBar1->SetStatusText(msg);*/
//			}
//			catch (const xml_schema::duplicate_id&) {
//				wxColour clr; clr.Set(255, 0, 0);
//				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
//				//wxString msg(wxT("!!! DUPLICATE ID !!!"));
//				//m_statusBar1->SetStatusText(msg);
//			}
//
//			wxString label;
//			label << wxT("SourceDetails-");
//			label << _std2wx(Element->id());
//			m_MatMLTreeCtrl->SetItemText(itemId, label);
//
//			return;
//		}
//	}
//	catch (const boost::bad_any_cast&) { return; }
//}

void SourceDetails_GUI::OnSourceDetailsTypeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		SourceDetails*  Element = boost::any_cast<SourceDetails* >(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			SourceDetails::type_optional& cont(Element->type());
			wxString str(m_SourceDetailsTypeTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			SourceDetails::type_type NewData((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void SourceDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(SourceDetails, Name) }
void SourceDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(SourceDetails, Notes) }

void SourceDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(SourceDetails, Name)}
void SourceDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(SourceDetails, Notes)}

void SourceDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(SourceDetails, Name) }
void SourceDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(SourceDetails, Notes) }