#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Specification_Base : public MatML_Base
	{
	public:
		Specification_Base() {};
		virtual ~Specification_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Specification > element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Specification.inl"



