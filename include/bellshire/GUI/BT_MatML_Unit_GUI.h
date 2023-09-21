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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/BT_MatML_Unit.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"

#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Unit_GUI_Base : public MatML_GUI_Base, public MatML_GUI_Lib, public Unit_Base
    {
    protected:
        wxTextCtrl* m_UnitNameTextCtrl;
        wxCheckBox* m_UnitCurrencyCheckBox;
        wxChoice* m_UnitCurrencyChoice;
        wxTextCtrl* m_UnitPowerTextCtrl;
        wxTextCtrl* m_UnitDescriptionTextCtrl;

    public:
        Unit_GUI_Base();
        Unit_GUI_Base(wxWindow* parent);
        virtual ~Unit_GUI_Base();

        wxTextCtrl* GetUnitNameTextCtrl();
        wxCheckBox* GetUnitCurrencyCheckBox();
        wxChoice* GetUnitCurrencyChoice();
        wxTextCtrl* GetUnitPowerTextCtrl();
        wxTextCtrl* GetUnitDescriptionTextCtrl();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& UnitNameTextCtrl, 
            wxCheckBox*& UnitCurrencyCheckBox, 
            wxChoice*& UnitCurrencyChoice, 
            wxTextCtrl*& UnitPowerTextCtrl, 
            wxTextCtrl*& UnitDescriptionTextCtrl
        );
        static wxWindow* CreateUnitPanel(wxWindow* parent,
            wxTextCtrl*& UnitNameTextCtrl,
            wxCheckBox*& UnitCurrencyCheckBox,
            wxChoice*& UnitCurrencyChoice,
            wxTextCtrl*& UnitPowerTextCtrl,
            wxTextCtrl*& UnitDescriptionTextCtrl
        );

        void Update( const observer_ptr<Unit> element);
        static wxString GetTreeLabel(const observer_ptr<Unit> element);
 
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
        bool operator==(const Unit_GUI_Base& other) const;
        //Unit_GUI_Base(const std::shared_ptr<Lib::Unit_lib>& m_lib_element, wxTextCtrl* m_UnitNameTextCtrl, wxCheckBox* m_UnitCurrencyCheckBox, wxChoice* m_UnitCurrencyChoice, wxTextCtrl* m_UnitPowerTextCtrl, wxTextCtrl* m_UnitDescriptionTextCtrl);
    };

    class Unit_GUI : public Unit_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Unit_GUI();
        Unit_GUI(wxWindow* parent);

        virtual ~Unit_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
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
    };

}; //namespace bellshire end

