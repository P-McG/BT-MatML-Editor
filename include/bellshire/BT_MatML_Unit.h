#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Unit_Base : public MatML_Base
	{
	public:
		Unit_Base() {};
		virtual ~Unit_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < Unit > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Unit.inl"


