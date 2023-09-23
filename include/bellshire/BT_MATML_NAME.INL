#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Name.h"

namespace bellshire
{
	template<class func_class>
	void Name_Base::TraverseMatMLTree(
		const observer_ptr < Name > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


