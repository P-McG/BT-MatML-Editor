/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Units_GUI.h
// Purpose:     Classes of Units_GUI Base and Derived.
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
#include "BT_MatML_MatMLDropSource.h"
#include "BT_MatML_MatMLDataObject.h"



namespace bellshire {

    class Units_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        wxTextCtrl* m_UnitsSystemTextCtrl;
        wxTextCtrl* m_UnitsFactorTextCtrl;
        wxTextCtrl* m_UnitsNameTextCtrl;
        wxButton* m_AutoInsertBaseUnitsButton;
        wxTextCtrl* m_UnitsDescriptionTextCtrl;
        TreeCtrlSorted* m_MatMLLibTreeCtrl;

        Default<Units>* m_test_units;

        wxDataFormat* m_dataformat;
        DnDMatMLDataObject* m_dropdata;
        MatMLDropSource* m_dragSource;
        DnDMatMLData* m_dndmatmldata;
        DnDMatMLDataObject* m_matmldata;

        Units_GUI_Base();
        Units_GUI_Base(wxWindow* parent);
        static wxNotebook* Create(wxWindow* parent, 
            wxTextCtrl*& UnitsSystemTextCtrl,
            wxTextCtrl*& UnitsFactorTextCtrl, 
            wxTextCtrl*& UnitsNameTextCtrl, 
            wxTextCtrl*& UnitsDescriptionTextCtrl,
            TreeCtrlSorted*& MatMLLibTreeCtrl,
            Default<Units>* test_units
        );
        virtual ~Units_GUI_Base();

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); };
        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void Update( Units* element);
        static wxString GetTreeLabel(Units& Element);
        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl, 
            const wxTreeItemId& ParentId, 
            Units& Element,
            const wxTreeItemId& PreviousId,
            bool Recursive=true,
            bool ChildRecursive=true
        );

        void SetConnect();
        virtual void OnUnitsNotebook(wxNotebookEvent& event) { event.Skip(); }
        virtual void OnUnitsSystemTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsFactorTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsNameTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnAutoInsertBaseUnitsButton(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsDescriptionTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertUnit(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteUnit(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteUnit(wxCommandEvent& event){ event.Skip(); }

        virtual void OnLeftDown(wxTreeEvent& event){ event.Skip(); }

 

    private:
    };

    class Units_GUI : public Units_GUI_Base
    {
    public:

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.
        wxTreeItemId m_draggedItem;// item being dragged right now

        Units_GUI();
        Units_GUI(wxWindow* parent);

        virtual ~Units_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnUnitsSystemTextCtrl(wxCommandEvent& event);
        void OnUnitsFactorTextCtrl(wxCommandEvent& event);
        void OnUnitsNameTextCtrl(wxCommandEvent& event);
        void OnUnitsDescriptionTextCtrl(wxCommandEvent& event);

        void OnInsertUnit(wxCommandEvent& event);

        void OnDeleteUnit(wxCommandEvent& event);

        void OnPasteUnit(wxCommandEvent& event);

        void OnLeftDown(wxTreeEvent& event);

    private:
    };

}; //namespace bellshire end

