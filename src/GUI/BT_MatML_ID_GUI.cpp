#include <wx/config.h>
#include "BT_MatML_ID_GUI.h"
#include "BT_MatML_GatherIDRefs.h"

using namespace bellshire;


ID_GUI_Base::ID_GUI_Base() 
	: m_GenerateUuidButton(nullptr),
	m_IDTextCtrl(nullptr),
	m_ReplaceIDRefs(nullptr),
	m_GUI(nullptr)
{

}

ID_GUI_Base::ID_GUI_Base(wxWindow* parent) 
	: m_GenerateUuidButton(nullptr), 
	m_IDTextCtrl(nullptr),
	m_ReplaceIDRefs(nullptr),
	m_GUI(nullptr)
{
	m_GUI = Create(parent, m_GenerateUuidButton, m_IDTextCtrl, m_ReplaceIDRefs);
	SetConnect();
}

ID_GUI_Base::~ID_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Creates a GUI for the UUID generation and the custom ID textctrl.
/// </summary>
/// <param name="parent"> Parent Window</param>
/// <param name="GenerateUuidButton"></param>
/// <param name="IDTextCtrl"></param>
/// <returns>wxPanel*</returns>
wxPanel* ID_GUI_Base::Create(wxWindow* parent, wxButton*& GenerateUuidButton, wxTextCtrl*& IDTextCtrl, wxCheckBox*& ReplaceIDRefs)
{
	wxPanel* IDCtrlPanel = new wxPanel(parent);

	wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(2);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->AddGrowableRow(0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	fgSizer1->AddSpacer(0);

	GenerateUuidButton = new wxButton(IDCtrlPanel, wxID_ANY, wxT("Uuid->ID"), wxDefaultPosition, wxDefaultSize, 0);

	fgSizer1->Add(GenerateUuidButton, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText = new wxStaticText(IDCtrlPanel, wxID_ANY, wxT("ID"), wxDefaultPosition, wxDefaultSize, 0);
	staticText->Wrap(-1);

	fgSizer1->Add(staticText, 0, wxALL, 5);

	IDTextCtrl = new wxTextCtrl(IDCtrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	IDTextCtrl->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVEBORDER));

	fgSizer1->Add(IDTextCtrl, 1, wxALL | wxEXPAND, 5);

	fgSizer1->AddSpacer(0);

	ReplaceIDRefs = new wxCheckBox(IDCtrlPanel, wxID_ANY, wxT("Replace all IDREFs and maintain conectivity"), wxDefaultPosition, wxDefaultSize, 0);
	ReplaceIDRefs->SetValue(true);
	staticText->Wrap(-1);

	fgSizer1->Add(ReplaceIDRefs, 0, wxALL, 5);

	fgSizer1->AddSpacer(0);

	wxStaticText* staticText1 = new wxStaticText(IDCtrlPanel, wxID_ANY, wxT("Note: \n1) xs:IDs cannot have \":\" characters anywhere in the name. \n2) cannot have a digit as the first character of the ID"), wxDefaultPosition, wxDefaultSize, 0);
	//staticText1->Wrap(-1);
	fgSizer1->Add(staticText1, 0, wxALL, 5);


	IDCtrlPanel->SetSizer(fgSizer1);
	IDCtrlPanel->Layout();
	fgSizer1->Fit(IDCtrlPanel);

	return IDCtrlPanel;
}


/// <summary>
/// Updates the MatML_GUI from the MatML element
/// </summary>
/// <param name="element"></param>
void ID_GUI_Base::Update( Material* element)
{

	wxString str;
	
	const Material::id_optional& cont(element->id());
	if (cont.present()) str << _std2wx((*cont));

	m_IDTextCtrl->ChangeValue(str);

	Show(true);

}

void ID_GUI_Base::Update( ComponentDetails* element)
{
	wxString str;

	const ComponentDetails::id_optional& cont(element->id());
	if (cont.present()) str << _std2wx(element->id().get());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);

}

