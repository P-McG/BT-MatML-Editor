#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MeasurementTechniqueDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void MeasurementTechniqueDetails_Base::TraverseMatMLTree(
		const observer_ptr < MeasurementTechniqueDetails > element,
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


			SetUpChild<MeasurementTechniqueDetails,
				Name,
				MeasurementTechniqueDetails::Name_type,
				Name_Base,
				func_class
			>(element, &MeasurementTechniqueDetails::Name, next_func, recursive);


			MeasurementTechniqueDetails::Notes_optional& (MeasurementTechniqueDetails:: * structural_cont_func2)() = &MeasurementTechniqueDetails::Notes;

			SetUpChildOptional<MeasurementTechniqueDetails,
				Notes,
				MeasurementTechniqueDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}
	}

};//end bellshire namespace


