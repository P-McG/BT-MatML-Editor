#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Result_Base : public MatML_Base
	{
	public:
		Result_Base() {};
		virtual ~Result_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Result > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Result.inl"



