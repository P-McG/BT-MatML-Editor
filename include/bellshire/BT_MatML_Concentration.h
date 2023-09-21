#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Concentration_Base : public MatML_Base
	{
	public:
		Concentration_Base() {};
		virtual ~Concentration_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Concentration> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Concentration.inl"



