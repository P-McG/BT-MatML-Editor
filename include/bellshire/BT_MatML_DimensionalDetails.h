#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class DimensionalDetails_Base : public MatML_Base
	{
	public:
		DimensionalDetails_Base() {};
		virtual ~DimensionalDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<DimensionalDetails> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_DimensionalDetails.inl"



