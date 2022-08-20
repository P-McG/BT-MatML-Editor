/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_TestConditionDetails_GUI.h
// Purpose:     Classes of TestConditionDetails_GUI Base and Derived.
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
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ID_GUI;

    class TestConditionDetails_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        ID_GUI* m_TestConditionDetails_ID_GUI;
        wxTextCtrl* m_TestConditionDetailsTypeTextCtrl;

        TestConditionDetails_GUI_Base();
        TestConditionDetails_GUI_Base(wxWindow* parent);

        virtual ~TestConditionDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent,
            ID_GUI*& TestConditionDetails_ID_GUI
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( TestConditionDetails* element);

        static ::std::string Label(::std::string name, ::std::string id);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId,
            TestConditionDetails& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnInsertParameterValue(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParameterValue(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteParameterValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

    private:
    };

    class TestConditionDetails_GUI : public TestConditionDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        TestConditionDetails_GUI();
        TestConditionDetails_GUI(wxWindow* parent);

        virtual ~TestConditionDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertParameterValue(wxCommandEvent& event);

        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteParameterValue(wxCommandEvent& event);

        void OnPasteParameterValue(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

