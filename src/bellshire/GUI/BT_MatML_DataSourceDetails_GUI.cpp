#include "pch.h"
#include <wx/config.h>

#include "bellshire/GUI/BT_MatML_DataSourceDetails_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire::GUI;

DataSourceDetails_GUI_Base::DataSourceDetails_GUI_Base()
	:m_DataSourceDetails_ID_GUI(nullptr), 
	m_DataSourceDetailsTypeTextCtrl(nullptr)
{

}

DataSourceDetails_GUI_Base::DataSourceDetails_GUI_Base(wxWindow* parent)
	:m_DataSourceDetails_ID_GUI(nullptr), 
	m_DataSourceDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_DataSourceDetails_ID_GUI, m_DataSourceDetailsTypeTextCtrl);
}

DataSourceDetails_GUI_Base::~DataSourceDetails_GUI_Base() {
	/*parent will destroy Ctrl or window */
	delete m_DataSourceDetails_ID_GUI;//this is neither a window nor a ctrl.
}

ID_GUI* DataSourceDetails_GUI_Base::GetDataSourceDetails_ID_GUI()
{
	return m_DataSourceDetails_ID_GUI;
}

wxTextCtrl* DataSourceDetails_GUI_Base::GetDataSourceDetailsTypeTextCtrl()
{
	return m_DataSourceDetailsTypeTextCtrl;
}


