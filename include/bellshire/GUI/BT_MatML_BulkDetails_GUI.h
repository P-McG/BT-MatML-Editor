/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_BulkDetails_GUI.h
// Purpose:     Classes of BulkDetails_GUI Base and Derived.
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

//#include <math.h>
#include "bellshire/matml31.hxx"
#include "bellshire/Lib/matml31_lib.hxx"
//
#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.h"
#include "bellshire/GUI/BT_MatML_MatMLLibDropTarget.h"


namespace bellshire::GUI {

    class BulkDetails_GUI_Base :  public BulkDetails_Base, public MatML_GUI_Base, public MatML_GUI_Lib
    {
    protected:
        MatMLLibDropTarget* m_droptarget;

    public:
        BulkDetails_GUI_Base();
        BulkDetails_GUI_Base(wxWindow* parent);
        BulkDetails_GUI_Base(MatMLLibDropTarget* droptarget);
        virtual ~BulkDetails_GUI_Base();

        static wxNotebook* Create(wxWindow* parent,
            TreeCtrlSorted*& MatMLLibTreeCtrl,
            observer_ptr<xml_schema::element_type> lib_element,
            MatMLLibDropTarget* droptarget
        );
        static wxWindow* CreateBulkDetailsPanel(wxWindow* parent);
        static wxString GetTreeLabel(const observer_ptr<BulkDetails> Element);

        MatMLLibDropTarget* GetDropTarget();

        void Update( const observer_ptr<BulkDetails> element);

        virtual void SetConnect();

        //EvtHandler functions to be bonded and over written by derived class.
        virtual void OnInsertName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertClass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSubclass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSpecification(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSource(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertForm(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertProcessingDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertCharacterization(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertPropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertNotes(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteName(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteClass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSubclass(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteCharacterization(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteForm(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteProcessingDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeletePropertyData(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteNotes(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSpecification(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSource(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteName(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteClass(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteSubclass(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteSpecification(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteSource(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteForm(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteProcessingDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteCharacterization(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPastePropertyData(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteNotes(wxCommandEvent& event){ event.Skip(); }

        //virtual void OnLeftDown(wxTreeEvent& event) { event.Skip(); }

        bool operator==(const BulkDetails_GUI_Base& other) const;
    };

   class BulkDetails_GUI : public BulkDetails_GUI_Base
    {

        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        BulkDetails_GUI();
        BulkDetails_GUI(wxWindow* parent);

        virtual ~BulkDetails_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//required before paste Event Handling.

        TreeCtrlSorted* GetMatMLTreeCtrl();
        ::boost::any GetMatMLItemToCopy();

        //template<typename MatML_Class, typename MatML_ContClass >
        //void InsertSeqContChild(MatML_ContClass& MatML);

        //Overwrites the base class functions
        void OnInsertName(wxCommandEvent& event);
        void OnInsertClass(wxCommandEvent& event);
        void OnInsertSubclass(wxCommandEvent& event);
        void OnInsertSpecification(wxCommandEvent& event);
        void OnInsertSource(wxCommandEvent& event);
        void OnInsertForm(wxCommandEvent& event);
        void OnInsertProcessingDetails(wxCommandEvent& event);
        void OnInsertCharacterization(wxCommandEvent& event);
        void OnInsertPropertyData(wxCommandEvent& event);
        void OnInsertNotes(wxCommandEvent& event);

        void OnDeleteName(wxCommandEvent& event);
        void OnDeleteClass(wxCommandEvent& event);
        void OnDeleteSubclass(wxCommandEvent& event);
        void OnDeleteForm(wxCommandEvent& event);
        void OnDeleteProcessingDetails(wxCommandEvent& event);
        void OnDeleteCharacterization(wxCommandEvent& event);
        void OnDeletePropertyData(wxCommandEvent& event);
        void OnDeleteNotes(wxCommandEvent& event);
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
        void OnPasteNotes(wxCommandEvent& event);

        void OnLeftDown(wxTreeEvent& event);

   };

}; //namespace bellshire end
