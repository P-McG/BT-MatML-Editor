/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_PropertyData_GUI.h
// Purpose:     Classes of PropertyData_GUI Base and Derived.
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
#include <wx/grid.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include <list>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class PropertyDetails_Display_GUI;
    class MeasurementTechniqueDetails_Display_GUI;
    class DataSourceDetails_Display_GUI;
    class SpecimenDetails_Display_GUI;
    class TestConditionDetails_Display_GUI;

    class PropertyData_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxChoice* m_PropertyDataPropertiesChoice;
        wxChoice* m_PropertyDataTechniqueChoice;
        wxChoice* m_PropertyDataSourceChoice;
        wxChoice* m_PropertyDataSpecimenChoice;
        wxChoice* m_PropertyDataTestChoice;
        wxTextCtrl* m_PropertyDataDelimiterTextCtrl;
        wxTextCtrl* m_PropertyDataQuoteTextCtrl;
        PropertyDetails_Display_GUI* m_PropertyDataPropertyDetails_Display_GUI;
        MeasurementTechniqueDetails_Display_GUI* m_PropertyDataMeasurementTechniqueDetails_Display_GUI;
        DataSourceDetails_Display_GUI* m_PropertyDataDataSourceDetails_Display_GUI;
        SpecimenDetails_Display_GUI* m_PropertyDataSpecimenDetails_Display_GUI;
        TestConditionDetails_Display_GUI* m_PropertyDataTestConditionDetails_Display_GUI;

        PropertyData_GUI_Base();
        PropertyData_GUI_Base(wxWindow* parent);

        virtual ~PropertyData_GUI_Base();

        static wxNotebook* Create(wxWindow* parent,
            wxChoice*& PropertyDataPropertiesChoice, 
            wxChoice*& PropertyDataTechniqueChoice, 
            wxChoice*& PropertyDataSourceChoice, 
            wxChoice*& PropertyDataSpecimenChoice, 
            wxChoice*& PropertyDataTestChoice, 
            wxTextCtrl*& PropertyDataDelimiterTextCtrl, 
            wxTextCtrl*& PropertyDataQuoteTextCtrl,
            PropertyDetails_Display_GUI*& PropertyDataPropertyDetails_Display_GUI,
            MeasurementTechniqueDetails_Display_GUI*& PropertyDataMeasurementTechniqueDetails_Display_GUI, 
            DataSourceDetails_Display_GUI*& PropertyDataDataSourceDetails_Display_GUI,
            SpecimenDetails_Display_GUI*& PropertyDataSpecimenDetails_Display_GUI,
            TestConditionDetails_Display_GUI*& PropertyTestConditionDetails_Display_GUI
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( PropertyData* element, const ::boost::shared_ptr<MatML_Doc> doc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            PropertyData& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnPropertyDataPropertiesChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataTechniqueChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataSourceChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataSpecimenChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataTestChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataDelimiterTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPropertyDataQuoteTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertData(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertUncertainty(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertQualifier(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertParameterValue(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParameterValue(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUncertainty(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteUncertainty(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteParameterValue(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }

    private:
    };

  class PropertyData_GUI : public PropertyData_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        PropertyData_GUI();
        PropertyData_GUI(wxWindow* parent);

        virtual ~PropertyData_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnPropertyDataPropertiesChoice(wxCommandEvent& event);
        void OnPropertyDataTechniqueChoice(wxCommandEvent& event);
        void OnPropertyDataSourceChoice(wxCommandEvent& event);
        void OnPropertyDataSpecimenChoice(wxCommandEvent& event);
        void OnPropertyDataTestChoice(wxCommandEvent& event);
        void OnPropertyDataDelimiterTextCtrl(wxCommandEvent& event);
        void OnPropertyDataQuoteTextCtrl(wxCommandEvent& event);

        void OnInsertData(wxCommandEvent& event);
        void OnInsertUncertainty(wxCommandEvent& event);
        void OnInsertQualifier(wxCommandEvent& event);
        void OnInsertParameterValue(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteParameterValue(wxCommandEvent& event);
        void OnDeleteQualifier(wxCommandEvent& event);
        void OnDeleteUncertainty(wxCommandEvent& event);

        void OnPasteData(wxCommandEvent& event);
        void OnPasteUncertainty(wxCommandEvent& event);
        void OnPasteQualifier(wxCommandEvent& event);
        void OnPasteParameterValue(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

        void OnBumpUp(wxCommandEvent& event);
        void OnBumpDown(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

