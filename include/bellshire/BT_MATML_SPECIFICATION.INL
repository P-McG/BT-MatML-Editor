#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Specification.h"

namespace bellshire
{
	template<class func_class>
	void Specification_Base::TraverseMatMLTree(
		observer_ptr < Specification > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


