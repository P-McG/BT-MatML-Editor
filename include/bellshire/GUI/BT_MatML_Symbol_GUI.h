/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Symbol_GUI.h
// Purpose:     Classes of Symbol_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Symbol.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Symbol_GUI_Base : public MatML_GUI_Base, public Symbol_Base
    {
    protected:
        wxTextCtrl* m_SymbolSubScriptTextCtrl;
        wxChoice* m_SymbolChoice;

    public:
        Symbol_GUI_Base();
        Symbol_GUI_Base(wxWindow* parent);
        virtual ~Symbol_GUI_Base();

        wxTextCtrl* GetSymbolSubScriptTextCtrl();
        wxChoice* GetSymbolChoice();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& SymbolSubScriptTextCtrl,
            wxChoice*& SymbolChoice
        );
        static wxWindow* CreateSymbolPanel(wxWindow* parent,
            wxTextCtrl*& SymbolSubScriptTextCtrl,
            wxChoice*& SymbolChoice
        );

        static wxString GetTreeLabel(const observer_ptr<Symbol> element);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Symbol& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( const observer_ptr<Symbol> element);

        void SetConnect();
        virtual void OnSymbolSubScriptTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnSymbolChoice(wxCommandEvent& event) { event.Skip(); }
    };

    class Symbol_GUI : public Symbol_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Symbol_GUI();
        Symbol_GUI(wxWindow* parent);

        virtual ~Symbol_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void OnSymbolSubScriptTextCtrl(wxCommandEvent& event);
        void OnSymbolChoice(wxCommandEvent& event);

    };

}; //namespace bellshire end
