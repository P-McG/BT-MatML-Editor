#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_PropertyDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Units.h"
#include "bellshire/BT_MatML_Unitless.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void PropertyDetails_Base::TraverseMatMLTree(
		const observer_ptr < PropertyDetails > element,
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


			SetUpChild<PropertyDetails,
				Name,
				PropertyDetails::Name_type,
				Name_Base,
				func_class
			>(element, &PropertyDetails::Name, next_func, recursive);


			PropertyDetails::Units_optional& (PropertyDetails:: * structural_cont_func2)() = &PropertyDetails::Units;

			SetUpChildOptional<PropertyDetails,
				Units,
				PropertyDetails::Units_optional,
				Units_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			PropertyDetails::Unitless_optional& (PropertyDetails:: * structural_cont_func3)() = &PropertyDetails::Unitless;

			SetUpChildOptional<PropertyDetails,
				Unitless,
				PropertyDetails::Unitless_optional,
				Unitless_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			PropertyDetails::Notes_optional& (PropertyDetails:: * structural_cont_func4)() = &PropertyDetails::Notes;

			SetUpChildOptional<PropertyDetails,
				Notes,
				PropertyDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace


