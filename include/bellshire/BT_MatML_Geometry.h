#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Geometry_Base : public MatML_Base
	{
	public:
		Geometry_Base() {};
		virtual ~Geometry_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < Geometry > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Geometry.inl"



