#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Orientation.h"

namespace bellshire
{
	template<class func_class>
	void Orientation_Base::TraverseMatMLTree(
		observer_ptr<Geometry::Orientation_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert from a weakly typed to a strongly typed required by the specialization of this functor

		if (element) {
			 auto element_strongly_typed_shared = std::make_shared<Orientation>(element);

			func.operator()(observer_ptr<Orientation>(element_strongly_typed_shared.get()));//Setup current
		}
	}

};//end bellshire namespace


