/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_AssociationDetails_GUI.h
// Purpose:     Classes of AssociationDetails_GUI Base and Derived.
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

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_AssociationDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class AssociationDetails_GUI_Base : public MatML_GUI_Base, public AssociationDetails_Base
    {
    protected:
    public:
        AssociationDetails_GUI_Base();
        AssociationDetails_GUI_Base(wxWindow* parent);
        virtual ~AssociationDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateAssociationDetailsPanel(wxWindow* parent
        );

        static wxString GetTreeLabel(const observer_ptr<AssociationDetails> Element);

        void Update( const observer_ptr<AssociationDetails> element);

        void SetConnect();

        //EvtHandler functions to be binded and overwritten by derived class.
        virtual void OnInsertAssociate(wxCommandEvent& event) {event.Skip(); };
        virtual void OnInsertRelationship(wxCommandEvent& event) { event.Skip(); };
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); };

        virtual void OnDeleteAssociate(wxCommandEvent& event){ event.Skip(); }
        virtual void OnDeleteRelationship(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteAssociate(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteRelationship(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class AssociationDetails_GUI : public AssociationDetails_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        AssociationDetails_GUI();
        AssociationDetails_GUI(wxWindow* parent);

        virtual ~AssociationDetails_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();
        ::boost::any GetMatMLItemToCopy();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions

        void OnInsertAssociate(wxCommandEvent& event);
        void OnInsertRelationship(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteAssociate(wxCommandEvent& event);
        void OnDeleteRelationship(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteAssociate(wxCommandEvent& event);
        void OnPasteRelationship(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };


}; //namespace bellshire end
