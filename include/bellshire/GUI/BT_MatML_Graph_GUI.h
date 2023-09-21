/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Graph_GUI.h
// Purpose:     Classes of Graph_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Graph.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {
    class MatML_GUI_Base;

    class GraphDisplay : public wxScrolledWindow
    { 
        wxTextCtrl* m_GraphTextCtrl = nullptr;

    public:
        GraphDisplay(wxNotebook* parent, wxTextCtrl* graphtextctrl);

        wxTextCtrl* GetGraphTextCtrl();
        virtual void OnDraw(wxDC& dc) wxOVERRIDE;
    };

    class Graph_GUI_Base : public MatML_GUI_Base, public Graph_Base
    {
    protected:
        wxTextCtrl* m_graphtextctrl;
        GraphDisplay* m_graphdisplay;

    public:
        Graph_GUI_Base();
        Graph_GUI_Base(wxWindow* parent);
        virtual ~Graph_GUI_Base();

        wxTextCtrl* GetGraphTextCtrl();
        GraphDisplay* GetGraphDisplay();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& graphtextctrl, 
            GraphDisplay*& graphdisplay
        );
        static wxWindow* CreateGraphPanel(wxWindow* parent,
            wxTextCtrl*& graphtextctrl
        );

        //wxNotebook* get() { return m_GUI; };

        void Update( const observer_ptr<Graph> element);

        static wxString GetTreeLabel(const observer_ptr<Graph> element);

        void SetConnect() {};

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class Graph_GUI : public Graph_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Graph_GUI();
        Graph_GUI(wxWindow* parent);
        virtual ~Graph_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end
