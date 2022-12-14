/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Unit_GUI.h
// Purpose:     Classes of Unit_GUI Base and Derived.
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
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Unit_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_UnitNameTextCtrl;
        wxCheckBox* m_UnitCurrencyCheckBox;
        wxChoice* m_UnitCurrencyChoice;
        wxTextCtrl* m_UnitPowerTextCtrl;
        wxTextCtrl* m_UnitDescriptionTextCtrl;

        Unit_GUI_Base();
        Unit_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxTextCtrl*& UnitNameTextCtrl, wxCheckBox*& UnitCurrencyCheckBox, wxChoice*& UnitCurrencyChoice, wxTextCtrl*& UnitPowerTextCtrl, wxTextCtrl*& UnitDescriptionTextCtrl);
        virtual ~Unit_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Unit* element);
        static wxTreeItemId  SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Unit& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnUnitNotebook(wxNotebookEvent& event) { event.Skip(); }
        virtual void OnUnitNameTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitCurrencyCheckBox(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitCurrencyChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitPowerTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitDescriptionTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertCurrency(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteCurrencyCode(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Unit_GUI : public Unit_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Unit_GUI();
        Unit_GUI(wxWindow* parent);

        virtual ~Unit_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);

        //Overwrites the base class functions
        void OnUnitNameTextCtrl(wxCommandEvent& event);
        void OnUnitCurrencyCheckBox(wxCommandEvent& event);
        void OnUnitCurrencyChoice(wxCommandEvent& event);
        void OnUnitPowerTextCtrl(wxCommandEvent& event);
        void OnUnitDescriptionTextCtrl(wxCommandEvent& event);

        void OnInsertName(wxCommandEvent& event);
        void OnInsertCurrency(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteCurrencyCode(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

