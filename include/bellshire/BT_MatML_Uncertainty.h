#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Uncertainty_Base : public MatML_Base
	{
	public:
		Uncertainty_Base() {};
		virtual ~Uncertainty_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Uncertainty > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Uncertainty.inl"



