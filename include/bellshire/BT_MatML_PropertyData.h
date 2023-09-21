#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class PropertyData_Base : public MatML_Base
	{
	public:
		PropertyData_Base() {};
		virtual ~PropertyData_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < PropertyData > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_PropertyData.inl"



