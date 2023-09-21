/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Description_GUI.h
// Purpose:     Classes of Description_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Description.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Description_GUI_Base : public MatML_GUI_Base, public Description_Base
    {
    protected:
        wxTextCtrl* m_DescriptionTextCtrl;

    public:
        Description_GUI_Base();
        Description_GUI_Base(wxWindow* parent);
        virtual ~Description_GUI_Base();

        wxTextCtrl* GetDescriptionTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& DescriptionTextCtrl);
        static wxWindow* CreateDescriptionPanel(wxWindow* parent, wxTextCtrl*& DescriptionTextCtrl);

        void Update( const observer_ptr<Description> element);

        static wxString GetTreeLabel(const observer_ptr<Description> element);

        void SetConnect();
        virtual void OnDescriptionTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

   class Description_GUI : public Description_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Description_GUI();
        Description_GUI(wxWindow* parent);

        virtual ~Description_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnDescriptionTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
#pragma once
