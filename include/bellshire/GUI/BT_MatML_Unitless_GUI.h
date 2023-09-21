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
#include "bellshire/BT_MatML_Unitless.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Unitless_GUI_Base : public MatML_GUI_Base, public Unitless_Base
    {
    public:
        Unitless_GUI_Base();
        Unitless_GUI_Base(wxWindow* parent);
        virtual ~Unitless_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateUnitlessPanel(wxWindow* parent);

        void Update( const observer_ptr<Unitless> element);

        static wxString GetTreeLabel(const observer_ptr<Unitless> element);
 
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

