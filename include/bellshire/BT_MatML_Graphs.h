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

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Graphs > element,
			func_class& func,
			RecursiveFlags recursive = {}
		);

	};


}//end namespace bellshire

#include "bellshire/BT_MatML_Graphs.inl"