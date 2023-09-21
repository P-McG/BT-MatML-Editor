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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Relationship.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Relationship_GUI_Base : public MatML_GUI_Base, public Relationship_Base
    {
    protected:
        wxTextCtrl* m_RelationshipTextCtrl;

    public:
        Relationship_GUI_Base();
        Relationship_GUI_Base(wxWindow* parent);
        virtual ~Relationship_GUI_Base();

        wxTextCtrl* GetRelationshipTextCtrl();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& RelationshipTextCtrl
        );
        static wxWindow* CreateRelationshipPanel(wxWindow* parent,
            wxTextCtrl*& RelationshipTextCtrl
        );

        void Update( const observer_ptr<Relationship> element);

        static wxString GetTreeLabel(const observer_ptr<Relationship> element);
 
        void SetConnect();
        virtual void OnRelationshipTextCtrl(wxCommandEvent& event) { event.Skip(); }
    };

   class Relationship_GUI : public Relationship_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Relationship_GUI();
        Relationship_GUI(wxWindow* parent);
        virtual ~Relationship_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnRelationshipTextCtrl(wxCommandEvent& event);
    };

}; //namespace bellshire end

