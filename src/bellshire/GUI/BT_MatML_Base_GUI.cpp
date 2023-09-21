#include "pch.h"
#include <wx/config.h>
#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"
//#include "bellshire/BT_MatML_MatMLDropSource.h"
//#include "bellshire/BT_MatML_MatMLDataObject.h"

using namespace bellshire;

MatML_GUI_Base::MatML_GUI_Base()
{
};

MatML_GUI_Base::~MatML_GUI_Base()
{

	/*parent will destroy Ctrl or window */
	//delete m_lib_element;
}
wxNotebook* /*bellshire::*/MatML_GUI_Base::GetGUI()
{
	return m_GUI;
}
TreeCtrlSorted* /*bellshire::*/MatML_GUI_Base::GetMatMLLibTreeCtrl()
{
	return m_MatMLLibTreeCtrl;
}
//std::shared_ptr<xml_schema::element_type> bellshire::MatML_GUI_Base::GetLibElement()
//{
//	return m_lib_element;
//}

void MatML_GUI_Base::SetLibConnect()
{
	//Set Connect
	m_MatMLLibTreeCtrl->Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(MatML_GUI_Base::OnLeftDown), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActivated*/
	m_MatMLLibTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler(MatML_GUI_Base::OnMatMLLibItemMenu), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnMatMLItemMenu*/
}

void MatML_GUI_Base::OnLeftDown(wxTreeEvent& event)
{
	MatML_GUI_Base::DnDSource(event, m_MatMLLibTreeCtrl, m_GUI);
}

void MatML_GUI_Base::OnRightDown(wxTreeEvent& event)
{
}

void MatML_GUI_Base::OnMatMLLibItemMenu(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	m_MatMLLibTreeCtrl->SelectItem(itemId);

	MatMLTreeItemData* item = itemId.IsOk() ? (MatMLTreeItemData*)m_MatMLLibTreeCtrl->GetItemData(itemId)
		: NULL;
	wxPoint clientpt = event.GetPoint();
	wxPoint screenpt = m_MatMLLibTreeCtrl->ClientToScreen(clientpt);

	ShowContextMenu(itemId, clientpt);/*!< Shows context menu*/
	event.Skip();
}


void MatML_GUI_Base::OnDeleteUnit(wxCommandEvent& event) { 

	 auto element= MatML_GUI_Base::GetSelMatML<Unit>(m_MatMLLibTreeCtrl);
	 auto element_parent = MatML_GUI_Base::GetSelParentMatML<Units>(m_MatMLLibTreeCtrl);
	if (element_parent) {
		MatML_Base::DeleteSeqContChild(element, element_parent->Unit());
		MatML_GUI_Base::SetupSelParent<Units, Units_GUI>(m_MatMLLibTreeCtrl);
	}
}

void MatML_GUI_Base::OnDelete(wxCommandEvent& event)
{
	OnDeleteLibMatML< Unit,
		Units,
		Units::Unit_sequence,
		Units_GUI,
		&::Units::Unit
	>(event);


}

void MatML_GUI_Base::ShowContextMenu(wxTreeItemId id, const wxPoint& pt)
{

	wxString title;
	if (id.IsOk())
	{
		title << wxT("Library Element Menu");
	}
	else
	{
		title = wxT("");
	}

	wxMenu menu(title);

	void (MatML_GUI_Base::* test2)(wxCommandEvent&) = &bellshire::GUI::MatML_GUI_Base::OnDelete;

	wxMenuItem* PopupMenuItem = new wxMenuItem(&menu, wxID_ANY, wxString("Delete"), wxEmptyString, wxITEM_NORMAL);
	menu.Append(PopupMenuItem);

	this->m_GUI->wxEvtHandler::Bind(wxEVT_COMMAND_MENU_SELECTED, &bellshire::GUI::MatML_GUI_Base::OnDelete, this, PopupMenuItem->GetId());


	m_MatMLLibTreeCtrl->PopupMenu(&menu, pt);
}




void MatML_GUI_Base::DnDSource(wxTreeEvent& event, TreeCtrlSorted* MatMLLibTreeCtrl, wxWindow* GUI)
{
	//Get the item from the current event.
	wxTreeItemId itemId = event.GetItem();

	if (itemId.IsOk()) {

		wxTreeItemData* treeitemdata(MatMLLibTreeCtrl->GetItemData(itemId));
		MatMLTreeItemData* item = (MatMLTreeItemData*)(treeitemdata);

		try {

			DnDAnyMatMLData dndmatmldata(item);
			DnDMatMLDataObject matmldata(&dndmatmldata);
			MatMLDropSource dragSource(GUI);

			dragSource.SetData(matmldata);

			wxDragResult result = dragSource.DoDragDrop();

			switch (result)
			{
			case wxDragCopy:
				// copy the data
				break;
			case wxDragMove:
				// move the data
				break;
			default:
				// do nothing
				break;
			}
		}
		catch (...) {}
	}
}
