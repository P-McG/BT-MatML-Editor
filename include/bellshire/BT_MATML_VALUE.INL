#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Value.h"

namespace bellshire
{
	template<class func_class>
	void Value_Base::TraverseMatMLTree(
		observer_ptr < Value > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


