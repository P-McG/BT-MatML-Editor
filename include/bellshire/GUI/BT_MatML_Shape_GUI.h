/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Shape_GUI.h
// Purpose:     Classes of Shape_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Shape.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Shape_GUI_Base : public MatML_GUI_Base, public Shape_Base
    {
    protected:
        wxTextCtrl* m_ShapeTextCtrl;

    public:
        Shape_GUI_Base();
        Shape_GUI_Base(wxWindow* parent);

        virtual ~Shape_GUI_Base();

        wxTextCtrl* GetShapeTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& ShapeTextCtrl);
        static wxWindow* CreateShapePanel(wxWindow* parent,
            wxTextCtrl*& ShapeTextCtrl
        );

        void Update( const observer_ptr<Shape> element);

        static wxString GetTreeLabel(const observer_ptr<Shape> element);
          
        void SetConnect();
        virtual void OnShapeTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

   class Shape_GUI : public Shape_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Shape_GUI();
        Shape_GUI(wxWindow* parent);

        virtual ~Shape_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnShapeTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
#pragma once
