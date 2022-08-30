#include <wx/config.h>
#include <wx/msgdlg.h>

#include "BT_MatML_MatML_Doc_GUI.h"
#include "BT_MatML_Material_GUI.h"
#include "BT_MatML_Metadata_GUI.h"
#include "BT_MatML_Utilities_GUI.h"



using namespace bellshire;

/// Constructor
/// <summary>
/// 
/// </summary>
MatML_Doc_GUI_Base::MatML_Doc_GUI_Base() :m_GUI(nullptr)
{}

/// Main Constructor
/// <summary>
/// </summary>
/// <param name="parent"></param>
MatML_Doc_GUI_Base::MatML_Doc_GUI_Base( wxWindow* parent ) : m_GUI(nullptr)
{
	/// Create Gui
	m_GUI = Create(parent);
}

/// Destructor
/// <summary>
/// 
/// </summary>
MatML_Doc_GUI_Base::~MatML_Doc_GUI_Base() {
	/// parent will distroy Ctrl or window
}


///
/// Creates the Gui for the MatML_Doc MatML data and Info.
/// <summary>
 /// </summary>
 /// <param name="parent"></param>
 /// <returns>wxNotebook*</returns>
wxNotebook* MatML_Doc_GUI_Base::Create(wxWindow* parent)
{
	/// Creates wxNotebook
	wxNotebook* MatML_DocNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	MatML_DocNotebook->Hide();
	MatML_DocNotebook->SetMinSize(wxSize(400, 500));

	/// Creates the MatML data panel
	wxScrolledWindow* MatML_DocPanel = new wxScrolledWindow(MatML_DocNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	MatML_DocPanel->SetScrollRate(5, 5);
	MatML_DocPanel->SetMinSize(wxSize(400, 500));
	//MatML_DocPanel->SetMaxSize(wxSize(-1, 100));

	wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer2->AddGrowableCol(0);
	fgSizer2->AddGrowableRow(0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	wxStaticText* staticText4 = new wxStaticText(MatML_DocPanel, wxID_ANY, wxT("No MatML data required"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer2->Add(staticText4, 0, wxALL, 5);

	MatML_DocPanel->SetSizer(fgSizer2);
	MatML_DocPanel->Layout();
	fgSizer2->Fit(MatML_DocPanel);

	/// Creates the MatML Info panel
	MatMLInfo_GUI matMLInfo_GUI(MatML_DocNotebook,
		wxT("********** MatML_Doc *************************\n\t\t\t\nThis element declares the content model for MatML_Doc, topmost in the\nhierarchy of elements that comprise a document marked up using MatML.\nContent models describe the relationships of the element and its child\nelements. MatML_Doc must contain one or more Material elements.\n\t\t\t\nMetadata contains descriptions of the data sources, properties,\nmeasurement techniques, specimens, and parameters which are\nreferenced when materials property data are encoded using\nother elements. Metadata may occur once or not at all within the\nMaterial element. For more information, see the documentation for the\nMetadata element.\t\t\t")
	);

	/// Adds the above panels to the wxNotebook
    
	bool b,b_dflt(false);//temps
	wxConfig(wxT("BTMatML")).Read(wxT("/General/MatMLDataSelection"), &b_dflt);;

	MatML_DocNotebook->AddPage(MatML_DocPanel, wxT("MatML Data."), b_dflt);
	MatML_DocNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), !b_dflt);



	return MatML_DocNotebook;
}


void MatML_Doc_GUI_Base::Update()
{
	/// Nothing to update

	/// Show Gui
	Show(true); 
}


/// <summary>
/// This set-up the Parent MatML data into a wxTreeCtrl element and then call on the Children to do the same.
/// This mimics the MatML data tree into wxWidget wxTreeCtrl.
/// </summary>
void MatML_Doc_GUI_Base::SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, MatML_Doc& Element)
{
	/// As this is the root element in the wxTreeCtrl, clear out all wxTreeCtrl data and start fresh.
	if(!MatMLTreeCtrl->IsEmpty())
		MatMLTreeCtrl->DeleteAllItems();

    /// Create the current element and add the MatMLTreeItemData
	wxString str;
	str << wxT("MatML-Doc");
	wxTreeItemId CurrentId = MatMLTreeCtrl->AddRoot(str, -1, -1, new MatMLTreeItemData(&Element));

	/// Setup element Material
	{
		MatML_Doc::Material_sequence& cont(Element.Material());
		MatML_Doc::Material_iterator iter(cont.begin());
		if (!cont.empty())
			for (; iter != cont.end(); ++iter)
				Material_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *iter, MatMLTreeCtrl->GetLastChild(CurrentId));
	}

	/// Setup element Metadata
	{
		MatML_Doc::Metadata_optional& cont(Element.Metadata());
		if (cont.present())
			Metadata_GUI::SetupMatMLTreeCtrl(MatMLTreeCtrl, CurrentId, *cont, MatMLTreeCtrl->GetLastChild(CurrentId));
	}

	/// Sort Children in order. Order is set by TreeCtrlSorted.	
	MatMLTreeCtrl->SortChildren(MatMLTreeCtrl->GetRootItem());

}


