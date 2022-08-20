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

#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    /// MatML_Doc_GUI_Base
    /// Base Gui class for MatML data MatML_Doc.
    /// <summary>
    /// - Creates the Gui, 
    /// - Update the Gui,
    /// - Sets up the MatML wxTreeCtrl
    /// - Connects Event Handler Functions 
    /// </summary>
    class MatML_Doc_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        MatML_Doc_GUI_Base();
        MatML_Doc_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~MatML_Doc_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };
        static void SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            MatML_Doc& Element
        );
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
    public:
        //Required before Event Handling.
        TreeCtrlSorted* m_MatMLTreeCtrl;
        ::boost::shared_ptr<MatML_Doc> m_MatMLDoc;

        MatML_Doc_GUI();
        MatML_Doc_GUI(wxWindow* parent);

        virtual ~MatML_Doc_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc);

        //Overwrites the base class functions
        void OnDeleteMaterial(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
