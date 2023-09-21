#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Synonym_Base : public MatML_Base
	{
	public:
		Synonym_Base() {};
		virtual ~Synonym_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < GlossaryTerm::Synonym_type > element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Synonym.inl"



