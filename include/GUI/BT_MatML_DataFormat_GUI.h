/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_DataFormat_GUI.h
// Purpose:     Classes of DataFormat_GUI Base and Derived.
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

#include <math.h>
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    //Utility for std:string and wxString
#define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
#define _wx2std(var) std::string(var.mb_str())

    class DataFormat_GUI
    {
    public:
        wxNotebook* m_GUI;

        DataFormat_GUI();
        DataFormat_GUI(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~DataFormat_GUI();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            DataFormat& Element, 
            const wxTreeItemId& PreviousId
        );
        void Update( DataFormat* element);
    private:
    };


}; //namespace bellshire end
