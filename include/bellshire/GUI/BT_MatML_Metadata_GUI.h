/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Metadata_GUI.h
// Purpose:     Classes of Metadata_GUI Base and Derived.
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
#include "bellshire/BT_MatML_Metadata.h"

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
#include "bellshire/GUI/BT_MatML_MatMLInfo_GUI.h"
#include "bellshire/GUI/BT_MatML_ID_GUI.h"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI {

    class Metadata_GUI_Base : public MatML_GUI_Base, public Metadata_Base
    {
    protected:

    public:
        Metadata_GUI_Base();
        Metadata_GUI_Base(wxWindow* parent);
        virtual ~Metadata_GUI_Base();

        static wxNotebook* Create(wxWindow* parent);
        static wxWindow* CreateMetadataPanel(wxWindow* parent);

        void Update( const observer_ptr<Metadata> element);

        static wxString GetTreeLabel(const observer_ptr<Metadata> element);

        void SetConnect() {};

        virtual void OnInsertAuthorityDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertDataSourceDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertMeasurementTechniqueDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertParameterDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertPropertyDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSourceDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertSpecimenDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnInsertTestConditionDetails(wxCommandEvent& event) { event.Skip(); }

        virtual void OnDeleteAuthorityDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteDataSourceDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteMeasurementTechniqueDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteParameterDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeletePropertyDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSpecimenDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteSourceDetails(wxCommandEvent& event) { event.Skip(); }
        virtual void OnDeleteTestConditionDetails(wxCommandEvent& event) { event.Skip(); }

        virtual void OnPasteAuthorityDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteDataSourceDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteMeasurementTechniqueDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteParameterDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPastePropertyDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteSourceDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteSpecimenDetails(wxCommandEvent& event){ event.Skip(); }
        virtual void OnPasteTestConditionDetails(wxCommandEvent& event){ event.Skip(); }
    };

    class Metadata_GUI : public Metadata_GUI_Base
    {
        TreeCtrlSorted* m_MatMLTreeCtrl;//Required before Event Handling.
        ::boost::any m_MatMLItemToCopy;//Required before Paste Event Handling.

    public:
        Metadata_GUI();
        Metadata_GUI(wxWindow* parent);

        virtual ~Metadata_GUI();

        TreeCtrlSorted* GetMatMLTreeCtrl();//Required before Event Handling.
        ::boost::any GetMatMLItemToCopy();//Required before Paste Event Handling.
        void SetEvtHandlerVar(TreeCtrlSorted*& MatMLTreeCtrl);//Required before Event Handling.
        void SetMatMLTreeCtrl(TreeCtrlSorted*& MatMLTreeCtrl);
        void SetMatMLItemToCopy(const ::boost::any& MatMLItemToCopy);//Required before paste Event Handling.

        //Overwrites the base class functions
        void OnInsertAuthorityDetails(wxCommandEvent& event);
        void OnInsertDataSourceDetails(wxCommandEvent& event);
        void OnInsertMeasurementTechniqueDetails(wxCommandEvent& event);
        void OnInsertParameterDetails(wxCommandEvent& event);
        void OnInsertPropertyDetails(wxCommandEvent& event);
        void OnInsertSourceDetails(wxCommandEvent& event);
        void OnInsertSpecimenDetails(wxCommandEvent& event);
        void OnInsertTestConditionDetails(wxCommandEvent& event);

        void OnDeleteAuthorityDetails(wxCommandEvent& event);
        void OnDeleteDataSourceDetails(wxCommandEvent& event);
        void OnDeleteMeasurementTechniqueDetails(wxCommandEvent& event);
        void OnDeleteParameterDetails(wxCommandEvent& event);
        void OnDeletePropertyDetails(wxCommandEvent& event);
        void OnDeleteSpecimenDetails(wxCommandEvent& event);
        void OnDeleteSourceDetails(wxCommandEvent& event);
        void OnDeleteTestConditionDetails(wxCommandEvent& event);

        void OnPasteAuthorityDetails(wxCommandEvent& event);
        void OnPasteDataSourceDetails(wxCommandEvent& event);
        void OnPasteMeasurementTechniqueDetails(wxCommandEvent& event);
        void OnPasteParameterDetails(wxCommandEvent& event);
        void OnPastePropertyDetails(wxCommandEvent& event);
        void OnPasteSourceDetails(wxCommandEvent& event);
        void OnPasteSpecimenDetails(wxCommandEvent& event);
        void OnPasteTestConditionDetails(wxCommandEvent& event);


    private:
    };

}; //namespace bellshire end
