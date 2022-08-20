/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_SourceDetails_GUI.h
// Purpose:     Classes of SourceDetails_GUI Base and Derived.
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
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "StringStream.h"
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ID_GUI;

    class SourceDetails_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI; 
        ID_GUI* m_SourceDetails_ID_GUI;
        wxTextCtrl* m_SourceDetailsTypeTextCtrl;

        SourceDetails_GUI_Base();
        SourceDetails_GUI_Base(wxWindow* parent);

        virtual ~SourceDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& SourceDetails_ID_GUI,
            wxTextCtrl*& SourceDetailsTypeTextCtrl
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( SourceDetails* element);

        static ::std::string Label(::std::string name, ::std::string id);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            SourceDetails& Element,
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnSourceDetailsTypeTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };

    class SourceDetails_GUI : public SourceDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        SourceDetails_GUI();
        SourceDetails_GUI(wxWindow* parent);

        virtual ~SourceDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnSourceDetailsTypeTextCtrl(wxCommandEvent& event);

        void OnInsertName(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end

