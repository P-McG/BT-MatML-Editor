#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Unitless_Base : public MatML_Base
	{
	public:
		Unitless_Base() {};
		virtual ~Unitless_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Unitless > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Unitless.inl"