void ID_GUI_Base::Update( TestConditionDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( SpecimenDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( SourceDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( PropertyDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( ParameterDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( MeasurementTechniqueDetails* element)
{
	wxString str;
	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}

void ID_GUI_Base::Update( DataSourceDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}


void ID_GUI_Base::Update( AuthorityDetails* element)
{
	wxString str;

	str << _std2wx(element->id());
	m_IDTextCtrl->ChangeValue(str);

	Show(true);
}


void ID_GUI_Base::SetConnect()
{
	m_GenerateUuidButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ID_GUI_Base::OnGenerateUuidButton), NULL, this);
	m_IDTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ID_GUI_Base::OnIDTextCtrl), NULL, this);
	m_IDTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ID_GUI_Base::OnIDTextCtrl), NULL, this);

}


/// <summary>
/// Constructor for the derived class
/// </summary>
ID_GUI::ID_GUI() : 
	ID_GUI_Base(), 
	m_MatMLTreeCtrl(nullptr)
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ID_GUI::ID_GUI(wxWindow* parent)
	: ID_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ID_GUI::~ID_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ID_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc> MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	SetMatMLDoc(MatMLDoc);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ID_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Set the Event Handler Variable associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ID_GUI::SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	m_MatMLDoc = MatMLDoc;
}

void ID_GUI::SwapIDRefs(MatML_Doc* matmldoc, xml_schema::idref& oldid, xml_schema::idref& newid)
{
	if (!oldid.empty()) {
		GatherIDRefs gatheridrefs;
		auto& cont(gatheridrefs.IDRefs(matmldoc));
		for (auto i : cont) {
			if (*i == oldid) {
				*i = xml_schema::idref(newid);
			}
		}
	}
}




/// <summary>
/// Event Handler call
/// Overwrites the base class calls
/// </summary>
/// <param name="event"></param>
void ID_GUI::OnGenerateUuidButton(wxCommandEvent& event)
{
	if (m_MatMLTreeCtrl == nullptr) {
		event.Skip();
		return;
	}

	wxTreeItemId ItemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* Item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(ItemId));

	boost::any any_ptr(Item->GetAnyMatMLDataPointer());

	ExchangeIDRefWithOptionalID<Material>(any_ptr);
	ExchangeIDRefWithID<TestConditionDetails>(any_ptr);
	ExchangeIDRefWithID<SpecimenDetails>(any_ptr);
	ExchangeIDRefWithID<PropertyDetails>(any_ptr);
	ExchangeIDRefWithID<ParameterDetails>(any_ptr);
	ExchangeIDRefWithID<MeasurementTechniqueDetails>(any_ptr);
	ExchangeIDRefWithID<DataSourceDetails>(any_ptr);
	ExchangeIDRefWithOptionalID<ComponentDetails>(any_ptr);
	ExchangeIDRefWithID<AuthorityDetails>(any_ptr);
	ExchangeIDRefWithID<SourceDetails>(any_ptr);
}

bool ID_GUI::Warning()
{
		::string msg("Replacing an ID will break connectivity!\n Do you want to proceed?");
		wxMessageDialog WarningDialog(NULL, msg, _("MatML Editor"), wxYES_NO | wxNO_DEFAULT | wxICON_EXCLAMATION, wxDefaultPosition);
		return (WarningDialog.ShowModal() == wxID_YES);
}

::string ID_GUI::GetUUIDLabel()
{
	/// xs:IDs cannot have : characters anywhere in 
	/// the name and cannot have a digit as the 
	/// first character of the name.

	wxConfig config(wxT("BTMatML"));;
	wxString uuidlabel_dflt("BT");
	bool b=config.Read(wxT("/General/UUIDPrefix"), &uuidlabel_dflt);

	std::string uuidlabel(_wx2std(uuidlabel_dflt));
	uuid_class iduuid;

	uuidlabel.append(cast_stream< ::string>("-"));

	uuidlabel.append(cast_stream< ::string>(iduuid));

	return uuidlabel;
}

