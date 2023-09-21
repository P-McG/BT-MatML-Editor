/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_PhaseComposition_GUI.h
// Purpose:     Classes of PhaseComposition_GUI Base and Derived.
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
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_PhaseComposition.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class PhaseComposition_GUI_Base : public MatML_GUI_Base, public PhaseComposition_Base
    {
    protected:

    public:
        PhaseComposition_GUI_Base();
        PhaseComposition_GUI_Base(wxWindow* parent);
        virtual ~PhaseComposition_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreatePhaseCompositionPanel(wxWindow* parent);

        void Update( const observer_ptr<PhaseComposition> element);

        static wxString GetTreeLabel(const observer_ptr<PhaseComposition> element);

        void SetConnect() {};

        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertPropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeletePropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPastePropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class PhaseComposition_GUI : public PhaseComposition_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        PhaseComposition_GUI();
        PhaseComposition_GUI(wxWindow* parent);

        virtual ~PhaseComposition_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertConcentration(wxCommandEvent& event);
        void OnInsertPropertyData(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteConcentration(wxCommandEvent& event);
        void OnDeletePropertyData(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteConcentration(wxCommandEvent& event);
        void OnPastePropertyData(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };
}; //namespace bellshire end

