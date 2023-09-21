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

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Characterization.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class Characterization_GUI_Base : public MatML_GUI_Base, public Characterization_Base
    {
    protected:

    public:

        Characterization_GUI_Base();
        Characterization_GUI_Base(wxWindow* parent);
        virtual ~Characterization_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateCharacterizationPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<Characterization> element);

        void Update( const observer_ptr<Characterization> element);

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

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.
    public:
        Characterization_GUI();
        Characterization_GUI(wxWindow* parent);

        virtual ~Characterization_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

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
    };

}; //namespace bellshire end
