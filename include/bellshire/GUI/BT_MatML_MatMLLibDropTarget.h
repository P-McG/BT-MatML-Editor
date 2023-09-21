#pragma once
#include <wx/dnd.h>
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_MatMLDataObject.h"


namespace bellshire::GUI {


	/// <summary>
	/// This class is used as the dnd drop target for the MatML_Lib TreeCtrlSorted
	/// </summary>
	class MatMLLibDropTarget : public wxDropTarget
	{
		TreeCtrlSorted* m_MatMLTreeCtrl;

	public:
		MatMLLibDropTarget();
		MatMLLibDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata = (DnDMatMLData * )nullptr);
		virtual ~MatMLLibDropTarget();

		TreeCtrlSorted* GetMatMLTreeCtrl();
		void SetMatMLTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl);
		virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult defResult);

		template< class MatML_Class,
			class MatML_ParentClass,
			class MatML_ContClass,
			class MatML_GUI,
			MatML_ContClass& (MatML_ParentClass::* cont_func)()
		>
			wxDragResult InsertSequenceData(boost::any parentdata, boost::any data, wxDragResult defResult);
	};

}//bellshire

#include "bellshire/GUI/BT_MatML_MatMLLibDropTarget.inl"