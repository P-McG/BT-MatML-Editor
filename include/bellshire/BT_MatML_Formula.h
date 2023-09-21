#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Formula_Base : public MatML_Base
	{
	public:
		Formula_Base() {};
		virtual ~Formula_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Formula> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Formula.inl"



