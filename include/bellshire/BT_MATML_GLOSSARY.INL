#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_GlossaryTerm.h"

namespace bellshire
{
	template<class func_class>
	void Glossary_Base::TraverseMatMLTree(
		const observer_ptr<Glossary> element,
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

			Glossary::Term_sequence& (Glossary:: * structural_cont_func2)() = &Glossary::Term;

			SetUpChildSequence<Glossary,
				GlossaryTerm,
				Glossary::Term_sequence,
				GlossaryTerm_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}

	}

};//end bellshire namespace

