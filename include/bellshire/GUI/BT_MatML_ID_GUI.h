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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include "wx/event.h"
#include <wx/msgdlg.h>

#include <memory>
#include <math.h>
#include <string>

#include "bellshire/matml31.hxx"

#include "bellshire/utilities/Uuid-Utility.h"

//#include "bellshire/BT_MatML_GUI.h"
#include "bellshire/BT_MatML_MatML_Doc.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class ID_GUI_Base : public wxEvtHandler
    {
    protected:
        wxPanel* m_GUI;
        wxButton* m_GenerateUuidButton;
        wxTextCtrl* m_IDTextCtrl;
        wxCheckBox* m_ReplaceIDRefs;

    public:
        ID_GUI_Base();
        ID_GUI_Base(wxWindow* parent);
        static wxPanel* Create(wxWindow* parent, wxButton*& GenerateUuidButton, wxTextCtrl*& IDTextCtrl, wxCheckBox*& ReplaceIDRefs);
        virtual ~ID_GUI_Base();

        wxPanel* GetGUI();
        wxButton* GetGenerateUuidButton();
        wxTextCtrl* GetIDTextCtrl();
        wxCheckBox* GetReplaceIDRefs();

        //template<class MatML_class>
        //void Update(MatML_class* element);

        void Update( const observer_ptr<Material> element);
        void Update( const observer_ptr<ComponentDetails> element);
        void Update( const observer_ptr<TestConditionDetails> element);
        void Update( const observer_ptr<SpecimenDetails> element);
        void Update( const observer_ptr<SourceDetails> element);
        void Update( const observer_ptr<PropertyDetails> element);
        void Update( const observer_ptr<ParameterDetails> element);
        void Update( const observer_ptr<MeasurementTechniqueDetails> element);
        void Update( const observer_ptr<DataSourceDetails> element);
        void Update( const observer_ptr<AuthorityDetails> element);

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxPanel* get() { return m_GUI; };

        void SetConnect();
        virtual void OnGenerateUuidButton(wxCommandEvent& event) { event.Skip(); }
        virtual void OnIDTextCtrl(wxCommandEvent& event) {event.Skip();}
    };

  class ID_GUI : public ID_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        observer_ptr<MatML_Doc> m_MatMLDoc;

    public:
        ID_GUI();
        ID_GUI(wxWindow* parent);

        virtual ~ID_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        observer_ptr<MatML_Doc> GetMatMLDoc();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, const observer_ptr<MatML_Doc> matml_doc);
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(const observer_ptr<MatML_Doc>& matml_doc);
        
        //Overwrites the base class functions
        void SwapIDRefs(const observer_ptr<MatML_Doc> matmldoc, xml_schema::idref& oldid, xml_schema::idref& newid);
        void OnGenerateUuidButton(wxCommandEvent& event);
        void OnIDTextCtrl(wxCommandEvent& event);
        bool Warning();

        void GenerateUuid(const observer_ptr<Material> element);
        void GenerateUuid(const observer_ptr < TestConditionDetails> element);
        void GenerateUuid(const observer_ptr < SpecimenDetails> element);
        void GenerateUuid(const observer_ptr < SourceDetails> element);
        void GenerateUuid(const observer_ptr < PropertyDetails> element);
        void GenerateUuid(const observer_ptr < ParameterDetails> element);
        void GenerateUuid(const observer_ptr < MeasurementTechniqueDetails> element);
        void GenerateUuid(const observer_ptr < DataSourceDetails> element);
        void GenerateUuid(const observer_ptr < ComponentDetails> element);
        void GenerateUuid(const observer_ptr < AuthorityDetails> element);
        ::std::string GetUUIDLabel();

        template<class MatML_Class>
        void ExchangeIDRefWithID(::boost::any any_ptr);

        template<class MatML_Class>
        void ExchangeIDRefWithOptionalID(::boost::any any_ptr);
    };

};//ending Bellshire namespace

#include "bellshire/GUI/BT_MatML_ID_GUI.inl"

