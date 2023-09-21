/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_AuthorityDetails_GUI.h
// Purpose:     Classes of AuthorityDetails_GUI Base and Derived.
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
#include <memory>
#include <math.h>

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_AuthorityDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class ID_GUI;

    class AuthorityDetails_GUI_Base : public MatML_GUI_Base, public AuthorityDetails_Base
    {
    protected:
        ID_GUI* m_AuthorityDetails_ID_GUI;

    public:
        AuthorityDetails_GUI_Base();
        AuthorityDetails_GUI_Base(wxWindow* parent);
        virtual ~AuthorityDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& AuthorityDetails_ID_GUI
        );
        static wxWindow* CreateAuthorityDetailsPanel(wxWindow* parent,
            ID_GUI*& AuthorityDetails_ID_GUI
        );

        void Update( const observer_ptr<AuthorityDetails> element);

        static ::std::string Label(::std::string name, ::std::string id);

        ID_GUI* GetAuthorityDetails_ID_GUI();
        static wxString GetTreeLabel(const observer_ptr<AuthorityDetails> Element);

        void SetConnect();

        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    private:
    };


    class AuthorityDetails_GUI : public AuthorityDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        AuthorityDetails_GUI();
        AuthorityDetails_GUI(wxWindow* parent);

        virtual ~AuthorityDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

        typedef Metadata::AuthorityDetails_sequence& (Metadata::* Cont_Func)();

    private:
    };
}; //namespace bellshire end

 // Template include
 #include "bellshire/GUI/BT_MatML_AuthorityDetails_GUI.inl"