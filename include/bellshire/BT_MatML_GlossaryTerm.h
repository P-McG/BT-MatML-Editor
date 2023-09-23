#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class GlossaryTerm_Base : public MatML_Base
	{
	public:
		GlossaryTerm_Base() {};
		virtual ~GlossaryTerm_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<GlossaryTerm> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_GlossaryTerm.inl"