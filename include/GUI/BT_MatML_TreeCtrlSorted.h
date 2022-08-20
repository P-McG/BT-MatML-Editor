/////////////////////////////////////////////////////////////////////////////
// Name:        TreeCtrlSorted.h
// Purpose:     MatML Sorted Version of the wxTree.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __TreeCtrlSorted__
#define __TreeCtrlSorted__

#include <wx/treectrl.h>
#include <wx/object.h>
#include "matml31.hxx"

namespace bellshire{
class TreeCtrlSorted : public ::wxTreeCtrl
{

	public:
		TreeCtrlSorted(wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
				long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxString(wxT("treeCtrl")))
				:wxTreeCtrl(parent, id, pos, size, style, validator, name){};
	    wxArrayString GetSortClasses();
		int ClassOrder(Class& item);
		int PositionOrder(Material* material);
		int PositionOrder(BulkDetails* parent, Class* element);

	protected:
		virtual int OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2);


		DECLARE_DYNAMIC_CLASS(TreeCtrlSorted)

	public:
		wxArrayString ClassOrderIndex;

};
}//namespace bellshire

#endif //__TreeCtrlSorted__
