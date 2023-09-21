#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class DataSourceDetails_Base : public MatML_Base
	{
	public:
		DataSourceDetails_Base() {};
		virtual ~DataSourceDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<DataSourceDetails> element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_DataSourceDetails.inl"



