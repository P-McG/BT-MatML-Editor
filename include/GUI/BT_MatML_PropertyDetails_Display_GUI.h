/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_PropertyDetails_GUI.h
// Purpose:     Classes of PropertyDetails_GUI Base and Derived.
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
#include <wx/grid.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include <list>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"


namespace bellshire {

    //Utility for std:string and wxString
#define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
#define _wx2std(var) std::string(var.mb_str())


    class PropertyDetails_Display_GUI
    {
    public:
        wxPanel* m_GUI;
        wxTextCtrl* m_PropertyDetailsNameTextCtrl;
        wxTextCtrl* m_PropertyDetailsUnitsTextCtrl;
        wxTextCtrl* m_PropertyDetailsNotesTextCtrl;

        PropertyDetails_Display_GUI();
        PropertyDetails_Display_GUI(wxNotebook* parent);

        virtual ~PropertyDetails_Display_GUI();

        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& PropertyDetailsNameTextCtrl,
            wxTextCtrl*& PropertyDetailsUnitsTextCtrl,
            wxTextCtrl*& PropertyDetailsNotesTextCtrl
        );

        void Update( PropertyData* element);
    private:
    };

}; //namespace bellshire end

