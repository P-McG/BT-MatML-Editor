#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Qualifier_Base : public MatML_Base
	{
	public:
		Qualifier_Base() {};
		virtual ~Qualifier_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < Qualifier > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Qualifier.inl"


