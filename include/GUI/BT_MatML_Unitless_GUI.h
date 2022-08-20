/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Unitless_GUI.h
// Purpose:     Classes of Unitless_GUI Base and Derived.
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

namespace bellshire {

    class Unitless_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Unitless_GUI_Base();
        Unitless_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~Unitless_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Unitless* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Unitless& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};
    private:
    };

    class Unitless_GUI : public Unitless_GUI_Base
    {
    public:

        Unitless_GUI();
        Unitless_GUI(wxWindow* parent);

        virtual ~Unitless_GUI();

        void SetEvtHandlerVar() {};
    private:
    };

}; //namespace bellshire end

