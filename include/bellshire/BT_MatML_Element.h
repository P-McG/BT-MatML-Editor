#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Element_Base : public MatML_Base
	{
	public:
		Element_Base() {};
		virtual ~Element_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Element> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Element.inl"



