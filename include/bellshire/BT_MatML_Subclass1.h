#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Subclass1_Base : public MatML_Base
	{
	public:
		Subclass1_Base() {};
		virtual ~Subclass1_Base() {};

		template<class func_class>
		static void TraverseMatMLTree( 
			observer_ptr < ComponentDetails::Subclass_type > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Subclass1.inl"



