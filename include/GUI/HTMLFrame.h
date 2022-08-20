#ifndef __HTMLFRAME__
#define __HTMLFRAME__

#include <wx/html/htmprint.h>
#include "HTMLFrameBase.h"

namespace bellshire{

/** Implementing HTMLFrameBase */
class HTMLFrame : public HTMLFrameBase
{
protected:
	// Handlers for HTMLFrameBase events.
	void OnHTMLPrintButton( wxCommandEvent& event );
	void OnHTMLPreviewButton( wxCommandEvent& event );
	void OnClose( wxCloseEvent& event );
	void OnCloseButton( wxCommandEvent& event );
	wxHtmlEasyPrinting* htmleasyprinting;
public:
	/** Constructor */
	HTMLFrame( wxWindow* parent );
	~HTMLFrame();

};
}//namespace bellshire

#endif // __HTMLFRAME__
