/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Orientation_GUI.h
// Purpose:     Classes of Orientation_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Orientation.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Orientation_GUI_Base : public MatML_GUI_Base, public Orientation_Base
    {
    protected:
        wxTextCtrl* m_OrientationTextCtrl;

    public:
        Orientation_GUI_Base();
        Orientation_GUI_Base(wxWindow* parent);
        virtual ~Orientation_GUI_Base();

        wxTextCtrl* GetOrientationTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& m_OrientationTextCtrl);
        static wxWindow* CreateOrientationPanel(wxWindow* parent,
            wxTextCtrl*& OrientationTextCtrl
        );

        void Update( const observer_ptr<Orientation> element);

        static wxString GetTreeLabel(const observer_ptr<Orientation> element);

        void SetConnect();
        virtual void OnOrientationTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

   class Orientation_GUI : public Orientation_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Orientation_GUI();
        Orientation_GUI(wxWindow* parent);

        virtual ~Orientation_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnOrientationTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
