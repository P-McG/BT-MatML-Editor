#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class Name_Base : public MatML_Base
	{
	public:
		Name_Base() {};
		virtual ~Name_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Name > element,
			func_class& cur_func,
			RecursiveFlags recursive = {}
		);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_Name.inl"

