#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Dimensions.h"

namespace bellshire
{
	template<class func_class>
	void Dimensions_Base::TraverseMatMLTree(
		observer_ptr<Geometry::Dimensions_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert from a weakly typed to a strongly typed required by the specialization of this functor

		if (element) {
			 auto element_strongly_typed_shared = std::make_shared<Dimensions>(element);

			func.operator()(observer_ptr<Dimensions>(element_strongly_typed_shared.get()));//Setup current
		}
	}

};//end bellshire namespace


