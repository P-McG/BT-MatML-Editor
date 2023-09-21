/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Associate_GUI.h
// Purpose:     Classes of Associate_GUI Base and Derived.
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

#include "bellshire/BT_MatML_Associate.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Associate_GUI_Base : public MatML_GUI_Base, public Associate_Base 
    {
    protected:
        wxTextCtrl* m_AssociateTextCtrl{nullptr};
    public:
        Associate_GUI_Base();
        Associate_GUI_Base(wxWindow* parent);
        virtual ~Associate_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& AssociateTextCtrl
        );
        static wxWindow* CreateAssociatePanel(wxWindow* parent,
            wxTextCtrl*& AssociateTextCtrl
        );

        wxTextCtrl* GetAssociateTextCtrl();
        static wxString GetTreeLabel(const observer_ptr<Associate> Element);

        void Update( const observer_ptr<Associate> element);

        void SetConnect();
        virtual void OnAssociateTextCtrl(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Associate_GUI : public Associate_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
    public:
        Associate_GUI();
        Associate_GUI(wxWindow* parent);
        virtual ~Associate_GUI() {};

        TreeCtrlSorted* GetMatMLTreeCtrl();
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnAssociateTextCtrl(wxCommandEvent& event);

    private:
    };
}; //namespace bellshire end
