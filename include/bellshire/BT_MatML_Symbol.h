#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Symbol_Base : public MatML_Base
	{
	public:
		Symbol_Base() {};
		virtual ~Symbol_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Symbol > element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Symbol.inl"


