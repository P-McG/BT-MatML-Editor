#pragma once

#include "bellshire/matml31.hxx"
#include "Bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class Graphs_Base : public MatML_Base
	{
	public:
		Graphs_Base() {};
		virtual ~Graphs_Base() {};

		template<class cur_func_class>
		static void TraverseMatMLTree(
			observer_ptr < Graphs > Element,
			cur_func_class& cur_func,
			RecursiveFlags recursive = {}
		);

	};


}//end namespace bellshire

#include "bellshire/BT_MatML_Graphs.inl"