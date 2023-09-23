#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_Material_GUI.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"
#include "bellshire/utilities/Uuid-Utility.h"

using namespace bellshire::GUI;

/// <summary>
/// Constructor for the base class
/// </summary>
Material_GUI_Base::Material_GUI_Base() 
	:m_Material_ID_GUI(nullptr), 
	m_MaterialLayersTextCtrl(nullptr), 
	m_MaterialLFORTextCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the base class
/// </summary>
/// <param name="parent"></param>
Material_GUI_Base::Material_GUI_Base(wxWindow* parent)
	:m_Material_ID_GUI(nullptr), 
	m_MaterialLayersTextCtrl(nullptr), 
	m_MaterialLFORTextCtrl(nullptr)
{
	m_GUI = Create(parent, m_Material_ID_GUI, m_MaterialLayersTextCtrl, m_MaterialLFORTextCtrl);
	SetConnect();
}

Material_GUI_Base::~Material_GUI_Base() {
	/*parent will destroy Ctrl or window */
	delete m_Material_ID_GUI;//this is neither a window nor a ctrl.
}

ID_GUI* Material_GUI_Base::GetMaterial_ID_GUI()
{
	return m_Material_ID_GUI;
}

wxTextCtrl* Material_GUI_Base::GetMaterialLayersTextCtrl()
{
	return m_MaterialLayersTextCtrl;
}

wxTextCtrl* Material_GUI_Base::GetMaterialLFORTextCtrl()
{
	return m_MaterialLFORTextCtrl;
}

/// <summary>
/// Create GUI for the Material MatML Data and Info.
/// Static function
/// </summary>
/// <param name="parent"></param>
/// <param name="Material_ID_GUI"></param>
/// <param name="MaterialLayersTextCtrl"></param>
/// <param name="MaterialLFORTextCtrl"></param>
/// <returns>wxNotebook*</returns>
wxNotebook* Material_GUI_Base::Create(wxWindow* parent, 
	ID_GUI*& Material_ID_GUI, 
	wxTextCtrl*& MaterialLayersTextCtrl, 
	wxTextCtrl*& MaterialLFORTextCtrl
)
{
	wxNotebook* MaterialNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	MaterialNotebook->Hide();
	MaterialNotebook->SetMinSize(wxSize(400, 500));

	wxWindow* MaterialPanel(CreateMaterialPanel(MaterialNotebook,
		Material_ID_GUI,
		MaterialLayersTextCtrl,
		MaterialLFORTextCtrl
	));

	MatMLInfo_GUI matMLInfo_GUI(MaterialNotebook,
		wxT("********** Material *************************\n\t\t\t\nThis element declares the content model for Material, which contains\nmaterials data. Material has three optional attributes.\n\nThe first attribute, id, may be used as an identification specifier for the\nmaterial, which is especially useful for complex systems such as\ncomposite laminates.\n\nThe second attribute, layers, may be used to indicate the number of\nlayers in complex systems such as composite laminates.\n\nThe third attribute, local_frame_of_reference, may be used as an\nidentification specifier for the local material orientation relative to the\nglobal frame of reference, which is especially useful for complex\nsystems such as anisotropic materials.\n\nMaterial is composed of the following elements.\n\nBulkDetails contains a description of the bulk material and must occur\nonce and only once within the Material element. For additional\ninformation, see the documentation for the BulkDetails element.\n\nComponentDetails contains a description of a component within the\nbulk material and may occur zero or more times within the Material\nelement. ComponentDetails may be used to describe complex materials\nsystems such as welds (e.g. the base metal, the heat affected zone,\nand the weld metal) or composites (e.g. the whiskers, fibers, and\nmatrix of a fiber-reinforced composite material). For additional\ninformation, see the documentation for the ComponentDetails\nelement.\n\nGraphs contains descriptions of two dimensional graphics and may\noccur once or not at all within the Material element. For additional\ninformation, see the documentation for the Graphs element.\n\nGlossary contains descriptions of the material and property terms\nused in the document and may occur once or not at all within the\nMaterial element. For additional information, see the documentation\nfor the Glossary element.")
	);

	bool b, b_dflt(false);//temps
		wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);

	MaterialNotebook->AddPage(MaterialPanel, wxT("MatML Data."), b_dflt);
	MaterialNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);

	return MaterialNotebook;
}

