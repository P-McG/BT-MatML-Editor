/////////////////////////////////////////////////////////////////////////////
// Name:        PreferenceFrameBase.h
// Purpose:     Base Class for Preferences wxWidget Frame.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once



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
#include <wx/editlbox.h>

namespace bellshire::GUI {
	///////////////////////////////////////////////////////////////////////////////
	/// Class PreferenceFrameBase
	///////////////////////////////////////////////////////////////////////////////
	class PreferenceFrameBase : public wxFrame
	{
	private:

	protected:
		wxListbook* m_listbook1;
		wxPanel* m_GeneralPanel;
		wxCheckBox* m_MatMLDataSelection;
		wxDirPickerCtrl* m_WorkingDirPicker;
		wxDirPickerCtrl* m_TemplateDirPicker;
		wxTextCtrl* m_UUIDPrefixTextCtrl;
		wxCheckBox* m_MatMLLibHideSelection;
		wxDirPickerCtrl* m_LibDirPicker;

		wxPanel* m_SortClassPanel;
		wxTextCtrl* m_ClassSortOrderTextCtrl;
		wxButton* m_ClassSortOrderAddButton;
		//wxListBox* m_ClassSortOrderListBox;
		wxEditableListBox* m_ClassSortOrderListBox;

		wxPanel* m_SavePanel;
		wxButton* m_SavePreferencesButton;
		wxButton* m_CancelPreferencesButton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnMatMLInfoSelection(wxCommandEvent& event) { event.Skip(); }
		virtual void OnWorkingDirPicker(wxFileDirPickerEvent& event) { event.Skip(); }
		virtual void OnTemplateDirPicker(wxFileDirPickerEvent& event) { event.Skip(); }
		virtual void OnUUIDPrefixTextCtrl(wxCommandEvent& event) { event.Skip(); }
		virtual void OnClassSortOrderTextCtrl(wxCommandEvent& event) { event.Skip(); }
		virtual void OnClassSortOrderAddButton(wxCommandEvent& event) { event.Skip(); }
		virtual void OnLibDirPicker(wxFileDirPickerEvent& event) { event.Skip(); }

		virtual void OnSavePreferencesButton(wxCommandEvent& event) { event.Skip(); }
		virtual void OnCancelPreferencesButton(wxCommandEvent& event) { event.Skip(); }

		void CreateGeneralPanel();
		void CreateSortClassPanel();

	public:

		PreferenceFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(680, 628), long style = wxCAPTION | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP | wxTAB_TRAVERSAL);
		~PreferenceFrameBase();
	};
}//namespace bellshire::GUI
