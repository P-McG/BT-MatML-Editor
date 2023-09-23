#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Value_Base : public MatML_Base
	{
	public:
		Value_Base() {};
		virtual ~Value_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Value > element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Value.inl"



