/**
 * @file BT_MatML_App.h
 *
 * @brief Defines the entry point for the console application.
 *
 * @author Paul McGrath
 * Contact:
 *
 */
#pragma once

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#ifdef __WIN32__
	// this is not supported by native control
#define NO_VARIABLE_HEIGHT
#endif

/// Namespace bellshire
/// <summary>
/// Contains the GUI and GUI associated classes.
/// OnInit() calls the creation of the MaterialFrame GUI
/// </summary>
/// - Application classes 
/// - MatML_GUI classes
namespace bellshire{

	/// BT_MatML_App
	/// <summary>
	/// Defines the entry point for the console application.
	/// </summary>
	class BT_MatML_App : public wxApp
	{
	public:
		BT_MatML_App();/*!<Constructor*/
		virtual ~BT_MatML_App();/*!<Destructor*/
		virtual bool OnInit();/*!<On Initiallization, creates the application window*/
		virtual int OnExit();/*!<On Exit*/
	};

	DECLARE_APP(BT_MatML_App)/*!<As per wxWidget, DECLARE_APP(appClass) in a header file to declare the wxGetApp function which returns a reference to the application object*/

}//namespace bellshire

