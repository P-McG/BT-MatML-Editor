#pragma once
#include <wx/dnd.h>
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/BT_MatML_MatMLDataObject.h"

#include "bellshire/utilities/BT_MatML_Get_Associated_Base_type.h"

namespace bellshire::GUI {

	/// <summary>
	/// This class is used as the dnd drop target for the MatML TreeCtrlSorted
	/// </summary>
	class MatMLDropTarget : public wxDropTarget
	{
		TreeCtrlSorted* m_MatMLTreeCtrl;

	public:
		MatMLDropTarget();
		MatMLDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata = (DnDMatMLData * )nullptr);
		virtual ~MatMLDropTarget();

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

		template<class MatML_Class,
			class MatML_Base_Class = bellshire::utilities::Get_Associated_Base_type<MatML_Class>::MatML_Base_type
		>
		void ClearIdRefs(boost::any data);

	};

}//bellshire::GUI

#include "bellshire/GUI/BT_MatML_MatMLDropTarget.inl"