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

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Notes.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Notes_GUI_Base : public MatML_GUI_Base, public Notes_Base
    {
    protected:

    public:
        wxTextCtrl* m_NotesTextCtrl;

        Notes_GUI_Base();
        Notes_GUI_Base(wxWindow* parent);
        virtual ~Notes_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& NotesTextCtrl);
        static wxWindow* CreateNotesPanel(wxWindow* parent,
            wxTextCtrl*& NotesTextCtrl
        );

        void Update( const observer_ptr<Notes> element);

        static wxString GetTreeLabel(const observer_ptr<Notes> element);

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