/// <summary>
/// Generate the UUID
/// </summary>
/// <param name="material"></param>
void ID_GUI::GenerateUuid(Material* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id().set(NewId);
}

void ID_GUI::GenerateUuid(ComponentDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id().set(NewId);
}

void ID_GUI::GenerateUuid(TestConditionDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(SpecimenDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(SourceDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(PropertyDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(ParameterDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(MeasurementTechniqueDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(DataSourceDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::GenerateUuid(AuthorityDetails* element)
{
	xml_schema::id NewId(GetUUIDLabel());
	element->id(NewId);
}

void ID_GUI::OnIDTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Material* const Element = boost::any_cast<Material* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			Material::id_optional& cont(Element->id());
			wxString str(m_IDTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			try {
				Material::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				if (cont.present()) { cont.reset(); cont.set(NewData); }
				else cont.set(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			//			wxString label;
			//			label <<  _std2wx(Element->BulkDetails().Name().c_str());
			//			m_MatMLTreeCtrl->SetItemText(itemId,label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		AuthorityDetails* Element = boost::any_cast<AuthorityDetails* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				AuthorityDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("AuthorityDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		PropertyDetails* const Element = boost::any_cast<PropertyDetails* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				PropertyDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("PropertyDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		ComponentDetails* const Element = boost::any_cast<ComponentDetails* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			ComponentDetails::id_optional& cont(Element->id());
			wxString str(m_IDTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			try {
				ComponentDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				if (cont.present()) { cont.reset(); cont.set(NewData); }
				else cont.set(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);

				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("ComponentDetails-");
			label << _std2wx(Element->Name());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		MeasurementTechniqueDetails* const element = boost::any_cast<MeasurementTechniqueDetails* const>(item->GetAnyMatMLDataPointer());
		if (element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				MeasurementTechniqueDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				element->id(NewData);

				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("MeasurementTechniqueDetails-");
			label << _std2wx(element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		ParameterDetails* const Element = boost::any_cast<ParameterDetails* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				ParameterDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				//wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("ParameterDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		SourceDetails* const Element = boost::any_cast<SourceDetails* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());
			try {
				SourceDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);/*
				wxString msg(wxT(""));
				m_statusBar1->SetStatusText(msg);*/
			}
			catch (const xml_schema::duplicate_id&) {
				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT("!!! DUPLICATE ID !!!"));
				//m_statusBar1->SetStatusText(msg);
			}
	
			wxString label;
			label << wxT("SourceDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);
	
			return;
		}
	}
	catch (const boost::bad_any_cast&) {};// do nothing until the last one

	try {
		SpecimenDetails* const Element = boost::any_cast<SpecimenDetails* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				SpecimenDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("SpecimenDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {}// do nothing until the last one

	try {
		TestConditionDetails* const Element = boost::any_cast<TestConditionDetails* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				TestConditionDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("TestConditionDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {}// do nothing until the last one

	try {
		DataSourceDetails* const Element = boost::any_cast<DataSourceDetails* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {
			wxString str(m_IDTextCtrl->GetValue());

			try {
				DataSourceDetails::id_type NewData((const char*)str.mb_str(wxConvUTF8));
				Element->id(NewData);
				wxColour clr; clr.Set(0, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
				//wxString msg(wxT(""));
				//m_statusBar1->SetStatusText(msg);
			}
			catch (...) {
				wxString msg;
				//msg << wxT("!!! DUPLICATE ID !!!");
				//m_statusBar1->SetStatusText(msg);

				wxColour clr; clr.Set(255, 0, 0);
				m_MatMLTreeCtrl->SetItemTextColour(itemId, clr);
			}

			wxString label;
			label << wxT("DataSourceDetails-");
			label << _std2wx(Element->id());
			m_MatMLTreeCtrl->SetItemText(itemId, label);

			return;
		}
	}
	catch (const boost::bad_any_cast&) {}// do nothing until the last one

}
