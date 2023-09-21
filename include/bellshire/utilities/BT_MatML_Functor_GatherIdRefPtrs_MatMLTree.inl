#pragma once
#include "bellshire/utilities/BT_MatML_Functor_GatherIdRefPtrs_MatMLTree.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/utilities/BT_MatML_Get_IdRefPtrs.h"

namespace bellshire::utilities
{

    /// <summary>
    /// Main evaluation function
    /// </summary>
    /// <typeparam name="MatML"></typeparam>
    /// <typeparam name="MatML_GUI"></typeparam>
    /// <param name="Element"></param>
    /// <returns></returns>
    template<class MatML >
    void Functor_GatherIdRefPtrs_MatMLTree
        ::operator()(observer_ptr<MatML> element)
    {     
       Get_IdRefPtrs idrefptrs(element);
       
       data_.gather_.insert(data_.gather_.end(), idrefptrs.value.begin(), idrefptrs.value.end());
    };

};//end namespace bellshire

