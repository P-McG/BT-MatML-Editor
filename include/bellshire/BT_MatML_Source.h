#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Source_Base : public MatML_Base
	{
	public:
		Source_Base() {};
		virtual ~Source_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < Source > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Source.inl"



