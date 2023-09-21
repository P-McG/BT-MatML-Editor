/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Abbreviation_GUI.h
// Purpose:     Classes of Abbreviation_GUI Base and Derived.
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

#include "bellshire/BT_MatML_Abbreviation.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"


namespace bellshire::GUI {

    class Abbreviation_GUI_Base : public MatML_GUI_Base, public Abbreviation_Base
    {
    protected:
        wxTextCtrl* m_AbbreviationTextCtrl{ nullptr };
    public:
        Abbreviation_GUI_Base();
        Abbreviation_GUI_Base(wxWindow* parent);
        virtual ~Abbreviation_GUI_Base() {};

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& AbbreviationTextCtrl
        );
        static wxWindow* CreateAbbreviationPanel(wxWindow* parent,
            wxTextCtrl*& AbbreviationTextCtrl
        );

        wxTextCtrl* GetAbbreviationTextCtrl();
        static wxString GetTreeLabel(const observer_ptr<Abbreviation> Element);

        void Update( const observer_ptr<Abbreviation> element);

        void SetConnect();

        virtual void OnAbbreviationTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    };

    class Abbreviation_GUI : public  Abbreviation_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl{ nullptr };//Required before Event Handling.

    public:
        Abbreviation_GUI();
        Abbreviation_GUI(wxWindow* parent);
        virtual ~Abbreviation_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnAbbreviationTextCtrl(wxCommandEvent& event); //todo

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end
