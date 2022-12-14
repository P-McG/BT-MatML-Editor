/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Geometry_GUI.h
// Purpose:     Classes of Geometry_GUI Base and Derived.
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

#include <wx/dcsvg.h>
#include <wx/notebook.h>
#include <wx/string.h>

#include <math.h>
#include <string.h>
#include "StringStream.h"

#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class Geometry_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;

        Geometry_GUI_Base();
        Geometry_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent);
        virtual ~Geometry_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Geometry* element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            Geometry& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect() {};
        virtual void OnInsertShape(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertDimensions(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertOrientation(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteShape(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteDimensions(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteOrientation(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };


    class Geometry_GUI : public Geometry_GUI_Base
    {
    public:
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Geometry_GUI();
        Geometry_GUI(wxWindow* parent);

        virtual ~Geometry_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertShape(wxCommandEvent& event);
        void OnInsertDimensions(wxCommandEvent& event);
        void OnInsertOrientation(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteShape(wxCommandEvent& event);
        void OnPasteDimensions(wxCommandEvent& event);
        void OnPasteOrientation(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
#pragma once
