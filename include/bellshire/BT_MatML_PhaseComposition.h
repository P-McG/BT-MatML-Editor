#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class PhaseComposition_Base : public MatML_Base
	{
	public:
		PhaseComposition_Base() {};
		virtual ~PhaseComposition_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<PhaseComposition> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_PhaseComposition.inl"



