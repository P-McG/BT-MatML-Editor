/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Subclass_GUI.h
// Purpose:     Classes of Subclass_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Subclass.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {
    /// <summary>
    /// In Subclass is used MatML's BulkDetails class.
    /// </summary>
    class Subclass_GUI_Base : public MatML_GUI_Base, public Subclass_Base
    {
    protected:

    public:
        Subclass_GUI_Base();
        Subclass_GUI_Base(wxWindow* parent);
        virtual ~Subclass_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateSubclassPanel(wxWindow* parent);

        static wxString GetTreeLabel(const observer_ptr<Subclass> element);
 
        void Update( const observer_ptr<Subclass> element);

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

    class Subclass_GUI : public Subclass_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Subclass_GUI();
        Subclass_GUI(wxWindow* parent);

        virtual ~Subclass_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base Subclass functions
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
