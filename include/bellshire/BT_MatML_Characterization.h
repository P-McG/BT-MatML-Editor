#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Characterization_Base : public MatML_Base
	{
	public:
		Characterization_Base() {};
		virtual ~Characterization_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Characterization> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Characterization.inl"



