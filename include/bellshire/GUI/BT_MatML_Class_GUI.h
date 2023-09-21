/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Class_GUI.h
// Purpose:     Classes of Class_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Class.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Class_GUI_Base : public MatML_GUI_Base, public Class_Base
    {
    private:

    public:

        Class_GUI_Base();
        Class_GUI_Base(wxWindow* parent);
        virtual ~Class_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateClassPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<Class> element);

        void Update( const observer_ptr<Class> element);

        void SetConnect() {};
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertParentMaterial(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertParentSubClass(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParentMaterial(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParentSubClass(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteParentMaterial(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteParentSubClass(wxCommandEvent& event){ event.Skip(); }

        virtual void OnBumpUp(wxCommandEvent& event){ event.Skip(); }
        virtual void OnBumpDown(wxCommandEvent& event){ event.Skip(); }

    private:
    };

   class Class_GUI : public Class_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Class_GUI();
        Class_GUI(wxWindow* parent);

        virtual ~Class_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertParentMaterial(wxCommandEvent& event);
        void OnInsertParentSubClass(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteParentMaterial(wxCommandEvent& event);
        void OnDeleteParentSubClass(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteParentMaterial(wxCommandEvent& event);
        void OnPasteParentSubClass(wxCommandEvent& event);

        void OnBumpUp(wxCommandEvent& event);
        void OnBumpDown(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
