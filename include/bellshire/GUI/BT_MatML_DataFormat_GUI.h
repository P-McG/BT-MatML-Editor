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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_DataFormat.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class DataFormat_GUI_Base : public MatML_GUI_Base, public DataFormat_Base
    {
    protected:

    public:

        DataFormat_GUI_Base();
        DataFormat_GUI_Base(wxWindow* parent);
        virtual ~DataFormat_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateDataFormatPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<DataFormat> element);

        void Update( const observer_ptr<DataFormat> element);

        void SetConnect();
    };

    class DataFormat_GUI : public DataFormat_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        DataFormat_GUI();
        DataFormat_GUI(wxWindow* parent);

        virtual ~DataFormat_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
    };

}; //namespace bellshire end
