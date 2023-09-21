#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Notes_Base::TraverseMatMLTree(
		observer_ptr < Notes > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


