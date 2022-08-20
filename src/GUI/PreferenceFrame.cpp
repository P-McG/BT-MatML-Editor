/**
 * @file PreferenceFrame.cpp
 *
 * @brief Defines the Preference Frames.
 *
 * @author Paul McGrath
 * Contact:
 *
 */

#include "PreferenceFrame.h"
using namespace bellshire;

PreferenceFrame::PreferenceFrame( wxWindow* parent )
:
PreferenceFrameBase( parent )
{
	config = new wxConfig(wxT("BTMatML"));
	SetPreferenceControls();
}

PreferenceFrame::~PreferenceFrame()
{
	// the changes will be written in config will be back automatically
	  delete config;
}

void PreferenceFrame::OnSavePreferencesButton( wxCommandEvent& event )
{
	//transfer information from controls to config.

	bool worked=false;

	// General

	worked = config->Write(wxT("/General/MatMLDataSelection"), (const bool)m_MatMLDataSelection->GetValue());
	assert(worked);

	worked=config->Write(wxT("/General/WorkingDir"), (const wxString)m_WorkingDirPicker->GetPath());
	assert(worked);

	worked=config->Write(wxT("/General/TemplateDir"), (const wxString)m_TemplateDirPicker->GetPath());
    assert(worked);

	worked=config->Write(wxT("/General/UUIDPrefix"), (const wxString)m_UUIDPrefixTextCtrl->GetValue());
    assert(worked);

	wxArrayString strarray;
	m_ClassSortOrderListBox->GetStrings(strarray);
	for (unsigned i = 0; i < strarray.GetCount(); ++i) {
		worked = config->Write(wxT("/General/ClassSortOrder/") + wxString::Format(wxT("%i"), i), strarray[i]);
		assert(worked);
	}

	config->Flush();

	this->Show(false);
	//this->MakeModal(false);
}

void PreferenceFrame::OnCancelPreferencesButton( wxCommandEvent& event )
{
 	this->Show(false);
	SetPreferenceControls(); //set back to previous
}

void PreferenceFrame::SetPreferenceControls()
{

	wxString str;//temps
	long l;//temps
	bool b,b_dflt(false);//temps

	//General

	if (config->Read(wxT("/General/MatMLDataSelection"), &b_dflt)) {
		m_MatMLDataSelection->SetValue(b_dflt);
	}

	str.Empty();
	if ( config->Read(wxT("/General/WorkingDir"), &str) ) {
		m_WorkingDirPicker->SetPath(str);
	}

	str.Empty();
	if ( config->Read(wxT("/General/TemplateDir"), &str) ) {
		m_TemplateDirPicker->SetPath(str);
	} 

	str.Empty();
	if ( config->Read(wxT("/General/UUIDPrefix"), &str) ) {
		m_UUIDPrefixTextCtrl->SetValue(str);
	} 

	m_ClassSortOrderListBox->SetStrings(GetSortClasses());
}

wxArrayString PreferenceFrame::GetSortClasses()
{
	unsigned i(0);
	bool b(true);
	wxString str;
	wxArrayString arraystr;
	do {
		str.Empty();
		b = config->Read(wxT("/General/ClassSortOrder/") + wxString::Format(wxT("%i"), i), &str);
		if (b) {
			arraystr.push_back(str);
			i++;
		}
	} while (b);
	return arraystr;
}
