#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ChemicalComposition.h"
#include "bellshire/BT_MatML_Compound.h"
#include "bellshire/BT_MatML_Element.h"

namespace bellshire
{
	template<class func_class>
	void ChemicalComposition_Base::TraverseMatMLTree(
		const observer_ptr<ChemicalComposition> element,
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

			ChemicalComposition::Compound_sequence& (ChemicalComposition:: * structural_cont_func2)() = &ChemicalComposition::Compound;

			SetUpChildSequence<ChemicalComposition,
				Compound,
				ChemicalComposition::Compound_sequence,
				Compound_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			ChemicalComposition::Element_sequence& (ChemicalComposition:: * structural_cont_func3)() = &ChemicalComposition::Element;

			SetUpChildSequence<ChemicalComposition,
				Element,
				ChemicalComposition::Element_sequence,
				Element_Base,
				func_class
			>(element, structural_cont_func3, next_func,recursive);
		}
	}

};//end bellshire namespace


