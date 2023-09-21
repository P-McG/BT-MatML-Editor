/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ParameterDetails_Display_GUI.h
// Purpose:     Classes of ParameterDetails_Display_GUI Base and Derived.
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
    class ParameterDetails_Display_GUI
    {
        wxPanel* m_GUI;
        wxTextCtrl* m_ParameterDetailsNameTextCtrl;
        wxTextCtrl* m_ParameterDetailsNotesTextCtrl;

    public:
        ParameterDetails_Display_GUI();
        ParameterDetails_Display_GUI(wxNotebook* parent);

        virtual ~ParameterDetails_Display_GUI();

        wxPanel* GetGUI();
        wxTextCtrl* GetParameterDetailsNameTextCtrl();
        wxTextCtrl* GetParameterDetailsNotesTextCtrl();
        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& ParameterDetailsNameTextCtrl,
            wxTextCtrl*& ParameterDetailsNotesTextCtrl
        );

        void Update( const observer_ptr<ParameterValue> element);
    };

}; //namespace bellshire end

