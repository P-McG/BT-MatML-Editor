/**
 * @file MaterialFrame.cpp
 *
 * @brief Declares the controls for the material frame
 *
 * @author Paul McGrath
 * Contact:
 *
 * Contains:
 * Setup[MatML Element] functions
 * On[parent]past[child]
 * OnDelete[parent]
 */
//#define _HAS_STD_BYTE 0
#include <pch.h>
#include "BT_MatML_Editor-Config.h"

#include "wx/settings.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"
#include <wx/file.h>
#include "wx/aboutdlg.h"


#include <iostream>
#include <fstream>
#include <time.h>
#include <limits>
#include <algorithm>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include <list>

#include "bellshire/utilities/Uuid-Utility.h"

#include "bellshire/utilities/StringStream.h"
#include "fcopy.h"
#include "bellshire/matml31.hxx"

#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MaterialFrame.h"
#include "bellshire/BT_MatML_Default.h"
#include "bellshire/GUI/HTMLFrame.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/utilities/BT_MatML_Utilities_GUI.h"
#include "bellshire/GUI/utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"

using namespace ::bellshire::GUI;

MaterialFrame::MaterialFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    :MaterialFrameBase(parent, id, title, pos, size, style)
{
    //htmlframe=new HTMLFrame(this);/*! Creates the HTML Frame Window */
    preferenceframe=new PreferenceFrame(this);/*! Creates the Preference Frame Window */
}

MaterialFrame::~MaterialFrame()
{
    //delete htmlframe;/*! Delete HTML Frame Window*/
    delete preferenceframe;/*! Delete Preference Frame Window*/

}

/// Re-Estabilished the wxTreeCtrl Sizer.
/// <summary>
/// </summary>
/// <returns></returns>
bool MaterialFrame::reEstabilishTreeCtrlSizer()
{

     wxFlexGridSizer* fgSizer;
     fgSizer = new wxFlexGridSizer( 2, 2, 0, 0 );/*! Create new Sizer*/
     fgSizer->AddGrowableCol( 0 );
     fgSizer->AddGrowableRow( 0 );
     fgSizer->SetFlexibleDirection( wxBOTH );
     fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

     fgSizer->Add( GetMatMLTreeCtrl(), 1, wxEXPAND, 0);/*! Add member wxTreeCtrl to sizer*/

     GetPanel68()->SetSizer(fgSizer);/*! Set main member panel sizer*/
     GetPanel68()->Layout();
     GetMatMLTreeCtrl()->SetSize(GetMatMLTreeCtrl()->GetClientSize());/*! Set member wxTreeCtrl size*/

     return true;
}

