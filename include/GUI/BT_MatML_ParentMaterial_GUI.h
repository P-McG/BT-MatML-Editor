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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include "wx/combobox.h"
#include "wx/textctrl.h"

#include <math.h>
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_Utilities_GUI.h"

namespace bellshire {

    class ParentMaterial_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxChoice* m_ParentMaterialIDChoice;
        wxComboBox* m_ParentMaterialFirstClassFilterComboBox;
        wxComboBox* m_ParentMaterialSecondClassFilterComboBox;
        wxComboBox* m_ParentMaterialThirdClassFilterComboBox;
        wxComboBox* m_ParentMaterialFourthClassFilterComboBox;
        wxComboBox* m_ParentMaterialFifthClassFilterComboBox;
        wxNotebook* m_GUI;

        ParentMaterial_GUI_Base();
        ParentMaterial_GUI_Base(wxWindow* parent);

        virtual ~ParentMaterial_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            wxChoice*& ParentMaterialIDChoice, 
            wxComboBox*& ParentMaterialFirstClassFilterComboBox, 
            wxComboBox*& ParentMaterialSecondClassFilterComboBox, 
            wxComboBox*& ParentMaterialThirdClassFilterComboBox, 
            wxComboBox*& ParentMaterialFourthClassFilterComboBox,
            wxComboBox*& ParentMaterialFifthClassFilterComboBox
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() {return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            ParentMaterial& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( ParentMaterial* element, const ::boost::shared_ptr<MatML_Doc> doc);
        void UpdateFiltersIDChoiceChoices(::boost::shared_ptr<MatML_Doc> MatMLDoc);
        void UpdateFilterComboBox(::boost::shared_ptr<MatML_Doc> MatMLDoc);
        void UpdateIDChoiceChoices(::boost::shared_ptr<MatML_Doc> MatMLDoc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        void FilterComboBoxClear();

        void SetConnect();
        virtual void OnParentMaterialIDChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnParentMaterialClassFilterComboBox(wxCommandEvent& event) { event.Skip(); }

        xml_schema::idrefs GetMaterialIDRefs(::boost::shared_ptr<MatML_Doc> MatMLDoc, std::list<xml_schema::string> ClassFilters);
        std::list<xml_schema::string>wx2std(const wxArrayString& wxstr);
        wxArrayString std2wx(const std::list<xml_schema::string>& stdstr);
        bool InFilter(Material* material, xml_schema::string* Filter);
        bool InFilter(Material* material, std::list<xml_schema::string> Filter);


    private:

    };

  class ParentMaterial_GUI : public ParentMaterial_GUI_Base
    {
    public:
        //Required before Event Handling.
        TreeCtrlSorted* m_MatMLTreeCtrl;
        ::boost::shared_ptr<MatML_Doc> m_MatMLDoc;

        ParentMaterial_GUI();
        ParentMaterial_GUI(wxWindow* parent);

        virtual ~ParentMaterial_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc);

        //Overwrites the base class functions
        void OnParentMaterialIDChoice(wxCommandEvent& event);
        void OnParentMaterialClassFilterComboBox(wxCommandEvent& event);

    private:

    };
}; //namespace bellshire end
