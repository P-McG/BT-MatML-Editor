#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class DataFormat_Base : public MatML_Base
	{
	public:
		DataFormat_Base() {};
		virtual ~DataFormat_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<DataFormat> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_DataFormat.inl"



