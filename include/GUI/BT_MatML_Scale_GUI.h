/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Scale_GUI.h
// Purpose:     Classes of Scale_GUI Base and Derived.
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
#include <wx/checkbox.h>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

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

    class Scale_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxChoice* m_ScaleChoice;

        Scale_GUI_Base();//ctor
        Scale_GUI_Base(wxWindow* parent);//ctor
        virtual ~Scale_GUI_Base();//dtor

        static wxNotebook* Create(wxWindow* parent,
            wxChoice*& ScaleChoice
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Scale* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Scale& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnScaleChoiceKillFocus(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class Scale_GUI : public Scale_GUI_Base
    {
    public:

        Scale_GUI();//ctor
        Scale_GUI(wxWindow* parent);//ctor

        virtual ~Scale_GUI();//dtor

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        // Overwrites the base class functions
        void OnScaleChoiceKillFocus(wxCommandEvent& event);

        // validator for wxWidget ScaletextCtrl
        class ScaleChoiceValidator : public wxValidator
        {
        public:
            TreeCtrlSorted* m_MatMLTreeCtrl;

            ScaleChoiceValidator(TreeCtrlSorted* MatMLTreeCtrl
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl)
            { };

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new ScaleChoiceValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;

        private:

        };

    private:
        ScaleChoiceValidator* m_ScaleChoiceValidator;

    };

}; //namespace bellshire end

