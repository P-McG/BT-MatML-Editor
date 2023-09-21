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


// For compilers that support pre-compilation, includes "wx/wx.h".
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
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Data.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

#include "bellshire/GUI/BT_MatML_StringValidator.h"

namespace bellshire::GUI {

    class Data_GUI_Base : public MatML_GUI_Base, public Data_Base
    {
    protected:
        wxTextCtrl* m_DataTextCtrl;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

    public:
        Data_GUI_Base();
        Data_GUI_Base(wxWindow* parent);

        virtual ~Data_GUI_Base();

        wxTextCtrl* GetDataTextCtrl();
        wxButton* GetValidationButton();
        wxCheckBox* GetValidationNewLineRemovalCheckBox();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& DataTextCtrl,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );
        static wxWindow* CreateDataPanel(wxWindow* parent,
            wxTextCtrl*& DataTextCtrl,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Update( const observer_ptr<Data> element);

        static wxString GetTreeLabel(const observer_ptr<Data> element);

        void SetConnect();
        virtual void OnDataTextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }
    };

   class Data_GUI : public Data_GUI_Base
    {
       class DataTextCtrlValidator;
       DataTextCtrlValidator* m_DataTextCtrlValidator;
    public:
        Data_GUI();
        Data_GUI(wxWindow* parent);

        virtual ~Data_GUI();

        DataTextCtrlValidator* GetDataTextCtrlValidator();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        //Overwrites the base class functions
        void OnDataTextCtrlKillFocus(wxCommandEvent& event);
        void OnValidationButtonButton(wxCommandEvent& event);

        // validator for wxWidget Data1textCtrl
        class DataTextCtrlValidator : public wxValidator, public StringValidator
        {
            TreeCtrlSorted* m_MatMLTreeCtrl;
            wxCheckBox* m_ValidationNewLineRemovalCheckBox;

        public:
            DataTextCtrlValidator(TreeCtrlSorted* MatMLTreeCtrl,
                wxCheckBox* ValidationNewLineRemovalCheckBox
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl),
                m_ValidationNewLineRemovalCheckBox(ValidationNewLineRemovalCheckBox)
            { };

            TreeCtrlSorted* GetMatMLTreeCtrl();
            wxCheckBox* GetValidationNewLineRemovalCheckBox();

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
        };
    };

}; //namespace bellshire end