wxWindow* Material_GUI_Base::CreateMaterialPanel(wxWindow* parent,
	ID_GUI*& Material_ID_GUI,
	wxTextCtrl*& MaterialLayersTextCtrl,
	wxTextCtrl*& MaterialLFORTextCtrl
)
{
	wxScrolledWindow* MaterialPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	MaterialPanel->SetScrollRate(5, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	Material_ID_GUI = new ID_GUI(MaterialPanel);
	bSizer1->Add(Material_ID_GUI->get(), 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizer3->AddGrowableCol(1);
	fgSizer3->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxStaticText* staticText4 = new wxStaticText(MaterialPanel, wxID_ANY, wxT("Layers"), wxDefaultPosition, wxDefaultSize, 0);
	staticText4->Wrap(-1);
	fgSizer3->Add(staticText4, 0, wxALL, 5);

	MaterialLayersTextCtrl = new wxTextCtrl(MaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer3->Add(MaterialLayersTextCtrl, 1, wxALL | wxEXPAND, 5);

	wxStaticText* staticText5 = new wxStaticText(MaterialPanel, wxID_ANY, wxT("Local Frame of Reference"), wxDefaultPosition, wxDefaultSize, 0);
	staticText5->Wrap(-1);
	fgSizer3->Add(staticText5, 0, wxALL, 5);

	MaterialLFORTextCtrl = new wxTextCtrl(MaterialPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	fgSizer3->Add(MaterialLFORTextCtrl, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(fgSizer3, 1, wxEXPAND, 5);

	MaterialPanel->SetSizer(bSizer1);
	MaterialPanel->Layout();
	bSizer1->Fit(MaterialPanel);

	return MaterialPanel;
}

/// <summary>
/// Updates the MatML_GUI from the MatML element
/// </summary>
/// <param name="element"></param>
void Material_GUI_Base::Update( const observer_ptr<Material> element)
{
	wxString str;

	m_Material_ID_GUI->Update(element);

	if (element) {
		str.clear();
		{
			const Material::layers_optional& cont(element->layers());
			if (cont.present()) str << double(*cont);
			m_MaterialLayersTextCtrl->ChangeValue(str);
		}

		str.clear();
		{
			const Material::local_frame_of_reference_optional& cont(element->local_frame_of_reference());
			if (cont.present()) str << _std2wx((*cont));
			m_MaterialLFORTextCtrl->ChangeValue(str);
		}

		ShowGUI(true);
	}

}

wxString Material_GUI_Base::GetTreeLabel(const observer_ptr<Material> element)
{
	wxString str;

	if (element) {
		str << _std2wx(element->BulkDetails().Name());
		//	if(Element.id().present())
		//		str << _std2wx(*element.id());
		//	else
		//		str << "NewMaterial";
	}

	return str;
}


/// <summary>
/// This was used only to make the old data format compatible with the new arrangement
/// </summary>
void Material_GUI_Base::ReplaceIDwithUuid(MatML_Doc& doc)
{
	MatML_Doc::Material_sequence& matcont(doc.Material());
	MatML_Doc::Material_iterator matiter(matcont.begin());
	for (; matiter != matcont.end(); ++matiter) {
		if (matiter->id().present()) {
			::vector<ParentMaterial*> compparentmateriallist;

			MatML_Doc::Material_sequence& matcont2(doc.Material());
			MatML_Doc::Material_iterator matiter2(matcont2.begin());
			for (; matiter2 != matcont2.end(); ++matiter2) {
				if (!matiter2->ComponentDetails().empty()) {
					Material::ComponentDetails_sequence& compcont(matiter2->ComponentDetails());
					Material::ComponentDetails_iterator compiter(compcont.begin());
					for (; compiter != compcont.end(); ++compiter) {
						if (!compiter->Class().empty()) {
							ComponentDetails::Class_sequence& classcont(compiter->Class());
							ComponentDetails::Class_iterator classiter(classcont.begin());
							for (; classiter != classcont.end(); ++classiter) {
								if (!classiter->ParentMaterial().empty()) {
									Material* parentmaterial(dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));
									if (&*matiter == parentmaterial) {
										compparentmateriallist.push_back(&classiter->ParentMaterial().front());
									}
								}
							}
						}
					}
				}
			}
			//generate newId
			bellshire::utilities::uuid_class iduuid;

			std::string idlabelstr("BTMAT-");
			idlabelstr.append(cast_stream< std::string>(iduuid));

			Material::id_type NewMatId(idlabelstr.c_str());
			matiter->id().set(NewMatId);

			if (!compparentmateriallist.empty()) {
				::vector<ParentMaterial*>::iterator listiter(compparentmateriallist.begin());
				for (; listiter != compparentmateriallist.end(); ++listiter) {
					(*listiter)->id().clear();
					(*listiter)->id() = ::ParentMaterial::id_type(matiter->id().get());
				}

			}
		}
	}
}

/// <summary>
/// This set-up the Parent MatML Data into a wxTreeCtrl element and then call on the Children to do the same.
/// Static Function
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
/// <param name="Parent"></param>
/// <param name="Element"></param>
/// <param name="materials"></param>
/// <returns></returns>
wxTreeItemId Material_GUI_Base::SetupBranch(TreeCtrlSorted*& MatMLTreeCtrl, wxWindow*& Parent, MatML_Doc& Element, std::vector<Material*>& materials)
{
	if (MatMLTreeCtrl != NULL) {
		MatMLTreeCtrl->DeleteAllItems(); //This also deletes the sizer
		delete MatMLTreeCtrl;
	}

	
	//To find these entries search for occurrences of m_MatMLTreeCtrl

	MatMLTreeCtrl = new TreeCtrlSorted(Parent, wxID_MatMLTreeCtrl, wxDefaultPosition, wxSize(-1, -1), wxTR_HAS_BUTTONS | wxTR_HAS_VARIABLE_ROW_HEIGHT | wxTR_LINES_AT_ROOT | wxTR_SINGLE | wxTR_TWIST_BUTTONS | wxCLIP_CHILDREN | wxNO_BORDER | wxTAB_TRAVERSAL | wxVSCROLL);
	MatMLTreeCtrl->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	MatMLTreeCtrl->SetMinSize(wxSize(200, 500));
	//m_treeCtrl->CreateImageList(size);
	//this->SetShowImages(true);

	wxString str;
	str << wxT("MatML-Doc");
	wxTreeItemId CurrentId = MatMLTreeCtrl->AddRoot(str, -1, -1, new MatMLTreeItemData());

	if (materials.empty()) return CurrentId; // Don't bother doing anything.

	//Setup Element Material
	{
		for (::vector<Material*>::iterator iter(materials.begin()); iter != materials.end(); ++iter) {

			auto material{observer_ptr<Material>(*iter)};
			bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(
				bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{ 
					MatMLTreeCtrl, CurrentId, MatMLTreeCtrl->GetLastChild(CurrentId) 
				});
			Material_GUI::TraverseMatMLTree(material, func1);
		}
	}

	//Setup Element Metadata
	{
		MatML_Doc::Metadata_optional& cont(Element.Metadata());
		if (cont.present()) {
			auto metadata_shared{observer_ptr<Metadata>( & *cont)};
			bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(
				bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{
					MatMLTreeCtrl, CurrentId, MatMLTreeCtrl->GetLastChild(CurrentId)
				});
			Metadata_GUI::TraverseMatMLTree(metadata_shared, func1);
		}
	}

	MatMLTreeCtrl->SortChildren(MatMLTreeCtrl->GetRootItem());//Test code

	MatMLTreeCtrl->SetSize(MatMLTreeCtrl->GetClientSize());
	//m_MatMLTreeCtrl->Layout();

	return CurrentId;
}

/// <summary>
/// Set up the connect between the MatML_GUI and the functions
/// </summary>
void Material_GUI_Base::SetConnect()
{
	m_MaterialLayersTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Material_GUI_Base::OnMaterialLayersTextCtrl), NULL, this);
	m_MaterialLayersTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Material_GUI_Base::OnMaterialLayersTextCtrl), NULL, this);
	m_MaterialLFORTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Material_GUI_Base::OnMaterialLFORTextCtrl), NULL, this);
	m_MaterialLFORTextCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(Material_GUI_Base::OnMaterialLFORTextCtrl), NULL, this);
}

