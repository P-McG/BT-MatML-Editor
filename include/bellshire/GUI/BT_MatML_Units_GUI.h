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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"

#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include <wx/statline.h>

//#include <boost/shared_ptr.hpp>
#include <math.h>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"
#include "bellshire/Lib/matml31_lib.hxx"

#include "bellshire/BT_MatML_Units.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"

#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"




//
//#include "bellshire/BT_MatML_GUI.h"
//#include "bellshire/BT_MatML_MatMLTreeItemData.h"
//#include "bellshire/BT_MatML_TreeCtrlSorted.h"
//#include "bellshire/BT_MatML_MatMLDropSource.h"
//#include "bellshire/BT_MatML_MatMLDataObject.h"
//#include "bellshire/BT_MatML_MatMLDropTarget.h"
//#include "bellshire/BT_MatML_MatML_Lib.h"



namespace bellshire::GUI {

    class Units_GUI_Base : public MatML_GUI_Base, public MatML_GUI_Lib, public Units_Base
    {
    protected:
        wxTextCtrl* m_UnitsSystemTextCtrl;
        wxTextCtrl* m_UnitsFactorTextCtrl;
        wxTextCtrl* m_UnitsNameTextCtrl;
        wxTextCtrl* m_UnitsDescriptionTextCtrl;
        MatMLLibDropTarget* m_droptarget;

    public:
        Units_GUI_Base();
        Units_GUI_Base(wxWindow* parent);
        virtual ~Units_GUI_Base();

        wxTextCtrl* GetUnitsSystemTextCtrl();
        wxTextCtrl* GetUnitsFactorTextCtrl();
        wxTextCtrl* GetUnitsNameTextCtrl();
        wxTextCtrl* GetUnitsDescriptionTextCtrl();
        MatMLLibDropTarget* GetDropTarget();

        static wxNotebook* Create(wxWindow* parent,
            wxTextCtrl*& UnitsSystemTextCtrl,
            wxTextCtrl*& UnitsFactorTextCtrl,
            wxTextCtrl*& UnitsNameTextCtrl,
            wxTextCtrl*& UnitsDescriptionTextCtrl,
            TreeCtrlSorted*& MatMLLibTreeCtrl,
            observer_ptr<Lib::Units_lib> lib_element,
            MatMLLibDropTarget* droptarget
        );

        static wxWindow* CreateUnitsPanel(wxWindow* parent,
            wxTextCtrl*& UnitsSystemTextCtrl,
            wxTextCtrl*& UnitsFactorTextCtrl,
            wxTextCtrl*& UnitsNameTextCtrl,
            wxTextCtrl*& UnitsDescriptionTextCtrl
        );

        void Update( const observer_ptr<Units> element);
        static wxString GetTreeLabel(const observer_ptr<Units> element);
 
        void SetConnect();
        virtual void OnUnitsNotebook(wxNotebookEvent& event) { event.Skip(); }
        virtual void OnUnitsSystemTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsFactorTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsNameTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnUnitsDescriptionTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertUnit(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteUnit(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteUnit(wxCommandEvent& event){ event.Skip(); }

 

    private:
    public:
        bool operator==(const Units_GUI_Base& other) const;
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

        //void OnLeftDown(wxTreeEvent& event);

    private:
    };

#include "bellshire/GUI/BT_MatML_Units_GUI.inl"

}; //namespace bellshire end

