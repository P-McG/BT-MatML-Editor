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
#include "bellshire/BT_MatML_Scale.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

#include "bellshire/GUI/BT_MatML_StringValidator.h"

namespace bellshire::GUI {

    class Scale_GUI_Base : public MatML_GUI_Base, public Scale_Base
    {
    protected:
        wxChoice* m_ScaleChoice;

    public:
        Scale_GUI_Base();//ctor
        Scale_GUI_Base(wxWindow* parent);//ctor
        virtual ~Scale_GUI_Base();//dtor

        wxChoice* GetScaleChoice();

        static wxNotebook* Create(wxWindow* parent,
            wxChoice*& ScaleChoice
        );
        static wxWindow* CreateScalePanel(wxWindow* parent,
            wxChoice*& ScaleChoice
        );

        void Update( const observer_ptr<Scale> element);

        static wxString GetTreeLabel(const observer_ptr<Scale> element);

        void SetConnect();
        virtual void OnScaleChoiceKillFocus(wxCommandEvent& event) { event.Skip(); }
    };

    class Scale_GUI : public Scale_GUI_Base
    {
    public:
        class ScaleChoiceValidator;
    private:
        ScaleChoiceValidator* m_ScaleChoiceValidator;
    public:

        Scale_GUI();//ctor
        Scale_GUI(wxWindow* parent);//ctor

        virtual ~Scale_GUI();//dtor

        ScaleChoiceValidator* GetScaleChoiceValidator();
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.

        // Overwrites the base class functions
        void OnScaleChoiceKillFocus(wxCommandEvent& event);

        // validator for wxWidget ScaletextCtrl
        class ScaleChoiceValidator : public wxValidator
        {
            TreeCtrlSorted* m_MatMLTreeCtrl;

        public:
            ScaleChoiceValidator(TreeCtrlSorted* MatMLTreeCtrl
            ) : m_MatMLTreeCtrl(MatMLTreeCtrl)
            { };

            TreeCtrlSorted* GetMatMLTreeCtrl();

            virtual bool Validate(wxWindow* parent) wxOVERRIDE;
            virtual wxObject* Clone() const wxOVERRIDE { return new ScaleChoiceValidator(*this); }

            // Called to transfer data to the window
            virtual bool TransferToWindow() wxOVERRIDE;

            // Called to transfer data from the window
            virtual bool TransferFromWindow() wxOVERRIDE;
        };
    };

}; //namespace bellshire end

