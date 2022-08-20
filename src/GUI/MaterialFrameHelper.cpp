/**
 * @file MaterialFrameHelper.cpp
 *
 * @brief
 *
 * @author Paul McGrath
 * Contact:
 *
 */
#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_MaterialFrame.h"
#include "BT_MatML_Default.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"
#include "BT_MatML_GUI.h"


void bellshire::MaterialFrame::OnClassInsertRelatedElementsButton( wxCommandEvent& event )
{
	//Get the current MatML data pointer
	wxTreeItemId CurrentItemID=m_MatMLTreeCtrl->GetSelection();
	if(!CurrentItemID.IsOk()) return;
	const MatMLTreeItemData* Current_MatML_Data((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(CurrentItemID)));


	//Get the current wxTreeCtrl selection
	wxTreeItemId MatML_DocItemId = m_MatMLTreeCtrl->GetSelection();
	wxTreeItemId MaterialItemId;

	//Find the Material for this tree branch
	while(MatML_DocItemId!=m_MatMLTreeCtrl->GetRootItem()){
	  MaterialItemId=MatML_DocItemId;
	  MatML_DocItemId=m_MatMLTreeCtrl->GetItemParent(MatML_DocItemId);
	}

	MatMLTreeItemData *MaterialItem = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(MaterialItemId));

	try{
		Material* const Element = boost::any_cast< Material* const>(MaterialItem->GetAnyMatMLDataPointer());
		try{
			if (Element == 0){return;}
			Class* const BulkDetailClass = boost::any_cast< Class* const>(Current_MatML_Data->GetAnyMatMLDataPointer());	 
			if (Element == 0){return;}
			if(BulkDetailClass->Name().present()){
				wxString TemplateName(BulkDetailClass->Name().get().c_str(),wxConvUTF8);

				LoadTemplateDoc(TemplateName);

				//wxString strTemplateFile;
				//strTemplateFile << wxT("P:\\LIBRARIES\\BT-MatML-Algorithms\\data\\Templates\\");
				//strTemplateFile << wxT("TEMPLATE-");
				//strTemplateFile << BulkDetailClass->Name().get();
				//strTemplateFile << wxT(".xml");
 			//	const char* File(strTemplateFile.mb_str());

				//try
				//{
				//  using namespace xml_schema;
				//  //Note that the schema .xsd file needs to be in the template directory
				//  template_doc=(MatML_Doc_ (File));
				//}


				//catch (const xml_schema::exception& e)
				//{

				//	wxString msg;
				//	msg << wxT("Error loading the template file: ");
				//	msg << File;


				//	wxMessageDialog *OpenDialog = new wxMessageDialog(
				//		this, msg, wxT("MatML Message"), wxOK, wxDefaultPosition);

				//	// Creates a "Message" dialog
				//	OpenDialog->ShowModal();
				//	return;
				//}

				try{
					if(template_doc.get()==0) return;
					SetupTemplateDoc(*Element);
				}
				catch (const xml_schema::exception& )
				{

					wxString msg;
					msg << wxT("Error Inserting the template: ");
					msg << TemplateName;


					wxMessageDialog *OpenDialog = new wxMessageDialog(
						this, msg, wxT("MatML Message"), wxOK, wxDefaultPosition);

					// Creates a "Message" dialog
					OpenDialog->ShowModal();
					return;
				}

				wxTreeItemId NewMaterialItemId = Material_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MatML_DocItemId,*Element,MaterialItemId);
				wxTreeItemId FoundItemId=findTreeItem(m_MatMLTreeCtrl,NewMaterialItemId,*Current_MatML_Data);
				m_MatMLTreeCtrl->Collapse(m_MatMLTreeCtrl->GetRootItem());
				m_MatMLTreeCtrl->EnsureVisible(FoundItemId);
				m_MatMLTreeCtrl->SelectItem(FoundItemId,true);
				m_MatMLTreeCtrl->Delete(MaterialItemId);

				UpdateCurrentPanel();

			}
			return;
		}
		catch(const boost::bad_any_cast &){return;}
	}
	catch(const boost::bad_any_cast &){return;}
}

