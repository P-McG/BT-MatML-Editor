/////////////////////////////////////////////////////////////////////////////
// Name:        PreferenceFrame.h
// Purpose:     Preferences wxWidget Frame.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __PreferenceFrame__
#define __PreferenceFrame__

#include "bellshire/GUI/BT_MatML_MaterialFrameBase.h"

namespace bellshire::GUI{

/** Implementing PreferenceFrameBase */
class PreferenceFrame : public PreferenceFrameBase
{
protected:
public:

	//configuration
	wxConfig* config;

	// Handlers for PreferenceFrameBase events.

	void OnSavePreferencesButton( wxCommandEvent& event );
	void OnCancelPreferencesButton( wxCommandEvent& event );

	void SetPreferenceControls();

	wxArrayString GetSortClasses();

	/** Constructor */
	PreferenceFrame( wxWindow* parent );
	~PreferenceFrame();
};
}//namespace bellshire

#endif // __PreferenceFrame__
