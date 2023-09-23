#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Concentration.h"
#include "bellshire/BT_MatML_Value.h"
#include "bellshire/BT_MatML_Units.h"
#include "bellshire/BT_MatML_Qualifier.h"
#include "bellshire/BT_MatML_Uncertainty.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Concentration_Base::TraverseMatMLTree(
		const observer_ptr<Concentration> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup Child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			SetUpChild<Concentration,
				Value,
				Concentration::Value_type,
				Value_Base,
				func_class
			>(element, &Concentration::Value, next_func, recursive);


			SetUpChild<Concentration,
				Units,
				Concentration::Units_type,
				Units_Base,
				func_class
			>(element, &Concentration::Units, next_func, recursive);


			Concentration::Qualifier_sequence& (Concentration:: * structural_cont_func3)() = &Concentration::Qualifier;

			SetUpChildSequence<Concentration,
				Qualifier,
				Concentration::Qualifier_sequence,
				Qualifier_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Concentration::Uncertainty_sequence& (Concentration:: * structural_cont_func4)() = &Concentration::Uncertainty;

			SetUpChildSequence<Concentration,
				Uncertainty,
				Concentration::Uncertainty_sequence,
				Uncertainty_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			Concentration::Notes_optional& (Concentration:: * structural_cont_func5)() = &Concentration::Notes;

			SetUpChildOptional<Concentration,
				Notes,
				Concentration::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);
		}

	}

};//end bellshire namespace


