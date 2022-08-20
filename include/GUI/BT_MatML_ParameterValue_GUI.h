/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ParameterValue_GUI.h
// Purpose:     Classes of ParameterValue_GUI Base and Derived.
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
#include "StringStream.h"
#include <boost/shared_ptr.hpp>
#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"
#include "BT_MatML_ID_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"



namespace bellshire {

    class ParameterDetails_Display_GUI;

    class ParameterValue_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxChoice* m_ParameterValueParameterChoice;
        wxChoice* m_ParameterValueFormatChoice;
        ParameterDetails_Display_GUI* m_ParameterValueParameterDetails_Display_GUI;

        ParameterValue_GUI_Base();
        ParameterValue_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, wxChoice*& ParameterValueParameterChoice, wxChoice*& ParameterValueFormatChoice, ParameterDetails_Display_GUI*& ParameterValueParameterDetails_Display_GUI);
        virtual ~ParameterValue_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        wxNotebook* get() { return m_GUI; };

        void Update( ParameterValue* element, const boost::shared_ptr<MatML_Doc> doc);

        static ::std::string Label(::std::string name, ::std::string id);
        static ::std::string LabelToId(::std::string label);

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId, 
            ParameterValue& Element, 
            const wxTreeItemId& PreviousId
        );

        void SetConnect();
        virtual void OnParameterValueParameterChoice(wxCommandEvent& event) { event.Skip(); }
        virtual void OnParameterValueFormatChoice(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertUncertainty(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteUncertainty(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteUncertainty(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteQualifier(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event) { event.Skip(); }

    private:
    };

   class ParameterValue_GUI : public ParameterValue_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        ParameterValue_GUI();
        ParameterValue_GUI(wxWindow* parent);

        virtual ~ParameterValue_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnParameterValueParameterChoice(wxCommandEvent& event);
        void OnParameterValueFormatChoice(wxCommandEvent& event);

        void OnInsertData(wxCommandEvent& event);
        void OnInsertUncertainty(wxCommandEvent& event);
        void OnInsertQualifier(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteQualifier(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);
        void OnDeleteUncertainty(wxCommandEvent& event);

        void OnPasteData(wxCommandEvent& event);
        void OnPasteUncertainty(wxCommandEvent& event);
        void OnPasteQualifier(wxCommandEvent& event);
        void OnPasteNotes(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
