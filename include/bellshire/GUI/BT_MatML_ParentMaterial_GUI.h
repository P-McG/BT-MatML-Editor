/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ParentMaterial_GUI.h
// Purpose:     Classes of ParentMaterial_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include "wx/combobox.h"
#include "wx/textctrl.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ParentMaterial.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/utilities/BT_MatML_Utilities_GUI.h"

namespace bellshire::GUI {

    class ParentMaterial_GUI_Base : public MatML_GUI_Base, public ParentMaterial_Base
    {
    protected:
        wxChoice* m_ParentMaterialIDChoice;
        wxComboBox* m_ParentMaterialFirstClassFilterComboBox;
        wxComboBox* m_ParentMaterialSecondClassFilterComboBox;
        wxComboBox* m_ParentMaterialThirdClassFilterComboBox;
        wxComboBox* m_ParentMaterialFourthClassFilterComboBox;
        wxComboBox* m_ParentMaterialFifthClassFilterComboBox;

    public:
        ParentMaterial_GUI_Base();
        ParentMaterial_GUI_Base(wxWindow* parent);

        virtual ~ParentMaterial_GUI_Base();

        wxChoice* GetParentMaterialIDChoice();
        wxComboBox* GetParentMaterialFirstClassFilterComboBox();
        wxComboBox* GetParentMaterialSecondClassFilterComboBox();
        wxComboBox* GetParentMaterialThirdClassFilterComboBox();
        wxComboBox* GetParentMaterialFourthClassFilterComboBox();
        wxComboBox* GetParentMaterialFifthClassFilterComboBox();

        static wxNotebook* Create(wxWindow* parent, 
            wxChoice*& ParentMaterialIDChoice, 
            wxComboBox*& ParentMaterialFirstClassFilterComboBox, 
            wxComboBox*& ParentMaterialSecondClassFilterComboBox, 
            wxComboBox*& ParentMaterialThirdClassFilterComboBox, 
            wxComboBox*& ParentMaterialFourthClassFilterComboBox,
            wxComboBox*& ParentMaterialFifthClassFilterComboBox
        );
        static wxWindow* CreateParentMaterialPanel(wxWindow* parent,
            wxChoice*& ParentMaterialIDChoice,
            wxComboBox*& ParentMaterialFirstClassFilterComboBox,
            wxComboBox*& ParentMaterialSecondClassFilterComboBox,
            wxComboBox*& ParentMaterialThirdClassFilterComboBox,
            wxComboBox*& ParentMaterialFourthClassFilterComboBox,
            wxComboBox*& ParentMaterialFifthClassFilterComboBox
        );

        static wxString GetTreeLabel(const observer_ptr<ParentMaterial> element);

        void Update( const observer_ptr<ParentMaterial> element, const observer_ptr<MatML_Doc> doc);
        void UpdateFiltersIDChoiceChoices(observer_ptr<MatML_Doc> matml_doc);
        void UpdateFilterComboBox(observer_ptr<MatML_Doc> matml_doc);
        void UpdateIDChoiceChoices(observer_ptr<MatML_Doc> matml_doc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        void FilterComboBoxClear();

        void SetConnect();
        virtual void OnParentMaterialIDChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnParentMaterialClassFilterComboBox(wxCommandEvent& event) { event.Skip(); }

        xml_schema::idrefs GetMaterialIDRefs(std::shared_ptr<MatML_Doc> MatMLDoc, std::list<xml_schema::string> ClassFilters);
        std::list<xml_schema::string>wx2std(const wxArrayString& wxstr);
        wxArrayString std2wx(const std::list<xml_schema::string>& stdstr);
        bool InFilter(Material* material, xml_schema::string* Filter);
        bool InFilter(Material* material, std::list<xml_schema::string> Filter);

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    };

  class ParentMaterial_GUI : public ParentMaterial_GUI_Base
    {
        
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        observer_ptr<MatML_Doc> m_MatMLDoc;//Required before Event Handling.

    public:
        ParentMaterial_GUI();
        ParentMaterial_GUI(wxWindow* parent);

        virtual ~ParentMaterial_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        observer_ptr<MatML_Doc> GetMatMLDoc();//Required before Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(const observer_ptr<MatML_Doc>& matml_doc);

        //Overwrites the base class functions
        void OnParentMaterialIDChoice(wxCommandEvent& event);
        void OnParentMaterialClassFilterComboBox(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    };
}; //namespace bellshire end
