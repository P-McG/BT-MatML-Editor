#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Data_Base : public MatML_Base
	{
	public:
		Data_Base() {};
		virtual ~Data_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Data> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Data.inl"



