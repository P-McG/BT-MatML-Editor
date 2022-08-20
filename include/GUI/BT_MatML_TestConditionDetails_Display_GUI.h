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


// For compilers that support precompilation, includes "wx/wx.h".
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
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"


namespace bellshire {

    //Utility for std:string and wxString
#define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
#define _wx2std(var) std::string(var.mb_str())


    class TestConditionDetails_Display_GUI
    {
    public:
        wxPanel* m_GUI;
        wxTextCtrl* m_TestConditionDetailsNotesTextCtrl;

        TestConditionDetails_Display_GUI();
        TestConditionDetails_Display_GUI(wxNotebook* parent);

        virtual ~TestConditionDetails_Display_GUI();

        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& TestConditionDetailsNotesTextCtrl
        );

        void Update( PropertyData* element);
    private:
    };

}; //namespace bellshire end

