/////////////////////////////////////////////////////////////////////////////
// Name:       BT_MatML_Formula_GUI.h
// Purpose:     Classes of Formula_GUI Base and Derived.
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

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Formula_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_FormulaTextCtrl;

        Formula_GUI_Base();
        Formula_GUI_Base(wxWindow* parent);
        virtual ~Formula_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& FormulaTextCtrl);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Formula& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( Formula* element);

        void SetConnect();
        virtual void OnFormulaTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Formula_GUI: public Formula_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Formula_GUI();
        Formula_GUI(wxWindow* parent);

        virtual ~Formula_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnFormulaTextCtrl(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
#pragma once
