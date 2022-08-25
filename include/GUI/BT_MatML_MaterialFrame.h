/** \file MaterialFrame.h
 * Main GUI header for MaterialFrame class.
 * Derivative of MaterialFrameBase setting up the wxWidget environment
 * 
 * @author Paul McGrath
 */
#ifndef __MaterialFrame__
#define __MaterialFrame__


// For storing configuration data
#include <wx/config.h> //(to let wxWidgets choose a wxConfig class for your platform)
#include <wx/confbase.h> //(base config class)
#include <wx/fileconf.h> //(wxFileConfig class)
#ifdef WIN32
#include <wx/msw/regconf.h> //(wxRegConfig class)
#endif

#include <wx/stdpaths.h> //returns the standard locations in the file system

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include "PreferenceFrame.h" //user preference interface.

#include <wx/event.h>
#include <wx/settings.h>

#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_MaterialFrameBase.h"
#include "BT_MatML_Utilities_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"


#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <stack>
#include "HTMLFrame.h"

#include <boost/serialization/strong_typedef.hpp>


namespace bellshire{

typedef ::std::list<boost::any> many;

/// MaterialFrame
/// <summary>
/// Application's GUIs (not directly associated with the MatML data classes) e.g. File Menu, Edit Menu, View Menu, etc.
/// </summary>
/// - MatML_Doc pointer holding the MatML Data.
/// - Placeholder member location for items to be copied.
/// - Event handlers, overiding the base classes functions, which are not directly related to MatML Data classes.
/// - OnDelete context menu event handler functions
/// - Current Document Path
class MaterialFrame : public MaterialFrameBase, public Utilities
{
public:

	boost::any m_MatMLItemToCopy;//placeholder location for items to be copied.

	// Event Handlers functions for MaterialFrameBase events.
	void OnElementActivated(wxTreeEvent& event);/*!< Provides Calls for the updating the associated MatML GUI. */
	void OnElementExpanded(wxTreeEvent& event);/*!< On element expansion sets the layout */
	void OnElementCollapsed(wxTreeEvent& event);/*!< On element collapsed sets the layout */
	void OnLeftDown(wxTreeEvent& event);/*!< On element collapsed sets the layout */

	void OnMatMLItemMenu(wxTreeEvent& event);/*!< On MatML item menu selection shows the GUI*/

protected:
	wxString m_CurrentDocPath;/*!< The Path to the file we have open */

	boost::shared_ptr<MatML_Doc> doc;/*!< Main MatML Document Pointer */

	std::stack<TreeCtrlSorted*> m_MatMLTreeCtrlStack;/*!< Stack of wxTreeCtrl Pointers. Allows for different Tree versions. */
	bool reEstabilishTreeCtrlSizer();

	//Templates
	std::auto_ptr<MatML_Doc> template_doc;/*!<used in the class tempates */

	//wxTreeItemId m_draggedItem;

	PreferenceFrame* preferenceframe;
	HTMLFrame* htmlframe;

	//Wrappers for MatML Data
	//std::list<boost::any> MatMLDataWrapper;

	void LoadFile();
	void ImportFile(const char* File);
	void backup();


	// Handlers for MaterialFrameBase events.
	void OnCloseSel( wxCloseEvent& event );
	void OnNewSel( wxCommandEvent& event );
	void OnOpenSel( wxCommandEvent& event );
	void OnSaveSel( wxCommandEvent& event );
	void OnSaveAsSel( wxCommandEvent& event );
	void OnExportMaterial( wxCommandEvent& event );
	void OnExportMaterial( wxString& filename );
	void OnExportMaterialBranch( wxCommandEvent& event );
	void OnExportMaterialBranch( wxString& filename);
	void OnImportMaterialBranch( wxCommandEvent& event );
	void OnIsolateMaterialBranch( wxCommandEvent& event );//New events have tobe implemented in SetupMaterialBranch
    void IsolateMaterialBranch();
	void OnExitIsolateMaterialBranch( wxCommandEvent& event );
    void ExitIsolateMaterialBranch();
	void OnExitSel( wxCommandEvent& event );
	void OnEditMenuPreferencesItem( wxCommandEvent& event );
	void OnSortMenuItem( wxCommandEvent& event );
	void SortMenuItem();
	void XSLT2HTMLviewer(const wxString XMLfilename, const wxString XSLTFile, const wxString HTMLDir,const wxString HTMLFileName);
	void XSLTProcessing(const wxString XMLfilename, const wxString XSLTFile, const wxString OutDir, const wxString OutFileName, const wxString XSLTParameters);
	void OnAbout(wxCommandEvent& event);

	void SetTreeCtrlConnect();

