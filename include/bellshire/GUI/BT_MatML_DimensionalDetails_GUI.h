/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_DimensionalDetails_GUI.h
// Purpose:     Classes of DimensionalDetails_GUI Base and Derived.
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
#include "bellshire/BT_MatML_DimensionalDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class DimensionalDetails_GUI_Base : public MatML_GUI_Base, public DimensionalDetails_Base
    {
    protected:

    public:
        DimensionalDetails_GUI_Base();
        DimensionalDetails_GUI_Base(wxWindow* parent);
        virtual ~DimensionalDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateDimensionalDetailsPanel(wxWindow* parent);

        void Update( const observer_ptr<DimensionalDetails> element);

        static wxString GetTreeLabel(const observer_ptr<DimensionalDetails> element);

        void SetConnect() {};
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertUnits(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertQualifier(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertUncertainty(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUncertainty(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUnits(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteValue(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUnits(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteQualifier(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUncertainty(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event){ event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event){ event.Skip(); }

    private:
    };


    class DimensionalDetails_GUI : public DimensionalDetails_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        DimensionalDetails_GUI();
        DimensionalDetails_GUI(wxWindow* parent);

        virtual ~DimensionalDetails_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertValue(wxCommandEvent& event);
        void OnInsertUnits(wxCommandEvent& event);
        void OnInsertQualifier(wxCommandEvent& event);
        void OnInsertUncertainty(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteQualifier(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteUncertainty(wxCommandEvent& event);
        void OnDeleteUnits(wxCommandEvent& event);
        void OnDeleteValue(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteValue(wxCommandEvent& event);
        void OnPasteUnits(wxCommandEvent& event);
        void OnPasteQualifier(wxCommandEvent& event);
        void OnPasteUncertainty(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end
#pragma once
