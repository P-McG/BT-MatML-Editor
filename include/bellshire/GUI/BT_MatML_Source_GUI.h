/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Source_GUI.h
// Purpose:     Classes of Source_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Source.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"

namespace bellshire::GUI {

    class SourceDetails_Display_GUI;

    class Source_GUI_Base : public MatML_GUI_Base, public Source_Base
    {
    protected:
        wxChoice* m_SourceChoice;
        SourceDetails_Display_GUI* m_SourceSourceDetails_Display_GUI;

    public:
        Source_GUI_Base();
        Source_GUI_Base(wxWindow* parent);

        virtual ~Source_GUI_Base();

        wxChoice* GetSourceChoice();
        SourceDetails_Display_GUI* GetSourceSourceDetails_Display_GUI();

        static wxNotebook* Create(wxWindow* parent, 
            wxChoice*& SourceChoice, 
            SourceDetails_Display_GUI*& m_SourceSourceDetails_Display_GUI
        );
        static wxWindow* CreateSourcePanel(wxWindow* parent,
            wxChoice*& SourceChoice,
            SourceDetails_Display_GUI*& SourceSourceDetails_Display_GUI
        );

        void Update( const observer_ptr<Source> element, const observer_ptr<MatML_Doc> doc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);
        static wxString GetTreeLabel(const observer_ptr<Source> element);

        void SetConnect();
        virtual void OnSourceChoice(wxCommandEvent& event) { event.Skip(); }
    };

   class Source_GUI : public Source_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

    public:
        Source_GUI();
        Source_GUI(wxWindow* parent);

        virtual ~Source_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnSourceChoice(wxCommandEvent& event);

    };

}; //namespace bellshire end

