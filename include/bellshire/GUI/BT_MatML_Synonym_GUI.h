/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Synonym_GUI.h
// Purpose:     Classes of Synonym_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Synonym.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Synonym_GUI_Base : public MatML_GUI_Base, public Synonym_Base
    {
    protected:
        wxTextCtrl* m_SynonymTextCtrl;

    public:
        Synonym_GUI_Base();
        Synonym_GUI_Base(wxWindow* parent);
        virtual ~Synonym_GUI_Base();

        wxTextCtrl* GetSynonymTextCtrl();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& SynonymTextCtrl);
        static wxWindow* CreateSynonymPanel(wxWindow* parent,
            wxTextCtrl*& SynonymTextCtrl
        );

        void Update( const observer_ptr<Synonym> element);

        static wxString GetTreeLabel(const observer_ptr<Synonym> element);

        void SetConnect();
        virtual void OnSynonymTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class Synonym_GUI : public Synonym_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Synonym_GUI();
        Synonym_GUI(wxWindow* parent);

        virtual ~Synonym_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnSynonymTextCtrl(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end
