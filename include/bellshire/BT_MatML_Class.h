#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Class_Base : public MatML_Base
	{
	public:
		Class_Base() {};
		virtual ~Class_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Class> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Class.inl"


