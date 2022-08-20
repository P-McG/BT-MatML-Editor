/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_MatMLInfo_GUI.h
// Purpose:     Classes of MatMLInfo_GUI Base and Derived.
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

namespace bellshire {

	class MatMLInfo_GUI {
	public:
		const wxString m_label;
		wxScrolledWindow* m_GUI;

		MatMLInfo_GUI();
		MatMLInfo_GUI(wxWindow* parent, const wxString& label);
		static wxScrolledWindow* Create(wxWindow* parent, const wxString& label);
		virtual ~MatMLInfo_GUI();

		wxScrolledWindow* get() { return m_GUI; };
	private:
	};

};//bellshire namespace end
