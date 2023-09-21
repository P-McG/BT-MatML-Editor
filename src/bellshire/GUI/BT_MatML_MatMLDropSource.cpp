#include "pch.h"
#include "bellshire/GUI/BT_MatML_MatMLDropSource.h"

using namespace bellshire::GUI;


/// <summary>
/// The constructor taking a wxDataObject.
/// </summary>
/// <param name="data"></param>
/// <param name="win"></param>
/// <param name="iconCopy"></param>
/// <param name="iconMove"></param>
/// <param name="iconNone"></param>
MatMLDropSource::MatMLDropSource(
	wxDataObject& data,
	wxWindow* win,
	const wxCursor& iconCopy,
	const wxCursor& iconMove,
	const wxCursor& iconNone
):wxDropSource(data, win, iconCopy, iconMove, iconNone)
{

}

MatMLDropSource::MatMLDropSource(
	wxWindow* win,
	const wxCursor& iconCopy,
	const wxCursor& iconMove,
	const wxCursor& iconNone
) 
	:wxDropSource(win, iconCopy, iconMove, iconNone)
{

}

MatMLDropSource::~MatMLDropSource()
{

}

///// <summary>
///// Starts the drag-and-drop operation which will terminate when the user releases the mouse. 
///// Call this in response to a mouse button press, for example.
///// </summary>
///// <param name="flags"></param>
///// <returns></returns>
//wxDragResult MatMLDropSource::DoDragDrop(int flags)
//{
//	Call base
//	return wxDropSource::DoDragDrop(flags);
//}

