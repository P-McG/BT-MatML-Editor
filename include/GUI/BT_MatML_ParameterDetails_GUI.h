/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ParameterDetails_GUI.h
// Purpose:     Classes of ParameterDetails_GUI Base and Derived.
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
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ID_GUI;

    class ParameterDetails_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI; 
        ID_GUI* m_ParameterDetails_ID_GUI;

        ParameterDetails_GUI_Base();
        ParameterDetails_GUI_Base(wxWindow* parent);

        virtual ~ParameterDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& ParameterDetails_ID_GUI
        );



        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( ParameterDetails* element);

        static ::std::string Label(::std::string name, ::std::string id);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            ParameterDetails& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertUnits(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertUnitless(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUnitless(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUnits(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUnits(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteUnitless(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

    private:
    };


    class ParameterDetails_GUI : public ParameterDetails_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        ParameterDetails_GUI();
        ParameterDetails_GUI(wxWindow* parent);

        virtual ~ParameterDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertUnits(wxCommandEvent& event);
        void OnInsertUnitless(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteUnitless(wxCommandEvent& event);
        void OnDeleteUnits(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteUnits(wxCommandEvent& event);
        void OnPasteUnitless(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };


}; //namespace bellshire end
