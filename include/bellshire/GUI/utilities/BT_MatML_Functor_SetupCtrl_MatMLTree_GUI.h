#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

#include "bellshire/GUI/utilities/BT_MatML_Get_Associated_GUI_type.h"
#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"



namespace bellshire::GUI::utilities
{

    class Functor_SetupCtrl_MatMLTree_GUI
    {
    public:
        struct Data{
            TreeCtrlSorted* MatMLTreeCtrl_{nullptr};
            wxTreeItemId ParentId_{ wxTreeItemId() };
            wxTreeItemId CurrentId_{ wxTreeItemId() };
            wxTreeItemId PreviousId_{ wxTreeItemId() };
        };

        Data data_;//!< Data to be used during tree transversal

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="data_in"></param>
        Functor_SetupCtrl_MatMLTree_GUI(Functor_SetupCtrl_MatMLTree_GUI::Data data
        ) : data_( data )
        {}

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="data_in"></param>
        Functor_SetupCtrl_MatMLTree_GUI(TreeCtrlSorted*& MatMLTreeCtrl
        ) : data_({ MatMLTreeCtrl })
        {}

        /// <summary>
        /// Ctor Function to Setup the next child functor.
        /// </summary>
        /// <param name="func"></param>
        Functor_SetupCtrl_MatMLTree_GUI(Functor_SetupCtrl_MatMLTree_GUI& func)
            :data_({
            func.data_.MatMLTreeCtrl_,
            func.data_.CurrentId_ //CurrentId_ is the new parent
                })
            {}

        template<class MatML, 
            class MatML_GUI = typename Get_Associated_GUI_type< MatML>::MatML_GUI_type
        >
        wxTreeItemId operator()();


        template<class MatML, 
            class MatML_GUI = Get_Associated_GUI_type< MatML >::MatML_GUI_type
        >
        wxTreeItemId operator()(const observer_ptr<MatML>& element);

    };

}//end namespace bellshire

#include "bellshire/GUI/utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.inl"