/// <summary>
/// Constructor for the derived class
/// </summary>
MatML_Doc_GUI::MatML_Doc_GUI() 
	: MatML_Doc_GUI_Base(),
	m_MatMLTreeCtrl(nullptr),
	m_MatMLDoc(nullptr)
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
MatML_Doc_GUI::MatML_Doc_GUI(wxWindow* parent)
	: MatML_Doc_GUI_Base(parent),
	m_MatMLTreeCtrl(nullptr),
	m_MatMLDoc(nullptr)
{
	SetConnect(); /// Set connection to the Event Handler Functions
}

/// <summary>
/// Destructor for the derived class
/// </summary>
MatML_Doc_GUI::~MatML_Doc_GUI() {
	/// parent window will destroy Ctrl or window
}

/// Set Event Handler Variables
/// <summary>
/// Function used to set up this objects member variables which is used in the EventHandler's functions.
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void MatML_Doc_GUI::SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	SetMatMLTreeCtrl(MatMLTreeCtrl);
	SetMatMLDoc(MatMLDoc);
}

/// <summary>
/// Set the Event Handler associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void MatML_Doc_GUI::SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Set the Event Handler Variable associated with the MatML wxTreeCtrl 
/// Required before using the derived class's event handler functions.
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
void MatML_Doc_GUI::SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc)
{
	m_MatMLDoc = MatMLDoc;
}

/// MatML data MatML_Doc delete child Material
/// <summary>
/// Overrides base class
/// </summary>
/// <param name="event"></param>
void MatML_Doc_GUI::OnDeleteMaterial(wxCommandEvent& event) {
	wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));

	bool update(false);

	try {
		Material* material = boost::any_cast<Material* >(item->GetAnyMatMLDataPointer());
		if (material != 0) {
			if (material->id().present()) {

				//Find all references to the material in the components and
				//erase the class with associated idref to the material.

				MatML_Doc::Material_sequence& matcont(m_MatMLDoc->Material());
				MatML_Doc::Material_iterator matiter(matcont.begin());
				for (; matiter != matcont.end(); ++matiter) {
					if (!matiter->ComponentDetails().empty()) {
						Material::ComponentDetails_sequence& compcont(matiter->ComponentDetails());
						Material::ComponentDetails_iterator compiter(compcont.begin());
						for (; compiter != compcont.end(); ++compiter) {
							if (!compiter->Class().empty()) {
								ComponentDetails::Class_sequence& classcont(compiter->Class());
								ComponentDetails::Class_iterator classiter(classcont.begin());
								do {
									bool erase(false);
									if (!classiter->ParentMaterial().empty()) {
										Material* parentmaterial(dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));
										if (material == parentmaterial) erase = true;
									}
									if (erase) {
										classiter = classcont.erase(classiter, classiter + 1);
										update = true;
									}
									else ++classiter;
								} while (classiter != classcont.end());
							}
						}
					}
				}
			}

			//Delete material in MatML_doc and the TreeCtrl
			MatML_Doc::Material_sequence& cont(m_MatMLDoc->Material());
			MatML_Doc::Material_iterator iter(cont.begin());
			//for(;iter!=cont.end();++iter){
			do {
				if (&*iter == material) {
					iter = cont.erase(iter);

					if (update == true) {
						//wipe out the whole ctrltree and set it up again
						MatML_Doc_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, *m_MatMLDoc);
						//
						if (iter != cont.end()) {
							wxTreeItemId newtreeitem(::bellshire::Utilities::MatMLtoTreeCtrl(m_MatMLTreeCtrl, &*iter));
							m_MatMLTreeCtrl->SelectItem(newtreeitem);
							m_MatMLTreeCtrl->EnsureVisible(newtreeitem);
						}
					}
					else {
						m_MatMLTreeCtrl->Delete(itemId);
					}
					return;
				}
				else ++iter;
			} while (iter != cont.end());
		}
	}
	catch (const boost::bad_any_cast&) {}
}
