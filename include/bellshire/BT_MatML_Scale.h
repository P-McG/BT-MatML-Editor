#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Scale_Base : public MatML_Base
	{
	public:
		Scale_Base() {};
		virtual ~Scale_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < Scale > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Scale.inl"



