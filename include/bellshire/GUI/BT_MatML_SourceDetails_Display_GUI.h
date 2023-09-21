/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_SourceDetails_Display_GUI.h
// Purpose:     Classes of SourceDetails_Display_GUI Base and Derived.
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
#include <wx/grid.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include <list>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"


namespace bellshire::GUI {

    class SourceDetails_Display_GUI
    {
        wxPanel* m_GUI;
        wxTextCtrl* m_SourceDetailsNameTextCtrl;
        wxTextCtrl* m_SourceDetailsNotesTextCtrl;

    public:
        SourceDetails_Display_GUI();
        SourceDetails_Display_GUI(wxNotebook* parent);

        virtual ~SourceDetails_Display_GUI();

        wxPanel* GetGUI();
        wxTextCtrl* GetSourceDetailsNameTextCtrl();
        wxTextCtrl* GetSourceDetailsNotesTextCtrl();
        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& SourceDetailsNameTextCtrl,
            wxTextCtrl*& SourceDetailsNotesTextCtrl
        );

        void Update( const observer_ptr<Source> element);
    };

}; //namespace bellshire end

