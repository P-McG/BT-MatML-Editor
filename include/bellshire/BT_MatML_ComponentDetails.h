#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class ComponentDetails_Base : public MatML_Base
	{
	public:
		ComponentDetails_Base() {};
		virtual ~ComponentDetails_Base() {};

		template<class MatML_Class, class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<MatML_Class> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire 

#include "bellshire/BT_MatML_ComponentDetails.inl"
