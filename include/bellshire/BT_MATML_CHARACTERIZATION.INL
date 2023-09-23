#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Characterization.h"
#include "bellshire/BT_MatML_Formula.h"
#include "bellshire/BT_MatML_ChemicalComposition.h"
#include "bellshire/BT_MatML_PhaseComposition.h"
#include "bellshire/BT_MatML_DimensionalDetails.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Characterization_Base::TraverseMatMLTree(
		const observer_ptr<Characterization> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if(!recursive.empty()) recursive.pop_front();

			SetUpChild<Characterization,
				Formula,
				Characterization::Formula_type,
				Formula_Base,
				func_class
			>(element, &Characterization::Formula, next_func, recursive);


			Characterization::ChemicalComposition_optional& (Characterization:: * structural_cont_func2)() = &Characterization::ChemicalComposition;

			SetUpChildOptional<Characterization,
				ChemicalComposition,
				Characterization::ChemicalComposition_optional,
				ChemicalComposition_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Characterization::PhaseComposition_sequence& (Characterization:: * structural_cont_func3)() = &Characterization::PhaseComposition;

			SetUpChildSequence<Characterization,
				PhaseComposition,
				Characterization::PhaseComposition_sequence,
				PhaseComposition_Base,
				func_class
			>(element, structural_cont_func3, next_func,recursive);


			Characterization::DimensionalDetails_sequence& (Characterization:: * structural_cont_func4)() = &Characterization::DimensionalDetails;

			SetUpChildSequence<Characterization,
				DimensionalDetails,
				Characterization::DimensionalDetails_sequence,
				DimensionalDetails_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			Characterization::Notes_optional& (Characterization:: * structural_cont_func5)() = &Characterization::Notes;

			SetUpChildOptional<Characterization,
				Notes,
				Characterization::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);
		}
	}

};//end bellshire namespace

