#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_SourceDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire::GUI;

SourceDetails_GUI_Base::SourceDetails_GUI_Base()
	:m_SourceDetails_ID_GUI(nullptr), 
	m_SourceDetailsTypeTextCtrl(nullptr)
{

}

SourceDetails_GUI_Base::SourceDetails_GUI_Base(wxWindow* parent)
	:m_SourceDetails_ID_GUI(nullptr),
	m_SourceDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_SourceDetails_ID_GUI, m_SourceDetailsTypeTextCtrl);
}

SourceDetails_GUI_Base::~SourceDetails_GUI_Base() {
	/*parent will destroy Ctrl or window */
	delete m_SourceDetails_ID_GUI;//this is neither a window nor a ctrl.
}

ID_GUI* SourceDetails_GUI_Base::GetSourceDetails_ID_GUI()
{
	return m_SourceDetails_ID_GUI;
}

wxTextCtrl* SourceDetails_GUI_Base::GetSourceDetailsTypeTextCtrl()
{
	return m_SourceDetailsTypeTextCtrl;
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
wxNotebook* SourceDetails_GUI_Base::Create(wxWindow* parent,
	ID_GUI*& SourceDetails_ID_GUI,
	wxTextCtrl*& SourceDetailsTypeTextCtrl
)
{
	wxNotebook* SourceDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	SourceDetailsNotebook->Hide();
	SourceDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* SourceDetailsPanel(CreateSourceDetailsPanel(SourceDetailsNotebook,
		SourceDetails_ID_GUI,
		SourceDetailsTypeTextCtrl
	));

	MatMLInfo_GUI matMLInfo_GUI(SourceDetailsNotebook,
		wxT("************** SourceDetails *************************\n\nThis element declares the content model for SourceDetails, which\ncontains the name of the source of the component.\n\nName contains the name of the source and has one optional\nattribute, Notes.\n\t\t\t\nNotes contains any additional information concerning the data source\nand may occur once or not at all within the DataSourceDetails element.\t\t\t")
	);

	bool b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	SourceDetailsNotebook->AddPage(SourceDetailsPanel, wxT("MatML Data."), b_dflt);
	SourceDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return SourceDetailsNotebook;
}

wxWindow* SourceDetails_GUI_Base::CreateSourceDetailsPanel(wxWindow* parent,
	ID_GUI*& SourceDetails_ID_GUI,
	wxTextCtrl*& SourceDetailsTypeTextCtrl
)
{

	wxScrolledWindow* SourceDetailsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	return SourceDetailsPanel;
}

void SourceDetails_GUI_Base::Update(const observer_ptr<SourceDetails> element)
{

	wxString str;

	m_SourceDetails_ID_GUI->Update(element);

	if (element) {
		str.clear();
		{
			const SourceDetails::type_optional& cont(element->type());
			if (cont.present()) str << _std2wx((*cont));
			m_SourceDetailsTypeTextCtrl->ChangeValue(str);
		}

		ShowGUI(true);
	}
}

::std::string SourceDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

wxString SourceDetails_GUI_Base::GetTreeLabel(const observer_ptr<SourceDetails> element)
{
	::std::string label;

	if (element) {
		label.assign("SourceDetails-");
		label.append(Label(element->Name(), element->id()));
	}

	return label;
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
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* SourceDetails_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any SourceDetails_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void SourceDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc)
{
	m_SourceDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl, MatMLDoc);
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


void SourceDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< SourceDetails,
		Metadata,
		Metadata::SourceDetails_sequence,
		SourceDetails_GUI,
		&Metadata::SourceDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void SourceDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingId< SourceDetails,
		Metadata,
		Metadata::SourceDetails_sequence,
		SourceDetails_GUI,
		&Metadata::SourceDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}