void bellshire::MaterialFrame::LoadTemplateDoc(wxString& TemplateName)
{
	using namespace xml_schema;

	std::string File;

try	{

	wxString defaultDir;
	preferenceframe->config->Read(wxT("/General/TemplateDir"), &defaultDir);

	wxString strTemplateFile;
	strTemplateFile << wxT("file://");
	strTemplateFile << defaultDir;
	strTemplateFile << wxT("/TEMPLATE-");
	strTemplateFile << TemplateName;
	strTemplateFile << wxT(".xml");

	//const char* File(strTemplateFile.mb_str());

	File=_wx2std(strTemplateFile);
	wxString msg_statusbar; msg_statusbar << wxT("Loading Template ") << strTemplateFile;
    m_statusBar1->SetStatusText(msg_statusbar);

    ::std::auto_ptr< ::MatML_Doc > temp(MatML_Doc_(File));

	template_doc.reset(temp.release());

//	  //Note that the schema .xsd file needs to be in the template directory
//	  template_doc.reset();
//	  template_doc=MatML_Doc_ (_wx2std(strTemplateFile));
	}


	catch (const xml_schema::exception& )
	{

		wxString msg;
		msg << wxT("Error loading the template file: ");
		msg << _std2wx(std::string(File));


		wxMessageDialog *OpenDialog = new wxMessageDialog(
			this, msg, wxT("MatML Message"), wxOK, wxDefaultPosition);

		// Creates a "Message" dialog
		OpenDialog->ShowModal();
		return;
	}
}



