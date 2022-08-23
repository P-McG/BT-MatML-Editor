#include <wx/config.h>
#include "BT_MatML_ParentMaterial_GUI.h"

using namespace bellshire;

ParentMaterial_GUI_Base::ParentMaterial_GUI_Base()
	:m_GUI(nullptr), 
	m_ParentMaterialIDChoice(nullptr), 
	m_ParentMaterialFirstClassFilterComboBox(nullptr), 
	m_ParentMaterialSecondClassFilterComboBox(nullptr), 
	m_ParentMaterialThirdClassFilterComboBox(nullptr), 
	m_ParentMaterialFourthClassFilterComboBox(nullptr), 
	m_ParentMaterialFifthClassFilterComboBox(nullptr)
{

}

ParentMaterial_GUI_Base::ParentMaterial_GUI_Base(wxWindow* parent)
	: m_GUI(nullptr),
	m_ParentMaterialIDChoice(nullptr),
	m_ParentMaterialFirstClassFilterComboBox(nullptr),
	m_ParentMaterialSecondClassFilterComboBox(nullptr),
	m_ParentMaterialThirdClassFilterComboBox(nullptr),
	m_ParentMaterialFourthClassFilterComboBox(nullptr),
	m_ParentMaterialFifthClassFilterComboBox(nullptr)
{
	m_GUI = Create(parent, 
		m_ParentMaterialIDChoice,
		m_ParentMaterialFirstClassFilterComboBox,
		m_ParentMaterialSecondClassFilterComboBox,
		m_ParentMaterialThirdClassFilterComboBox,
		m_ParentMaterialFourthClassFilterComboBox,
		m_ParentMaterialFifthClassFilterComboBox);
}

ParentMaterial_GUI_Base::~ParentMaterial_GUI_Base() {
	/*parent will distroy Ctrl or window */
}


