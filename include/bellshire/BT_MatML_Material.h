#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Material_Base: public MatML_Base
	{
	public:
		Material_Base() {};
		virtual ~Material_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Material > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Material.inl"


