#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Data.h"

namespace bellshire
{
	template<class func_class>
	void Data_Base::TraverseMatMLTree(
		observer_ptr<Data> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);
	}

};//end bellshire namespace


