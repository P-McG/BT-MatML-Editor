#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Graph.h"

namespace bellshire
{
	template<class func_class>
	void Graph_Base::TraverseMatMLTree(
		observer_ptr < Graph > element,
		func_class& func, 
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


