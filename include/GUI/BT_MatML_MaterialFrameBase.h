/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_MaterialFrameBase_GUI.h
// Purpose:     Class of MaterialFrameBase.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __BT_MatML_MaterialFrameBase_GUI__
#define __BT_MatML_MaterialFrameBase_GUI__

#include <list>
#include <math.h>

// For compilers that don't support precompilation, include "wx/wx.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/radiobox.h>
#include <wx/statbmp.h>
#include <wx/listbox.h>
#include <wx/bmpbuttn.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include <wx/html/htmlwin.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include "wx/dcsvg.h"
 
#include "BT_MatML_GUI.h"
#include "PreferenceFrameBase.h"

///////////////////////////////////////////////////////////////////////////

namespace bellshire
{

	class TreeCtrlSorted;

#define wxID_MATERIAL 1000
#define wxID_MaterialMB 1001
#define wxID_MatMLTreeCtrl 1002

	/// MaterialFrameBase
	/// Sets up the Applications GUI
	/// <summary>
	/// Contains:\n
	/// - Application wxWidget GUI data Members.
	/// - MatML GUI members
	/// - Virtual event handlers, overiden in the derived classes
	/// 
	/// 
	/// </summary>
	class MaterialFrameBase : public wxFrame
	{
	private:

	protected:
		wxMenuBar* m_menubar1;/*!<Main Menu Bar*/

		wxMenu* m_FileMenu;
		wxMenuItem* m_NewMenuItem;
		wxMenuItem* m_OpenMenuItem;
		wxMenuItem* m_SaveMenuItem;
		wxMenuItem* m_SaveAsMenuItem;
		wxMenuItem* m_ExportMaterialMenuItem;
		wxMenuItem* m_ExportMaterialBranchMenuItem;
		wxMenuItem* m_ImportMaterialBranchMenuItem;
		wxMenuItem* m_ExitMenuItem;

		wxMenu* m_EditMenu;
		wxMenuItem* m_EditMenuPreferencesItem;
		wxMenuItem* m_SortClass1MenuItem;
		wxMenuItem* m_IsolateMaterialBranchMenuItem;
		wxMenuItem* m_ExitIsolateMaterialBranchMenuItem;

		wxMenu* m_ViewMenu;

		wxMenu* m_HelpMenu;
		wxMenuItem* m_AboutMenuItem;

		wxStatusBar* m_statusBar1;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel68;
		TreeCtrlSorted* m_MatMLTreeCtrl;
		wxPanel* m_MultiPanel;
		wxPanel* m_IntroPanel;
		wxStaticBitmap* m_logobitmap;
		wxStaticText* m_IntroStaticText;



		GUI* m_GUI;/*!< MatML GUIs Classes*/

		void SetMenuConnect();/*!<Connect event handlers for Menu Select*/

		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseSel(wxCloseEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Close Menu Select*/
		virtual void OnNewSel(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On New Menu Select*/
		virtual void OnOpenSel(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Open Menu Select*/
		virtual void OnSaveSel(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Save Menu Select*/
		virtual void OnSaveAsSel(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On SaveAs Menu Select*/
		virtual void OnExportMaterial(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Export Material Menu Select*/
		virtual void OnExportMaterialBranch(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Export Material Branch Menu Select*/
		virtual void OnImportMaterialBranch(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Import Material Branch Menu Select*/
		virtual void OnExitSel(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Exit Menu Select*/
		virtual void OnEditMenuPreferencesItem(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Edit Menu's Preferences Menu Select*/
		virtual void OnSortMenuItem(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Sort Menu Select*/
		virtual void OnIsolateMaterialBranch(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Isolate Material Branch Menu Select*/
		virtual void OnExitIsolateMaterialBranch(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Exit Isolate Material Branch Menu Select*/
		virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }/*!<Virtual event handlers for On About Menu Select*/

		void SetTreeCtrlConnect();/*!<Connect event handlers for wxTreeCtrl*/

		virtual void OnElementActivated(wxTreeEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Element Activated wxTreeCtrl Select*/
		virtual void OnElementCollapsed(wxTreeEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Element Colapse wxTreeCtrl Select*/
		virtual void OnElementExpanded(wxTreeEvent& event) { event.Skip(); }/*!<Virtual event handlers for On Element Expanded wxTreeCtrl Select*/
		virtual void OnMatMLItemMenu(wxTreeEvent& event) { event.Skip(); }/*!<Virtual event handlers for On MatML Item wxTreeCtrl Select*/

	public:

		MaterialFrameBase(wxWindow* parent,
			wxWindowID id = wxID_MATERIAL,
			const wxString& title = wxT("MatML Editer"),
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxSize(770, 628),
			long style = wxCAPTION | wxCLOSE_BOX | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTAB_TRAVERSAL
		);/*!<Constructor*/
		~MaterialFrameBase();/*!<Destructor*/

		void m_splitter1OnIdle(wxIdleEvent&)
		{
			m_splitter1->SetSashPosition(200);
			m_splitter1->Disconnect(wxEVT_IDLE, wxIdleEventHandler(MaterialFrameBase::m_splitter1OnIdle), NULL, this);
		}
	};

}; // namespace bellshire


#endif //__BT_MatML_MaterialFrameBase_GUI__
