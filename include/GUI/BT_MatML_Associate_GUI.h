/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Associate_GUI.h
// Purpose:     Classes of Associate_GUI Base and Derived.
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
#include "BT_MatML_ID_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Associate_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxTextCtrl* m_AssociateTextCtrl;
        wxNotebook* m_GUI;

        Associate_GUI_Base();
        Associate_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& AssociateTextCtrl);
        virtual ~Associate_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static void SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Associate& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( Associate* element);

        void SetConnect();
        virtual void OnAssociateTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Associate_GUI : public Associate_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Associate_GUI();
        Associate_GUI(wxWindow* parent);

        virtual ~Associate_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnAssociateTextCtrl(wxCommandEvent& event);

    private:
    };
}; //namespace bellshire end
