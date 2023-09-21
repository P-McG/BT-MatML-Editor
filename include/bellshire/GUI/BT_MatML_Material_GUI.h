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


// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/frame.h>

#include <wx/radiobut.h>
#include "wx/dcsvg.h"
#include "wx/notebook.h"

#include <math.h>

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Material.h"
#include "bellshire/GUI/utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"


namespace bellshire::GUI {

    class MatML_GUI_Base;
    class ID_GUI;

    class Material_GUI_Base : public MatML_GUI_Base, public Material_Base
    {
    protected:
        ID_GUI* m_Material_ID_GUI;
        wxTextCtrl* m_MaterialLayersTextCtrl;
        wxTextCtrl* m_MaterialLFORTextCtrl;

    public:
        Material_GUI_Base();
        Material_GUI_Base(wxWindow* parent);
        virtual ~Material_GUI_Base();

        ID_GUI* GetMaterial_ID_GUI();
        wxTextCtrl* GetMaterialLayersTextCtrl();
        wxTextCtrl* GetMaterialLFORTextCtrl();

        static wxNotebook* Create(wxWindow* parent, 
            ID_GUI*& Material_ID_GUI,
            wxTextCtrl*& MaterialLayersTextCtrl,
            wxTextCtrl*& MaterialLFORTextCtrl
        );
        static wxWindow* CreateMaterialPanel(wxWindow* parent,
            ID_GUI*& Material_ID_GUI,
            wxTextCtrl*& MaterialLayersTextCtrl,
            wxTextCtrl*& MaterialLFORTextCtrl
        );

        static wxString GetTreeLabel(const observer_ptr<Material> element);

        void ReplaceIDwithUuid(MatML_Doc& doc);
        static wxTreeItemId SetupBranch(TreeCtrlSorted*& MatMLTreeCtrl, wxWindow*& ParentId, MatML_Doc& Element, std::vector<Material*>& materials);
        void Update( const observer_ptr<Material> element);

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
    };

 class Material_GUI : public Material_GUI_Base
    {
  
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        observer_ptr<MatML_Doc> m_MatMLDoc;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Material_GUI();
        Material_GUI(wxWindow* parent);

        virtual ~Material_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        observer_ptr<MatML_Doc> GetMatMLDoc();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.

        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl, observer_ptr<MatML_Doc>& MatMLDoc);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLDoc(const observer_ptr<MatML_Doc>& matml_doc);
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
    };
}; //namespace bellshire end

#include "bellshire/GUI/BT_MatML_Material_GUI.inl"