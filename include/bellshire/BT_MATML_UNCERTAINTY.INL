#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Uncertainty.h"
#include "bellshire/BT_MatML_Value.h"
#include "bellshire/BT_MatML_Units.h"
#include "bellshire/BT_MatML_Unitless.h"
#include "bellshire/BT_MatML_Scale.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Uncertainty_Base::TraverseMatMLTree(
		observer_ptr < Uncertainty > element,
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


			SetUpChild<Uncertainty,
				Value,
				Uncertainty::Value_type,
				Value_Base,
				func_class
			>(element, &Uncertainty::Value, next_func, recursive);


			Uncertainty::Units_optional& (Uncertainty:: * structural_cont_func2)() = &Uncertainty::Units;

			SetUpChildOptional<Uncertainty,
				Units,
				Uncertainty::Units_optional,
				Units_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Uncertainty::Unitless_optional& (Uncertainty:: * structural_cont_func3)() = &Uncertainty::Unitless;

			SetUpChildOptional<Uncertainty,
				Unitless,
				Uncertainty::Unitless_optional,
				Unitless_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Uncertainty::Scale_optional& (Uncertainty:: * structural_cont_func4)() = &Uncertainty::Scale;

			SetUpChildOptional<Uncertainty,
				Scale,
				Uncertainty::Scale_optional,
				Scale_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			Uncertainty::Notes_optional& (Uncertainty:: * structural_cont_func5)() = &Uncertainty::Notes;

			SetUpChildOptional<Uncertainty,
				Notes,
				Uncertainty::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);
		}
	}

};//end bellshire namespace

