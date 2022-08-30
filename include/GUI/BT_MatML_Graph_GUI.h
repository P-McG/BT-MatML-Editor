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

    class GraphDisplay : public wxScrolledWindow
    {
    public:
        GraphDisplay(wxNotebook* parent, wxTextCtrl* graphtextctrl);
        virtual void OnDraw(wxDC& dc) wxOVERRIDE;
    private:
        wxTextCtrl* m_GraphTextCtrl = nullptr;
    };

    class Graph_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxTextCtrl* m_graphtextctrl;
        GraphDisplay* m_graphdisplay;
        wxNotebook* m_GUI;

        Graph_GUI_Base();
        Graph_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& graphtextctrl, GraphDisplay*& graphdisplay);
        virtual ~Graph_GUI_Base();

        void Show(bool show=true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( Graph* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            Graph& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Graph_GUI : public Graph_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Graph_GUI();
        Graph_GUI(wxWindow* parent);
        virtual ~Graph_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
