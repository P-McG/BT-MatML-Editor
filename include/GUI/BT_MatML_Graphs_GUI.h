/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Graphs_GUI.h
// Purpose:     Classes of Graphs_GUI Base and Derived.
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
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Graphs_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Graphs_GUI_Base();
        Graphs_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~Graphs_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Graphs* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Graphs& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};

        virtual void OnInsertGraph(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteGraph(wxCommandEvent& event) { event.Skip(); }
    private:
    };

    class Graphs_GUI : public Graphs_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Graphs_GUI();
        Graphs_GUI(wxWindow* parent);

        virtual ~Graphs_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertGraph(wxCommandEvent& event);

        void OnPasteGraph(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
