/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_MatML_Doc_GUI.h
// Purpose:     Classes of MatML_Doc_GUI Base and Derived.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/shared_ptr.hpp>

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include "wx/window.h"

#include <math.h>
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"

#include "bellshire/BT_MatML_MatML_Doc.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI
{

    /// MatML_Doc_GUI_Base
    /// Base Gui class for MatML data MatML_Doc.
    /// <summary>
    /// - Creates the Gui, 
    /// - Update the Gui,
    /// - Sets up the MatML wxTreeCtrl
    /// - Connects Event Handler Functions 
    /// </summary>
    class MatML_Doc_GUI_Base : public MatML_GUI_Base, public MatML_Doc_Base
    {
    protected:
    public:
        MatML_Doc_GUI_Base();
        MatML_Doc_GUI_Base(wxWindow* parent);
        virtual ~MatML_Doc_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateMatML_DocPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<MatML_Doc> element);

        void Update();

        void SetConnect() {};

        virtual void OnDeleteMaterial(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    /// MatML_Doc_GUI
    ///  Gui class for MatML data MatML_Doc.
    /// <summary>
    /// - Over rides the Event Handler Functions
    /// - Gathers, and stores member variables, which are required for the Event Handler Functions
    /// </summary>
    class MatML_Doc_GUI : public MatML_Doc_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        observer_ptr<MatML_Doc> m_MatMLDoc;//Required before Event Handling.

    public:
        MatML_Doc_GUI();
        MatML_Doc_GUI(wxWindow* parent);

        virtual ~MatML_Doc_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        observer_ptr<MatML_Doc> GetMatMLDoc();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(const observer_ptr<MatML_Doc>& matml_doc);

        //Overwrites the base class functions
        void OnDeleteMaterial(wxCommandEvent& event);
    };

}; //namespace bellshire end
