#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Description.h"

namespace bellshire
{
	template<class func_class>
	void Description_Base::TraverseMatMLTree(
		const observer_ptr<Form::Description_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert from a weakly typed to a strongly typed required by specialization of the functor
		if (element) {
			auto test = std::make_shared<Description>(element);

			func.operator()(observer_ptr<Description>(test.get()));//Setup current
		}
	}

};//end bellshire namespace


