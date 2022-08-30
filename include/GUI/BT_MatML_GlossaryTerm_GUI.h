/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_GlossaryTerm_GUI.h
// Purpose:     Classes of GlossaryTerm_GUI Base and Derived.
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

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "StringStream.h"

#include "matml31.hxx"
#include "matml31_strongtypedef.h"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class GlossaryTerm_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        GlossaryTerm_GUI_Base();
        GlossaryTerm_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~GlossaryTerm_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( GlossaryTerm* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            GlossaryTerm& Element,
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};

        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertDefinition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertAbbreviation(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSynonym(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteDefinition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteAbbreviation(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSynonym(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteDefinition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteAbbreviation(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteSynonym(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }


    private:
    };


    class GlossaryTerm_GUI : public GlossaryTerm_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        GlossaryTerm_GUI();
        GlossaryTerm_GUI(wxWindow* parent);

        virtual ~GlossaryTerm_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertDefinition(wxCommandEvent& event);
        void OnInsertAbbreviation(wxCommandEvent& event);
        void OnInsertSynonym(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteDefinition(wxCommandEvent& event);
        void OnDeleteAbbreviation(wxCommandEvent& event);
        void OnDeleteSynonym(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteDefinition(wxCommandEvent& event);
        void OnPasteAbbreviation(wxCommandEvent& event);
        void OnPasteSynonym(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
