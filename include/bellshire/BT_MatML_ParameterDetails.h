#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class ParameterDetails_Base : public MatML_Base
	{
	public:
		ParameterDetails_Base() {};
		virtual ~ParameterDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < ParameterDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_ParameterDetails.inl"



