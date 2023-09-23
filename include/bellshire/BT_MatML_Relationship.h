#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Relationship_Base : public MatML_Base
	{
	public:
		Relationship_Base() {};
		virtual ~Relationship_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Relationship > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Relationship.inl"



