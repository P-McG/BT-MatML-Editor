/**
 * @file HTMLFrame.cpp
 *
 * @brief
 *
 * @author Paul McGrath
 * Contact:
 *
 */
#include "pch.h"
#include "bellshire/GUI/HTMLFrame.h"

using namespace bellshire::GUI;

HTMLFrame::HTMLFrame( wxWindow* parent ):HTMLFrameBase( parent )
{
	htmleasyprinting=new wxHtmlEasyPrinting(wxT("Printing"),this);
}
HTMLFrame::~HTMLFrame()
{
	delete htmleasyprinting;
}


void HTMLFrame::OnHTMLPrintButton( wxCommandEvent& event )
{
	// TODO: Implement OnHTMLPrintButton
	htmleasyprinting->PrintFile(m_HTMLWindow->GetOpenedPage());

}

void HTMLFrame::OnHTMLPreviewButton( wxCommandEvent& event )
{
	htmleasyprinting->PreviewFile(m_HTMLWindow->GetOpenedPage());
}

void HTMLFrame::OnClose( wxCloseEvent& event )
{
	//don't really close the frame only hide it.
	this->Show(false);
	this->Lower();

}
void HTMLFrame::OnCloseButton( wxCommandEvent& event )
{
	//don't really close the frame only hide it.
	this->Show(false);
	this->Lower();

}
