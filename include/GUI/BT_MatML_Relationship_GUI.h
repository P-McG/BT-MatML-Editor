/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Relationship_GUI.h
// Purpose:     Classes of Relationship_GUI Base and Derived.
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

#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Relationship_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_RelationshipTextCtrl;

        Relationship_GUI_Base();
        Relationship_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& RelationshipTextCtrl);
        virtual ~Relationship_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( Relationship* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Relationship& Element,
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnRelationshipTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class Relationship_GUI : public Relationship_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Relationship_GUI();
        Relationship_GUI(wxWindow* parent);
        virtual ~Relationship_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnRelationshipTextCtrl(wxCommandEvent& event);


    private:
    };

}; //namespace bellshire end

