/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_AuthorityDetails_Display_GUI.h
// Purpose:     Classes of AuthorityDetails_Display_GUI Base and Derived.
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


    class AuthorityDetails_Display_GUI
    {
        wxPanel* m_GUI;
        wxTextCtrl* m_AuthorityDetailsNameTextCtrl;
        wxTextCtrl* m_AuthorityDetailsNotesTextCtrl;

    public:
        AuthorityDetails_Display_GUI();
        AuthorityDetails_Display_GUI(wxNotebook* parent);

        virtual ~AuthorityDetails_Display_GUI();

        wxPanel* GetGUI();
        wxTextCtrl* GetAuthorityDetailsNameTextCtrl();
        wxTextCtrl* GetAuthorityDetailsNotesTextCtrl();

        wxPanel* get() { return m_GUI; };

        static wxPanel* Create(
            wxNotebook* parent,
            wxTextCtrl*& AuthorityDetailsNameTextCtrl,
            wxTextCtrl*& AuthorityDetailsNotesTextCtrl
        );

        void Update( const observer_ptr<Name> element);
        void Update( const observer_ptr<Specification> element);
    };

}; //namespace bellshire end

