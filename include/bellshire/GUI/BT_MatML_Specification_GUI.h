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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Specification.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class AuthorityDetails_Display_GUI;

    class Specification_GUI_Base : public MatML_GUI_Base, public Specification_Base
    {
    protected:
        wxTextCtrl* m_SpecificationTextCtrl; 
        wxChoice* m_AuthorityChoice;
        AuthorityDetails_Display_GUI* m_SpecificationAuthorityDetails_Display_GUI;

    public:
        Specification_GUI_Base();
        Specification_GUI_Base(wxWindow* parent);

        wxTextCtrl* GetSpecificationTextCtrl();
        wxChoice* GetAuthorityChoice();
        AuthorityDetails_Display_GUI* GetSpecificationAuthorityDetails_Display_GUI();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& SpecificationTextCtrl, 
            wxChoice*& AuthorityChoice,
            AuthorityDetails_Display_GUI*& SpecificationAuthorityDetails_Display_GUI
        );
        static wxWindow* CreateSpecificationPanel(wxWindow* parent,
            wxTextCtrl*& SpecificationTextCtrl,
            wxChoice*& AuthorityChoice,
            AuthorityDetails_Display_GUI*& SpecificationAuthorityDetails_Display_GUI
        );

        virtual ~Specification_GUI_Base();

        void Update( const observer_ptr<Specification> element, const observer_ptr<MatML_Doc> doc);

        static wxString GetTreeLabel(const observer_ptr<Specification> element);

        void SetConnect();
        virtual void OnSpecificationTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnSpecificationAuthorityChoice(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event){ event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event){ event.Skip(); }
    };

    class Specification_GUI : public Specification_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Specification_GUI();
        Specification_GUI(wxWindow* parent);

        virtual ~Specification_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnSpecificationTextCtrl(wxCommandEvent& event);
        void OnSpecificationAuthorityChoice(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end

