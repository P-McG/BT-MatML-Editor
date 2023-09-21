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
#include "bellshire/BT_MatML_Geometry.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Geometry_GUI_Base : public MatML_GUI_Base, public Geometry_Base
    {
    protected:

    public:
        Geometry_GUI_Base();
        Geometry_GUI_Base(wxWindow* parent);
        virtual ~Geometry_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateGeometryPanel(wxWindow* parent);

        void Update( const observer_ptr<Geometry> element);

        static wxString GetTreeLabel(const observer_ptr<Geometry> element);

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
    };


    class Geometry_GUI : public Geometry_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Geometry_GUI();
        Geometry_GUI(wxWindow* parent);

        virtual ~Geometry_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

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
    };

}; //namespace bellshire end
#pragma once
