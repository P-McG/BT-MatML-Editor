#pragma once


#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

#include "bellshire/utilities/BT_MatML_has_a_idref.h"

#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include <type_traits>
#include <list>

namespace bellshire::utilities
{
    //class Functor_ReplaceIdRef_MatMLTree
    //{
    //public:
    //    using Find_type = ::xml_schema::idref;
    //    using Replace_type = ::xml_schema::idref;

    //    struct Data {
    //        Find_type find_;
    //        Replace_type replace_;
    //    };

    //    Data data_;//!< Data to be used during tree transversal

    //    /// <summary>
    //    /// Ctor
    //    /// </summary>
    //    /// <param name="data_in"></param>
    //    Functor_ReplaceIdRef_MatMLTree(Functor_ReplaceIdRef_MatMLTree::Data data
    //    ) : data_(data)
    //    {}

    //    /// <summary>
    //    /// Ctor Function to Setup the next child functor.
    //    /// </summary>
    //    /// <param name="func"></param>
    //    Functor_ReplaceIdRef_MatMLTree(Functor_ReplaceIdRef_MatMLTree& func)
    //        :data_(func.data_)
    //    {}

    //    template<class MatML>
    //        wxTreeItemId operator()(const observer_ptr<MatML> element);

    //};

};//end namespace bellshire

#include "bellshire/utilities/BT_MatML_Functor_ReplaceIdRef_MatMLTree.inl"
