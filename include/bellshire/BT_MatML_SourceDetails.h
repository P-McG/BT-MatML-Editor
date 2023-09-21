#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class SourceDetails_Base : public MatML_Base
	{
	public:
		SourceDetails_Base() {};
		virtual ~SourceDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < SourceDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_SourceDetails.inl"



