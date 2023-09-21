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



// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ChemicalComposition.h"

#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class ChemicalComposition_GUI_Base : public MatML_GUI_Base, public ChemicalComposition_Base
    {
    protected:

    public:

        ChemicalComposition_GUI_Base();
        ChemicalComposition_GUI_Base(wxWindow* parent);
        virtual ~ChemicalComposition_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateChemicalCompositionPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<ChemicalComposition> element);

        void Update( const observer_ptr<ChemicalComposition> element);

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
    protected:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        ChemicalComposition_GUI();
        ChemicalComposition_GUI(wxWindow* parent);

        virtual ~ChemicalComposition_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

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
    };

}; //namespace bellshire end
