#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ParentMaterial.h"

namespace bellshire
{
	template<class func_class>
	void ParentMaterial_Base::TraverseMatMLTree(
		observer_ptr < ParentMaterial > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace

