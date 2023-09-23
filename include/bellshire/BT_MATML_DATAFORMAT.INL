#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_DataFormat.h"

namespace bellshire
{
	template<class func_class>
	void DataFormat_Base::TraverseMatMLTree(
		const observer_ptr<DataFormat> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);// setup current
	}

};//end bellshire namespace

