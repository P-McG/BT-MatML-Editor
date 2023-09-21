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

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "bellshire/utilities/StringStream.h"

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_MeasurementTechniqueDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class ID_GUI;

    class MeasurementTechniqueDetails_GUI_Base : public MatML_GUI_Base, public MeasurementTechniqueDetails_Base
    {
    protected:
        ID_GUI* m_MeasurementTechniqueDetails_ID_GUI;

    public:
        MeasurementTechniqueDetails_GUI_Base();
        MeasurementTechniqueDetails_GUI_Base(wxWindow* parent);

        virtual ~MeasurementTechniqueDetails_GUI_Base();

        ID_GUI* GetMeasurementTechniqueDetails_ID_GUI();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& MeasurementTechniqueDetails_ID_GUI
        );
        static wxWindow* CreateMeasurementTechniqueDetailsPanel(wxWindow* parent,
            ID_GUI*& MeasurementTechniqueDetails_ID_GUI
        );

        void Update( const observer_ptr<MeasurementTechniqueDetails> element);

        static ::std::string Label(::std::string name, ::std::string id);
        static wxString GetTreeLabel(const observer_ptr<MeasurementTechniqueDetails> element);

        void SetConnect();
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

   class MeasurementTechniqueDetails_GUI : public MeasurementTechniqueDetails_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        MeasurementTechniqueDetails_GUI();
        MeasurementTechniqueDetails_GUI(wxWindow* parent);

        virtual ~MeasurementTechniqueDetails_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class event handler functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };
}; //namespace bellshire end
