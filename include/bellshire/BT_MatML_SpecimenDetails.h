#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class SpecimenDetails_Base : public MatML_Base
	{
	public:
		SpecimenDetails_Base() {};
		virtual ~SpecimenDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < SpecimenDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_SpecimenDetails.inl"



