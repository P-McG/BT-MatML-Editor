#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Symbol.h"

namespace bellshire
{
	template<class func_class>
	void Symbol_Base::TraverseMatMLTree(
		const observer_ptr < Symbol > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


