#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Units_Base : public MatML_Base
	{
	public:
		Units_Base() {};
		virtual ~Units_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Units > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Units.inl"



