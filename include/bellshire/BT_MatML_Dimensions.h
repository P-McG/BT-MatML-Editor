#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Dimensions_Base : public MatML_Base
	{
	public:
		Dimensions_Base() {};
		virtual ~Dimensions_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Geometry::Dimensions_type> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Dimensions.inl"