/// <summary>
/// Create the GUI for the ParentMaterial MatML Data and Info
/// </summary>
/// <param name="parent"></param>
/// <param name="ParentMaterialPanel"></param>
/// <param name="ParentMaterialIDChoice"></param>
/// <param name="ParentMaterialFirstClassFilterComboBox"></param>
/// <param name="ParentMaterialSecondClassFilterComboBox"></param>
/// <param name="ParentMaterialThirdClassFilterComboBox"></param>
/// <param name="ParentMaterialFourthClassFilterComboBox"></param>
/// <param name="ParentMaterialFifthClassFilterComboBox"></param>
/// <returns>bool</returns>
wxNotebook* ParentMaterial_GUI_Base::Create(wxWindow* parent, wxChoice*& ParentMaterialIDChoice, wxComboBox*& ParentMaterialFirstClassFilterComboBox, wxComboBox*& ParentMaterialSecondClassFilterComboBox, wxComboBox*& ParentMaterialThirdClassFilterComboBox, wxComboBox*& ParentMaterialFourthClassFilterComboBox, wxComboBox*& ParentMaterialFifthClassFilterComboBox)
{
	wxNotebook* ParentMaterialNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	ParentMaterialNotebook->Hide();
	ParentMaterialNotebook->SetMinSize(wxSize(400, 500));

	wxScrolledWindow* ParentMaterialPanel = new wxScrolledWindow(ParentMaterialNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	ParentMaterialPanel->SetScrollRate(5, 5);

	wxFlexGridSizer* fgSizer121 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer121->AddGrowableCol(1);
	fgSizer121->SetFlexibleDirection(wxBOTH);
	fgSizer121->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText71 = new wxStaticText(ParentMaterialPanel, wxID_ANY, wxT("Parent Material ID"), wxDefaultPosition, wxDefaultSize, 0);
	staticText71->Wrap(-1);
	fgSizer121->Add(staticText71, 0, wxALL, 5);

	wxArrayString ParentMaterialIDChoiceChoices;
	ParentMaterialIDChoice = new wxChoice(ParentMaterialPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ParentMaterialIDChoiceChoices, 0);
	ParentMaterialIDChoice->SetSelection(0);
	ParentMaterialIDChoice->SetMinSize(wxSize(300, -1));

	fgSizer121->Add(ParentMaterialIDChoice, 1, wxALL | wxEXPAND, 5);

	fgSizer121->Add(0, 0, 1, wxEXPAND, 5);

	wxStaticBoxSizer* sbSizer2 = new wxStaticBoxSizer(new wxStaticBox(ParentMaterialPanel, wxID_ANY, wxT("BulkDetails Class Filters")), wxVERTICAL);

	wxFlexGridSizer* fgSizer137 = new wxFlexGridSizer(5, 1, 0, 0);
	fgSizer137->AddGrowableCol(0);
	fgSizer137->SetFlexibleDirection(wxBOTH);
	fgSizer137->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	ParentMaterialFirstClassFilterComboBox = new wxComboBox(ParentMaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	ParentMaterialFirstClassFilterComboBox->SetMinSize(wxSize(300, -1));

	fgSizer137->Add(ParentMaterialFirstClassFilterComboBox, 1, wxALL | wxEXPAND, 5);

	ParentMaterialSecondClassFilterComboBox = new wxComboBox(ParentMaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	ParentMaterialSecondClassFilterComboBox->SetMinSize(wxSize(300, -1));

	fgSizer137->Add(ParentMaterialSecondClassFilterComboBox, 1, wxALL | wxEXPAND, 5);

	ParentMaterialThirdClassFilterComboBox = new wxComboBox(ParentMaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL,  wxCB_READONLY);
	ParentMaterialThirdClassFilterComboBox->SetMinSize(wxSize(300, -1));

	fgSizer137->Add(ParentMaterialThirdClassFilterComboBox, 1, wxALL | wxEXPAND, 5);

	ParentMaterialFourthClassFilterComboBox = new wxComboBox(ParentMaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	ParentMaterialFourthClassFilterComboBox->SetMinSize(wxSize(300, -1));

	fgSizer137->Add(ParentMaterialFourthClassFilterComboBox, 1, wxALL | wxEXPAND, 5);

	ParentMaterialFifthClassFilterComboBox = new wxComboBox(ParentMaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	ParentMaterialFifthClassFilterComboBox->SetMinSize(wxSize(300, -1));

	fgSizer137->Add(ParentMaterialFifthClassFilterComboBox, 1, wxALL | wxEXPAND, 5);

	sbSizer2->Add(fgSizer137, 1, wxEXPAND, 5);

	fgSizer121->Add(sbSizer2, 1, wxEXPAND, 5);

	ParentMaterialPanel->SetSizer(fgSizer121);
	ParentMaterialPanel->Layout();
	fgSizer121->Fit(ParentMaterialPanel);

	MatMLInfo_GUI matMLInfo_GUI(ParentMaterialNotebook,
		wxT("************ Class::ParentMaterial*************************\n\nParentMaterial is an reference by ID to another Material in the \nMatML_Doc and can occur only once in the Class element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	ParentMaterialNotebook->AddPage(ParentMaterialPanel, wxT("MatML Data."), b_dflt);
	ParentMaterialNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return ParentMaterialNotebook;
}



/// <summary>
/// 
/// Updates the Parent Material Panel
/// includes getting the list of Material id's and comparing the materials class names to the filters
/// </summary>
/// <param name="element"></param>
void ParentMaterial_GUI_Base::Update( ParentMaterial* element, const ::boost::shared_ptr<MatML_Doc> MatMLDoc)
{

	//Clear it and start fresh
	m_ParentMaterialIDChoice->Clear();

	//FilterComboBoxClear();

	UpdateFilterComboBox(MatMLDoc);
	UpdateIDChoiceChoices(MatMLDoc);

	const xml_schema::idref& idref(element->id());
	const Material* parentmaterial(dynamic_cast<const Material*>(&*idref));

	::std::string label, id;
	if (parentmaterial) {
		if (parentmaterial->id().present()) id = parentmaterial->id().get();
		label.assign(Label(parentmaterial->BulkDetails().Name(), id));
	}
		
	m_ParentMaterialIDChoice->SetStringSelection(_std2wx(label));

	Show(true);
}

void ParentMaterial_GUI_Base::FilterComboBoxClear()
{
	m_ParentMaterialFirstClassFilterComboBox->Clear();
	m_ParentMaterialSecondClassFilterComboBox->Clear();
	m_ParentMaterialThirdClassFilterComboBox->Clear();
	m_ParentMaterialFourthClassFilterComboBox->Clear();
	m_ParentMaterialFifthClassFilterComboBox->Clear();
}

void ParentMaterial_GUI_Base::UpdateFiltersIDChoiceChoices(::boost::shared_ptr<MatML_Doc> MatMLDoc)
{
	UpdateFilterComboBox(MatMLDoc);
	UpdateIDChoiceChoices(MatMLDoc);
}

void ParentMaterial_GUI_Base::UpdateFilterComboBox(::boost::shared_ptr<MatML_Doc> MatMLDoc)
{
	::std::list<Name*> classNames(Utilities::GetMatMLDocClassNames(MatMLDoc));
	wxArrayString wxClassNames;

	wxClassNames.Add("");//Add a blank for removing class selection

	for (::std::list<Name*>::iterator iterClass(classNames.begin()); iterClass != classNames.end(); ++iterClass) {
		Name* name(*iterClass);
		const xml_schema::string& tmp(*name);
		wxString str(_std2wx(tmp));

		wxClassNames.Add(str);
	}
	
	m_ParentMaterialFirstClassFilterComboBox->Set(wxClassNames);
	m_ParentMaterialSecondClassFilterComboBox->Set(wxClassNames);
	m_ParentMaterialThirdClassFilterComboBox->Set(wxClassNames);
	m_ParentMaterialFourthClassFilterComboBox->Set(wxClassNames);
	m_ParentMaterialFifthClassFilterComboBox->Set(wxClassNames);
}

void ParentMaterial_GUI_Base::UpdateIDChoiceChoices(::boost::shared_ptr<MatML_Doc> MatMLDoc)
{

	wxArrayString strFilters;
	strFilters.Add(m_ParentMaterialFirstClassFilterComboBox->GetValue());
	strFilters.Add(m_ParentMaterialSecondClassFilterComboBox->GetValue());
	strFilters.Add(m_ParentMaterialThirdClassFilterComboBox->GetValue());
	strFilters.Add(m_ParentMaterialFourthClassFilterComboBox->GetValue());
	strFilters.Add(m_ParentMaterialFifthClassFilterComboBox->GetValue());

	//Setup the id String for ParentMaterialID.id choices boxes
	std::list< std::pair< Material*, xml_schema::string> > materialid = Utilities::GetMaterialIDPair(MatMLDoc, Utilities::wx2std(strFilters));

	for (std::list< std::pair< Material*, xml_schema::string> >::iterator iter(materialid.begin()); iter != materialid.end(); ++iter) {
		::std::string label(Label(iter->first->BulkDetails().Name(), iter->second));
		m_ParentMaterialIDChoice->Append(_std2wx(label), (void*)iter->first);
	}
	
}


::std::string ParentMaterial_GUI_Base::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}
::std::string ParentMaterial_GUI_Base::LabelToId(::std::string label)
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
wxTreeItemId ParentMaterial_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
	const wxTreeItemId& ParentId, 
	ParentMaterial& Element, 
	const wxTreeItemId& PreviousId
)
{
	::std::string label, id;
	label.assign("ParentMaterial-");
	if (!Element.id().empty()) {
		const xml_schema::idref& idref(Element.id());
		const Material* parentmaterial(dynamic_cast<const Material*>(&*idref));
		if (parentmaterial) {
			if (parentmaterial->id().present()) id.assign(parentmaterial->id().get());
			label = Label(parentmaterial->BulkDetails().Name(), id);
		}
	}

	MatMLTreeItemData* data = new MatMLTreeItemData(&Element);

	wxTreeItemId CurrentId;

	if (PreviousId.IsOk())
		CurrentId = MatMLTreeCtrl->InsertItem(ParentId, PreviousId, _std2wx(label), -1, -1, data);
	else
		CurrentId = MatMLTreeCtrl->AppendItem(ParentId, _std2wx(label), -1, -1, data);

	//Setup MatML Attribute
	//SetupId();

	//Setup Element
	//--NONE--
	return CurrentId;
}


void ParentMaterial_GUI_Base::SetConnect()
{
	m_ParentMaterialIDChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialIDChoice), NULL, this);
	m_ParentMaterialFirstClassFilterComboBox->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialClassFilterComboBox), NULL, this);
	m_ParentMaterialSecondClassFilterComboBox->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialClassFilterComboBox), NULL, this);
	m_ParentMaterialThirdClassFilterComboBox->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialClassFilterComboBox), NULL, this);
	m_ParentMaterialFourthClassFilterComboBox->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialClassFilterComboBox), NULL, this);
	m_ParentMaterialFifthClassFilterComboBox->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(ParentMaterial_GUI_Base::OnParentMaterialClassFilterComboBox), NULL, this);
}


