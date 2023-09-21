#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"
#include <list>

namespace bellshire
{

	class BulkDetails_Base : public MatML_Base
	{
	public:
		BulkDetails_Base() {};
		virtual ~BulkDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<BulkDetails> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_BulkDetails.inl"
