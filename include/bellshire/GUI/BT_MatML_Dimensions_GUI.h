/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Dimensions_GUI.h
// Purpose:     Classes of Dimensions_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Dimensions.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Dimensions_GUI_Base : public MatML_GUI_Base, public Dimensions_Base
    {
    protected:
        wxTextCtrl* m_DimensionsTextCtrl;

    public:
        Dimensions_GUI_Base();
        Dimensions_GUI_Base(wxWindow* parent);
        virtual ~Dimensions_GUI_Base();

        wxTextCtrl* GetDimensionsTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& DimensionsTextCtrl);
        static wxWindow* CreateDimensionsPanel(wxWindow* parent, wxTextCtrl*& DimensionsTextCtrl);

        void Update( const observer_ptr<Dimensions> element);

        static wxString GetTreeLabel(const observer_ptr<Dimensions> element);

        void SetConnect();
        virtual void OnDimensionsTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

   class Dimensions_GUI : public Dimensions_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Dimensions_GUI();
        Dimensions_GUI(wxWindow* parent);

        virtual ~Dimensions_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnDimensionsTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
#pragma once
