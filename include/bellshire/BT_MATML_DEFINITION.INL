#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_Definition.h"

namespace bellshire
{
	template<class func_class>
	void Definition_Base::TraverseMatMLTree(
		const observer_ptr<GlossaryTerm::Definition_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert to a strongly typed required for the specialization of the functor
		observer_ptr<Definition> test = std::make_shared<Definition>(element).get();

		func.operator()(test);// Setup current
	}

};//end bellshire namespace

