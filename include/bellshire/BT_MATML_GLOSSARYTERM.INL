#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_GlossaryTerm.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Definition.h"
#include "bellshire/BT_MatML_Synonym.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void GlossaryTerm_Base::TraverseMatMLTree(
		const observer_ptr < GlossaryTerm > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup Current
		func_class next_func(func);//Setup child


		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			SetUpChild<GlossaryTerm,
				Name,
				GlossaryTerm::Name_type,
				Name_Base,
				func_class
			>(element, &GlossaryTerm::Name, next_func, recursive);


			SetUpChild<GlossaryTerm,
				::bellshire::Definition,
				GlossaryTerm::Definition_type,
				Definition_Base,
				func_class
			>(element, &GlossaryTerm::Definition, next_func, recursive);


			GlossaryTerm::Abbreviation_sequence& (GlossaryTerm:: * structural_cont_func3)() = &GlossaryTerm::Abbreviation;

			SetUpChildSequence<GlossaryTerm,
				Abbreviation,
				GlossaryTerm::Abbreviation_sequence,
				Abbreviation_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			GlossaryTerm::Synonym_sequence& (GlossaryTerm:: * structural_cont_func4)() = &GlossaryTerm::Synonym;

			SetUpChildSequence<GlossaryTerm,
				Synonym,
				GlossaryTerm::Synonym_sequence,
				Synonym_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);



			GlossaryTerm::Notes_optional& (GlossaryTerm:: * structural_cont_func5)() = &GlossaryTerm::Notes;

			SetUpChildOptional<GlossaryTerm,
				Notes,
				GlossaryTerm::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);
		}

	
	}

};//end bellshire namespace

