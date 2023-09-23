#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ParameterDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Units.h"
#include "bellshire/BT_MatML_Unitless.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void ParameterDetails_Base::TraverseMatMLTree(
		const observer_ptr < ParameterDetails > element,
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

			SetUpChild<ParameterDetails,
				Name,
				ParameterDetails::Name_type,
				Name_Base,
				func_class
			>(element, &ParameterDetails::Name, next_func, recursive);


			ParameterDetails::Units_optional& (ParameterDetails:: * structural_cont_func2)() = &ParameterDetails::Units;

			SetUpChildOptional<ParameterDetails,
				Units,
				ParameterDetails::Units_optional,
				Units_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			ParameterDetails::Unitless_optional& (ParameterDetails:: * structural_cont_func3)() = &ParameterDetails::Unitless;

			SetUpChildOptional<ParameterDetails,
				Unitless,
				ParameterDetails::Unitless_optional,
				Unitless_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			ParameterDetails::Notes_optional& (ParameterDetails:: * structural_cont_func4)() = &ParameterDetails::Notes;

			SetUpChildOptional<ParameterDetails,
				Notes,
				ParameterDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);

		}
	}

};//end bellshire namespace


