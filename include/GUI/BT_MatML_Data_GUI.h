/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Data_GUI.h
// Purpose:     Classes of Data_GUI Base and Derived.
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
#include <wx/checkbox.h>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

#include "BT_MatML_StringValidator.h"

namespace bellshire {

    class Data_GUI_Base : public MatML_Base_GUI

    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_DataTextCtrl;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

        Data_GUI_Base();
        Data_GUI_Base(wxWindow* parent);

        virtual ~Data_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& DataTextCtrl,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( Data* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            Data& Element,
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnDataTextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class Data_GUI : public Data_GUI_Base
    {
    public:

        //TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Data_GUI();
        Data_GUI(wxWindow* parent);

        virtual ~Data_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        //Overwrites the base class functions
        void OnDataTextCtrlKillFocus(wxCommandEvent& event);
        void OnValidationButtonButton(wxCommandEvent& event);

        // validator for wxWidget Data1textCtrl
        class DataTextCtrlValidator : public wxValidator, public StringValidator
        {
        public:
            TreeCtrlSorted* m_MatMLTreeCtrl;
            wxCheckBox* m_ValidationNewLineRemovalCheckBox;

            DataTextCtrlValidator(TreeCtrlSorted* MatMLTreeCtrl,
                wxCheckBox* ValidationNewLineRemovalCheckBox
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl),
                m_ValidationNewLineRemovalCheckBox(ValidationNewLineRemovalCheckBox)
            { };

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;

            //bool ValidateString(
            //    ::std::string input, 
            //   ::std::string Format="float",
            //    ::std::string Delimiter=",",
            //    bool NewLineRemoval=false, 
            //    ::std::string* msg=nullptr
            //);
           
            virtual wxObject* Clone() const wxOVERRIDE { return new DataTextCtrlValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;

            //template<typename T>
            //bool isValid(const string& num);

        private:

        };


    private:
        DataTextCtrlValidator* m_DataTextCtrlValidator;
    };

}; //namespace bellshire end
