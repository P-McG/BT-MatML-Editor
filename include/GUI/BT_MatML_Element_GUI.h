/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Element_GUI.h
// Purpose:     Classes of Element_GUI Base and Derived.
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

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class Element_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Element_GUI_Base();
        Element_GUI_Base(wxWindow* parent);
        virtual ~Element_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        static wxNotebook* Create(wxWindow* parent);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Element& element, 
            const wxTreeItemId& PreviousId
        ); 
        void Update( Element* element);

        void SetConnect() {};

        virtual void OnInsertSymbol(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteSymbol(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteConcentration(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Element_GUI : public Element_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Element_GUI();
        Element_GUI(wxWindow* parent);

        virtual ~Element_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertSymbol(wxCommandEvent& event);
        void OnInsertConcentration(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteConcentration(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteSymbol(wxCommandEvent& event);
        void OnPasteConcentration(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
#pragma once
