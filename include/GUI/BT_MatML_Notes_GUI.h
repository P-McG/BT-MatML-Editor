/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Notes_GUI.h
// Purpose:     Classes of Notes_GUI Base and Derived.
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

    class Notes_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_NotesTextCtrl;

        Notes_GUI_Base();
        Notes_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& NotesTextCtrl);
        virtual ~Notes_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( Notes* element);
        static wxTreeItemId SetupMatMLTreeCtrl(
            TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Notes& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnNotesTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Notes_GUI : public Notes_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Notes_GUI();
        Notes_GUI(wxWindow* parent);

        virtual ~Notes_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnNotesTextCtrl(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
