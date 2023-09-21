#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class ParentMaterial_Base : public MatML_Base
	{
	public:
		ParentMaterial_Base() {};
		virtual ~ParentMaterial_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < ParentMaterial > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_ParentMaterial.inl"



