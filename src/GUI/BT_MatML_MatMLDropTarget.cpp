#include "BT_MatML_MatMLDropTarget.h"
#include "BT_MatML_Default.h"
#include "BT_MatML_Units_GUI.h"

using namespace bellshire;

MatMLDropTarget::MatMLDropTarget()
	:wxDropTarget(new DnDMatMLDataObject)/*,
	m_dropdata(nullptr)*/
{
	return;
}

MatMLDropTarget::MatMLDropTarget(TreeCtrlSorted* MatMLTreeCtrl, DnDMatMLData* dndmatmldata) 
	:wxDropTarget(new DnDMatMLDataObject(dndmatmldata)),
	m_MatMLTreeCtrl(MatMLTreeCtrl)/*,
	m_dropdata(nullptr)*/
{
	return;
}

MatMLDropTarget::~MatMLDropTarget() {
	//delete m_dropdata;
};

void MatMLDropTarget::SetMatMLTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl)
{
	m_MatMLTreeCtrl = MatMLTreeCtrl;
}

/// <summary>
/// Called after OnDrop() returns true. By default this will usually GetData() 
/// and will return the suggested default value defResult.
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
	wxDataFormat dataformat(const wxString("DF_ANYMATMLDATA"));

	DnDMatMLDataObject* dnd_data_obj((DnDMatMLDataObject*)this->GetDataObject());
	DnDUnitMatMLData* dnd_data((DnDUnitMatMLData * )dnd_data_obj->GetMatMLData());

	int flags;
	wxTreeItemId itemId = m_MatMLTreeCtrl->HitTest(wxPoint(x, y), flags);
	MatMLTreeItemData* item = (MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(itemId));
	boost::any parentdata(item->GetAnyMatMLDataPointer());

	if (flags && wxTREE_HITTEST_ONITEMLABEL) {
		try {

			Units* parentelement = boost::any_cast<Units*>(parentdata);
			const Unit* element(dnd_data->GetUnit());

			if (parentelement && element ) {

				parentelement->Unit().push_back(*element);

				MatML_Base_GUI::SetupSel<Units, Units_GUI>(m_MatMLTreeCtrl);

				return defResult;
			}
		}
		catch (const boost::bad_any_cast&) { return wxDragNone; }
	}

	return defResult;
}
