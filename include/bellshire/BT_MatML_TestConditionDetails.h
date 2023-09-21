#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class TestConditionDetails_Base : public MatML_Base
	{
	public:
		TestConditionDetails_Base() {};
		virtual ~TestConditionDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < TestConditionDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_TestConditionDetails.inl"



