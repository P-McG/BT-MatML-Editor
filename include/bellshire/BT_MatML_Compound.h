#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Compound_Base : public MatML_Base
	{
	public:
		Compound_Base() {};
		virtual ~Compound_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Compound> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Compound.inl"



