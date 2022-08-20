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

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"

namespace bellshire {

    class SourceDetails_Display_GUI;

    class Source_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxChoice* m_SourceChoice;
        SourceDetails_Display_GUI* m_SourceSourceDetails_Display_GUI;

        Source_GUI_Base();
        Source_GUI_Base(wxWindow* parent);

        virtual ~Source_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, 
            wxChoice*& SourceChoice, 
            SourceDetails_Display_GUI*& m_SourceSourceDetails_Display_GUI
        );

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Source* element, const ::boost::shared_ptr<MatML_Doc> doc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Source& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnSourceChoice(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class Source_GUI : public Source_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.

        Source_GUI();
        Source_GUI(wxWindow* parent);

        virtual ~Source_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);

        //Overwrites the base class functions
        void OnSourceChoice(wxCommandEvent& event);


    private:
    };

}; //namespace bellshire end