/// <summary>
/// Constructor for the derived class
/// </summary>
Material_GUI::Material_GUI() : Material_GUI_Base(), m_MatMLTreeCtrl(nullptr)
{

}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
/// <param name="MatMLTreeCtrl"></param>
Material_GUI::Material_GUI(wxWindow* parent) 
	: Material_GUI_Base(parent), m_MatMLTreeCtrl(nullptr)
{
	SetConnect();
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Material_GUI::~Material_GUI() {
	/*parent will destroy Ctrl or window */
}

TreeCtrlSorted* Material_GUI::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

observer_ptr<MatML_Doc> Material_GUI::GetMatMLDoc()
{
	return m_MatMLDoc;
}

::boost::any Material_GUI::GetMatMLItemToCopy()
{
	return m_MatMLItemToCopy;
}

/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Material_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	SetMatMLDoc(MatMLDoc);
	m_Material_ID_GUI->SetEvtHandlerVar(m_MatMLTreeCtrl, MatMLDoc);
}


/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Material_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void Material_GUI::SetMatMLDoc(const observer_ptr<MatML_Doc>& matml_doc)
{
	if(matml_doc)
		m_MatMLDoc = matml_doc;
}

void Material_GUI::SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy)
{
	m_MatMLItemToCopy = MatMLItemToCopy;
}

