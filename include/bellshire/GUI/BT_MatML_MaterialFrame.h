/** \file MaterialFrame.h
 * Main GUI header for MaterialFrame class.
 * Derivative of MaterialFrameBase setting up the wxWidget environment
 * 
 * @author Paul McGrath
 */
#ifndef __MaterialFrame__
#define __MaterialFrame__

 // For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// For storing configuration data
#include <wx/config.h> //(to let wxWidgets choose a wxConfig class for your platform)
#include <wx/confbase.h> //(base config class)
#include <wx/fileconf.h> //(wxFileConfig class)
#ifdef WIN32
#include <wx/msw/regconf.h> //(wxRegConfig class)
#endif

#include <wx/stdpaths.h> //returns the standard locations in the file system
#include <wx/event.h>
#include <wx/settings.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

//#include "bellshire/BT_MatML_GUI_Base.H"
#include "PreferenceFrame.h" //user preference interface.

#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MaterialFrameBase.h"
#include "bellshire/GUI/utilities/BT_MatML_Utilities_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"


#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <stack>
#include "HTMLFrame.h"

#include <boost/serialization/strong_typedef.hpp>


namespace bellshire::GUI{

typedef ::std::list<boost::any> many;

/// MaterialFrame
/// <summary>
/// Application's GUIs (not directly associated with the MatML data classes) e.g. File Menu, Edit Menu, View Menu, etc.
/// </summary>
/// - MatML_Doc pointer holding the MatML Data.
/// - Placeholder member location for items to be copied.
/// - Event handlers, overriding the base classes functions, which are not directly related to MatML Data classes.
/// - OnDelete context menu event handler functions
/// - Current Document Path
class MaterialFrame : public MaterialFrameBase, public Utilities
{
	boost::any m_MatMLItemToCopy;//placeholder location for items to be copied.
	std::shared_ptr<::MatML_Doc> doc;/*!< Main MatML Document pointer*/
	std::stack<TreeCtrlSorted*> m_MatMLTreeCtrlStack;/*!< Stack of wxTreeCtrl Pointers. Allows for different Tree versions. */
	std::unique_ptr<MatML_Doc> template_doc;/*!<used in the class templates *///Templates
	//wxTreeItemId m_draggedItem;
protected:
	PreferenceFrame* preferenceframe;
	HTMLFrame* htmlframe;

public:
	boost::any GetMatMLItemToCopy();//placeholder location for items to be copied.
	std::shared_ptr<MatML_Doc> GetDoc();/*!< Main MatML Document Pointer */
	std::stack<TreeCtrlSorted*> GetMatMLTreeCtrlStack();/*!< Stack of wxTreeCtrl Pointers. Allows for different Tree versions. */
	std::unique_ptr<MatML_Doc> GetTemplateDoc();/*!<used in the class templates *///Templates
	//wxTreeItemId m_draggedItem;
	PreferenceFrame* GetPreferenceFrame();
	HTMLFrame* GetHtmlFrame();

	bool Warning(::std::string msg)
	{
		wxMessageDialog WarningDialog(NULL, msg, _("MatML Editor"), wxOK | wxICON_EXCLAMATION, wxDefaultPosition);
		return (WarningDialog.ShowModal() == wxID_YES);
	}

	// Event Handlers functions for MaterialFrameBase events.
	void OnElementActivated(wxTreeEvent& event);/*!< Provides Calls for the updating the associated MatML GUI. */
	void OnElementExpanded(wxTreeEvent& event);/*!< On element expansion sets the layout */
	void OnElementCollapsed(wxTreeEvent& event);/*!< On element collapsed sets the layout */
	void OnLeftDown(wxTreeEvent& event);/*!< On element collapsed sets the layout */
	void OnRightDown(wxTreeEvent& event);

	void OnMatMLItemMenu(wxTreeEvent& event);/*!< On MatML item menu selection shows the GUI*/

protected:
	void LoadFile();
	void ImportFile(const char* File);
	void backup();
	bool reEstabilishTreeCtrlSizer();

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
	void OnDeleteGraph(wxCommandEvent& event);/*! Call parent's to delete the MatML data */
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
	observer_ptr<MatML> GetMatML(::bellshire::GUI::TreeCtrlSorted* TreeCtrl, wxTreeItemId* ItemId)
	{
		MatMLTreeItemData* treeitemdata = (MatMLTreeItemData*)(TreeCtrl->GetItemData(*ItemId));

		if (treeitemdata) 
			return GetMatML<MatML>(treeitemdata);
		
		return observer_ptr<MatML>();
	}

	template< class MatML>
	observer_ptr<MatML> GetMatML(MatMLTreeItemData* treeitemdata)
	{
		const boost::any anyptr(treeitemdata->GetAnyMatMLDataPointer());
		
		try {
			if (anyptr.type() == typeid(observer_ptr<MatML>)) {
				return boost::any_cast<observer_ptr<MatML>>(anyptr);
			}
		}
		catch (const boost::bad_any_cast&) {}

		return observer_ptr<MatML>();
	}

public:
	
	MaterialFrame(wxWindow* parent,
		wxWindowID id = wxID_MATERIAL,
		const wxString& title = wxT("MatML Editor"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(770, 628),
		long style = wxCAPTION | wxCLOSE_BOX | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTAB_TRAVERSAL
	);/*!< Constructor */
	virtual ~MaterialFrame();/*!< Destructor */

	wxTreeItemId findTreeItem(TreeCtrlSorted* pTreeCtrl, const wxTreeItemId& root, const wxString& text, bool bCaseSensitive, bool bExactMatch);
	wxTreeItemId findTreeItem(TreeCtrlSorted* pTreeCtrl, const wxTreeItemId& root, const MatMLTreeItemData& MatML_Data);

	void OnClassInsertRelatedElementsButton( wxCommandEvent& event );
	void SetupTemplateDoc(observer_ptr<Material> element);

	//MatML Template Utility
	void LoadTemplateDoc(wxString& TemplateName);
	void CopyTemplateMetadata();
	void CopyTemplateParameterValue(ProcessingDetails& Element);
	void CopyTemplateProperty(ComponentDetails& Element, ComponentDetails& TemplateElement);
	void CopyTemplateProcessingDetails(ComponentDetails& Element, ComponentDetails& TemplateElement);

	void CopyComponentNameToParentMaterial();


};


}//namespace bellshire
#endif // __MaterialFrame__
