/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Glossary_GUI.h
// Purpose:     Classes of Glossary_GUI Base and Derived.
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

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "StringStream.h"

#include "matml31.hxx"
#include "matml31_strongtypedef.h"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Glossary_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Glossary_GUI_Base();
        Glossary_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~Glossary_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Glossary* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Glossary& Element,
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};
        virtual void OnInsertTerm(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteGlossaryTerm(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteTerm(wxCommandEvent& event) { event.Skip(); }

    private:
    };


    class Glossary_GUI : public Glossary_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Glossary_GUI();
        Glossary_GUI(wxWindow* parent);

        virtual ~Glossary_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertTerm(wxCommandEvent& event);

        void OnDeleteGlossaryTerm(wxCommandEvent& event);

        void OnPasteTerm(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
