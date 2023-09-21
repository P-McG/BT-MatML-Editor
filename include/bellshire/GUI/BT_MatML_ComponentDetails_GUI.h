/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_ComponentDetails_GUI.h
// Purpose:     Classes of ComponentDetails_GUI Base and Derived.
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

#include <math.h>

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ComponentDetails.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MatMLDropSource.h"
#include "bellshire/GUI/BT_MatML_MatMLDataObject.h"
#include "bellshire/GUI/BT_MatML_MatMLDropTarget.h"



namespace bellshire::GUI {

    class ID_GUI;

    class ComponentDetails_GUI_Base : public MatML_GUI_Base, public MatML_GUI_Lib, public ComponentDetails_Base
    {
    protected:
        std::unique_ptr<ID_GUI> m_ComponentDetails_ID_GUI;
        MatMLLibDropTarget* m_droptarget;

    public:
        ComponentDetails_GUI_Base();
        ComponentDetails_GUI_Base(wxWindow* parent);
        ComponentDetails_GUI_Base( std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI, MatMLLibDropTarget* droptarget);
        virtual ~ComponentDetails_GUI_Base();

        //ID_GUI* GetComponentDetails_ID_GUI();

        MatMLLibDropTarget* GetDropTarget();

        static wxNotebook* Create(wxWindow* parent, 
            std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI,
            TreeCtrlSorted*& MatMLLibTreeCtrl,
            observer_ptr<xml_schema::element_type> lib_element,
            MatMLLibDropTarget* droptarget
        );
        static wxWindow* CreateComponentDetailsPanel(
            wxWindow* parent,
            std::unique_ptr<ID_GUI>& ComponentDetails_ID_GUI
        );

        void Update( const observer_ptr<ComponentDetails> element);
        static wxString GetTreeLabel(const observer_ptr<ComponentDetails> element);

        void SetConnect();
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertClass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSubclass1(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSpecification(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSource(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertForm(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertProcessingDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertCharacterization(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertPropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertAssociationDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertComponentDetails(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteClass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSubclass1(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteAssociationDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteCharacterization(wxCommandEvent& event) { event.Skip(); }
        //virtual void OnDeleteComponentDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteForm(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteProcessingDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeletePropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSpecification(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSource(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteClass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteSubclass1(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteSpecification(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteSource(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteForm(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteProcessingDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteCharacterization(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPastePropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteAssociationDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteComponentDetails(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpUp(wxCommandEvent& event){ event.Skip(); }
        virtual void OnBumpDown(wxCommandEvent& event){ event.Skip(); }

        bool operator==(const ComponentDetails_GUI_Base& other) const;
    };


    class ComponentDetails_GUI : public ComponentDetails_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        ComponentDetails_GUI();
        ComponentDetails_GUI(wxWindow* parent);
 
        virtual ~ComponentDetails_GUI();
        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.


        //Overwrites the base class Event handler functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertClass(wxCommandEvent& event);
        void OnInsertSubclass1(wxCommandEvent& event);
        void OnInsertSpecification(wxCommandEvent& event);
        void OnInsertSource(wxCommandEvent& event);
        void OnInsertForm(wxCommandEvent& event);
        void OnInsertProcessingDetails(wxCommandEvent& event);
        void OnInsertCharacterization(wxCommandEvent& event);
        void OnInsertPropertyData(wxCommandEvent& event);
        void OnInsertAssociationDetails(wxCommandEvent& event);
        void OnInsertComponentDetails(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteClass(wxCommandEvent& event);
        void OnDeleteSubclass1(wxCommandEvent& event);
        void OnDeleteAssociationDetails(wxCommandEvent& event);
        void OnDeleteCharacterization(wxCommandEvent& event);
        //void OnDeleteComponentDetails(wxCommandEvent& event);
        void OnDeleteForm(wxCommandEvent& event);
        void OnDeleteProcessingDetails(wxCommandEvent& event);
        void OnDeletePropertyData(wxCommandEvent& event);
        void OnDeleteSpecification(wxCommandEvent& event);
        void OnDeleteSource(wxCommandEvent& event);

        void OnPasteName(wxCommandEvent& event);
        void OnPasteClass(wxCommandEvent& event);
        void OnPasteSubclass(wxCommandEvent& event);
        void OnPasteSpecification(wxCommandEvent& event);
        void OnPasteSource(wxCommandEvent& event);
        void OnPasteForm(wxCommandEvent& event);
        void OnPasteProcessingDetails(wxCommandEvent& event);
        void OnPasteCharacterization(wxCommandEvent& event);
        void OnPastePropertyData(wxCommandEvent& event);
        void OnPasteAssociationDetails(wxCommandEvent& event);
        void OnPasteComponentDetails(wxCommandEvent& event);

        void OnBumpUp(wxCommandEvent& event);
        void OnBumpDown(wxCommandEvent& event);

        void OnLeftDown(wxTreeEvent& event);
    };

}; //namespace bellshire end
