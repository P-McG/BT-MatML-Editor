#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Subclass_Base : public MatML_Base
	{
	public:
		Subclass_Base() {};
		virtual ~Subclass_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Class::ParentSubClass_type> element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Subclass.inl"



