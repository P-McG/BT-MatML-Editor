#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Data1_Base : public MatML_Base
	{
	public:
		Data1_Base() {};
		virtual ~Data1_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Data1> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Data1.inl"



