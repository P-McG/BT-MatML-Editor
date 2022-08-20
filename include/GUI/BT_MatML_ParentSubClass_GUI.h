/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ParentSubClass_GUI.h
// Purpose:     ParentSubClasses of ParentSubClass_GUI Base and Derived.
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
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class ParentSubClass_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_ParentSubClassTextCtrl;

        ParentSubClass_GUI_Base();
        ParentSubClass_GUI_Base(wxWindow* parent);
        virtual ~ParentSubClass_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& ParentSubClassTextCtrl);
        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Class::ParentSubClass_type& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update(ParentSubClass* element);

        void SetConnect() {};
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertParentMaterial(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertParentSubClass(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParentMaterial(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParentSubClass(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteParentMaterial(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteParentSubClass(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class ParentSubClass_GUI : public ParentSubClass_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        ParentSubClass_GUI();
        ParentSubClass_GUI(wxWindow* parent);

        virtual ~ParentSubClass_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertParentMaterial(wxCommandEvent& event);
        void OnInsertParentSubClass(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteParentMaterial(wxCommandEvent& event);
        void OnDeleteParentSubClass(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteParentMaterial(wxCommandEvent& event);
        void OnPasteParentSubClass(wxCommandEvent& event);

        void OnBumpUp(wxCommandEvent& event);
        void OnBumpDown(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
