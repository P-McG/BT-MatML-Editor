#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_SpecimenDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void SpecimenDetails_Base::TraverseMatMLTree(
		const observer_ptr < SpecimenDetails > element,
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

			SpecimenDetails::Name_optional& (SpecimenDetails:: * structural_cont_func1)() = &SpecimenDetails::Name;

			SetUpChildOptional<SpecimenDetails,
				Name,
				SpecimenDetails::Name_optional,
				Name_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);


			SpecimenDetails::Notes_optional& (SpecimenDetails:: * structural_cont_func2)() = &SpecimenDetails::Notes;

			SetUpChildOptional<SpecimenDetails,
				Notes,
				SpecimenDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}
	}

};//end bellshire namespace


