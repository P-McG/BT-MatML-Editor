/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_CurrencyCode_GUI.h
// Purpose:     Classes of CurrencyCode_GUI Base and Derived.
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

    class CurrencyCode_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxChoice* m_CurrencyCodeChoice;
        wxNotebook* m_GUI;

        CurrencyCode_GUI_Base();
        CurrencyCode_GUI_Base(wxWindow* parent);
        virtual ~CurrencyCode_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        static wxNotebook* Create(wxWindow* parent, wxChoice*& CurrencyCodeChoice);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            CurrencyCode& Element, 
            const wxTreeItemId& PreviousId
        );

        void Update( CurrencyCode* element);

        void SetConnect();
        virtual void OnCurrencyCodeChoice(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class CurrencyCode_GUI : public CurrencyCode_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        CurrencyCode_GUI();
        CurrencyCode_GUI(wxWindow* parent);

        virtual ~CurrencyCode_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnCurrencyCodeChoice(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
#pragma once
