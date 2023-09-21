/////////////////////////////////////////////////////////////////////////////
// Name:       BT_MatML_Form_GUI.h
// Purpose:     Classes of Form_GUI Base and Derived.
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

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "bellshire/utilities/StringStream.h"

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Form.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class Form_GUI_Base : public MatML_GUI_Base, public Form_Base
    {
    protected:

    public:
        Form_GUI_Base();
        Form_GUI_Base(wxWindow* parent);
        virtual ~Form_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateFormPanel(wxWindow* parent);

        void Update( const observer_ptr<Form> element);
        static wxString GetTreeLabel(const observer_ptr<Form> element);

        void SetConnect() {};
        virtual void OnInsertDescription(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertGeometry(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteGeometry(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteDescription(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteGeometry(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }
    };

    class Form_GUI : public Form_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Form_GUI();
        Form_GUI(wxWindow* parent);

        virtual ~Form_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertDescription(wxCommandEvent& event);
        void OnInsertGeometry(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteGeometry(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteDescription(wxCommandEvent& event);
        void OnPasteGeometry(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    };


}; //namespace bellshire end
#pragma once
