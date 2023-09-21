/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Result_GUI.h
// Purpose:     Classes of Result_GUI Base and Derived.
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
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_Result.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Result_GUI_Base : public MatML_GUI_Base, public Result_Base
    {
    protected:
        wxTextCtrl* m_ResultTextCtrl;

    public:
        Result_GUI_Base();
        Result_GUI_Base(wxWindow* parent);
        virtual ~Result_GUI_Base();

        wxTextCtrl* GetResultTextCtrl();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& ResultTextCtrl
        );
        static wxWindow* CreateResultPanel(wxWindow* parent,
            wxTextCtrl*& ResultTextCtrl
        );

        static wxString GetTreeLabel(const observer_ptr<Result> element);

        void Update( const observer_ptr<Result> element);

        void SetConnect();
        virtual void OnResultTextCtrl(wxCommandEvent& event) { event.Skip(); }

    };

    class Result_GUI : public  Result_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Result_GUI();
        Result_GUI(wxWindow* parent);

        virtual ~Result_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnResultTextCtrl(wxCommandEvent& event); //todo
    };

}; //namespace bellshire end
