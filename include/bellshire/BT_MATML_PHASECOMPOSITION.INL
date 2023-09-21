#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_PhaseComposition.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Concentration.h"
#include "bellshire/BT_MatML_PropertyData.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void PhaseComposition_Base::TraverseMatMLTree(
		observer_ptr<PhaseComposition> element,
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

			SetUpChild<PhaseComposition,
				Name,
				PhaseComposition::Name_type,
				Name_Base,
				func_class
			>(element, &PhaseComposition::Name, next_func, recursive);


			PhaseComposition::Concentration_optional& (PhaseComposition:: * structural_cont_func2)() = &PhaseComposition::Concentration;

			SetUpChildOptional<PhaseComposition,
				Concentration,
				PhaseComposition::Concentration_optional,
				Concentration_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			PhaseComposition::PropertyData_sequence& (PhaseComposition:: * structural_cont_func3)() = &PhaseComposition::PropertyData;

			SetUpChildSequence<PhaseComposition,
				PropertyData,
				PhaseComposition::PropertyData_sequence,
				PropertyData_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			PhaseComposition::Notes_optional& (PhaseComposition:: * structural_cont_func4)() = &PhaseComposition::Notes;

			SetUpChildOptional<PhaseComposition,
				Notes,
				PhaseComposition::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace

