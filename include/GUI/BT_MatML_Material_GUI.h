/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Material_GUI.h
// Purpose:     Classes of Material_GUI Base and Derived.
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

#include <wx/frame.h>

#include <wx/radiobut.h>
#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>

#include "matml31.hxx"

#include "BT_MatML_Base_GUI.h"
#include "BT_MatML_ID_GUI.h"
#include "BT_MatML_MatMLInfo_GUI.h"

#include "BT_MatML_GUI.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"




namespace bellshire {

    class ID_GUI;

    class Material_GUI_Base : public MatML_Base_GUI
    {
    public:
        wxNotebook* m_GUI;
        ID_GUI* m_Material_ID_GUI;
        wxTextCtrl* m_MaterialLayersTextCtrl;
        wxTextCtrl* m_MaterialLFORTextCtrl;

        Material_GUI_Base();
        Material_GUI_Base(wxWindow* parent);

        virtual ~Material_GUI_Base();

        static wxNotebook* Create(wxWindow* parent, ID_GUI*& Material_ID_GUI, wxTextCtrl*& MaterialLayersTextCtrl, wxTextCtrl*& MaterialLFORTextCtrl);

        void Show(bool show = true) { if (m_GUI != nullptr) m_GUI->Show(show); return; };
        wxNotebook* get() { return m_GUI; };

        static wxTreeItemId SetupMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl,
            const wxTreeItemId& ParentId,
            Material& Element, 
            const wxTreeItemId& PreviousId
        );
        static wxTreeItemId SetupBranch(TreeCtrlSorted*& MatMLTreeCtrl, wxWindow*& ParentId, MatML_Doc& Element, std::vector<Material*>& materials);
        void Update( Material* element);

        void SetConnect();
        virtual void OnMaterialLayersTextCtrl(wxCommandEvent& event) { event.Skip(); }
        virtual void OnMaterialLFORTextCtrl(wxCommandEvent& event) { event.Skip(); }

        virtual void OnInsertMaterial(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertBulkDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertComponentDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertGraphs(wxCommandEvent& event){ event.Skip(); }
        virtual void OnInsertGlossary(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteBulkDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteComponentDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteGraphs(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteGlossary(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteBulkDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteComponentDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteGraphs(wxCommandEvent& event) { event.Skip(); }
        virtual void OnPasteGlossary(wxCommandEvent& event) { event.Skip(); }

        virtual void OnCopyMaterial(wxCommandEvent& event) { event.Skip(); }

        virtual void OnBumpDown(wxCommandEvent& event) { event.Skip(); }
        virtual void OnBumpUp(wxCommandEvent& event) { event.Skip(); }

    private:
    };

 class Material_GUI : public Material_GUI_Base
    {
    public:
  
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::shared_ptr<MatML_Doc> m_MatMLDoc;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

        Material_GUI();
        Material_GUI(wxWindow* parent);

        virtual ~Material_GUI();

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, ::boost::shared_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(::boost::shared_ptr<MatML_Doc>& MatMLDoc);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnMaterialLayersTextCtrl(wxCommandEvent& event);
        void OnMaterialLFORTextCtrl(wxCommandEvent& event);

        void OnInsertMaterial(wxCommandEvent& event);
        void OnInsertBulkDetails(wxCommandEvent& event);
        void OnInsertComponentDetails(wxCommandEvent& event);
        void OnInsertGraphs(wxCommandEvent& event);
        void OnInsertGlossary(wxCommandEvent& event);

        void OnDeleteBulkDetails(wxCommandEvent& event);
        void OnDeleteComponentDetails(wxCommandEvent& event);
        void OnDeleteGraphs(wxCommandEvent& event);
        void OnDeleteGlossary(wxCommandEvent& event);

        void OnPasteBulkDetails(wxCommandEvent& event);
        void OnPasteComponentDetails(wxCommandEvent& event);
        void OnPasteGraphs(wxCommandEvent& event);
        void OnPasteGlossary(wxCommandEvent& event);

        void OnCopyMaterial(wxCommandEvent& event);

        void OnBumpDown(wxCommandEvent& event);
        void OnBumpUp(wxCommandEvent& event);

    private:
    };

}; //namespace bellshire end
