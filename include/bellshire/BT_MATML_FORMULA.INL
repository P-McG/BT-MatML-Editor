#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Formula.h"
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_Graphs.h"

namespace bellshire
{
	template<class func_class>
	void Formula_Base::TraverseMatMLTree(
		observer_ptr < Formula> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace

