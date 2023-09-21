/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_MeasurementTechniqueDetails_Display_GUI.h
// Purpose:     Classes of MeasurementTechniqueDetails_Display_GUI Base and Derived.
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
#include <wx/grid.h>

#include <boost/shared_ptr.hpp>
#include <math.h>
#include <list>
#include "bellshire/utilities/StringStream.h"
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"


namespace bellshire::GUI {
    class MeasurementTechniqueDetails_Display_GUI
    { 
        wxPanel* m_GUI;
        wxTextCtrl* m_MeasurementTechniqueDetailsNameTextCtrl;
        wxTextCtrl* m_MeasurementTechniqueDetailsNotesTextCtrl;
    public:


        MeasurementTechniqueDetails_Display_GUI();
        MeasurementTechniqueDetails_Display_GUI(wxNotebook* parent);

        virtual ~MeasurementTechniqueDetails_Display_GUI();

        wxPanel* GetGUI();
        wxTextCtrl* GetMeasurementTechniqueDetailsNameTextCtrl();
        wxTextCtrl* GetMeasurementTechniqueDetailsNotesTextCtrl();
        wxPanel* get() { return m_GUI; }

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& MeasurementTechniqueDetailsNameTextCtrl,
            wxTextCtrl*& MeasurementTechniqueDetailsNotesTextCtrl
        );

        void Update( const observer_ptr<PropertyData> element);
    };

}; //namespace bellshire end

