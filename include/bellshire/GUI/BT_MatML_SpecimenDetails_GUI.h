/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_SpecimenDetails_GUI.h
// Purpose:     Classes of SpecimenDetails_GUI Base and Derived.
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
#include <wx/statline.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_SpecimenDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class ID_GUI;

    class SpecimenDetails_GUI_Base : public MatML_GUI_Base, public SpecimenDetails_Base
    {
    protected:
        ID_GUI* m_SpecimenDetails_ID_GUI;
        wxTextCtrl* m_SpecimenDetailsTypeTextCtrl;

    public:
        SpecimenDetails_GUI_Base();
        SpecimenDetails_GUI_Base(wxWindow* parent);

        virtual ~SpecimenDetails_GUI_Base();

        ID_GUI* GetSpecimenDetails_ID_GUI();
        wxTextCtrl* GetSpecimenDetailsTypeTextCtrl();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& SpecimenDetails_ID_GUI,
            wxTextCtrl*& SpecimenDetailsTypeTextCtrl
        );
        static wxWindow* CreateSpecimenDetailsPanel(wxWindow* parent,
            ID_GUI*& SpecimenDetails_ID_GUI,
            wxTextCtrl*& SpecimenDetailsTypeTextCtrl
        );

        void Update( const observer_ptr<SpecimenDetails> element);

        static ::std::string Label(::std::string name, ::std::string id);
        static wxString GetTreeLabel(const observer_ptr<SpecimenDetails> element);
        
        void SetConnect();
        virtual void OnSpecimenDetailsTypeTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertGeometry(wxCommandEvent& event){ event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteGeometry(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event){event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){event.Skip(); }
        virtual void OnPasteGeometry(wxCommandEvent& event){event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }
    };

    class SpecimenDetails_GUI : public SpecimenDetails_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        SpecimenDetails_GUI();
        SpecimenDetails_GUI(wxWindow* parent);
        virtual ~SpecimenDetails_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnSpecimenDetailsTypeTextCtrl(wxCommandEvent& event);

        void OnInsertName(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);
        void OnInsertGeometry(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteGeometry(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);
        void OnPasteGeometry(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);
    };

}; //namespace bellshire end

