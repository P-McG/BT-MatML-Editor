#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_DimensionalDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Value.h"
#include "bellshire/BT_MatML_Units.h"
#include "bellshire/BT_MatML_Qualifier.h"
#include "bellshire/BT_MatML_Uncertainty.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void DimensionalDetails_Base::TraverseMatMLTree(
		observer_ptr<DimensionalDetails> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);// Setup current
		func_class next_func(func);// Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if(!recursive.empty()) recursive.pop_front();

			SetUpChild<DimensionalDetails,
				Name,
				DimensionalDetails::Name_type,
				Name_Base,
				func_class
			>(element, &DimensionalDetails::Name, next_func, recursive);


			SetUpChild<DimensionalDetails,
				Value,
				DimensionalDetails::Value_type,
				Value_Base,
				func_class
			>(element, &DimensionalDetails::Value, next_func, recursive);


			SetUpChild<DimensionalDetails,
				Units,
				DimensionalDetails::Units_type,
				Units_Base,
				func_class
			>(element, &DimensionalDetails::Units, next_func, recursive);


			DimensionalDetails::Qualifier_optional& (DimensionalDetails:: * structural_cont_func4)() = &DimensionalDetails::Qualifier;

			SetUpChildOptional<DimensionalDetails,
				Qualifier,
				DimensionalDetails::Qualifier_optional,
				Qualifier_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			DimensionalDetails::Uncertainty_sequence& (DimensionalDetails:: * structural_cont_func5)() = &DimensionalDetails::Uncertainty;

			SetUpChildSequence<DimensionalDetails,
				Uncertainty,
				DimensionalDetails::Uncertainty_sequence,
				Uncertainty_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);


			DimensionalDetails::Notes_optional& (DimensionalDetails:: * structural_cont_func6)() = &DimensionalDetails::Notes;

			SetUpChildOptional<DimensionalDetails,
				Notes,
				DimensionalDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func6, next_func, recursive);
		}
	}

};//end bellshire namespace


