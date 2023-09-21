/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Qualifier_GUI.h
// Purpose:     Classes of Qualifier_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Qualifier.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Qualifier_GUI_Base : public MatML_GUI_Base, public Qualifier_Base
    {
    protected:
        wxTextCtrl* m_QualifierTextCtrl;
        wxButton* m_ValidationButton;
        wxCheckBox* m_ValidationNewLineRemovalCheckBox;

    public:
        Qualifier_GUI_Base();
        Qualifier_GUI_Base(wxWindow* parent);
        virtual ~Qualifier_GUI_Base();

        wxTextCtrl* GetQualifierTextCtrl();
        wxButton* GetValidationButton();
        wxCheckBox* GetValidationNewLineRemovalCheckBox();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& QualifierTextCtrl,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );
        static wxWindow* CreateQualifierPanel(wxWindow* parent,
            wxTextCtrl*& QualifierTextCtrl,
            wxButton*& ValidationButton,
            wxCheckBox*& ValidationNewLineRemovalCheckBox
        );

        void Update( const observer_ptr<Qualifier> element);

        static wxString GetTreeLabel(const observer_ptr<Qualifier> element);

        void SetConnect();
        virtual void OnQualifierTextCtrlKillFocus(wxCommandEvent& event) { event.Skip(); }
        virtual void OnValidationButtonButton(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

  class Qualifier_GUI : public Qualifier_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Qualifier_GUI();
        Qualifier_GUI(wxWindow* parent);

        virtual ~Qualifier_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnQualifierTextCtrlKillFocus(wxCommandEvent& event);
        void OnValidationButtonButton(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
        // validator for wxWidget Data1textCtrl
        class TextCtrlValidator : public wxValidator, public StringValidator
        {
            TreeCtrlSorted* m_MatMLTreeCtrl;
            wxCheckBox* m_ValidationNewLineRemovalCheckBox;

        public:
            TextCtrlValidator(TreeCtrlSorted* MatMLTreeCtrl,
                wxCheckBox* ValidationNewLineRemovalCheckBox
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl),
                m_ValidationNewLineRemovalCheckBox(ValidationNewLineRemovalCheckBox)
            { };

            TreeCtrlSorted* GetMatMLTreeCtrl();
            wxCheckBox* GetValidationNewLineRemovalCheckBox();

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new TextCtrlValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;


        private:

        };

        TextCtrlValidator* m_TextCtrlValidator;
    };

}; //namespace bellshire end