void bellshire::MaterialFrame::SetupTemplateDoc(Material& Element)
{

	//Transfer the Metadata
	wxTreeItemId MetadataId(findTreeItem(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetRootItem(), wxT("*** METADATA ***"),true,true));

	Metadata::AuthorityDetails_sequence& contAuthorityDetails(template_doc->Metadata()->AuthorityDetails());
	if(!contAuthorityDetails.empty()){
		for(Metadata::AuthorityDetails_iterator iterAuthorityDetails(contAuthorityDetails.begin());
			iterAuthorityDetails!=contAuthorityDetails.end();
			++iterAuthorityDetails){
			try	{
				doc->Metadata()->AuthorityDetails().push_back(*iterAuthorityDetails);
				AuthorityDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->AuthorityDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::DataSourceDetails_sequence& contDataSourceDetails(template_doc->Metadata()->DataSourceDetails());
	if(!contDataSourceDetails.empty()){
		for(Metadata::DataSourceDetails_iterator iterDataSourceDetails(contDataSourceDetails.begin());
			iterDataSourceDetails!=contDataSourceDetails.end();
			++iterDataSourceDetails){
			try	{
				doc->Metadata()->DataSourceDetails().push_back(*iterDataSourceDetails);
				DataSourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->DataSourceDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::MeasurementTechniqueDetails_sequence& contMeasurementTechniqueDetails(template_doc->Metadata()->MeasurementTechniqueDetails());
	if(!contMeasurementTechniqueDetails.empty()){
		for( Metadata::MeasurementTechniqueDetails_iterator iterMeasurementTechniqueDetails(contMeasurementTechniqueDetails.begin());
			iterMeasurementTechniqueDetails!=contMeasurementTechniqueDetails.end();
			++iterMeasurementTechniqueDetails){

			try{
				doc->Metadata()->MeasurementTechniqueDetails().push_back(*iterMeasurementTechniqueDetails);
				MeasurementTechniqueDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->MeasurementTechniqueDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::ParameterDetails_sequence& contParameterDetails(template_doc->Metadata()->ParameterDetails());
	if(!contParameterDetails.empty()){
		for( Metadata::ParameterDetails_iterator iterParameterDetails(contParameterDetails.begin());
			iterParameterDetails!=contParameterDetails.end();
			++iterParameterDetails){

			try{
				doc->Metadata()->ParameterDetails().push_back(*iterParameterDetails);
				ParameterDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetadataId,doc->Metadata()->ParameterDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}

	}

	Metadata::PropertyDetails_sequence& contPropertyDetails(template_doc->Metadata()->PropertyDetails());
	if(!contPropertyDetails.empty()){
		for( Metadata::PropertyDetails_iterator iterPropertyDetails(contPropertyDetails.begin());
			iterPropertyDetails!=contPropertyDetails.end();
			++iterPropertyDetails){

			try{
				doc->Metadata()->PropertyDetails().push_back(*iterPropertyDetails);
				PropertyDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetadataId,doc->Metadata()->PropertyDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::SourceDetails_sequence& contSourceDetails(template_doc->Metadata()->SourceDetails());
	if(!contSourceDetails.empty()){
		for( Metadata::SourceDetails_iterator iterSourceDetails(contSourceDetails.begin());
			iterSourceDetails!=contSourceDetails.end();
			++iterSourceDetails){
			try{
				doc->Metadata()->SourceDetails().push_back(*iterSourceDetails);
				SourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetadataId,doc->Metadata()->SourceDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}


	Metadata::SpecimenDetails_sequence& contSpecimenDetails(template_doc->Metadata()->SpecimenDetails());
	if(!contSpecimenDetails.empty()){
		for( Metadata::SpecimenDetails_iterator iterSpecimenDetails(contSpecimenDetails.begin());
			iterSpecimenDetails!=contSpecimenDetails.end();
			++iterSpecimenDetails){
			try{
				doc->Metadata()->SpecimenDetails().push_back(*iterSpecimenDetails);
				SpecimenDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetadataId,doc->Metadata()->SpecimenDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::TestConditionDetails_sequence& contTestConditionDetails(template_doc->Metadata()->TestConditionDetails());
	if(!contTestConditionDetails.empty()){
		for( Metadata::TestConditionDetails_iterator iterTestConditionDetails(contTestConditionDetails.begin());
			iterTestConditionDetails!=contTestConditionDetails.end();
			++iterTestConditionDetails){
			try{
				doc->Metadata()->TestConditionDetails().push_back(*iterTestConditionDetails);
				TestConditionDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetadataId,doc->Metadata()->TestConditionDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	//Copy the PropertyData	(if not already there) into the BulkDetails
	BulkDetails::PropertyData_sequence& contTemplatePropertyData(template_doc->Material().front().BulkDetails().PropertyData());
	if(!contTemplatePropertyData.empty()){
		for(BulkDetails::PropertyData_iterator iterTemplate(contTemplatePropertyData.begin());
			iterTemplate!=contTemplatePropertyData.end();
			++iterTemplate){
			bool Present=false;
			BulkDetails::PropertyData_sequence& cont(Element.BulkDetails().PropertyData());
			if(!cont.empty()){
				for(BulkDetails::PropertyData_iterator iter(cont.begin());
					iter!=cont.end();
					++iter){
						if(iterTemplate->property()==iter->property()) {Present=true;break;}
				}
			}
			if(!Present) cont.push_back(*iterTemplate);
		}
	}

	//Copy the ProcessingDetails (if not already there) into the BulkDetails
	BulkDetails::ProcessingDetails_sequence& contTemplateProcessingDetails(template_doc->Material().front().BulkDetails().ProcessingDetails());
	if(!contTemplateProcessingDetails.empty()){
		for(BulkDetails::ProcessingDetails_iterator iterTemplate(contTemplateProcessingDetails.begin());
			iterTemplate!=contTemplateProcessingDetails.end();
			++iterTemplate){
			bool Present=false;
			BulkDetails::ProcessingDetails_sequence& cont(Element.BulkDetails().ProcessingDetails());
			if(!cont.empty()){
				for(BulkDetails::ProcessingDetails_iterator iter(cont.begin());
					iter!=cont.end();
					++iter){
						if(iterTemplate->Name()==iter->Name()) {Present=true;break;}
				}
			}
			if(!Present) cont.push_back(*iterTemplate);
		}
	}


	//Add or locate ComponentDetails with the Same Class as the template.

	//loop throught the template's ComponentDetails
	Material::ComponentDetails_sequence& contTemplateComponentDetails(template_doc->Material().front().ComponentDetails());
	if(!contTemplateComponentDetails.empty()){
		for(Material::ComponentDetails_iterator iterTemplateComponentDetails(contTemplateComponentDetails.begin());
			iterTemplateComponentDetails!=contTemplateComponentDetails.end();
			++iterTemplateComponentDetails){

			bool Present=false;

			//loop throught the Materials' ComponentDetails
			Material::ComponentDetails_sequence& contComponentDetails(Element.ComponentDetails());
			Material::ComponentDetails_iterator iterComponentDetails;

			if(!contComponentDetails.empty()){
				for(iterComponentDetails=contComponentDetails.begin();
					iterComponentDetails!=contComponentDetails.end();
					++iterComponentDetails){

					//Loop Through the Materials' ComponentDetails classes.
					ComponentDetails::Class_sequence& contClass(iterComponentDetails->Class());
					if(!contClass.empty() && !iterTemplateComponentDetails->Class().empty()){
						for(ComponentDetails::Class_iterator iterClass(contClass.begin());
							iterClass!=contClass.end();
							++iterClass){
							if(iterClass->Name()==iterTemplateComponentDetails->Class().front().Name()) {
								CopyTemplateProperty(*iterComponentDetails, *iterTemplateComponentDetails);
								CopyTemplateProcessingDetails(*iterComponentDetails, *iterTemplateComponentDetails);
								Present=true;
								break;   //for Materials' ComponentDetails Class loop
							}
						}
					}
					else if(iterTemplateComponentDetails->Class().empty()){
						CopyTemplateProperty(*iterComponentDetails, *iterTemplateComponentDetails);
						CopyTemplateProcessingDetails(*iterComponentDetails, *iterTemplateComponentDetails);
						Present=true;
					}
				}
			}
			if(!Present){

				contComponentDetails.push_back(*iterTemplateComponentDetails);
				iterComponentDetails=contComponentDetails.end()-1;
				//below maybe redundant
				CopyTemplateProperty(*iterComponentDetails, *iterTemplateComponentDetails);
				CopyTemplateProcessingDetails(*iterComponentDetails, *iterTemplateComponentDetails);
			}
		}
	}
}

void bellshire::MaterialFrame::CopyTemplateMetadata()
{

	//Transfer the Metadata
	wxTreeItemId MetadataId(findTreeItem(m_MatMLTreeCtrl, m_MatMLTreeCtrl->GetRootItem(), wxT("*** METADATA ***"),true,true));

	Metadata::AuthorityDetails_sequence& contAuthorityDetails(template_doc->Metadata()->AuthorityDetails());
	if(!contAuthorityDetails.empty()){
		for(Metadata::AuthorityDetails_iterator iterAuthorityDetails(contAuthorityDetails.begin());
			iterAuthorityDetails!=contAuthorityDetails.end();
			++iterAuthorityDetails){
			try	{
				doc->Metadata()->AuthorityDetails().push_back(*iterAuthorityDetails);
				AuthorityDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->AuthorityDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::DataSourceDetails_sequence& contDataSourceDetails(template_doc->Metadata()->DataSourceDetails());
	if(!contDataSourceDetails.empty()){
		for(Metadata::DataSourceDetails_iterator iterDataSourceDetails(contDataSourceDetails.begin());
			iterDataSourceDetails!=contDataSourceDetails.end();
			++iterDataSourceDetails){
			try	{
				doc->Metadata()->DataSourceDetails().push_back(*iterDataSourceDetails);
				DataSourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->DataSourceDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::MeasurementTechniqueDetails_sequence& contMeasurementTechniqueDetails(template_doc->Metadata()->MeasurementTechniqueDetails());
	if(!contMeasurementTechniqueDetails.empty()){
		for( Metadata::MeasurementTechniqueDetails_iterator iterMeasurementTechniqueDetails(contMeasurementTechniqueDetails.begin());
			iterMeasurementTechniqueDetails!=contMeasurementTechniqueDetails.end();
			++iterMeasurementTechniqueDetails){

			try{
				doc->Metadata()->MeasurementTechniqueDetails().push_back(*iterMeasurementTechniqueDetails);
				MeasurementTechniqueDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->MeasurementTechniqueDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::ParameterDetails_sequence& contParameterDetails(template_doc->Metadata()->ParameterDetails());
	if(!contParameterDetails.empty()){
		for( Metadata::ParameterDetails_iterator iterParameterDetails(contParameterDetails.begin());
			iterParameterDetails!=contParameterDetails.end();
			++iterParameterDetails){

			try{
				doc->Metadata()->ParameterDetails().push_back(*iterParameterDetails);
				ParameterDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->ParameterDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}

	}

	Metadata::PropertyDetails_sequence& contPropertyDetails(template_doc->Metadata()->PropertyDetails());
	if(!contPropertyDetails.empty()){
		for( Metadata::PropertyDetails_iterator iterPropertyDetails(contPropertyDetails.begin());
			iterPropertyDetails!=contPropertyDetails.end();
			++iterPropertyDetails){

			try{
				doc->Metadata()->PropertyDetails().push_back(*iterPropertyDetails);
				PropertyDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->PropertyDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::SourceDetails_sequence& contSourceDetails(template_doc->Metadata()->SourceDetails());
	if(!contSourceDetails.empty()){
		for( Metadata::SourceDetails_iterator iterSourceDetails(contSourceDetails.begin());
			iterSourceDetails!=contSourceDetails.end();
			++iterSourceDetails){
			try{
				doc->Metadata()->SourceDetails().push_back(*iterSourceDetails);
				SourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->SourceDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}


	Metadata::SpecimenDetails_sequence& contSpecimenDetails(template_doc->Metadata()->SpecimenDetails());
	if(!contSpecimenDetails.empty()){
		for( Metadata::SpecimenDetails_iterator iterSpecimenDetails(contSpecimenDetails.begin());
			iterSpecimenDetails!=contSpecimenDetails.end();
			++iterSpecimenDetails){
			try{
				doc->Metadata()->SpecimenDetails().push_back(*iterSpecimenDetails);
				SpecimenDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->SpecimenDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}

	Metadata::TestConditionDetails_sequence& contTestConditionDetails(template_doc->Metadata()->TestConditionDetails());
	if(!contTestConditionDetails.empty()){
		for( Metadata::TestConditionDetails_iterator iterTestConditionDetails(contTestConditionDetails.begin());
			iterTestConditionDetails!=contTestConditionDetails.end();
			++iterTestConditionDetails){
			try{
				doc->Metadata()->TestConditionDetails().push_back(*iterTestConditionDetails);
				TestConditionDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetadataId,doc->Metadata()->TestConditionDetails().back(),wxTreeItemId());
			}
			catch(...){}//tried this exception. Didn't work "const xml_schema::xsi_already_in_use&"
		}
	}
}


void bellshire::MaterialFrame::CopyTemplateProperty(ComponentDetails& Element, ComponentDetails& TemplateElement)
{
	//Copy the PropertyData (if not already there) into the ComponentDetail
	ComponentDetails::PropertyData_sequence& contTemplatePropertyData(TemplateElement.PropertyData());
	if(!contTemplatePropertyData.empty()){
		for(ComponentDetails::PropertyData_iterator iterTemplate(contTemplatePropertyData.begin());
			iterTemplate!=contTemplatePropertyData.end();
			++iterTemplate){
			bool Present=false;
			ComponentDetails::PropertyData_sequence& cont(Element.PropertyData());
			if(!cont.empty()){
				for(ComponentDetails::PropertyData_iterator iter(cont.begin());
					iter!=cont.end();
					++iter){
						if(iterTemplate->property()==iter->property()) {Present=true;break;}
				}
			}
			if(!Present) cont.push_back(*iterTemplate);
		}
	}
}

void bellshire::MaterialFrame::CopyTemplateProcessingDetails(ComponentDetails& Element, ComponentDetails& TemplateElement)
{

	//Copy the ProcessingDetails (if not already there) into the ComponentDetail
	ComponentDetails::ProcessingDetails_sequence& contTemplateProcessingDetails(TemplateElement.ProcessingDetails());
	if(!contTemplateProcessingDetails.empty()){
		for(ComponentDetails::ProcessingDetails_iterator iterTemplate(contTemplateProcessingDetails.begin());
			iterTemplate!=contTemplateProcessingDetails.end();
			++iterTemplate){
			bool Present=false;
			ComponentDetails::ProcessingDetails_sequence& cont(Element.ProcessingDetails());
			if(!cont.empty()){
				for(ComponentDetails::ProcessingDetails_iterator iter(cont.begin());
					iter!=cont.end();
					++iter){
					if(iterTemplate->Name()==iter->Name()) {Present=true;break;}
				}
			}
			if(!Present) cont.push_back(*iterTemplate);
		}
	}
}

void bellshire::MaterialFrame::CopyTemplateParameterValue(ProcessingDetails& Element)
{
	wxString str;

	try{
		ProcessingDetails::ParameterValue_sequence& contTemplate(
			template_doc->Material().begin()->BulkDetails().ProcessingDetails().begin()->ParameterValue());
		ProcessingDetails::ParameterValue_iterator iterTemplate;
		if(!contTemplate.empty()){
			for(iterTemplate=contTemplate.begin();iterTemplate!=contTemplate.end();++iterTemplate){

				bool found=false;

				ProcessingDetails::ParameterValue_sequence& cont(Element.ParameterValue());
				ProcessingDetails::ParameterValue_iterator iter;
				if(!cont.empty()){
					for(iter=cont.begin();iter!=cont.end();++iter){
						//See if currently existing
						if(found=(iterTemplate->parameter()==iter->parameter())) break;
					}
				}

				//Copy if not present
				if(!found) cont.push_back(*iterTemplate);
			}
		}
	}
	catch (const xml_schema::exception& )
	{

		wxString msg;
		msg << wxT("Error Inserting the template's ParameterValue: ");

		wxMessageDialog *OpenDialog = new wxMessageDialog(
			this, msg, wxT("MatML Message"), wxOK, wxDefaultPosition);

		// Creates a "Message" dialog
		OpenDialog->ShowModal();
		return;
	}
}








