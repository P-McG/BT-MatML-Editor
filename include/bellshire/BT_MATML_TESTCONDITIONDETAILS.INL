#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_TestConditionDetails.h"
#include "bellshire/BT_MatML_ParameterValue.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void TestConditionDetails_Base::TraverseMatMLTree(
		observer_ptr < TestConditionDetails > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			TestConditionDetails::ParameterValue_sequence& (TestConditionDetails:: * structural_cont_func1)() = &TestConditionDetails::ParameterValue;

			SetUpChildSequence<TestConditionDetails,
				ParameterValue,
				TestConditionDetails::ParameterValue_sequence,
				ParameterValue_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);


			TestConditionDetails::Notes_optional& (TestConditionDetails:: * structural_cont_func2)() = &TestConditionDetails::Notes;

			SetUpChildOptional<TestConditionDetails,
				Notes,
				TestConditionDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}
	}

};//end bellshire namespace


