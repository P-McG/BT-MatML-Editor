/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Abbreviation_GUI.h
// Purpose:     Classes of Abbreviation_GUI Base and Derived.
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

#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"


namespace bellshire {

    class Abbreviation_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_AbbreviationTextCtrl;

        Abbreviation_GUI_Base();
        Abbreviation_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& AbbreviationTextCtrl);
        virtual ~Abbreviation_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId  SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            GlossaryTerm::Abbreviation_type& Element,
            const wxTreeItemId& PreviousId
        );
        void Update( Abbreviation* element);

        void SetConnect();
        virtual void OnAbbreviationTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Abbreviation_GUI : public  Abbreviation_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Abbreviation_GUI();
        Abbreviation_GUI(wxWindow* parent);

        virtual ~Abbreviation_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnAbbreviationTextCtrl(wxCommandEvent& event); //todo

    private:
    };

}; //namespace bellshire end
