/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Glossary_GUI.h
// Purpose:     Classes of Glossary_GUI Base and Derived.
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
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_Glossary.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class Glossary_GUI_Base : public MatML_GUI_Base, public Glossary_Base
    {
    protected:

    public:
        Glossary_GUI_Base();
        Glossary_GUI_Base(wxWindow* parent);
        virtual ~Glossary_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateGlossaryPanel(wxWindow* parent);

        void Update( const observer_ptr<Glossary> element);

        static wxString GetTreeLabel(const observer_ptr<Glossary> element);

        void SetConnect() {};
        virtual void OnInsertTerm(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteGlossaryTerm(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteTerm(wxCommandEvent& event) { event.Skip(); }
    };


    class Glossary_GUI : public Glossary_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Glossary_GUI();
        Glossary_GUI(wxWindow* parent);

        virtual ~Glossary_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertTerm(wxCommandEvent& event);

        void OnDeleteGlossaryTerm(wxCommandEvent& event);

        void OnPasteTerm(wxCommandEvent& event);
    };

}; //namespace bellshire end