/// <summary>
/// Create the GUI for the DataSourceDetails MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="fgSizer"></param>
/// <param name="DataSourceDetailsNotebook"></param>
/// <param name="DataSourceDetailsPanel"></param>
/// <param name="DataSourceDetailsGenerateUuidButton"></param>
/// <param name="DataSourceDetailsIDTextCtrl"></param>
/// <param name="DataSourceDetailsTypeTextCtrl"></param>
/// <returns>bool</returns>
wxNotebook* DataSourceDetails_GUI_Base::Create(wxWindow* parent, 
	ID_GUI*& DataSourceDetails_ID_GUI,
	wxTextCtrl*& DataSourceDetailsTypeTextCtrl
)
{
	wxNotebook* DataSourceDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DataSourceDetailsNotebook->Hide();
	DataSourceDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* DataSourceDetailsPanel(CreateDataSourceDetailsPanel(DataSourceDetailsNotebook,
		DataSourceDetails_ID_GUI,
		DataSourceDetailsTypeTextCtrl
	));

	MatMLInfo_GUI matMLInfo_GUI(DataSourceDetailsNotebook,
		wxT("********* DataSourceDetails *************************\n\nThis element declares the content model for DataSourceDetails, which\ncontains a description of a data source referenced by the PropertyData\nelement. DataSourceDetails has one required attribute, id, which may be\narbitrarily assigned but must be unique among id attributes assigned\nelsewhere in a MatML document. DataSourceDetails also has one\noptional attribute, type, for specifying the type of the data source\n(examples include \"unpublished report,\" \"journal,\" \"handbook,\" etc.)\nDataSourceDetails is composed of the following elements.\n\nName contains the name of the data source and has one optional\nattribute, authority, for identifying an authoritative source of data\nsource names. Name must occur once and only once within the\nDataSourceDetails element.\n\nNotes contains any additional information concerning the data source\nand may occur once or not at all within the DataSourceDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataSourceDetailsNotebook->AddPage(DataSourceDetailsPanel, wxT("MatML Data."), b_dflt);
	DataSourceDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataSourceDetailsNotebook;
}

wxWindow* DataSourceDetails_GUI_Base::CreateDataSourceDetailsPanel(wxWindow* parent, 
	ID_GUI*& DataSourceDetails_ID_GUI, 
	wxTextCtrl*& DataSourceDetailsTypeTextCtrl
)
{

	wxScrolledWindow* DataSourceDetailsPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	DataSourceDetailsPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer47 = new wxBoxSizer(wxVERTICAL);
	DataSourceDetails_ID_GUI = new ID_GUI(DataSourceDetailsPanel);
	bSizer47->Add(DataSourceDetails_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer29 = new wxFlexGridSizer(3, 2, 0, 0);
	fgSizer29->AddGrowableCol(1);
	fgSizer29->SetFlexibleDirection(wxBOTH);
	fgSizer29->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText44 = new wxStaticText(DataSourceDetailsPanel, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0);
	staticText44->Wrap(-1);
	fgSizer29->Add(staticText44, 0, wxALL, 5);

	DataSourceDetailsTypeTextCtrl = new wxTextCtrl(DataSourceDetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer29->Add(DataSourceDetailsTypeTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer47->Add(fgSizer29, 1, wxEXPAND, 5);

	DataSourceDetailsPanel->SetSizer(bSizer47);
	DataSourceDetailsPanel->Layout();
	bSizer47->Fit(DataSourceDetailsPanel);

	return DataSourceDetailsPanel;
}

void DataSourceDetails_GUI_Base::Update( const observer_ptr<DataSourceDetails> element)
{

	wxString str;

	m_DataSourceDetails_ID_GUI->Update(element);

	if (element) {
		str.clear();
		{
			const DataSourceDetails::type_optional& cont(element->type());
			if (cont.present()) str << _std2wx(cont.get());
			m_DataSourceDetailsTypeTextCtrl->ChangeValue(str);
		}

		ShowGUI(true);
	}
}

::std::string DataSourceDetails_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

wxString DataSourceDetails_GUI_Base::GetTreeLabel(const observer_ptr<DataSourceDetails> element)
{
	::std::string label;

	if (element) {
		label.assign("DataSourceDetails-");
		label.append(Label(element->Name(), element->id()));
	}

	return label;
}


void DataSourceDetails_GUI_Base::SetConnect()
{
	m_DataSourceDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(DataSourceDetails_GUI_Base::OnDataSourceDetailsTypeTextCtrl), NULL, this);
	m_DataSourceDetailsTypeTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(DataSourceDetails_GUI_Base::OnDataSourceDetailsTypeTextCtrl), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
DataSourceDetails_GUI::DataSourceDetails_GUI() : DataSourceDetails_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
DataSourceDetails_GUI::DataSourceDetails_GUI(wxWindow* parent)
	: DataSourceDetails_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
DataSourceDetails_GUI::~DataSourceDetails_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* DataSourceDetails_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

::boost::any DataSourceDetails_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DataSourceDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc)
{
	GetDataSourceDetails_ID_GUI()->SetEvtHandlerVar(MatMLTreeCtrl, MatMLDoc);
	SetMatMLTreeCtrl(MatMLTreeCtrl);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DataSourceDetails_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}


void DataSourceDetails_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void DataSourceDetails_GUI::OnDataSourceDetailsTypeTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		DataSourceDetails* const Element = boost::any_cast<DataSourceDetails* const>(item->GetAnyMatMLDataPointer());	//<<--Specialized
		if (Element != 0) {
			DataSourceDetails::type_optional& cont(Element->type()); //<<--Specialized
			wxString str(GetDataSourceDetailsTypeTextCtrl()->GetValue()); //<<--Specialized
			DataSourceDetails::type_type NewData((const char*)str.mb_str(wxConvUTF8)); //<<--Specialized
			if (cont.present()) cont = NewData;
			else cont.set(NewData);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

}

void DataSourceDetails_GUI::OnInsertName(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(DataSourceDetails, Name) }
void DataSourceDetails_GUI::OnInsertNotes(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(DataSourceDetails, Notes) }

void DataSourceDetails_GUI::OnDeleteName(wxCommandEvent& event) {ON_PARENT_DELETE_CHILD(DataSourceDetails, Name)}
void DataSourceDetails_GUI::OnDeleteNotes(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(DataSourceDetails, Notes)}

void DataSourceDetails_GUI::OnPasteName(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(DataSourceDetails, Name) }
void DataSourceDetails_GUI::OnPasteNotes(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(DataSourceDetails, Notes) }


void DataSourceDetails_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingId< DataSourceDetails,
		Metadata,
		Metadata::DataSourceDetails_sequence,
		DataSourceDetails_GUI,
		&Metadata::DataSourceDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void DataSourceDetails_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingId< DataSourceDetails,
		Metadata,
		Metadata::DataSourceDetails_sequence,
		DataSourceDetails_GUI,
		&Metadata::DataSourceDetails
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
