/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Specification_GUI.h
// Purpose:     Classes of Specification_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class AuthorityDetails_Display_GUI;

    class Specification_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI; 
        wxTextCtrl* m_SpecificationTextCtrl; 
        wxChoice* m_AuthorityChoice;
        AuthorityDetails_Display_GUI* m_SpecificationAuthorityDetails_Display_GUI;

        Specification_GUI_Base();
        Specification_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& SpecificationTextCtrl, wxChoice*& AuthorityChoice, AuthorityDetails_Display_GUI*& SpecificationAuthorityDetails_Display_GUI);
        virtual ~Specification_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Specification* element, const ::boost::shared_ptr<MatML_Doc> doc);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Specification& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnSpecificationTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnSpecificationAuthorityChoice(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Specification_GUI : public Specification_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Specification_GUI();
        Specification_GUI(wxWindow* parent);

        virtual ~Specification_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnSpecificationTextCtrl(wxCommandEvent& event);
        void OnSpecificationAuthorityChoice(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

