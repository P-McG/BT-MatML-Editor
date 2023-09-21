#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Description_Base : public MatML_Base
	{
	public:
		Description_Base() {};
		virtual ~Description_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Form::Description_type> element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Description.inl"



