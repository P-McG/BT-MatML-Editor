/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ChemicalElementSymbol_GUI.h
// Purpose:     Classes of ChemicalElementSymbol_GUI Base and Derived.
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

    //Utility for std:string and wxString
    #define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
    #define _wx2std(var) std::string(var.mb_str())

    class ChemicalElementSymbol_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxChoice* m_ChemicalElementSymbolChoice;
        wxNotebook* m_GUI;

        ChemicalElementSymbol_GUI_Base();
        ChemicalElementSymbol_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxChoice*& ChemicalElementSymbolChoice);
        virtual ~ChemicalElementSymbol_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            ChemicalElementSymbol& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( ChemicalElementSymbol* element);

        void SetConnect();
        virtual void OnChemicalElementSymbol(wxCommandEvent& event) { event.Skip(); }

    private:
    };

  class ChemicalElementSymbol_GUI : public ChemicalElementSymbol_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        ChemicalElementSymbol_GUI();
        ChemicalElementSymbol_GUI(wxWindow* parent);

        virtual ~ChemicalElementSymbol_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnChemicalElementSymbol(wxCommandEvent& event);
 
    private:
    };

}; //namespace bellshire end
