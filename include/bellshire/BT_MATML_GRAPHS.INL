#pragma once
#include "bellshire/BT_MatML_Graph.h"
#include "bellshire/BT_MatML_Graphs.h"

namespace bellshire
{
	template<class func_class>
	void Graphs_Base::TraverseMatMLTree(
		const observer_ptr < Graphs > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			Graphs::Graph_sequence& (Graphs:: * structural_cont_func1)() = &Graphs::Graph;

			SetUpChildSequence<Graphs,
				Graph,
				Graphs::Graph_sequence,
				Graph_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);
		}

	}

};//end bellshire namespace