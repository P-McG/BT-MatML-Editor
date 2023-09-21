#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Abbreviation.h"

namespace bellshire
{
	template<class func_class>
	void Abbreviation_Base::TraverseMatMLTree(
		observer_ptr<GlossaryTerm::Abbreviation_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert to a strongly typed required by specialization of the functor
		observer_ptr<Abbreviation> element_strongly_typed{ std::make_shared<Abbreviation>(element).get() };

		func.operator()(element_strongly_typed);// Setup current

	}

};//end bellshire namespace

