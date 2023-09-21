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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "bellshire/utilities/StringStream.h"

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_Graphs.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Graphs_GUI_Base : public MatML_GUI_Base, public Graphs_Base
    {
    protected:

    public:
        Graphs_GUI_Base();
        Graphs_GUI_Base(wxWindow* parent);
        virtual ~Graphs_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateGraphsPanel(wxWindow* parent);

        void Update( const observer_ptr<Graphs> element);

        static wxString GetTreeLabel(const observer_ptr<Graphs> element);

        void SetConnect() {};

        virtual void OnInsertGraph(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteGraph(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteGraph(wxCommandEvent& event) { event.Skip(); }
    };

    class Graphs_GUI : public Graphs_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Graphs_GUI();
        Graphs_GUI(wxWindow* parent);

        virtual ~Graphs_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertGraph(wxCommandEvent& event);
        void OnDeleteGraph(wxCommandEvent& event);
        void OnPasteGraph(wxCommandEvent& event);
    };

}; //namespace bellshire end
