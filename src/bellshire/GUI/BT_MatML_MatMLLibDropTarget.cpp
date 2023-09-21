#include "pch.h"
#include "bellshire/GUI/BT_MatML_MatMLLibDropTarget.h"
#include "bellshire/BT_MatML_Default.h"
//#include "bellshire/BT_MatML_Units_GUI.h"

using namespace bellshire::GUI;

MatMLLibDropTarget::MatMLLibDropTarget()
	:wxDropTarget(new DnDMatMLDataObject),
	m_MatMLTreeCtrl(nullptr)
{
	return;
}

MatMLLibDropTarget::MatMLLibDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata) 
	:wxDropTarget(new DnDMatMLDataObject(dndmatmldata)),
	m_MatMLTreeCtrl(MatMLTreeCtrl)
{
	return;
}

MatMLLibDropTarget::~MatMLLibDropTarget() {
};

TreeCtrlSorted* MatMLLibDropTarget::GetMatMLTreeCtrl()
{
	return m_MatMLTreeCtrl;
}

void MatMLLibDropTarget::SetMatMLTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl)
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
wxDragResult MatMLLibDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult defResult)
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

					if (parentdata.type() == typeid(Units*) && data.type() == typeid(Unit*))	
					{
						if (defResult == InsertSequenceData< Unit, Units, Units::Unit_sequence, Units_GUI, &Units::Unit>(parentdata, data, defResult))
						{
							delete dnd_data; //Clean data owned
								dnd_data = nullptr; //Null just encase double deleted
								return defResult;
						}
					}
					if (defResult == InsertSequenceData< Class, BulkDetails, BulkDetails::Class_sequence, BulkDetails_GUI, &BulkDetails::Class>(parentdata, data, defResult))
					{
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Subclass, BulkDetails, BulkDetails::Subclass_sequence, BulkDetails_GUI, &BulkDetails::Subclass>(parentdata, data, defResult))
					{
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Class, ComponentDetails, ComponentDetails::Class_sequence, ComponentDetails_GUI, &ComponentDetails::Class>(parentdata, data, defResult))
					{
						delete dnd_data; //Clean data owned
						dnd_data = nullptr; //Null just encase double deleted
						return defResult;
					}
					if (defResult == InsertSequenceData< Subclass, ComponentDetails, ComponentDetails::Subclass_sequence, ComponentDetails_GUI, &ComponentDetails::Subclass>(parentdata, data, defResult))
					{
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
