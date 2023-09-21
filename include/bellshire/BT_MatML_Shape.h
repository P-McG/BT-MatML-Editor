#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Shape_Base : public MatML_Base
	{
	public:
		Shape_Base() {};
		virtual ~Shape_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Geometry::Shape_type> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Shape.inl"



