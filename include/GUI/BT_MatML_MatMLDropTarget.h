#pragma once
#include <wx/dnd.h>
#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_MatMLDataObject.h"

namespace bellshire {
	class MatMLDropTarget : public wxDropTarget
	{
	public:
		MatMLDropTarget();
		MatMLDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata = (DnDMatMLData * )nullptr);
		virtual ~MatMLDropTarget();

		void SetMatMLTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl);
		virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult defResult);

	private:
		TreeCtrlSorted* m_MatMLTreeCtrl;
		//MatMLDataObjectSimple* m_dropdata;

	};
}//bellshire
