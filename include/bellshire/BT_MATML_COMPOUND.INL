#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Compound.h"
#include "bellshire/BT_MatML_Element.h"
#include "bellshire/BT_MatML_Concentration.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Compound_Base::TraverseMatMLTree(
		observer_ptr<Compound> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);// Setup current
		func_class next_func(func);// Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			Compound::Element_sequence& (Compound:: * structural_cont_func2)() = &Compound::Element;

			SetUpChildSequence<Compound,
				Element,
				Compound::Element_sequence,
				Element_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Compound::Concentration_optional& (Compound:: * structural_cont_func3)() = &Compound::Concentration;

			SetUpChildOptional<Compound,
				Concentration,
				Compound::Concentration_optional,
				Concentration_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Compound::Notes_optional& (Compound:: * structural_cont_func4)() = &Compound::Notes;

			SetUpChildOptional<Compound,
				Notes,
				Compound::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace


