#pragma once
#include "bellshire/GUI/utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/GUI/utilities/BT_MatML_Get_Associated_GUI_type.h"

namespace bellshire::GUI::utilities
{

    /// <summary>
    /// Evaluated function return
    /// </summary>
    /// <typeparam name="MatML"></typeparam>
    /// <typeparam name="MatML_GUI"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<class MatML,
        class MatML_GUI
    >
    wxTreeItemId Functor_SetupCtrl_MatMLTree_GUI
        ::operator()(void)
    {
        return data_.CurrentId_;
    };


    /// <summary>
    /// Main evaluation function
    /// </summary>
    /// <typeparam name="MatML"></typeparam>
    /// <typeparam name="MatML_GUI"></typeparam>
    /// <param name="Element"></param>
    /// <returns></returns>
    template<
        class MatML, 
        class MatML_GUI
    >
    wxTreeItemId Functor_SetupCtrl_MatMLTree_GUI
        ::operator()(const observer_ptr<MatML>& element)
    {

        if (element) {
            if (typeid(MatML) == typeid(MatML_Doc)) {
                /// As this is the root element in the wxTreeCtrl, clear out all wxTreeCtrl data and start fresh.
                if (!data_.MatMLTreeCtrl_->IsEmpty())
                    data_.MatMLTreeCtrl_->DeleteAllItems();

                /// Create the current element and add the MatMLTreeItemData

                    //This function requires weakly typed element
                wxString str(MatML_GUI::GetTreeLabel(element));

                //This function requires strongly typed element
                data_.CurrentId_ = data_.MatMLTreeCtrl_->AddRoot(str, -1, -1, new MatMLTreeItemData(element));

            }
            else {


                //this function requires weakly typed element
                wxString str(MatML_GUI::GetTreeLabel(element));

                //This function requires strongly typed element
                MatMLTreeItemData* data(new MatMLTreeItemData(element));

                if (data_.PreviousId_.IsOk())
                    data_.CurrentId_ = data_.MatMLTreeCtrl_->InsertItem(data_.ParentId_, data_.PreviousId_, str, -1, -1, data);
                else
                    data_.CurrentId_ = data_.MatMLTreeCtrl_->AppendItem(data_.ParentId_, str, -1, -1, data);
            }
        }
        return  data_.CurrentId_;
       
    }

};//end namespace bellshire
