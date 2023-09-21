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
#include "bellshire/BT_MatML_Formula.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Formula_GUI_Base : public MatML_GUI_Base, public Formula_Base
    {
    protected:
        wxTextCtrl* m_FormulaTextCtrl;

    public:
        Formula_GUI_Base();
        Formula_GUI_Base(wxWindow* parent);
        virtual ~Formula_GUI_Base();

        wxTextCtrl* GetFormulaTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& FormulaTextCtrl);
        static wxWindow* CreateFormulaPanel(wxWindow* parent, wxTextCtrl*& FormulaTextCtrl);

        static wxString GetTreeLabel(const observer_ptr<Formula> element);

        void Update( const observer_ptr<Formula> element);

        void SetConnect();
        virtual void OnFormulaTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

    class Formula_GUI: public Formula_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Formula_GUI();
        Formula_GUI(wxWindow* parent);

        virtual ~Formula_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnFormulaTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
#pragma once
