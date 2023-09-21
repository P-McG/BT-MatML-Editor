#pragma once
#include "bellshire/utilities/BT_MatML_Functor_ReplaceIdRef_MatMLTree.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/utilities/BT_MatML_has_a_idref.h"

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
    wxTreeItemId Functor_ReplaceIdRef_MatMLTree
        ::operator()(const observer_ptr<MatML> element)
    {     
       Replace_IdRef(element, find_, replace_);
    };

};//end namespace bellshire

