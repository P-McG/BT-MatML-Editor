/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Definition_GUI.h
// Purpose:     Classes of Definition_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Definition.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Definition_GUI_Base : public MatML_GUI_Base, public Definition_Base
    {
    protected:
        wxTextCtrl* m_DefinitionTextCtrl;

    public:
        Definition_GUI_Base();
        Definition_GUI_Base(wxWindow* parent);
        virtual ~Definition_GUI_Base();

        wxTextCtrl* GetDefinitionTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& DefinitionTextCtrl);
        static wxWindow* CreateDefinitionPanel(wxWindow* parent, wxTextCtrl*& DefinitionTextCtrl);

        void Update(const observer_ptr<Definition> element);

        static wxString GetTreeLabel(const observer_ptr<Definition> element);

        void SetConnect();
        virtual void OnDefinitionTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class Definition_GUI : public Definition_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:

        Definition_GUI();
        Definition_GUI(wxWindow* parent);

        virtual ~Definition_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnDefinitionTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end
