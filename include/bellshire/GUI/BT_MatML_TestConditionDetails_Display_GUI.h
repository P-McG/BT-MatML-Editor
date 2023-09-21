/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_TestConditionDetails_Display_GUI.h
// Purpose:     Classes of TestConditionDetails_Display_GUI Base and Derived.
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
#include <wx/grid.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include <list>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"


namespace bellshire::GUI {
    class TestConditionDetails_Display_GUI
    {
        wxPanel* m_GUI;
        wxTextCtrl* m_TestConditionDetailsNotesTextCtrl;

    public:
        TestConditionDetails_Display_GUI();
        TestConditionDetails_Display_GUI(wxNotebook* parent);

        virtual ~TestConditionDetails_Display_GUI();

        wxPanel* GetGUI();
        wxTextCtrl* GetTestConditionDetailsNotesTextCtrl();
        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& TestConditionDetailsNotesTextCtrl
        );

        void Update(const observer_ptr< PropertyData> element);
    };

}; //namespace bellshire end

