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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Value.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

#include "bellshire/GUI/BT_MatML_StringValidator.h"



namespace bellshire::GUI {

    class Value_GUI_Base : public MatML_GUI_Base, public Value_Base
    {
    protected:
        wxTextCtrl* m_TextCtrl;
        wxChoice* m_FormatChoice;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

    public:
        Value_GUI_Base();//ctor
        Value_GUI_Base(wxWindow* parent);//ctor
        virtual ~Value_GUI_Base();//dtor

        wxTextCtrl* GetTextCtrl();
        wxChoice* GetFormatChoice();
        wxButton* GetValidationButton();
        wxCheckBox* GetValidationNewLineRemovalCheckBox();

        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& TextCtrl,
            wxChoice*& FormatChoice,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );
        static wxWindow* CreateValuePanel(wxWindow* parent,
            wxTextCtrl*& ValueTextCtrl,
            wxChoice*& FormatChoice,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Update( const observer_ptr<Value> element);
        static wxString GetTreeLabel(const observer_ptr<Value> element);

        void SetConnect();
        virtual void OnTextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnFormatChoiceKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }
    };

    class Value_GUI : public Value_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Value_GUI();
        Value_GUI(wxWindow* parent);

        virtual ~Value_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
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

