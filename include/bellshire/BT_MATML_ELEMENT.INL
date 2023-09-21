#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Element.h"
#include "bellshire/BT_MatML_Symbol.h"
#include "bellshire/BT_MatML_Concentration.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Element_Base::TraverseMatMLTree(
		observer_ptr<Element> element,
		func_class& func,
		std::list<bool> recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			SetUpChild<Element,
				Symbol,
				Element::Symbol_type,
				Symbol_Base,
				func_class
			>(element, &Element::Symbol, next_func, recursive);


			Element::Concentration_optional& (Element:: * structural_cont_func2)() = &Element::Concentration;

			SetUpChildOptional<Element,
				Concentration,
				Element::Concentration_optional,
				Concentration_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Element::Notes_optional& (Element:: * structural_cont_func3)() = &Element::Notes;

			SetUpChildOptional<Element,
				Notes,
				Element::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);
		}

	}
};//end bellshire namespace

