#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_MatML_Base.h"

#include <list>

namespace bellshire
{

	class Abbreviation_Base : public MatML_Base
	{
	public:
		Abbreviation_Base() {};
		virtual ~Abbreviation_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<GlossaryTerm::Abbreviation_type> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Abbreviation.inl"