void Material_GUI::OnMaterialLFORTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Material* const Element = boost::any_cast<Material* const>(item->GetAnyMatMLDataPointer());
		if (Element != 0) {

			Material::local_frame_of_reference_optional& cont(Element->local_frame_of_reference());

			wxString str(m_MaterialLFORTextCtrl->GetValue());

			if (str.IsEmpty()) { cont.reset(); return; }

			Material::local_frame_of_reference_type NewLFOR((const char*)str.mb_str(wxConvUTF8));
			if (cont.present()) cont = NewLFOR;
			else cont.set(NewLFOR);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

}

void Material_GUI::OnMaterialLayersTextCtrl(wxCommandEvent& event)
{
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	try {
		Material* const Element = boost::any_cast<Material* const>(item->GetAnyMatMLDataPointer());
		Material::layers_optional& cont(Element->layers());
		if (Element != 0) {
			wxString str(m_MaterialLayersTextCtrl->GetValue());
			if (str.IsEmpty()) { cont.reset(); return; }

			long nLayers;
			str.ToLong(&nLayers);
			Material::layers_type NewLayers(nLayers);
			if (cont.present()) cont = NewLayers;
			else cont.set(NewLayers);
			return;
		}
	}
	catch (const boost::bad_any_cast&) { return; }

	// TODO: Implement OnMaterialLayers
}


