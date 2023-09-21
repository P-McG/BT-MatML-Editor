/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Data1_GUI.h
// Purpose:     Classes of Data1_GUI Base and Derived.
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
#include <wx/statline.h>
#include <wx/checkbox.h>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Data1.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

#include "bellshire/GUI/BT_MatML_StringValidator.h"

namespace bellshire::GUI {

    class Data1_GUI_Base : public MatML_GUI_Base, public Data1_Base
    {
    protected:
        wxTextCtrl* m_Data1TextCtrl;
        wxChoice* m_FormatChoice;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

    public:
        Data1_GUI_Base();//ctor
        Data1_GUI_Base(wxWindow* parent);//ctor
        virtual ~Data1_GUI_Base();//dtor

        wxTextCtrl* GetData1TextCtrl();
        wxChoice* GetFormatChoice();
        wxButton* GetValidationButton();
        wxCheckBox* GetValidationNewLineRemovalCheckBox();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& DataTextCtrl,
            wxChoice*& FormatChoice,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );
        static wxWindow* CreateDataPanel(wxWindow* parent,
            wxTextCtrl*& DataTextCtrl,
            wxChoice*& FormatChoice,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Update( const observer_ptr<Data1> element);

        static wxString GetTreeLabel(const observer_ptr<Data1> element);

        void SetConnect();
        virtual void OnData1TextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnFormatChoiceKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class Data1_GUI : public Data1_GUI_Base
    {
       class Data1TextCtrlValidator;
       class FormatChoiceValidator;

       Data1TextCtrlValidator* m_Data1TextCtrlValidator;
       FormatChoiceValidator* m_FormatChoiceValidator;

    public:
        Data1_GUI();//ctor
        Data1_GUI(wxWindow* parent);//ctor

        virtual ~Data1_GUI();//dtor

        Data1TextCtrlValidator* GetData1TextCtrlValidator();
        FormatChoiceValidator* GetFormatChoiceValidator();
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        // Overwrites the base class functions
        void OnData1TextCtrlKillFocus(wxCommandEvent& event);
        void OnFormatChoiceKillFocus(wxCommandEvent& event);
        void OnValidationButtonButton(wxCommandEvent& event);

        // validator for wxWidget Data1textCtrl
        class Data1TextCtrlValidator : public wxValidator, public StringValidator
        {
            TreeCtrlSorted* m_MatMLTreeCtrl;
            wxCheckBox* m_ValidationNewLineRemovalCheckBox;

        public:
            Data1TextCtrlValidator(TreeCtrlSorted* MatMLTreeCtrl,
                wxCheckBox* ValidationNewLineRemovalCheckBox
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl),
                m_ValidationNewLineRemovalCheckBox(ValidationNewLineRemovalCheckBox)
            { };

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new Data1TextCtrlValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;
           
        };

        // validator for wxWidget FormatChoice
        class FormatChoiceValidator : public wxValidator
        {
        public:
            TreeCtrlSorted* m_MatMLTreeCtrl;

            FormatChoiceValidator(TreeCtrlSorted* MatMLTreeCtrl) { m_MatMLTreeCtrl = MatMLTreeCtrl; }

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new FormatChoiceValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;

        private:

        };

    private:


    };

}; //namespace bellshire end

