/**
 * @file BT_MatML_MaterialFrameBase_GUI.cpp
 *
 * @brief
 *
 * @author Paul McGrath
 * Contact:
 * @todo
 */

#include "GUI/BT_MatML_TreeCtrlSorted.h"
#include "GUI/BT_MatML_MaterialFrameBase.h"


///////////////////////////////////////////////////////////////////////////
using namespace bellshire;


/// <summary>
/// Create the Main entry GUI for the Menus, the wxTreeCtrl, and all the
/// MatML Data and Info, then connects the Event Handler Functions.
/// </summary>
MaterialFrameBase::MaterialFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) 
	: wxFrame( parent, id, title, pos, size, style ), 
	m_GUI(nullptr)/*,*/
	//m_dataformat(nullptr), 
	//m_dropdata(nullptr),
	//m_droptarget(nullptr),
	//unit_dnd_buf(nullptr)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	/// Creation of Menu Bar
	m_menubar1 = new wxMenuBar( 0 );
	m_FileMenu = new wxMenu();

	m_NewMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("&New") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_NewMenuItem );
	
	m_OpenMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("&Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_OpenMenuItem );
	
	m_SaveMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("&Save") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_SaveMenuItem );
	
	m_SaveAsMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("Save As") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_SaveAsMenuItem );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_FileMenu->AppendSeparator();
	
	m_ExportMaterialMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("Export Material") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_ExportMaterialMenuItem );
	
	m_ExportMaterialBranchMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("Export Material Branch") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_ExportMaterialBranchMenuItem );
	
	m_ImportMaterialBranchMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("Import Material Branch") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_ImportMaterialBranchMenuItem );
	
	wxMenuItem* m_separator5 = m_FileMenu->AppendSeparator();
	
	m_ExitMenuItem = new wxMenuItem( m_FileMenu, wxID_ANY, wxString( wxT("E&xit") ) , wxEmptyString, wxITEM_NORMAL );
	m_FileMenu->Append( m_ExitMenuItem );
	
	m_menubar1->Append( m_FileMenu, wxT("&File") ); 
	
	m_EditMenu = new wxMenu();

	m_EditMenuPreferencesItem = new wxMenuItem( m_EditMenu, wxID_ANY, wxString( wxT("Preferences") ) , wxEmptyString, wxITEM_NORMAL );
	m_EditMenu->Append( m_EditMenuPreferencesItem );
	
	m_menubar1->Append( m_EditMenu, wxT("Edit") ); 
	
	m_ViewMenu = new wxMenu();

	m_SortClass1MenuItem = new wxMenuItem( m_ViewMenu, wxID_ANY, wxString( wxT("Perform Material Sort") ) , wxEmptyString, wxITEM_NORMAL );
	m_ViewMenu->Append( m_SortClass1MenuItem );
	
	wxMenuItem* m_separator4 = m_ViewMenu->AppendSeparator();
	
	m_IsolateMaterialBranchMenuItem = new wxMenuItem( m_ViewMenu, wxID_ANY, wxString( wxT("Isolate Material Branch") ) , wxEmptyString, wxITEM_NORMAL );
	m_ViewMenu->Append( m_IsolateMaterialBranchMenuItem );
	
	m_ExitIsolateMaterialBranchMenuItem = new wxMenuItem( m_ViewMenu, wxID_ANY, wxString( wxT("Exit Isolate Material Branch") ) , wxEmptyString, wxITEM_NORMAL );
	m_ViewMenu->Append( m_ExitIsolateMaterialBranchMenuItem );
	
	m_menubar1->Append( m_ViewMenu, wxT("&View") );  

	m_HelpMenu = new wxMenu();

	m_AboutMenuItem = new wxMenuItem(m_HelpMenu, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_HelpMenu->Append(m_AboutMenuItem);

	m_menubar1->Append(m_HelpMenu, wxT("&Help"));

	
	this->SetMenuBar( m_menubar1 );

	///Creation of Status bar
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	///Creation of Windows
	wxFlexGridSizer* fgSizer122 = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizer122->AddGrowableCol( 0 );
	fgSizer122->AddGrowableRow( 0 );
	fgSizer122->SetFlexibleDirection( wxBOTH );
	fgSizer122->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_BORDER|wxSP_LIVE_UPDATE|wxNO_BORDER );
	m_splitter1->SetSashGravity( 0.5 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MaterialFrameBase::m_splitter1OnIdle ), NULL, this );
	m_splitter1->SetMinimumPaneSize( 200 );
	
	m_panel68 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxVSCROLL );
	m_panel68->SetMinSize( wxSize( 100,500 ) );
	
	wxFlexGridSizer* fgSizer125 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer125->AddGrowableCol( 0 );
	fgSizer125->AddGrowableRow( 0 );
	fgSizer125->SetFlexibleDirection( wxBOTH );
	fgSizer125->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_MatMLTreeCtrl = new TreeCtrlSorted( m_panel68, wxID_MatMLTreeCtrl, wxDefaultPosition, wxSize( -1,-1 ), wxTR_HAS_BUTTONS|wxTR_HAS_VARIABLE_ROW_HEIGHT|wxTR_LINES_AT_ROOT|wxTR_SINGLE|wxTR_TWIST_BUTTONS|wxALWAYS_SHOW_SB|wxCLIP_CHILDREN|wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER|wxTAB_TRAVERSAL|wxVSCROLL );
	m_MatMLTreeCtrl->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));
	m_MatMLTreeCtrl->SetMinSize( wxSize( 100,500 ) );
	
	fgSizer125->Add( m_MatMLTreeCtrl, 1, wxEXPAND, 0 );

	//Set up dnd target
	m_droptarget=new MatMLDropTarget(m_MatMLTreeCtrl);
	m_MatMLTreeCtrl->SetDropTarget(m_droptarget);
	
	m_panel68->SetSizer( fgSizer125 );
	m_panel68->Layout();
	fgSizer125->Fit( m_panel68 );
	m_MultiPanel = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	wxFlexGridSizer* fgSizer124 = new wxFlexGridSizer(1, GUI::m_nclasses+1 , 0, 0);

	///Set growable columns for the MatML_GUI
	for (size_t i = 0; i < fgSizer124->GetCols(); i++)
		fgSizer124->AddGrowableCol( i );

	fgSizer124->AddGrowableRow( 0 );
	fgSizer124->SetFlexibleDirection( wxBOTH );
	fgSizer124->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	/*! Creation of all the MatML GUIs*/
	m_GUI = new GUI(m_MultiPanel);
    m_GUI->SetSizer(fgSizer124);

	m_GUI->m_Intro_GUI->Show();

	/// Layout the windows
	m_MultiPanel->SetSizer( fgSizer124 );
	m_MultiPanel->Layout();
	fgSizer124->Fit( m_MultiPanel );
	m_splitter1->SplitVertically( m_panel68, m_MultiPanel, 200 );
	fgSizer122->Add( m_splitter1, 0, wxEXPAND, 0 );
	
	this->SetSizer( fgSizer122 );
	this->Layout();
	
	/// Connect Menu and TreeCtrl Events
	SetMenuConnect();
	SetTreeCtrlConnect();

}