void Material_GUI::OnInsertMaterial(wxCommandEvent& event) {
	//Get current position
	wxTreeItemId CurrentItemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* CurrentItem = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(CurrentItemId));

	try {
		auto element{ boost::any_cast<observer_ptr<Material> >(CurrentItem->GetAnyMatMLDataPointer()) };
		auto element_parent_observer{ m_MatMLDoc};

		if (element_parent_observer) {
			wxTreeItemId itemId = m_MatMLTreeCtrl->GetRootItem();

			//Setup Element Material
			auto& cont(element_parent_observer->Material());
			auto iter(cont.begin());
			if (!cont.empty()) {
				for (; iter != cont.end(); ++iter) {
					auto lhs{observer_ptr<Material>(&*iter)};
					auto rhs{element};
					if (lhs && lhs==rhs) {
						cont.push_back(Default<::Material>());
						auto material{ observer_ptr<Material>(&cont.back())};
						bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(
							bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{
								m_MatMLTreeCtrl, itemId, CurrentItemId
							});
						Material_GUI::TraverseMatMLTree( material, func1);
						return;
					}
				}
			}
		}
	}
	catch (const boost::bad_any_cast&) { return; }
}
void Material_GUI::OnInsertBulkDetails(wxCommandEvent& event) { ON_PARENT_INSERT_CHILD(Material, BulkDetails) }
void Material_GUI::OnInsertComponentDetails(wxCommandEvent& event) { ON_PARENT_INSERT_ITER_CONT_CHILD(Material, ComponentDetails) }
void Material_GUI::OnInsertGraphs(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Material, Graphs) }
void Material_GUI::OnInsertGlossary(wxCommandEvent& event) { ON_PARENT_INSERT_CONT_CHILD(Material, Glossary) }

void Material_GUI::OnDeleteBulkDetails(wxCommandEvent& event) { ON_PARENT_DELETE_CHILD(Material, BulkDetails) }
void Material_GUI::OnDeleteComponentDetails(wxCommandEvent& event) {ON_PARENT_DELETE_ITER_CONT_CHILD(Material, ComponentDetails)}
void Material_GUI::OnDeleteGlossary(wxCommandEvent& event) {ON_PARENT_DELETE_CONT_CHILD(Material, Glossary)};
void Material_GUI::OnDeleteGraphs(wxCommandEvent& event) { ON_PARENT_DELETE_CONT_CHILD(Material, Graphs) };

void Material_GUI::OnPasteBulkDetails(wxCommandEvent& event) { ON_PARENT_PASTE_CHILD(Material, BulkDetails) }
void Material_GUI::OnPasteComponentDetails(wxCommandEvent& event) {
	ON_PARENT_PASTE_ITER_CONT_CHILD(Material, ComponentDetails)
}
void Material_GUI::OnPasteGraphs(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Material, Graphs) }
void Material_GUI::OnPasteGlossary(wxCommandEvent& event) { ON_PARENT_PASTE_CONT_CHILD(Material, Glossary) }

