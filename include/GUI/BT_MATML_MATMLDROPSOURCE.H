#pragma once
#include <wx/dnd.h>

namespace bellshire {

	class MatMLDropSource : public wxDropSource
	{
	public:
		MatMLDropSource(
			wxDataObject& data,
			wxWindow* win = NULL,
			const wxCursor& iconCopy = wxNullCursor,
			const wxCursor& iconMove = wxNullCursor,
			const wxCursor& iconNone = wxNullCursor
		);

		MatMLDropSource(
			wxWindow* win = NULL,
			const wxCursor& iconCopy = wxNullCursor,
			const wxCursor& iconMove = wxNullCursor,
			const wxCursor& iconNone = wxNullCursor
		);

		virtual ~MatMLDropSource() {};

		//virtual wxDragResult DoDragDrop(int flags = wxDrag_CopyOnly);

	private:
	};

};//bellshire
