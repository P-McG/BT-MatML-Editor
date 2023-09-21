/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Uncertainty_GUI.h
// Purpose:     Classes of Uncertainty_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Uncertainty.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class Uncertainty_GUI_Base : public MatML_GUI_Base, public Uncertainty_Base
    {
    protected:
        wxTextCtrl* m_UncertaintyDistributionTypeTextCtrl;
        wxTextCtrl* m_UncertaintyNum_Std_DevTextCtrl;
        wxTextCtrl* m_UncertaintyPercentileTextCtrl;
        wxTextCtrl* m_UncertaintyConfidenceLevelTextCtrl;
        wxChoice* m_UncertaintyScaleChoice;

    public:
        Uncertainty_GUI_Base();
        Uncertainty_GUI_Base(wxWindow* parent);
        virtual ~Uncertainty_GUI_Base();

        wxTextCtrl* GetUncertaintyDistributionTypeTextCtrl();
        wxTextCtrl* GetUncertaintyNum_Std_DevTextCtrl();
        wxTextCtrl* GetUncertaintyPercentileTextCtrl();
        wxTextCtrl* GetUncertaintyConfidenceLevelTextCtrl();
        wxChoice* GetUncertaintyScaleChoice();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& UncertaintyDistributionTypeTextCtrl,
            wxTextCtrl*& UncertaintyNum_Std_DevTextCtrl,
            wxTextCtrl*& UncertaintyPercentileTextCtrl,
            wxTextCtrl*& UncertaintyConfidenceLevelTextCtrl,
            wxChoice*& UncertaintyScaleChoice
        );
        static wxWindow* CreateUncertaintyPanel(wxWindow* parent,
            wxTextCtrl*& UncertaintyDistributionTypeTextCtrl,
            wxTextCtrl*& UncertaintyNum_Std_DevTextCtrl,
            wxTextCtrl*& UncertaintyPercentileTextCtrl,
            wxTextCtrl*& UncertaintyConfidenceLevelTextCtrl,
            wxChoice*& UncertaintyScaleChoice
        );

        void Update( const observer_ptr<Uncertainty> element);

        static wxString GetTreeLabel(const observer_ptr<Uncertainty> element);

        void SetConnect();
        virtual void OnUncertaintyDistributionTypeTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUncertaintyNum_Std_DevTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUncertaintyPercentileTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUncertaintyConfidenceLevelTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUncertaintyScaleChoice(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertUnits(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertUnitless(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertScale(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteUnitless(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUnits(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteValue(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteScale(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUnits(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUnitless(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteScale(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class Uncertainty_GUI : public Uncertainty_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Uncertainty_GUI();
        Uncertainty_GUI(wxWindow* parent);

        virtual ~Uncertainty_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnUncertaintyDistributionTypeTextCtrl(wxCommandEvent& event);
        void OnUncertaintyNum_Std_DevTextCtrl(wxCommandEvent& event);
        void OnUncertaintyPercentileTextCtrl(wxCommandEvent& event);
        void OnUncertaintyConfidenceLevelTextCtrl(wxCommandEvent& event);
        //void OnUncertaintyScaleChoice(wxCommandEvent& event); //todo

        void OnInsertValue(wxCommandEvent& event);
        void OnInsertUnits(wxCommandEvent& event);
        void OnInsertUnitless(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);
        void OnInsertScale(wxCommandEvent& event);

        void OnDeleteUnitless(wxCommandEvent& event);
        void OnDeleteUnits(wxCommandEvent& event);
        void OnDeleteValue(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteScale(wxCommandEvent& event);

        void OnPasteValue(wxCommandEvent& event);
        void OnPasteUnits(wxCommandEvent& event);
        void OnPasteUnitless(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);
        void OnPasteScale(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end

