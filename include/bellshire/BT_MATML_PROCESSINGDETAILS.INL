#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ProcessingDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_ParameterValue.h"
#include "bellshire/BT_MatML_Result.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void ProcessingDetails_Base::TraverseMatMLTree(
		observer_ptr < ProcessingDetails > element,
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

			SetUpChild<ProcessingDetails,
				Name,
				ProcessingDetails::Name_type,
				Name_Base,
				func_class
			>(element, &ProcessingDetails::Name, next_func, recursive);


			ProcessingDetails::ParameterValue_sequence& (ProcessingDetails:: * structural_cont_func2)() = &ProcessingDetails::ParameterValue;

			SetUpChildSequence<ProcessingDetails,
				ParameterValue,
				ProcessingDetails::ParameterValue_sequence,
				ParameterValue_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			//ProcessingDetails::Result_optional& (ProcessingDetails:: * structural_cont_func3)() = &ProcessingDetails::Result;

			//SetUpChildOptional<ProcessingDetails,
			//	::bellshire::Result,
			//	ProcessingDetails::Result_optional,
			//	Result_Base,
			//	func_class
			//>(element, structural_cont_func3, next_func, recursive);


			ProcessingDetails::Notes_optional& (ProcessingDetails:: * structural_cont_func4)() = &ProcessingDetails::Notes;

			SetUpChildOptional<ProcessingDetails,
				Notes,
				ProcessingDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace


