#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Unit.h"

namespace bellshire
{
	template<class func_class>
	void Unit_Base::TraverseMatMLTree(
		observer_ptr < Unit > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child
	}

};//end bellshire namespace


