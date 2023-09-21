#include "pch.h"
#include "bellshire/GUI/BT_MatML_MatMLDropTarget.h"
#include "bellshire/BT_MatML_Default.h"
//#include "bellshire/GUI/BT_MatML_Units_GUI.h"

using namespace bellshire::GUI;

MatMLDropTarget::MatMLDropTarget()
	:wxDropTarget(new DnDMatMLDataObject),
	m_MatMLTreeCtrl(nullptr)
{
	return;
}

MatMLDropTarget::MatMLDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata) 
	:wxDropTarget(new DnDMatMLDataObject(dndmatmldata)),
	m_MatMLTreeCtrl(MatMLTreeCtrl)
{
	return;
}

MatMLDropTarget::~MatMLDropTarget() {
};

TreeCtrlSorted* MatMLDropTarget::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

void MatMLDropTarget::SetMatMLTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Called after OnDrop() returns true. By default this will usually GetData() 
/// and will return the suggested default value defResult.
/// 
/// Warning:
/// The sequence items should not, at this time, refer to IDREF elements. This
/// is due to the ID not being imported as well as the dropped item.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="defResult"></param>
/// <returns></returns>
wxDragResult MatMLDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult defResult)
{
	if (!GetData())
	{
		//wxLogError("Failed to get drag and drop data");

		return wxDragNone;
	}

	// This method (wxDropTarget::GetData()) may only be called from within OnData(). 
	// By default, this method copies the data from the drop source to the wxDataObject 
	// associated with this drop target, calling its wxDataObject::SetData() method.
	DnDMatMLDataObject* dnd_data_obj((DnDMatMLDataObject*)this->GetDataObject());
	DnDAnyMatMLData* dnd_data((DnDAnyMatMLData * )dnd_data_obj->GetMatMLData());//Gain ownership of the data.
	if (!dnd_data->IsNull()) {
		boost::any data(dnd_data->GetMatMLTreeItemData()->GetAnyMatMLDataPointer());//Gain ownership of the data

		int flags;
		wxTreeItemId itemId = m_MatMLTreeCtrl->HitTest(wxPoint(x, y), flags);

		if (itemId.IsOk()) {
			MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
			if (item) {
				boost::any parentdata(item->GetAnyMatMLDataPointer());

				if (flags && wxTREE_HITTEST_ONITEMLABEL) {
					if (defResult == InsertSequenceData< Unit, Units, Units::Unit_sequence, Units_GUI, &Units::Unit>(parentdata, data, defResult))
					{
						//To ensure there are no dangling external references
						//that can cause validation errors on next loading.
						ClearIdRefs<Unit>(data);

						//dnd cleanup
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted

						return defResult;

					}
					if (defResult == InsertSequenceData< Class, BulkDetails, BulkDetails::Class_sequence, BulkDetails_GUI, &BulkDetails::Class>(parentdata, data, defResult))
					{
						//To ensure there are no dangling external references
						//that can cause validation errors on next loading.
						ClearIdRefs<Class>(data);

						//dnd cleanup
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Subclass, BulkDetails, BulkDetails::Subclass_sequence, BulkDetails_GUI, &BulkDetails::Subclass>(parentdata, data, defResult))
					{
						//To ensure there are no dangling external references
						//that can cause validation errors on next loading.
						ClearIdRefs<BulkDetails::Subclass_type>(data);

						//dnd cleanup
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Class, ComponentDetails, ComponentDetails::Class_sequence, ComponentDetails_GUI, &ComponentDetails::Class>(parentdata, data, defResult))
					{
						//To ensure there are no dangling external references
						//that can cause validation errors on next loading.
						ClearIdRefs<Class>(data);

						//dnd cleanup
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Subclass, ComponentDetails, ComponentDetails::Subclass_sequence, ComponentDetails_GUI, &ComponentDetails::Subclass>(parentdata, data, defResult))
					{
						//To ensure there are no dangling external references
						//that can cause validation errors on next loading.
						ClearIdRefs<Subclass>(data);

						//dnd cleanup
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
				}
			}
		}
	}

	delete dnd_data; //Clean data owned
	dnd_data = nullptr; //Null just encase double deleted

	return wxDragNone;
}

