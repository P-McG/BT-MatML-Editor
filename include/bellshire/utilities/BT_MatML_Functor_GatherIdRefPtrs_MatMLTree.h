#pragma once


#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

#include "bellshire/utilities/BT_MatML_has_a_idref.h"

#include <type_traits>
#include <list>
#include <vector>

namespace bellshire::utilities
{
    class Functor_GatherIdRefPtrs_MatMLTree
    {
    public:

        struct Data {
            using Gather_type = ::std::vector<::xml_schema::idref*>;

            Gather_type& gather_;
        };

        Data& data_;//!< Data to be used during tree transveral, ref. for back fed data.

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="data_in"></param>
        Functor_GatherIdRefPtrs_MatMLTree(Functor_GatherIdRefPtrs_MatMLTree::Data& data
        ) : data_(data)
        {}

        /// <summary>
        /// Ctor Function to Setup the next child functor.
        /// </summary>
        /// <param name="func"></param>
        Functor_GatherIdRefPtrs_MatMLTree(Functor_GatherIdRefPtrs_MatMLTree& func)
            :data_(func.data_)
        {}

        template<class MatML>
            void operator()(observer_ptr<MatML> element);

    };

};//end namespace bellshire

#include "bellshire/utilities/BT_MatML_Functor_GatherIdRefPtrs_MatMLTree.inl"