/// <summary>
/// Sets the Connection of the wxTreeCtrl event handler from an instant of a wxTreeCtrl to events associated functions
/// These calls overwrite the MaterialFrameBase class calls.
/// </summary>
void MaterialFrame::SetTreeCtrlConnect()
{
    /* SUSPECT TO BE DEAD CODE; MATERIALFRAMEBASE::SetTreeCtrlConnect IS ACTIVE CODE */
    GetMatMLTreeCtrl()->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(bellshire::GUI::MaterialFrame::OnElementActivated), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActived*/
    GetMatMLTreeCtrl()->Connect(wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler(bellshire::GUI::MaterialFrame::OnMatMLItemMenu), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnMatMLItemMenu*/
    GetMatMLTreeCtrl()->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(bellshire::GUI::MaterialFrame::OnElementActivated), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActivated*/
    GetMatMLTreeCtrl()->Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(bellshire::GUI::MaterialFrame::OnLeftDown), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActivated*/
   // m_MatMLTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler(bellshire::GUI::MaterialFrame::OnRightDown), NULL, this);/*! Connection of the wxTreeCtrl event handler to fn OnElementActivated*/
}

/// On Close Selection
/// <summary>
/// Event Handler Function for Closing MatML_Doc
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnCloseSel( wxCloseEvent& event )
{
    wxString message;
    message << wxT("Would you like to Save?");
    wxMessageDialog SaveDialog(this,message,wxT("MatML Closing"),wxYES_NO|wxYES_DEFAULT|wxICON_EXCLAMATION);/*! Create Save wxDialog*/
    if(SaveDialog.ShowModal()==wxID_YES){

        wxString CurrentDocPath(""), RecentDocPath("");
        if (!preferenceframe->config->Read(wxT("/General/CurrentDocPath"), &CurrentDocPath))
            Warning(::std::string("Configuration read failed"));
        
        RecentDocPath=CurrentDocPath;
        if(!preferenceframe->config->Write(wxT("/General/RecentDocPath"), RecentDocPath))
            Warning(::std::string("Configuration read failed"));//Copy to recent doc path

        xml_schema::namespace_infomap map;/*! Prepare namespace mapping */
        map[""].schema = "matml31.xsd";/*! Prepare schema location information.*/

        ofstream outFile(CurrentDocPath.mb_str(), ios::trunc);/*! Write file out. */

        if (!outFile) exit(-1);/*! If there were any errors on opening? Exit.*/

        doc = std::make_shared< ::MatML_Doc >();
        MatML_Doc_(outFile, *doc, map);/*! Parse MatML data*/

        outFile.close();/*! Close files */
        

    }
    GetMatMLTreeCtrl()->DeleteAllItems();/*! Delete all Items in MatML wxTreeCtrl */
    this->Destroy();/*! Destroy MaterialFrame*/

}

/// On new selections.
/// <summary>
/// Event Handler Function for new MatML_Doc
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnNewSel( wxCommandEvent& event )
{

    if(doc){
        wxMessageDialog SaveDialog(this,wxT("Would you like to Save?"),wxT("MatML Closing"),wxYES_NO|wxYES_DEFAULT|wxICON_EXCLAMATION);/*! Create Save wxDialog*/
        if(SaveDialog.ShowModal()==wxID_YES) OnSaveSel(event);
    }

    doc.reset(new Default<MatML_Doc>);/*! Reset the MatML pointer to a new Default MatML Document */

    GetMatMLTreeCtrl()->DeleteAllItems();/*! Delete all Items in MatML wxTreeCtrl */
    m_MatMLItemToCopy=nullptr;/*! reset MatML Item to copy to nullptr */

    
    MatML_Doc_GUI::TraverseMatMLTree(doc.get(),
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI(m_MatMLTreeCtrl)
    );/*! Set the MatML Elements to the wxTreeCtrl.*/

    GetGUI()->SetEvtHandlerVar(GetMatMLTreeCtrl(), doc.get());/*! Set the Event Handler's Variables for the MatML_GUIs.*/

    /// reset the path of our current open file
    wxString str(wxT("")), CurrentDocPath;
    if(!preferenceframe->config->Read(wxT("/General/WorkingDir"), &str)) 
        Warning(::std::string("Configuration read failed"));
    CurrentDocPath << str << wxT("/Untitled.xml");

    if(!preferenceframe->config->Write(wxT("/General/CurrentDocPath"), (const wxString)CurrentDocPath))
        Warning(::std::string("Configuration write failed"));;

    /// Set the Title to reflect the file open
    SetTitle(_("Edit - Untitled.xml *"));

    GetGUI()->HideAllPanels();/*! Hide all the MatML GUI panels*/
    GetGUI()->m_MatML_Doc_GUI->ShowGUI(true);/*! Show the Metadata panel*/
    this->Layout();
    GetGUI()->m_MatML_Doc_GUI->GetGUI()->Raise();

}

/// <summary>
/// On Open Selection
/// Event Handler Function for opening a MatML_Doc
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnOpenSel( wxCommandEvent& event )
{

    if(doc.get()!=NULL){
        wxString message,title;
        message << wxT("Would you like to Save?");

        wxMessageDialog SaveDialog(this,message,title,wxYES_NO|wxYES_DEFAULT|wxICON_EXCLAMATION);
        if(SaveDialog.ShowModal()==wxID_YES) OnSaveSel(event);
    }


    // TODO: Implement OnOpenSel
    wxString defaultDir("");
    if(!preferenceframe->config->Read(wxT("/General/WorkingDir"), &defaultDir))
        Warning(::std::string("Configuration read failed"));

    wxFileDialog OpenDialog(
        this, _("Choose a file to open"),defaultDir, wxEmptyString,
        _("MatML files (*.xml)|*.xml"),
        wxFD_OPEN, wxDefaultPosition);

    // Creates a "open file" dialog with MatML file types
    if (OpenDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
    {
        GetMatMLTreeCtrl()->DeleteAllItems();
        m_MatMLItemToCopy=nullptr;//NULL
        
        if (!preferenceframe->config->Write(wxT("/General/CurrentDocPath"), (const wxString)OpenDialog.GetPath()))
            Warning(::std::string("Configuration write failed"));
        
        // Sets our current document to the file the user selected
        LoadFile(); //Opens that file

        // Set the Title to reflect the  file open
        SetTitle(wxString(wxT("MatML Document - ")) << OpenDialog.GetFilename());

        //Set up the MatML Tree
        wxTreeItemId selItemId = m_MatMLTreeCtrl->GetRootItem();
        if (selItemId.IsOk()) {
            m_MatMLTreeCtrl->SelectItem(selItemId);
            m_MatMLTreeCtrl->SortChildren(selItemId);
        }
        m_MultiPanel->Layout();
        m_GUI->m_MatML_Doc_GUI->ShowGUI(true);
        

    }
}

/// <summary>
/// On Save Selection
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnSaveSel( wxCommandEvent& event )
{
    // TODO: Implement OnSaveSel
    // Save to the already-set path for the document

    //Temp Storage
    ::stack<TreeCtrlSorted*> tempTreeCtrlStack;

    //Store Data
    //Make sure saving with the full TreeCtrl.
    if(!m_MatMLTreeCtrlStack.empty()){

        //DONT DELETE!!! WILL BE RESTORED LATER.
 //       m_MatMLTreeCtrl->DeleteAllItems();
 //       delete m_MatMLTreeCtrl;

        while(!m_MatMLTreeCtrlStack.empty()){
            tempTreeCtrlStack.push(m_MatMLTreeCtrl);
            m_MatMLTreeCtrl=m_MatMLTreeCtrlStack.top();
            m_MatMLTreeCtrlStack.pop();
        }
    }

    // Prepare namespace mapping and schema location information.
    //
    xml_schema::namespace_infomap map;
    map[""].schema = "matml31.xsd";

    // Write it out.
    wxString CurrentDocPath("/Untitled.xml");//temps
    if(!preferenceframe->config->Read(wxT("/General/CurrentDocPath"), &CurrentDocPath))
        Warning(::std::string("Configuration read failed"));

    ofstream outFile (CurrentDocPath.mb_str(),ios::trunc);
    if (!outFile) exit(-1);// were there any errors on opening?

    MatML_Doc_ (outFile, *doc, map);

    outFile.close();

    //Restore Data
    //Make sure saving with the full TreeCtrl.
    if(!tempTreeCtrlStack.empty()){

        while(!tempTreeCtrlStack.empty()){
            m_MatMLTreeCtrlStack.push(m_MatMLTreeCtrl);
            m_MatMLTreeCtrl=tempTreeCtrlStack.top();
            tempTreeCtrlStack.pop();
        }
    }

}

/// <summary>
/// On SaveAs Selection
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnSaveAsSel( wxCommandEvent& event )
{

    //Temp Storage
    ::stack<TreeCtrlSorted*> tempTreeCtrlStack;

    //Store Data
    //Make sure saving with the full TreeCtrl.
    if(!m_MatMLTreeCtrlStack.empty()){

        //DONT DELETE!!! WILL BE RESTORED LATER.
 //       m_MatMLTreeCtrl->DeleteAllItems();
 //       delete m_MatMLTreeCtrl;

        while(!m_MatMLTreeCtrlStack.empty()){
            tempTreeCtrlStack.push(m_MatMLTreeCtrl);
            m_MatMLTreeCtrl=m_MatMLTreeCtrlStack.top();
            m_MatMLTreeCtrlStack.pop();
        }
    }

    // TODO: Implement OnSaveAsSel
    wxString CurrentDocPath;
    if(!preferenceframe->config->Read(wxT("/General/WorkingDir"), &CurrentDocPath))
        Warning(::std::string("Configuration read failed"));

    wxFileDialog SaveDialog(
        this, _("Save File As _?"), CurrentDocPath, wxEmptyString,
        _("MatML files (*.xml)|*.xml"),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    // Creates a Save Dialog with MatML file types
    if (SaveDialog.ShowModal() == wxID_OK) // If the user clicked "OK"
    {
        CurrentDocPath = SaveDialog.GetPath();
        if(!preferenceframe->config->Write(wxT("/General/CurrentDocPath"), (const wxString) CurrentDocPath))
            Warning(::std::string("Configuration write failed"));

        // set the path of our current document to the file the user chose to save under
        // Save the file to the selected path
        // Prepare namespace mapping and schema location information.
        //
        xml_schema::namespace_infomap map;
        map[""].schema = "matml31.xsd";

        // Write it out.

        ofstream outFile (CurrentDocPath.mb_str(),ios::trunc);
        if (!outFile) exit(-1);// were there any errors on opening?



        MatML_Doc_ (outFile, *doc, map);

        outFile.close();

        // Set the Title to reflect the file open
        SetTitle(wxString(wxT("Edit - ")) << SaveDialog.GetFilename());
    }

    //Restore Data
    //Make sure saving with the full TreeCtrl.
    if(!tempTreeCtrlStack.empty()){

        while(!tempTreeCtrlStack.empty()){
            m_MatMLTreeCtrlStack.push(m_MatMLTreeCtrl);
            m_MatMLTreeCtrl=tempTreeCtrlStack.top();
            tempTreeCtrlStack.pop();
        }
    }
}

/// <summary>
/// On Export Material Selection
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnExportMaterial( wxCommandEvent& event )
{
    // TODO: Implement OnSaveAsSel
    wxString defaultDir;
    if(!preferenceframe->config->Read(wxT("/General/WorkingDir"), &defaultDir))
        Warning(::std::string("Configuration read failed"));

    wxFileDialog SaveDialog(
        this, _("Save Material in File As _?"),defaultDir, wxEmptyString,
        _("MatML files (*.xml)|*.xml"),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    // Creates a Save Dialog with MatML file types
    if (SaveDialog.ShowModal() == wxID_OK){// If the user clicked "OK"
        wxString filename(SaveDialog.GetPath());
        OnExportMaterial(filename);
    }
    return;
}

/// <summary>
/// 
/// </summary>
/// <param name="filename"></param>
void MaterialFrame::OnExportMaterial(wxString& filename)
{
    // set the path of our current document to the file the user chose to save under
    // Save the file to the selected path
    // Prepare namespace mapping and schema location information.
    //
    xml_schema::namespace_infomap map;
    map[""].schema = "matml31.xsd";

    // Write it out.
    //char* tmpfilename=(char*)filename.c_str();
    std::string tmpfilename=_wx2std(filename);

    wxString msg_statusbar(wxT("Exporting ")); msg_statusbar << _std2wx(tmpfilename);
    m_statusBar1->SetStatusText(msg_statusbar);

    ofstream outFile (tmpfilename.c_str(),ios::trunc);
    if (!outFile) exit(-1);// were there any errors on opening?
        wxString str;


    //Get the current MatML data pointer
    wxTreeItemId CurrentItemID=m_MatMLTreeCtrl->GetSelection();
    const MatMLTreeItemData* Current_MatML_Data((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(CurrentItemID)));

    //Get the current wxTreeCtrl selection
    wxTreeItemId MatML_DocItemId = m_MatMLTreeCtrl->GetSelection();
    if(!MatML_DocItemId.IsOk()) return;
    wxTreeItemId MaterialItemId;


    //Find the Material for this tree branch
    while(MatML_DocItemId!=m_MatMLTreeCtrl->GetRootItem()){
      MaterialItemId=MatML_DocItemId;
      MatML_DocItemId=m_MatMLTreeCtrl->GetItemParent(MatML_DocItemId);
    }

    MatMLTreeItemData *MaterialItem = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(MaterialItemId));
    MatMLTreeItemData *Item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(MatML_DocItemId));

    try{
        Material* const Element = boost::any_cast< Material* const>(MaterialItem->GetAnyMatMLDataPointer());


        MatML_Doc ExportDoc;
        MatML_Doc::Material_sequence& ms (ExportDoc.Material());

        ms.push_back(*Element);

        //Remove ComponentDetails->Class->ParentMaterial to prevent idrefs not matching
        Material::ComponentDetails_sequence& compcont(ms.back().ComponentDetails());
        if(!compcont.empty()){
            Material::ComponentDetails_iterator compiter(compcont.begin());
            for(;compiter!=compcont.end();++compiter){
                ComponentDetails::Class_sequence& classcont(compiter->Class());
                if(!classcont.empty()){
                    ComponentDetails::Class_iterator classiter(classcont.begin());
                    do{
                        if(!classiter->ParentMaterial().empty()) classiter=classcont.erase(classiter);
                        else ++classiter;
                    }while(classiter!=classcont.end());
                }
            }
        }

        ExportDoc.Metadata(doc->Metadata().get());

        MatML_Doc_ (outFile, ExportDoc, map);

     }
    catch(const boost::bad_any_cast &){return;}

    outFile.close();
}

/// <summary>
/// On Export Material Branch Selection
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnExportMaterialBranch( wxCommandEvent& event )
{
    // TODO: Implement OnSaveAsSel
    wxString defaultDir;
    preferenceframe->config->Read(wxT("/General/WorkingDir"), &defaultDir);

    wxFileDialog *SaveDialog = new wxFileDialog(
        this, _("Save Material in File As _?"), defaultDir, wxEmptyString,
        _("MatML files (*.xml)|*.xml"),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    // Creates a Save Dialog with MatML file types
    if (SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
    {
        wxString filename(SaveDialog->GetPath());
        OnExportMaterialBranch(filename);
    }
    return;
}

/// <summary>
/// On Export of Material Branch
/// Event Handler Function
/// </summary>
/// <param name="filename"></param>
void MaterialFrame::OnExportMaterialBranch(wxString& filename)
{
        // set the path of our current document to the file the user chose to save under
        // Save the file to the selected path
        // Prepare namespace mapping and schema location information.
        //
        xml_schema::namespace_infomap map;
        map[""].schema = "matml31.xsd";

        // Write it out.

        ofstream outFile (filename.mb_str(),ios::trunc);
        if (!outFile) exit(-1);// were there any errors on opening?
            wxString str;


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
        MatMLTreeItemData *Item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(MatML_DocItemId));

        try{
            const auto& Element = boost::any_cast< observer_ptr<Material>>(MaterialItem->GetAnyMatMLDataPointer());

            ::vector<observer_ptr<Material>> mps;
            CollectBranchMaterials(doc.get(), Element, mps);

            MatML_Doc ExportDoc;
            for (::vector<observer_ptr<Material>>::iterator iter = mps.begin(); iter != mps.end(); ++iter) {
                const observer_ptr<Material> material{*iter};
                ExportDoc.Material().push_back(*material);
            }

            ExportDoc.Metadata(doc->Metadata().get());

            //Strip the dangling ComponentDetails->Class->ParentMaterial->idref
            MatML_Doc::Material_sequence& matcont(ExportDoc.Material());
            MatML_Doc::Material_iterator matiter1(matcont.begin());
            for(;matiter1!=matcont.end();++matiter1){
                if(matiter1->ComponentDetails().empty()) continue;
                Material::ComponentDetails_sequence& compcont(matiter1->ComponentDetails());
                Material::ComponentDetails_iterator compiter(compcont.begin());
                for(;compiter!=compcont.end();++compiter){
                    if(compiter->Class().empty()) continue;
                    ComponentDetails::Class_sequence& classcont(compiter->Class());
                    ComponentDetails::Class_iterator classiter(classcont.begin());
                    do{
                        if(classiter->ParentMaterial().empty()) {++classiter; continue;}
                        MatML_Doc::Material_iterator matiter2(matcont.begin());
                        bool found(false);
                        for(;matiter2!=matcont.end();++matiter2)
                            //can't use pointers for this comparision due to
                            //the CollectBranchMaterials(Element,ms) copying the elements changing the
                            //memory location and breaking the link.
                            if(matiter2->id().present()
                                && matiter2->id()->compare(classiter->ParentMaterial().front().id().c_str())==0) {found=true;break;}
                        if(!found) classiter=classcont.erase(classiter);
                        else ++classiter;
                    }while(classiter!=classcont.end());
                }
            }

            //Save the file out.
            MatML_Doc_ (outFile, ExportDoc, map);

         }
        catch(const boost::bad_any_cast &){return;}

        outFile.close();
}

/// <summary>
/// On Import of Material Branch
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnImportMaterialBranch( wxCommandEvent& event )
{
    // TODO: Implement OnImportSel
    wxString defaultDir;
    preferenceframe->config->Read(wxT("/General/WorkingDir"), &defaultDir);

    wxFileDialog OpenDialog(
        this, _("Choose a file to Import"),defaultDir, wxEmptyString,
        _("MatML files (*.xml)|*.xml"),
        wxFD_OPEN, wxDefaultPosition);

    // Creates a "open file" dialog with MatML file types
    if (OpenDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
    {

        // Sets our current document to the file the user selected
        ImportFile(OpenDialog.GetPath().mb_str()); //Opens that file

        m_MultiPanel->Layout();
        m_GUI->m_MatML_Doc_GUI->ShowGUI(true);
    }
}

/// <summary>
/// On Isolate to the Material Branch
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnIsolateMaterialBranch( wxCommandEvent& event )
{
    IsolateMaterialBranch();
}



/// <summary>
/// Isolate to the Material Branch
/// This function:
/// - finds selected branch's MatML materials
/// - Hides the TreeCtrl item if its MatML Data is in the branch.
/// </summary>
void MaterialFrame::IsolateMaterialBranch()
{
    wxString str;

    //Get the current MatML data pointer
    wxTreeItemId CurrentItemId = m_MatMLTreeCtrl->GetSelection();
    if (!CurrentItemId.IsOk() || CurrentItemId == m_MatMLTreeCtrl->GetRootItem()) return;
    MatMLTreeItemData* Current_MatML_Data((MatMLTreeItemData*)(m_MatMLTreeCtrl->GetItemData(CurrentItemId)));

    //Get the current wxTreeCtrl selection
    wxTreeItemId MatML_DocItemId = m_MatMLTreeCtrl->GetSelection();
    wxTreeItemId CurrentMaterialItemId;

    //Loop to find the Material for the selection on this tree branch
    while (MatML_DocItemId != m_MatMLTreeCtrl->GetRootItem()) {
        CurrentMaterialItemId = MatML_DocItemId;
        MatML_DocItemId = m_MatMLTreeCtrl->GetItemParent(MatML_DocItemId);
    }

    //Need this to locate the MatML Data in the new tree.
    auto CurrentMaterial(GetMatML<Material>(m_MatMLTreeCtrl, &CurrentMaterialItemId));

     //gather the MatML branch
    std::vector<observer_ptr<Material>> ms;
    CollectBranchMaterials(doc.get(), CurrentMaterial, ms);

    //Loop over the TreeCtrl's materials and see if in the MatML branch
    wxTreeItemIdValue cookie;
    unsigned n(m_MatMLTreeCtrl->GetChildrenCount(MatML_DocItemId, false));
    wxTreeItemId itemId=m_MatMLTreeCtrl->GetFirstChild(MatML_DocItemId, cookie);
    do {
        wxTreeItemId nextitemId = m_MatMLTreeCtrl->GetNextChild(MatML_DocItemId, cookie);
        auto material{ GetMatML<Material>(m_MatMLTreeCtrl, &itemId) };
        if (material) {
            std::vector<observer_ptr<Material>>::iterator it;
            const auto mat0 ( material);
            auto p = [material](observer_ptr<Material> m) {return material==m; };
            it = std::find_if(ms.begin(), ms.end(), p);
            if (it == ms.end()) 
                m_MatMLTreeCtrl->Delete(itemId);//Delete TreeCtrl's Material if it is not in the MatML branch.
        }
        itemId = nextitemId;
    } while (itemId.IsOk());


    //Arrange the wxTreeCtrl to see and select the previous material
    const wxTreeItemId BranchCurrentItemId=Utilities::MatMLtoTreeCtrl(m_MatMLTreeCtrl, CurrentMaterial);
    m_MatMLTreeCtrl->CollapseAll();
    m_MatMLTreeCtrl->SelectItem(BranchCurrentItemId);
    m_MatMLTreeCtrl->EnsureVisible(BranchCurrentItemId);

    m_statusBar1->SetStatusText(wxT(""));
    UpdateCurrentPanel();
    m_splitter1->Refresh();
    m_splitter1->Update();
}


/// <summary>
/// On Exit Isolate of the Material Branch
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnExitIsolateMaterialBranch( wxCommandEvent& event )
{
    ExitIsolateMaterialBranch();
}

/// <summary>
/// Exit Isolate of the Material Branch
/// </summary>
void MaterialFrame::ExitIsolateMaterialBranch()
{

    //Get the current MatML data pointer
    wxTreeItemId CurrentItemId=m_MatMLTreeCtrl->GetSelection();
    if(!CurrentItemId.IsOk() || CurrentItemId==m_MatMLTreeCtrl->GetRootItem()) return;
    MatMLTreeItemData* Current_MatML_Data((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(CurrentItemId)));

    //Get the current wxTreeCtrl selection
    wxTreeItemId MatML_DocItemId = m_MatMLTreeCtrl->GetSelection();
    wxTreeItemId CurrentMaterialItemId;

    //Find the Material for this tree branch
    while(MatML_DocItemId!=m_MatMLTreeCtrl->GetRootItem()){
      CurrentMaterialItemId=MatML_DocItemId;
      MatML_DocItemId=m_MatMLTreeCtrl->GetItemParent(MatML_DocItemId);
    }

    //Need this to locate the MatML Data in the new tree.
    auto CurrentMaterial(GetMatML<Material>(m_MatMLTreeCtrl, &CurrentMaterialItemId));

    //Rebuild MatML data
    bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(m_MatMLTreeCtrl);
    MatML_Doc_GUI_Base::TraverseMatMLTree(doc.get(), func1);

    //Arrange the wxTreeCtrl to see and select the previous material
    const wxTreeItemId BranchCurrentItemId=Utilities::MatMLtoTreeCtrl(m_MatMLTreeCtrl, CurrentMaterial);
    m_MatMLTreeCtrl->CollapseAll();
    m_MatMLTreeCtrl->SelectItem(BranchCurrentItemId);
    m_MatMLTreeCtrl->EnsureVisible(BranchCurrentItemId);

    m_statusBar1->SetStatusText(wxT(""));
    UpdateCurrentPanel();
    m_splitter1->Refresh();
    m_splitter1->Update();
}

/// <summary>
/// On Exit Selection
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnExitSel( wxCommandEvent& event )
{

    //Saving is Captured on the call to OnCloseSel.

    // TODO: Implement OnExitSel
    Close(TRUE); // Close the window
}


/// <summary>
/// On Edit Menu Preferences Item
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnEditMenuPreferencesItem( wxCommandEvent& event )
{
    //preferenceframe->MakeModal();
    preferenceframe->CenterOnScreen();
    preferenceframe->Show();
    preferenceframe->SetFocus();

}

/// <summary>
/// On Sort Menu Item
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnSortMenuItem( wxCommandEvent& event )
{
    wxTreeItemId item(m_MatMLTreeCtrl->GetRootItem());

    if (item.IsOk()) {
        m_MatMLTreeCtrl->SortChildren(item);
    }
}

/// <summary>
/// On Sort Menu Item
/// </summary>
void MaterialFrame::SortMenuItem()
{
    wxTreeItemId item(m_MatMLTreeCtrl->GetRootItem());

    if (item.IsOk()) {
        m_MatMLTreeCtrl->SortChildren(item);
    }
}


void MaterialFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName("BT-MatML-Editor");
    info.SetVersion("0.1.4","version 0.1.4");
    info.SetDescription(_("Editor for the XML MatML Schema"));
    info.SetCopyright("(C) 2022-2023");
    info.SetWebSite("https://p-mcg.github.io/BT-MatML-Editor/");
    info.AddDeveloper("Paul McGrath");

    wxAboutBox(info, this);
}


boost::any bellshire::GUI::MaterialFrame::GetMatMLItemToCopy()
{
    return m_MatMLItemToCopy;
}

std::shared_ptr<MatML_Doc> bellshire::GUI::MaterialFrame::GetDoc()
{
    return doc;
}

std::stack<TreeCtrlSorted*> bellshire::GUI::MaterialFrame::GetMatMLTreeCtrlStack()
{
    return m_MatMLTreeCtrlStack;
}

std::unique_ptr<MatML_Doc> bellshire::GUI::MaterialFrame::GetTemplateDoc()
{
    return std::move(template_doc);
}

PreferenceFrame* bellshire::GUI::MaterialFrame::GetPreferenceFrame()
{
    return preferenceframe;
}

HTMLFrame* bellshire::GUI::MaterialFrame::GetHtmlFrame()
{
    return htmlframe;
}

/// <summary>
/// On Element Activated.
/// Event Handlers Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnElementActivated( wxTreeEvent& event )
{

    m_GUI->HideAllPanels();

    // show some info about this item
    wxTreeItemId itemId = event.GetItem();

    //If the item is activated on the root then return.
    if(!itemId.IsOk()) return;
    MatMLTreeItemData *item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(itemId));
    const boost::any anyptr(item->GetAnyMatMLDataPointer());

    m_GUI->Update_GUI(anyptr, doc.get());

    m_MultiPanel->Layout();
}


/// <summary>
/// On Element Expanded
/// Event Handlers functions
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnElementExpanded(wxTreeEvent& event)
{
    m_MatMLTreeCtrl->Layout();
}

/// <summary>
/// On Element Collapsed
/// Event Handlers functions
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnElementCollapsed(wxTreeEvent& event)
{
    m_MatMLTreeCtrl->Layout();
}


/// <summary>
/// On MatML Item Selection
/// Event Handlers functions
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnMatMLItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem();
    m_MatMLTreeCtrl->SelectItem(itemId);

    MatMLTreeItemData *item = itemId.IsOk() ? (MatMLTreeItemData *)m_MatMLTreeCtrl->GetItemData(itemId)
                                         : NULL;
    wxPoint clientpt = event.GetPoint();
    wxPoint screenpt = ClientToScreen(clientpt);

    ShowContextMenu(itemId, clientpt);/*!< Shows context menu*/
    event.Skip();
}

/// <summary>
/// Pop-up menu linking and binding
/// Links the Menu Item to the context menu.
/// Binds the Event Handler Functions to the Menu Item.
/// </summary>
/// <typeparam name="EventArg"></typeparam>
/// <typeparam name="EventTag"></typeparam>
/// <typeparam name="Class"></typeparam>
/// <typeparam name="EventHandler"></typeparam>
/// <param name="menu"></param>
/// <param name="desc"></param>
/// <param name="eventType"></param>
/// <param name="method"></param>
/// <param name="handler"></param>
template<typename EventTag, typename Class, typename EventArg, typename EventHandler >
void MaterialFrame::PopupLinkBind(wxMenu& menu, ::std::string desc, const EventTag& eventType, void(Class::* method)(EventArg&), EventHandler* handler)
{
    wxMenuItem* PopupMenuItem = new wxMenuItem(&menu, wxID_ANY, wxString(desc.c_str()), wxEmptyString, wxITEM_NORMAL);
    menu.Append(PopupMenuItem);
    wxEvtHandler::Bind(eventType, method, handler, PopupMenuItem->GetId());

}

/// <summary>
/// Pop-up menu For Pasting
/// Places the MatML Item To Copy.
/// Pop-up menu linking and binding
/// Polymorphicly associated
/// </summary>
/// <typeparam name="EventArg"></typeparam>
/// <typeparam name="Parent_GUIClass"></typeparam>
/// <typeparam name="EventHandler"></typeparam>
/// <typeparam name="EventTag"></typeparam>
/// <typeparam name="MatMLClass"></typeparam>
/// <typeparam name="ParentBase_GUIClass"></typeparam>
/// <param name="MatMLItemToCopy"></param>
/// <param name="Parent_GUI"></param>
/// <param name="menu"></param>
/// <param name="desc"></param>
/// <param name="eventType"></param>
/// <param name="method"></param>
/// <param name="handler"></param>
template<typename MatMLClass, typename Parent_GUIClass, typename EventTag, typename ParentBase_GUIClass, typename EventArg, typename EventHandler >
void MaterialFrame::Popup_Paste(const boost::any& MatMLItemToCopy, Parent_GUIClass* Parent_GUI, wxMenu& menu, ::std::string desc, const EventTag& eventType, void(ParentBase_GUIClass::* method)(EventArg&), EventHandler* handler)
{
	if(!m_MatMLItemToCopy.empty()){ 
        if ( typeid(MatMLClass*) == MatMLItemToCopy.type()) {
            PopupLinkBind(menu, desc, eventType, method, handler);
            Parent_GUI->SetMatMLItemToCopy(MatMLItemToCopy);
               
        }
	} 
}

/// <summary>
/// Shows/Creates the wxTreeCtrl context menu
/// Event Handler functions 
/// polymorphicly associated with the context menu are binded here.
/// </summary>
/// <param name="id"></param>
/// <param name="pt"></param>
void MaterialFrame::ShowContextMenu(wxTreeItemId id, const wxPoint& pt)
{

    wxString title;
    if ( id.IsOk() )
    {
        title << wxT("Element Menu");
    }
    else
    {
        title = wxT("");
    }

    wxMenu menu(title);

    wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
    if(!itemId.IsOk()||(itemId==m_MatMLTreeCtrl->GetRootItem())) return;
    MatMLTreeItemData *item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(itemId));
    const boost::any anyptr(item->GetAnyMatMLDataPointer());

    //Add Sorting

    PopupLinkBind(menu, "SortOrder", wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnSortMenuItem, this);

    //Add IsolateMaterialBranch
    PopupLinkBind(menu, ::std::string("IsolateBranch"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnIsolateMaterialBranch, this);

    //Add ExitIsolateMaterialBranch // FOR SOME REASON THIS CAUSES ERRORS WIH THE MOUSE
//    POPUP_LINK(ExitIsolateMaterialBranch,ExitIsolateBranch)
//	POPUP_CONNECT(ExitIsolateMaterialBranch)

    menu.AppendSeparator();

    PopupLinkBind(menu, ::std::string("Copy"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnCopy, this);

    if (anyptr.type() == typeid(AssociationDetails*)) {

        Popup_Paste<Associate>(m_MatMLItemToCopy, m_GUI->m_AssociationDetails_GUI.get(), menu, ::std::string("Paste Associate"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnPasteAssociate, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());
        Popup_Paste<Relationship>(m_MatMLItemToCopy,  m_GUI->m_AssociationDetails_GUI.get(), menu, ::std::string("Paste Relationship"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnPasteRelationship, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());
        Popup_Paste<Relationship>(m_MatMLItemToCopy, m_GUI->m_AssociationDetails_GUI.get(), menu, ::std::string("Paste Relationship"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnPasteRelationship, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy,  m_GUI->m_AssociationDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnPasteNotes, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnBumpUp, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI->get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnBumpDown, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteAssociationDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Associate"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnInsertAssociate, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Relationship"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnInsertRelationship,(AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AssociationDetails_GUI_Base::OnInsertNotes, (AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get());

        goto done;
    }


    if (anyptr.type() == typeid(AuthorityDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_AuthorityDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnPasteName, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_AuthorityDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnPasteNotes, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnBumpUp, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnBumpDown, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteAuthorityDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnInsertName, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::AuthorityDetails_GUI_Base::OnInsertNotes, (AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(BulkDetails*)) {

        Popup_Paste< Name>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteName, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Class>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Class"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteClass, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Subclass>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Subclass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteSubclass, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Specification>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Specification"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteSpecification, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Source>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Source"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteSource, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Form>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Form"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteForm, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< ProcessingDetails>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste ProcessingDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteProcessingDetails, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Characterization>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Characterization"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteCharacterization, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< PropertyData>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPastePropertyData, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        Popup_Paste< Notes>(m_MatMLItemToCopy, m_GUI->m_BulkDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnPasteNotes, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());

        menu.AppendSeparator();
            
        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteBulkDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertName, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Class"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertClass, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Subclass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertSubclass, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Specification"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertSpecification, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Source"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertSource, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Form"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertForm, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("ProcessingDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertProcessingDetails, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Characterization"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertCharacterization, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertPropertyData, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::BulkDetails_GUI_Base::OnInsertNotes, (BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Characterization*)) {

        Popup_Paste<Formula>(m_MatMLItemToCopy, m_GUI->m_Characterization_GUI.get(), menu, ::std::string("Paste Formula"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnPasteFormula, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        Popup_Paste<ChemicalComposition>(m_MatMLItemToCopy, m_GUI->m_Characterization_GUI.get(), menu, ::std::string("Paste ChemicalComposition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnPasteChemicalComposition, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        Popup_Paste<PhaseComposition>(m_MatMLItemToCopy, m_GUI->m_Characterization_GUI.get(), menu, ::std::string("Paste PhaseComposition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnPastePhaseComposition, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        Popup_Paste<DimensionalDetails>(m_MatMLItemToCopy, m_GUI->m_Characterization_GUI.get(), menu, ::std::string("Paste DimensionalDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnPasteDimensionalDetails, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Characterization_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnPasteNotes, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteCharacterization, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Formula"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnInsertFormula, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        PopupLinkBind(menu, ::std::string("ChemicalComposition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnInsertChemicalComposition, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        PopupLinkBind(menu, ::std::string("PhaseComposition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnInsertPhaseComposition, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        PopupLinkBind(menu, ::std::string("DimensionalDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnInsertDimensionalDetails, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Characterization_GUI_Base::OnInsertNotes, (Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(ChemicalComposition*)) {

        Popup_Paste<Compound>(m_MatMLItemToCopy, m_GUI->m_ChemicalComposition_GUI.get(), menu, ::std::string("Paste Compound"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ChemicalComposition_GUI_Base::OnPasteCompound, (ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get());
        Popup_Paste<Element>(m_MatMLItemToCopy, m_GUI->m_ChemicalComposition_GUI.get(), menu, ::std::string("Paste Element"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ChemicalComposition_GUI_Base::OnPasteElement, (ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteChemicalComposition, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Compound"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ChemicalComposition_GUI_Base::OnInsertCompound, (ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get());
        PopupLinkBind(menu, ::std::string("Element"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ChemicalComposition_GUI_Base::OnInsertElement, (ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(ChemicalElementSymbol*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteChemicalElementSymbol, this);

            menu.AppendSeparator();
            //None
            goto done;
        }


    if (anyptr.type() == typeid(ParentSubClass*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_ParentSubClass_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnPasteName, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());
        Popup_Paste<ParentMaterial>(m_MatMLItemToCopy, m_GUI->m_ParentSubClass_GUI.get(), menu, ::std::string("Paste ParentMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnPasteParentMaterial, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());
        Popup_Paste<ParentSubClass>(m_MatMLItemToCopy, m_GUI->m_ParentSubClass_GUI.get(), menu, ::std::string("Paste ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnPasteParentSubClass, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnBumpUp, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnBumpDown, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteParentSubClass, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnInsertName, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());
        PopupLinkBind(menu, ::std::string("Material"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnInsertParentMaterial, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());
        PopupLinkBind(menu, ::std::string("ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentSubClass_GUI_Base::OnInsertParentSubClass, (ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Class*)) {

        Popup_Paste< Name>(m_MatMLItemToCopy, m_GUI->m_Class_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnPasteName, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());
        Popup_Paste< ParentMaterial>(m_MatMLItemToCopy, m_GUI->m_Class_GUI.get(), menu, ::std::string("Paste ParentMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnPasteParentMaterial, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());
        Popup_Paste< ParentSubClass>(m_MatMLItemToCopy, m_GUI->m_Class_GUI.get(), menu, ::std::string("Paste ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnPasteParentSubClass, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnBumpUp, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnBumpDown, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());

        menu.AppendSeparator();
            
        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteClass, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnInsertName, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());
        PopupLinkBind(menu, ::std::string("Material"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnInsertParentMaterial, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());
        PopupLinkBind(menu, ::std::string("ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Class_GUI_Base::OnInsertParentSubClass, (Class_GUI_Base*)m_GUI->m_Class_GUI.get());

        goto done;
    }

   if (anyptr.type() == typeid(Subclass*)) {

        Popup_Paste< Name>(m_MatMLItemToCopy, m_GUI->m_Subclass_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnPasteName, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());
        Popup_Paste< ParentMaterial>(m_MatMLItemToCopy, m_GUI->m_Subclass_GUI.get(), menu, ::std::string("Paste ParentMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnPasteParentMaterial, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());
        Popup_Paste< ParentSubClass>(m_MatMLItemToCopy, m_GUI->m_Subclass_GUI.get(), menu, ::std::string("Paste ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnPasteParentSubClass, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnBumpUp, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnBumpDown, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());

        menu.AppendSeparator();
            
        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSubclass, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnInsertName, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());
        PopupLinkBind(menu, ::std::string("Material"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnInsertParentMaterial, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());
        PopupLinkBind(menu, ::std::string("ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass_GUI_Base::OnInsertParentSubClass, (Subclass_GUI_Base*)m_GUI->m_Subclass_GUI.get());

        goto done;
    }

   if (anyptr.type() == typeid(Subclass1*)) {

       Popup_Paste< Name>(m_MatMLItemToCopy, m_GUI->m_Subclass1_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnPasteName, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());
       Popup_Paste< ParentMaterial>(m_MatMLItemToCopy, m_GUI->m_Subclass1_GUI.get(), menu, ::std::string("Paste ParentMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnPasteParentMaterial, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());
       Popup_Paste< ParentSubClass>(m_MatMLItemToCopy, m_GUI->m_Subclass1_GUI.get(), menu, ::std::string("Paste ParentSubclass1"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnPasteParentSubClass, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());

       menu.AppendSeparator();

       PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnBumpUp, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());
       PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnBumpDown, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());

       menu.AppendSeparator();

       PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSubclass1, this);

       menu.AppendSeparator();

       PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnInsertName, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());
       PopupLinkBind(menu, ::std::string("Material"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnInsertParentMaterial, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());
       PopupLinkBind(menu, ::std::string("ParentSubClass"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Subclass1_GUI_Base::OnInsertParentSubClass, (Subclass1_GUI_Base*)m_GUI->m_Subclass1_GUI.get());

       goto done;
   }

    if (anyptr.type() == typeid(ComponentDetails*)) {

        //menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Goto ParentMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnGotoParentMaterial, this);
        //POPUP_LINK(GotoParentMaterial,GotoParentMaterial)
        //POPUP_CONNECT(GotoParentMaterial)

        menu.AppendSeparator();

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteName, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Class>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Class"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteClass, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Subclass1>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Subclass1"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteSubclass1, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Specification>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Specification"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteSpecification, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Source>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Source"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteSource, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Form>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Form"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteForm, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<ProcessingDetails>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste ProcessingDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteProcessingDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<Characterization>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste Characterization"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteCharacterization, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<PropertyData>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPastePropertyData, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<AssociationDetails>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste AssociationDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteAssociationDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        Popup_Paste<ComponentDetails>(m_MatMLItemToCopy, m_GUI->m_ComponentDetails_GUI.get(), menu, ::std::string("Paste ComponentDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnPasteComponentDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnBumpUp, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnBumpDown, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteComponentDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertName, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Class"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertClass, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Subclass1"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertSubclass1, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Specification"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertSpecification, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Source"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertSource, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Form"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertForm, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("ProcessingDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertProcessingDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Characterization"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertCharacterization, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertPropertyData, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("AssociationDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertAssociationDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("ComponentDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ComponentDetails_GUI_Base::OnInsertComponentDetails, (ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Compound*)) {
        Popup_Paste<Element>(m_MatMLItemToCopy, m_GUI->m_Compound_GUI.get(), menu, ::std::string("Paste Element"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnPasteElement, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());
        Popup_Paste<Concentration>(m_MatMLItemToCopy, m_GUI->m_Compound_GUI.get(), menu, ::std::string("Paste Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnPasteConcentration, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Compound_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnPasteNotes, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnBumpUp, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnBumpDown, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteCompound, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Element"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnInsertElement, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());
        PopupLinkBind(menu, ::std::string("Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnInsertConcentration, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Compound_GUI_Base::OnInsertNotes, (Compound_GUI_Base*)m_GUI->m_Compound_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Concentration*)) {

        Popup_Paste<Value>(m_MatMLItemToCopy, m_GUI->m_Concentration_GUI.get(), menu, ::std::string("Paste Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnPasteValue, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        Popup_Paste<Units>(m_MatMLItemToCopy, m_GUI->m_Concentration_GUI.get(), menu, ::std::string("Paste Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnPasteUnits, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        Popup_Paste<Qualifier>(m_MatMLItemToCopy, m_GUI->m_Concentration_GUI.get(), menu, ::std::string("Paste Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnPasteQualifier, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        Popup_Paste<Uncertainty>(m_MatMLItemToCopy, m_GUI->m_Concentration_GUI.get(), menu, ::std::string("Paste Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnPasteUncertainty, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Concentration_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnPasteNotes, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteConcentration, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnInsertNotes, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        PopupLinkBind(menu, ::std::string("Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnInsertUnits, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        PopupLinkBind(menu, ::std::string("Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnInsertQualifier, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        PopupLinkBind(menu, ::std::string("Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnInsertUncertainty, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Concentration_GUI_Base::OnInsertNotes, (Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(CurrencyCode*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteCurrencyCode, this);

            menu.AppendSeparator();

            //None

            goto done;
        }

    if (anyptr.type() == typeid(DataFormat*)) {

//			menu.AppendSeparator();
// 
//           PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteDataFormat, this);

            menu.AppendSeparator();

            //None

            goto done;
        }

    if (anyptr.type() == typeid(DataSourceDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_DataSourceDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnPasteName, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_DataSourceDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnPasteNotes, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnBumpUp, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnBumpDown, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteDataSourceDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnInsertName, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DataSourceDetails_GUI_Base::OnInsertNotes, (DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get());

        goto done;
    }


    if (anyptr.type() == typeid(DimensionalDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteName, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        Popup_Paste<Value>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteValue, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        Popup_Paste<Units>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteUnits, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        Popup_Paste<Qualifier>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteQualifier, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        Popup_Paste<Uncertainty>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteUncertainty, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_DimensionalDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnPasteNotes, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnBumpUp, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnBumpDown, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteDimensionalDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertName, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertValue, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertUnits, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertQualifier, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertUncertainty, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::DimensionalDetails_GUI_Base::OnInsertNotes, (DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Element*)) {

        Popup_Paste<Symbol>(m_MatMLItemToCopy, m_GUI->m_Element_GUI.get(), menu, ::std::string("Paste Symbol"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnPasteSymbol, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());
        Popup_Paste<Concentration>(m_MatMLItemToCopy, m_GUI->m_Element_GUI.get(), menu, ::std::string("Paste Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnPasteConcentration, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Element_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnPasteNotes, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnBumpUp, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnBumpDown, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteElement, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Symbol"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnInsertSymbol, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());
        PopupLinkBind(menu, ::std::string("Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnInsertConcentration, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Element_GUI_Base::OnInsertNotes, (Element_GUI_Base*)m_GUI->m_Element_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Form*)) {

        //Popup_Paste<Description>(m_MatMLItemToCopy, m_GUI->m_Form_GUI.get(), menu, ::std::string("Paste Description"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnPasteDescription, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());
        Popup_Paste<Geometry>(m_MatMLItemToCopy, m_GUI->m_Form_GUI.get(), menu, ::std::string("Paste Geometry"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnPasteGeometry, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Form_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnPasteNotes, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteForm, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Description"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnInsertDescription, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());
        PopupLinkBind(menu, ::std::string("Geometry"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnInsertGeometry, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Form_GUI_Base::OnInsertNotes, (Form_GUI_Base*)m_GUI->m_Form_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Formula*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteFormula, this);

            menu.AppendSeparator();

            //None

            goto done;
        }

    if (anyptr.type() == typeid(Geometry*)) {

        Popup_Paste<Shape>(m_MatMLItemToCopy, m_GUI->m_Geometry_GUI.get(), menu, ::std::string("Paste Shape"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnPasteShape, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        Popup_Paste<Dimensions>(m_MatMLItemToCopy, m_GUI->m_Geometry_GUI.get(), menu, ::std::string("Paste Dimensions"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnPasteDimensions, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        Popup_Paste<Orientation>(m_MatMLItemToCopy, m_GUI->m_Geometry_GUI.get(), menu, ::std::string("Paste Orientation"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnPasteOrientation, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Geometry_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnPasteNotes, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteGeometry, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Shape"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnInsertShape, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        PopupLinkBind(menu, ::std::string("Dimensions"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnInsertDimensions, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        PopupLinkBind(menu, ::std::string("Orientation"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnInsertOrientation, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Geometry_GUI_Base::OnInsertNotes, (Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Glossary*)) {

        Popup_Paste<GlossaryTerm>(m_MatMLItemToCopy, m_GUI->m_Glossary_GUI.get(), menu, ::std::string("Paste GlossaryTerm"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Glossary_GUI_Base::OnPasteTerm, (Glossary_GUI_Base*)m_GUI->m_Glossary_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteGlossary, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Term"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Glossary_GUI_Base::OnInsertTerm, (Glossary_GUI_Base*)m_GUI->m_Glossary_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(GlossaryTerm*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_GlossaryTerm_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnPasteName, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        Popup_Paste<Definition>(m_MatMLItemToCopy, m_GUI->m_GlossaryTerm_GUI.get(), menu, ::std::string("Paste Definition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnPasteDefinition, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        Popup_Paste<Abbreviation>(m_MatMLItemToCopy, m_GUI->m_GlossaryTerm_GUI.get(), menu, ::std::string("Paste Abbreviation"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnPasteAbbreviation, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        Popup_Paste<Synonym>(m_MatMLItemToCopy, m_GUI->m_GlossaryTerm_GUI.get(), menu, ::std::string("Paste Synonym"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnPasteSynonym, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_GlossaryTerm_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnPasteNotes, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnBumpUp, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnBumpDown, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteGlossaryTerm, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnInsertName, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        PopupLinkBind(menu, ::std::string("Definition"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnInsertDefinition, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        PopupLinkBind(menu, ::std::string("Abbreviation"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnInsertAbbreviation, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        PopupLinkBind(menu, ::std::string("Synonym"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnInsertSynonym, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::GlossaryTerm_GUI_Base::OnInsertNotes, (GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Definition*)) {

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteDefinition, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(Abbreviation*)) {

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteAbbreviation, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Abbreviation_GUI_Base::OnBumpUp, (Abbreviation_GUI_Base*)m_GUI->m_Abbreviation_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Abbreviation_GUI_Base::OnBumpDown, (Abbreviation_GUI_Base*)m_GUI->m_Abbreviation_GUI.get());

        menu.AppendSeparator();

        //None
        goto done;
    }

    if (anyptr.type() == typeid(Synonym*)) {

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSynonym, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Synonym_GUI_Base::OnBumpUp, (Synonym_GUI_Base*)m_GUI->m_Synonym_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Synonym_GUI_Base::OnBumpDown, (Synonym_GUI_Base*)m_GUI->m_Synonym_GUI.get());

        menu.AppendSeparator();

        //None
        goto done;
    }

    if (anyptr.type() == typeid(Graphs*)) {

        Popup_Paste<Graph>(m_MatMLItemToCopy, m_GUI->m_Graphs_GUI.get(), menu, ::std::string("Paste Graph"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Graphs_GUI_Base::OnPasteGraph, (Graphs_GUI_Base*)m_GUI->m_Graphs_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteGraphs, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Graph"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Graphs_GUI_Base::OnInsertGraph, (Graphs_GUI_Base*)m_GUI->m_Graphs_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Graph*)) {

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Graph_GUI_Base::OnBumpUp, (Graph_GUI_Base*)m_GUI->m_Graph_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Graph_GUI_Base::OnBumpDown, (Graph_GUI_Base*)m_GUI->m_Graph_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteGraph, this);

        goto done;
    }

    if (anyptr.type() == typeid(Material*)) {

        PopupLinkBind(menu, ::std::string("NewMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnInsertMaterial, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        PopupLinkBind(menu, ::std::string("CopyMaterial"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnCopyMaterial, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());

        menu.AppendSeparator();

        Popup_Paste<BulkDetails>(m_MatMLItemToCopy, m_GUI->m_Material_GUI.get(), menu, ::std::string("Paste BulkDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnPasteBulkDetails, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        Popup_Paste<ComponentDetails>(m_MatMLItemToCopy, m_GUI->m_Material_GUI.get(), menu, ::std::string("Paste ComponentDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnPasteComponentDetails, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        Popup_Paste<Graphs>(m_MatMLItemToCopy, m_GUI->m_Material_GUI.get(), menu, ::std::string("Paste Graphs"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnPasteGraphs, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        Popup_Paste<Glossary>(m_MatMLItemToCopy, m_GUI->m_Material_GUI.get(), menu, ::std::string("Paste Glossary"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnPasteGlossary, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnBumpUp, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnBumpDown, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteMaterial, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BulkDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnInsertBulkDetails, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        PopupLinkBind(menu, ::std::string("ComponentDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnInsertComponentDetails, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        PopupLinkBind(menu, ::std::string("Graphs"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnInsertGraphs, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());
        PopupLinkBind(menu, ::std::string("Glossary"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Material_GUI_Base::OnInsertGlossary, (Material_GUI_Base*)m_GUI->m_Material_GUI.get());

        goto done;
    }

    //if (anyptr.type() == typeid(MatML_Doc*)) {

    //	  POPUP_LINK(DeleteMatML_Doc,Delete)
    //	  POPUP_CONNECT(DeleteMatML_Doc)
    //	  menu.AppendSeparator();

    //		//Material
    //		POPUP_LINK(MatML_DocInsertMaterial,Material)
    //		POPUP_CONNECT(MatML_DocInsertMaterial)
    //		//MetaData
    //		POPUP_LINK(MatML_DocInsertMetadata,Metadata)
    //		POPUP_CONNECT(MatML_DocInsertMetadata)

    //		UpdateMatML_DocPanel(derived24);
    //		goto done;
    //	}

    if (anyptr.type() == typeid(MeasurementTechniqueDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_MeasurementTechniqueDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnPasteName, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_MeasurementTechniqueDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnPasteNotes, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnBumpUp, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnBumpDown, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteMeasurementTechniqueDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnInsertName, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MeasurementTechniqueDetails_GUI_Base::OnInsertNotes, (MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Metadata*)) {

        Popup_Paste<AuthorityDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste AuthorityDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteAuthorityDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<DataSourceDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste DataSourceDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteDataSourceDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<MeasurementTechniqueDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste MeasurementTechniqueDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteMeasurementTechniqueDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<ParameterDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste ParameterDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteParameterDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<PropertyDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste PropertyDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPastePropertyDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<SourceDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste SourceDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteSourceDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<SpecimenDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste SpecimenDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteSpecimenDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        Popup_Paste<TestConditionDetails>(m_MatMLItemToCopy, m_GUI->m_Metadata_GUI.get(), menu, ::std::string("Paste TestConditionDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnPasteTestConditionDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteMetadata, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("AuthorityDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertAuthorityDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("DataSourceDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertDataSourceDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("MeasurementTechniqueDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertMeasurementTechniqueDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("ParameterDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertParameterDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("PropertyDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertPropertyDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("SourceDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertSourceDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("SpecimenDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertSpecimenDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());
        PopupLinkBind(menu, ::std::string("TestConditionDetails"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Metadata_GUI_Base::OnInsertTestConditionDetails, (Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Name*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteName, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(Notes*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteNotes, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(ParameterDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_ParameterDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnPasteName, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        Popup_Paste<Units>(m_MatMLItemToCopy, m_GUI->m_ParameterDetails_GUI.get(), menu, ::std::string("Paste Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnPasteUnits, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        Popup_Paste<Unitless>(m_MatMLItemToCopy, m_GUI->m_ParameterDetails_GUI.get(), menu, ::std::string("Paste Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnPasteUnitless, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_ParameterDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnPasteNotes, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnBumpUp, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnBumpDown, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteParameterDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnInsertName, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnInsertUnits, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnInsertUnitless, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterDetails_GUI_Base::OnInsertNotes, (ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(ParameterValue*)) {

        Popup_Paste<Data>(m_MatMLItemToCopy, m_GUI->m_ParameterValue_GUI.get(), menu, ::std::string("Paste Data"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnPasteData, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        Popup_Paste<Uncertainty>(m_MatMLItemToCopy, m_GUI->m_ParameterValue_GUI.get(), menu, ::std::string("Paste Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnPasteUncertainty, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        Popup_Paste<Qualifier>(m_MatMLItemToCopy, m_GUI->m_ParameterValue_GUI.get(), menu, ::std::string("Paste Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnPasteQualifier, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_ParameterValue_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnPasteNotes, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnBumpUp, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnBumpDown, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteParameterValue, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Data"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnInsertData, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        PopupLinkBind(menu, ::std::string("Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnInsertUncertainty, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        PopupLinkBind(menu, ::std::string("Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnInsertQualifier, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParameterValue_GUI_Base::OnInsertNotes, (ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(ParentMaterial*)) {


        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentMaterial_GUI_Base::OnBumpUp, (ParentMaterial_GUI_Base*)m_GUI->m_ParentMaterial_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ParentMaterial_GUI_Base::OnBumpDown, (ParentMaterial_GUI_Base*)m_GUI->m_ParentMaterial_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteParentMaterial, this);

            goto done;
        }


    if (anyptr.type() == typeid(PhaseComposition*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_PhaseComposition_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnPasteName, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        Popup_Paste<Concentration>(m_MatMLItemToCopy, m_GUI->m_PhaseComposition_GUI.get(), menu, ::std::string("Paste Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnPasteConcentration, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        Popup_Paste<PropertyData>(m_MatMLItemToCopy, m_GUI->m_PhaseComposition_GUI.get(), menu, ::std::string("Paste PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnPastePropertyData, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_PhaseComposition_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnPasteNotes, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
 
        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnBumpUp, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnBumpDown, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeletePhaseComposition, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnInsertName, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        PopupLinkBind(menu, ::std::string("Concentration"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnInsertConcentration, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        PopupLinkBind(menu, ::std::string("PropertyData"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnInsertPropertyData, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PhaseComposition_GUI_Base::OnInsertNotes, (PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(ProcessingDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_ProcessingDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnPasteNotes, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        Popup_Paste<ParameterValue>(m_MatMLItemToCopy, m_GUI->m_ProcessingDetails_GUI.get(), menu, ::std::string("Paste ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnPasteParameterValue, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        Popup_Paste<Result>(m_MatMLItemToCopy, m_GUI->m_ProcessingDetails_GUI.get(), menu, ::std::string("Paste Result"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnPasteResult, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_ProcessingDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnPasteNotes, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnBumpUp, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnBumpDown, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteProcessingDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnInsertName, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnInsertParameterValue, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Result"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnInsertResult, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::ProcessingDetails_GUI_Base::OnInsertNotes, (ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Result*)) {

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteResult, this);

                goto done;
        }

    if (anyptr.type() == typeid(PropertyData*)) {

        Popup_Paste<Data1>(m_MatMLItemToCopy, m_GUI->m_PropertyData_GUI.get(), menu, ::std::string("Paste Data"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnPasteData, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        Popup_Paste<Uncertainty>(m_MatMLItemToCopy, m_GUI->m_PropertyData_GUI.get(), menu, ::std::string("Paste Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnPasteUncertainty, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        Popup_Paste<Qualifier>(m_MatMLItemToCopy, m_GUI->m_PropertyData_GUI.get(), menu, ::std::string("Paste Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnPasteQualifier, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        Popup_Paste<ParameterValue>(m_MatMLItemToCopy, m_GUI->m_PropertyData_GUI.get(), menu, ::std::string("Paste ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnPasteParameterValue, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_PropertyData_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnPasteNotes, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnBumpUp, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnBumpDown, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeletePropertyData, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Data"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnInsertNotes, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        PopupLinkBind(menu, ::std::string("Uncertainty"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnInsertUncertainty, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        PopupLinkBind(menu, ::std::string("Qualifier"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnInsertQualifier, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        PopupLinkBind(menu, ::std::string("ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnInsertParameterValue, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyData_GUI_Base::OnInsertNotes, (PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(PropertyDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_PropertyDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnPasteName, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        Popup_Paste<Units>(m_MatMLItemToCopy, m_GUI->m_PropertyDetails_GUI.get(), menu, ::std::string("Paste Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnPasteUnits, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        Popup_Paste<Unitless>(m_MatMLItemToCopy, m_GUI->m_PropertyDetails_GUI.get(), menu, ::std::string("Paste Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnPasteUnitless, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_PropertyDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnPasteNotes, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnBumpUp, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnBumpDown, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeletePropertyDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnInsertName, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnInsertUnits, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnInsertUnitless, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::PropertyDetails_GUI_Base::OnInsertNotes, (PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Qualifier*)) {

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Qualifier_GUI_Base::OnBumpUp, (Qualifier_GUI_Base*)m_GUI->m_Qualifier_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Qualifier_GUI_Base::OnBumpDown, (Qualifier_GUI_Base*)m_GUI->m_Qualifier_GUI.get());

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteQualifier, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(Relationship*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteRelationship, this);

            //None
            goto done;
        }

    if (anyptr.type() == typeid(Source*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSource, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(SourceDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_SourceDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnPasteName, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_SourceDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnPasteNotes, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnBumpUp, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnBumpDown, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSourceDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnInsertName, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SourceDetails_GUI_Base::OnInsertNotes, (SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Specification*)) {
        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Specification_GUI_Base::OnBumpUp, (Specification_GUI_Base*)m_GUI->m_Specification_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Specification_GUI_Base::OnBumpDown, (Specification_GUI_Base*)m_GUI->m_Specification_GUI.get());

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSpecification, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(SpecimenDetails*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_SpecimenDetails_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnPasteName, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_SpecimenDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnPasteNotes, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());
        Popup_Paste<Geometry>(m_MatMLItemToCopy, m_GUI->m_SpecimenDetails_GUI.get(), menu, ::std::string("Paste Geometry"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnPasteGeometry, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnBumpUp, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnBumpDown, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteSpecimenDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnInsertName, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnInsertNotes, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Geometry"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::SpecimenDetails_GUI_Base::OnInsertGeometry, (SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(TestConditionDetails*)) {

        Popup_Paste<ParameterValue>(m_MatMLItemToCopy, m_GUI->m_TestConditionDetails_GUI.get(), menu, ::std::string("Paste ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnPasteParameterValue, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_TestConditionDetails_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnPasteNotes, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnBumpUp, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnBumpDown, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteTestConditionDetails, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("ParameterValue"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnInsertParameterValue, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::TestConditionDetails_GUI_Base::OnInsertNotes, (TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Uncertainty*)) {

        Popup_Paste<Value>(m_MatMLItemToCopy, m_GUI->m_Uncertainty_GUI.get(), menu, ::std::string("Paste Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnPasteValue, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        Popup_Paste<Units>(m_MatMLItemToCopy, m_GUI->m_Uncertainty_GUI.get(), menu, ::std::string("Paste Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnPasteUnits, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        Popup_Paste<Unitless>(m_MatMLItemToCopy, m_GUI->m_Uncertainty_GUI.get(), menu, ::std::string("Paste Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnPasteUnitless, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        Popup_Paste<Notes>(m_MatMLItemToCopy, m_GUI->m_Uncertainty_GUI.get(), menu, ::std::string("Paste Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnPasteNotes, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        Popup_Paste<Scale>(m_MatMLItemToCopy, m_GUI->m_Uncertainty_GUI.get(), menu, ::std::string("Paste Scale"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnPasteScale, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
 
        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnBumpUp, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnBumpDown, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteUncertainty, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Value"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnInsertValue, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        PopupLinkBind(menu, ::std::string("Units"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnInsertUnits, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        PopupLinkBind(menu, ::std::string("Unitless"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnInsertUnitless, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        PopupLinkBind(menu, ::std::string("Notes"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnInsertNotes, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());
        PopupLinkBind(menu, ::std::string("Scale"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Uncertainty_GUI_Base::OnInsertScale, (Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Unit*)) {

        Popup_Paste<Name>(m_MatMLItemToCopy, m_GUI->m_Unit_GUI.get(), menu, ::std::string("Paste Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnPasteName, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());
        Popup_Paste<CurrencyCode>(m_MatMLItemToCopy, m_GUI->m_Unit_GUI.get(), menu, ::std::string("Paste CurrencyCode"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnPasteCurrencyCode, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("BumpUp"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnBumpUp, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());
        PopupLinkBind(menu, ::std::string("BumpDown"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnBumpDown, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteUnit, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Name"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnInsertName, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());
        PopupLinkBind(menu, ::std::string("Currency"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Unit_GUI_Base::OnInsertCurrency, (Unit_GUI_Base*)m_GUI->m_Unit_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Unitless*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteUnitless, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    if (anyptr.type() == typeid(Units*)) {

        Popup_Paste<Unit>(m_MatMLItemToCopy, m_GUI->m_Units_GUI.get(), menu, ::std::string("Paste Unit"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Units_GUI_Base::OnPasteUnit, (Units_GUI_Base*)m_GUI->m_Units_GUI.get());

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteUnits, this);

        menu.AppendSeparator();

        PopupLinkBind(menu, ::std::string("Unit"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::Units_GUI_Base::OnInsertUnit, (Units_GUI_Base*)m_GUI->m_Units_GUI.get());

        goto done;
    }

    if (anyptr.type() == typeid(Value*)) {

            menu.AppendSeparator();

            PopupLinkBind(menu, ::std::string("Delete"), wxEVT_COMMAND_MENU_SELECTED, &::bellshire::GUI::MaterialFrame::OnDeleteValue, this);

            menu.AppendSeparator();

            //None
            goto done;
        }

    done:;


    PopupMenu(&menu, pt);

}

/// <summary>
/// Given a Material Gather Associate ComponentDetails ParentMaterials
/// </summary>
::vector<ParentMaterial*> MaterialFrame::MaterialGatherAssociatedComponentParentMaterial(Material* material)
{

    ::vector<ParentMaterial*> compparentmateriallist;

    if (material->id().present()) {
        MatML_Doc::Material_sequence& matcont(doc->Material());
        MatML_Doc::Material_iterator matiter(matcont.begin());
        for (; matiter != matcont.end(); ++matiter) {
            if (!matiter->ComponentDetails().empty()) {
                Material::ComponentDetails_sequence& compcont(matiter->ComponentDetails());
                Material::ComponentDetails_iterator compiter(compcont.begin());
                for (; compiter != compcont.end(); ++compiter) {
                    if (!compiter->Class().empty()) {
                        ComponentDetails::Class_sequence& classcont(compiter->Class());
                        ComponentDetails::Class_iterator classiter(classcont.begin());
                        for (; classiter != classcont.end(); ++classiter) {
                            if (!classiter->ParentMaterial().empty()) {
                                Material* parentmaterial(dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));
                                if (material == parentmaterial) {
                                    compparentmateriallist.push_back(&classiter->ParentMaterial().front());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return compparentmateriallist;
}

/// <summary>
/// Given a Material Set the ParentMaterial from a list.
/// </summary>
/// <param name="compparentmateriallist"></param>
/// <param name="material"></param>
void MaterialFrame::MaterialSetParentMaterial(::vector<ParentMaterial*> compparentmateriallist, Material* material)
{
    if (!compparentmateriallist.empty()) {
        ::vector<ParentMaterial*>::iterator listiter(compparentmateriallist.begin());
        for (; listiter != compparentmateriallist.end(); ++listiter) {
            (*listiter)->id().clear();
            (*listiter)->id() = ParentMaterial::id_type(material->id().get());
        }
    }
}

/// <summary>
/// Load File
/// </summary>
void MaterialFrame::LoadFile()
{
  try
  {
      backup();

      // TODO: Implement OnOpenSel
      wxString CurrentDocPath("");
      if (preferenceframe->config->Read(wxT("/General/CurrentDocPath"), &CurrentDocPath)) {

          ::xml_schema::string File(_wx2std(CurrentDocPath));

          //auto tmp0 = MatML_Doc_(File);// note you will get a parsing error if the *.xsd file is not with the *.xml file 
          auto tmp0 = MatML_Doc_(File);
          auto tmp = tmp0.release();
          doc.reset(tmp);

          bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(m_MatMLTreeCtrl);
          MatML_Doc_GUI::TraverseMatMLTree(doc.get(), func1);//Set up the MatML elements to the wxTreeCtrl.
          m_GUI->SetEvtHandlerVar(m_MatMLTreeCtrl, doc.get());//Set the Event Handler's Variables for the MatML_GUIs.
      }
  }
  //catch (const xml_schema::no_element_info& e)
  //{
  //    // This exception indicates that we tried to parse or serialize
  //    // an unknown element.
  //    //
  //    cerr << "unknown request: " << e.element_namespace() << "#" <<
  //        e.element_name() << endl;
  //    r = 1;
  //}
  //catch (const xml_schema::exception& e)
  //{
  //    cerr << e << endl;
  //    r = 1;
  //}
  //catch (const std::ios_base::failure&)
  //{
  //    cerr << argv[1] << ": unable to open or read failure" << endl;
  //    r = 1;
  //}
  catch (const xml_schema::parsing& e)
  { 

      std::string msg;
      
      msg.append(e.what());

      for (auto diag : e.diagnostics()) {
          msg.append("\n");
          msg.append("Line: ");
          msg.append(to_string(diag.line()) + "\n");
          msg.append("column: ");
          msg.append(to_string(diag.column()) + "\n");
          msg.append("Message: ");
          msg.append(diag.message() + "\n");
      }

      msg.append("\n\n Note: Common problems with parsing \n1) *.xml file is not in the same directory as the *.xsd file. \n2) *.xml file has xmlns:xsi entry different than the *.xsd file \n3) xs:IDs cannot have \":\" characters anywhere in the name and cannot\n have a digit as the first character of the ID");
      wxMessageDialog OpenDialog(this, msg, _("MatML Message"), wxOK, wxDefaultPosition);
      OpenDialog.ShowModal();
  }
  catch (const xml_schema::exception& e)
  {
    wxMessageDialog OpenDialog(this, e.what(), _("MatML Message"), wxOK, wxDefaultPosition);
    OpenDialog.ShowModal();
  }

}

/// <summary>
/// Import File
/// </summary>
/// <param name="File"></param>
void MaterialFrame::ImportFile(const char* File)
{
    // TODO: Implement File Loading
  try
  {
      //backup();

      //using namespace xml_schema;
      //std::shared_ptr<MatML_Doc> importdoc;
      //importdoc.reset(MatML_Doc_ (File).release());

      //wxTreeItemId CurrentId=m_MatMLTreeCtrl->GetRootItem();

      //wxTreeItemId MetaDataId=m_MatMLTreeCtrl->GetLastChild(CurrentId);

      ////Setup Element Material
      //{
      //    MatML_Doc::Material_sequence& cont(importdoc->Material());
      //    MatML_Doc::Material_iterator iter(cont.begin());
      //    if(!cont.empty())
      //        for (; iter!=cont.end (); ++iter){
      //            try{
      //                doc->Material().push_back(*iter);
      //                Material_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, 
      //                    CurrentId, doc->Material().back(),
      //                    m_MatMLTreeCtrl->GetLastChild(CurrentId)
      //                );
      //            }
      //            catch(const xml_schema::duplicate_id & ){continue;}
      //        }
      //}

      ////Setup Element Metadata
      //{
      //    MatML_Doc::Metadata_optional& metacont(importdoc->Metadata());
      //    if(metacont.present()){

      //        //Setup Element AuthorityDetails
      //        {
      //            Metadata::AuthorityDetails_sequence& cont(metacont->AuthorityDetails());
      //            Metadata::AuthorityDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->AuthorityDetails().push_back(*iter);
      //                        AuthorityDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->AuthorityDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element DataSourceDetails
      //        {
      //            Metadata::DataSourceDetails_sequence& cont(metacont->DataSourceDetails());
      //            Metadata::DataSourceDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->DataSourceDetails().push_back(*iter);
      //                        DataSourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->DataSourceDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element MeasurementTechniqueDetails
      //        {
      //            Metadata::MeasurementTechniqueDetails_sequence& cont(metacont->MeasurementTechniqueDetails());
      //            Metadata::MeasurementTechniqueDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->MeasurementTechniqueDetails().push_back(*iter);
      //                        MeasurementTechniqueDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->MeasurementTechniqueDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element ParameterDetails
      //        {
      //             Metadata::ParameterDetails_sequence& cont(metacont->ParameterDetails());
      //            Metadata::ParameterDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->ParameterDetails().push_back(*iter);
      //                        ParameterDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->ParameterDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element PropertyDetails
      //        {
      //            Metadata::PropertyDetails_sequence& cont(metacont->PropertyDetails());
      //            Metadata::PropertyDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->PropertyDetails().push_back(*iter);
      //                        PropertyDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->PropertyDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element SourceDetails
      //        {
      //            Metadata::SourceDetails_sequence& cont(metacont->SourceDetails());
      //            Metadata::SourceDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->SourceDetails().push_back(*iter);
      //                        SourceDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl, MetaDataId, doc->Metadata()->SourceDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element SpecimenDetails
      //        {
      //            Metadata::SpecimenDetails_sequence& cont(metacont->SpecimenDetails());
      //            Metadata::SpecimenDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->SpecimenDetails().push_back(*iter);
      //                        SpecimenDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetaDataId, doc->Metadata()->SpecimenDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        //Setup Element TestConditionDetails
      //        {
      //            Metadata::TestConditionDetails_sequence& cont(metacont->TestConditionDetails());
      //            Metadata::TestConditionDetails_iterator iter(cont.begin());
      //            if(!cont.empty())
      //                for (; iter!=cont.end (); ++iter){
      //                    try{
      //                        doc->Metadata()->TestConditionDetails().push_back(*iter);
      //                        TestConditionDetails_GUI::SetupMatMLTreeCtrl(m_MatMLTreeCtrl,MetaDataId, doc->Metadata()->TestConditionDetails().back(), wxTreeItemId());
      //                    }
      //                    catch(const xml_schema::duplicate_id & ){continue;}
      //                }
      //        }

      //        m_MatMLTreeCtrl->Expand(CurrentId);
      //    }

      //}

      //m_MatMLTreeCtrl->SortChildren(m_MatMLTreeCtrl->GetRootItem());//Test code

  }

  catch (const xml_schema::exception& )
  {

    wxMessageDialog OpenDialog(
        this, _("Error importing the file"), _("MatML Message"), wxOK, wxDefaultPosition);

    // Creates a "Message" dialog
    OpenDialog.ShowModal();
  }

}

/// <summary>
/// Perform a file backup
/// </summary>
void MaterialFrame::backup()
{
    char * tmpname;
    char strdir[256]={".//Back-up//"};
    char strfilename[256]={"backupfile"};
    char strdelimiter[256]={"-"};
    char strext[256]={".xml"};
    char strtime[256];

    system("mkdir Back-up");

    time_t tms;
    ::std::time(&tms);

    tm *ptm = localtime(&tms);

    strftime(strtime, 100,"%S-%M-%H-%j-%Y",ptm);

    // Length of new string includes directory
    // separator and null character
    size_t newlen = strlen(strdir) + strlen(strfilename)
        + strlen(strdelimiter) + strlen(strtime) + strlen(strext)+ 2;
    tmpname = (char *) malloc(5*256* /*newlen*/ sizeof(char));
    if (tmpname == NULL) {
        // Handle memory error.
        exit(1);
    }

    strcpy(tmpname, strdir);
    strcat(tmpname, strfilename);
    strcat(tmpname, strdelimiter);
    strcat(tmpname, strtime);
    strcat(tmpname, strext);

    cerr << tmpname <<  endl;

    wxString CurrentDocPath("");
    preferenceframe->config->Read(wxT("/General/WorkingDir"), &CurrentDocPath);

    FileCopy(CurrentDocPath.mb_str(),tmpname);
    free(tmpname);

}

/// <summary>
/// This function Updates the wxTreeCtrl's Current selected element's 
/// polymorhically associated wxNotebook/wxPanel.
/// </summary>
void MaterialFrame::UpdateCurrentPanel()
{

    //If the item is activated on the root then return.
    wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
    if(!itemId.IsOk()||(itemId==m_MatMLTreeCtrl->GetRootItem())) return;
    MatMLTreeItemData *item = (MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(itemId));
    const boost::any anyptr(item->GetAnyMatMLDataPointer());

    m_GUI->Update_GUI(anyptr, doc.get());
}


/// <summary>
/// //The following functions setup wxTreeCtrl branches and assigns a MatML element pointer to the wxTreeCtrl elements
/// </summary>
/// <param name="element"></param>
/// <param name="materials"></param>
void MaterialFrame::SetupMaterialBranch(MatML_Doc& element, std::vector<Material*>& materials)
{
}

/// <summary>
/// On Copy
/// Event Handler Function
/// Sets the MatML Item To Copy
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnCopy(wxCommandEvent& event){
    wxTreeItemId itemId = m_MatMLTreeCtrl->GetSelection();
    if(!itemId.IsOk()||(itemId==m_MatMLTreeCtrl->GetRootItem())) return;
    m_MatMLItemToCopy = ((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(itemId)))->GetAnyMatMLDataPointer();
}

/// <summary>
/// For Deletion the MatML Elements may have multiple parents. Need to keep the following functions
/// and have them call the deletion functions in the parents. 
/// These calls are made to the Base class' virtual functions which is overwriten by the derived classes.
/// Calling the derived class directly will not allow that inheritence.
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteAssociate(wxCommandEvent& event){
     ((AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get())->OnDeleteAssociate(event);/*! Call parents to delete MatML data*/
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteAssociationDetails(wxCommandEvent& event) 
{
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteAssociationDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteAuthorityDetails(wxCommandEvent& event)
{
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteAuthorityDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteBulkDetails(wxCommandEvent& event)
{
    ((Material_GUI_Base*)m_GUI->m_Material_GUI.get())->OnDeleteBulkDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteCharacterization(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*) m_GUI->m_BulkDetails_GUI.get())->OnDeleteCharacterization(event);
    ((ComponentDetails_GUI_Base*) m_GUI->m_ComponentDetails_GUI.get())->OnDeleteCharacterization(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteChemicalComposition(wxCommandEvent& event) {
    ((Characterization_GUI_Base*) m_GUI->m_Characterization_GUI.get())->OnDeleteChemicalComposition(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteChemicalElementSymbol(wxCommandEvent& event){}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteClass(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteClass(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteClass(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSubclass(wxCommandEvent& event)
{
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteSubclass(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSubclass1(wxCommandEvent& event)
{
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteSubclass1(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteComponentDetails(wxCommandEvent& event){
//	((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails)->OnDeleteComponentDetails(event);
    ((Material_GUI_Base*)m_GUI->m_Material_GUI.get())->OnDeleteComponentDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteCompound(wxCommandEvent& event) {
    ((ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get())->OnDeleteCompound(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteConcentration(wxCommandEvent& event){
    ((Compound_GUI_Base*)m_GUI->m_Compound_GUI.get())->OnDeleteConcentration(event);
    ((Element_GUI_Base*)m_GUI->m_Element_GUI.get())->OnDeleteConcentration(event);
    ((PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get())->OnDeleteConcentration(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteCurrencyCode(wxCommandEvent& event){}


//void MaterialFrame::OnDeleteDataFormat(wxCommandEvent& event){	ON_PARENT_DELETE_ITER_CONT_CHILD(ParameterValue,DataFormat)}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteDataSourceDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteDataSourceDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteDimensionalDetails(wxCommandEvent& event){
    ((Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get())->OnDeleteDimensionalDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteElement(wxCommandEvent& event){
    ((ChemicalComposition_GUI_Base*)m_GUI->m_ChemicalComposition_GUI.get())->OnDeleteElement(event);
    ((Compound_GUI_Base*)m_GUI->m_Compound_GUI.get())->OnDeleteElement(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteForm(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteForm(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteForm(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteFormula(wxCommandEvent& event){
    ((Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get())->OnDeleteFormula(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteGeometry(wxCommandEvent& event){
    ((Form_GUI_Base*)m_GUI->m_Form_GUI.get())->OnDeleteGeometry(event);
    ((SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get())->OnDeleteGeometry(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteGlossary(wxCommandEvent& event) {
    ((Material_GUI_Base*)m_GUI->m_Material_GUI.get())->OnDeleteGlossary(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteGlossaryTerm(wxCommandEvent& event)
{
    ((Glossary_GUI_Base*)m_GUI->m_Glossary_GUI.get())->OnDeleteGlossaryTerm(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteDefinition(wxCommandEvent& event){
    ((GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get())->OnDeleteDefinition(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteAbbreviation(wxCommandEvent& event)
{
    ((GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get())->OnDeleteAbbreviation(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSynonym(wxCommandEvent& event)
{
    ((GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get())->OnDeleteSynonym(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteGraphs(wxCommandEvent& event) { 
    ((Material_GUI_Base*)m_GUI->m_Material_GUI.get())->OnDeleteGraphs(event); 
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteGraph(wxCommandEvent& event) { 
    ((Graphs_GUI_Base*)m_GUI->m_Graphs_GUI.get())->OnDeleteGraph(event); 
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteMaterial(wxCommandEvent& event){ 
    ((MatML_Doc_GUI_Base*)m_GUI->m_MatML_Doc_GUI.get())->OnDeleteMaterial(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteMeasurementTechniqueDetails(wxCommandEvent& event) {
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteMeasurementTechniqueDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteMetadata(wxCommandEvent& event){}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteName(wxCommandEvent& event){
    ((AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get())->OnDeleteName(event);
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteName(event);
    ((Class_GUI_Base*)m_GUI->m_Class_GUI.get())->OnDeleteName(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteName(event);
    ((DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get())->OnDeleteName(event);
    ((Element_GUI_Base*)m_GUI->m_Element_GUI.get())->OnDeleteName(event);
    ((MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get())->OnDeleteName(event);
    ((ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get())->OnDeleteName(event);
    ((PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get())->OnDeleteName(event);
    ((ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get())->OnDeleteName(event);
    ((PropertyDetails_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteName(event);
    ((ParentSubClass_GUI_Base*)m_GUI->m_ParentSubClass_GUI.get())->OnDeleteName(event);
    ((SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get())->OnDeleteName(event);
    ((SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get())->OnDeleteName(event);
    ((Unit_GUI_Base*)m_GUI->m_Unit_GUI.get())->OnDeleteName(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteNotes(wxCommandEvent& event){
    ((AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get())->OnDeleteNotes(event);
    ((AuthorityDetails_GUI_Base*)m_GUI->m_AuthorityDetails_GUI.get())->OnDeleteNotes(event);
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteNotes(event);
    ((Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get())->OnDeleteNotes(event);
    ((Compound_GUI_Base*)m_GUI->m_Compound_GUI.get())->OnDeleteNotes(event);
    ((Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get())->OnDeleteNotes(event);
    ((DataSourceDetails_GUI_Base*)m_GUI->m_DataSourceDetails_GUI.get())->OnDeleteNotes(event);
    ((DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get())->OnDeleteNotes(event);
    ((Element_GUI_Base*)m_GUI->m_Element_GUI.get())->OnDeleteNotes(event);
    ((Form_GUI_Base*)m_GUI->m_Form_GUI.get())->OnDeleteNotes(event);
    ((Geometry_GUI_Base*)m_GUI->m_Geometry_GUI.get())->OnDeleteNotes(event);
    ((GlossaryTerm_GUI_Base*)m_GUI->m_GlossaryTerm_GUI.get())->OnDeleteNotes(event);
    ((MeasurementTechniqueDetails_GUI_Base*)m_GUI->m_MeasurementTechniqueDetails_GUI.get())->OnDeleteNotes(event);
    ((ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get())->OnDeleteNotes(event);
    ((ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get())->OnDeleteNotes(event);
    ((PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get())->OnDeleteNotes(event);
    ((ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get())->OnDeleteNotes(event);
    ((PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteNotes(event);
    ((PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get())->OnDeleteNotes(event);
    ((SourceDetails_GUI_Base*)m_GUI->m_SourceDetails_GUI.get())->OnDeleteNotes(event);
    ((SpecimenDetails_GUI_Base*)m_GUI->m_SpecimenDetails_GUI.get())->OnDeleteNotes(event);
    ((TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get())->OnDeleteNotes(event);
    ((Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get())->OnDeleteNotes(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteParentMaterial(wxCommandEvent& event) {
    ((Class_GUI_Base*)m_GUI->m_Class_GUI.get())->OnDeleteParentMaterial(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteParentSubClass(wxCommandEvent& event) {
    ((Class_GUI_Base*)m_GUI->m_Class_GUI.get())->OnDeleteParentSubClass(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteParameterDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteParameterDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteParameterValue(wxCommandEvent& event){
    ((ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get())->OnDeleteParameterValue(event);
    ((PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteParameterValue(event);
    ((TestConditionDetails_GUI_Base*)m_GUI->m_TestConditionDetails_GUI.get())->OnDeleteParameterValue(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeletePhaseComposition(wxCommandEvent& event){
    ((Characterization_GUI_Base*)m_GUI->m_Characterization_GUI.get())->OnDeletePhaseComposition(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteProcessingDetails(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteProcessingDetails(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteProcessingDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteResult(wxCommandEvent& event) {
    ((ProcessingDetails_GUI_Base*)m_GUI->m_ProcessingDetails_GUI.get())->OnDeleteResult(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeletePropertyData(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeletePropertyData(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeletePropertyData(event);
    ((PhaseComposition_GUI_Base*)m_GUI->m_PhaseComposition_GUI.get())->OnDeletePropertyData(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeletePropertyDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeletePropertyDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteQualifier(wxCommandEvent& event){
    ((Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get())->OnDeleteQualifier(event);
    ((DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get())->OnDeleteQualifier(event);
    ((ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get())->OnDeleteQualifier(event);
    ((PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteQualifier(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteRelationship(wxCommandEvent& event){
    ((AssociationDetails_GUI_Base*)m_GUI->m_AssociationDetails_GUI.get())->OnDeleteRelationship(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSpecification(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteSpecification(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteSpecification(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSpecimenDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteSpecimenDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSource(wxCommandEvent& event){
    ((BulkDetails_GUI_Base*)m_GUI->m_BulkDetails_GUI.get())->OnDeleteSource(event);
    ((ComponentDetails_GUI_Base*)m_GUI->m_ComponentDetails_GUI.get())->OnDeleteSource(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteSourceDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteSourceDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteTestConditionDetails(wxCommandEvent& event){
    ((Metadata_GUI_Base*)m_GUI->m_Metadata_GUI.get())->OnDeleteTestConditionDetails(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteUncertainty(wxCommandEvent& event){
    ((Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get())->OnDeleteUncertainty(event);
    ((DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get())->OnDeleteUncertainty(event);
    ((ParameterValue_GUI_Base*)m_GUI->m_ParameterValue_GUI.get())->OnDeleteUncertainty(event);
    ((PropertyData_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteUncertainty(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteScale(wxCommandEvent& event){
    ((Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get())->OnDeleteScale(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteUnit(wxCommandEvent& event){
    ((Units_GUI_Base*)m_GUI->m_Units_GUI.get())->OnDeleteUnit(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteUnitless(wxCommandEvent& event){
    ((ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get())->OnDeleteUnitless(event);
    ((PropertyDetails_GUI_Base*)m_GUI->m_PropertyData_GUI.get())->OnDeleteUnitless(event);
    ((Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get())->OnDeleteUnitless(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteUnits(wxCommandEvent& event){
    ((Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get())->OnDeleteUnits(event);
    ((DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get())->OnDeleteUnits(event);
    ((ParameterDetails_GUI_Base*)m_GUI->m_ParameterDetails_GUI.get())->OnDeleteUnits(event);
    ((PropertyDetails_GUI_Base*)m_GUI->m_PropertyDetails_GUI.get())->OnDeleteUnits(event);
    ((Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get())->OnDeleteUnits(event);
}

/// <summary>
/// Call parents to delete MatML data
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnDeleteValue(wxCommandEvent& event){
    ((Concentration_GUI_Base*)m_GUI->m_Concentration_GUI.get())->OnDeleteValue(event);
    ((DimensionalDetails_GUI_Base*)m_GUI->m_DimensionalDetails_GUI.get())->OnDeleteValue(event);
    ((Uncertainty_GUI_Base*)m_GUI->m_Uncertainty_GUI.get())->OnDeleteValue(event);
}

/// <summary>
/// Based on the pointer to wxTreeCtrl and the root element, finds the matching wxString content.
/// Can do
/// - a CaseSenitive match 
/// - Exact match or contains match.
/// </summary>
/// <param name="pTreeCtrl"></param>
/// <param name="root"></param>
/// <param name="text"></param>
/// <param name="bCaseSensitive"></param>
/// <param name="bExactMatch"></param>
/// <returns></returns>
wxTreeItemId MaterialFrame::findTreeItem(TreeCtrlSorted* pTreeCtrl, const wxTreeItemId& root, const wxString& text, bool bCaseSensitive, bool bExactMatch)
{
    wxTreeItemId item=root, child;
    wxTreeItemIdValue cookie;
    wxString findtext(text), itemtext;
    bool bFound;
    if(!bCaseSensitive) findtext.MakeLower();

    while(item.IsOk())
    {
        itemtext = pTreeCtrl->GetItemText(item);
        if(!bCaseSensitive) itemtext.MakeLower();
        bFound = bExactMatch ? (itemtext == findtext) : itemtext.Contains(findtext);
        if(bFound) return item;
        child = pTreeCtrl->GetFirstChild(item, cookie);
        if(child.IsOk()) child = findTreeItem(pTreeCtrl, child, text, bCaseSensitive, bExactMatch);
        if(child.IsOk()) return child;
        item = pTreeCtrl->GetNextSibling(item);
    } // while(item.IsOk())

    return item;
}

/// <summary>
/// Based on the pointer to wxTreeCtrl and the root element, finds the matching MatMLTreeItemData memory location.
/// </summary>
/// <param name="pTreeCtrl"></param>
/// <param name="root"></param>
/// <param name="MatML_Data"></param>
/// <returns></returns>
wxTreeItemId MaterialFrame::findTreeItem(TreeCtrlSorted* pTreeCtrl, const wxTreeItemId& root, const MatMLTreeItemData& MatML_Data)
{
    wxTreeItemId item=root, child;
    wxTreeItemIdValue cookie;
    MatMLTreeItemData findMatML_Data(MatML_Data);
    bool bFound;

    while(item.IsOk())
    {
        MatMLTreeItemData* ItemData=(MatMLTreeItemData *)(pTreeCtrl->GetItemData(item));
        bFound=(findMatML_Data==*ItemData);
        if(bFound) return item;
        child = pTreeCtrl->GetFirstChild(item, cookie);
        if(child.IsOk()) child = findTreeItem(pTreeCtrl, child, MatML_Data);
        if(child.IsOk()) return child;
        item = pTreeCtrl->GetNextSibling(item);
    } // while(item.IsOk())

    return item;
}


void MaterialFrame::CopyComponentNameToParentMaterial()
{

    //This was used only to make the old data format compatible with the new arragement
    MatML_Doc::Material_sequence& matcont(doc->Material());
    MatML_Doc::Material_iterator matiter(matcont.begin());
    for(;matiter!=matcont.end();++matiter){
        if(!matiter->ComponentDetails().empty()){
            Material::ComponentDetails_sequence& compcont(matiter->ComponentDetails());
            Material::ComponentDetails_iterator compiter(compcont.begin());
            for(;compiter!=compcont.end();++compiter){
                MatML_Doc::Material_sequence& matcont2(doc->Material());
                MatML_Doc::Material_iterator matiter2(matcont2.begin());
                for(;matiter2!=matcont2.end();++matiter2){
                    if(matiter2->id().present()){
                        if(matiter2->id()->compare(compiter->Name().c_str())==0){
                            ParentMaterial pmat(matiter2->id().get());
                            Class NewData;
                            NewData.ParentMaterial().push_back(pmat);
                            compiter->Class().push_back(NewData);
                            break;
                        }
                    }
                }
            }
        }
    }

}



/// <summary>
/// On Component Details Goto Parent Material
/// Event Handler Function
/// </summary>
/// <param name="event"></param>
void MaterialFrame::OnGotoParentMaterial(wxCommandEvent& event)
{

    wxTreeItemIdValue cookie;

    //Get the current MatML data pointer
    wxTreeItemId SelectedItemID=m_MatMLTreeCtrl->GetSelection();
    const MatMLTreeItemData* Selected_MatML_Data((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(SelectedItemID)));

    try{
        ComponentDetails* const Element = boost::any_cast< ComponentDetails* const>(Selected_MatML_Data->GetAnyMatMLDataPointer());
        if(Element->Class().empty()) return;
        ComponentDetails::Class_sequence& classcont(Element->Class());
        ComponentDetails::Class_iterator classiter(classcont.begin());
        for(;classiter!=classcont.end();++classiter){
            if(!classiter->ParentMaterial().empty()){
                Material* parentmaterial (dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));

                //Search for the material.
                wxTreeItemId itemID=m_MatMLTreeCtrl->GetFirstChild(m_MatMLTreeCtrl->GetRootItem(),cookie);
                while(itemID.IsOk())
                {
                    const MatMLTreeItemData* Current_MatML_Data((MatMLTreeItemData *)(m_MatMLTreeCtrl->GetItemData(itemID)));
                    try{
                        Material* const currentmaterial = boost::any_cast< Material* const>(Current_MatML_Data->GetAnyMatMLDataPointer());
                        if(parentmaterial==currentmaterial){
                            m_MatMLTreeCtrl->SelectItem(itemID);
                            m_MatMLTreeCtrl->EnsureVisible(itemID);
                            m_MatMLTreeCtrl->Expand(itemID);
                            return;
                        }
                    }
                    catch(const boost::bad_any_cast &){return;}
                    itemID = m_MatMLTreeCtrl->GetNextSibling(itemID);
                } // while(itemID.IsOk())
            }
        }
    }
    catch(const boost::bad_any_cast &){return;}

}

void MaterialFrame::OnLeftDown(wxTreeEvent& event)
{
    MatML_GUI_Base::DnDSource(event, m_MatMLTreeCtrl, this);
}

