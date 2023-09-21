/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Name_GUI.h
// Purpose:     Classes of Name_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/shared_ptr.hpp>

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Name.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {
    
    class AuthorityDetails_Display_GUI;

    class Name_GUI_Base : public MatML_GUI_Base, public Name_Base
    {
    protected:
        wxTextCtrl* m_NameTextCtrl;
        wxChoice* m_AuthorityChoice;
        AuthorityDetails_Display_GUI* m_NameAuthorityDetails_Display_GUI;

    public:
        Name_GUI_Base();
        Name_GUI_Base(wxWindow* parent);

        virtual ~Name_GUI_Base();

        wxTextCtrl* GetNameTextCtrl();
        wxChoice* GetAuthorityChoice();
        AuthorityDetails_Display_GUI* GetNameAuthorityDetails_Display_GUI();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& NameTextCtrl,
            wxChoice*& AuthorityChoice, 
            AuthorityDetails_Display_GUI*& NameAuthorityDetails_Display_GUI
        );
        static wxWindow* CreateNamePanel(wxWindow* parent,
            wxTextCtrl*& NameTextCtrl,
            wxChoice*& AuthorityChoice,
            AuthorityDetails_Display_GUI*& NameAuthorityDetails_Display_GUI
        );

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);
        static wxString GetTreeLabel(const observer_ptr<Name> element);

        void Update(const observer_ptr<Name> element, observer_ptr<MatML_Doc> doc);

        void SetConnect();
        virtual void OnNameTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnNameAuthorityChoice(wxCommandEvent& event) { event.Skip(); }
    };

    class Name_GUI : public Name_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Name_GUI();
        Name_GUI(wxWindow* parent);

        virtual ~Name_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnNameTextCtrl(wxCommandEvent& event);
        void OnNameAuthorityChoice(wxCommandEvent& event);
    };

}; //namespace bellshire end
