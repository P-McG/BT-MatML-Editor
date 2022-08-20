/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ID_GUI.h
// Purpose:     Classes of ID_GUI Base and Derived.
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
#include "wx/event.h"
#include <wx/msgdlg.h>

#include <math.h>

#include "matml31.hxx"

#include "Uuid-Utility.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class ID_GUI_Base : public wxEvtHandler
    {
    public:
        wxPanel* m_GUI;
        wxButton* m_GenerateUuidButton;
        wxTextCtrl* m_IDTextCtrl;

        ID_GUI_Base();
        ID_GUI_Base(wxWindow* parent);
        static wxPanel* Create(wxWindow* parent, wxButton*& GenerateUuidButton, wxTextCtrl*& IDTextCtrl);
        virtual ~ID_GUI_Base();

        //template<class MatML_class>
        //void Update(MatML_class* element);

        void Update( Material* element);
        void Update( ComponentDetails* element);
        void Update( TestConditionDetails* element);
        void Update( SpecimenDetails* element);
        void Update( SourceDetails* element);
        void Update( PropertyDetails* element);
        void Update( ParameterDetails* element);
        void Update( MeasurementTechniqueDetails* element);
        void Update( DataSourceDetails* element);

        void Update( AuthorityDetails* element);

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxPanel* get() { return m_GUI; };


        void SetConnect();
        virtual void OnGenerateUuidButton(wxCommandEvent& event) { event.Skip(); }
        virtual void OnIDTextCtrl(wxCommandEvent& event) {event.Skip();}

    private:
    };

  class ID_GUI : public ID_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        ID_GUI();
        ID_GUI(wxWindow* parent);

        virtual ~ID_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        
        //Overwrites the base class functions
        void OnGenerateUuidButton(wxCommandEvent& event);
        void OnIDTextCtrl(wxCommandEvent& event);
        bool Warning();

        void GenerateUuid(Material* element);
        void GenerateUuid(TestConditionDetails* element);
        void GenerateUuid(SpecimenDetails* element);
        void GenerateUuid(SourceDetails* element);
        void GenerateUuid(PropertyDetails* element);
        void GenerateUuid(ParameterDetails* element);
        void GenerateUuid(MeasurementTechniqueDetails* element);
        void GenerateUuid(DataSourceDetails* element);
        void GenerateUuid(ComponentDetails* element);
        void GenerateUuid(AuthorityDetails* element);
        ::string GetUUIDLabel();

    private:
    };

};//ending Bellshire namespace

