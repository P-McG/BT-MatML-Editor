/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Characterization_GUI.h
// Purpose:     Classes of Characterization_GUI Base and Derived.
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
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class Characterization_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Characterization_GUI_Base();
        Characterization_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~Characterization_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            Characterization& Element,
            const wxTreeItemId& PreviousId
        );
        void Update( Characterization* element);

        void SetConnect() {};

        virtual void OnInsertFormula(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertChemicalComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertPhaseComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertDimensionalDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteFormula(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteChemicalComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeletePhaseComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteDimensionalDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteFormula(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteChemicalComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPastePhaseComposition(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteDimensionalDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Characterization_GUI : public Characterization_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Characterization_GUI();
        Characterization_GUI(wxWindow* parent);

        virtual ~Characterization_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertFormula(wxCommandEvent& event);
        void OnInsertChemicalComposition(wxCommandEvent& event);
        void OnInsertPhaseComposition(wxCommandEvent& event);
        void OnInsertDimensionalDetails(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteFormula(wxCommandEvent& event);
        void OnDeleteChemicalComposition(wxCommandEvent& event);
        void OnDeletePhaseComposition(wxCommandEvent& event);
        void OnDeleteDimensionalDetails(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteFormula(wxCommandEvent& event);
        void OnPasteChemicalComposition(wxCommandEvent& event);
        void OnPastePhaseComposition(wxCommandEvent& event);
        void OnPasteDimensionalDetails(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);
 
    private:
    };

}; //namespace bellshire end
