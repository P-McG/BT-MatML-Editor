#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class MatML_Doc_Base : public MatML_Base
	{
	public:
		MatML_Doc_Base() {};
		virtual ~MatML_Doc_Base() {};

		template< class func_class>
		static void TraverseMatMLTree(
			observer_ptr < MatML_Doc > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_MatML_Doc.inl"