void Material_GUI::OnCopyMaterial(wxCommandEvent& event) {
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	try {
		auto element_observer{ boost::any_cast<observer_ptr<Material>>(item->GetAnyMatMLDataPointer())};
		 auto element_parent_observer{ m_MatMLDoc};
		if (element_observer && element_parent_observer) {
			auto& cont(element_parent_observer->Material());
			auto iter(cont.begin());
			for (; iter != cont.end(); ++iter) {
				auto lhs{observer_ptr<Material>(&*iter)};
				auto rhs{element_observer};
				if ( lhs == rhs) {

					//Make a Copy
					Material NewData(*iter);

					wxString NewId;

					//Change the Material's id to some holder BELLSHIRE-TEMP-ID.
					wxString PrevId;
					if (NewData.id().present()) PrevId << _std2wx(NewData.id().get());
					else PrevId << wxT("BELLSHIRE-TEMP-ID");
					NewId << wxT("BELLSHIRE-TEMP-ID");
					NewData.id().set(xml_schema::id(::std::string(NewId.mb_str())));//BULKDETAIL ID

					//Change the ComponentDetails' id to some holder BELLSHIRE-TEMP-ID-#.
					wxArrayString PrevCompId;
					Material::ComponentDetails_sequence& contComp(NewData.ComponentDetails());
					Material::ComponentDetails_iterator iterComp;
					if (!contComp.empty()) {
						PrevCompId.Alloc(contComp.size());
						int IdNum = 0, PrevIdIndex = 0;
						for (iterComp = contComp.begin(); iterComp != contComp.end(); ++iterComp, PrevIdIndex++) {
							if (iterComp->id().present()) {
								PrevCompId.Insert(_std2wx(iterComp->id().get()), PrevIdIndex);
								IdNum++;
								NewId.clear();
								NewId << wxT("BELLSHIRE-TEMP-ID"); NewId << wxT("-"); NewId << IdNum;
								iterComp->id().reset();
								iterComp->id().set(xml_schema::id(std::string(NewId.mb_str())));
							}
						}
					}

					MatML_Doc::Material_iterator NewIter = cont.insert(iter, NewData);

					//Reinstalling the Material's Id's with an appending number
					NewId.clear();
					for (int IdNum = 1;; IdNum++) {
						NewId.clear(); NewId << PrevId; NewId << wxT("-"); NewId << IdNum;
						try {
							NewIter->id().set(m_Material_ID_GUI->GetUUIDLabel());
							break;
						}
						catch (...) {}
					}

					//Reinstalling the ComponentDetails' Id with an appending number
					Material::ComponentDetails_sequence& NewContComp(NewIter->ComponentDetails());
					Material::ComponentDetails_iterator NewIterComp;
					if (!NewContComp.empty()) {
						int PrevIdIndex = 0;
						for (NewIterComp = NewContComp.begin(); NewIterComp != NewContComp.end(); ++NewIterComp, PrevIdIndex++) {
							if (NewIterComp->id().present()) {
								NewId.clear();
								for (int IdNum = 1;; IdNum++) {
									NewId << PrevCompId[PrevIdIndex]; NewId << wxT("-"); NewId << IdNum;
									try {
										NewIterComp->id().reset();
										//NewIterComp->id().set(NewId.c_str());

										//generate newId
										bellshire::utilities::uuid_class iduuid;

										std::string idlabelstr("");
										idlabelstr.append(cast_stream< std::string>(iduuid));

										Material::id_type NewMatId(idlabelstr.c_str());
										NewIterComp->id().set(NewMatId);

										break;
									}
									catch (...) {}
								}
							}
						}
					}

					auto material_new{observer_ptr<Material>( & *NewIter)};

					bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func(
						bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data{
							m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetRootItem(), itemId
						});

					Material_GUI::TraverseMatMLTree(material_new, func);

					wxTreeItemId newselection(m_MatMLTreeCtrl->GetNextSibling(itemId));//nay give problems if the copy did not suceed.
					m_MatMLTreeCtrl->SelectItem(newselection);
					m_MatMLTreeCtrl->Expand(newselection);

					return;
				}
			}
		}
	}
	catch (const boost::bad_any_cast&) {}
}


void Material_GUI::OnBumpDown(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpDownHavingOptionalId< Material,
		MatML_Doc,
		MatML_Doc::Material_sequence,
		Material_GUI,
		&MatML_Doc::Material
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, itemId, nextitemId);

}

void Material_GUI::OnBumpUp(wxCommandEvent& event)
{

	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	wxTreeItemId previtemId = m_MatMLTreeCtrl->GetPrevSibling(itemId);

	wxTreeItemId itemParentId = (m_MatMLTreeCtrl->GetItemParent(m_MatMLTreeCtrl->GetSelection()));
	MatMLTreeItemData* itemParent = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemParentId));

	boost::any anyptr(item->GetAnyMatMLDataPointer());
	boost::any anyptrparent(itemParent->GetAnyMatMLDataPointer());

	IndividualBumpUpHavingOptionalId< Material,
		MatML_Doc,
		MatML_Doc::Material_sequence,
		Material_GUI,
		&MatML_Doc::Material
	>
		(anyptr, anyptrparent, m_MatMLTreeCtrl, itemParentId, previtemId, itemId);

}
