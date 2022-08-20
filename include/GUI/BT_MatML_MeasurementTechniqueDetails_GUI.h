/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_MeasurementTechniqueDetails_GUI.h
// Purpose:     Classes of MeasurementTechniqueDetails_GUI Base and Derived.
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
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ID_GUI;

    class MeasurementTechniqueDetails_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        ID_GUI* m_MeasurementTechniqueDetails_ID_GUI;

        MeasurementTechniqueDetails_GUI_Base();
        MeasurementTechniqueDetails_GUI_Base(wxWindow* parent);

        virtual ~MeasurementTechniqueDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& MeasurementTechniqueDetails_ID_GUI
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( MeasurementTechniqueDetails* element);

        static ::std::string Label(::std::string name, ::std::string id);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            MeasurementTechniqueDetails& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class MeasurementTechniqueDetails_GUI : public MeasurementTechniqueDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        MeasurementTechniqueDetails_GUI();
        MeasurementTechniqueDetails_GUI(wxWindow* parent);

        virtual ~MeasurementTechniqueDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class event handler functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };
}; //namespace bellshire end
