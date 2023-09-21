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



// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ChemicalElementSymbol.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {
    class ChemicalElementSymbol_GUI_Base : public MatML_GUI_Base, public ChemicalElementSymbol_Base
    {
    protected:
        wxChoice* m_ChemicalElementSymbolChoice;

    public:
        ChemicalElementSymbol_GUI_Base();
        ChemicalElementSymbol_GUI_Base(wxWindow* parent);
        virtual ~ChemicalElementSymbol_GUI_Base();

        wxChoice* GetChemicalElementSymbolChoice();

        static wxNotebook* Create(wxWindow* parent,
            wxChoice*& ChemicalElementSymbolChoice
        );
        static wxWindow* CreateChemicalElementSymbolPanel(wxWindow* parent,
            wxChoice*& ChemicalElementSymbolChoice
        );

        static wxString GetTreeLabel(const observer_ptr<ChemicalElementSymbol> element);

        void Update( const observer_ptr<ChemicalElementSymbol> element);

        void SetConnect();
        virtual void OnChemicalElementSymbol(wxCommandEvent& event) { event.Skip(); }

    private:
    };

  class ChemicalElementSymbol_GUI : public ChemicalElementSymbol_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        ChemicalElementSymbol_GUI();
        ChemicalElementSymbol_GUI(wxWindow* parent);

        virtual ~ChemicalElementSymbol_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnChemicalElementSymbol(wxCommandEvent& event);

    };

}; //namespace bellshire end