/// <summary>
/// Constructor for the derived class
/// </summary>
ParentMaterial_GUI::ParentMaterial_GUI() 
	: ParentMaterial_GUI_Base(),
	m_MatMLTreeCtrl(nullptr),
	m_MatMLDoc(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
ParentMaterial_GUI::ParentMaterial_GUI(wxWindow* parent)
	: ParentMaterial_GUI_Base(parent), m_MatMLTreeCtrl(nullptr), m_MatMLDoc(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
ParentMaterial_GUI::~ParentMaterial_GUI() {
	/*parent will distroy Ctrl or window */
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParentMaterial_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	SetMatMLDoc(MatMLDoc);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParentMaterial_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void ParentMaterial_GUI::SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	m_MatMLDoc = MatMLDoc;
}

void ParentMaterial_GUI::OnParentMaterialIDChoice(wxCommandEvent& event)
{
	// These pointers are required
	if (m_MatMLTreeCtrl == nullptr ) { event.Skip(); return; };

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		ParentMaterial* const Element = boost::any_cast<ParentMaterial* const>(item->GetAnyMatMLDataPointer());	 
		if (Element != 0) {

			int choiceindex(m_ParentMaterialIDChoice->GetSelection());
			if (choiceindex == wxNOT_FOUND) return;

			Material* material(static_cast<Material*>(m_ParentMaterialIDChoice->GetClientData(choiceindex)));
			if (!material) return;

			if (!material->id().present()) return;

			//Set up the MatML Data
			ParentMaterial::id_type NewData(material->id().get());
			(Element->id()) = NewData;

			//Set up the MatMLTreeCtrl Class Label
			wxString str;
			str << _std2wx(material->id().get());
			wxString name;
			if (!material->BulkDetails().Name().empty()) {
				name << wxT("Class-") << _std2wx(material->BulkDetails().Name());
				m_MatMLTreeCtrl->SetItemText(m_MatMLTreeCtrl->GetItemParent(itemId), name);
			}

			//Set up MatMLTreeCtrl Parent Material Label
			::std::string label;
			label.assign("Parent Material-");
			::std::string id;
			if (material->id().present()) id.assign(material->id().get());
			label.append(Label(material->BulkDetails().Name(), id.c_str()));
			m_MatMLTreeCtrl->SetItemText(itemId, _std2wx(label));

			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}

void ParentMaterial_GUI::OnParentMaterialClassFilterComboBox(wxCommandEvent& event)
{
	// These pointers are required
	if (m_MatMLTreeCtrl != nullptr && m_MatMLDoc != nullptr) {
		wxString Selection = m_ParentMaterialIDChoice->GetStringSelection();

		//Clear it and start fresh
		m_ParentMaterialIDChoice->Clear();

		UpdateIDChoiceChoices(m_MatMLDoc);

		if (m_ParentMaterialIDChoice->SetStringSelection(Selection) == false) {
			std::string msg("ParentMaterial ID Filtered Out.\nPlease select another ParentMaterial ID, \nOR adjust the filters before poceeding.\nNote: Leaving ParentMaterial ID blank will create parsing errors!");
			wxMessageDialog Dialog(NULL, msg, _("MatML Message"), wxOK, wxDefaultPosition);
			Dialog.ShowModal();
		}
	}
	else{ 
		event.Skip();
	};
}