	//wxTreeCtrl context menu
	template<typename EventTag, typename Class, typename EventArg, typename EventHandler >
	void PopupLinkBind(wxMenu& menu, ::std::string desc, const EventTag& eventType, void(Class::* method)(EventArg&), EventHandler* handler);

	template<typename MatMLClass, typename Parent_GUIClass, typename EventTag, typename ParentBase_GUIClass, typename EventArg, typename EventHandler >
	void Popup_Paste(const boost::any& MatMLItemToCopy, Parent_GUIClass* Parent_GUI, wxMenu& menu, ::std::string desc, const EventTag& eventType, void(ParentBase_GUIClass::* method)(EventArg&), EventHandler* handler);

	void ShowContextMenu(wxTreeItemId id, const wxPoint& pt);

	::vector<ParentMaterial*> MaterialGatherAssociatedComponentParentMaterial(Material* material);
	void MaterialSetParentMaterial(::vector<ParentMaterial*> compparentmateriallist, Material* material);

	void OnCopy(wxCommandEvent& event);

	//void OnPasteMaterial(wxCommandEvent& event);

	///following functions are for the Deletion of the wxTreeCtrl elements
	void OnDeleteAssociate(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteAssociationDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteAuthorityDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteBulkDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteCharacterization(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteChemicalComposition(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteChemicalElementSymbol(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteClass(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSubclass(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSubclass1(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteComponentDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteCompound(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteConcentration(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteCurrencyCode(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteDataSourceDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteDimensionalDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteElement(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteForm(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteFormula(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteGeometry(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteGlossary(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteGlossaryTerm(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteDefinition(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteAbbreviation(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSynonym(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteGraphs(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteMaterial(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteMeasurementTechniqueDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteMetadata(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteName(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteNotes(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteParameterDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteParentMaterial(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteParentSubClass(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteParameterValue(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeletePhaseComposition(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteProcessingDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteResult(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeletePropertyData(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeletePropertyDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteQualifier(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteRelationship(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSource(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSourceDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSpecification(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteSpecimenDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteTestConditionDetails(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteUncertainty(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteScale(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteUnit(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteUnitless(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteUnits(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
	void OnDeleteValue(wxCommandEvent& event);/*! Call parent's to delete the MatML data */

	void OnGotoParentMaterial(wxCommandEvent& event);
	
	void SetupMaterialBranch(MatML_Doc &element,std::vector<Material*> &materials);	/*!< The following functions setup wxTreeCtrl branchesand assigns a MatML element pointer to the wxTreeCtrl elements */

	void UpdateCurrentPanel();

	template< class MatML>
	MatML* GetMatML(bellshire::TreeCtrlSorted* TreeCtrl, wxTreeItemId* ItemId)
	{
		MatMLTreeItemData* treeitemdata = (MatMLTreeItemData*)(TreeCtrl->GetItemData(*ItemId));

		MatML* matml(nullptr);
		if (treeitemdata) 
			matml=GetMatML<MatML>(treeitemdata);

		return matml;
	}

	template< class MatML>
	MatML* GetMatML(MatMLTreeItemData* treeitemdata)
	{
		const boost::any anyptr(treeitemdata->GetAnyMatMLDataPointer());
		MatML* matml = nullptr;
		try {
			if (anyptr.type() == typeid(MatML*)) {
				matml = boost::any_cast<MatML*>(anyptr);
			}
		}
		catch (const boost::bad_any_cast&) {}

		return matml;
	}

public:
	
	MaterialFrame(wxWindow* parent,
		wxWindowID id = wxID_MATERIAL,
		const wxString& title = wxT("MatML Editer"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(770, 628),
		long style = wxCAPTION | wxCLOSE_BOX | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTAB_TRAVERSAL
	);/*!< Constructor */
	virtual ~MaterialFrame();/*!< Destructor */

	wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxString& text, bool bCaseSensitive, bool bExactMatch);
	wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const MatMLTreeItemData& MatML_Data);

	void OnClassInsertRelatedElementsButton( wxCommandEvent& event );
	void SetupTemplateDoc(Material& Element);

	//MatML Template Utility
	void LoadTemplateDoc(wxString& TemplateName);
	void CopyTemplateMetadata();
	void CopyTemplateParameterValue(ProcessingDetails& Element);
	void CopyTemplateProperty(ComponentDetails& Element, ComponentDetails& TemplateElement);
	void CopyTemplateProcessingDetails(ComponentDetails& Element, ComponentDetails& TemplateElement);

	void CopyComponentNameToParentMaterial();
	void ReplaceIDwithUuid();

};


}//namespace bellshire
#endif // __MaterialFrame__