/// <summary>
/// 
/// </summary>
MaterialFrameBase::~MaterialFrameBase()
{
	delete m_GUI; m_GUI = nullptr;
	delete m_dropTarget; m_dropTarget = nullptr;
}

void MaterialFrameBase::SetMenuConnect() 
{
	//File Menu
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MaterialFrameBase::OnCloseSel));
	this->Connect(m_NewMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnNewSel));
	this->Connect(m_OpenMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnOpenSel));
	this->Connect(m_SaveMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnSaveSel));
	this->Connect(m_SaveAsMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnSaveAsSel));
	this->Connect(m_ExportMaterialMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnExportMaterial));
	this->Connect(m_ExportMaterialBranchMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnExportMaterialBranch));
	this->Connect(m_ImportMaterialBranchMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnImportMaterialBranch));
	this->Connect(m_ExitMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnExitSel));
	//Edit Menu
	this->Connect(m_EditMenuPreferencesItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnEditMenuPreferencesItem));
	//View Menu
	this->Connect(m_SortClass1MenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnSortMenuItem));
	this->Connect(m_IsolateMaterialBranchMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnIsolateMaterialBranch));
	this->Connect(m_ExitIsolateMaterialBranchMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnExitIsolateMaterialBranch));
	//Help Menu
	this->Connect(m_AboutMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MaterialFrameBase::OnAbout));
}

void MaterialFrameBase::SetTreeCtrlConnect()
{
	m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(MaterialFrameBase::OnElementActivated), NULL, this);
	m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_COLLAPSED, wxTreeEventHandler(MaterialFrameBase::OnElementCollapsed), NULL, this);
	m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_EXPANDED, wxTreeEventHandler(MaterialFrameBase::OnElementExpanded), NULL, this);
	m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler(MaterialFrameBase::OnMatMLItemMenu), NULL, this);
	m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(MaterialFrameBase::OnElementActivated), NULL, this);
	
}
