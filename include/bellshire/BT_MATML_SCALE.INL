#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Scale.h"

namespace bellshire
{
	template<class func_class>
	void Scale_Base::TraverseMatMLTree(
		const observer_ptr < Scale > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


