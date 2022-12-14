/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Intro_GUI.h
// Purpose:     Classes of Intro_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/shared_ptr.hpp>

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statbmp.h>

#include <math.h>
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    /// Intro_GUI_Base
    /// Base Gui class for MatML data Intro.
    /// <summary>
    /// - Creates the Gui, 
    /// - Update the Gui
    /// </summary>
    class Intro_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxStaticBitmap* m_logobitmap;

        Intro_GUI_Base();
        Intro_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxStaticBitmap* logobitmap);
        virtual ~Intro_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };
        void Update();

    private:
    };

    /// Intro_GUI
    ///  Gui class for MatML data Intro.
    /// <summary>
    /// - Over rides the Event Handler Functions
    /// - Gathers, and stores member variables, which are required for the Event Handler Functions
    /// </summary>
    class Intro_GUI : public Intro_GUI_Base
    {
    public:

        Intro_GUI();
        Intro_GUI(wxWindow* parent);

        virtual ~Intro_GUI();

    private:
    };

}; //namespace bellshire end
