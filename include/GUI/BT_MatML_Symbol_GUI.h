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

    class Symbol_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_SymbolSubScriptTextCtrl;
        wxChoice* m_SymbolChoice;

        Symbol_GUI_Base();
        Symbol_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& SymbolSubScriptTextCtrl, wxChoice*& SymbolChoice);
        virtual ~Symbol_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Symbol& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( Symbol* element);

        void SetConnect();
        virtual void OnSymbolSubScriptTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnSymbolChoice(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Symbol_GUI : public Symbol_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Symbol_GUI();
        Symbol_GUI(wxWindow* parent);

        virtual ~Symbol_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void OnSymbolSubScriptTextCtrl(wxCommandEvent& event);
        void OnSymbolChoice(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
