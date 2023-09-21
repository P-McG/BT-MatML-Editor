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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_TestConditionDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class ID_GUI;

    class TestConditionDetails_GUI_Base : public MatML_GUI_Base, public TestConditionDetails_Base
    {
    protected:
        ID_GUI* m_TestConditionDetails_ID_GUI;
        wxTextCtrl* m_TestConditionDetailsTypeTextCtrl;

    public:
        TestConditionDetails_GUI_Base();
        TestConditionDetails_GUI_Base(wxWindow* parent);
        virtual ~TestConditionDetails_GUI_Base();

        ID_GUI* GetTestConditionDetails_ID_GUI();
        wxTextCtrl* GetTestConditionDetailsTypeTextCtrl();

        static wxNotebook* Create(wxWindow* parent,
            ID_GUI*& TestConditionDetails_ID_GUI
        );
        static wxWindow* CreateTextConditionDetailsPanel(wxWindow* parent,
            ID_GUI*& TestConditionDetails_ID_GUI
        );

        void Update( const observer_ptr<TestConditionDetails> element);

        static ::std::string Label(::std::string name, ::std::string id);
        static wxString GetTreeLabel(const observer_ptr<TestConditionDetails> element);

        void SetConnect();
        virtual void OnInsertParameterValue(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParameterValue(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteParameterValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class TestConditionDetails_GUI : public TestConditionDetails_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        TestConditionDetails_GUI();
        TestConditionDetails_GUI(wxWindow* parent);

        virtual ~TestConditionDetails_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertParameterValue(wxCommandEvent& event);

        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteParameterValue(wxCommandEvent& event);

        void OnPasteParameterValue(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end

