#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_SourceDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void SourceDetails_Base::TraverseMatMLTree(
		observer_ptr < SourceDetails > element,
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

			SetUpChild<SourceDetails,
				Name,
				SourceDetails::Name_type,
				Name_Base,
				func_class
			>(element, &SourceDetails::Name, next_func, recursive);


			SourceDetails::Notes_optional& (SourceDetails:: * structural_cont_func2)() = &SourceDetails::Notes;

			SetUpChildOptional<SourceDetails,
				Notes,
				SourceDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);

		}
	}

};//end bellshire namespace


