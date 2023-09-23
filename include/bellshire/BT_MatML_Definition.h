#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class Definition_Base : public MatML_Base
	{
	public:
		Definition_Base() {};
		virtual ~Definition_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<GlossaryTerm::Definition_type> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_Definition.inl"