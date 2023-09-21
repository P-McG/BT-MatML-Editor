#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ParameterValue.h"
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_Graphs.h"
#include "bellshire/BT_MatML_Data.h"
#include "bellshire/BT_MatML_Uncertainty.h"
#include "bellshire/BT_MatML_Qualifier.h"

namespace bellshire
{
	template<class func_class>
	void ParameterValue_Base::TraverseMatMLTree(
		observer_ptr < ParameterValue > element,
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

			SetUpChild<ParameterValue,
				Data,
				ParameterValue::Data_type,
				Data_Base,
				func_class
			>(element, &ParameterValue::Data, next_func, recursive);


			ParameterValue::Uncertainty_sequence& (ParameterValue:: * structural_cont_func2)() = &ParameterValue::Uncertainty;

			SetUpChildSequence<ParameterValue,
				Uncertainty,
				ParameterValue::Uncertainty_sequence,
				Uncertainty_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			ParameterValue::Qualifier_sequence& (ParameterValue:: * structural_cont_func3)() = &ParameterValue::Qualifier;

			SetUpChildSequence<ParameterValue,
				Qualifier,
				ParameterValue::Qualifier_sequence,
				Qualifier_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			ParameterValue::Notes_optional& (ParameterValue:: * structural_cont_func4)() = &ParameterValue::Notes;

			SetUpChildOptional<ParameterValue,
				Notes,
				ParameterValue::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);

		}
	}

};//end bellshire namespace


