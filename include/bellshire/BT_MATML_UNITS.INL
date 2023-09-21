#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Unit.h"
#include "bellshire/BT_MatML_Units.h"

namespace bellshire
{
	template<class func_class>
	void Units_Base::TraverseMatMLTree(
		observer_ptr < Units > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);


		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			Units::Unit_sequence& (Units:: * structural_cont_func1)() = &Units::Unit;

			SetUpChildSequence<Units,
				Unit,
				Units::Unit_sequence,
				Unit_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);
		}

	}

};//end bellshire namespace

