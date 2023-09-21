#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Shape.h"
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_Graphs.h"

namespace bellshire
{
	template<class func_class>
	void Shape_Base::TraverseMatMLTree(
		observer_ptr<Geometry::Shape_type> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert from a weakly typed to a strongly typed required by the specialization of this functor

		if (element) {
			 auto element_strongly_typed_shared = std::make_shared<Shape>(element);

			func.operator()(observer_ptr<Shape>(element_strongly_typed_shared.get()));//Setup current
		}
	}

};//end bellshire namespace


