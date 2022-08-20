/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Value_GUI.h
// Purpose:     Classes of Value_GUI Base and Derived.
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
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

#include "BT_MatML_StringValidator.h"



namespace bellshire {

    class Value_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI; 
        wxTextCtrl* m_TextCtrl;
        wxChoice* m_FormatChoice;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

        Value_GUI_Base();//ctor
        Value_GUI_Base(wxWindow* parent);//ctor

        virtual ~Value_GUI_Base();//dtor

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& TextCtrl,
            wxChoice*& FormatChoice,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Value* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Value& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnTextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnFormatChoiceKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Value_GUI : public Value_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Value_GUI();
        Value_GUI(wxWindow* parent);

        virtual ~Value_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        //Overwrites the base class functions
        void OnTextCtrlKillFocus(wxCommandEvent& event);
        void OnFormatChoiceKillFocus(wxCommandEvent& event);
        void OnValidationButtonButton(wxCommandEvent& event);

        // validator for wxWidget Data1textCtrl
        class TextCtrlValidator : public wxValidator, public StringValidator
        {
        public:
            TreeCtrlSorted* m_MatMLTreeCtrl;
            wxCheckBox* m_ValidationNewLineRemovalCheckBox;

            TextCtrlValidator(TreeCtrlSorted* MatMLTreeCtrl,
                wxCheckBox* ValidationNewLineRemovalCheckBox
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl),
                m_ValidationNewLineRemovalCheckBox(ValidationNewLineRemovalCheckBox)
            { };

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new TextCtrlValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;

        private:

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
        TextCtrlValidator* m_TextCtrlValidator;
        FormatChoiceValidator* m_FormatChoiceValidator;
    };

}; //namespace bellshire end

