/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ProcessingDetails_GUI.h
// Purpose:     Classes of ProcessingDetails_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class ProcessingDetails_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_ProcessingDetailsResultTextCtrl;

        ProcessingDetails_GUI_Base();
        ProcessingDetails_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& ProcessingDetailsResultTextCtrl);
        virtual ~ProcessingDetails_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( ProcessingDetails* element);
        static wxTreeItemId SetupMatMLTreeCtrl(
            TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            ProcessingDetails& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnProcessingDetailsResultTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertParameterValue(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertResult(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParameterValue(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) {event.Skip(); }
        virtual void OnDeleteResult(wxCommandEvent& event) {event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) {event.Skip(); }
        virtual void OnPasteParameterValue(wxCommandEvent& event) {event.Skip(); }
        virtual void OnPasteResult(wxCommandEvent& event) {event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) {event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event){event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event){event.Skip(); }

    private:
    };

    class ProcessingDetails_GUI : public ProcessingDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        ProcessingDetails_GUI();
        ProcessingDetails_GUI(wxWindow* parent);

        virtual ~ProcessingDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnProcessingDetailsResultTextCtrl(wxCommandEvent& event);

        void OnInsertName(wxCommandEvent& event);
        void OnInsertParameterValue(wxCommandEvent& event);
        void OnInsertResult(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteResult(wxCommandEvent& event);
        void OnDeleteParameterValue(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteParameterValue(wxCommandEvent& event);
        void OnPasteResult(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

