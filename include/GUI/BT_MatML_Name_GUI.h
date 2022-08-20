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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {
    
    class AuthorityDetails_Display_GUI;

    class Name_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_NameTextCtrl;
        wxChoice* m_AuthorityChoice;
        AuthorityDetails_Display_GUI* m_NameAuthorityDetails_Display_GUI;

        Name_GUI_Base();
        Name_GUI_Base(wxWindow* parent);

        virtual ~Name_GUI_Base();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& NameTextCtrl,
            wxChoice*& AuthorityChoice, 
            AuthorityDetails_Display_GUI*& NameAuthorityDetails_Display_GUI
        );

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update(Name* element, ::boost::shared_ptr<MatML_Doc> doc);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Name& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnNameTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnNameAuthorityChoice(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Name_GUI : public Name_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Name_GUI();
        Name_GUI(wxWindow* parent);

        virtual ~Name_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnNameTextCtrl(wxCommandEvent& event);
        void OnNameAuthorityChoice(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
