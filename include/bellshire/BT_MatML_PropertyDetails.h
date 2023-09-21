#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class PropertyDetails_Base : public MatML_Base
	{
	public:
		PropertyDetails_Base() {};
		virtual ~PropertyDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < PropertyDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_PropertyDetails.inl"



