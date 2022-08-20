/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ChemicalComposition_GUI.h
// Purpose:     Classes of ChemicalComposition_GUI Base and Derived.
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
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ChemicalComposition_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        ChemicalComposition_GUI_Base();
        ChemicalComposition_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~ChemicalComposition_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            ChemicalComposition& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( ChemicalComposition* element);

        void SetConnect() {};
        virtual void OnInsertCompound(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertElement(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteCompound(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteElement(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteCompound(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteElement(wxCommandEvent& event){ event.Skip(); }

    private:
    };

   class ChemicalComposition_GUI : public ChemicalComposition_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        ChemicalComposition_GUI();
        ChemicalComposition_GUI(wxWindow* parent);

        virtual ~ChemicalComposition_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertCompound(wxCommandEvent& event);
        void OnInsertElement(wxCommandEvent& event);

        void OnDeleteCompound(wxCommandEvent& event);
        void OnDeleteElement(wxCommandEvent& event);

        void OnPasteCompound(wxCommandEvent& event);
        void OnPasteElement(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
