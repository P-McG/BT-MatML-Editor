#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Graph_Base : public MatML_Base
	{
	public:
		Graph_Base() {};
		virtual ~Graph_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Graph > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Graph.inl"



