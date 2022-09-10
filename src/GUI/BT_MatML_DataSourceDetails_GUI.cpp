#include <wx/config.h>

#include "BT_MatML_DataSourceDetails_GUI.h"
#include "BT_MatML_MaterialFrame.h"

using namespace bellshire;

DataSourceDetails_GUI_Base::DataSourceDetails_GUI_Base()
	:m_GUI(nullptr), 
	m_DataSourceDetails_ID_GUI(nullptr), 
	m_DataSourceDetailsTypeTextCtrl(nullptr)
{

}

DataSourceDetails_GUI_Base::DataSourceDetails_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_DataSourceDetails_ID_GUI(nullptr), 
	m_DataSourceDetailsTypeTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_DataSourceDetails_ID_GUI, m_DataSourceDetailsTypeTextCtrl);
}

DataSourceDetails_GUI_Base::~DataSourceDetails_GUI_Base() {
	/*parent will distroy Ctrl or window */
	delete m_DataSourceDetails_ID_GUI;//this is neither a window nor a ctrl.
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
wxNotebook* DataSourceDetails_GUI_Base::Create(wxWindow* parent, ID_GUI*& DataSourceDetails_ID_GUI, wxTextCtrl*& DataSourceDetailsTypeTextCtrl)
{
	wxNotebook* DataSourceDetailsNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	DataSourceDetailsNotebook->Hide();
	DataSourceDetailsNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* DataSourceDetailsPanel = new wxScrolledWindow(DataSourceDetailsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
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

	MatMLInfo_GUI matMLInfo_GUI(DataSourceDetailsNotebook,
		wxT("********* DataSourceDetails *************************\n\nThis element declares the content model for DataSourceDetails, which\ncontains a description of a data source referenced by the PropertyData\nelement. DataSourceDetails has one required attribute, id, which may be\narbitrarily assigned but must be unique among id attributes assigned\nelsewhere in a MatML document. DataSourceDetails also has one\noptional attribute, type, for specifying the type of the data source\n(examples include \"unpublished report,\" \"journal,\" \"handbook,\" etc.)\nDataSourceDetails is composed of the following elements.\n\nName contains the name of the data source and has one optional\nattribute, authority, for identifying an authoritative source of data\nsource names. Name must occur once and only once within the\nDataSourceDetails element.\n\nNotes contains any additional information concerning the data source\nand may occur once or not at all within the DataSourceDetails element.\t\t\t")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	DataSourceDetailsNotebook->AddPage(DataSourceDetailsPanel, wxT("MatML Data."), b_dflt);
	DataSourceDetailsNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return DataSourceDetailsNotebook;
}

void DataSourceDetails_GUI_Base::Update( DataSourceDetails* element)
{
	wxString str;

	m_DataSourceDetails_ID_GUI->Update(element);

	str.clear();
	{
		const DataSourceDetails::type_optional& cont(element->type());
		if (cont.present()) str << _std2wx(cont.get());
		m_DataSourceDetailsTypeTextCtrl->ChangeValue(str);
	}

	Show(true);
}

::std::string DataSourceDetails_GUI_Base::Label(::std::string name, ::std::string id)
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
wxTreeItemId DataSourceDetails_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	DataSourceDetails& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label;
	label.assign("DataSourceDetails-");
	label.append(Label(Element.Name(), Element.id()));

	//strDataSourceDetailsId.Add(str);


	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, new MatMLTreeItemData(&Element));

	//MatML Attributes
	//Id
	//type

	//Setup Elements Name
	if (Element.Name() != "")
		Name_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, Element.Name(), wxTreeItemId());

	//Setup Elements Notes
	{
		DataSourceDetails::Notes_optional& cont(Element.Notes());
		if (cont.present())
			Notes_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, wxTreeItemId());
	}

	return CurrentId;
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
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void DataSourceDetails_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	m_DataSourceDetails_ID_GUI->SetEvtHandlerVar(MatMLTreeCtrl, MatMLDoc);
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
		DataSourceDetails* const Element = boost::any_cast<DataSourceDetails* const>(item->GetAnyMatMLDataPointer());	//<<--Speciallized
		if (Element != 0) {
			DataSourceDetails::type_optional& cont(Element->type()); //<<--Speciallized
			wxString str(m_DataSourceDetailsTypeTextCtrl->GetValue()); //<<--Speciallized
			DataSourceDetails::type_type NewData((const char*)str.mb_str(wxConvUTF8)); //<<--Speciallized
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
