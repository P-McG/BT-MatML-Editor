#include "HTMLFrameBase.h"


HTMLFrameBase::HTMLFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer(wxHORIZONTAL);

	m_panel62 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer(wxHORIZONTAL);

	m_HTMLPreviewButton = new wxButton(m_panel62, wxID_ANY, wxT("Preview"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer63->Add(m_HTMLPreviewButton, 0, wxALL, 5);

	m_HTMLPrintButton = new wxButton(m_panel62, wxID_ANY, wxT("Print"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer63->Add(m_HTMLPrintButton, 0, wxALL, 5);

	m_HTMLCloseButton = new wxButton(m_panel62, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer63->Add(m_HTMLCloseButton, 0, wxALL, 5);

	m_panel62->SetSizer(bSizer63);
	m_panel62->Layout();
	bSizer63->Fit(m_panel62);
	bSizer59->Add(m_panel62, 1, wxEXPAND | wxALL, 0);

	bSizer58->Add(bSizer59, 0, wxEXPAND, 0);

	m_HTMLWindow = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO | wxSUNKEN_BORDER);
	bSizer58->Add(m_HTMLWindow, 1, wxALL | wxEXPAND, 0);

	this->SetSizer(bSizer58);
	this->Layout();
	m_statusBar2 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	// Connect Events
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(HTMLFrameBase::OnClose));
	m_HTMLPreviewButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HTMLFrameBase::OnHTMLPreviewButton), NULL, this);
	m_HTMLPrintButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HTMLFrameBase::OnHTMLPrintButton), NULL, this);
	m_HTMLCloseButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HTMLFrameBase::OnCloseButton), NULL, this);
}

HTMLFrameBase::~HTMLFrameBase()
{
}
