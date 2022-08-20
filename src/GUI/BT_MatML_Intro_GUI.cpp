#include "BT_MatML_Intro_GUI.h"

#include "../images/BT_MatML_Editor_256px.xpm"

using namespace bellshire;

/// Constructor
/// <summary>
/// 
/// </summary>
Intro_GUI_Base::Intro_GUI_Base() 
	:m_GUI(nullptr),
	m_logobitmap(nullptr)
{}

/// Main Constructor
/// <summary>
/// </summary>
/// <param name="parent"></param>
Intro_GUI_Base::Intro_GUI_Base( wxWindow* parent ) 
	: m_GUI(nullptr),
	m_logobitmap(nullptr)
{
	/// Create Gui
	m_GUI = Create(parent, m_logobitmap);
}

/// Destructor
/// <summary>
/// 
/// </summary>
Intro_GUI_Base::~Intro_GUI_Base() {
	/// parent will distroy Ctrl or window
}


///
/// Creates the Gui for the Intro MatML data and Info.
/// <summary>
 /// </summary>
 /// <param name="parent"></param>
 /// <returns>wxNotebook*</returns>
wxNotebook* Intro_GUI_Base::Create(wxWindow* parent, wxStaticBitmap* logobitmap)
{
	/// Creates wxNotebook
	wxNotebook* IntroNotebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 | wxFULL_REPAINT_ON_RESIZE);
	IntroNotebook->Hide();
	IntroNotebook->SetMinSize(wxSize(400, 500));

	/// Creates the MatML data panel
	wxScrolledWindow* IntroPanel = new wxScrolledWindow(IntroNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	IntroPanel->SetScrollRate(5, 5);
	IntroPanel->SetMinSize(wxSize(400, 500));
	//IntroPanel->SetMaxSize(wxSize(-1, 100));

	wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer2->AddGrowableCol(0);
	fgSizer2->AddGrowableRow(1);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	logobitmap = new wxStaticBitmap(IntroPanel, wxID_ANY, wxBitmap(BT_MatML_Editor_256px_xpm), wxDefaultPosition, wxDefaultSize, long(0));
	logobitmap->Centre();
	fgSizer2->Add(logobitmap, 1, wxALL | wxEXPAND, 5);

	wxStaticText* IntroStaticText = new wxStaticText(IntroPanel, wxID_ANY, "\nWelcome to BT-MatML-Editor.\n\nPlease select:\nFile->New, or\nFile->Open \nto begin.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	IntroStaticText->Wrap(-1);
	IntroStaticText->Centre();
	fgSizer2->Add(IntroStaticText, 1, wxALL | wxEXPAND, 5);

	IntroPanel->SetSizer(fgSizer2);
	IntroPanel->Layout();
	fgSizer2->Fit(IntroPanel);

	/// Creates the MatML Info panel
	MatMLInfo_GUI matMLInfo_GUI(IntroNotebook,
		wxT("")
	);

	/// Adds the above panels to the wxNotebook
	IntroNotebook->AddPage(IntroPanel, wxT("MatML Data."), true);
	IntroNotebook->AddPage(matMLInfo_GUI.get(), wxT("MatML Info."), false);

	return IntroNotebook;
}


void Intro_GUI_Base::Update()
{
	/// Nothing to update

	/// Show Gui
	Show(true); 
}


/// <summary>
/// Constructor for the derived class
/// </summary>
Intro_GUI::Intro_GUI() 
	: Intro_GUI_Base()
{}

/// <summary>
/// Constructor for the derived class
/// </summary>
/// <param name="parent"></param>
Intro_GUI::Intro_GUI(wxWindow* parent)
	: Intro_GUI_Base(parent)
{
}

/// <summary>
/// Destructor for the derived class
/// </summary>
Intro_GUI::~Intro_GUI() {
	/// parent window will destroy Ctrl or window
}
